#include <stdio.h>
#include <stdlib.h>

// Define the node structure
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int value) {
    struct Node* newNode = malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Insert at the beginning
struct Node* insertAtBeginning(struct Node* head, int value) {
    struct Node* newNode = createNode(value);
    newNode->next = head;
    return newNode;  // New head
}

// Insert at the end
struct Node* insertAtEnd(struct Node* head, int value) {
    struct Node* newNode = createNode(value);
    
    if (head == NULL) {
        return newNode;
    }
    
    struct Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    return head;
}

// Insert at specific position (0-indexed)
struct Node* insertAtPosition(struct Node* head, int value, int position) {
    if (position == 0) {
        return insertAtBeginning(head, value);
    }
    
    struct Node* newNode = createNode(value);
    struct Node* current = head;
    
    // Navigate to position-1
    for (int i = 0; i < position - 1 && current != NULL; i++) {
        current = current->next;
    }
    
    if (current == NULL) {
        printf("Position out of bounds\n");
        free(newNode);
        return head;
    }
    
    newNode->next = current->next;
    current->next = newNode;
    return head;
}

// Delete node with specific value
struct Node* deleteNode(struct Node* head, int value) {
    if (head == NULL) {
        printf("List is empty\n");
        return NULL;
    }
    
    // If head needs to be deleted
    if (head->data == value) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
        printf("Deleted %d from beginning\n", value);
        return head;
    }
    
    // Find the node to delete
    struct Node* current = head;
    while (current->next != NULL && current->next->data != value) {
        current = current->next;
    }
    
    if (current->next == NULL) {
        printf("Value %d not found\n", value);
        return head;
    }
    
    struct Node* nodeToDelete = current->next;
    current->next = current->next->next;
    free(nodeToDelete);
    printf("Deleted %d\n", value);
    return head;
}

// Delete at specific position
struct Node* deleteAtPosition(struct Node* head, int position) {
    if (head == NULL) {
        printf("List is empty\n");
        return NULL;
    }
    
    if (position == 0) {
        struct Node* temp = head;
        head = head->next;
        printf("Deleted %d from position 0\n", temp->data);
        free(temp);
        return head;
    }
    
    struct Node* current = head;
    for (int i = 0; i < position - 1 && current->next != NULL; i++) {
        current = current->next;
    }
    
    if (current->next == NULL) {
        printf("Position out of bounds\n");
        return head;
    }
    
    struct Node* nodeToDelete = current->next;
    current->next = current->next->next;
    printf("Deleted %d from position %d\n", nodeToDelete->data, position);
    free(nodeToDelete);
    return head;
}

// Search for a value
int search(struct Node* head, int value) {
    struct Node* current = head;
    int position = 0;
    
    while (current != NULL) {
        if (current->data == value) {
            return position;
        }
        current = current->next;
        position++;
    }
    return -1;  // Not found
}

// Get length of list
int getLength(struct Node* head) {
    int count = 0;
    struct Node* current = head;
    
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// Print the entire list
void printList(struct Node* head) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    struct Node* current = head;
    printf("List: ");
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf(" -> NULL\n");
}

// Free all memory
void freeList(struct Node* head) {
    struct Node* current = head;
    struct Node* next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    printf("Memory freed\n");
}

// Reverse the linked list
struct Node* reverseList(struct Node* head) {
    struct Node* prev = NULL;
    struct Node* current = head;
    struct Node* next = NULL;
    
    while (current != NULL) {
        next = current->next;    // Store next
        current->next = prev;    // Reverse current node's pointer
        prev = current;          // Move pointers one position ahead
        current = next;
    }
    return prev;  // prev is new head
}

// Main function with menu
int main() {
    struct Node* head = NULL;
    int choice, value, position;
    
    printf("=== Linked List Operations ===\n");
    
    while (1) {
        printf("\n1. Insert at beginning\n");
        printf("2. Insert at end\n");
        printf("3. Insert at position\n");
        printf("4. Delete by value\n");
        printf("5. Delete at position\n");
        printf("6. Search\n");
        printf("7. Print list\n");
        printf("8. Get length\n");
        printf("9. Reverse list\n");
        printf("10. Exit\n");
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
                position = search(head, value);
                if (position != -1) {
                    printf("Value %d found at position %d\n", value, position);
                } else {
                    printf("Value %d not found\n", value);
                }
                break;
                
            case 7:
                printList(head);
                break;
                
            case 8:
                printf("Length: %d\n", getLength(head));
                break;
                
            case 9:
                head = reverseList(head);
                printf("List reversed\n");
                break;
                
            case 10:
                freeList(head);
                printf("Goodbye!\n");
                return 0;
                
            default:
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}