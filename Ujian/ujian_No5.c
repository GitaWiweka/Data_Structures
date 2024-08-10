#include <stdio.h>
#include <limits.h>   // Header file untuk konstanta seperti INT_MAX
#include <stdbool.h>  // Header file untuk tipe data boolean

#define V 5  // Jumlah node yang ada adalah 5

// Menemukan nilai minimum
int MinKey(int key[], bool InMST[]) {
    int nilai_min = INT_MAX;  // Inisialisasi nilai minimum dengan nilai maksimum integer
    int minimum_index;        // Menyimpan indeks dari node dengan key terkecil

    // Loop untuk memeriksa setiap node
    for (int v = 0; v < V; v++) {
        // Jika node belum termasuk dalam MST dan nilai kuncinya lebih kecil dari nilai minimum saat ini
        if (InMST[v] == false && key[v] < nilai_min) {
            nilai_min = key[v];
            minimum_index = v;
        }
    }
    return minimum_index;  // Mengembalikan indeks dengan key terkecil yang tidak termasuk dalam MST
}

// Menampilkan MST yang dihasilkan
void displayMST(int parent[], int graph[V][V]) {
    printf("Jalur \tJarak antar titik\n");
    for (int i = 1; i < V; i++)
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
}

// Fungsi membangun dan mencetak MST menggunakan algoritma Prim
void primMST(int graph[V][V]) {
    int parent[V];  // Menyimpan MST yang dihasilkan
    int key[V];     // Nilai kunci untuk memilih edge minimum
    bool inMST[V];  // Melacak node yang sudah termasuk dalam MST

    // Inisialisasi semua nilai kunci sebagai INT_MAX dan inMST[] sebagai false
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, inMST[i] = false;

    key[0] = 0;         // Nilai kunci dari node pertama adalah 0 sehingga node ini dipilih pertama kali
    parent[0] = -1;     // Node pertama tidak memiliki parent, sehingga diinisialisasi dengan -1

    // Membangun MST
    for (int count = 0; count < V - 1; count++) {
        int u = MinKey(key, inMST);  // Memilih node dengan nilai kunci minimum
        inMST[u] = true;             // Tambahkan node yang dipilih ke dalam MST

        // Perbarui nilai kunci dan parent dari node yang terhubung dengan node yang dipilih
        for (int v = 0; v < V; v++)
            if (graph[u][v] && inMST[v] == false && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }

    // Mencetak MST yang dihasilkan
    displayMST(parent, graph);
}

int main() {
    // Definisikan grafik sebagai matriks bobot (weight matrix)
    int graph[V][V] = {
        {0, 30, 20, 10, 0},   // Data Center
        {30, 0, 0, 5, 25},    // Kantor 1
        {20, 0, 0, 13, 40},   // Kantor 2
        {10, 5, 13, 0, 0},    // Pemukiman 1
        {0, 25, 40, 0, 0}     // Pemukiman 2
    };

    // Panggil fungsi untuk menjalankan algoritma Prim dan cetak MST
    primMST(graph);

    return 0;
}
