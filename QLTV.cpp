#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct {
char ma_truyen[20];
char ten[20];
char tac_gia[20];
char the_loai[20];
int tap_so[10];
float don_gia_thue;
bool tinh_trang;
int so_luong;
} truyen;

struct Node{
truyen data;
struct Node *pNext;
};

struct Stack{
Node *top;
};

void Push(Stack *t, truyen x)
{
if (t->top == NULL) {
Node *p = (Node*)malloc(sizeof(Node));
x.so_luong = 1;
p->data = x;
p->pNext = NULL;
t->top = p;
return;
}
Node *p = t->top;
while (p != NULL) {
if (strcmp(p->data.ma_truyen, x.ma_truyen) == 0) {
p->data.so_luong++;
return;
}
p = p->pNext;
}
Node *moi = (Node*)malloc(sizeof(Node));
x.so_luong = 1;
moi->data = x;
moi->pNext = t->top;
t->top = moi;
}

void hienThiTruyen(truyen t) {
printf("[%s] %-15s | Tac gia: %-10s | The loai: %-10s | So luong: %d | Gia: %.0f | %s\n",
t.ma_truyen,
t.ten,
t.tac_gia,
t.the_loai,
t.so_luong,
t.don_gia_thue,
t.tinh_trang ? "Con" : "Da cho thue"
);
}

void Top(Stack *t,int a)
{
Node *p=t->top;
if (p == NULL) {
printf("Stack rong! Khong co truyen nao.\n");
return;
}
printf("%d Truyen moi nhap gan nhat (Top):\n",a);
int dem=0;
while(p!=NULL && dem<a)
{
hienThiTruyen(p->data);
p=p->pNext;
dem++;
}
}

typedef struct {
Node *top;
} StackTra;

void PushTam(StackTra *t, truyen x) {
Node *p = (Node*)malloc(sizeof(Node));
if (!p) {
printf("Khong du bo nho!\n");
return;
}
p->data = x;
p->pNext = t->top;
t->top = p;
}

truyen PopTam(StackTra *t) {
truyen loi = {"", "", "", "", {0}, 0.0, false, 0};
if (t->top == NULL) {
printf("StackTra rong, khong the PopTam!\n");
return loi;
}

Node *p = t->top;
truyen a = p->data;
t->top = p->pNext;
free(p);
return a;
}

truyen Pop(Stack *s,StackTra *tra) {
truyen loi = {"", "", "", "", {0}, 0.0, false, 0};
if (s->top == NULL) {
printf("Stack rong, khong the Pop!\n");
return loi;
}

Node *p = s->top;
truyen a = p->data;
if (p->data.so_luong > 1) {
p->data.so_luong--;
return a;
}
s->top = p->pNext;
PushTam(tra,a);
free(p);
return a;
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

void pushThue(Stacklog *t,thue a)
{
Nodelog *p=(Nodelog*)malloc(sizeof(Nodelog));
p->data=a;
p->lnext=t->top;
t->top=p;
}

void PrintThue(thue l) {
printf("Ma: %s | Ten: %s | Ngay thue: %s | Ngay du kien: %s | Ngay tra: %s | So ngay: %d | Phi: %.2f\n",
l.ma_truyen, l.ten, l.ngay_thue, l.ngay_du_kien, l.ngay_tra, l.so_ngay, l.tong_phi);
}

void Xuatthue(Stacklog *t) {
Nodelog *p = t->top;
while (p != NULL) {
PrintThue(p->data);
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
int dem=0;
while(p!=NULL && dem<n)
{
PrintThue(p->data);
p=p->lnext;
dem++;
}
}

thue Popthue(Stacklog *t)
{
thue loi = {"", "", "", "", "", 0, 0.0};
if(t->top==NULL)
{
printf("ko co truyen nao duoc thue");
return loi;
}
Nodelog *p=t->top;
thue a=p->data;
t->top=p->lnext;
free(p);
return a;
}

void thueTruyen(Stack *kho, Stacklog *logThue)
{
    if (isEmpty(kho)) {
        printf("Kho trong, khong co truyen de thue!\n");
        return;
    }
    char ma[20];
    printf("\nNhap ma truyen muon thue: ");
    scanf("%s", ma);
    Node *p = kho->top;
    while(p != NULL){
        if (strcmp(p->data.ma_truyen, ma) == 0)
        {
            if (p->data.so_luong > 0)
            {
                p->data.so_luong--;
                if (p->data.so_luong == 0) p->data.tinh_trang = false;

                thue log;
                strcpy(log.ma_truyen, p->data.ma_truyen);

                printf("Nhap ngay thue (dd/mm/yyyy): ");
                scanf("%s", log.ngay_thue);
                printf("Nhap ngay du kien tra (dd/mm/yyyy): ");
                scanf("%s", log.ngay_du_kien);
                printf("Nhap so ngay thue: ");
                scanf("%d", &log.so_ngay);
                printf("Nhap ten nguoi thue: ");
                getchar();
                fgets(log.ten, sizeof(log.ten), stdin);
                log.ten[strcspn(log.ten, "\n")] = '\0';
                log.tong_phi = log.so_ngay * p->data.don_gia_thue;
                strcpy(log.ngay_tra, "-");

                pushThue(logThue, log);
                printf("\n Thue thanh cong!\n");
                printf("Tong phi du kien: %.0f VND\n", log.tong_phi);
                printf("So luong con lai cua '%s': %d\n", p->data.ten, p->data.so_luong);
                return;
            }
            else {
                printf(" Truyen '%s' da het hang!\n", p->data.ma_truyen);
                return;
            }
        }
        p = p->pNext;
    }
    printf("Khong tim thay ma truyen '%s' trong kho!\n", ma);
}
int soSanhNgay(const char *date1, const char *date2) {
int d1, m1, y1;
int d2, m2, y2;
sscanf(date1, "%d/%d/%d", &d1, &m1, &y1);
sscanf(date2, "%d/%d/%d", &d2, &m2, &y2);

if (y1 != y2) return (y1 > y2) ? 1 : -1;
if (m1 != m2) return (m1 > m2) ? 1 : -1;
if (d1 != d2) return (d1 > d2) ? 1 : -1;
return 0;
}
void PushKho(Stack *s, truyen x)
{
Node *p = (Node*)malloc(sizeof(Node));
p->data = x;
p->pNext = s->top;
s->top = p;
}
void traTruyen(Stack *kho, Stacklog *lichSu, StackTra *tra)
{
if (lichSu->top == NULL) {
printf("Khong co giao dich thue nao!\n");
return;
}

char ma[20], tenNguoi[50];
printf("Nhap ma truyen can tra: ");
scanf("%s", ma);
printf("Nhap ten nguoi tra: ");
getchar();
fgets(tenNguoi, sizeof(tenNguoi), stdin);
tenNguoi[strcspn(tenNguoi, "\n")] = '\0';
Nodelog *p = lichSu->top;
bool timThay = false;

while (p != NULL)
{
if (strcmp(p->data.ma_truyen, ma) == 0 && strcmp(p->data.ten, tenNguoi) == 0)
{
timThay = true;
if (strcmp(p->data.ngay_tra, "-") != 0) {
printf("Truyen nay da duoc tra truoc do!\n");
return;
}
char ngayTraThucTe[20];
printf("Nhap ngay tra thuc te (dd/mm/yyyy): ");
scanf("%s", ngayTraThucTe);
if (soSanhNgay(ngayTraThucTe, p->data.ngay_thue) < 0) {
printf("Loi: Ngay tra khong duoc truoc ngay thue!\n");
return;
}
strcpy(p->data.ngay_tra, ngayTraThucTe);
Node *q = kho->top;
bool coTrongKho = false;

while (q != NULL) {
if (strcmp(q->data.ma_truyen, ma) == 0) {
q->data.so_luong++;
q->data.tinh_trang = true;
printf("Da cap nhat lai so luong truyen '%s' trong kho (+1).\n", q->data.ten);
coTrongKho = true;
break;
}
q = q->pNext;
}
if (!coTrongKho && tra->top != NULL)
{
truyen traVe = PopTam(tra);
PushKho(kho, traVe);
}

printf("Tra truyen thanh cong!\n");
return;
}
p = p->lnext;
}

if (!timThay)
printf("Khong tim thay thong tin thue tuong ung!\n");
}
/*typedef struct {
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
}*/

void InTheoThuTuNhap(Stack *s) {
StackTra d;
d.top=NULL;
if (isEmpty(s)) {
printf("Stack rong, khong co truyen!\n");
return;
}
Stack temp;
temp.top = NULL;
Node *p = s->top;
while (p != NULL) {
Push(&temp, p->data);
p = p->pNext;
}
printf("Danh sach truyen theo thu tu nhap (tu cu den moi):\n");
while (temp.top != NULL) {
hienThiTruyen(temp.top->data);
Pop(&temp,&d);
}
}

/*typedef struct {
Node *top;
} StackTam;

void PushTam(StackTam *t, truyen x) {
Node *p = (Node*)malloc(sizeof(Node));
p->data = x;
p->pNext = t->top;
t->top = p;
}

void PopTam(StackTam *t) {
if (t->top == NULL) return;
Node *p = t->top;
t->top = p->pNext;
free(p);
}*/



int main() {
    Stack kho;
    kho.top = NULL;

    StackTra tra;
    tra.top = NULL;

    Stacklog logThue;
    logThue.top = NULL;

    truyen a = {"T01", "Doraemon", "Fujiko", "Thieu nhi", {1, 2, 3}, 5000, true, 3};
    truyen b = {"T02", "Conan", "Aoyama", "Trinh tham", {1, 2}, 7000, true, 2};
    truyen c = {"T03", "One Piece", "Oda", "Phieu luu", {1}, 10000, true, 1};
    Push(&kho, a);
    Push(&kho, b);
    Push(&kho, c);

    int choice;
    do {
        printf("\n========== MENU QUAN LY TRUYEN ==========\n");
        printf("1. Xem toan bo truyen trong kho (tu cu den moi)\n");
        printf("2. Xem n truyen moi nhap gan nhat\n");
        printf("3. Thue truyen\n");
        printf("4. Tra truyen\n");
        printf("5. Xem lich su thue\n");
        printf("6. Xem n truyen vua duoc thue gan nhat\n");
        printf("0. Thoat\n");
        printf("==========================================\n");
        printf("Nhap lua chon: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                InTheoThuTuNhap(&kho);
                break;
            case 2: {
                int n;
                printf("Nhap so truyen muon xem: ");
                scanf("%d", &n);
                Top(&kho, n);
                break;
            }
            case 3:
                thueTruyen(&kho, &logThue);
                break;
            case 4:
                traTruyen(&kho, &logThue, &tra);
                break;
            case 5:
                printf("\n===== LICH SU THUE TRUYEN =====\n");
                Xuatthue(&logThue);
                break;
            case 6: {
                int n;
                printf("Nhap so lan thue gan nhat muon xem: ");
                scanf("%d", &n);
                Topthue(&logThue, n);
                break;
            }
            case 0:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
                break;
        }
    } while (choice != 0);

    return 0;
}

