#include <bits/stdc++.h>
using namespace std;
struct MST{
    struct edge{
        int from, to, dis;
        edge(int u=0, int v=0, int w=0):from(u),to(v),dis(w){};
        bool operator<(const edge& rhs)const{return dis<rhs.dis;}
    };
    int n,m;
    vector<edge> edges,mst;
    vector<int> fa;
    MST(int n=0, int m=0){
        this->n=n;
        this->m=m;
        edges.clear();
        mst.clear();
        edges.resize(m);
        fa.resize(n+1);
        iota(fa.begin(), fa.end(), 0);
    }
    int findfa(int x){return fa[x]==x?x:fa[x]=findfa(fa[x]);}
    void initMatrix(int n,istream &in = cin){
        this->n = n;
        edges.clear();
        mst.clear();
        fa.resize(n+1);
        iota(fa.begin(), fa.end(), 0);
        for(int i=1,t;i<=n;i++)
        for(int j=1;j<=n;j++){
            in>>t;
            if(i!=j)edges.push_back(edge(i,j,t)),this->m++;
        }
    }
    void initEdges(int n, int m, istream &in = cin){
        this->n = n;
        this->m = m;
        edges.clear();
        mst.clear();
        fa.resize(n+1);
        iota(fa.begin(), fa.end(), 0);
        for(int i=1,u,v,w;i<=m;i++){
            in>>u>>v>>w;
            edges.push_back(edge(u,v,w));
        }
    }
    void work(){
        sort(edges.begin(), edges.end());
        for(auto E:edges){
            int fx=findfa(E.from);
            int fy=findfa(E.to);
            if(fx!=fy){
                mst.push_back(E);
                fa[fx]=fy;
            }
        }
        for(auto c:mst){
            cout<<c.from<<" -> "<<c.to<<"\t"<<c.dis<<endl;

        }
    }
}G;
void printmemu(){
    puts("\t\t 1. 矩阵读入");
    puts("\t\t 2. 按边度入");
    puts("\t\t q. 退出");
}
int main(){
    while(1){
        printmemu();
        string  c;
        cin>>c;
        while(c.size()!=1 || !(c=="1"||c=="2"||c=="3"||c=="q")){
            puts("invalid input!");
            cin>>c;
        }
        if(c[0]=='1'){
            puts("输入点数:");
            int n;cin>>n;
            G.initMatrix(n);
            G.work();
        }else if(c[0]=='2'){


            int n,m;
            puts("输入点数:");
            cin>>n;
            puts("输入边数:");
            cin>>m;
            G.initEdges(n,m);
            G.work();
        }
        else break;
        system("pause");
        system("cls");
    }
    return 0;
}
