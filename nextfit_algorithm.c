#include <stdio.h>
#define max 25

void main() {
    char choice; // Variable to store user input for restarting the program

    do {
        int frag[max], b[max], f[max], i, j, nb, nf, temp, highest = 0;
        static int bf[max], ff[max];
        int flag, flagn[max], fragi = 0, fragx = 0;
        int last_allocated_block = 0; // Track last allocated block for Next Fit

        printf("\n\tMemory Management Scheme - Next Fit");

        // Get number of blocks with validation
        do {
            printf("\nEnter the number of blocks (max 25): ");
            scanf("%d", &nb);
            if (nb > max) {
                printf("Error: Number of blocks cannot exceed %d. Please try again.\n", max);
            }
        } while (nb > max);

        // Get number of processes with validation
        do {
            printf("Enter the number of Processes (max 25): ");
            scanf("%d", &nf);
            if (nf > max) {
                printf("Error: Number of processes cannot exceed %d. Please try again.\n", max);
            }
        } while (nf > max);

        printf("\nEnter the size of the blocks:-\n");

        // Get block sizes
        for (i = 1; i <= nb; i++) {
            printf("Block %d: ", i);
            scanf("%d", &b[i]);
            ff[i] = i;
        }
        printf("Enter the size of the Processes :-\n");

        // Get process sizes
        for (i = 1; i <= nf; i++) {
            printf("Process %d: ", i);
            scanf("%d", &f[i]);
        }

        printf("\n\nProcess_No\tProcess_Size\tBlock_No\tBlock_Size\tFragment\n");

        // Fixed allocation logic
        for (i = 1; i <= nf; i++) {
            flag = 0; // Reset flag to indicate if the process was allocated
            int checked_blocks = 0; // Tracks how many blocks have been checked

            // Start searching from the last allocated block
            j = last_allocated_block + 1;
            while (checked_blocks < nb) {
                if (j > nb) {
                    j = 1; // Wrap around to the first block
                }
                if (f[i] <= b[j]) {
                    // Allocate the block to the process
                    flagn[j] = 1;
                    printf("%-15d\t%-15d\t%-15d\t%-15d\t", i, f[i], ff[j], b[j]);
                    b[j] = b[j] - f[i];
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
                printf("%-15d\t%-15d\t%-15s\t%-15s\t%-15s\n", i, f[i], "WAIT...", "WAIT...", "WAIT...");
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
