/*
	Name: Bai 6
	Copyright: IUH
	Author: Nguyen Vo Hiep
	Date: 13/09/23 12:39
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
struct ttsinhvien{
	char MSSV[10], hoten[30];
	int gioitinh; //1: nu, 0: nam
	DATE ngaysinh; 
	char diachi[50];
	float dtb;
	char xeploai[10]; 
};
typedef struct ttsinhvien SINHVIEN;

struct node{
	SINHVIEN sv;
	node *pNext;
};
typedef struct node NODE;

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
void Xuat1SV(SINHVIEN sv); 						//Xuat thong tin 1 sinh vien
void XuatDanhSach(LIST L);						//Xuat danh sach sinh vien
void SpecName(char ch[]);						//Dinh dang ten nguoi, tinh thanh
int XoaSV(LIST &L, char MSSV[]);				//Xoa sinh vien voi MSSV cho truoc khoi danh sach
void SapTheoDTBtang(LIST &L);					//Sap xep danh sach theo dtb tang
void LietKeSV(LIST L);							//Liet ke cac sinh vien co diem trung binh >=5
int DemSLNam(LIST L);							//Dem so luong sinh vien nam
int CapNhatDiemTB(LIST L, char MSSV[]);			//Cap nhat diem trung binh cua mot sinh vien thong qua MSSV
void XepLoai(SINHVIEN &sv);
NODE *timSV(LIST L, char MSSV[]);
void swap(SINHVIEN &sv1, SINHVIEN &sv2);
void sapXepTheoTen(LIST &L);

//Main
int main(){
	LIST L;
	NODE *p;
	SINHVIEN SV;
	int n;
	char MSSV[10], masv[10];
	NhapDanhSach(L);
	ThemSV(L);
	XuatDanhSach(L);
	fflush(stdin);
	printf("Nhap MSSV cua sinh vien can xoa: ");gets(MSSV);
	int x = XoaSV(L, MSSV);
	if(x == 1)
		printf("Xoa thanh cong sinh vien co ma so %s", MSSV);
	else
		printf("Khong tim thay sinh vien co ma so %s", MSSV);
	//XuatDanhSach(L, n);
	LietKeSV(L);
	int k = DemSLNam(L);
	printf("\nSo luong sinh vien nam la: %d", k);
	printf("\nNhap MSSV can sua diem: ");gets(masv);
	int l = CapNhatDiemTB(L, masv);
	if(l == 0){
		printf("Sua thanh cong!\n");
		XuatDanhSach(L);
	}
	else
		printf("Khong tim thay sinh vien co ma so %s!\n", masv);
	SapTheoDTBtang(L);
	XuatDanhSach(L);
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
	fflush(stdin);
	do{
		printf("Nhap diem trung binh cua sinh vien: ");scanf("%f", &sv.dtb);
		if(sv.dtb < 0 || sv.dtb > 10)
		printf("Vui long nhap lai!\n");
	}while(sv.dtb < 0 || sv.dtb > 10);
	XepLoai(sv);
}

bool KiemTraNgaySinh(SINHVIEN sv){
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
	while(i<n-1){
		Nhap1SV(SV);
		p = TaoSV(SV);
		ThemCuoi(L,p);
		i++;
	}
}

//Them 1 sinh vien vao danh sach
void ThemSV(LIST &L){
	SINHVIEN SV;
	NODE *p;
	Nhap1SV(SV);
	p = TaoSV(SV);
	ThemCuoi(L, p);
}

//Xuat thong tin 1 sinh vien
void Xuat1SV(SINHVIEN sv){
	SpecName(sv.hoten);
	SpecName(sv.diachi);
	printf("%-10s|%-20s|%-10s|%2d/%2d/%4d|%-20s|%15.2f|%10s|\n", sv.MSSV, sv.hoten, sv.gioitinh == 1?"Nu":"Nam", sv.ngaysinh.ngay, sv.ngaysinh.thang, sv.ngaysinh.nam, sv.diachi, sv.dtb, sv.xeploai);
}

//Xuat danh sach sinh vien
void XuatDanhSach(LIST L){
	NODE *p = L.pHead;
	if(p == NULL){
		printf("Mang khong co sinh vien nao.\n");
		exit(0);
	}
	printf("|%5s|%-10s|%-20s|%-10s|%10s|%-20s|%15s|%10s|\n", "STT", "MSSV", "Ho Ten", "Gioi Tinh", "Ngay Sinh", "Dia Chi", "Diem Trung Binh", "Xep Loai");
	int i=1;
	while(p != NULL){
		printf("|%5d|", i);
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

//H�m x�a sinh vien theo MSSV
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
			printf("|%5d|", i);
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
	else if(sv.dtb >= 7)
		strcpy(sv.xeploai, "Kha");
	else if(sv.dtb >= 5)
		strcpy(sv.xeploai, "Trung binh");
	else
		strcpy(sv.xeploai, "Yeu");
}


NODE *timSV(LIST L, char MSSV[]) {
  NODE *p = L.pHead;
  while(p != NULL) {
    if(strcmp(p->sv.MSSV, MSSV) == 0) {
      return p;
    }
    p = p->pNext;
  }
  return NULL;
}

void swap(SINHVIEN &sv1, SINHVIEN &sv2) {
  SINHVIEN temp = sv1;
  sv1 = sv2;
  sv2 = temp;
}

void sapXepTheoTen(LIST &L) {
	NODE *p = L.pHead;
	NODE *q = NULL;
	if(p == NULL){
		printf("Mang khong co sinh vien nao.\n");
		exit(0);
	}
	while(p != NULL){
		for(NODE *P = p->pNext;P!= NULL; P = P->pNext){
			if(strcmp(p->sv.hoten, P->sv.hoten) > 0){
				swap(p->sv, P->sv);
			}
		}
		p = p->pNext;
	}
}
