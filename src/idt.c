#include <stdint.h>
#include <stdbool.h>

#include "out.h"

#define IDT_MAX_DESCRIPTORS 256

/* Define the IDT entry structure */

typedef struct {
    uint16_t isr_low;
    uint16_t kernel_cs;
    uint8_t  reserved;
    uint8_t  attributes;
    uint16_t isr_high;
} __attribute__((packed)) idt_entry_t;

__attribute__((alligned(0x10))) static idt_entry_t idt[256];

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idtr_t;

static idtr_t idtr;

__attribute__((NORETURN)) void exception_handler(void);
void exception_handler(void) {

    outlf("Exception occurred!");
    __asm__ __volatile__("cli; hlt");
}

void idt_set_descriptor(int vector, void *isr, uint8_t flags);
void idt_set_descriptor(int vector, void *isr, uint8_t flags) {
    idt_entry_t *descriptor = &idt[vector];

    descriptor->isr_low = (uint32_t)isr & 0xFFFF;
    descriptor->kernel_cs = 0x08; // Kernel code segment offset
    descriptor->attributes = flags;
    descriptor->isr_high = (uint32_t)isr >> 16;  
    descriptor->reserved = 0;
}

static bool vector_initialized[IDT_MAX_DESCRIPTORS];

extern void* isr_stub_table[];

void idt_init(void);
void idt_init(void) {

    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;

    for(uint8_t vector = 0;vector < 32;vector++) {
        idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
        vector_initialized[vector] = true;
    }

    __asm__ __volatile__("lidt %0" : : "m"(idtr));
    __asm__ __volatile__("sti");
    outlf("IDT initialized");
}