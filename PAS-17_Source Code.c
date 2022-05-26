#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<omp.h>
#include<ctype.h>

/*Proyek Akhir 
Kelompok 17 
Nama: 
Handaneswari Pramuahyta Imanda - 2106731346
Andikha Wisanggeni - 2106731503
*/

//struct berisi data customer untuk linked list
struct Customer {
    char name[32];
    char checkin[15];
    char checkout[15];
    char checkinstat[10];
    char checkoutstat[10];
    char roomType[20];
    int total;
    char paket[20];
    struct Customer *next_cust;
};

//function prototype
struct Customer *head;
struct Customer *bookhistory();
struct Customer *searchtodelete();
void loginAdmin(FILE *file, struct Customer *head);
void loadData(FILE *file,struct Customer *load, int code);
void bookingdata(struct Customer *data,int code);
void push(struct Customer **head_ref,struct Customer tempdata);
int menuAdmin(FILE *file, struct Customer *head);
int menuGuest(struct Customer *head,FILE *file);
int deletedata (struct Customer **head, int position);
void checkin(struct Customer *data);
void checkout(struct Customer *data);
int bookRoom(struct Customer *head, FILE *file);
int deletedata (struct Customer **head,int position);
int deletedatafile(char *searchname);


int main(){
    system("color 4F");
    struct Customer *temp;
    head = NULL;
    temp = NULL;
    FILE *file;
	int pilihan;
	do{
	printf("                                   SELAMAT DATANG DI K-OYO \n");
	printf("		 ====================================================================\n");
	printf("		||            Silahkan pilih role anda:                             ||\n");
	printf("		||             1- Guest                                             ||\n");
	printf("		||             2- Admin                                             ||\n");
	printf("		||             3- Keluar                                            ||\n");
	printf("		=====================================================================\n");
	printf("\n 		>>Pilihan role: ");
	scanf("%d",&pilihan );
	system("cls");
	switch(pilihan){
		case 1: 
		menuGuest(head,file);
		break;
		case 2: 
		loginAdmin(file,head);
		break;
		case 3:
		break;
		}
	}while(pilihan!=3);
}

//untuk log in admin 
void loginAdmin(FILE *file, struct Customer *head){
	printf("			Selamat Datang Admin! \n");
	char username[10],c=' ';
    char pw[10],code[10];
    char uname[10]="admin";
    char pass[10]="pass";
    int flag, i=0;
    do{
    printf("\n  **************************  LOGIN FORM  **************************  ");
    printf(" \n                       ENTER USERNAME:-");
	scanf("%s", &username);
	printf(" \n                       ENTER PASSWORD:-");
    	while(i<10)
	{
	    pw[i]=getch();
	    c=pw[i];
	    if(c==13) break;
	    else printf("*");
	    i++;
	}
	pw[i]='\0';
    if(strcmp(username,uname)==0 && strcmp(pw,pass)==0){
    	printf("  \n\n                 WELCOME !!!! LOGIN IS SUCCESSFUL \n");
    	system("pause");
    	system("cls");
    	flag = 1;
    	menuAdmin(file, head);
    	break;
	}
	else{
		printf("\nPassword atau Username salah silahkan coba lagi \n");
	}
	} while(flag==0);
}

int menuAdmin(FILE *file, struct Customer *head){
	int pilihan; 
	printf("\n				Welcome Admin!\n");
	printf("====================================================================\n");
	printf("	Menu Admin: ");
	printf("\n	1. Lihat Data Booking Kamar");
	printf("\n	2. Check In");
	printf("\n	3. Check Out");
	printf("\n=====================================================================\n");
	printf("\n	Pilihan: ");
	scanf("%d", &pilihan);
	system("cls");
	switch(pilihan){
		case 1:
			loadData(file, head,1);
			break;
		case 2: 
			loadData(file, head,2);
			break;
		case 3:
			loadData(file,head,3);
			break;
	}
}

int menuGuest(struct Customer *head,FILE *file){
	int pilihancust;
	printf("MENU: ");
	printf("\n1. Pesan Kamar"); 
	printf("\n2. Lihat Riwayat Booking");  
	printf("\n3. Batalkan Pesanan");
	printf("\n4. Kembali ke menu");
	printf("\nPilihan: ");
	scanf("%d", &pilihancust);
	system("cls");
	switch(pilihancust){
		case(1): 
			bookRoom(head,file);
			break;
		case(2): 
			bookhistory(&head);
			break;
		case(3): 
			searchtodelete(&head);
			break;	
		case(4):
			pilihancust = 3;
			return pilihancust;
			break;
		}
}

//untuk melakukan check in 
void checkin(struct Customer *data){
	struct Customer *current = data;
	char searchname[30];
	printf("Nama yang akan melakukan check in: ");
	scanf(" %[^\n]s", &searchname);
	if(current == NULL){ //mengecek apakah linked list memiliki isi atau tidak
        printf("belum ada booking yang dilakukan!\n");
    }
    else{
    	while (current != NULL){
    		if(strcmp(searchname,current->name)==0){
    			printf("\nNama Pemesan: %s", current->name);
				printf("\nTanggal Check in: %s", current->checkin);
				printf("\nStatus : Checked in");
				printf("\nTanggal Check out: %s ", current->checkout);
				printf("\nJenis Kamar: %s ", current->roomType);
				printf("\nPaket:  %s ", current->paket);
		}
    	current = current->next_cust;
 	   }	
    }
    	system("pause");
    	system("cls");
}

//untuk melakukan check out 
void checkout(struct Customer *data){
	struct Customer *current = data;
	char searchname[30];
	printf("Nama yang akan melakukan check in: ");
	scanf(" %[^\n]s", &searchname);
	if(current == NULL){ //mengecek apakah linked list memiliki isi atau tidak
        printf("belum ada booking yang dilakukan!\n");
    }
    else{
    	while (current != NULL){
    		if(strcmp(searchname,current->name)==0){
    			printf("\nNama Pemesan: %s", current->name);
				printf("\nTanggal Check in: %s", current->checkin);
				printf("\nTanggal Check out: %s ", current->checkout);
				printf("\nStatus : Checked out");
				printf("\nJenis Kamar: %s ", current->roomType);
				printf("\nPaket:  %s ", current->paket);
		}
    	current = current->next_cust;
 	   }	
    }
    	system("pause");
    	system("cls");
}

//untuk me-load data ketika program pertama kali dijalankan
//data diambil dari file berisi input yang sudah dimasukkan oleh user
void loadData(FILE *file,struct Customer *load, int code){
	struct Customer newdata;
	struct Customer tempdata;
	char *token;
  	char buffer[1024];
	int datacount=0,col;
	//membuka file yang berisi input customer
	file = fopen("test.csv","r");
	// Error Correction apabila file tidak dapat dibuka
	if(file == NULL){
		printf("Tidak Terdapat File untuk Di Load !!\n");
		system("pause");
		return;
	}
	// Loop untuk mengambil data dari file csv
	while (fgets(buffer, sizeof(buffer), file)){
		col = 1;
		// Melakukan parsing data dengan batasan ;
    	token = strtok(buffer, ";");
    	while(token != NULL){
   		// Mengambil nama dalam kolom pertama
    	if(col == 1){
    		strcpy(tempdata.name,token);
		}
		// Mengambil Asal Negara dari kolom kedua
		else if(col ==2){
			strcpy(tempdata.checkin,token);
		}
		// Mengambil data jenis dari kolom ketiga
		else if(col ==3){
			strcpy(tempdata.checkout,token);	
		}
		// Mengambil data jumlah penjualan dari kolom keempat
		else if(col ==4){
			strcpy(tempdata.roomType,token);
		}
		else if(col ==5){
			strcpy(tempdata.paket,token);
		}
		col++;
    	token = strtok(NULL, ";");
    	}
    	/*memasukkan data yang baru ke dalam linked list 
    	yang masih kosong */
		push(&head,tempdata);
		}
	fclose(file);
	bookingdata(head,code);
	}
	
//untuk memasukkan ke dalam linked list dan membuat node baru
void push(struct Customer **head_ref,struct Customer tempdata)
{
	/*di dalam linked list, data yang paling terakhir ditambahkan akan ditabahkan
	di depan linked list*/
    struct Customer* new_node = (struct Customer*) malloc(sizeof(struct Customer));
    strcpy(new_node->name,tempdata.name);
    strcpy(new_node->checkin, tempdata.checkin);
    strcpy(new_node->checkout,tempdata.checkout);
    strcpy(new_node->roomType,tempdata.roomType);
    strcpy(new_node->paket,tempdata.paket);
    new_node->next_cust = (*head_ref);
    (*head_ref)    = new_node;
}

//menampilkan data dalam bentuk tabel
void bookingdata(struct Customer *data,int code){
	struct Customer *current = data;
	if(code==1){
	if(current == NULL){ //mengecek apakah linked list memiliki isi atau tidak
        printf("belum ada booking yang dilakukan!\n");
    }
    else{
    	printf("%-20s %-10s %-10s %-15s %-15s\n","Nama","Check in", "Check Out","Room Type","Pake");
		#pragma omp parallel
    	{
		#pragma omp master
		{
	while(current != NULL){
		#pragma omp task firstprivate(current)
		{
			#pragma omp critical
		printf("%-20s %-10s %-10s %-15s %-15s"	,current->name, current->checkin,
												 current->checkout,current->roomType,
												 current->paket);
											}
		current = current->next_cust;
		}
	system("pause");
	system("cls");
			}
		}	
	}
}
	else if(code ==2){
		//mengambil data untuk function check in
		checkin(current);
	}
	else if(code == 3){
		//mengambil data untuk function check out 
		checkout(current);
	}
}

//mengisi data dan melakukan booking kamar
int bookRoom(struct Customer *head, FILE *file){
	struct Customer *newdata; 
	struct Customer *current;
	newdata = malloc(sizeof(struct Customer));
	int i;
	int roomtype,day, paket, konfirmasi;
	//membuka file untuk menyimpan data yang telah dimasukkan
	file = fopen("test.csv","a");
	time_t t;
	time(&t);
	if(newdata != NULL){
	printf("		Pemesanan Kamar\n");
	printf("Tanggal hari ini: %s ",ctime(&t));
	printf("Nama: ");
	scanf(" %[^\n]s", &newdata->name);
	printf("Masukkan tanggal check in (dd/mm/yyyy): "); //blm ada error handlingnya 
	scanf(" %[^\n]s", &newdata->checkin);
	printf("Masukkan tanggal check out (dd/mm/yyyy): "); //blm ada error handlingnya 
	scanf(" %[^\n]s", &newdata->checkout);  
	printf("Jumlah Kamar: ");
	scanf("%d", &newdata->total);
	system("cls");
	#pragma omp for
	for(i=0;i< newdata->total ;i++){
	printf("Pesanan atas nama: %s \n", newdata->name);
	printf("pesanan untuk kamar ke-%d\n", newdata->total);
	printf("Jenis Kamar: ");
	printf("\n1. Standard (600.000)");
	printf("\n2. Deluxe   (700.000)");
	printf("\n3. Suite    (1.100.000)");
	printf("\nPilihan: ");
	scanf("%d", &roomtype);
	if(roomtype==1)
	strcpy(newdata->roomType, "Standard");
	else if(roomtype==2)
	strcpy(newdata->roomType,"Deluxe");
	else
	strcpy(newdata->roomType,"Suite");
	printf("Paket: ");
	printf("\n1. With Breakfast (+50.000)");
	printf("\n2. No Breakfast");
	printf("\nPilihan: ");
	scanf("%d",&paket); 
	if(paket==1)
	strcpy(newdata->paket,"With Breakfast");
	else
	strcpy(newdata->paket,"No Breakfast");
	}
	system("pause");
	system("cls");
	printf("Konfirmasi Pesanan: \n");
	printf("\nNama Pemesan: %s", newdata->name);
	printf("\nTanggal Check in: %s", newdata->checkin);
	printf("\nTanggal Check out: %s ", newdata->checkout);
	printf("\nBanyak Kamar yang dipesan: %d ", newdata->total);
	printf("\nJenis Kamar: %s ", newdata->roomType);
	printf("\nPaket:  %s ", newdata->paket);
	printf("\nKonfirmasi pesanan: ");
	scanf("%d", &konfirmasi);
	if(konfirmasi==1){
	printf("pesanan terkonfirmasi\n");
	system("pause");
	system("cls");
	//menuliskan data ke file 
	fprintf(file,"%s;%s;%s;%s;%s\n", newdata->name, newdata->checkin, newdata->checkout, newdata->roomType, newdata->paket);
	fclose(file);
	newdata->next_cust = NULL;
	 if(head == NULL){
            head = newdata;
        }else{
            current = head;
            while(current->next_cust != NULL){
            current = current->next_cust;
        	}
        	current->next_cust = newdata;
      		 }
    	}
	}
}

//mencari data booking yang sudah dilakukan customer
struct Customer *bookhistory(struct Customer *data){
	struct Customer *current = data;
	char searchname[30];
	printf("Nama pemesan: ");
	scanf(" %[^\n]s", &searchname);
	if(current == NULL){ //mengecek apakah linked list memiliki isi atau tidak
        printf("tidak ada pesanan yang dilakukan dengan nama tersebut!\n");
        return NULL;
    }
    while(current != NULL){
     if(strcmp(current->name,searchname)==0){
	    printf("\nNama Pemesan: %s", current->name);
		printf("\nTanggal Check in: %s", current->checkin);
		printf("\nTanggal Check out: %s ", current->checkout);
		printf("\nBanyak Kamar yang dipesan: %d ", current->total);
		printf("\nJenis Kamar: %s ", current->roomType);
		printf("\nPaket:  %s ", current->paket);
	}
	current = current->next_cust;
}
}

//mencari nama customer untuk melakukan cancel terhadap booking
struct Customer *searchtodelete(struct Customer *data){
	struct Customer *current = data;
	char searchname[30];
	int position=0;
	printf("Nama pemesan: ");
	scanf(" %[^\n]s", &searchname);
	if(current == NULL){ //mengecek apakah linked list memiliki isi atau tidak
        printf("tidak ada pesanan yang dilakukan dengan nama tersebut!\n");
        return NULL;
    }
    while(current != NULL){
     if(strcmp(current->name,searchname)==0){
	   deletedata(&current,position);
	   deletedatafile(searchname);
	   break;
	}
	position++;
	current = current->next_cust;	
}
}

//menghapus data
int deletedata (struct Customer **head,int position)
{
	struct Customer *current = *head;
	struct Customer *previous = *head;
	if(*head==NULL){
		printf("List is already empty");
	}
	else if(position == 1){
		*head = current->next_cust;
		free(current);
		current=NULL;
	}
	else{
		while(position != 2){
			previous = current;
			current = current->next_cust;
			position--;
		}
			previous->next_cust = current->next_cust;
			free(current);
			current=NULL;
	}
	printf("Succesfully Deleted\n");
	system("pause");
	system("cls");
}

//hapus data di file 
int deletedatafile(char *searchname){
char name[50], roomtype[10], paket[10];
	char checkin[10],checkout[10];
	char *sp;
	FILE *f1,*f2;
	f1 = fopen("test.csv","r");
	f2 = fopen("testTemp.csv","a");
	char line[100];
	while(fgets(line,100,f1)!=NULL){
		sp = strtok(line,";");
		strcpy(name,sp);
		sp = strtok(NULL,";");
		strcpy(checkin,sp);
		sp = strtok(NULL,";");
		strcpy(checkout,sp);
		sp = strtok(NULL,";");
		strcpy(roomtype,sp);
		sp = strtok(NULL,";");
		strcpy(paket,sp);
		if(strcmp(name,searchname)!=0){
			fprintf(f2,"%s;%s;%s;%s;%s\n",name,checkin,checkout, roomtype,paket);
		}
	}
	fclose(f1);
	fclose(f2);
	remove("test.csv");
    rename("testTemp.csv", "test.csv");
}

