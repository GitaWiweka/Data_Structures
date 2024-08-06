#include <stdio.h> //deklarasi fungsi output/input
#include <stdlib.h> //deklarasi fungsi utilitas umum
#include <string.h> //deklarasi fungsi manipulasi string

#define B 7 //mendefinisikan orde B-tree

//struktur data produk
typedef struct Produk{
    int IDProduk;
    char NamaProduk[60];
    float HargaProduk;
    int StokProduk;
    char KategoriProduk[50];
    char DeskripsiProduk[100];
} Produk;

//struktur untuk merepresentasikan node pada B-tree
typedef struct BTreeNode {
    int x; //kunci yang ada di node
    Produk keys[B - 1]; //array key yang tersimpan dalam node
    struct BTreeNode *children[B];
    int leaf; //penunjuk node adalah leaf atau bukan
} BTreeNode;

//deklarasi fungsi
BTreeNode *membuatNode(int leaf); //membuat node baru 
void traversal(BTreeNode *root); //menjelajahi B-Tree mulai dari root
void insert(BTreeNode **root, Produk k); //penambahan item baru
BTreeNode *search(BTreeNode *root, int IDProduk); //penelusuran node dengan identifier tertentu
void Delete_Key(BTreeNode *root, int IDProduk); //hapus item dengan identifier
void SplitChild(BTreeNode *parentNode, int index); //memecah children di posisi index
void InsertNode_NonFull(BTreeNode *node, Produk Item); //penambahan children pada node yang belum penuh
void RemoveLeaf(BTreeNode *node, int index); //menghapus item dari leaf
void RemoveNonLeaf(BTreeNode *node, int index); //menghapus item dari non-leaf
void Gabung(BTreeNode *node, int index); //menggabungkan 2 children
void AdjustNode(BTreeNode *node, int index); //children dari node pada posisis tertentu memiliki item minimum
void borrowPrevSiblings(BTreeNode *node, int index); //meminjam item dari children sebelum 
void borrowNextSiblings(BTreeNode *node, int index); //meminjam item dari children selanjutnya

//membuat dan analisis node baru
BTreeNode *membuatNode(int leaf){
    BTreeNode *nodeBaru = (BTreeNode *)malloc(sizeof(BTreeNode));
    nodeBaru->x = 0;
    nodeBaru->leaf = leaf;
    for (int i = 0; i < B; i++)
        nodeBaru->children[i] = NULL;
    return nodeBaru;
}

//fungsi penjelasan secara in-order
void traversal(BTreeNode *root){
    if (root != NULL){
        for (int i = 0; i < root->x; i++){
            printf("ID Produk: %d\nNama Produk: %s\n", root->keys[i].IDProduk, root->keys[i].NamaProduk);
            if (!root->leaf)
                traversal(root->children[i]);
        }
        if (!root->leaf)
            traversal(root->children[root->x]);
    }
}

//fungsi penyisipan key pada node yang tidak penuh
void InsertNode_NonFull(BTreeNode *node, Produk Item){
    int i = node->x - 1;
    //jika node leaf, insert key langsung ke node leaf
    if (node->leaf){
        while (i >= 0 && Item.IDProduk < node->keys[i].IDProduk){
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = Item;
        node->x++;
    } else {
        //menemukan children yang akan diinsert
        while (i >= 0 && Item.IDProduk < node->keys[i].IDProduk)
            i--;
        i++;
        if (node->children[i]->x == B - 1){
            SplitChild(node, i);
            if (Item.IDProduk > node->keys[i].IDProduk)
                i++;
        }
        InsertNode_NonFull(node->children[i], Item);
    }
}

void SplitChild(BTreeNode *parentNode, int index){
    BTreeNode *y = parentNode->children[index]; //mengambil children yang penuh yang akan dibagi
    BTreeNode *z = membuatNode(y->leaf); //node baru yang menyimpan setengah key dari anak yang dibagi
    z->x = B / 2 - 1; //inisialisasi jumlah key

    //menyalin setengah key
    for (int j = 0; j < B / 2 - 1; j++)
        z->keys[j] = y->keys[j + B / 2];

    //jika, y bukan leaf, copy setengah children dari y ke z
    if (!y->leaf){
        for (int j = 0; j < B / 2; j++)
            z->children[j] = y->children[j + B / 2];
    }
    //memperbarui jumlah key
    y->x = B / 2 - 1;

    //insert z sebagai new children dari parent
    for (int j = parentNode->x; j >= index + 1; j--)
        parentNode->children[j + 1] = parentNode->children[j];
    
    parentNode->children[index + 1] = z; //menempatkan node z pada posisi yang sesuai

    for (int j = parentNode->x - 1; j >= index; j--)
        parentNode->keys[j + 1] = parentNode->keys[j];

    parentNode->keys[index] = y->keys[B / 2 - 1];
    parentNode->x++; //tambah jumlah kunci di parent
}

//fungsi untuk insert key dalam B-tree
void insert(BTreeNode **root, Produk k){
    BTreeNode *r = *root; //mengambil pointer ke root dari B-tree

    //jika root penuh, bagi root
    if (r->x == B - 1){
        BTreeNode *s = membuatNode(0);
        *root = s; //node baru sebagai root baru
        s->children[0] = r;
        //bagi root yang penuh
        SplitChild(s, 0);
        InsertNode_NonFull(s, k); //insert key baru ke dalam root
    } else {
        //jika root tidak penuh, insert key ke dalam root
        InsertNode_NonFull(r, k);
    }
}

//fungsi untuk mencari dengan identifier
BTreeNode *search(BTreeNode *root, int IDProduk){
    //key tidak ditemukan jika root NULL
    if (root == NULL) return NULL;

    int i = 0;

    //menemukan posisi key dengan ID produk
    while (i < root->x && IDProduk > root->keys[i].IDProduk)
        i++;
    
    //return node jika ID produk ditemukan
    if (i < root->x && root->keys[i].IDProduk == IDProduk)
        return root;
    
    //jika node adalah leaf dan ID produk not found, maka key tidak
    if (root->leaf)
        return NULL;
    
    return search(root->children[i], IDProduk);
}

//fungsi menghapus key dengan Identifier
void Delete_Key(BTreeNode *root, int IDProduk){
    if (root == NULL) //jika root NULL, key tidak terdapat dalam tree
        return; 

    int index = 0;

    while (index < root->x && root->keys[index].IDProduk < IDProduk)
        index++;

    //jika key ditemukan
    if (index < root->x && root->keys[index].IDProduk == IDProduk){
        if (root->leaf)
            RemoveLeaf(root, index); //hapus key dari leaf
        else
            RemoveNonLeaf(root, index); //hapus key dari non leaf
    } else {
        if (root->leaf)
            return;

        //menentukan apakah indeks berada pada jangkauan node
        int LastKey = ((index == root->x) ? 1 : 0);

        if (root->children[index]->x < B / 2) //memastikan children memiliki cukup key
            AdjustNode(root, index);
        
        if (LastKey && index > root->x)
            Delete_Key(root->children[index - 1], IDProduk);
        else
            Delete_Key(root->children[index], IDProduk);
    }
}

//fungsi remove key dari node leaf
void RemoveLeaf(BTreeNode *node, int index){
    for (int i = index + 1; i < node->x; i++)
        node->keys[i - 1] = node->keys[i];
    
    //pengurangan jumlah node karena proses penghapusan
    node->x--;
}

//fungsi menghapus key dari node non leaf
void RemoveNonLeaf(BTreeNode *node, int index) {
    int k = node->keys[index].IDProduk; //menyimpan ID key yang akan dihapus

    if (node->children[index]->x >= B / 2) {
        Produk pred = node->children[index]->keys[node->children[index]->x - 1]; //pendahulu dari key subtree kiri
        node->keys[index] = pred;
        Delete_Key(node->children[index], pred.IDProduk);
    } else if (node->children[index + 1]->x >= B / 2) {
        Produk successor = node->children[index + 1]->keys[0]; //successor dari key subtree kanan
        node->keys[index] = successor;
        Delete_Key(node->children[index + 1], successor.IDProduk);
    } else {
        Gabung(node, index);
        Delete_Key(node->children[index], k);
    }
}

//fungsi untuk menggabungkan children
void Gabung(BTreeNode *node, int index) {
    BTreeNode *child = node->children[index];
    BTreeNode *sibling = node->children[index + 1];

    child->keys[B / 2 - 1] = node->keys[index];

    for (int i = 0; i < sibling->x; i++)
        child->keys[i + B / 2] = sibling->keys[i];

    if (!child->leaf) {
        for (int i = 0; i <= sibling->x; i++)
            child->children[i + B / 2] = sibling->children[i];
    }

    for (int i = index + 1; i < node->x; i++)
        node->children[i] = node->children[i + 1];

    for (int i = index; i < node->x - 1; i++)
        node->keys[i] = node->keys[i + 1];

    child->x += sibling->x + 1;
    node->x--;
    free(sibling);
}

//fungsi untuk menyesuaikan anak dari node jika tidak memiliki cukup key
void AdjustNode(BTreeNode *node, int index) {
    if (index && node->children[index - 1]->x >= B / 2)
        borrowPrevSiblings(node, index);
    else if (index != node->x && node->children[index + 1]->x >= B / 2)
        borrowNextSiblings(node, index);
    else {
        if (index != node->x)
            Gabung(node, index);
        else
            Gabung(node, index - 1);
    }
}

//fungsi untuk meminjam dari saudara sebelumnya
void borrowPrevSiblings(BTreeNode *node, int index) {
    BTreeNode *child = node->children[index];
    BTreeNode *sibling = node->children[index - 1];

    for (int i = child->x - 1; i >= 0; i--)
        child->keys[i + 1] = child->keys[i];

    if (!child->leaf) {
        for (int i = child->x; i >= 0; i--)
            child->children[i + 1] = child->children[i];
    }

    child->keys[0] = node->keys[index - 1];

    if (!child->leaf)
        child->children[0] = sibling->children[sibling->x];

    node->keys[index - 1] = sibling->keys[sibling->x - 1];
    child->x++;
    sibling->x--;
}

//fungsi untuk meminjam dari saudara selanjutnya
void borrowNextSiblings(BTreeNode *node, int index) {
    BTreeNode *child = node->children[index];
    BTreeNode *sibling = node->children[index + 1];

    child->keys[child->x] = node->keys[index];
    if (!child->leaf)
        child->children[child->x + 1] = sibling->children[0];

    node->keys[index] = sibling->keys[0];

    for (int i = 1; i < sibling->x; i++)
        sibling->keys[i - 1] = sibling->keys[i];

    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->x; i++)
            sibling->children[i - 1] = sibling->children[i];
    }

    child->x++;
    sibling->x--;
}

//fungsi utama
int main() {
    BTreeNode *root = membuatNode(1);

    Produk p1 = {1245, "Gantungan Baju", 90.000, 50, "Kategori: Peralatan Baju", "Deskripsi: menggantung pakaian"};
    Produk p2 = {3245, "Sapu", 10.000, 20, "Kategori: Peralatan Rumah Tangga", "Deskripsi: menyapu rumah"};
    Produk p3 = {4567, "Lemari", 999.000, 3, "Kategori: Peralatan Baju", "Deskripsi: lemari pakaian"};
    Produk p4 = {4568, "Rice Cooker", 85.000, 13, "Kategori: Peralatan Dapur", "Deskripsi: memasak nasi"};
    Produk p5 = {5678, "Gelas", 250.000, 100, "Kategori: Peralatan Dapur", "Deskripsi: gelas kaca aesthetic"};

    insert(&root, p1);
    insert(&root, p2);
    insert(&root, p3);
    insert(&root, p4);
    insert(&root, p5);

    printf("Traversal B-Tree: \n");
    traversal(root);

    printf("\nMencari produk dengan ID Produk 1245:\n");
    BTreeNode *HasilSearch = search(root, 1245);
    if (HasilSearch) {
        printf("Produk ditemukan:\nID Produk: %d\nNama Produk: %s\n", HasilSearch->keys[1].IDProduk, HasilSearch->keys[1].NamaProduk);
    } else {
        printf("Produk tidak ditemukan\n");
    }

    printf("\nMenghapus produk dengan ID Produk 5678\n");
    Delete_Key(root, 5678);

    printf("B-Tree setelah penghapusan:\n");
    traversal(root);

    return 0;
}
