#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
// Khai b�o c?u tr�c d? li?u Truy?n (m�, t�n, t�c gi?, th? lo?i, t?p s?, don gi� thu�/ng�y, t�nh tr?ng)
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
}Node;

struct Stack{
    Node *top;
};
void Push(Stack *t,truyen x)

int main()
{

}

