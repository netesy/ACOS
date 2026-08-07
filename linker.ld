ENTRY(_start)

SECTIONS
{
    . = 1M;

    . = ALIGN(4096);
    _text_start = .;
    .text :
    {
        *(.text)
    }
    . = ALIGN(4096);
    _text_end = .;

    _rodata_start = .;
    .rodata :
    {
        *(.rodata)
    }
    . = ALIGN(4096);
    _rodata_end = .;

    _data_start = .;
    .data :
    {
        *(.data)
    }
    . = ALIGN(4096);
    _data_end = .;

    _bss_start = .;
    .bss :
    {
        *(COMMON)
        *(.bss)
    }
    . = ALIGN(4096);
    _bss_end = .;
    _kernel_end = .;

    /DISCARD/ :
    {
        *(.note.gnu.property)
    }
}
