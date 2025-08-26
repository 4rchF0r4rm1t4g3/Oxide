# Oxide
this os is a unix like it is inspired by unix and will later support unix commands and such
=======

### Project Structure

- `src/boot.s` — Multiboot-compliant bootloader (for GRUB)
- `src/kernel.c` — Kernel entry point
- `src/out.c` — VGA text output routines
- `src/idt.c`, `src/idt.s` — Interrupt Descriptor Table setup
- `linker.ld` — Linker script

---

### How It Was Made

#### 1. Bootloader Setups