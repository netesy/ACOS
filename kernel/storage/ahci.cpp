#include <kernel/storage/ahci.h>
#include <kernel/memory/pmm.h>
#include <acos/runtime.h>
#include <kernel/hal/serial.h>

namespace acos::hal {
    void serial_print(const char* s);
}

namespace acos::storage {

struct HBACommandHeader {
    u8  cfl:5;
    u8  a:1;
    u8  w:1;
    u8  p:1;
    u8  r:1;
    u8  b:1;
    u8  c:1;
    u8  rsv0:1;
    u8  pmp:4;
    u16 prdtl;
    u32 prdbc;
    u32 ctba;
    u32 ctbau;
    u32 rsv1[4];
};

struct HBAPRDTEntry {
    u32 dba;
    u32 dbau;
    u32 rsv0;
    u32 dbc:22;
    u32 rsv1:9;
    u32 i:1;
};

struct HBACommandTable {
    u8  cfis[64];
    u8  acmd[16];
    u8  rsv[48];
    HBAPRDTEntry prdt_entry[1];
};

struct FIS_REG_H2D {
    u8  fis_type;
    u8  pmport:4;
    u8  rsv0:3;
    u8  c:1;
    u8  command;
    u8  featurel;
    u8  lba0;
    u8  lba1;
    u8  lba2;
    u8  device;
    u8  lba3;
    u8  lba4;
    u8  lba5;
    u8  featureh;
    u8  countl;
    u8  counth;
    u8  icc;
    u8  control;
    u8  rsv1[4];
};

AHCIController::AHCIController(u64 base_addr) : m_base_addr(base_addr) {}

bool AHCIController::initialize() {
    if (!m_base_addr) return false;
    volatile u32* hba_mem = reinterpret_cast<volatile u32*>(m_base_addr);
    hba_mem[1] |= 0x80000000; // GHC.AE
    u32 pi = hba_mem[3];
    for (u32 i = 0; i < 32; i++) {
        if (pi & (1 << i)) {
            volatile u32* port_reg = hba_mem + (0x100 / 4) + (i * 0x80 / 4);
            if ((port_reg[10] & 0x0F) == 0x03) {
                AHCIPort* port = new AHCIPort(i, (void*)port_reg);
                port->configure();
                m_ports[m_port_count++] = port;
            }
        }
    }
    return m_port_count > 0;
}

AHCIPort::AHCIPort(u32 port_num, void* hba_port_reg)
    : m_port_num(port_num), m_reg(hba_port_reg), m_capacity(256ULL * 1024 * 1024) {}

void AHCIPort::configure() {
    volatile u32* port = (volatile u32*)m_reg;
    port[6] &= ~0x0001;
    port[6] &= ~0x0010;
    while (port[6] & 0x8000 || port[6] & 0x4000);
    u64 cl_phys = acos::memory::pmm_alloc();
    u64 fis_phys = acos::memory::pmm_alloc();
    port[0] = (u32)cl_phys;
    port[1] = (u32)(cl_phys >> 32);
    port[2] = (u32)fis_phys;
    port[3] = (u32)(fis_phys >> 32);
    for (int i = 0; i < 32; i++) {
        m_ctba[i] = acos::memory::pmm_alloc();
        HBACommandHeader* cmd_header = (HBACommandHeader*)cl_phys + i;
        cmd_header->ctba = (u32)m_ctba[i];
        cmd_header->ctbau = (u32)(m_ctba[i] >> 32);
        cmd_header->cfl = 0;
    }
    port[6] |= 0x0010;
    port[6] |= 0x0001;
}

int AHCIPort::find_cmd_slot() {
    u32 slots = ((volatile u32*)m_reg)[13] | ((volatile u32*)m_reg)[14];
    for (int i = 0; i < 32; i++) if (!((slots >> i) & 1)) return i;
    return -1;
}

i32 AHCIPort::read_block(u64 block_id, void* buffer) {
    volatile u32* port = (volatile u32*)m_reg;
    int slot = find_cmd_slot();
    if (slot == -1) return -1;
    u64 cl_base = ((u64)port[1] << 32) | port[0];
    HBACommandHeader* cmd_header = (HBACommandHeader*)cl_base + slot;
    cmd_header->cfl = sizeof(FIS_REG_H2D) / sizeof(u32);
    cmd_header->w = 0;
    cmd_header->prdtl = 1;
    HBACommandTable* cmd_table = (HBACommandTable*)m_ctba[slot];
    memset(cmd_table, 0, 256);
    cmd_table->prdt_entry[0].dba = (u32)(u64)buffer;
    cmd_table->prdt_entry[0].dbau = (u32)((u64)buffer >> 32);
    cmd_table->prdt_entry[0].dbc = 511;
    cmd_table->prdt_entry[0].i = 1;
    FIS_REG_H2D* fis = (FIS_REG_H2D*)(&cmd_table->cfis);
    fis->fis_type = 0x27; fis->c = 1; fis->command = 0x25;
    fis->lba0 = (u8)block_id; fis->lba1 = (u8)(block_id >> 8); fis->lba2 = (u8)(block_id >> 16);
    fis->device = 1 << 6; fis->lba3 = (u8)(block_id >> 24); fis->lba4 = (u8)(block_id >> 32);
    fis->lba5 = (u8)(block_id >> 40); fis->countl = 1; fis->counth = 0;
    port[4] = 0xFFFFFFFF; port[14] = 1 << slot;
    while (port[14] & (1 << slot)) if (port[4] & 0x40000000) return -1;
    return 0;
}

i32 AHCIPort::write_block(u64 b, const void* d) { (void)b; (void)d; return -1; }
void AHCIPort::flush() {}
}
