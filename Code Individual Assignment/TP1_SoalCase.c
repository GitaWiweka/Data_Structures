#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListItem {
    int IDKaryawan;
    char NamaKaryawan[31];
    char TempatLahir[31];
    char TanggalLahir[11];
    char Jabatan[51];
    struct ListItem* next;
} ListItem;

ListItem* CreateList(int IDKaryawan, char NamaKaryawan[], char TempatLahir[], char TanggalLahir[], char Jabatan[]){
    ListItem* NewList = (ListItem*)malloc(sizeof(ListItem));
    NewList->IDKaryawan = IDKaryawan;
    strcpy(NewList->NamaKaryawan, NamaKaryawan);
    strcpy(NewList->TempatLahir, TempatLahir);
    strcpy(NewList->TanggalLahir, TanggalLahir);
    strcpy(NewList->Jabatan, Jabatan);
    NewList->next = NULL;
    return NewList;
}

void PushList(ListItem** head, int IDKaryawan, char NamaKaryawan[], char TempatLahir[], char TanggalLahir[], char Jabatan[]){
    ListItem* NewList = CreateList(IDKaryawan, NamaKaryawan, TempatLahir, TanggalLahir, Jabatan);
    if(*head == NULL || (*head)->IDKaryawan > IDKaryawan){
        NewList->next = *head;
        *head = NewList;
    } else {
        ListItem* traversal = *head;
        while (traversal->next != NULL && traversal->next->IDKaryawan <= IDKaryawan){
            traversal = traversal->next;
        }
        NewList->next = traversal->next;
        traversal->next = NewList; 
    }
}

void PrintList(ListItem* head){
    ListItem* traversal = head;
    while (traversal != NULL){
        printf("\nID Karyawan: %d\n", traversal->IDKaryawan);
        printf("Nama Karyawan: %s\n", traversal->NamaKaryawan);
        printf("Tempat Lahir Karyawan: %s\n", traversal->TempatLahir);
        printf("Tanggal Lahir Karyawan: %s\n", traversal->TanggalLahir);
        printf("Jabatan Karyawan: %s\n", traversal->Jabatan);
        printf("\n");
        traversal = traversal->next;
    }
}

void DeleteList(ListItem** head, int IDKaryawan){
    if (*head == NULL) return;
    if ((*head)->IDKaryawan == IDKaryawan){
        ListItem* temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }
    ListItem* traversal = *head;
    while (traversal->next != NULL && traversal->next->IDKaryawan != IDKaryawan){
        traversal = traversal->next;
    }
    if (traversal->next != NULL){
        ListItem* temp = traversal->next;
        traversal->next = traversal->next->next;
        free(temp);
    }
}

void DeleteAll(ListItem** head){
    ListItem* traversal = *head;
    ListItem* next;
    while (traversal != NULL){
        next = traversal->next;
        free(traversal);
        traversal = next;
    }
    *head = NULL;
}

int main(){
    ListItem* head = NULL;
    int menu;
    int IDKaryawan;
    char NamaKaryawan[31];
    char TempatLahir[31];
    char TanggalLahir[11];
    char Jabatan[51];

    while (1) {
        printf("\n\n1. Push Data Karyawan\n");
        printf("2. Menampilkan semua daftar karyawan\n");
        printf("3. Hapus data karyawan berdasarkan ID karyawan\n");
        printf("4. Hapus semua data karyawan\n");
        printf("5. Keluar dari program\n");
        printf("Pilihan menu: ");
        scanf("%d", &menu);

        switch (menu){
            case 1:
                printf("\nMasukkan ID Karyawan (maksimal 5 angka): ");
                scanf("%d", &IDKaryawan);
                if(IDKaryawan < 0 || IDKaryawan > 99999){
                    printf("Input tidak valid. Id karyawan maksimal 5 angka.\n");
                    continue;
                }
                printf("Nama lengkap karyawan: ");
                getchar();
                fgets(NamaKaryawan, sizeof(NamaKaryawan), stdin);
                NamaKaryawan[strcspn(NamaKaryawan, "\n")] = 0;
                printf("Tempat lahir karyawan (maksimal 30 karakter): ");
                fgets(TempatLahir, sizeof(TempatLahir), stdin);
                TempatLahir[strcspn(TempatLahir, "\n")] = 0;
                printf("Masukkan tanggal lahir karyawan (YYYY-MM-DD): ");
                scanf("%10s", TanggalLahir);
                getchar();
                printf("Masukkan jabatan karyawan (maksimal 50 karakter): ");
                fgets(Jabatan, sizeof(Jabatan), stdin);
                Jabatan[strcspn(Jabatan, "\n")] = 0;

                if (strlen(NamaKaryawan) > 30 || strlen(TempatLahir) > 30 || strlen(TanggalLahir) != 10 || strlen(Jabatan) > 50){
                    printf("Input tidak valid. Silahkan coba lagi.\n");
                    continue;
                }

                PushList(&head, IDKaryawan, NamaKaryawan, TempatLahir, TanggalLahir, Jabatan);
                if (head != NULL && head->next != NULL){
                    ListItem* traversal = head;
                    while (traversal->next != NULL) {
                        if (traversal->next->IDKaryawan < traversal->IDKaryawan){
                            ListItem* temp = traversal->next;
                            traversal->next = traversal->next->next;
                            free(temp);
                            break;
                        }
                        traversal = traversal->next;
                    }
                }
                printf("\n\n================= DATA DITAMBAHKAN =================\n");
                break;

            case 2:
                PrintList(head);
                break;

            case 3:
            printf("\nSilahkan masukkan ID karyawan untuk dihapus: ");
            scanf("%d", &IDKaryawan);
            DeleteList(&head, IDKaryawan);
            printf("\n\n================= DATA DIHAPUS =================\n");
            break;

            case 4:
            DeleteAll(&head);
            printf("\n\n================= DATA DIHAPUS =================\n");
            break;

            case 5:
            DeleteAll(&head);
            printf("\n\n================================ TERIMAKASIH ================================");
            return 0;

            default:
                printf("Tidak Valid. Silahkan masukkan pilihan 1-5.\n");
        }
    }
}
