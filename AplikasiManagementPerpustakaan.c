// Note : dequeue function setelah di debug ada segmentation fault, perlu diperbaiki.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct request {
       char peminjam[20];
       char kontak[20];
       char judul[20];
       char status[20];
       struct request *next;
} request;

typedef struct idPinjam {
       int id;
       char judul[20];
       char status[20];
       char kontak[20];
       char peminjam[20];
       char tanggal[20];
       char deadline[20];
       struct idPinjam *left, *right;
} idPinjam;

/*typedef struct bookData {
	char judul[20];
	int id;
	char penerbit[20];
	char tanggal[20];
	char author[20];
	int count;
} bookData;


void readFile(struct bookData *size)
{
  FILE *data = fopen("dataBuku.txt", "r");

  while (!(feof(data))
  {
    struct bookData semuaBuku;

    fscanf(data, "%[^#]#%i#%[^#]#%[^#]#%[^\n\r]\n", semuaBuku.judul, &semuaBuku.id,
           semuaBuku.penerbit, semuaBuku.tanggal, semuaBuku.author);
           
    size->count++;
  }
  
  fclose(data);
}

void sorting()
{
	int sortBy;
	
	printf("=============================\n"
            "           Sort By\n"
           "=============================\n"
            "1. Judul\n"
            "2. ID\n"
            "3. Publisher\n"
            "4. Tanggal Terbit\n"
            "5. Author\n");
    printf("Choose : "); scanf("%d", sortBy);
    
    if(sortBy == 1)
    {
    	
	}
}*/

idPinjam *newNode(int id, request *item) {
       idPinjam *temp = ( idPinjam *)malloc(sizeof( idPinjam));
       temp->id = id;
       strcpy(temp->judul, item->judul);
       strcpy(temp->status, "sedang dipinjam");
       strcpy(temp->kontak, item->kontak);
       strcpy(temp->peminjam, item->peminjam);
       time_t t = time(NULL);
       struct tm tm = *localtime(&t);
       strftime(temp->tanggal, sizeof(temp->tanggal), "%d-%m-%Y", &tm);
       printf("Tanggal peminjaman: %s\n", temp->tanggal);
       tm.tm_mday += 14;
       strftime(temp->deadline, sizeof(temp->deadline), "%d-%m-%Y", &tm);
       printf("Deadline: %s\n", temp->deadline);
       
       temp->left = temp->right = NULL;
       return temp;
}

idPinjam *insert( idPinjam *node, int id, request* curr) {
    if (node == NULL) return newNode(id, curr);
    if (id < node->id)
        node->left = insert(node->left, id, curr);
    else if (id > node->id)
        node->right = insert(node->right,  id, curr);
    return node;
}
void pinjam(request **head , request **tail){
       request *newQueue = (request *)malloc(sizeof(request));
       printf("Masukkan nama peminjam: ");
       scanf("%s", newQueue->peminjam);
       printf("Masukkan kontak peminjam: ");
       scanf("%s", newQueue->kontak);
       printf("Masukkan judul buku: ");
       scanf("%s", newQueue->judul);
       strcpy(newQueue->status, "pending");
       newQueue->next = NULL;
       if (*head == NULL) {
              *head = newQueue;
              *tail = newQueue;
       } else {
              (*tail)->next = newQueue;
              *tail = newQueue;
       }
}

void dequeue(request **head){
       request *temp = *head;
       *head = (*head)->next;
       free(temp);
}

void approve(request **head, idPinjam **root, int idCount){
       
       while (*head != NULL) {
              printf("%s\n", (*head)->peminjam);
              printf("%s\n", (*head)->kontak);
              printf("%s\n", (*head)->judul);
              int choice;
              
              while (choice != 1 && choice != 2) {
                     printf("Status:\n"
                     "1. Approve\n"
                     "2. Reject\n");
              
                     scanf("%d", &choice);
                     switch (choice) {
                            case 1:
                                   idCount++;
                                   insert(*root, idCount, *head);
                                   printf("Request Approved\n");
                                   dequeue(*head);
                                   break;
                            case 2:
                                   printf("Request Rejected\n");
                                   dequeue(*head);
                                   break;
                            default:
                                   printf("Input salah\n");
                                   break;
                     }
              }

                                   
       }
}



// void print(request *req) {
//        printf("\nNama peminjam: %s", req->peminjam);
//        printf("\nKontak peminjam: %s", req->kontak);
//        printf("\nJudul buku: %s", req->judul);
//        printf("\nTanggal pinjam: %s", req->tanggal);
//        printf("\nDeadline pinjam: %s", req->deadline);
//        printf("\nStatus pinjam: %s", req->status);
//        printf("\nID pinjam: %s", req->id);
// }
int menu () {
       int menu;
       printf("=============================\n"
              " Library Inventory Manager\n"
              "=============================\n"
              "1. Sorting Buku\n"
              "2. Search buku\n"
              "3. Request peminjaman buku\n"
              "4. Approve peminjaman buku\n"
              "5. Kembalikan buku\n"
              "6. Exit\n");
       printf("Pilih menu: ");
       scanf("%d", &menu);
       return menu;
}




int main(int argc, char *argv[])
{
       idPinjam *root = NULL;
       int idCount = 0;
       request *head = NULL, *tail = NULL;
       
       
       while (1) {
              switch (menu()) {
              case 1:
                     break;
              case 2:
                     break;
              case 3:       
                     pinjam(&head, &tail);
                     break;
              case 4:
                     approve(&head, &root, idCount);
                     break;
              case 5:
                     break;
              case 6:
                     return 0;
              default:
                     printf("Pilihan tidak tersedia\n");
              }
       }
       // printf("=============================\n"
       //      "           Sort By\n"
       //     "=============================\n"
       //     "1. Judul\n"
       //     "2. ID\n"
       //     "3. Publisher\n"
       //     "4. Tanggal Terbit\n"
       //     "5. Author\n");

       // printf("=============================\n"
       //      "           Search\n"
       //     "=============================\n"
       //     " Input idword: Algoritma\n\n"
       //     "=============================\n"
       //     "Nama : Algoritma dan data struktur\n"
       //     "ID   : B001\n"
       //     "Penerbit : Gajah Mada\n"
       //     "Tanggal terbit : 01/01/2020\n"
       //     "Author : Raja\n"
       //     "=============================\n"
       //     "Nama : Algoritma bagi pemula\n"
       //     "ID   : B002\n"
       //     "Penerbit : Gajah Mada\n"
       //     "Tanggal terbit : 01/01/2020\n"
       //     "Author : Dana\n");

       // printf("=============================\n"
       //         "    Peminjaman buku\n"
       //     "=============================\n"
       //     " Nama lengkap buku: Algoritma dan data struktur\n\n"
       //     "=============================\n"
       //     "Nama : Algoritma dan data struktur\n"
       //     "ID   : B001\n"
       //     "Penerbit : Gajah Mada\n"
       //     "Tanggal terbit : 01/01/2020\n"
       //     "Author : Raja\n"
       //        "=============================\n"
       //        "Request peminjaman akan dibuat\n");
    return 0;
}
