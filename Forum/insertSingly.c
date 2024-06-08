#include <stdio.h>
#include <stdlib.h>

struct node
{
    int List;
    struct node* next;
};

struct node* MembuatNode(int List){
    struct node* NodeBaru = (struct node*)malloc(sizeof(struct node));
    NodeBaru->List = List;
    NodeBaru->next = NULL;
    return NodeBaru;
}

void TambahkanNode_Belakang(struct node** headRef, int List) {
    struct node* NodeBaru = MembuatNode(List);

    if (*headRef == NULL) {
        *headRef = NodeBaru;
        return;
    }
    struct node* NodeTerakhir = *headRef;
    while (NodeTerakhir->next != NULL) {
        NodeTerakhir = NodeTerakhir->next;
    }
    NodeTerakhir->next = NodeBaru;
}

void MencetakList(struct node* Node) {
    while (Node != NULL) {
        printf("%d ", Node->List);
        Node = Node->next;
    }
    printf("\n");
}

int main() {
    struct node* head = NULL;
    TambahkanNode_Belakang(&head, 1);
    TambahkanNode_Belakang(&head, 2);
    TambahkanNode_Belakang(&head, 3);
    TambahkanNode_Belakang(&head, 4);
    TambahkanNode_Belakang(&head, 5);
    TambahkanNode_Belakang(&head, 6);

    printf("Linked list: ");
    MencetakList(head);
    return 0;
}