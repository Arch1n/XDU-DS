#include <bits/stdc++.h>
using namespace std;

struct node{
    string Character;
    int cnt;
    node(string x="", int y=0):Character(x),cnt(y){}
    bool operator< (const node &rhs) const{
        return cnt==rhs.cnt ? Character<rhs.Character : cnt<rhs.cnt;
    }
    node operator+ (node &rhs){
        node x;
        if(*this < rhs)
            x = node(Character+rhs.Character , cnt+rhs.cnt);
        else
            x = node(rhs.Character+Character , cnt+rhs.cnt);
        return x;
    }
};

struct Haff{
    vector <node> nodes;
    map <char,string> code;
    vector <vector<int> >G;
    map <node, size_t> id;

    void AddEdge(const node& x, const node& y){
        size_t idx = id[x], idy = id[y];
        assert(max(idx, idy) < G.size());
        G[idx].push_back(idy);
        //G[idy].push_back(idx);
    }
    void _print(ostream &out, size_t x,string spaces){
        spaces+="\t\t\t\t";
        if(!G[x].empty())_print(out, G[x][0], spaces);
        out<<spaces<<nodes[x].Character<<endl;
        if(!G[x].empty())_print(out, G[x][1], spaces);
    }
    void PrintTree(ostream &out){
        string spaces;
        int root = nodes.size()-1;
        _print(cout, root, spaces);
        _print(out, root, spaces);
    }

    void encode(int x, string lastcode=""){
        if(G[x].empty()){
            node cur = nodes[x];
            assert(cur.Character.size() == 1);
            char ch = cur.Character[0];
            code[ch] = lastcode;
            return;
        } else {
            encode(G[x][0],lastcode+"0");
            encode(G[x][1],lastcode+"1");
        }

    }
    void PreEncode(){
        code.clear();
        encode(nodes.size()-1);
    }
    string Encode(char x){
        if(code.count(x))
            return code[x];
        else return " ";
    }
    void Init(istream &in = cin, ostream &out = cout){
        int n; in>>n; in.ignore(); out<<n<<endl;
        G.resize(2*n);
        string tmp, input;
        for(int i=1;i<=n && getline(in, tmp); i++){
            out<<tmp<<endl;
            tmp+=' ';
            input+=tmp;
        }
        size_t pos = 0;
        string ch; int cnt;
        multiset<node> q;
        for(int i=1;i<=n && pos<input.size(); i++){
            ch = string ("")+input[pos];
            pos += 2;
            cnt = 0;
            while(isdigit(input[pos])){
                cnt = (cnt<<3) + (cnt<<1) + input[pos] - '0';
                pos ++;
            }
            node cur = node(ch, cnt);
            id[cur] = nodes.size();
            nodes.push_back(cur);
            q.insert(cur);
            pos++;
        }

        while(q.size() != 1){
            node fir = *q.begin(); q.erase(q.begin());
            node sec = *q.begin(); q.erase(q.begin());
            node sum = fir + sec;
            id[sum] = nodes.size();
            nodes.push_back(sum);
            q.insert(sum);
            if(fir < sec) swap(fir, sec);
            AddEdge(sum, fir);
            AddEdge(sum, sec);
        }

       /* for(auto &c:G){
            for(auto d:c){
                cout<<d<<" ";
            }
            cout<<endl;
        }
        for(size_t i=0;i<nodes.size();i++){
            cout<<i<<"  :"<<nodes[i].Character<<"   "<<nodes[i].cnt<<endl;
        }*/
        this->PreEncode();
    }
    void Decode(istream &in, ostream &out){
        string tmp,line;
        while(getline(in,tmp)){
            line+=tmp;
        }
       	//cout<<line<<endl;
       	//cout<<line.size()<<endl;
        size_t i=0,idx;
        while(1){
            if(i>=line.size())break;
            idx = nodes.size()-1;
            while(i <= line.size()){
                if(G[idx].empty()){
                    out<<nodes[idx].Character;
                    break;
                }
                idx = G[idx][ line[i]-'0' ];
                i++;
            }
            //i++;
        }
    }
}T;

int main(){
    while(1){
        system("cls");
        puts("I\t: 初始化");
        puts("E\t: 编码");
        puts("D\t: 译码");
        puts("P\t: 印代码文件");
        puts("T\t: 印哈夫曼树");
        puts("Q\t: 退出");
        string op;
        cin>>op;
        op[0] = toupper(op[0]);
        while(!(op.size()==1 && (op[0]=='I'|| op[0]=='E' || op[0]=='D' || op[0]=='P' || op[0]=='T' || op[0]=='Q'))){
            puts("无效的操作");
            system("pause");
            puts("");
            //system("cls");
            cin>>op;

        }
        if(op=="I"){
            ofstream hfmTree("hfmTree");
            T.Init(cin,hfmTree);
            hfmTree.close();
        }
        else if(op=="E"){
            if(T.code.size() == 0) {
                ofstream hfmTree("hfmTree");
                T.Init(cin,hfmTree);
                hfmTree.close();
            }
            ifstream ToBeTran("ToBeTran");
            ofstream CodeFile("CodeFile");
            string tmp,line;
            while(getline(ToBeTran, tmp)){
                line+=tmp;
            }
            for(size_t i=0; i<line.size(); i++)
                CodeFile<<T.Encode(line[i]);
            CodeFile<<endl;
            ToBeTran.close();
            CodeFile.close();
        }
        else if(op=="D"){
            ifstream CodeFile("CodeFile");
            ofstream TextFile("TextFile");
            T.Decode(CodeFile, TextFile);
            CodeFile.close();
            TextFile.close();
        }
        else if(op=="P"){
            ifstream CodeFile("CodeFile");
            ofstream CodePrin("CodePrin");
            string tmp,line;
            while(getline(CodeFile, tmp)){
                line += tmp;
            }
            for(size_t i=0; i<line.size(); i++){
                if(i&&i%50==0){
                    CodePrin<<endl;
                    cout<<endl;
                }
                CodePrin<<line[i];
                cout<<line[i];
            }
            cout<<endl;
            CodeFile.close();
            CodePrin.close();
            system("pause");
        }
        else if(op=="T"){
            ofstream TreePrint("TreePrint");
            T.PrintTree(TreePrint);
            TreePrint.close();
        }
        else if(op=="Q"){
            break;
        }

    }
    return 0;
}
