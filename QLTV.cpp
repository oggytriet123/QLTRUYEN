#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
// Khai báo c?u trúc d? li?u Truy?n (mã, tên, tác gi?, th? lo?i, t?p s?, don giá thuê/ngày, tình tr?ng)
typedef struct {
char ma_truyen[20];
char ten[20];
char tac_gia[20];
char the_loai[20];
int tap_so[10];
float don_gia_thue;
bool tinh_trang; // 1 la con; 0 la da cho thue
} truyen;

struct Node{
truyen data;
struct Node *pNext;
};

struct Stack{
Node *top;
};

void Push(Stack *t,truyen x)
{
Node *p = (Node*)malloc(sizeof(Node));
p->data = x;
p->pNext=t->top;
t->top=p;
}

void hienThiTruyen(truyen t) {
printf("Ma truyen: %s\n", t.ma_truyen);
printf("Ten: %s\n", t.ten);
printf("Tac gia: %s\n", t.tac_gia);
printf("The loai: %s\n", t.the_loai);
printf("Tap so: ");
for (int i = 0; i < 10; i++) {
if (t.tap_so[i] != 0) // chỉ in nếu có dữ liệu
printf("%d ", t.tap_so[i]);
}
printf("\n");
printf("Don gia thue/ngay: %.2f\n", t.don_gia_thue);
printf("Tinh trang: %s\n", t.tinh_trang ? "Con" : "Da cho thue");
printf("----------------------------\n");
}


void Top(Stack *t,int a)
{
Node *p=t->top;
if (p == NULL) {
printf("Stack rong! Khong co truyen nao.\n");
return;
}
printf("%d Truyen moi nhap gan nhat (Top):\n",a);
for(int i=0;i<a;i++)
{
hienThiTruyen(p->data);
p=p->pNext;
}
}

bool Pop(Stack *s) {
if(s->top == NULL) {
printf("Stack rong, khong the Pop!\n");
return false;
}
Node *p = s->top;
s->top = p->pNext;
free(p);
return true;
}
bool isEmpty(Stack *s) {
return s->top == NULL;
}

typedef struct
{
char ma_truyen[20];
char ten[50];
char ngay_thue[20];
char ngay_du_kien[20];
char ngay_tra[20];
int so_ngay;
float tong_phi;
}thue;

typedef struct Nodelog{
thue data;
struct Nodelog*lnext;
}Nodelog;

typedef struct{
Nodelog *top;
}Stacklog;

void pushLog(Stacklog *t,thue a)
{
Nodelog *p=(Nodelog*)malloc(sizeof(Nodelog));
p->data=a;
p->lnext=t->top;
t->top=p;
}

void Printlog(thue l) {
printf("Ma: %s | Ten: %s | Ngay thue: %s | Ngay du kien: %s | Ngay tra: %s | So ngay: %d | Phi: %.2f\n",
l.ma_truyen, l.ten, l.ngay_thue, l.ngay_du_kien, l.ngay_tra, l.so_ngay, l.tong_phi);
}

void Xuatthue(Stacklog *t) {
Nodelog *p = t->top;
while (p != NULL) {
Printlog(p->data);
p = p->lnext;
}
}

void Topthue(Stacklog *t,int n)
{
if(t->top==NULL)
{
printf("ko co truyen nao duoc thue");
return;
}
Nodelog *p=t->top;
for(int i=0;i<n;i++)
{
Printlog(p->data);
p=p->lnext;
}
}

void Popthue(Stacklog *t)
{
if(t->top==NULL)
{
printf("ko co truyen nao duoc thue");
return;
}
Nodelog *p=t->top;
t->top=p->lnext;
free(p);
}

typedef struct {
Node *top;
} StackUndo;

void PushUndo(StackUndo *u, truyen x) {
Node *p = (Node*)malloc(sizeof(Node));
p->data = x;
p->pNext = u->top;
u->top = p;
}

bool Undo(Stack *main, StackUndo *undo) {
if (undo->top == NULL) {
printf("Khong co thao tac nao de hoan tac!\n");
return false;
}
Node *p = undo->top;
undo->top = p->pNext;
Push(main, p->data); // hoàn tác lại
free(p);
printf("Da hoan tac mot thao tac.\n");
return true;
}

int main()
{
Stack s;
s.top = NULL;
truyen a = {"T01", "Doraemon", "Fujiko", "Thieu nhi", {1,2,3}, 5000, true};
truyen b = {"T02", "Conan", "Aoyama", "Trinh tham", {1,2}, 7000, true};
truyen c = {"T03", "One Piece", "Oda", "Phieu luu", {1}, 10000, true};
Push(&s, a);
Push(&s, b);
Push(&s, c);
Top(&s, 1); // in ra 1 truyện trên cùng
Top(&s, 2); // in ra 2 truyện trên cùng
Top(&s, 3); // in ra 3 truyện trên cùng
Top(&s, 5); // in ra nhiều hơn số phần tử, vẫn ok

return 0;
}

