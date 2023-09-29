/*
	Name: Quan ly sinh vien by single linked list
	Copyright: IUH
	Author: 
	Date: 
	Description: Quan ly thong tin sinh vien cua 1 lop hoc
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 50

typedef struct date{
	int ngay;
	int thang;
	int nam; 
}DATE; 

//Cau truc thong tin sinh vien
typedef struct ttsinhvien{
	char MSSV[10], hoten[30];
	int gioitinh; //1: nu, 0: nam
	DATE ngaysinh; 
	char diachi[50];
	float dtb;
	char xeploai[10]; 
}SINHVIEN;

typedef struct node{
	SINHVIEN sv;
	node *pNext;
}NODE;

typedef struct lsv{
	NODE *pHead, *pTail;
}LIST;

void KhoiTao(LIST &L);							//Khoi tao danh sach chua thong tin sinh vien 1 lop hoc
void ThemDau(LIST &L, NODE *p);					//Them 1 node vao dau danh sach
void ThemCuoi(LIST &L, NODE *p);				//Them 1 node vao cuoi danh sach
NODE *TaoSV(SINHVIEN SV);						//Tao node chua thong tin 1 sinh vien
void Nhap1SV(SINHVIEN &sv); 					//Nhap thong tin 1 sinh vien
bool KiemTraNgaySinh(SINHVIEN sv);				//Kiem tra tinh hop le cua ngay sinh
void NhapDanhSach(LIST &L); 					//Nhap danh sach sinh vien
void ThemSV(LIST &L);							//Them 1 sinh vien vao danh sach
bool CapNhatSV(LIST L, char MSSV[]); 
void Xuat1SV(SINHVIEN sv); 						//Xuat thong tin 1 sinh vien
void XuatDanhSach(LIST L);						//Xuat danh sach sinh vien
void SpecName(char ch[]);						//Dinh dang ten nguoi, tinh thanh
int XoaSV(LIST &L, char MSSV[]);				//Xoa sinh vien voi MSSV cho truoc khoi danh sach
void SapTheoDTBtang(LIST &L);					//Sap xep danh sach theo dtb tang
void LietKeSV(LIST L);							//Liet ke cac sinh vien co diem trung binh >=5
int DemSLNam(LIST L);							//Dem so luong sinh vien nam
int DemSLNu(LIST L);
int CapNhatDiemTB(LIST L, char MSSV[]);			//Cap nhat diem trung binh cua mot sinh vien thong qua MSSV
void XepLoai(SINHVIEN &sv);
void ThongKeTheoDTB(LIST L);
NODE *SinhVienCoDTBCaoNhat(LIST L);
NODE *TimSV(LIST L, char MSSV[]);
void Swap(SINHVIEN &sv1, SINHVIEN &sv2);
void SapXepTheoTen(LIST &L);
void GhiDanhSachVaoFile(LIST L, char filename[]);
void DocFileRaMang(LIST &L1, char filename[]);

int menu() {
	int choice;
	do {
		printf("\nChuong trinh quan ly sinh vien\n");
		printf("1. Nhap danh sach sinh vien\n");
		printf("2. Xuat danh sach sinh vien\n");
		printf("3. Them sinh vien\n");
		printf("4. Cap nhat sinh vien\n");
		printf("5. Tim sinh vien\n");
		printf("6. Xoa sinh vien\n");
		printf("7. Sap xep sinh vien\n");
		printf("8. Thong ke so luong sinh vien theo gioi tinh\n");
		printf("9. Thong ke so luong sinh vien theo diem trung binh\n");
		printf("10. Ghi danh sach sinh vien vao file\n");
		printf("11. Doc danh sach sinh vien trong file ra mang\n");
		printf("12. Thoat chuong trinh\n");
		for(int i = 0; i < 108; i++) {
			printf("=");
		}
		printf("\nNhap lua chon cua ban: ");
		scanf("%d", &choice);
		if(choice < 1 || choice > 12) {
			printf("Lua chon khong hop le. Vui long nhap lai!\n");
		} 
	} while(choice < 1 || choice > 12);

	if(choice == 12) {
		printf("Chuong trinh ket thuc\n");
		exit(0);
	}
	return choice;
}

//Main
int main(){
	LIST L;
	NODE *p;
	SINHVIEN SV;
	int n;
	char MSSV[10], masv[10], MaSV[10], filename[20];
	KhoiTao(L);
	while(true) {
		switch (menu()) {
			case 1:
				system("cls");
				NhapDanhSach(L);
				//SapXepTheoTen(L);
				break;
			
			case 2:
				system("cls");
				XuatDanhSach(L);
				break;

			case 3:
				system("cls");
				ThemSV(L);
				//SapXepTheoTen(L);
				break;

			case 4:{
				system("cls");
				printf("Nhap ma so sinh vien can cap nhat: ");
				fflush(stdin);
				gets(MaSV);
				bool b = CapNhatSV(L, MaSV);
				if(b == false)
					printf("Khong tim thay ma so sinh vien can cap nhat.\n");
				else{
					printf("Cap nhat thanh cong sinh vien co ma so %s", MaSV);
					SapXepTheoTen(L);
				}
				break;
			}
			case 5: {
				system("cls");
				printf("Nhap ma so sinh vien can tim: ");
				fflush(stdin);
				gets(MaSV);
				NODE *SV = TimSV(L, MaSV);
				if(SV == NULL) {
					printf("Khong tim thay sinh vien co ma so %s\n", MaSV);
				} else {
					printf("Thong tin sinh vien co ma so %s\n", MaSV);
					printf("\n|%-10s|%-30s|%-10s|%10s|%-20s|%15s|%-10s|\n","MSSV",
					"HO TEN","GIOI TINH","NGAY SINH","DIA CHI","DIEM TRUNG BINH","XEP LOAI");
					for(int j=0;j<113;j++)
						printf("-");
					printf("\n"); 
					Xuat1SV(SV->sv);
				}
				break;
			}
			case 6:
				system("cls");
				printf("Nhap ma so sinh vien can xoa: ");
				fflush(stdin);
				gets(MaSV);
				if(XoaSV(L, MaSV) == 0)
					printf("Khong ton tai sinh vien co ma so %s \n", MaSV);
				else{
					printf("Xoa thanh cong sinh vien co ma so %s \n", MaSV);
				}
				//SapXepTheoTen(L);
				break;

			case 7: {
				system("cls");
				printf("1. Sap xep theo ho ten\n");
				printf("2. Sap xep theo diem trung binh\n");
				int choice;
				do {
					printf("Nhap lua chon cua ban: ");
					scanf("%d", &choice);
					if(choice < 1 || choice > 2) {
						printf("Lua chon khong hop le. Vui long nhap lai!\n");
					} 
				} while(choice < 1 || choice > 2);
				if(choice == 1) {
					SapXepTheoTen(L);
				} else {
					SapTheoDTBtang(L);
				}
				break;
			}
			case 8:
				system("cls");
				printf("So luong sinh vien nam: %d\n", DemSLNam(L));
				printf("So luong sinh vien nu: %d\n", DemSLNu(L));
				break;

			case 9:{
				system("cls");
				ThongKeTheoDTB(L);
				NODE *dtbmax = SinhVienCoDTBCaoNhat(L);
				printf("Sinh vien co diem trung binh cao nhat : \n");
				printf("\n|%-10s|%-30s|%-10s|%10s|%-20s|%15s|%-10s|\n","MSSV",
					"HO TEN","GIOI TINH","NGAY SINH","DIA CHI","DIEM TRUNG BINH","XEP LOAI");
				for(int j=0;j<113;j++)
					printf("-");
				printf("\n"); 
				Xuat1SV(dtbmax->sv);
				break;
			}
			case 10:
				system("cls");
				fflush(stdin);
				printf("Nhap ten file dung de luu danh sach sinh vien: ");gets(filename);
				GhiDanhSachVaoFile(L, filename);
				break;
			case 11:
				system("cls");
				fflush(stdin);
				LIST L1;
				printf("Nhap ten file dung de xuat danh sach sinh vien: ");gets(filename);
				DocFileRaMang(L1, filename);
				XuatDanhSach(L1);
				break;
		}
	}
}


//Nhap thong tin 1 sinh vien
void Nhap1SV(SINHVIEN &sv){
	fflush(stdin);
	printf("Nhap ma so sinh vien: ");gets(sv.MSSV);
	fflush(stdin);
	printf("Nhap ho ten cua sinh vien: ");gets(sv.hoten);
	fflush(stdin);
	printf("Nhap lua chon gioi tinh(1: nu, 0: nam): ");scanf("%d", &sv.gioitinh);
	do{
		fflush(stdin);
		printf("Nhap ngay sinh: ");
	    scanf("%d/%d/%d",&sv.ngaysinh.ngay, &sv.ngaysinh.thang,&sv.ngaysinh.nam);
	}while(KiemTraNgaySinh(sv) == false);
	fflush(stdin);
	printf("Nhap dia chi cua sinh vien: ");gets(sv.diachi);
	do{
		printf("Nhap diem trung binh cua sinh vien: ");scanf("%f", &sv.dtb);
		if(sv.dtb < 0 || sv.dtb > 10)
		printf("Vui long nhap lai!\n");
	}while(sv.dtb < 0 || sv.dtb > 10);
	XepLoai(sv);
}

bool KiemTraNgaySinh(SINHVIEN sv){
	if(sv.ngaysinh.ngay == NULL || sv.ngaysinh.thang == NULL || sv.ngaysinh.nam == NULL){
		printf("=>Ngay, thang hoac nam khong duoc de trong! Nhap lai.\n"); 
		return false;
	}
	if(sv.ngaysinh.thang < 1||sv.ngaysinh.thang > 12){
		printf("=>Thang khong hop le vui long nhap lai.\n");
		return false;
	}
	switch(sv.ngaysinh.thang){
		case 1:case 3:case 5:case 7:case 8:case 10:case 12:
			if(sv.ngaysinh.ngay < 1||sv.ngaysinh.ngay > 31){
				printf("=>Ngay khong hop le. Vui long nhap lai!\n");
				return false;					
			}
			break;
		case 4:case 6:case 9:case 11:
			if(sv.ngaysinh.ngay < 1||sv.ngaysinh.ngay > 30){
				printf("=>Ngay khong hop le. Vui long nhap lai!\n");
				return false;				
			}
			break;
		case 2:
			if(sv.ngaysinh.nam % 400 ==0 || (sv.ngaysinh.nam % 4 ==0 && sv.ngaysinh.nam % 100 !=0) )
				if(sv.ngaysinh.ngay < 1 || sv.ngaysinh.ngay > 29){
					printf("=>Ngay khong hop le. Vui long nhap lai!\n");
					return false;
				}
			if(sv.ngaysinh.ngay < 1 || sv.ngaysinh.ngay > 28){
				printf("=>Ngay khong hop le. Vui long nhap lai!\n");
				return false;
			}
			break;
	}
	return true;
}

//Khoi tao danh sach chua thong tin sinh vien 1 lop hoc
void KhoiTao(LIST &L){
	L.pHead = L.pTail = NULL;
}

//Tao 1 node chua thong tin 1 sinh vien
NODE *TaoSV(SINHVIEN SV){
	NODE *p = new NODE;
	if(p == NULL){
		printf("Cap phat bo nho khong thanh cong. Ket thuc!");
		exit(0);
	}
	p->sv = SV;
	p->pNext = NULL;
	return p;
}

//Them 1 node vao dau danh sach
void ThemDau(LIST &L, NODE *p){
	if(L.pHead==NULL)
		L.pHead=L.pTail=p;
	else{
		p->pNext=L.pHead;
		L.pHead=p;
	}
}

//Them 1 node vao cuoi danh sach
void ThemCuoi(LIST &L, NODE *p){
	if(L.pHead==NULL)
		L.pHead=L.pTail=p;
	else{
		L.pTail->pNext = p;
		L.pTail = p;
	}
}

//Nhap vao danh sach sinh vien
void NhapDanhSach(LIST &L){
	int n;
	SINHVIEN SV;
	NODE *p;
	do{
		printf("Nhap so luong sinh vien cua lop hoc: ");
		scanf("%d", &n);
		if(n <= 0)
			printf("So luong sinh vien phai lon hon 0. Vui long nhap lai!\n");
	}while(n <= 0);
	int i=0;
	while(i < n){
		do{
			Nhap1SV(SV);
			if(TimSV(L,SV.MSSV) != NULL)
				printf("Ma sinh vien da ton tai. Vui long nhap lai!\n"); 
		}while(TimSV(L,SV.MSSV) != NULL);
		p = TaoSV(SV);
		ThemCuoi(L,p);
		i++;
	}
}

//Them 1 sinh vien vao danh sach
void ThemSV(LIST &L){
	SINHVIEN SV;
	NODE *p;
	do{
		Nhap1SV(SV);
		if(TimSV(L,SV.MSSV) != NULL)
			printf("Ma sinh vien da ton tai. Vui long nhap lai!\n"); 
	}while(TimSV(L,SV.MSSV) != NULL); 
	p = TaoSV(SV);
	ThemCuoi(L, p);
}

bool CapNhatSV(LIST L, char MSSV[]){
	NODE *p = TimSV(L, MSSV);
	if(p == NULL)
		return false;
	else{	
		printf("Nhap ho ten cua sinh vien: ");gets(p->sv.hoten);
		fflush(stdin);
		printf("Nhap lua chon gioi tinh(1: nu, 0: nam): ");scanf("%d", &p->sv.gioitinh);
		do{
			fflush(stdin);
			printf("Nhap ngay sinh: ");
			scanf("%d/%d/%d",&p->sv.ngaysinh.ngay, &p->sv.ngaysinh.thang, &p->sv.ngaysinh.nam);
		}while(KiemTraNgaySinh(p->sv) == false);
		fflush(stdin);
		printf("Nhap dia chi cua sinh vien: ");gets(p->sv.diachi);
		do{
			printf("Nhap diem trung binh cua sinh vien: ");scanf("%f", &p->sv.dtb);
			if(p->sv.dtb < 0 || p->sv.dtb > 10)
			printf("Vui long nhap lai!\n");
		}while(p->sv.dtb < 0 || p->sv.dtb > 10);
		XepLoai(p->sv);
		return true;
	}	
	
}

//Xuat thong tin 1 sinh vien
void Xuat1SV(SINHVIEN sv){
	SpecName(sv.hoten);
	SpecName(sv.diachi);
	printf("|%-10s|%-30s|%-10s|%2d/%2d/%4d|%-20s|%15.2f|%10s|\n", sv.MSSV, sv.hoten, sv.gioitinh == 1?"Nu":"Nam", sv.ngaysinh.ngay, sv.ngaysinh.thang, sv.ngaysinh.nam, sv.diachi, sv.dtb, sv.xeploai);
}

//Xuat danh sach sinh vien
void XuatDanhSach(LIST L){
	NODE *p = L.pHead;
	if(p == NULL){
		printf("Mang khong co sinh vien nao.\n");
		exit(0);
	}
	printf("|%5s|%-10s|%-30s|%-10s|%10s|%-20s|%15s|%10s|\n", "STT", "MSSV", "Ho Ten", "Gioi Tinh", "Ngay Sinh", "Dia Chi", "Diem Trung Binh", "Xep Loai");
	int i=1;
	while(p != NULL){
		printf("|%5d", i);
		Xuat1SV(p->sv);
		p = p->pNext;
		i++;
	}

}

//Dinh dang ho ten, tinh thanh
void SpecName(char ch[]){
	strlwr(ch);
	for(int i = 0;i < strlen(ch)-2; i++){
		if(ch[i] == ' ' && ch[i+1] != ' ' )
			if(ch[i+1] >= 97&&ch[i+1]<=122)
				ch[i+1] -=32;
	}
	if(ch[0] != ' ')
		if(ch[0] >= 97&&ch[0]<=122)
			ch[0] -=32;
}

//H?m x?a sinh vien theo MSSV
int XoaSV(LIST &L, char MSSV[]){
	NODE *pDel = L.pHead;
	NODE *pPre = NULL;
	if(L.pHead == NULL){
		printf("Mang khong co sinh vien nao.\n");
		exit(0);
	}
	while (pDel != NULL){
		if(stricmp(pDel->sv.MSSV, MSSV) == 0){
			if(pDel == L.pHead){
				L.pHead = L.pHead->pNext;
				pDel->pNext = NULL;
				delete pDel;
				return 1;
			}
			else if(pDel->pNext == NULL){
				L.pTail = pPre;
				pPre->pNext = NULL;
				delete pDel;
				return 1;
			}
			else{
				pPre->pNext = pDel->pNext;
				pDel->pNext = NULL;
				delete pDel;
				return 1;
			}
		}
		pPre = pDel;
		pDel = pDel->pNext;
	}
	
	return 0;
}

//Sap xep danh sach theo dtb tang
void SapTheoDTBtang(LIST &L){
	NODE *p = L.pHead;
	NODE *q = NULL;
	if(p == NULL){
		printf("Mang khong co sinh vien nao.\n");
		exit(0);
	}
	while(p != NULL){
		for(NODE *P = p->pNext;P!= NULL; P = P->pNext){
			if(p->sv.dtb > P->sv.dtb){
				SINHVIEN temp = p->sv;
				p->sv = P->sv;
				P->sv = temp;
			}
		}
		p = p->pNext;	
	}
}

//Liet ke danh sach cac sinh vien co diem trung binh >=5
void LietKeSV(LIST L){
	NODE *p = L.pHead;
	if(p == NULL){
		printf("Mang khong co sinh vien nao.\n");
		exit(0);
	}
	printf("\n\t-------DANH SACH CAC SINH VIEN CO DIEM TRUNG BINH TU 5 TRO LEN-------\n");
	printf("|%5s|%-10s|%-20s|%-10s|%10s|%-20s|%15s|%10s|\n", "STT", "MSSV", "Ho Ten", "Gioi Tinh", "Ngay Sinh", "Dia Chi", "Diem Trung Binh", "Xep Loai");
	int i = 1;
	while(p != NULL){
		if(p->sv.dtb >= 5){
			printf("|%5d", i);
			Xuat1SV(p->sv);
			i++;
		}
		p = p->pNext;
	}
}

//Dem so luong sinh vien nam
int DemSLNam(LIST L){
	NODE *p = L.pHead;
	if(p == NULL){
		printf("Mang khong co sinh vien nao.\n");
		exit(0);
	}
	int dem = 0;
	while (p!= NULL){
		if(p->sv.gioitinh == 0)
			dem++;
		p = p->pNext;
	}
	return dem;
}

//Dem so luong sinh vien nu
int DemSLNu(LIST L){
	NODE *p = L.pHead;
	if(p == NULL){
		printf("Mang khong co sinh vien nao.\n");
		exit(0);
	}
	int dem = 0;
	while (p != NULL){
		if(p->sv.gioitinh == 1)
			dem++;
		p = p->pNext;
	}
	return dem;
}

//Cap nhat diem trung binh theo MSSV
int CapNhatDiemTB(LIST L, char MSSV[]){
	NODE *p = L.pHead;
	if(p == NULL){
		printf("Mang khong co sinh vien nao.\n");
		exit(0);
	}
	while(p != NULL){
		if(stricmp(p->sv.MSSV, MSSV) == 0){
			do{
				printf("Nhap diem trung binh cua sinh vien: ");scanf("%f", &p->sv.dtb);
				if(p->sv.dtb < 0 || p->sv.dtb > 10)
				printf("Vui long nhap lai!\n");
			}while(p->sv.dtb < 0 || p->sv.dtb > 10);
			XepLoai(p->sv);
			return 1;
		}
		p = p->pNext;
	}
	return 0;
}

void XepLoai(SINHVIEN &sv) {
	if(sv.dtb >= 9)
		strcpy(sv.xeploai, "Xuat sac");
	else if(sv.dtb >= 8)
		strcpy(sv.xeploai, "Gioi");
	else if(sv.dtb >= 6.5)
		strcpy(sv.xeploai, "Kha");
	else if(sv.dtb >= 5)
		strcpy(sv.xeploai, "Trung binh");
	else
		strcpy(sv.xeploai, "Yeu");
}

void ThongKeTheoDTB(LIST L) {
	NODE *p = L.pHead;
	int xuatSacCount = 0, gioiCount = 0, khaCount = 0, trungBinhCount = 0, yeuCount = 0;
	while(p != NULL){
		if(p->sv.dtb >= 9) {
			xuatSacCount++;
		} else if(p->sv.dtb >= 8) {
			gioiCount++;
		} else if(p->sv.dtb >= 7) {
			khaCount++;
		} else if(p->sv.dtb >= 5) {
			trungBinhCount++;
		} else {
			yeuCount++;
		}
		p = p->pNext;
	}
	printf("So luong sinh vien xuat sac: %d\n", xuatSacCount);
	printf("So luong sinh vien gioi: %d\n", gioiCount);
	printf("So luong sinh vien kha: %d\n", khaCount);
	printf("So luong sinh vien trung binh: %d\n", trungBinhCount);
	printf("So luong sinh vien yeu: %d\n", yeuCount);
}

NODE *SinhVienCoDTBCaoNhat(LIST L){
	NODE *max = L.pHead;
	NODE *p = max->pNext;
	while(p != NULL){
		if(max->sv.dtb < p->sv.dtb)
			max = p;
		p = p->pNext;
	}
	return max;
}

NODE *TimSV(LIST L, char MSSV[]) {
  NODE *p = L.pHead;
  while(p != NULL) {
    if(strcmp(p->sv.MSSV, MSSV) == 0) {
      return p;
    }
    p = p->pNext;
  }
  return NULL;
}

void Swap(SINHVIEN &sv1, SINHVIEN &sv2) {
  SINHVIEN temp = sv1;
  sv1 = sv2;
  sv2 = temp;
}

void SapXepTheoTen(LIST &L) {
	NODE *p = L.pHead;
	NODE *q = NULL;
	if(p == NULL){
		printf("Mang khong co sinh vien nao.\n");
		exit(0);
	}
	while(p != NULL){
		for(NODE *P = p->pNext;P!= NULL; P = P->pNext){
			if(stricmp(p->sv.hoten, P->sv.hoten) > 0){
				Swap(p->sv, P->sv);
			}
		}
		p = p->pNext;
	}
}

void GhiDanhSachVaoFile(LIST L, char filename[]){
	FILE *f;
	NODE *p = L.pHead;
	f = fopen(filename, "wb");
	if(f == NULL){
		printf("Loi khong mo duoc tap tin.\n");
		exit(0);
	}
	while(p != NULL){
		fwrite(&p->sv, sizeof(SINHVIEN), 4, f);
		p = p->pNext;
	}
	printf("Ghi thanh cong.\n");
	fclose(f);
}

void DocFileRaMang(LIST &L1, char filename[]){
	FILE *f;
	SINHVIEN sv;
	NODE *pAdd;
	KhoiTao(L1);
	f = fopen(filename, "r");
	do{
	    fread(&sv, sizeof(SINHVIEN), 4, f);
	    pAdd = TaoSV(sv);
	    if(pAdd == NULL)
	    	return ;
	    ThemCuoi(L1, pAdd);
	}while(pAdd != NULL); 
    printf("Doc thanh cong.\n");
    fclose(f);
}
