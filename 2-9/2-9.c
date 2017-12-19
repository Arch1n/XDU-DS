#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

const int INITSIZE = 1000;
const int INC = 500;
typedef struct myQueue {
	int head, tail;
	int pool;
	int *base;
} myQueue;

void initQueue(myQueue *q) {
	q->base = (int*) malloc(INITSIZE * sizeof(int));
	q->pool = INITSIZE;
	q->head = q->tail = 0;
}

int* getQueueFront(myQueue *q) {
	return &(q->base[q->head]);
}

int isQueueEmpty(myQueue *q) {
	return q->head == q->tail;
}

int popQueue(myQueue *q) {
	assert(!isQueueEmpty(q));
	int cur = q->base[q->head];
	q->head ++;
	return cur;
}

void pushQueue(myQueue *q, int cur) {

	if(q->tail+1 >= q->pool) {
		q->base = realloc(q->base, (q->pool + INC)*sizeof(int) );
		q->pool += INC;
	}
	q->base[q->tail] = cur;
	q->tail ++;
}

void printQueue(myQueue *q){
    int i;
    for(i=q->head;i<q->tail;i+=2)printf("%d %d\n",q->base[i], q->base[i+1]);
    puts("   ");
}
const int maxn = 50 + 5;
const int dx[5] = {1,0,-1, 0};
const int dy[5] = {0,1, 0,-1};
int main() {
	freopen("1.txt", "r", stdin);
	//freopen("2.txt", "w", stdout);

	int map[maxn][maxn];
	int fax[maxn][maxn];
	int fay[maxn][maxn];
	int vis[maxn][maxn];
	myQueue q;
	initQueue(&q);
	int n,i,j,m,xx,yy,k;
	memset(map, -1, sizeof(map));
	memset(vis, 0, sizeof(vis));
	memset(fax, 0, sizeof(fax));
	memset(fay, 0, sizeof(fay));
	scanf("%d", &n);
	scanf("%d%d", &yy, &xx);
	for(i=1; i<=n; i++) {
		char s[maxn];
		scanf("%s",s+1);
		m = strlen(s+1);
		for(j=1; j<=m; j++)map[i][j] = s[j]=='*';
	}
	pushQueue(&q,1);
	pushQueue(&q,1);
	fax[1][1] = 1;
	fay[1][1] = 1;
	vis[1][1] = 1;
	while(!isQueueEmpty(&q)) {
		int nx = popQueue(&q);
		int ny = popQueue(&q);
		//printf("%d %d\n", nx,ny);
		if(nx == xx && ny == yy) {
			break;
		}
		for(k=0; k<4; k++) {
			int tx = nx + dx[k];
			int ty = ny + dy[k];

			//printQueue(&q);
			if(map[tx][ty] == 0 && !vis[tx][ty]) {
				pushQueue(&q, tx);
				pushQueue(&q, ty);
				fax[tx][ty] = nx;
				fay[tx][ty] = ny;
				vis[tx][ty] = 1;
			}
		}
	}
	//puts("233");

    /*printf("finish  [%d, %d]\n",xx,yy);
	for (i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            printf("(%d,%d) -> (%d,%d) ",i,j,fax[i][j],fay[i][j]);
        }
        puts("");
    }*/
	while(!(xx==1&&yy==1)) {
		map[xx][yy]=2;
		int _x = xx, _y = yy;
		xx=fax[_x][_y];
		yy=fay[_x][_y];
		//printf("%d %d\n",xx,yy);
		if(xx<1)break;

	}
	//	puts("233");
    map[1][1]=2;
	for(i=1; i<=n; i++) {
		for(j=1; j<=m; j++) {
			if(map[i][j]==1)putchar('*');
			else if(map[i][j]==2)putchar('x');
			else putchar('.');
		}
		puts("");
	}
	return 0;
}
