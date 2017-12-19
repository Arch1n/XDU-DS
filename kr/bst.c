#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define OK 1
#define ERROR 0

struct node {
    struct node *lc, *rc, *fa;
    int data, cnt;
};

typedef struct node node, *lnode;

lnode TreeCount(lnode root, int val) {
    lnode p = root;
    while(1) {
        if(p == NULL)
            return NULL;
        else if(val == p->data)
            return p;
        else if(val < p->data)
            p = p->lc;
        else
            p = p->rc;
        //printf("p:  %x\n",p);
    }
}


void TreeInsert(lnode *root, int data) {

    /*if(*root == NULL) {
        *root = (lnode) malloc (sizeof(node));
        (*root)->data = data;
        (*root)->cnt = 1;
        (*root)->lc = (*root)->rc = (*root)->fa = NULL;
        return ;
    }*/
    lnode p = *root, fa_p;
    int insert_dir;
    /*0 4 left
      1 4 right*/
    while(1) {
        if(p == NULL) {
            lnode newnode = (lnode) malloc (sizeof(node));
            newnode->data = data;
            newnode->cnt = 1;
            newnode->lc = newnode->rc = NULL;
            newnode->fa = fa_p;
            if(!insert_dir)
                fa_p->lc = newnode;
            else
                fa_p->rc = newnode;
            break;
        } else if(data == p->data) {
            p->cnt ++;
            break;
        } else if(data < p->data)
            fa_p = p, p = p->lc, insert_dir = 0;
        else
            fa_p = p, p = p->rc, insert_dir = 1;
    }
}

void _TreeDelete(lnode root, int data) {
    lnode target = TreeCount(root, data);
    if(target == NULL)
        return ;
    lnode fa = target->fa;
    if(target->lc == NULL && target->rc == NULL) {
        if(fa->lc == target)
            fa->lc = NULL;
        else
            fa->rc = NULL;
        free(target);
    }
    //bug! start
    else if(target->lc != NULL && target->rc == NULL) {
        if(fa->lc == target)
            fa->lc = target->lc;
        else
            fa->rc = target->lc;
        target->lc->fa = fa;
        free(target);
    } else if(target->lc == NULL && target->rc != NULL) {
        if(fa->lc == target)
            fa->lc = target->rc;
        else
            fa->rc = target->rc;
        target->rc->fa = fa;
        free(target);
    }
    // bug! end
    else {
        lnode succ = target->lc;
        if(succ != NULL) {
            while(succ->rc != NULL)
                succ = succ->rc;
            int tmp = succ->data;
            int tmpcnt = succ->cnt;
            _TreeDelete(root, tmp);
            target->data = tmp;
            target->cnt = tmpcnt;
        } else puts("boom!");
    }
}

int TreeDelele(lnode root, int data) {
    lnode target = TreeCount(root, data);
    //printf("Delete find %x\n", target);
    if(target == NULL) {
        puts("No such found!");
        return ERROR;
    } else if(target->cnt > 1)
        target->cnt --;
    else {
        _TreeDelete(root, data);
    }
    return OK;
}

void TreeInorderTraversal(lnode root) {
    if(root == NULL) return;
    // puts("#");
    TreeInorderTraversal(root->lc);
    int i;
    for(i = 0; i < root->cnt; i++)
        printf("%d ", root->data);

    //printf("%x %d %d %x %x %x\n",root,root->data,root->cnt,root->lc,root->rc,root->fa);
    TreeInorderTraversal(root->rc);
}

void build(lnode *root) {
    int n;
    puts("input the number of value : n");
    scanf("%d", &n);
    while(n--) {
        int val;
        scanf("%d", &val);
        TreeInsert(root, val);
    }
}
int main() {
    lnode root = (lnode)malloc(sizeof(node));
    root->data = INT_MAX;
    root->lc = root->rc = root->fa = NULL;
    root->cnt = 0;
    build(&root);
    printf("%d\n", root->data);
    int m;
    puts("ok");
    scanf("%d", &m);
    while(m--) {
        //puts("~");
        int op, val;
        scanf("%d", &op);
        if(op==1) {
            scanf("%d", &val);
            TreeInsert(&root, val);
        } else if(op==2) {
            scanf("%d", &val);
            TreeDelele(root, val);
        }
        else TreeInorderTraversal(root),puts("");
    }
    return 0;
}
