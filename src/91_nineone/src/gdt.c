#include "types.h"

struct gdt_entry_struct {
    uint16 limit_low;           // De nederste 16 bitene av grensen
    uint16 base_low;            // De nederste 16 bitene av basen
    uint8  base_middle;         // De neste 8 bitene av basen
    uint8  access;              // Tilgangsflagg (hva segmentet kan brukes til)
    uint8  granularity;         // Flagg for størrelse og de øverste 4 bitene av limit
    uint8  base_high;           // De siste 8 bitene av basen
} __attribute__((packed));

typedef struct gdt_entry_struct GdtEntry;

// Denne strukturen sendes til CPU-en (instruksjonen LGDT)
struct gdt_ptr_struct {
    uint16 limit;               // Størrelsen på GDT minus 1
    uint32 base;                // Adressen til den første GDT-oppføringen
} __attribute__((packed));

typedef struct gdt_ptr_struct GdtPtr;

// Vi definerer 3 entries: NULL, Code og Data
GdtEntry gdt_entries[3];
GdtPtr   gdt_ptr;

// Denne funksjonen defineres i Assembly-filen din (gdt_flush.asm)
extern void gdt_flush(uint32);

// Funksjon for å sette opp en enkelt gate i tabellen
static void gdt_set_gate(int32 num, uint32 base, uint32 limit, uint8 access, uint8 gran) {
    gdt_entries[num].base_low    = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high   = (base >> 24) & 0xFF;

    gdt_entries[num].limit_low   = (limit & 0xFFFF);
    gdt_entries[num].granularity = (limit >> 16) & 0x0F;

    gdt_entries[num].granularity |= gran & 0xF0;
    gdt_entries[num].access      = access;
}

// Hovedfunksjonen som kalles fra kernel_main
void init_gdt() {
    // Sett opp GDT-pointeren
    gdt_ptr.limit = (sizeof(GdtEntry) * 3) - 1;
    gdt_ptr.base  = (uint32)&gdt_entries;

    // 1. NULL-segmentet (Påkrevd av CPU-en, skal være bare nuller)
    gdt_set_gate(0, 0, 0, 0, 0);

    // 2. Code Segment: Base 0, Limit 4GB, Tilgang 0x9A, Granularity 0xCF
    // 0x9A betyr: Present, Ring 0, Executable, Readable
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    // 3. Data Segment: Base 0, Limit 4GB, Tilgang 0x92, Granularity 0xCF
    // 0x92 betyr: Present, Ring 0, Writable
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    // Fortell CPU-en om den nye tabellen via Assembly-funksjonen
    gdt_flush((uint32)&gdt_ptr);
}