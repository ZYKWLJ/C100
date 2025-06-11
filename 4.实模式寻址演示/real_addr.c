#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

// Simulate 16-bit registers
typedef short uint16;
typedef int uint32;

int main()
{
    // Initialize random number generator
    srand((unsigned int)time(NULL));

    // 1. Generate random segment base address and offset (16-bit range)
    uint16 DS = rand() & 0xFFFF; // Segment base address (random 16-bit value)
    uint16 BX = rand() & 0xFFFF; // Segment offset (random 16-bit value)

    // 2. Virtual address = Segment base : Offset
    printf("=== Virtual Address (Logical Address) ===\n");
    printf("Segment Base (DS) = 0x%04X\n", DS);
    printf("Offset (BX)       = 0x%04X\n", BX);
    printf("Virtual Address   = 0x%04X:%04X\n", DS, BX);

    // 3. Calculate linear address (in real mode = physical address):
    //    Segment base << 4 + Offset
    uint32 linear_addr = ((uint32)DS << 4) + BX;
    uint32 physical_addr = linear_addr;

    // 4. Print linear and physical addresses
    printf("\n=== Address Translation ===\n");
    printf("Linear Address    = 0x%08X (Segment << 4 + Offset = 0x%04X<<4 + 0x%04X = 0x%08X)\n",
           linear_addr, DS, BX, linear_addr);
    printf("Physical Address  = 0x%08X (Real mode has no paging, same as linear address)\n", physical_addr);

    return 0;
}
