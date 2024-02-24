#include "StrList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    StrList* list = StrList_alloc();
    if (list == NULL) {
        printf("Failed to allocate memory for the list.\n");
        return 1;
    }

   
    char input[1024];


    while (1) {
   
        int option;
       scanf("%d", &option); // Reads the option

        switch (option) {
        case 1:
            int numWords;
         
            scanf("%d", &numWords); // Reads the number of words
            while ((getchar()) != '\n'); // Clear the buffer to consume any leftover newline character

            char text[1024];

            scanf(" %[^\n]", text); // Reads a line of text until a newline is encountered, space before % to skip any leading whitespace

            // Tokenize the input text
            char *word = strtok(text, " ");
            int wordCount = 0; // Keep track of the number of words processed
            while (word != NULL && wordCount < numWords) {
                StrList_insertLast(list, word);
                word = strtok(NULL, " "); // Get the next word
                wordCount++;
            }
            break;


         case 2:
            int index;
      
            

            scanf("%d", &index); // Read index
            
            getchar(); // Consume the newline character left in the input buffer by scanf
            if (index < 0 || index > StrList_size(list)) {
                    printf("Index out of bounds\n");
                    break;
                }

            scanf("%[^\n]", input); // Read the word until a newline is encountered
            
            StrList_insertAt(list, input, index);
            break;

            case 3:
                StrList_print(list);
                break;
            case 4:
                printf("%zu\n", StrList_size(list));
                break;
            case 5:
      
                scanf("%d", &index);
                if (index < 0 || index >= StrList_size(list)-1) {
                    printf("Index out of bounds\n");
                    break;
                }
                StrList_printAt(list, index);
                break;
            case 6:
                printf("%d\n", StrList_printLen(list));
                break;
            case 7:
        
                scanf("%*c%[^\n]", input); // Read until newline, consuming any leading space
                printf("%d\n", StrList_count(list, input));
                break;
            case 8:
                scanf("%*c%[^\n]", input); // Read until newline, consuming any leading space
                StrList_remove(list, input);
                break;
            case 9:
            
                scanf("%d", &index);

                if (index < 0 || index >= StrList_size(list)) {
                    printf("Index out of bounds\n");
                    break;
                }
                StrList_removeAt(list, index);
                break;
            case 10:
                StrList_reverse(list);
                break;
            case 11:
                StrList_free(list);
                list = StrList_alloc(); // Reallocate a new empty list
                break;
            case 12:
                StrList_sort(list);
                break;
            case 13:
                printf("%s\n", StrList_isSorted(list) ? "true" : "false");
                break;
            case 0:
                StrList_free(list);
                return 0;
            default:
                printf("Invalid option.\n");
                break;
        }
        // Clear input buffer if anything is left to avoid issues with the next read
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
    }

    return 0;
}
