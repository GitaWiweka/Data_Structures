#include <stdio.h>
#include <stdlib.h>

struct node
{
    int List;
    struct node* next;
};

void HapusNode_Depan(struct node** head_ref){
    if(*head_ref == NULL){
        printf("Linked list sudah kosong\n");
        return;
    }

    struct node* temp = *head_ref;
    *head_ref = (*head_ref)->next;
    free(temp);
    
    printf("Node dihapus dari depan\n");
}

void TambahkanNode_Depan(struct node** head_ref, int ListBaru){
    
    struct node* NodeBaru = (struct node*) malloc(sizeof(struct node));

    NodeBaru->List = ListBaru;
    NodeBaru->next = *head_ref;
    *head_ref = NodeBaru;
}

void TampilkanList(struct node* node){
    while (node != NULL){
        printf("%d -> ", node->List);
        node = node->next;
    }
    printf("NULL\n");
}

int main(){
    struct node* head = NULL;

    TambahkanNode_Depan(&head, 6);
    TambahkanNode_Depan(&head, 5);
    TambahkanNode_Depan(&head, 4);
    TambahkanNode_Depan(&head, 3);
    TambahkanNode_Depan(&head, 2);
    TambahkanNode_Depan(&head, 1);

    printf("Linked list sebelum penghapusan node depan: ");
    TampilkanList(head);

    HapusNode_Depan(&head);

    printf("Linked list setelah penghapusan: ");
    TampilkanList(head);

    return 0;
}
