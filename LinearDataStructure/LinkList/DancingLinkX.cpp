#include <cstdio>
#include <cstring>

const int MAXA = 10;
const int MAXC = 324+10;
const int MAXR = 729+10;
const int MAXN = MAXR*4+MAXC;

int n = 324, T;

struct DancingLinks{
    char c;
    int sz, S[MAXC], 
        Col[MAXN], Row[MAXN], 
        L[MAXN], R[MAXN], U[MAXN], D[MAXN], 
        head[MAXA][MAXA][MAXA],
        anna[MAXA][MAXA];

    inline  void Clear() {
        memset(S, 0, sizeof(S));
        memset(Col, 0, sizeof(Col));
        for (int i=0; i<=81*4; i++)
            L[i] = i-1, R[i] = i+1,
            U[i] = i, D[i] = i;
        L[0] = n, R[n] = 0;
        sz = n;
    }

    inline void Scan() {
        do
            c = getchar();
        while (!(48<=c && c<=57));

        for (int i=1; i<=9; i++)
            for (int j=1; j<=9; j++)
                anna[i][j] = c-48,
                c = getchar();
    }

    inline void Print() {
        for (int i=1; i<=9; i++)
            for (int j=1; j<=9; j++)
                printf("%d", anna[i][j]);
        printf("\n");
    }
    
    inline int _GetPortion(int i,int j) {
        return (--i/3)*3+(--j/3+1);
    }

    inline void AddNode(int c,int sz) {
        U[D[c]] = sz, D[sz] = D[c];
        U[sz] = c, D[c] = sz;
        S[c] ++, Col[sz] = c;
    }

    inline void Remove(int c) {
        L[R[c]] = L[c], R[L[c]] = R[c];
        for (int i=D[c]; i!=c; i=D[i])
            for (int j=R[i]; j!=i; j=R[j])
                U[D[j]]=U[j], D[U[j]]=D[j],
                -- S[Col[j]];
    }

    inline void Resume(int c) {
        for (int i=U[c]; i!=c; i=U[i])
            for (int j=L[i]; j!=i; j=L[j])
                U[D[j]] = j, D[U[j]] = j,
                ++ S[Col[j]];
        L[R[c]] = c, R[L[c]] = c;
    }

    inline bool DFS(int k) {
            if (k>81) return true;
    
            int c = R[0], temp;
            for (int i=R[0]; i!=0; i=R[i]) {
                if (!S[i]) return false;
                if (S[i]<S[c]) c = i;
            }
            Remove(c);

            for (int i=D[c]; i!=c; i=D[i]) {
                temp = Row[i];
                anna[temp/100][(temp/10)%10] = temp%10;
                for (int j=R[i]; j!=i; j=R[j])
                    Remove(Col[j]);
        
                if (DFS(k+1)) return true;
        
                for (int j=L[i]; j!=i; j=L[j])
                    Resume(Col[j]);
            }
            Resume(c);
    
            return false;
        }

        inline void AddRow(int i, int j, int k) {
            for (int u=1; u<=4; u++)
                L[sz+u] = sz+u-1, R[sz+u] = sz+u+1,
                Row[sz+u] = 100*i+10*j+k;
                
            L[sz+1] = sz+4, R[sz+4] = sz+1;
            head[i][j][k] = sz+1;
            AddNode(81*0+(i-1)*9+j, ++sz);
            AddNode(81*1+(i-1)*9+k, ++sz);
            AddNode(81*2+(j-1)*9+k, ++sz);
            AddNode(81*3+(_GetPortion(i,j)-1)*9+k, ++sz);
        }
        
        inline void Solve() {
            Clear();
            Scan();
            
            for (int i=1; i<=9; i++)
                for (int j=1; j<=9; j++)    
                    if (anna[i][j]) AddRow(i, j, anna[i][j]);
                    else
                        for (int k=1;k<=9;k++)
                            AddRow(i, j, k);
            
            int k = 0;
            for (int i=1; i<=9; i++)
                for (int j=1; j<=9; j++)
                    if (anna[i][j]) {
                        ++ k;
                        Remove(Col[head[i][j][anna[i][j]]]);
                        for (int u=R[head[i][j][anna[i][j]]]; u!=head[i][j][anna[i][j]]; u=R[u])
                            Remove(Col[u]);
                    }

            DFS(k+1);
            Print();
        }
};

int main() {
	DancingLinks dl;
	dl.solve();
}
