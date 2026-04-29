#include "idt.h"
#include "isr.h"



__attribute__((aligned(0x10))) 
static idt_entry_t idt[IDT_MAX_DESCRIPTORS]; // Create an array of IDT entries; aligned for performance

static idtr_t idtr;

extern void* isr_stub_table[];

static void idt_memset(void* dest, uint8_t value, uint32_t length) {
    uint8_t* ptr = (uint8_t*) dest;

    for (uint32_t i = 0; i < length; i++) {
        ptr[i] = value;
    }
}

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) {
    idt_entry_t* descriptor = &idt[vector];

    descriptor->isr_low = (uint32_t)isr & 0xFFFF;
    descriptor->kernel_cs = 0x08;
    descriptor->attributes = flags;
    descriptor->isr_high = ((uint32_t)isr >> 16) & 0xFFFF;
    descriptor->reserved = 0;
}

void idt_init(void) { 
    idtr.base = (uint32_t)&idt[0];
    idtr.limit = (uint16_t)(sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1);
   
    idt_memset(&idt, 0, sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS);

    for (uint8_t vector = 0; vector < 4; vector++) {
        idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
    }

    __asm__ volatile ("lidt %0" : : "m"(idtr));
}