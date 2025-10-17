#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include<time.h>

struct tm chuyenchuoithanhngay(const char *chuoi) {
    struct tm ngay = {0};
    int d, m, y;
    sscanf(chuoi, "%d/%d/%d", &d, &m, &y);
    ngay.tm_mday = d;
    ngay.tm_mon  = m - 1;
    ngay.tm_year = y - 1900;
    return ngay;
}

int tinhkhoangcachngay(const char *chuoi1, const char *chuoi2) {
    struct tm t1 = chuyenchuoithanhngay(chuoi1);
    struct tm t2 = chuyenchuoithanhngay(chuoi2);
    time_t time1 = mktime(&t1);
    time_t time2 = mktime(&t2);
    double hieu = difftime(time2, time1); // hiệu số giây
    return (int)(hieu / (60 * 60 * 24));  // đổi giây -> ngày
}


int sosanhngay(const char *date1, const char *date2) {
    int d1, m1, y1;
    int d2, m2, y2;
    sscanf(date1, "%d/%d/%d", &d1, &m1, &y1);
    sscanf(date2, "%d/%d/%d", &d2, &m2, &y2);

    if (y1 != y2) return (y1 > y2) ? 1 : -1;
    if (m1 != m2) return (m1 > m2) ? 1 : -1;
    if (d1 != d2) return (d1 > d2) ? 1 : -1;
    return 0;
}


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

struct Node {
    truyen data;
    struct Node *pNext;
};

struct Stack {
    Node *top;
};

void Push(Stack *t, truyen x) {
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

void nhapTruyen(Stack *kho) {
    truyen t;
    printf("Nhap ma truyen: ");
    scanf("%s", t.ma_truyen);
    getchar(); // bỏ ký tự Enter

    printf("Nhap ten truyen: ");
    fgets(t.ten, sizeof(t.ten), stdin);
    t.ten[strcspn(t.ten, "\n")] = '\0';

    printf("Nhap tac gia: ");
    fgets(t.tac_gia, sizeof(t.tac_gia), stdin);
    t.tac_gia[strcspn(t.tac_gia, "\n")] = '\0';

    printf("Nhap the loai: ");
    fgets(t.the_loai, sizeof(t.the_loai), stdin);
    t.the_loai[strcspn(t.the_loai, "\n")] = '\0';

    printf("Nhap don gia thue: ");
    scanf("%f", &t.don_gia_thue);

    printf("Nhap so luong: ");
    scanf("%d", &t.so_luong);

    t.tinh_trang = (t.so_luong > 0);

    Push(kho, t);
    printf("Da them truyen moi vao kho thanh cong!\n");
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

void Top(Stack *t, int a) {
    Node *p = t->top;
    if (p == NULL) {
        printf("Stack rong! Khong co truyen nao.\n");
        return;
    }

    printf("%d Truyen moi nhap gan nhat (Top):\n", a);
    int dem = 0;
    while (p != NULL && dem < a) {
        hienThiTruyen(p->data);
        p = p->pNext;
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

truyen Pop(Stack *s, StackTra *tra) {
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
    PushTam(tra, a);
    free(p);
    return a;
}

bool isEmpty(Stack *s) {
    return s->top == NULL;
}

typedef struct {
    char ma_truyen[20];
    char ten[50];
    char ngay_thue[20];
    char ngay_du_kien[20];
    char ngay_tra[20];
    int so_ngay;
    float tong_phi;
} thue;

typedef struct Nodelog {
    thue data;
    struct Nodelog *lnext;
} Nodelog;

typedef struct {
    Nodelog *top;
} Stacklog;

void pushThue(Stacklog *t, thue a) {
    Nodelog *p = (Nodelog*)malloc(sizeof(Nodelog));
    p->data = a;
    p->lnext = t->top;
    t->top = p;
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

void Topthue(Stacklog *t, int n) {
    if (t->top == NULL) {
        printf("ko co truyen nao duoc thue");
        return;
    }

    Nodelog *p = t->top;
    int dem = 0;
    while (p != NULL && dem < n) {
        PrintThue(p->data);
        p = p->lnext;
        dem++;
    }
}

thue Popthue(Stacklog *t) {
    thue loi = {"", "", "", "", "", 0, 0.0};
    if (t->top == NULL) {
        printf("ko co truyen nao duoc thue");
        return loi;
    }

    Nodelog *p = t->top;
    thue a = p->data;
    t->top = p->lnext;
    free(p);
    return a;
}

void thueTruyen(Stack *kho, Stacklog *logThue) {
    if (isEmpty(kho)) {
        printf("Kho trong, khong co truyen de thue!\n");
        return;
    }

    char ma[20];
    printf("\nNhap ma truyen muon thue: ");
    scanf("%s", ma);

    Node *p = kho->top;
    while (p != NULL) {
        if (strcmp(p->data.ma_truyen, ma) == 0) {
            if (p->data.so_luong > 0) {
                p->data.so_luong--;
                if (p->data.so_luong == 0) p->data.tinh_trang = false;

                thue log;
                strcpy(log.ma_truyen, p->data.ma_truyen);

                printf("Nhap ngay thue (dd/mm/yyyy): ");
                scanf("%s", log.ngay_thue);
                printf("Nhap ngay du kien tra (dd/mm/yyyy): ");
                scanf("%s", log.ngay_du_kien);
                if (sosanhngay(log.ngay_du_kien, log.ngay_thue) < 0) {
                printf("Loi: Ngay du kien tra phai sau ngay thue!\n");
                return;}
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
            } else {
                printf(" Truyen '%s' da het hang!\n", p->data.ma_truyen);
                return;
            }
        }
        p = p->pNext;
    }
    printf("Khong tim thay ma truyen '%s' trong kho!\n", ma);
}


void PushKho(Stack *s, truyen x) {
    Node *p = (Node*)malloc(sizeof(Node));
    p->data = x;
    p->pNext = s->top;
    s->top = p;
}

void traTruyen(Stack *kho, Stacklog *lichSu, StackTra *tra) {
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

    while (p != NULL) {
        if (strcmp(p->data.ma_truyen, ma) == 0 && strcmp(p->data.ten, tenNguoi) == 0) {
            timThay = true;
            if (strcmp(p->data.ngay_tra, "-") != 0) {
                printf("Truyen nay da duoc tra truoc do!\n");
                return;
            }

            char ngayTraThucTe[20];
            printf("Nhap ngay tra thuc te (dd/mm/yyyy): ");
            scanf("%s", ngayTraThucTe);

            if (sosanhngay(ngayTraThucTe, p->data.ngay_thue) < 0) {
                printf("Loi: Ngay tra khong duoc truoc ngay thue!\n");
                return;
            }

            strcpy(p->data.ngay_tra, ngayTraThucTe);
            Node *q = kho->top;
            bool coTrongKho = false;
            float phithat;
            int a = tinhkhoangcachngay(p->data.ngay_thue,p->data.ngay_tra);
            while (q != NULL) {
                if (strcmp(q->data.ma_truyen, ma) == 0) {
                    if(a<=0)
                    {
                        phithat=q->data.don_gia_thue;
                    }else
                    {
                        phithat=a*q->data.don_gia_thue;
                    }
                    q->data.so_luong++;
                    q->data.tinh_trang = true;
                    printf("Da cap nhat lai so luong truyen '%s' trong kho (+1).\n", q->data.ten);
                    coTrongKho = true;
                    break;
                }
                q = q->pNext;
            }
            p->data.tong_phi=phithat;
            if (!coTrongKho && tra->top != NULL) {
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

void InTheoThuTuNhap(Stack *s) {
    StackTra d;
    d.top = NULL;

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
        Pop(&temp, &d);
    }
}

void ghiDanhSachTruyen(Stack *kho) {
    FILE *f = fopen("truyen.txt", "w");
    if (!f) {
        printf("Khong mo duoc file de ghi!\n");
        return;
    }

    Node *p = kho->top;
    while (p != NULL) {
        fprintf(f, "%s|%s|%s|%s|%.0f|%d|%d\n",
                p->data.ma_truyen,
                p->data.ten,
                p->data.tac_gia,
                p->data.the_loai,
                p->data.don_gia_thue,
                p->data.so_luong,
                p->data.tinh_trang);
        p = p->pNext;
    }

    fclose(f);
}

void docDanhSachTruyen(Stack *kho) {
    FILE *f = fopen("truyen.txt", "r");
    if (!f) {
        printf("Chua co file du lieu, tao moi!\n");
        return;
    }

    truyen t;
    while (fscanf(f, "%[^|]|%[^|]|%[^|]|%[^|]|%f|%d|%d\n",
                  t.ma_truyen,
                  t.ten,
                  t.tac_gia,
                  t.the_loai,
                  &t.don_gia_thue,
                  &t.so_luong,
                  (int*)&t.tinh_trang) == 7)
    {
        Push(kho, t);
    }

    fclose(f);
}

int main() {
    Stack kho;
    kho.top = NULL;

    Stacklog log;
    log.top = NULL;

    StackTra tra;
    tra.top = NULL;

    docDanhSachTruyen(&kho);

    int choice;
    do {
        printf("\n========== MENU QUAN LY TRUYEN ==========\n");
        printf("1. Xem danh sach truyen\n");
        printf("2. Nhap truyen moi\n");
        printf("3. Thue truyen\n");
        printf("4. Tra truyen\n");
        printf("0. Thoat\n");
        printf("=========================================\n");
        printf("Chon chuc nang: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                InTheoThuTuNhap(&kho);
                break;

            case 2:
                nhapTruyen(&kho);
                ghiDanhSachTruyen(&kho);
                break;

            case 3:
                thueTruyen(&kho, &log);
                ghiDanhSachTruyen(&kho);
                break;

            case 4:
                traTruyen(&kho, &log, &tra);
                ghiDanhSachTruyen(&kho);
                break;

            case 0:
                printf("\n Dang luu du lieu truoc khi thoat...\n");
                ghiDanhSachTruyen(&kho);
                printf(" Thoat chuong trinh!\n");
                break;

            default:
                printf(" Lua chon khong hop le!\n");
        }

    } while (choice != 0);

    return 0;
}
