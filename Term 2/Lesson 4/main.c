#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int year;
    char name[35];
    char group[10];
};

struct Node {
    struct Student data;
    struct Node* next;
};

struct LinkedList {
    struct Node* head;
};

struct Node* createNode(struct Student data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int Search(struct LinkedList L, struct Student S) {
    struct Node* current = L.head;
    while (current != NULL) {
        if (current->data.year == S.year &&
            strcmp(current->data.name, S.name) == 0 &&
            strcmp(current->data.group, S.group) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void Add(struct LinkedList* L, struct Student S) {
    struct Node* newNode = createNode(S);
    if (L->head == NULL) {
        L->head = newNode;
    } else {
        struct Node* current = L->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void AddAfter(struct LinkedList* L, struct Student S, char* key) {
    struct Node* current = L->head;
    while (current != NULL) {
        if (strcmp(current->data.name, key) == 0) {
            struct Node* newNode = createNode(S);
            newNode->next = current->next;
            current->next = newNode;
            return;
        }
        current = current->next;
    }
}

void Delete(struct LinkedList* L, char* key) {
    struct Node* current = L->head;
    struct Node* prev = NULL;
    while (current != NULL) {
        if (strcmp(current->data.name, key) == 0) {
            if (prev == NULL) {
                L->head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

int main() {
    struct LinkedList list;
    list.head = NULL;

    struct Student s_one = {2023, "Рома", "ККСО-02"};
    struct Student s_two = {2023, "Лиза", "ККСО-03"};

    Add(&list, s_one);
    Add(&list, s_two);

    printf("Результат: %s\n", Search(list, s_two) ? "Найдено" : "Не найдено");

    struct Student s_three = {2024, "Кулебяка", "ККСО-05"};
    AddAfter(&list, s_three, "Кулебяка");
    Delete(&list, "Кулебяка");
    printf("Результат: %s\n", Search(list, s_three) ? "Найдено" : "Не найдено");
}
