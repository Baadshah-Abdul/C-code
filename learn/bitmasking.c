#include <stdio.h>
#include <stdint.h> // For uint8_t

// Define permission flags using bit shifting
#define READ     (1 << 0)  // 0000 0001 (binary) = 1 (decimal)
#define WRITE    (1 << 1)  // 0000 0010 (binary) = 2 (decimal)
#define EXECUTE  (1 << 2)  // 0000 0100 (binary) = 4 (decimal)
#define DELETE   (1 << 3)  // 0000 1000 (binary) = 8 (decimal)

int main() {
    // Initialize permissions (none by default)
    uint8_t permissions = 0;
    
    // Grant READ and WRITE permissions
    permissions = READ | WRITE;
    printf("Permissions after adding READ + WRITE: %d\n", permissions); // Output: 3 (binary: 0011)

    // Check if a user has WRITE permission
    if (permissions & WRITE) {
        printf("User has WRITE permission.\n");
    }

    // Add EXECUTE permission
    permissions |= EXECUTE;
    printf("Permissions after adding EXECUTE: %d\n", permissions); // Output: 7 (binary: 0111)

    // Remove WRITE permission
    permissions &= ~WRITE;
    printf("Permissions after removing WRITE: %d\n", permissions); // Output: 5 (binary: 0101)

    // Check if DELETE is granted (should fail)
    if (!(permissions & DELETE)) {
        printf("User does NOT have DELETE permission.\n");
    }

    return 0;
}
