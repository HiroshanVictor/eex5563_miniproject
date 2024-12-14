#include <stdio.h>
#define max_size 25

void main() {
    char choice; // Variable to store user input for restarting the program

    do {
        int nb, np, b[max_size], p[max_size], frag[max_size], i, j;
        static int b_no[max_size];
        int flag, flagn[max_size], fragi = 0, fragx = 0;
        int last_allocated_block = 0; // Track last allocated block for Next Fit

        printf("\n\tMemory Management Scheme - Next Fit");

        // Get number of blocks with validation
        do {
            printf("\nEnter the number of blocks : ");
            scanf("%d", &nb);
            if (nb > max_size) {
                printf("Error: Number of blocks cannot exceed %d. Please try again.\n", max_size);
            }
        } while (nb > max_size);

        // Get number of processes with validation
        do {
            printf("Enter the number of Processes : ");
            scanf("%d", &np);
            if (np > max_size) {
                printf("Error: Number of processes cannot exceed %d. Please try again.\n", max_size);
            }
        } while (np > max_size);

        // Get block sizes
        printf("\nEnter the size of the blocks(KB):-\n");

        for (i = 1; i <= nb; i++) {
            printf("Block %d: ", i);
            scanf("%d", &b[i]);
            b_no[i] = i;
        }

        // Get process sizes
        printf("Enter the size of the Processes (KB) :-\n");

        for (i = 1; i <= np; i++) {
            printf("Process %d: ", i);
            scanf("%d", &p[i]);
        }

        // Display header
        printf("\n\nProcess_No\tProcess_Size\tBlock_No\tBlock_Size\tFragment\n");

        // Next fit memory allocation logic
        for (i = 1; i <= np; i++) {
            flag = 0; // Reset flag to indicate if the process was allocated
            int checked_blocks = 0; // Tracks how many blocks have been checked

            // Start searching from the last allocated block
            j = last_allocated_block + 1;
            while (checked_blocks < nb) {
                if (j > nb) {
                    j = 1; // Wrap around to the first block
                }
                if (p[i] <= b[j]) {
                    // Allocate the block to the process
                    flagn[j] = 1;
                    printf("%-15d\t%-15d\t%-15d\t%-15d\t", i, p[i], b_no[j], b[j]);
                    b[j] = b[j] - p[i];
                    fragi = fragi + b[j];
                    printf("%-15d\n", b[j]);
                    last_allocated_block = j; // Update the last allocated block
                    flag = 1; // Mark the process as allocated
                    break;
                }
                j++;
                checked_blocks++;
            }

            // If no block could accommodate the process
            if (flag == 0) {
                printf("%-15d\t%-15d\t%-15s\t%-15s\t%-15s\n", i, p[i], "Can not", "allocate", "process");
            }
        }

        // Calculate internal and external fragmentation
        printf("Internal Fragmentation = %d", fragi);
        for (j = 1; j <= nb; j++) {
            if (flagn[j] != 1)
                fragx = fragx + b[j];
        }
        printf("\nExternal Fragmentation = %d\n", fragx);

        // Ask the user if they want to restart the program
        printf("\nDo you want to restart the program? (y/n): ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');

    printf("\nProgram terminated. Goodbye!\n");
}
