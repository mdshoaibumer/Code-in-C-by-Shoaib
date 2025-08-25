#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 16
#define LOAD_FACTOR_THRESHOLD 0.75

// Hash map entry
typedef struct HashEntry {
    char* key;
    int value;
    struct HashEntry* next;
} HashEntry;

// Hash map structure
typedef struct HashMap {
    HashEntry** buckets;
    int size;
    int capacity;
} HashMap;

// CREATE: Make a new hash map
HashMap* createHashMap(int initialCapacity) {
    HashMap* map = malloc(sizeof(HashMap));
    if (!map) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    
    map->capacity = initialCapacity;
    map->size = 0;
    map->buckets = calloc(map->capacity, sizeof(HashEntry*));
    if (!map->buckets) {
        free(map);
        printf("Memory allocation failed!\n");
        return NULL;
    }
    
    printf("Created hash map with %d buckets\n", initialCapacity);
    return map;
}

// HASH FUNCTION
unsigned int hash(const char* key, int capacity) {
    unsigned int hashValue = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hashValue = hashValue * 31 + key[i];
    }
    return hashValue % capacity;
}

// CREATE ENTRY
HashEntry* createEntry(const char* key, int value) {
    HashEntry* entry = malloc(sizeof(HashEntry));
    if (!entry) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    entry->key = malloc(strlen(key) + 1);
    if (!entry->key) {
        free(entry);
        printf("Memory allocation failed!\n");
        return NULL;
    }
    strcpy(entry->key, key);
    entry->value = value;
    entry->next = NULL;
    return entry;
}

// RESIZE
void resize(HashMap* map) {
    printf("Hash map is getting full, expanding...\n");
    HashEntry** oldBuckets = map->buckets;
    int oldCapacity = map->capacity;

    map->capacity *= 2;
    map->size = 0;
    map->buckets = calloc(map->capacity, sizeof(HashEntry*));
    if (!map->buckets) {
        printf("Resize failed!\n");
        map->buckets = oldBuckets;
        map->capacity = oldCapacity;
        return;
    }

    for (int i = 0; i < oldCapacity; i++) {
        HashEntry* entry = oldBuckets[i];
        while (entry) {
            HashEntry* next = entry->next;
            unsigned int newIndex = hash(entry->key, map->capacity);
            entry->next = map->buckets[newIndex];
            map->buckets[newIndex] = entry;
            map->size++;
            entry = next;
        }
    }
    free(oldBuckets);
    printf("Expanded to %d buckets\n", map->capacity);
}

// PUT
void put(HashMap* map, const char* key, int value) {
    if (!map || !key) {
        printf("Invalid input\n");
        return;
    }
    double loadFactor = (double)map->size / map->capacity;
    if (loadFactor >= LOAD_FACTOR_THRESHOLD) {
        resize(map);
    }
    unsigned int index = hash(key, map->capacity);
    HashEntry* entry = map->buckets[index];
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            entry->value = value;
            printf("Updated '%s' = %d\n", key, value);
            return;
        }
        entry = entry->next;
    }
    HashEntry* newEntry = createEntry(key, value);
    if (!newEntry) return;
    newEntry->next = map->buckets[index];
    map->buckets[index] = newEntry;
    map->size++;
    printf("Added '%s' = %d (bucket %d)\n", key, value, index);
}

// GET
int get(HashMap* map, const char* key, int* found) {
    if (!map || !key) {
        *found = 0;
        return -1;
    }
    unsigned int index = hash(key, map->capacity);
    HashEntry* entry = map->buckets[index];
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            *found = 1;
            printf("Found '%s' = %d\n", key, entry->value);
            return entry->value;
        }
        entry = entry->next;
    }
    *found = 0;
    printf("Key '%s' not found\n", key);
    return -1;
}

// CONTAINS
int contains(HashMap* map, const char* key) {
    int found;
    get(map, key, &found);
    return found;
}

// REMOVE
int removeKey(HashMap* map, const char* key) {
    if (!map || !key) return 0;
    unsigned int index = hash(key, map->capacity);
    HashEntry* entry = map->buckets[index];
    HashEntry* prev = NULL;
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            if (prev) {
                prev->next = entry->next;
            } else {
                map->buckets[index] = entry->next;
            }
            printf("Removed '%s' = %d\n", entry->key, entry->value);
            free(entry->key);
            free(entry);
            map->size--;
            return 1;
        }
        prev = entry;
        entry = entry->next;
    }
    printf("Cannot remove '%s' - not found\n", key);
    return 0;
}

// DISPLAY
void display(HashMap* map) {
    if (!map) {
        printf("Hash map is NULL\n");
        return;
    }
    printf("\nHASH MAP CONTENTS (Size: %d, Capacity: %d)\n", map->size, map->capacity);
    printf("------------------------------------------\n");
    for (int i = 0; i < map->capacity; i++) {
        printf("Bucket %2d: ", i);
        HashEntry* entry = map->buckets[i];
        if (!entry) {
            printf("[empty]\n");
        } else {
            while (entry) {
                printf("['%s'=%d]", entry->key, entry->value);
                if (entry->next) printf(" -> ");
                entry = entry->next;
            }
            printf("\n");
        }
    }
    printf("------------------------------------------\n\n");
}

// STATISTICS
void getStatistics(HashMap* map) {
    if (!map) return;
    printf("\nHASH MAP STATISTICS\n");
    printf("-------------------\n");
    printf("Total entries: %d\n", map->size);
    printf("Total buckets: %d\n", map->capacity);
    printf("Load factor: %.2f\n", (double)map->size / map->capacity);

    int emptyBuckets = 0, maxChainLength = 0, totalCollisions = 0;
    for (int i = 0; i < map->capacity; i++) {
        int chainLength = 0;
        HashEntry* entry = map->buckets[i];
        if (!entry) {
            emptyBuckets++;
        } else {
            while (entry) {
                chainLength++;
                entry = entry->next;
            }
            if (chainLength > 1) totalCollisions += (chainLength - 1);
            if (chainLength > maxChainLength) maxChainLength = chainLength;
        }
    }
    printf("Empty buckets: %d (%.1f%%)\n", emptyBuckets, (double)emptyBuckets / map->capacity * 100);
    printf("Total collisions: %d\n", totalCollisions);
    printf("Longest chain: %d\n", maxChainLength);
    printf("Average chain length: %.2f\n", (double)map->size / (map->capacity - emptyBuckets));
    printf("-------------------\n\n");
}

// CLEANUP
void freeHashMap(HashMap* map) {
    if (!map) return;
    for (int i = 0; i < map->capacity; i++) {
        HashEntry* entry = map->buckets[i];
        while (entry) {
            HashEntry* next = entry->next;
            free(entry->key);
            free(entry);
            entry = next;
        }
    }
    free(map->buckets);
    free(map);
    printf("Hash map memory cleaned up\n");
}

// DEMO
void runDemo() {
    printf("HASH MAP DEMO - STUDENT GRADES SYSTEM\n");
    printf("======================================\n\n");
    HashMap* grades = createHashMap(INITIAL_SIZE);
    printf("Adding student grades...\n");
    put(grades, "Alice", 95);
    put(grades, "Bob", 87);
    put(grades, "Charlie", 92);
    put(grades, "Diana", 88);
    put(grades, "Eve", 91);
    put(grades, "Frank", 85);
    put(grades, "Grace", 94);
    put(grades, "Henry", 89);
    display(grades);
    int found;
    get(grades, "Alice", &found);
    get(grades, "Unknown", &found);
    printf("\nUpdating Bob's grade...\n");
    put(grades, "Bob", 90);
    printf("\nRemoving Frank...\n");
    removeKey(grades, "Frank");
    display(grades);
    getStatistics(grades);
    printf("Adding more students to trigger resize...\n");
    put(grades, "Ivy", 93);
    put(grades, "Jack", 86);
    put(grades, "Kate", 97);
    put(grades, "Leo", 84);
    put(grades, "Mia", 96);
    put(grades, "Noah", 88);
    put(grades, "Olivia", 92);
    put(grades, "Paul", 89);
    put(grades, "Quinn", 95);
    display(grades);
    getStatistics(grades);
    freeHashMap(grades);
}

// MAIN MENU
int main() {
    HashMap* map = createHashMap(INITIAL_SIZE);
    int choice;
    char key[100];
    int value, found;

    printf("INTERACTIVE HASH MAP IN C\n");
    printf("==========================\n");
    printf("Built for learning and practice\n\n");

    while (1) {
        printf("\nMENU:\n");
        printf("1. Add/Update key-value pair\n");
        printf("2. Get value by key\n");
        printf("3. Check if key exists\n");
        printf("4. Remove key\n");
        printf("5. Display all entries\n");
        printf("6. Show statistics\n");
        printf("7. Run demo\n");
        printf("8. Clear all entries\n");
        printf("9. Exit\n");
        printf("\nChoice: ");
        
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter key: ");
                scanf("%s", key);
                printf("Enter value: ");
                scanf("%d", &value);
                put(map, key, value);
                break;
            case 2:
                printf("Enter key to search: ");
                scanf("%s", key);
                get(map, key, &found);
                break;
            case 3:
                printf("Enter key to check: ");
                scanf("%s", key);
                if (contains(map, key)) {
                    printf("Key '%s' exists\n", key);
                } else {
                    printf("Key '%s' does not exist\n", key);
                }
                break;
            case 4:
                printf("Enter key to remove: ");
                scanf("%s", key);
                removeKey(map, key);
                break;
            case 5:
                display(map);
                break;
            case 6:
                getStatistics(map);
                break;
            case 7:
                printf("\n");
                runDemo();
                break;
            case 8:
                freeHashMap(map);
                map = createHashMap(INITIAL_SIZE);
                printf("Cleared all entries\n");
                break;
            case 9:
                freeHashMap(map);
                printf("Thanks for using the hash map demo!\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
