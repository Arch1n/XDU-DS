#include <stdio.h>
#include "myList.h"

void makeCir(List *L){
    L->begin->prev = L->end;
    L->end->next = L->begin;
}

void initJoseph(List *L, int n){
    int cur = 0, i;
    for(i = 1; i <= n; i++){
        scanf("%d", &cur);

        insertNodeFront(L->end, cur, i);
    }
}

void work(List *L, int m){
    int cnt = 1;
    int tmp = 0;
    iterator cur = begin(L);
    while (L->begin->next != L->end){
        if(cur == L->begin || cur == L->end){
            cur = cur->next;
        } else{

            if(cnt == m){
                m = cur->data;
                if(!tmp)printf("%d", cur->idx);
                else printf(" %d", cur->idx);
                tmp ++;
                cur = cur->prev;
                deleleNode(cur->next);
                cur = cur->next;
                cnt = 1;
            }
            else {
                cnt ++;
                cur = cur->next;
            }

        }
    }
    puts("");
}

int main(){
    int n, m;
    List Cir;
    initList(&Cir);
    scanf("%d%d", &n, &m);
    initJoseph(&Cir, n);
    makeCir(&Cir);
    work(&Cir,m);
    return 0;
}