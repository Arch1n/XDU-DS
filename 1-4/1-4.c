#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>
#include <assert.h>

struct NODE {
    int data;
    struct NODE *next, *prev;
};
typedef struct NODE node;
typedef struct NODE* link;
typedef link iterator;

typedef struct {
    iterator begin,end;
} List ;

void initList(List *L) {
    L->begin = (iterator) malloc(sizeof(node));
    L->end = (iterator) malloc(sizeof(node));

    L->begin->next = L->end;
    L->begin->prev = NULL;
    L->begin->data = INT_MIN;

    L->end->next = NULL;
    L->end->prev = L->begin;
    L->end->data = INT_MAX;
}

iterator insertNodeBehind(iterator lhs,int data) {
    iterator cur = (iterator) malloc(sizeof(node));
    iterator rhs = lhs->next;
    lhs->next = cur;
    rhs->prev = cur;
    cur->next = rhs;
    cur->prev = lhs;
    cur->data = data;
    return cur;
}

iterator insertNodeFront(iterator rhs,int data) {
    iterator cur = (iterator) malloc(sizeof(node));
    iterator lhs = rhs->prev;
    lhs->next = cur;
    rhs->prev = cur;
    cur->next = rhs;
    cur->prev = lhs;
    cur->data = data;
    return cur;
}

void deleleNode(iterator cur) {
    iterator lhs = cur->prev;
    iterator rhs = cur->next;
    lhs->next = rhs;
    rhs->prev = lhs;
    free(cur);
}

iterator begin(List *L) {
    return L->begin->next;
}

iterator end(List *L) {
    return L->end;
}

iterator rbegin(List *L) {
    return L->end->prev;
}

iterator rend(List *L) {
    return L->begin;
}

/************************************************************************************/
typedef struct {
    List L;
    int neg;
} num;

void initnum(num *A) {
    initList(&(A->L));
    A->neg = 0;
}

void read(num *A) {
    initnum(A);
    char ch;
    int isFirstChar = 1;
    int cur = 0;
    while(1) {
        ch = getchar();
        if(isFirstChar && ch == '-') {
            A->neg = 1;
        } else if(ch == ',' || ch == '\n') {
            insertNodeBehind((A->L).begin, cur);
            cur = 0;
            if(ch == '\n') return;
        } else {
            assert(isdigit(ch));
            cur = (cur<<3) + (cur<<1) + ch - '0';
            assert(0 <= cur && cur <= 9999);
        }
        isFirstChar = 0;
    }
}

void print(num A) {
    if(A.neg) putchar('-');
    iterator it;
    int i=0;
    for(it = rbegin(&A.L) ; it != rend(&A.L) ; it = it->prev, i++) {
        if(i)printf(",%04d",it->data);
        else printf("%d",it->data);
    }
    putchar('\n');
}

void _add(List* A, List *B, num *C) {
    iterator itA = begin(A);
    iterator itB = begin(B);
    while(itA != end(A) && itB != end(B)) {
        insertNodeFront(C->L.end, itA->data + itB->data);
        itA = itA->next;
        itB = itB->next;
    }
    while(itA != end(A)) {
        insertNodeFront(C->L.end, itA->data);
        itA = itA->next;
    }
    while(itB != end(B)) {
        insertNodeFront(C->L.end, itB->data);
        itB = itB->next;
    }
    iterator ext = insertNodeFront(C->L.end,0);
    iterator it;
    for(it = begin(&C->L); it != ext; it = it->next) {
        it->next->data += it->data / 10000;
        it->data %= 10000;
    }
    if(ext -> data == 0)
        deleleNode(ext);
}

void _sub(List* A, List *B, num *C) {
    iterator itA = begin(A);
    iterator itB = begin(B);
    while(itA != end(A) && itB != end(B)) {
        insertNodeFront(C->L.end, itA->data - itB->data);
        itA = itA->next;
        itB = itB->next;
    }
    while(itA != end(A)) {
        insertNodeFront(C->L.end, itA->data);
        itA = itA->next;
    }
    while(itB != end(B)) {
        insertNodeFront(C->L.end, - itB->data);
        itB = itB->next;
    }
    iterator ext = insertNodeFront(C->L.end,0);
    iterator it;
    for(it = begin(&C->L); it != ext; it = it->next) {
        while(it->data < 0) {
            it->data += 10000;
            it->next->data --;
        }
    }//½èÎ»
    for(it = begin(&C->L); it != ext; it = it->next) {
        if(it->data < 10000) continue;
        it->next->data += it->data / 10000;
        it->data %= 10000;
    }//½øÎ»
    if(ext -> data == 0)
        deleleNode(ext);
    it = rbegin(&C->L);
    if(it->data < 0) {
        C->neg = 1;
        for(it = rbegin(&C->L); it != rend(&C->L); it = it->prev) {
            it->data = - it->data;
        }
        for(it = begin(&C->L); it != ext; it = it->next) {
            while(it->data < 0) {
                it->data += 10000;
                it->next->data --;
            }
        }
        for(it = begin(&C->L); it != ext; it = it->next) {
            it->next->data += it->data / 10000;
            it->data %= 10000;
        }
    }
    it = rbegin(&C->L);
    while(it->data == 0 && it->prev != rend(&C->L)) {
        deleleNode(it);
        it = rbegin(&C->L);
    }
}

num add(num A,num B) {
    num C;
    initnum(&C);
    if(A.neg) {
        if(B.neg){
            _add(&A.L, &B.L, &C); // -a + -b = -(a+b)
            C.neg = 1;
        } else{
            _sub(&B.L, &A.L, &C);//  -a + b = b-a
        }
    } else {
        if(B.neg){
            _sub(&A.L, &B.L, &C);// a + -b  = a-b
        } else{
            _add(&A.L, &B.L, &C);// a + b
            C.neg = 0;
        }
    }
    return C;
}

num sub(num A,num B) {
    num C;
    initnum(&C);
    if(A.neg) {
        if(B.neg){
            _sub(&B.L, &A.L, &C);//b - a
        } else{
            _add(&B.L, &A.L, &C);//-(a + b)
            C.neg = 1;
        }
    } else {
        if(B.neg){
            _add(&A.L, &B.L, &C);//a + b
            C.neg = 0;
        } else{
            _sub(&A.L, &B.L, &C);//a - b
            //C.neg = 1;
        }
    }
    return C;
}

int main() {
    num A,B;
    puts("Input A:");read(&A);
    puts("Input B:");read(&B);

    printf("A = ");print(A);
    printf("B = ");print(B);

    printf("A + B = ");print(add(A,B));
    printf("A - B = ");print(sub(A,B));
    return 0;
}
