#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d", temp->data);
        if(temp->next) printf(" -> ");
        temp = temp->next;
    }
    printf("\n");
}

void insertFront(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

void insertEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* last = *head;
    while (last->next != NULL)
        last = last->next;
    last->next = newNode;
}

void insertAfterK(struct Node* head, int k, int data) {
    struct Node* temp = head;
    for (int i = 1; i < k && temp != NULL; i++)
        temp = temp->next;
    if (temp == NULL) {
        printf("List is too short\n");
        return;
    }
    struct Node* newNode = createNode(data);
    newNode->next = temp->next;
    temp->next = newNode;
}

void insertAfterValue(struct Node* head, int value, int data) {
    struct Node* temp = head;
    while (temp != NULL) {
        if (temp->data == value) {
            struct Node* newNode = createNode(data);
            newNode->next = temp->next;
            temp->next = newNode;
            return;
        }
        temp = temp->next;
    }
    printf("Value not found\n");
}

void insertBeforeK(struct Node** head, int k, int data) {
    if (k <= 1) {
        insertFront(head, data);
        return;
    }
    struct Node* current = *head;
    for (int i = 1; i < k - 1 && current != NULL; i++)
        current = current->next;
    if (current == NULL) {
        printf("List is too short\n");
        return;
    }
    struct Node* newNode = createNode(data);
    newNode->next = current->next;
    current->next = newNode;
}

void insertBeforeValue(struct Node** head, int value, int data) {
    if ((*head)->data == value) {
        insertFront(head, data);
        return;
    }
    struct Node* current = *head;
    while (current->next != NULL && current->next->data != value)
        current = current->next;
    if (current->next == NULL) {
        printf("Value not found\n");
        return;
    }
    struct Node* newNode = createNode(data);
    newNode->next = current->next;
    current->next = newNode;
}

void deleteFirst(struct Node** head) {
    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }
    struct Node* temp = *head;
    *head = (*head)->next;
    free(temp);
}

void deleteLast(struct Node** head) {
    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }
    struct Node* second_last = *head;
    while (second_last->next->next != NULL)
        second_last = second_last->next;
    free(second_last->next);
    second_last->next = NULL;
}

void deleteAfterK(struct Node* head, int k) {
    struct Node* temp = head;
    for (int i = 1; i < k && temp != NULL; i++)
        temp = temp->next;
    if (temp == NULL || temp->next == NULL) {
        printf("Invalid position\n");
        return;
    }
    struct Node* toDelete = temp->next;
    temp->next = toDelete->next;
    free(toDelete);
}

void deleteBeforeK(struct Node** head, int k) {
    if (k <= 2) {
        printf("Invalid position\n");
        return;
    }
    if (*head == NULL || (*head)->next == NULL) {
        printf("List is too short\n");
        return;
    }
    if (k == 2) {
        deleteFirst(head);
        return;
    }
    struct Node* current = *head;
    for (int i = 1; i < k - 2 && current->next != NULL; i++)
        current = current->next;
    if (current->next == NULL || current->next->next == NULL) {
        printf("Invalid position\n");
        return;
    }
    struct Node* toDelete = current->next;
    current->next = toDelete->next;
    free(toDelete);
}

void deleteKth(struct Node** head, int k) {
    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }
    if (k == 1) {
        deleteFirst(head);
        return;
    }
    struct Node* current = *head;
    for (int i = 1; i < k - 1 && current->next != NULL; i++)
        current = current->next;
    if (current->next == NULL) {
        printf("Invalid position\n");
        return;
    }
    struct Node* toDelete = current->next;
    current->next = toDelete->next;
    free(toDelete);
}

void deleteValue(struct Node** head, int value) {
    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }
    if ((*head)->data == value) {
        deleteFirst(head);
        return;
    }
    struct Node* current = *head;
    while (current->next != NULL && current->next->data != value)
        current = current->next;
    if (current->next == NULL) {
        printf("Value not found\n");
        return;
    }
    struct Node* toDelete = current->next;
    current->next = toDelete->next;
    free(toDelete);
}

void reverseList(struct Node** head) {
    struct Node* prev = NULL;
    struct Node* current = *head;
    struct Node* next;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

void sortList(struct Node** head) {
    struct Node *current, *index;
    int temp;
    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }
    for (current = *head; current != NULL; current = current->next) {
        for (index = current->next; index != NULL; index = index->next) {
            if (current->data > index->data) {
                temp = current->data;
                current->data = index->data;
                index->data = temp;
            }
        }
    }
}

bool searchElement(struct Node* head, int value) {
    struct Node* current = head;
    while (current != NULL) {
        if (current->data == value)
            return true;
        current = current->next;
    }
    return false;
}

void mergeLists(struct Node** head1, struct Node** head2) {
    if (*head1 == NULL) {
        *head1 = *head2;
        *head2 = NULL;
        return;
    }
    if (*head2 == NULL)
        return;

    struct Node* temp1 = *head1;
    while (temp1->next != NULL)
        temp1 = temp1->next;
    temp1->next = *head2;
    *head2 = NULL;

    sortList(head1);
}

void concatenateLists(struct Node** head1, struct Node** head2) {
    if (*head1 == NULL) {
        *head1 = *head2;
        *head2 = NULL;
        return;
    }
    if (*head2 == NULL)
        return;

    struct Node* temp1 = *head1;
    while (temp1->next != NULL)
        temp1 = temp1->next;
    temp1->next = *head2;
    *head2 = NULL;
}

bool areListsEqual(struct Node* head1, struct Node* head2) {
    while (head1 != NULL && head2 != NULL) {
        if (head1->data != head2->data)
            return false;
        head1 = head1->next;
        head2 = head2->next;
    }
    return (head1 == NULL && head2 == NULL);
}

int main() {
    struct Node* head = NULL;
    struct Node* head2 = NULL;
    int choice, data, k, value;
    bool equal;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Create a linked list\n");
        printf("2. Print the content of the list\n");
        printf("3. Insert an element at the front of the list\n");
        printf("4. Insert an element at the end of the list\n");
        printf("5. Insert a node after the kth node\n");
        printf("6. Insert a node after the node containing a given value\n");
        printf("7. Insert a node before the kth node\n");
        printf("8. Insert a node before the node containing a given value\n");
        printf("9. Delete the first node\n");
        printf("10. Delete the last node\n");
        printf("11. Delete a node after the kth node\n");
        printf("12. Delete a node before the kth node\n");
        printf("13. Delete the kth node\n");
        printf("14. Delete the node containing a specified value\n");
        printf("15. Find the reverse of a list\n");
        printf("16. Sort the list\n");
        printf("17. Search a given element\n");
        printf("18. Merge two lists in ascending order\n");
        printf("19. Concatenate two lists\n");
        printf("20. Check if two lists are equal\n");
        printf("21. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter number of elements: ");
                int n;
                scanf("%d", &n);
                printf("Enter elements: ");
                for (int i = 0; i < n; i++) {
                    scanf("%d", &data);
                    insertEnd(&head, data);
                }
                break;
            case 2:
                printList(head);
                break;
            case 3:
                printf("Enter element to insert at the front: ");
                scanf("%d", &data);
                insertFront(&head, data);
                break;
            case 4:
                printf("Enter element to insert at the end: ");
                scanf("%d", &data);
                insertEnd(&head, data);
                break;
            case 5:
                printf("Enter the value of k: ");
                scanf("%d", &k);
                printf("Enter element to insert after kth node: ");
                scanf("%d", &data);
                insertAfterK(head, k, data);
                break;
            case 6:
                printf("Enter the value after which to insert: ");
                scanf("%d", &value);
                printf("Enter element to insert: ");
                scanf("%d", &data);
                insertAfterValue(head, value, data);
                break;
            case 7:
                printf("Enter the value of k: ");
                scanf("%d", &k);
                printf("Enter element to insert before kth node: ");
                scanf("%d", &data);
                insertBeforeK(&head, k, data);
                break;
            case 8:
                printf("Enter the value before which to insert: ");
                scanf("%d", &value);
                printf("Enter element to insert: ");
                scanf("%d", &data);
                insertBeforeValue(&head, value, data);
                break;
            case 9:
                deleteFirst(&head);
                break;
            case 10:
                deleteLast(&head);
                break;
            case 11:
                printf("Enter the value of k: ");
                scanf("%d", &k);
                deleteAfterK(head, k);
                break;
            case 12:
                printf("Enter the value of k: ");
                scanf("%d", &k);
                deleteBeforeK(&head, k);
                break;
            case 13:
                printf("Enter the value of k: ");
                scanf("%d", &k);
                deleteKth(&head, k);
                break;
            case 14:
                printf("Enter the value to delete: ");
                scanf("%d", &value);
                deleteValue(&head, value);
                break;
            case 15:
                reverseList(&head);
                break;
            case 16:
                sortList(&head);
                break;
            case 17:
                printf("Enter the element to search: ");
                scanf("%d", &data);
                if (searchElement(head, data))
                    printf("Element found\n");
                else
                    printf("Element not found\n");
                break;
            case 18:
                printf("Enter number of elements for second list: ");
                scanf("%d", &n);
                printf("Enter elements for second list: ");
                for (int i = 0; i < n; i++) {
                    scanf("%d", &data);
                    insertEnd(&head2, data);
                }
                sortList(&head);
                sortList(&head2);
                mergeLists(&head, &head2);
                break;
            case 19:
                printf("Enter number of elements for second list: ");
                scanf("%d", &n);
                printf("Enter elements for second list: ");
                for (int i = 0; i < n; i++) {
                    scanf("%d", &data);
                    insertEnd(&head2, data);
                }
                concatenateLists(&head, &head2);
                break;
            case 20:
                printf("Enter number of elements for second list: ");
                scanf("%d", &n);
                printf("Enter elements for second list: ");
                for (int i = 0; i < n; i++) {
                    scanf("%d", &data);
                    insertEnd(&head2, data);
                }
                equal = areListsEqual(head, head2);
                if (equal)
                    printf("Lists are equal\n");
                else
                    printf("Lists are not equal\n");
                break;
            case 21:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}
