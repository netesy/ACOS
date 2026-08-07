#include "hda.h"
#include <acos/runtime.h>
#include <kernel/memory/heap.h>

namespace acos::drivers::audio {

namespace {

// Intel HDA Registers Layout offsets
[[maybe_unused]] constexpr u32 HDA_REG_GCAP    = 0x00; // Global Capabilities
constexpr u32 HDA_REG_GCTL    = 0x08; // Global Control
[[maybe_unused]] constexpr u32 HDA_REG_WAKEEN  = 0x0C; // Wake Enable
constexpr u32 HDA_REG_STATESTS = 0x0E; // State Status (Codec wake status)
[[maybe_unused]] constexpr u32 HDA_REG_INTCTL  = 0x20; // Interrupt Control
[[maybe_unused]] constexpr u32 HDA_REG_INTSTS  = 0x24; // Interrupt Status

// CORB/RIRB Registers
constexpr u32 HDA_REG_CORBBLBASE = 0x40; // CORB Lower Base Address
constexpr u32 HDA_REG_CORBBUBASE = 0x44; // CORB Upper Base Address
constexpr u32 HDA_REG_CORBWP     = 0x48; // CORB Write Pointer
constexpr u32 HDA_REG_CORBRP     = 0x4A; // CORB Read Pointer
constexpr u32 HDA_REG_CORBCTL    = 0x4C; // CORB Control
constexpr u32 HDA_REG_CORBSIZE   = 0x4E; // CORB Size

constexpr u32 HDA_REG_RIRBBLBASE = 0x50; // RIRB Lower Base Address
constexpr u32 HDA_REG_RIRBBUBASE = 0x54; // RIRB Upper Base Address
[[maybe_unused]] constexpr u32 HDA_REG_RIRBWP     = 0x58; // RIRB Write Pointer
constexpr u32 HDA_REG_RIRBCTL    = 0x5C; // RIRB Control
constexpr u32 HDA_REG_RIRBSIZE   = 0x5E; // RIRB Size

// Stream Descriptors (Output Stream 0 is usually offset 0x80 + 0x20 * 4 = 0x100)
constexpr u32 HDA_REG_SD_CTL     = 0x00; // Stream Control
[[maybe_unused]] constexpr u32 HDA_REG_SD_STS     = 0x03; // Stream Status
[[maybe_unused]] constexpr u32 HDA_REG_SD_LPIB    = 0x04; // Link Position In Buffer
constexpr u32 HDA_REG_SD_CBL     = 0x08; // Cyclic Buffer Length
constexpr u32 HDA_REG_SD_LVI     = 0x0C; // Last Valid Index (BDL size - 1)
[[maybe_unused]] constexpr u32 HDA_REG_SD_FIFOS   = 0x10; // FIFO Size
constexpr u32 HDA_REG_SD_FMT     = 0x12; // Stream Format
constexpr u32 HDA_REG_SD_BDPL    = 0x18; // Buffer Descriptor List Pointer Low
constexpr u32 HDA_REG_SD_BDPU    = 0x1C; // Buffer Descriptor List Pointer High

struct HDA_BDL_Entry {
    u32 addr_low;
    u32 addr_high;
    u32 length;
    u32 ioc; // Interrupt On Completion (bit 0)
} __attribute__((packed));

} // namespace

IntelHDA::IntelHDA(u64 bar0) : m_bar0(bar0), m_regs(reinterpret_cast<volatile u8*>(bar0)) {}

bool IntelHDA::initialize() {
    if (!m_regs) return false;
    (void)m_bar0; // Mark m_bar0 as used to prevent compiler warning

    // 1. Reset Controller
    volatile u32* gctl = reinterpret_cast<volatile u32*>(m_regs + HDA_REG_GCTL);
    *gctl &= ~0x01; // Clear CRST (Controller Reset)
    u32 timeout = 10000;
    while ((*gctl & 0x01) && timeout > 0) {
        timeout--;
    }

    *gctl |= 0x01; // Set CRST (Exit Reset)
    timeout = 10000;
    while (!(*gctl & 0x01) && timeout > 0) {
        timeout--;
    }

    if (!(*gctl & 0x01)) return false; // Controller failed to exit reset

    // 2. Setup CORB/RIRB Ring Buffers
    static u32 corb_buffer[256] __attribute__((aligned(128)));
    static u64 rirb_buffer[256] __attribute__((aligned(128)));

    // Set CORB Base Address
    u64 corb_phys = reinterpret_cast<u64>(corb_buffer);
    *reinterpret_cast<volatile u32*>(m_regs + HDA_REG_CORBBLBASE) = corb_phys & 0xFFFFFFFF;
    *reinterpret_cast<volatile u32*>(m_regs + HDA_REG_CORBBUBASE) = (corb_phys >> 32) & 0xFFFFFFFF;

    // Set RIRB Base Address
    u64 rirb_phys = reinterpret_cast<u64>(rirb_buffer);
    *reinterpret_cast<volatile u32*>(m_regs + HDA_REG_RIRBBLBASE) = rirb_phys & 0xFFFFFFFF;
    *reinterpret_cast<volatile u32*>(m_regs + HDA_REG_RIRBBUBASE) = (rirb_phys >> 32) & 0xFFFFFFFF;

    // Configure size to 256 entries (size code 2)
    m_regs[HDA_REG_CORBSIZE] = (m_regs[HDA_REG_CORBSIZE] & ~0x03) | 2;
    m_regs[HDA_REG_RIRBSIZE] = (m_regs[HDA_REG_RIRBSIZE] & ~0x03) | 2;

    // Reset read and write pointers
    *reinterpret_cast<volatile u16*>(m_regs + HDA_REG_CORBWP) = 0;
    // Set CORBRP reset bit (bit 15)
    volatile u16* corbrp = reinterpret_cast<volatile u16*>(m_regs + HDA_REG_CORBRP);
    *corbrp |= (1 << 15);
    *corbrp &= ~(1 << 15);

    // Start CORB & RIRB (set CTL bits to 1)
    m_regs[HDA_REG_CORBCTL] = 0x02; // Enable CORB DMA
    m_regs[HDA_REG_RIRBCTL] = 0x02; // Enable RIRB DMA

    // 3. Enumerate connected codecs using STATESTS
    volatile u16* statests = reinterpret_cast<volatile u16*>(m_regs + HDA_REG_STATESTS);
    u16 codecs = *statests;
    (void)codecs;

    return true;
}

void IntelHDA::shutdown() {
    if (!m_regs) return;
    // Stop CORB & RIRB DMA
    m_regs[HDA_REG_CORBCTL] = 0;
    m_regs[HDA_REG_RIRBCTL] = 0;
    // Clear global control
    *reinterpret_cast<volatile u32*>(m_regs + HDA_REG_GCTL) &= ~0x01;
}

bool IntelHDA::create_stream(u32 device_id, const acos::audio::StreamConfig& config) {
    (void)device_id;
    // Configure Stream Format (PCM, 44.1kHz, 16-bit, Stereo)
    u16 format = 0;
    if (config.sample_rate == 44100) format |= (1 << 14); // 44.1kHz
    else if (config.sample_rate == 48000) format |= 0;     // 48.0kHz

    if (config.format == acos::audio::AudioFormat::PCM16) format |= (1 << 4); // 16-bit
    else if (config.format == acos::audio::AudioFormat::PCM32) format |= (5 << 4); // 32-bit (HDA format code 5)

    format |= (config.channels - 1); // Channels (0-indexed)

    // Select Output Stream 1 (Offset 0x100)
    volatile u8* sd_regs = m_regs + 0x100;
    *reinterpret_cast<volatile u16*>(sd_regs + HDA_REG_SD_FMT) = format;

    // Allocate Buffer Descriptor List (BDL)
    static HDA_BDL_Entry bdl_table[2] __attribute__((aligned(128)));
    static u8 stream_buffer_1[16384] __attribute__((aligned(128)));
    static u8 stream_buffer_2[16384] __attribute__((aligned(128)));

    u64 buf1_phys = reinterpret_cast<u64>(stream_buffer_1);
    bdl_table[0].addr_low = buf1_phys & 0xFFFFFFFF;
    bdl_table[0].addr_high = (buf1_phys >> 32) & 0xFFFFFFFF;
    bdl_table[0].length = 16384;
    bdl_table[0].ioc = 1; // Interrupt on completion

    u64 buf2_phys = reinterpret_cast<u64>(stream_buffer_2);
    bdl_table[1].addr_low = buf2_phys & 0xFFFFFFFF;
    bdl_table[1].addr_high = (buf2_phys >> 32) & 0xFFFFFFFF;
    bdl_table[1].length = 16384;
    bdl_table[1].ioc = 1;

    // Load BDL Base address
    u64 bdl_phys = reinterpret_cast<u64>(bdl_table);
    *reinterpret_cast<volatile u32*>(sd_regs + HDA_REG_SD_BDPL) = bdl_phys & 0xFFFFFFFF;
    *reinterpret_cast<volatile u32*>(sd_regs + HDA_REG_SD_BDPU) = (bdl_phys >> 32) & 0xFFFFFFFF;

    // Set cyclic buffer length (CBL)
    *reinterpret_cast<volatile u32*>(sd_regs + HDA_REG_SD_CBL) = 16384 * 2;
    // Set last valid index (LVI = 1)
    *reinterpret_cast<volatile u16*>(sd_regs + HDA_REG_SD_LVI) = 1;

    return true;
}

void IntelHDA::destroy_stream(u32 device_id) {
    (void)device_id;
    volatile u8* sd_regs = m_regs + 0x100;
    // Stop stream and clear addresses
    *reinterpret_cast<volatile u32*>(sd_regs + HDA_REG_SD_CTL) &= ~0x02; // Clear RUN bit
    *reinterpret_cast<volatile u32*>(sd_regs + HDA_REG_SD_BDPL) = 0;
    *reinterpret_cast<volatile u32*>(sd_regs + HDA_REG_SD_BDPU) = 0;
}

bool IntelHDA::submit_buffer(u32 device_id, const void* data, usize size) {
    (void)device_id;
    if (!data || size == 0) return false;

    // Copy stream samples to the cyclic DMA buffers
    volatile u8* sd_regs = m_regs + 0x100;
    // Retrieve BDL Low pointer to find the buffer destination
    u32 bdl_low = *reinterpret_cast<volatile u32*>(sd_regs + HDA_REG_SD_BDPL);
    HDA_BDL_Entry* bdl = reinterpret_cast<HDA_BDL_Entry*>(static_cast<u64>(bdl_low));

    if (bdl) {
        u64 dest_phys = (static_cast<u64>(bdl[0].addr_high) << 32) | bdl[0].addr_low;
        void* dest = reinterpret_cast<void*>(dest_phys);
        usize copy_size = (size < 16384) ? size : 16384;
        memcpy(dest, data, copy_size);
    }

    return true;
}

void IntelHDA::pause(u32 device_id) {
    (void)device_id;
    volatile u8* sd_regs = m_regs + 0x100;
    *reinterpret_cast<volatile u32*>(sd_regs + HDA_REG_SD_CTL) &= ~0x02; // Clear RUN
}

void IntelHDA::resume(u32 device_id) {
    (void)device_id;
    volatile u8* sd_regs = m_regs + 0x100;
    // Set Stream ID to 1 (upper nibble of SD_CTL, bits 23:20) and RUN bit to start DMA
    *reinterpret_cast<volatile u32*>(sd_regs + HDA_REG_SD_CTL) = (1 << 20) | 0x02;
}

void IntelHDA::stop(u32 device_id) {
    (void)device_id;
    pause(device_id);
}

} // namespace acos::drivers::audio
