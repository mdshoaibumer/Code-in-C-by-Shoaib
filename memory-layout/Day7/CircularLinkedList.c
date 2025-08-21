#include <stdio.h>
#include <stdlib.h>

// Circular Linked List Node Structure
struct CircularNode {
    int data;
    struct CircularNode* next;
};

// Create a new circular node
struct CircularNode* createCircularNode(int value) {
    struct CircularNode* newNode = malloc(sizeof(struct CircularNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = newNode;     // Points to itself initially
    return newNode;
}

// Insert at the beginning
struct CircularNode* insertAtBeginning(struct CircularNode* head, int value) {
    struct CircularNode* newNode = createCircularNode(value);
    
    if (head == NULL) {
        return newNode;          // Single node pointing to itself
    }
    
    // Find the last node (the one pointing to head)
    struct CircularNode* last = head;
    while (last->next != head) {
        last = last->next;
    }
    
    newNode->next = head;        // New node points to current head
    last->next = newNode;        // Last node points to new node
    
    return newNode;              // New node becomes head
}

// Insert at the end
struct CircularNode* insertAtEnd(struct CircularNode* head, int value) {
    struct CircularNode* newNode = createCircularNode(value);
    
    if (head == NULL) {
        return newNode;
    }
    
    // Find the last node
    struct CircularNode* last = head;
    while (last->next != head) {
        last = last->next;
    }
    
    last->next = newNode;        // Last node points to new node
    newNode->next = head;        // New node points to head (maintains circular nature)
    
    return head;
}

// Insert at specific position
struct CircularNode* insertAtPosition(struct CircularNode* head, int value, int position) {
    if (position == 0) {
        return insertAtBeginning(head, value);
    }
    
    if (head == NULL) {
        printf("List is empty, inserting at beginning\n");
        return insertAtBeginning(head, value);
    }
    
    struct CircularNode* newNode = createCircularNode(value);
    struct CircularNode* current = head;
    
    // Navigate to position-1
    for (int i = 0; i < position - 1; i++) {
        current = current->next;
        if (current == head) {   // We've completed a full circle
            printf("Position beyond list length, inserting at end\n");
            free(newNode);
            return insertAtEnd(head, value);
        }
    }
    
    newNode->next = current->next;
    current->next = newNode;
    
    return head;
}

// Delete node with specific value
struct CircularNode* deleteNode(struct CircularNode* head, int value) {
    if (head == NULL) {
        printf("List is empty\n");
        return NULL;
    }
    
    // If only one node and it matches
    if (head->next == head && head->data == value) {
        free(head);
        printf("Deleted %d (last node)\n", value);
        return NULL;
    }
    
    // If head node needs to be deleted
    if (head->data == value) {
        // Find the last node
        struct CircularNode* last = head;
        while (last->next != head) {
            last = last->next;
        }
        
        last->next = head->next;  // Last node points to second node
        struct CircularNode* temp = head;
        head = head->next;        // Second node becomes head
        free(temp);
        printf("Deleted %d (was head)\n", value);
        return head;
    }
    
    // Find the node to delete
    struct CircularNode* current = head;
    while (current->next != head && current->next->data != value) {
        current = current->next;
    }
    
    if (current->next == head) {
        printf("Value %d not found\n", value);
        return head;
    }
    
    struct CircularNode* nodeToDelete = current->next;
    current->next = current->next->next;
    free(nodeToDelete);
    printf("Deleted %d\n", value);
    return head;
}

// Delete at specific position
struct CircularNode* deleteAtPosition(struct CircularNode* head, int position) {
    if (head == NULL) {
        printf("List is empty\n");
        return NULL;
    }
    
    // If deleting the first node
    if (position == 0) {
        // If only one node
        if (head->next == head) {
            printf("Deleted %d from position 0 (last node)\n", head->data);
            free(head);
            return NULL;
        }
        
        // Find the last node
        struct CircularNode* last = head;
        while (last->next != head) {
            last = last->next;
        }
        
        last->next = head->next;
        printf("Deleted %d from position 0\n", head->data);
        struct CircularNode* temp = head;
        head = head->next;
        free(temp);
        return head;
    }
    
    struct CircularNode* current = head;
    
    // Navigate to position-1
    for (int i = 0; i < position - 1; i++) {
        current = current->next;
        if (current == head) {
            printf("Position out of bounds\n");
            return head;
        }
    }
    
    if (current->next == head) {
        printf("Position out of bounds\n");
        return head;
    }
    
    struct CircularNode* nodeToDelete = current->next;
    current->next = current->next->next;
    printf("Deleted %d from position %d\n", nodeToDelete->data, position);
    free(nodeToDelete);
    return head;
}

// Print the circular list (with limit to prevent infinite loop)
void printCircularList(struct CircularNode* head) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    struct CircularNode* current = head;
    printf("Circular List: ");
    
    do {
        printf("%d", current->data);
        current = current->next;
        if (current != head) {
            printf(" -> ");
        }
    } while (current != head);
    
    printf(" -> (back to %d...)\n", head->data);
}

// Print with cycle indication
void printWithCycleInfo(struct CircularNode* head, int maxNodes) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    struct CircularNode* current = head;
    printf("Showing first %d nodes: ", maxNodes);
    
    for (int i = 0; i < maxNodes && current != NULL; i++) {
        printf("%d", current->data);
        if (i < maxNodes - 1) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf(" -> ...(circular)\n");
}

// Search for a value
int searchCircular(struct CircularNode* head, int value) {
    if (head == NULL) {
        return -1;
    }
    
    struct CircularNode* current = head;
    int position = 0;
    
    do {
        if (current->data == value) {
            return position;
        }
        current = current->next;
        position++;
    } while (current != head);
    
    return -1;
}

// Get length of circular list
int getCircularLength(struct CircularNode* head) {
    if (head == NULL) {
        return 0;
    }
    
    struct CircularNode* current = head;
    int count = 0;
    
    do {
        count++;
        current = current->next;
    } while (current != head);
    
    return count;
}

// Check if list is circular (for verification)
int isCircular(struct CircularNode* head) {
    if (head == NULL) {
        return 1;  // Empty list is considered circular
    }
    
    struct CircularNode* current = head->next;
    
    while (current != NULL && current != head) {
        current = current->next;
    }
    
    return (current == head);
}

// Split circular list into two halves
void splitCircularList(struct CircularNode* head, struct CircularNode** head1, struct CircularNode** head2) {
    if (head == NULL || head->next == head) {
        *head1 = head;
        *head2 = NULL;
        return;
    }
    
    struct CircularNode* slow = head;
    struct CircularNode* fast = head;
    
    // Find middle using slow-fast pointer technique
    while (fast->next != head && fast->next->next != head) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    // If even number of nodes, adjust fast
    if (fast->next->next == head) {
        fast = fast->next;
    }
    
    // Split the list
    *head1 = head;
    *head2 = slow->next;
    
    slow->next = head;        // First half becomes circular
    fast->next = *head2;      // Second half becomes circular
}

// Free circular list memory
void freeCircularList(struct CircularNode* head) {
    if (head == NULL) {
        return;
    }
    
    struct CircularNode* current = head;
    struct CircularNode* next;
    
    do {
        next = current->next;
        free(current);
        current = next;
    } while (current != head);
    
    printf("Memory freed\n");
}

// Main function for circular linked list
int main() {
    struct CircularNode* head = NULL;
    int choice, value, position, maxDisplay;
    
    printf("=== Circular Linked List Operations ===\n");
    
    while (1) {
        printf("\n1. Insert at beginning\n");
        printf("2. Insert at end\n");
        printf("3. Insert at position\n");
        printf("4. Delete by value\n");
        printf("5. Delete at position\n");
        printf("6. Search\n");
        printf("7. Print list (complete cycle)\n");
        printf("8. Print with limit\n");
        printf("9. Get length\n");
        printf("10. Check if circular\n");
        printf("11. Split into two circular lists\n");
        printf("12. Exit\n");
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
                position = searchCircular(head, value);
                if (position != -1) {
                    printf("Value %d found at position %d\n", value, position);
                } else {
                    printf("Value %d not found\n", value);
                }
                break;
                
            case 7:
                printCircularList(head);
                break;
                
            case 8:
                printf("Enter max nodes to display: ");
                scanf("%d", &maxDisplay);
                printWithCycleInfo(head, maxDisplay);
                break;
                
            case 9:
                printf("Length: %d\n", getCircularLength(head));
                break;
                
            case 10:
                if (isCircular(head)) {
                    printf("List is circular\n");
                } else {
                    printf("List is NOT circular\n");
                }
                break;
                
            case 11: {
                struct CircularNode* head1 = NULL;
                struct CircularNode* head2 = NULL;
                splitCircularList(head, &head1, &head2);
                
                printf("First half: ");
                printCircularList(head1);
                printf("Second half: ");
                printCircularList(head2);
                
                // For demo, we'll use the first half as our main list
                head = head1;
                if (head2) freeCircularList(head2);
                break;
            }
                
            case 12:
                freeCircularList(head);
                printf("Goodbye!\n");
                return 0;
                
            default:
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}