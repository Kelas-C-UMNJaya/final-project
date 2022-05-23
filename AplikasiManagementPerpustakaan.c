#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

typedef struct request {
       char peminjam[50];
       char kontak[20];
       char judul[50];
       char status[20];
       struct request *next;
} request;

typedef struct idPinjam {
       int id;
       char judul[50];
       char status[20];
       char kontak[20];
       char peminjam[50];
       char tanggal[20];
       char deadline[20];
       int height;
       struct idPinjam *left, *right;
} idPinjam;


typedef struct bookData {
	char judul[50];
	char id[50];
	char penerbit[50];
	char tanggal[50];
	char author[50];
	char status[50];
} bookData;

typedef struct allBook {
	struct bookData buku;
	struct allBook *next;
} allBook;

struct allBook *headBook = NULL;
struct allBook *curr = NULL;
//struct allBook input[];

int count = 0;
int idCount = 0;
int max(int a, int b);
idPinjam *insertFile( idPinjam *node, idPinjam newPeminjam, int id);
idPinjam *newFileNode(int id, idPinjam newPeminjam);
idPinjam* leftRotate(idPinjam *x);
idPinjam* rightRotate(idPinjam *y);
int getBalance(idPinjam *N);
int height(idPinjam *N);

void readFileDataBuku(struct allBook **headBook)
{
	struct bookData semuaBuku;
	FILE *data = fopen("dataBuku.txt", "r");

	while (!(feof(data)))
	{
		struct allBook *link = (struct allBook*)malloc(sizeof(struct allBook));

		fscanf(data, "%[^#]# %[^#]# %[^#]# %[^#]# %[^#]# %[^\n\r]\n", semuaBuku.id, semuaBuku.judul,
           semuaBuku.penerbit, semuaBuku.tanggal, semuaBuku.author, semuaBuku.status);
           
        if(*headBook == NULL)
		{
			link->buku = semuaBuku;
			link->next = *headBook;
			*headBook = link;
		}
		else
		{
			struct allBook *tempNode = *headBook;

			while(tempNode->next != NULL)
			{
				tempNode = tempNode->next;
			}
			link->buku = semuaBuku;
			link->next = *headBook;
			*headBook = link;
		}
	}

	fclose(data);
}

void swap(struct allBook *a, struct allBook *b)
{
	struct bookData temp = a->buku;
	a->buku = b->buku;
	b->buku = temp;
}

void sortJudul()
{
	int swapped;
	struct allBook *ptr1 = NULL;
	struct allBook *lptr = NULL;
	
	do
    {
        swapped = 0;
        ptr1 = headBook;
  
        while (ptr1->next != lptr)
        {
            if(strcmp(ptr1->buku.judul, ptr1->next->buku.judul) > 0)
            { 
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}

void sortID(struct allBook *headBook)
{
	int swapped;
	struct allBook *ptr1 = NULL;
	struct allBook *lptr = NULL;
	
	do
    {
        swapped = 0;
        ptr1 = headBook;
  
        while (ptr1->next != lptr)
        {
            if(strcmp(ptr1->buku.id, ptr1->next->buku.id) > 0)
            { 
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}

void sortPublisher(struct allBook *headBook)
{
	int swapped;
	struct allBook *ptr1;
	struct allBook *lptr = NULL;
	
	do
    {
        swapped = 0;
        ptr1 = headBook;
  
        while (ptr1->next != lptr)
        {
            if(strcmp(ptr1->buku.penerbit, ptr1->next->buku.penerbit) > 0)
            { 
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}

void sortTerbit(struct allBook *headBook)
{
	int swapped;
	struct allBook *ptr1;
	struct allBook *lptr = NULL;
	
	do
    {
        swapped = 0;
        ptr1 = headBook;
  
        while (ptr1->next != lptr)
        {
            if(strcmp(ptr1->buku.tanggal, ptr1->next->buku.tanggal) > 0)
            { 
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}

void sortAuthor(struct allBook *headBook)
{
	int swapped;
	struct allBook *ptr1;
	struct allBook *lptr = NULL;
	
	do
    {
        swapped = 0;
        ptr1 = headBook;
  
        while (ptr1->next != lptr)
        {
            if(strcmp(ptr1->buku.author, ptr1->next->buku.author) > 0)
            { 
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}

void printSort()
{
	curr = headBook;
	printf("\n");
	printf("======================================================================================================================\n");
	printf("|                                                     DATA BUKU                                                      |\n");
	printf("======================================================================================================================\n");
	
	while(curr != NULL)
	{
		struct bookData hasil = curr->buku;
		
		printf("| %s | %-40s | %-10s | %-10s | %-20s | %-15s |\n", hasil.id, hasil.judul,
           hasil.penerbit, hasil.tanggal, hasil.author, hasil.status);
        
        curr = curr->next;
	}
	
	printf("----------------------------------------------------------------------------------------------------------------------\n");
	printf("\n");
	getch();
}

void sorting()
{
	system("cls");
	int sortBy;

	printf("=============================\n"
            "           Sort By\n"
            "=============================\n"
             "1. Judul\n"
             "2. ID\n"
             "3. Publisher\n"
             "4. Tanggal Terbit\n"
             "5. Author\n");
	printf("Choose : "); scanf("%d", &sortBy);

	if(sortBy == 1)
	{
		sortJudul();
		printSort();
	}
	else if (sortBy == 2)
	{
		sortID(headBook);
		printSort();
	}
	else if (sortBy == 3)
	{
		sortPublisher(headBook);
		printSort();
	}
	else if (sortBy == 4)
	{
		sortTerbit(headBook);
		printSort();
	}
	else if (sortBy == 5)
	{
		sortAuthor(headBook);
		printSort();
	}
	else
	{
		printf("\nINVALID!");
	}
}


void readFileDataPeminjam(struct idPinjam **dbPeminjam)
{
	FILE *data = fopen("dataPeminjam.txt", "r");

	while (!(feof(data)))
	{
              idPinjam newPeminjam;
   
              fscanf(data, "%[^#]#%[^#]#%[^#]#%[^#]#%[^#]#%[^#]#%d[^\n\r]\n",   newPeminjam.judul,
              newPeminjam.status, newPeminjam.kontak, newPeminjam.peminjam, newPeminjam.tanggal, newPeminjam.deadline, &newPeminjam.id);
	
              (*dbPeminjam) = insertFile((*dbPeminjam), newPeminjam, newPeminjam.id);
             
              idCount++;
	}
	fclose(data);
}

idPinjam *insertFile( idPinjam *node, idPinjam newPeminjam, int id) {
       
       if (node == NULL) return newFileNode(id, newPeminjam);
       if (id < node->id)
              node->left = insertFile(node->left, newPeminjam, id);
       else if (id > node->id)
              node->right = insertFile(node->right, newPeminjam, id);
       else
              return node;

       node->height = height(node);

       int balance = getBalance(node);

       // Left Left Case
       if (balance > 1 && id < node->left->id)
           return rightRotate(node);

       // Right Right Case
       if (balance < -1 && id > node->right->id)
           return leftRotate(node);

       // Left Right Case
       if (balance > 1 && id > node->left->id)
       {
           node->left =  leftRotate(node->left);
           return rightRotate(node);
       }

       // Right Left Case
       if (balance < -1 && id < node->right->id)
       {
           node->right = rightRotate(node->right);
           return leftRotate(node);
       }


    return node;
}

idPinjam *newFileNode(int id, idPinjam newPeminjam) {
       idPinjam *temp = ( idPinjam *)malloc(sizeof( idPinjam));
       temp->id = id;
       strcpy(temp->judul, newPeminjam.judul);
       strcpy(temp->status, newPeminjam.status);
       strcpy(temp->kontak, newPeminjam.kontak);
       strcpy(temp->peminjam, newPeminjam.peminjam);
       strcpy(temp->tanggal, newPeminjam.tanggal);
       strcpy(temp->deadline, newPeminjam.deadline);
       temp->height = 0;
       temp->left = temp->right = NULL;
       return temp;
       
}

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
       temp->height = 0;

       temp->left = temp->right = NULL;
       return temp;
}

int height(idPinjam *N)
{
    if (N == NULL)
        return 0;
    return 1+max(height(N->left), height(N->right));
}

int max(int a, int b)
{
    return (a > b)? a : b;
}

int getBalance(idPinjam *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

idPinjam* rightRotate(idPinjam *y)
{
    idPinjam *x = y->left;
    idPinjam *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = height(y);
    x->height = height(x);

    return x;
}

idPinjam* leftRotate(idPinjam *x)
{
    idPinjam *y = x->right;
    idPinjam *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = height(x);
    y->height = height(y);

    return y;
}

idPinjam *insert( idPinjam *node, int id, request* curr) {
       if (node == NULL) return newNode(id, curr);
       if (id < node->id)
              node->left = insert(node->left, id, curr);
       else if (id > node->id)
              node->right = insert(node->right,  id, curr);
       else
              return node;

       node->height = height(node);

       int balance = getBalance(node);

       // Left Left Case
       if (balance > 1 && id < node->left->id)
           return rightRotate(node);

       // Right Right Case
       if (balance < -1 && id > node->right->id)
           return leftRotate(node);

       // Left Right Case
       if (balance > 1 && id > node->left->id)
       {
           node->left =  leftRotate(node->left);
           return rightRotate(node);
       }

       // Right Left Case
       if (balance < -1 && id < node->right->id)
       {
           node->right = rightRotate(node->right);
           return leftRotate(node);
       }


    return node;
}

void ubahStatusBukudDikembalikan (idPinjam *node) {
    curr = headBook;
    while (curr != NULL) {
        if (strcmp(curr->buku.judul, node->judul) == 0) {
            strcpy (curr->buku.status, "Belum Dipinjam");
            return;
        }
        curr = curr->next;
    }
}



idPinjam *delete( idPinjam *node, int id) {
    if (node == NULL) return NULL;
       if (id < node->id)
              node->left = delete(node->left, id);
       else if (id > node->id)
              node->right = delete(node->right, id);
       else {
              if (node->left == NULL && node->right == NULL) {
              ubahStatusBukudDikembalikan(node);
              free(node);
              node = NULL;
              } else if (node->left == NULL) {
              ubahStatusBukudDikembalikan(node);
              idPinjam *temp = node;
              node = node->right;
              free(temp);
              } else if (node->right == NULL) {
              ubahStatusBukudDikembalikan(node);
              idPinjam *temp = node;
              node = node->left;
              free(temp);
              } else {
              ubahStatusBukudDikembalikan(node);
              idPinjam *temp = node->right;
              while (temp->left != NULL)
                     temp = temp->left;
              node->id = temp->id;
              node->right = delete(node->right, temp->id);
              }
       }
       return node;
}



void pinjam(request **head , request **tail){
       request *newQueue = (request *)malloc(sizeof(request));
       char confirm;
       int found = 0;
       system("cls");
       printf("------------------------------------------\n");
       printf("               Make Request               \n");
       printf("------------------------------------------\n");
       fflush(stdin);
       printf("Masukkan nama peminjam: ");
       scanf("%[^\n]", newQueue->peminjam);
       fflush(stdin);
       printf("Masukkan kontak peminjam: ");
       scanf("%[^\n]", newQueue->kontak);
       fflush(stdin);

       do{

           found = 0;

            printf("Masukkan judul buku: ");
            scanf("%[^\n]", newQueue->judul);
            fflush(stdin);
            allBook *curr = headBook;

            while (curr != NULL) {
                if (strcmp(curr->buku.judul, newQueue->judul) == 0) {
                    printf("| %s | %-30s | %-10s | %-10s | %-10s | %-15s |\n",  curr->buku.id, curr->buku.judul, curr->buku.penerbit, curr->buku.author, curr->buku.tanggal, curr->buku.status);
                    found = 1;
                    break;
                }
                curr = curr->next;
            }
            if(found == 1){
                if (strcmp(curr->buku.status, "Belum Dipinjam") == 0) {
                    break;
                }
                else {
                    printf("Buku sedang dipinjam\n");
                    getch();
                    free(newQueue);
                    goto end;
                }
            }
            else {
                printf("Buku tidak ditemukan\n\n");
                getch();
            }
        } while (1);

       printf("confirm? (y/n)"); scanf ("%c", &confirm);
       fflush(stdin);
       strcpy(newQueue->status, "pending");
        if (confirm == 'y') {
            if (*head == NULL) {
                *head = newQueue;
                *tail = newQueue;
            } else {
                (*tail)->next = newQueue;
                *tail = newQueue;
            }
            printf("Request berhasil dibuat!\n");
        } else {
            printf("Request dibatalkan!\n");
        }
        end:
}

void dequeue(request **head){
       request *temp = *head;
       *head = (*head)->next;
       free(temp);
}

void ubahStatusBukuDipinjam ( request *head) {
    curr = headBook;
    while (curr != NULL) {
        if (strcmp(curr->buku.judul, head->judul) == 0) {
            strcpy(curr->buku.status, "Dipinjam");
            return;
        }
        curr = curr->next;
    }
}

void approve(request **head, idPinjam **root, int idCount){
       int choice;
       while (*head != NULL) {
              choice = 0;
              system("cls");
              printf("-------------------------------------\n");
              printf("             Process Request         \n");
              printf("-------------------------------------\n");
              printf("Nama   : %s\n", (*head)->peminjam);
              printf("Kontak : %s\n", (*head)->kontak);
              printf("Buku   : %s\n", (*head)->judul);


              while (choice != 1 && choice != 2) {
                     printf("\nStatus:\n"
                     "1. Approve\n"
                     "2. Reject\n");

                     scanf("%d", &choice);
                     fflush(stdin);
                     switch (choice) {
                            case 1:
                                    (*root) = insert((*root), idCount, (*head));
                                    ubahStatusBukuDipinjam(*head);
                                    idCount++; idCount++;
                                   printf("Request Approved\n");
                                   dequeue(head);
                                   break;
                            case 2:
                                   printf("Request Rejected\n");
                                   dequeue(head);
                                   break;
                            default:
                                   printf("Input salah\n");
                                   break;
                     }
              }
              printf("Request sudah habis\n");
              getch();
       }
}

void kembalikanBuku(idPinjam **root){
        int id;
            system("cls");
            printf("-------------------------------------\n");
            printf("             Return Book             \n");
            printf("-------------------------------------\n");
            printf("Masukkan ID buku yang ingin dikembalikan: ");
            scanf("%d", &id);
            delete((*root), id);
            printf("buku sudah dikembalikan\n");
            printf("\n"
            "Press any key to continue...");
            getch();
            
                    
        
}    


int menu () {
       int menu;
       system("cls");
       printf("=============================\n"
              " Library Inventory Manager\n"
              "=============================\n"
              "1. Sorting Buku\n"
              "2. Search buku\n"
              "3. Request peminjaman buku\n"
              "4. Process request\n"
              "5. Kembalikan buku\n"
              "6. Exit\n");
       printf("Pilih menu: ");
       scanf("%d", &menu);
       return menu;
}


void printInorder(idPinjam* node)
{
    if (node == NULL)
        return;
 
    /* first recur on left child */
    printInorder(node->left);
 
    /* then print the data of node */
    printf("%d ", node->id);
    printf("%s ", node->peminjam);
 
    /* now recur on right child */
    printInorder(node->right);
}

// void saveChange(idPinjam *root){
//     FILE *fp = fopen("dataBuku.txt", "w");
//     if(fp == NULL) {
//         perror("Unable to open file!");
//         exit(1);
//     }
//     printInorder(root);
//     fclose(fp);
// }

int main()
{
       idPinjam *root = NULL;
       
       request *head = NULL, *tail = NULL;
       readFileDataPeminjam(&root);
       readFileDataBuku(&headBook);
       
       

       while (1) {
              switch (menu()) {
              case 1:
              		 sorting();
                     break;
              case 2:
              		// search();
                     break;
              case 3:
                     pinjam(&head, &tail);
                     break;
              case 4:
                     approve(&head, &root, idCount);
                     getch();
                     break;
              case 5:
                     kembalikanBuku(&root);
                     break;
              case 6:
                    //  saveChange(root);
                     return 0;
              default:
                     printf("Pilihan tidak tersedia\n");
              }
       }

    
    return 0;
}
