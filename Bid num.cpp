#include <stdio.h> 
#include <stdlib.h>
#include<cmath>

#define N 500 //大數位數=4N 

int Dimensions(int*);//大數維度 
void add(int*, int*, int*);
void subtract(int*, int*, int*);
void multiply(int*, int, int*);//大數乘整數  
void divide(int*, int, int*);//大數除整數 
//void big_div(int*,int*int*); //大數除大數(未使用 
void towComplement(int*, int*);  // ~
void absv(int*, int*);    // 轉abs
void print(int*);         // 顯示大數
void equal(int*,int*);//大數等值 
void level(int, int, int*);//階層 
void delevel(int, int, int*);//去階層 
void clevel(int,int,int*); //c int a取int b 

int main(){
 int a[N]={0},b[N],u,d;
 scanf("%d%d",&u,&d);
 clevel(u,d,a); print(a);
 //printf("\n\n%d",Dimensions(a));
}
/*int main(void) { 
    int a[] = {0, 0, 0, 1234, 5678, 9910, 1923, 1124};
    int b[] = {9999, 9999, 9999, 9999, 9999, 9999, 9999, 9901}; // -99
    int c1[N], c2[N], c3[N], c4[N] = {0};
        
    add(a, b, c1);       print(c1);
    subtract(a, b, c2);  print(c2);
    multiply(a, -3, c3); print(c3);
    divide(a, -3, c4);   print(c4);

    return 0; 
} */

void add(int* a, int* b, int* c) { 
    if(b[0] == 9999) {
        int Complement[N] = {0};
        towComplement(b, Complement);
        subtract(a, Complement, c);
    } else {
        int i, carry = 0; 
        for(i = N - 1; i >= 0; i--) {
            c[i] = a[i] + b[i] + carry; 
            if(c[i] < 10000) {
                carry = 0; 
            } else { // 進位 
                c[i] = c[i] - 10000; 
                carry = 1; 
            } 
        } 
    }
} 

void subtract(int* a, int* b, int* c) {
    if(b[0] == 9999) {
        int Complement[N] = {0};
        towComplement(b, Complement);
        add(a, Complement, c);
    } else {
        int i, borrow = 0; 
        for(i = N - 1; i >= 0; i--) { 
            c[i] = a[i] - b[i] - borrow; 
            if(c[i] >= 0) {
                borrow = 0;
            } else { // 借位 
                c[i] = c[i] + 10000; 
                borrow = 1; 
            } 
       } 
    }
} 

void multiply(int* a, int b, int* c) { // b 為乘數
    int op1[N] = {0}; absv(a, op1);
    int op2 = abs(b);

    int i, tmp, carry = 0; 
    for(i = N - 1; i >= 0; i--) { 
        tmp = op1[i] * op2 + carry; 
        c[i] = tmp % 10000;    
        carry = tmp / 10000; 
    }
    
    if((a[0] == 9999 && b > 0) || (a[0] == 0 && b < 0)) {
        towComplement(c, c);
    }
} 

void divide(int* a, int b, int *c) {  // b 為除數 
    int op1[N] = {0}; absv(a, op1);
    int op2 = abs(b);
    
    int i, tmp, remain = 0; 
    for(i = 1; i < N; i++) { 
        tmp = op1[i] + remain; 
        c[i] = tmp / op2; 
        remain = (tmp % op2) * 10000; 
    }

    if((a[0] == 9999 && b > 0) || (a[0] == 0 && b < 0)) {
        towComplement(c, c);
    }    
}

int Dimensions(int* a){
	int i;
	for(i=N-1;i>=0 && a[i]==0;i--);
	if(i==0)
		return 0;
	else
		return i*4-4+log10((float)a[i]);
}

/*void big_div(int* a,int* b,int* c){
	
}*/

void towComplement(int* src, int* Complement) {
    int j;
    for(j = 0; j < N; j++) {
        Complement[j] = 9999 - src[j];
    }
    Complement[N - 1] += 1;
}

void absv(int* src, int* op) {
    if(src[0] == 9999) {
        towComplement(src, op);
    } else {
        int i;
        for(i = 0; i < N; i++) {
            op[i] = src[i];
        }
    }
}

void print(int* c) {
    int v[N] = {0}; absv(c, v);
    
    if(c[0] == 9999) {
        printf("-");
    }
    
    int isDropZero = 1;
    int i;
    for(i = 0; i < N; i++) {
        char s[5] = {'\0'};
        sprintf(s, "%04d", v[i]);
        if(isDropZero) {
            int j;
            for(j = 0; s[j] == '0' && j < 4; j++);
            if(j < 4) {
                isDropZero = 0;
                for(; j < 4; j++) {
                    printf("%c", s[j]);
                }
            } else if(i == N - 1) {
                printf("0");
            }
        } else {
            printf(s);
        }
    }
    printf("\n");
}
void equal(int* a, int* b){
 for(int u=0;u<N;u++)
  a[u]=b[u];
}
void level(int initial, int final, int *c){
 c[N]={0};
 int d[N]={0};
 c[N-1]=1;
 //int d[N];
 for(int u= initial;u<= final;u++){
  multiply(c,u,c);
 // equal(c,d);
 }
}

void delevel(int initial, int final, int *c){
 //c[N]={0};
 int d[N]={0};
 //c[N-1]=1;
 //int d[N];
 for(int u= initial;u<= final;u++){
  divide(c,u,c);
 // equal(c,d);
 }
}

void clevel(int a, int b, int *c){
 int at[N],bt[N],d[N],t[N];
 c[N]={0};
 c[N]=1;
 level(a-b+1,a,c);
 delevel(1,b,c);
 //delevel(a-b,a,c);
 
}