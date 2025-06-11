#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdint.h>

// Global Descriptor Table (GDT) Entry
typedef struct
{
    uint16_t limit_low;  // Segment limit (bits 0-15)
    uint16_t base_low;   // Segment base (bits 0-15)
    uint8_t base_middle; // Segment base (bits 16-23)
    uint8_t access;      // Access rights
    uint8_t granularity; // Granularity and flags
    uint8_t base_high;   // Segment base (bits 24-31)
} GDT_Entry;

// Segment Selector structure
typedef struct
{
    uint16_t index : 13; // Descriptor index (13 bits)
    uint16_t ti : 1;     // Table Indicator (1 bit)
    uint16_t rpl : 2;    // Requested Privilege Level (2 bits)
} Segment_Selector;

// Page Directory Entry structure
typedef struct
{
    uint32_t present : 1;     // Present flag
    uint32_t read_write : 1;  // Read/Write flag
    uint32_t user_super : 1;  // User/Supervisor flag
    uint32_t pwt : 1;         // Page-level Write-Through
    uint32_t pcd : 1;         // Page-level Cache Disable
    uint32_t accessed : 1;    // Accessed flag
    uint32_t dirty : 1;       // Dirty flag (reserved for PDE)
    uint32_t page_size : 1;   // Page Size flag
    uint32_t global : 1;      // Global flag (ignored)
    uint32_t available : 3;   // Available for system use
    uint32_t page_frame : 20; // Page Frame address (high 20 bits)
} Page_Directory_Entry;

// Page Table Entry structure
typedef struct
{
    uint32_t present : 1;     // Present flag
    uint32_t read_write : 1;  // Read/Write flag
    uint32_t user_super : 1;  // User/Supervisor flag
    uint32_t pwt : 1;         // Page-level Write-Through
    uint32_t pcd : 1;         // Page-level Cache Disable
    uint32_t accessed : 1;    // Accessed flag
    uint32_t dirty : 1;       // Dirty flag
    uint32_t pat : 1;         // Page Attribute Table
    uint32_t global : 1;      // Global flag
    uint32_t available : 3;   // Available for system use
    uint32_t page_frame : 20; // Page Frame address (high 20 bits)
} Page_Table_Entry;

// Simulated CPU Registers
typedef struct
{
    uint16_t cs; // Code Segment
    uint16_t ds; // Data Segment
    uint16_t es; // Extra Segment
    uint16_t ss; // Stack Segment
    uint16_t fs; // Additional Segment 1
    uint16_t gs; // Additional Segment 2

    uint32_t eip; // Instruction Pointer
    uint32_t eax; // General Purpose
    uint32_t ebx; // General Purpose
    uint32_t ecx; // General Purpose
    uint32_t edx; // General Purpose

    uint32_t cr0; // Control Register 0
    uint32_t cr3; // Control Register 3 (Page Directory Base)

    uint32_t gdtr;      // GDT Base Address
    uint16_t gdt_limit; // GDT Limit

    uint32_t ldtr;      // LDT Base Address
    uint16_t ldt_limit; // LDT Limit
} Registers;

// Global variables
GDT_Entry gdt[16];                         // Simulated GDT
Page_Directory_Entry page_directory[1024]; // Page Directory
Page_Table_Entry page_tables[1024][1024];  // Page Tables
Registers registers;                       // CPU Registers

// Initialize system components
void init_system()
{
    // Initialize random number generator
    srand((unsigned int)time(NULL));

    // Initialize registers
    memset(&registers, 0, sizeof(Registers));

    // Set GDT base and limit
    registers.gdtr = 0x10000;
    registers.gdt_limit = sizeof(gdt) - 1;

    // Set CR3 (Page Directory Base)
    registers.cr3 = 0x20000;

    // Initialize GDT
    for (int i = 0; i < 16; i++)
    {
        gdt[i].base_low = 0;
        gdt[i].base_middle = 0;
        gdt[i].base_high = 0;
        gdt[i].limit_low = 0xFFFF;
        gdt[i].access = 0x93;      // Present, Data Segment, Read/Write
        gdt[i].granularity = 0xCF; // 4KB granularity, 32-bit protected mode

        // Randomly set some segment bases
        if (i > 0 && rand() % 3 == 0)
        {
            uint32_t base = (rand() & 0xFFFFFF) << 8;
            gdt[i].base_low = base & 0xFFFF;
            gdt[i].base_middle = (base >> 16) & 0xFF;
            gdt[i].base_high = (base >> 24) & 0xFF;
        }
    }

    // Initialize Page Directory and Page Tables (all entries valid)
    for (int i = 0; i < 1024; i++)
    {
        page_directory[i].present = 1; // Force all PDEs to be present
        page_directory[i].read_write = 1;
        page_directory[i].user_super = 0; // Kernel mode
        page_directory[i].page_frame = (0x30000 + i * 4096) >> 12;

        // Initialize corresponding page table
        for (int j = 0; j < 1024; j++)
        {
            page_tables[i][j].present = 1; // Force all PTEs to be present
            page_tables[i][j].read_write = 1;
            page_tables[i][j].user_super = 0;
            page_tables[i][j].page_frame = (0x100000 + i * 1024 * 4096 + j * 4096) >> 12;
        }
    }

    // Set random register values
    registers.cs = (rand() & 0x1FFF) << 3;
    registers.ds = 0x0008; // Set valid data segment selector (GDT[1])
    registers.eip = rand() & 0xFFFFFF;
    registers.eax = rand() & 0xFFFFFF;
    registers.ebx = 0x1000; // Set valid offset (4KB aligned)

    // Enable Protected Mode and Paging
    registers.cr0 = 0x80010001; // PE bit(0)=1: Protected Mode, PG bit(31)=1: Paging Enabled
}

// Get segment base address from segment selector
uint32_t get_segment_base(uint16_t segment_selector)
{
    Segment_Selector selector;
    selector.index = (segment_selector >> 3) & 0x1FFF;
    selector.ti = (segment_selector >> 2) & 0x1;
    selector.rpl = segment_selector & 0x3;

    printf("\n=== Segment Selector Analysis ===\n");
    printf("Selector Value: 0x%04X\n", segment_selector);
    printf("Descriptor Index: %d (0x%03X)\n", selector.index, selector.index);
    printf("Table Indicator: %d (%s)\n", selector.ti, selector.ti ? "LDT" : "GDT");
    printf("Requested Privilege Level: %d\n", selector.rpl);

    // Determine GDT or LDT
    uint32_t table_base = (selector.ti == 0) ? registers.gdtr : registers.ldtr;
    const char *table_name = (selector.ti == 0) ? "GDT" : "LDT";

    // Calculate descriptor offset
    uint32_t descriptor_offset = selector.index * sizeof(GDT_Entry);
    uint32_t descriptor_address = table_base + descriptor_offset;

    printf("\n=== Descriptor Lookup ===\n");
    printf("Using %s Table, Base: 0x%08X\n", table_name, table_base);
    printf("Descriptor Index: %d, Offset: 0x%08X\n", selector.index, descriptor_offset);
    printf("Descriptor Address: 0x%08X\n", descriptor_address);

    // Get descriptor (simplified as direct array access)
    GDT_Entry *descriptor = &gdt[selector.index];

    // Combine segment base address
    uint32_t base_address = (descriptor->base_high << 24) |
                            (descriptor->base_middle << 16) |
                            descriptor->base_low;

    printf("\n=== Segment Base Extraction ===\n");
    printf("Descriptor Access Byte: 0x%02X\n", descriptor->access);
    printf("Descriptor Granularity Byte: 0x%02X\n", descriptor->granularity);
    printf("Segment Base Address: 0x%08X\n", base_address);

    return base_address;
}

// Real Mode address translation
uint32_t real_mode_addressing(uint16_t segment, uint16_t offset)
{
    printf("\n\n===== Real Mode Address Translation =====\n");
    printf("Segment Register: 0x%04X\n", segment);
    printf("Offset: 0x%04X\n", offset);

    // Real-mode calculation: segment<<4 + offset
    uint32_t physical_address = ((uint32_t)segment << 4) + offset;

    printf("Physical Address = segment<<4 + offset = 0x%04X<<4 + 0x%04X = 0x%08X\n",
           segment, offset, physical_address);

    return physical_address;
}

// Protected Mode address translation (no paging)
uint32_t protected_mode_addressing(uint16_t segment_selector, uint32_t offset)
{
    printf("\n\n===== Protected Mode Address Translation (No Paging) =====\n");

    // Get segment base address
    uint32_t segment_base = get_segment_base(segment_selector);

    // Calculate linear address (equals physical address without paging)
    uint32_t linear_address = segment_base + offset;

    printf("\n=== Linear Address Calculation ===\n");
    printf("Segment Base: 0x%08X\n", segment_base);
    printf("Offset: 0x%08X\n", offset);
    printf("Linear Address = Base + Offset = 0x%08X + 0x%08X = 0x%08X\n",
           segment_base, offset, linear_address);

    return linear_address;
}

// Protected Mode address translation (with paging)
uint32_t protected_mode_with_paging(uint16_t segment_selector, uint32_t offset)
{
    printf("\n\n===== Protected Mode Address Translation (With Paging) =====\n");

    // Get segment base address
    uint32_t segment_base = get_segment_base(segment_selector);

    // Calculate linear address
    uint32_t linear_address = segment_base + offset;

    printf("\n=== Linear Address Calculation ===\n");
    printf("Segment Base: 0x%08X\n", segment_base);
    printf("Offset: 0x%08X\n", offset);
    printf("Linear Address = Base + Offset = 0x%08X + 0x%08X = 0x%08X\n",
           segment_base, offset, linear_address);

    // Extract Page Directory Index (bits 22-31)
    uint32_t page_dir_index = (linear_address >> 22) & 0x3FF;
    // Extract Page Table Index (bits 12-21)
    uint32_t page_table_index = (linear_address >> 12) & 0x3FF;
    // Extract Page Offset (bits 0-11)
    uint32_t page_offset = linear_address & 0xFFF;

    printf("\n=== Linear Address Decomposition ===\n");
    printf("Linear Address: 0x%08X\n", linear_address);
    printf("Page Directory Index: %d (0x%03X)\n", page_dir_index, page_dir_index);
    printf("Page Table Index: %d (0x%03X)\n", page_table_index, page_table_index);
    printf("Page Offset: 0x%03X\n", page_offset);

    // Get Page Directory Entry
    Page_Directory_Entry *pde = &page_directory[page_dir_index];

    printf("\n=== Page Directory Lookup ===\n");
    printf("Page Directory Base (CR3): 0x%08X\n", registers.cr3);
    printf("PDE Address: 0x%08X\n", registers.cr3 + page_dir_index * 4);
    printf("PDE Value: 0x%08X\n", *(uint32_t *)pde);
    printf("PDE Status: %s\n", pde->present ? "Present" : "Not Present");

    if (!pde->present)
    {
        printf("Error: Page Directory Entry not present, triggering page fault!\n");
        return 0xFFFFFFFF; // Return invalid address
    }

    // Get Page Table Base
    uint32_t page_table_base = pde->page_frame << 12;

    // Get Page Table Entry
    Page_Table_Entry *pte = &page_tables[page_dir_index][page_table_index];

    printf("\n=== Page Table Lookup ===\n");
    printf("Page Table Base: 0x%08X\n", page_table_base);
    printf("PTE Address: 0x%08X\n", page_table_base + page_table_index * 4);
    printf("PTE Value: 0x%08X\n", *(uint32_t *)pte);
    printf("PTE Status: %s\n", pte->present ? "Present" : "Not Present");

    if (!pte->present)
    {
        printf("Error: Page Table Entry not present, triggering page fault!\n");
        return 0xFFFFFFFF; // Return invalid address
    }

    // Calculate Physical Address
    uint32_t physical_address = (pte->page_frame << 12) + page_offset;

    printf("\n=== Physical Address Calculation ===\n");
    printf("Page Frame Base: 0x%08X\n", pte->page_frame << 12);
    printf("Page Offset: 0x%03X\n", page_offset);
    printf("Physical Address = Frame Base + Offset = 0x%08X + 0x%03X = 0x%08X\n",
           pte->page_frame << 12, page_offset, physical_address);

    return physical_address;
}

void instruction()
{
    printf("instruction:\n");
    printf("cpuaddr rm: real mode\n");
    printf("cpuaddr pmnp: protected mode no paging\n");
    printf("cpuaddr pm/pmp: protected mode with paging\n");
}
int main(int argc, int *argv[])
{
    // Initialize system
    init_system();

    // Generate random segment and offset values
    uint16_t segment = rand() & 0xFFFF;
    uint16_t offset16 = rand() & 0xFFFF;
    uint32_t offset32 = 0x1000; // Use 4KB aligned offset for validity

    switch (argc)
    {
    case 1:
        instruction();
        break;

    case 2:
        if (strcmp(argv[1], "rm") == 0)
        {
            real_mode_addressing(segment, offset16);
            break;
        }
        else if (strcmp(argv[1], "pmnp") == 0)
        {
            protected_mode_addressing(registers.ds, offset32);
            break;
        }
        else if (strcmp(argv[1], "pm") == 0 || strcmp(argv[1], "pmp") == 0)
        {
            protected_mode_with_paging(registers.ds, offset32);
            break;
        }
        else
        {
            instruction();
            break;
        }
    default:
        instruction();
        break;
    }
    return 0;
}