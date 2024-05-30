#include <stdio.h>
#include <string.h>

// Deklarasi struct untuk tanggal dan tempat lahir
typedef struct {
    int day;
    int month;
    int year;
    char place[50];
} DateOfBirth;

// Deklarasi struct untuk data pasien
typedef struct {
    char name[50];
    DateOfBirth dob;
    char address[100];
    int patientID;
} Patient;

// Deklarasi array of struct untuk menyimpan data pasien
Patient patients[5];

int main() {
    // Deklarasi dan inisialisasi data pasien
    for (int i = 0; i < 5; i++) {
        strcpy(patients[i].name, "Name");
        patients[i].dob.day = 1;
        patients[i].dob.month = 1;
        patients[i].dob.year = 2000;
        strcpy(patients[i].address, "Address");
        patients[i].patientID = i + 1;
    }

    // Menampilkan data pasien
    for (int i = 0; i < 5; i++) {
        printf("Name: %s\n", patients[i].name);
        printf("Date of Birth: %d-%d-%d, %s\n", patients[i].dob.day, patients[i].dob.month, patients[i].dob.year, patients[i].dob.place);
        printf("Address: %s\n", patients[i].address);
        printf("Patient ID: %d\n", patients[i].patientID);
        printf("\n");
    }

    return 0;
}