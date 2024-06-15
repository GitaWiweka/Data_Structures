#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int angka;
    struct node* prev;
    struct node* next;
} node;

//membuat node baru
node* BuatNode(int angka) {
    node* Newnode = (node*)malloc(sizeof(node));
    Newnode->angka = angka;
    Newnode->prev = NULL;
    Newnode->next = NULL;
    return Newnode;
}

//insert node didepan
void InsertDepan(node** head, int angka) {
    node* Newnode = BuatNode(angka);
    if(*head == NULL) {
        *head = Newnode;
    } else {
        Newnode->next = *head;
        (*head)->prev = Newnode;
        *head = Newnode;
    }
}

//print double linked list
void printAngka(node* head) {
    while (head != NULL) {
        printf("%d ", head->angka);
        head = head->next;
    }
    printf("\n");
}

int main() {
    node* head = NULL;

    //insert node
    InsertDepan(&head, 7);
    InsertDepan(&head, 6);
    InsertDepan(&head, 5);
    InsertDepan(&head, 4);
    InsertDepan(&head, 3);
    InsertDepan(&head, 2);
    InsertDepan(&head, 1);

    //print double linked list
    printAngka(head);

    return 0;
}