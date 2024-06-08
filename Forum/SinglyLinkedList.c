#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct InfoPasien
{
    char NamaPasien[100];
    int umur;
    char JenisKelamin[15];
    char AlamatPasien[100];
    char PenyakitPasien[50];
};

struct node{
    struct InfoPasien pasien;
    struct node* next;
};

struct node* MembuatNode(char NamaPasien[], int umur, char JenisKelamin[], char AlamatPasien[], char PenyakitPasien[]){
    struct node* nodebaru = (struct node*)malloc(sizeof(struct node));
    strcpy(nodebaru->pasien.NamaPasien, NamaPasien);
    nodebaru->pasien.umur = umur;
    strcpy(nodebaru->pasien.JenisKelamin, JenisKelamin);
    strcpy(nodebaru->pasien.AlamatPasien, AlamatPasien);
    strcpy(nodebaru->pasien.PenyakitPasien, PenyakitPasien);
    nodebaru->next = NULL;
    return nodebaru;
}

void TambahNode(struct node** head, char NamaPasien[], int umur, char JenisKelamin[], char AlamatPasien[], char PenyakitPasien[]){
    struct node* nodebaru = MembuatNode(NamaPasien, umur, JenisKelamin, AlamatPasien, PenyakitPasien);
    if(*head == NULL){
        *head = nodebaru;
        return;
    }
    struct node* temp = *head;
    while (temp->next != NULL){
        temp = temp->next;
    }
    temp->next = nodebaru;
}

void DaftarPasien(struct node* head){
    struct node* temp = head;
    while (temp != NULL){
        printf("Nama Pasien: %s, Umur Pasien: %d, Jenis Kelamin: %s, Alamat Pasien: %s, Penyakit yang dialami: %s\n\n",
                temp->pasien.NamaPasien, temp->pasien.umur, temp->pasien.JenisKelamin, temp->pasien.AlamatPasien, temp->pasien.PenyakitPasien);
        temp = temp->next;
    }
}

int main(){
    struct node* head = NULL;

    TambahNode(&head, "Kim Namjoon", 31, "Laki-laki", "Jl. Melati", "Batuk dan pilek");
    TambahNode(&head, "Kim Taehyung", 29, "Laki-laki", "Jl. Kebangsaan", "Demam");
    TambahNode(&head, "Kim seokjin", 32, "Laki-laki", "Jl. Cempaka", "Pilek");
    TambahNode(&head, "Park Jimin", 29, "Laki-laki", "Jl. Kamboja", "Keluhan pada bahu");

    DaftarPasien(head);

    return 0;
}
