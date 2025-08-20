#include <stdio.h>
#include <stdlib.h>

// Doubly Linked List Node Structure
struct DoublyNode {
    int data;
    struct DoublyNode* next;    // Points to next node
    struct DoublyNode* prev;    // Points to previous node
};

// Create a new doubly linked node
struct DoublyNode* createDoublyNode(int value) {
    struct DoublyNode* newNode = malloc(sizeof(struct DoublyNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Insert at the beginning
struct DoublyNode* insertAtBeginning(struct DoublyNode* head, int value) {
    struct DoublyNode* newNode = createDoublyNode(value);
    
    if (head != NULL) {
        head->prev = newNode;    // Current head's prev points to new node
    }
    newNode->next = head;        // New node's next points to current head
    
    return newNode;              // New node becomes head
}

// Insert at the end
struct DoublyNode* insertAtEnd(struct DoublyNode* head, int value) {
    struct DoublyNode* newNode = createDoublyNode(value);
    
    if (head == NULL) {
        return newNode;          // If list is empty
    }
    
    // Find the last node
    struct DoublyNode* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    // Connect the nodes
    current->next = newNode;
    newNode->prev = current;
    
    return head;
}

// Insert at specific position
struct DoublyNode* insertAtPosition(struct DoublyNode* head, int value, int position) {
    if (position == 0) {
        return insertAtBeginning(head, value);
    }
    
    struct DoublyNode* newNode = createDoublyNode(value);
    struct DoublyNode* current = head;
    
    // Navigate to the position
    for (int i = 0; i < position && current != NULL; i++) {
        current = current->next;
    }
    
    if (current == NULL) {
        // Insert at end if position is beyond list length
        free(newNode);
        return insertAtEnd(head, value);
    }
    
    // Insert before current node
    newNode->next = current;
    newNode->prev = current->prev;
    
    if (current->prev != NULL) {
        current->prev->next = newNode;
    } else {
        head = newNode;          // New node becomes head
    }
    current->prev = newNode;
    
    return head;
}

// Delete node with specific value
struct DoublyNode* deleteNode(struct DoublyNode* head, int value) {
    if (head == NULL) {
        printf("List is empty\n");
        return NULL;
    }
    
    struct DoublyNode* current = head;
    
    // Find the node to delete
    while (current != NULL && current->data != value) {
        current = current->next;
    }
    
    if (current == NULL) {
        printf("Value %d not found\n", value);
        return head;
    }
    
    // Update connections
    if (current->prev != NULL) {
        current->prev->next = current->next;
    } else {
        head = current->next;    // Deleting head
    }
    
    if (current->next != NULL) {
        current->next->prev = current->prev;
    }
    
    free(current);
    printf("Deleted %d\n", value);
    return head;
}

// Delete at specific position
struct DoublyNode* deleteAtPosition(struct DoublyNode* head, int position) {
    if (head == NULL) {
        printf("List is empty\n");
        return NULL;
    }
    
    struct DoublyNode* current = head;
    
    // Navigate to position
    for (int i = 0; i < position && current != NULL; i++) {
        current = current->next;
    }
    
    if (current == NULL) {
        printf("Position out of bounds\n");
        return head;
    }
    
    // Update connections
    if (current->prev != NULL) {
        current->prev->next = current->next;
    } else {
        head = current->next;
    }
    
    if (current->next != NULL) {
        current->next->prev = current->prev;
    }
    
    printf("Deleted %d from position %d\n", current->data, position);
    free(current);
    return head;
}

// Print list forward
void printListForward(struct DoublyNode* head) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    struct DoublyNode* current = head;
    printf("Forward: NULL <- ");
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" <-> ");
        }
        current = current->next;
    }
    printf(" -> NULL\n");
}

// Print list backward
void printListBackward(struct DoublyNode* head) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    // Go to the last node
    struct DoublyNode* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    printf("Backward: NULL <- ");
    while (current != NULL) {
        printf("%d", current->data);
        if (current->prev != NULL) {
            printf(" <-> ");
        }
        current = current->prev;
    }
    printf(" -> NULL\n");
}

// Search for a value
int searchDoubly(struct DoublyNode* head, int value) {
    struct DoublyNode* current = head;
    int position = 0;
    
    while (current != NULL) {
        if (current->data == value) {
            return position;
        }
        current = current->next;
        position++;
    }
    return -1;
}

// Get length of doubly linked list
int getDoublyLength(struct DoublyNode* head) {
    int count = 0;
    struct DoublyNode* current = head;
    
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// Reverse the doubly linked list
struct DoublyNode* reverseDoublyList(struct DoublyNode* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    
    struct DoublyNode* current = head;
    struct DoublyNode* temp = NULL;
    
    // Swap next and prev for all nodes
    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;     // Move to next node (which is prev now)
    }
    
    // Update head to the last node processed
    if (temp != NULL) {
        head = temp->prev;
    }
    
    return head;
}

// Free all memory
void freeDoublyList(struct DoublyNode* head) {
    struct DoublyNode* current = head;
    struct DoublyNode* next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    printf("Memory freed\n");
}

// Main function for doubly linked list
int main() {
    struct DoublyNode* head = NULL;
    int choice, value, position;
    
    printf("=== Doubly Linked List Operations ===\n");
    
    while (1) {
        printf("\n1. Insert at beginning\n");
        printf("2. Insert at end\n");
        printf("3. Insert at position\n");
        printf("4. Delete by value\n");
        printf("5. Delete at position\n");
        printf("6. Search\n");
        printf("7. Print forward\n");
        printf("8. Print backward\n");
        printf("9. Get length\n");
        printf("10. Reverse list\n");
        printf("11. Exit\n");
        printf("Choice: ");
        
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                head = insertAtBeginning(head, value);
                printf("Inserted %d at beginning\n", value);
                break;
                
            case 2:
                printf("Enter value: ");
                scanf("%d", &value);
                head = insertAtEnd(head, value);
                printf("Inserted %d at end\n", value);
                break;
                
            case 3:
                printf("Enter value: ");
                scanf("%d", &value);
                printf("Enter position: ");
                scanf("%d", &position);
                head = insertAtPosition(head, value, position);
                break;
                
            case 4:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                head = deleteNode(head, value);
                break;
                
            case 5:
                printf("Enter position to delete: ");
                scanf("%d", &position);
                head = deleteAtPosition(head, position);
                break;
                
            case 6:
                printf("Enter value to search: ");
                scanf("%d", &value);
                position = searchDoubly(head, value);
                if (position != -1) {
                    printf("Value %d found at position %d\n", value, position);
                } else {
                    printf("Value %d not found\n", value);
                }
                break;
                
            case 7:
                printListForward(head);
                break;
                
            case 8:
                printListBackward(head);
                break;
                
            case 9:
                printf("Length: %d\n", getDoublyLength(head));
                break;
                
            case 10:
                head = reverseDoublyList(head);
                printf("List reversed\n");
                break;
                
            case 11:
                freeDoublyList(head);
                printf("Goodbye!\n");
                return 0;
                
            default:
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}