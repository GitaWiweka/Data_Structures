#include <stdio.h>
#include <string.h>

typedef struct TanggalLahir {
    char Tanggal[20];
    char Tempat[50];
} TanggalLahir;

typedef struct Pasien{
    char NamaPasien[50];
    char AlamatPasien[150];
    int IdPasien;
    TanggalLahir tanggallahir;
} Pasien;

typedef struct DataPasien {
    Pasien pasien[100];
    int JumlahPasien;
} DataPasien;

int main(){
    DataPasien datapasien;

    //data pasien pertama
    strcpy(datapasien.pasien[0].NamaPasien, "Namjoon");
    strcpy(datapasien.pasien[0].AlamatPasien, "Jl. Melati No. 6");
    datapasien.pasien[0].IdPasien = 1209;
    strcpy(datapasien.pasien[0].tanggallahir.Tanggal, "1994-09-12");
    strcpy(datapasien.pasien[0].tanggallahir.Tempat, "Bali");

    //data pasien kedua
    strcpy(datapasien.pasien[1].NamaPasien, "Taehyung");
    strcpy(datapasien.pasien[1].AlamatPasien, "Jl. Mawar No. 8");
    datapasien.pasien[1].IdPasien = 3012;
    strcpy(datapasien.pasien[1].tanggallahir.Tanggal, "1995-12-30");
    strcpy(datapasien.pasien[1].tanggallahir.Tempat, "Lombok");

    //data pasien ketiga
    strcpy(datapasien.pasien[2].NamaPasien, "Yoongi");
    strcpy(datapasien.pasien[2].AlamatPasien, "Jl. Puring No. 12");
    datapasien.pasien[2].IdPasien = 9933;
    strcpy(datapasien.pasien[2].tanggallahir.Tanggal, "1993-03-09");
    strcpy(datapasien.pasien[2].tanggallahir.Tempat, "Jakarta");

   //display data pasien
   printf("Nama Pasien: %s\n", datapasien.pasien[0].NamaPasien);
   printf("ID Pasien: %d\n", datapasien.pasien[0].IdPasien);
   printf("Alamat Pasien: %s\n", datapasien.pasien[0].AlamatPasien);
   printf("Tanggal dan Tempat Lahir Pasien: %s, %s\n\n\n", datapasien.pasien[0].tanggallahir.Tanggal, datapasien.pasien[0].tanggallahir.Tempat);

    //display data pasien 2
    printf("Nama Pasien: %s\n", datapasien.pasien[1].NamaPasien);
   printf("ID Pasien: %d\n", datapasien.pasien[1].IdPasien);
   printf("Alamat Pasien: %s\n", datapasien.pasien[1].AlamatPasien);
   printf("Tanggal dan Tempat Lahir Pasien: %s, %s\n\n\n", datapasien.pasien[1].tanggallahir.Tanggal, datapasien.pasien[1].tanggallahir.Tempat);

   //display data pasien 3
    printf("Nama Pasien: %s\n", datapasien.pasien[2].NamaPasien);
   printf("ID Pasien: %d\n", datapasien.pasien[2].IdPasien);
   printf("Alamat Pasien: %s\n", datapasien.pasien[2].AlamatPasien);
   printf("Tanggal dan Tempat Lahir Pasien: %s, %s\n", datapasien.pasien[2].tanggallahir.Tanggal, datapasien.pasien[2].tanggallahir.Tempat);

   return 0;
}
