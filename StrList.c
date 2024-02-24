#include "StrList.h"
#include <stdio.h>
#include <string.h>

// Define the node structure
typedef struct Node {
    char* data;
    struct Node* next;
} Node;

// Define the StrList structure
struct _StrList {
    Node* head;
    size_t size;
};

// Allocate a new empty StrList
StrList* StrList_alloc() {
    StrList* list = (StrList*)malloc(sizeof(StrList));
    if (list == NULL) {
        return NULL; // Memory allocation failed
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

// Free the memory and resources allocated to StrList
void StrList_free(StrList* list) {
    if (list == NULL) return;
    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current->data); // Free the string
        free(current); // Free the node
        current = next;
    }
    free(list); // Finally, free the list structure
}

// Returns the number of elements in the StrList
size_t StrList_size(const StrList* list) {
    if (list == NULL) return 0;
    return list->size;
}

// Inserts an element in the end of the StrList
void StrList_insertLast(StrList* list, const char* data) {
    if (list == NULL) return;
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        return; // Memory allocation failed
    }
    newNode->data = strdup(data); // Copy the string
    newNode->next = NULL;

    if (list->head == NULL) {
        // If the list is empty, newNode becomes the head
        list->head = newNode;
    } else {
        // Otherwise, find the last node and insert after it
        Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    list->size++;
}

void StrList_insertAt(StrList* list, const char* data, int index) {
    if (list == NULL || index < 0 || index > list->size) return; // Index out of bounds
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        return; // Memory allocation failed
    }
    newNode->data = strdup(data); // Duplicate the string
    if (index == 0) {
        // Insert at the beginning
        newNode->next = list->head;
        list->head = newNode;
    } else {
        // Find the node before the insertion point
        Node* current = list->head;
        for (int i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    list->size++;
}

void StrList_print(const StrList* list) {
    if (list == NULL) return;
    Node* current = list->head;
    while (current != NULL) {
        printf("%s ", current->data);
        current = current->next;
    }
    printf("\n");
}
void StrList_printLength(const StrList* list) {
    if (list == NULL) printf("0\n");
    else printf("%zu\n", list->size);
}
void StrList_printAt(const StrList* list, int index) {
    if (list == NULL || index < 0 || index >= list->size) {
        printf("Index out of bounds\n");
        return;
    }
    Node* current = list->head;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }
    printf("%s\n", current->data);
}
int StrList_printLen(const StrList* list) {
    if (list == NULL) return 0;
    int totalLength = 0;
    Node* current = list->head;
    while (current != NULL) {
        totalLength += strlen(current->data);
        current = current->next;
    }
    return totalLength;
}
int StrList_count(StrList* list, const char* data) {
    if (list == NULL) return 0;
    int count = 0;
    Node* current = list->head;
    while (current != NULL) {
        if (strcmp(current->data, data) == 0) {
            ++count;
        }
        current = current->next;
    }
    return count;
}
void StrList_remove(StrList* list, const char* data) {
    if (list == NULL || list->head == NULL) return;

    Node* current = list->head;
    Node* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->data, data) == 0) {
            if (prev == NULL) { // Removing the head
                list->head = current->next;
            } else {
                prev->next = current->next;
            }
            Node* next = current->next;
            free(current->data);
            free(current);
            current = next;
            list->size--;
        } else {
            prev = current;
            current = current->next;
        }
    }
}
void StrList_removeAt(StrList* list, int index) {
    if (list == NULL || index < 0 || index >= list->size) return;

    Node* current = list->head;
    Node* prev = NULL;

    for (int i = 0; i < index && current != NULL; ++i) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) return;

    if (prev == NULL) { // Removing the head
        list->head = current->next;
    } else {
        prev->next = current->next;
    }

    free(current->data);
    free(current);
    list->size--;
}
void StrList_reverse(StrList* list) {
    if (list == NULL || list->head == NULL) return;

    Node* prev = NULL;
    Node* current = list->head;
    Node* next = NULL;

    while (current != NULL) {
        next = current->next; // Store next
        current->next = prev; // Reverse current node's pointer
        prev = current; // Move pointers one position ahead
        current = next;
    }
    list->head = prev;
}
int StrList_isEqual(const StrList* list1, const StrList* list2) {
    if (list1 == NULL || list2 == NULL) return 0;
    if (list1->size != list2->size) return 0;

    Node* current1 = list1->head;
    Node* current2 = list2->head;

    while (current1 != NULL && current2 != NULL) {
        if (strcmp(current1->data, current2->data) != 0) {
            return 0;
        }
        current1 = current1->next;
        current2 = current2->next;
    }

    return 1;
}
StrList* StrList_clone(const StrList* list) {
    if (list == NULL) return NULL;

    StrList* clone = StrList_alloc();
    if (clone == NULL) return NULL;

    Node* current = list->head;
    while (current != NULL) {
        StrList_insertLast(clone, current->data);
        current = current->next;
    }

    return clone;
}
void StrList_sort(StrList* list) {
    if (list == NULL || list->size < 2) return;

    int swapped;
    do {
        swapped = 0;
        Node* current = list->head;
        while (current != NULL && current->next != NULL) {
            if (strcmp(current->data, current->next->data) > 0) {
                char* temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = 1;
            }
            current = current->next;
        }
    } while (swapped);
}
int StrList_isSorted(StrList* list) {
    if (list == NULL || list->size < 2) return 1;

    Node* current = list->head;
    while (current != NULL && current->next != NULL) {
        if (strcmp(current->data, current->next->data) > 0) {
            return 0;
        }
        current = current->next;
    }

    return 1;
}
