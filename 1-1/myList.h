//
// Created by Arch1n on 2017/10/18.
//

#ifndef DATASTRUCTURE_MYLIST_H
#define DATASTRUCTURE_MYLIST_H


#include <stdlib.h>

struct NODE {
    int data;
    int idx;

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

iterator insertNodeBehind(iterator lhs, int data, int idx) {
    iterator cur = (iterator) malloc(sizeof(node));
    iterator rhs = lhs->next;
    lhs->next = cur;
    rhs->prev = cur;
    cur->next = rhs;
    cur->prev = lhs;
    cur->data = data;
    return cur;
}

iterator insertNodeFront(iterator rhs, int data,int idx) {
    iterator cur = (iterator) malloc(sizeof(node));
    iterator lhs = rhs->prev;
    lhs->next = cur;
    rhs->prev = cur;
    cur->next = rhs;
    cur->prev = lhs;
    cur->data = data;
    cur->idx = idx;
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

#endif //DATASTRUCTURE_MYLIST_H
