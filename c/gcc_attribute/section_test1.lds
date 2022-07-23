SECTIONS
{
    . = ALIGN(8);
    __init_start = .;
    __start_init : { *(__start_init) }
    __init_end = .;
}
INSERT AFTER .rodata