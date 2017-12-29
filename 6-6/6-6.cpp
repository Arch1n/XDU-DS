#include <bits/stdc++.h>
using namespace std;
vector<int> ori, mess, tmp;
long long Shiftcnt, Compcnt;

#define FORMAT  \
    "[%s]\n" \
    "  time elapsed: %.6fs\n" \
    "  swap:         %lld\n" \
    "  compare:      %lld\n" \

void gen(int n ,bool genrandom = true){
    ori.resize(n+1);
    mess.resize(n+1);
    iota(ori.begin(), ori.end(), 0);
    iota(mess.begin(), mess.end(), 0);
    if(genrandom)
        random_shuffle(++mess.begin(), mess.end());
    else
        reverse(++mess.begin(), mess.end());
}

void work(const char* (*func) (int)){
    Shiftcnt = 0, Compcnt = 0;
    tmp.clear();
    for(auto c:mess)tmp.push_back(c);
    clock_t begin_time,end_time;
    begin_time = clock();
    const char *name = func(tmp.size()-1);
    end_time = clock();
    printf(FORMAT, name, (end_time - begin_time) * 1.0 / CLOCKS_PER_SEC, Shiftcnt, Compcnt);
}

const char * BubbleSort(int n){
    bool swapped = false;
    do{
        swapped = false;
        for(int i=1;i<n-1;i++){
            if(Compcnt++, tmp[i+1] < tmp[i]){
                Shiftcnt += 3;
                swapped = true;
                swap(tmp[i], tmp[i+1]);
            }
        }

    }while(swapped);
    return __func__;
}

const char * InsertSort(int n){
    for(int i=2;i<=n;i++){
        tmp[0]=tmp[i],Shiftcnt++;
        int j=i-1;
        while(Compcnt++, tmp[0]<tmp[j]){
            tmp[j+1]=tmp[j], Shiftcnt++;
            j--;
        }
        tmp[j+1]=tmp[0], Shiftcnt++;
    }
    return __func__;
}

const char * SelectSort(int n){
    for(int i=1;i<=n-1;i++){
        int minn=i;
        for(int j=i+1;j<=n;j++){
            if(Compcnt++, tmp[j] < tmp[minn])
                minn = j;
        }
        if(minn != i) swap(tmp[i], tmp[minn]), Shiftcnt += 3;
    }
    return __func__;
}

void Qsort(int l, int r){
    if(l<r){
        int i=l, j=r;
        int mid = (l+r)>>1;
        do{
            while(Compcnt++, tmp[i]<tmp[mid]) i++;
            while(Compcnt++, tmp[mid]<tmp[j]) j--;
            if(i <= j){
                if(mid == i) mid=j;
                else if(mid == j) mid=i;
                swap(tmp[i], tmp[j]);
                Shiftcnt += 3;
                i++;
                j--;
            }
        }while(i<=j);
        Qsort(l,j);Qsort(i,r);
    }
}
const char * QuickSort(int n){
    Qsort(1,n);
    return __func__;
}

const char * ShellSort(int n){
    int i=4, h=1;
    while(i<=n) i<<=1, h=(h<<1)|1;
    while(h!=0){
        i=h;
        while(i<=n){
            int j=i-h;
            while(j>0 && (Compcnt++, tmp[j+h]<tmp[j])){
                swap(tmp[j], tmp[j+h]), Shiftcnt+=3;
                j = j-h;
            }
            i++;
        }
        h = (h-1)/2;
    }
    return __func__;
}

void modify(int l,int r){
    int i=l;
    int j=l<<1;
    int lf=0;
    bool finished = false;
    Shiftcnt++, tmp[0] = tmp[l];
    Shiftcnt++, lf = tmp[l];
    while(j<=r && !finished){
        if(j<r && (Compcnt++, tmp[j+1]>tmp[j])) j++;
        if(! (Compcnt++, tmp[j]>tmp[0])) finished = true;
        else {
            Shiftcnt++, tmp[i] = tmp[j];
            i=j;
            j=i<<1;
        }
    }
    Shiftcnt++, tmp[i]=lf;
}

const char * HeapSort(int n){
    for(int left = n/2;left; left--) modify(left, n);
        for(int right = n; right>=2; right--){
            swap(tmp[1], tmp[right]), Shiftcnt+=3;
            modify(1, right-1);
        }
    return __func__;
}
int main(){

    gen(10000, 0);
    work(BubbleSort);
    work(InsertSort);
    work(SelectSort);
    work(QuickSort);
    work(ShellSort);
    work(HeapSort);
    return 0;
}
