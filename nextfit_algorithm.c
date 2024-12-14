/**
 * Program to demonstrate the Next Fit memory allocation scheme.
 *
 * Author: H.D.H.M.J. Victor
 * Register No: 421420945 (Remainder after dividing reg.no by 6 = 1)
 * Description:
 * This program allocates processes to memory blocks using the Next Fit scheme.
 * It takes input for the number of memory blocks and processes, their sizes and allocates memory blocks in a circular fashion starting from the last allocated block.
 * The program provides an option to restart and handles errors if the input exceeds predefined limits.
 */

#include <stdio.h>
#define max_size 25

void main() {
    char choice; // Variable to store user input for restarting the program

    do {
        int nb, np, b[max_size], p[max_size], i, j, last_allocated_block = 0;

        printf("\t\tRegister No: 421420945");
        printf("\n\t\tMemory Management Scheme - Next Fit\n");

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
        for (i = 0; i < nb; i++) {
            printf("Block %d: ", i + 1);
            scanf("%d", &b[i]);
        }

        // Get process sizes
        printf("\nEnter the size of the processes:\n");
        for (i = 0; i < np; i++) {
            printf("Process %d: ", i + 1);
            scanf("%d", &p[i]);
        }

        // Output table header
        printf("\n\nProcess_No\tProcess_Size(KB)\tBlock_No\tBlock_Size(KB)\tFragment(KB)\n");

        // Next fit memory allocation logic
        for (i = 0; i < np; i++) {
            int allocated = 0; //Tracks if the current process is allocated
            int blocks_checked = 0; //Ensures all blocks are checked without infinite looping
            j = last_allocated_block; //Starts searching for a block from where the last allocation

            // Allocates the process to the block.
            while (blocks_checked < nb) {
                if (p[i] <= b[j]) {
                    printf("%-15d\t%-16d\t%-15d\t%-15d\t%-d\n",
                           i + 1, p[i], j + 1, b[j], b[j] - p[i]);
                    b[j] -= p[i]; // Updates the block size after allocation
                    last_allocated_block = j; //Updates last_allocated_block to the current block index
                    allocated = 1;
                    break;
                }
                j = (j + 1) % nb; //Moves to the next block
                blocks_checked++;
            }

            // If no block could accommodate the process
            if (!allocated) {
                printf("%-15d\t%-16d\t Can not be allocated...\n", i + 1, p[i]);
            }
        }

        printf("\nDo you want to restart the program? (y/n): ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');

    printf("\nProgram terminated.\n");
}
