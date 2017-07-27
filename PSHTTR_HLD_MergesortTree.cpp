#include <bits/stdc++.h>
using namespace std;
 
#define N 100001
#define LN 16
 
vector <int> adj[N], costs[N];
vector<int > chainArray[N];
int root, mx, chainNo, chainInd[N], chainHead[N], posInChain[N];
int depth[N], pa[LN][N], subsize[N];
 
#define gc getchar_unlocked
void scanint(int &x)
{
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
 
void Merge(vector<int> &a, vector<int> &b, vector<int> &o){
    int i = 0,j = 0, n1 = a.size(), n2 = b.size();
    while (i < n1 && j < n2)
        if (a[i] <= b[j])   o.push_back(a[i++]);
        else    o.push_back(b[j++]);
    while (i < n1)
        o.push_back(a[i++]);
    while (j < n2)
        o.push_back(b[j++]);
}
 
class MST{
public:
    vector<int> * tree;
    vector<int> * xtree;
    int i;
    int n;
    int s;
    ~MST(){
        if(s>0){
            delete[] tree;
            delete[] xtree;
        }
    }
    void setup(int I);
    void build_tree(int cur , int l , int r );
    int xquery(int x, int y, int k);
    int _xquery( int cur, int l, int r, int x, int y, int k);
    void printTree();
};
 
void MST::setup(int I){
    i = I;
    n = chainArray[i].size();
    s = 1<<((int)ceil(log2(n)));
    if(n<=1) return;
    tree = new vector<int>[s];
    xtree = new vector<int>[s];
    build_tree(0,0,n-1);
}
 
void MST::build_tree(int cur , int l , int r ){
    int mid = (l+r)/2;
    vector<int>a,b;
    bool lsingle = 0, rsingle = 0;
    
    if(l == mid){
        a.push_back(chainArray[i][l]);
        lsingle = 1;
    }
    else build_tree(2*cur+1 , l , mid ); // Build left tree
 
    if(mid+1 == r){
        b.push_back(chainArray[i][r]);
        rsingle = 1;
    }
    else build_tree(2*cur+2 , mid+1 , r ); // Build right tree
    
    if(lsingle)
        Merge(a, b, tree[cur]);
    else if(rsingle)
        Merge(tree[2*cur+1], b, tree[cur]);
    else
        Merge( tree[2*cur+1], tree[2*cur+2], tree[cur]);
    xtree[cur].push_back(tree[cur][0]);
    for(int i=1;i<tree[cur].size();++i)
        xtree[cur].push_back(xtree[cur][i-1]^tree[cur][i]);
}
 
int MST::xquery(int x, int y, int k){
    return _xquery(0,0,n-1,x,y,k);
}
 
int MST::_xquery( int cur, int l, int r, int x, int y, int k){
    if( r < x || l > y )
           return 0;
    if( x<=l && r<=y ){
        if(l==r)
            if(chainArray[i][l]<=k){
                return chainArray[i][l];
            }
            else{
                return 0;   
            }
        int i = upper_bound(tree[cur].begin(),tree[cur].end(),k)-tree[cur].begin();
        if(i==0)return 0;
        return xtree[cur][i-1];
    }
    int mid=(r+l)/2;
    return _xquery(2*cur+1,l,mid,x,y,k)^_xquery(2*cur+2,mid+1,r,x,y,k);
}
 
void MST::printTree(){
    if(n<=1) return;
    cout<<"tree:\n";
    for(int i=0;i<s;++i){
        cout<<i<<" - ";
        for(int j=0;j<tree[i].size();++j)
            cout<<tree[i][j]<<' ';
        cout<<endl;
    }
    cout<<"xtree:\n";
    for(int i=0;i<s;++i){
        cout<<i<<" - ";
        for(int j=0;j<xtree[i].size();++j)
            cout<<xtree[i][j]<<' ';
        cout<<endl;
    }
    cout<<"---------------\n";
}
 
int query_up2(int u, int v, int k, MST * T) {
    // cout<<"u:"<<u<<" v:"<<v<<endl;
    if(u == v) return 0;
    int uchain, vchain = chainInd[v], ans = 0;
    while(1){
        uchain = chainInd[u];
        // printf("chain:%d @pos: %d\n",uchain,posInChain[u]);
        if(uchain == vchain) {
            if(u==v) return ans;
            ans = ans^(T[uchain].xquery(posInChain[v]+1,posInChain[u],k));
            return ans;
        }
        ans ^= (T[uchain].xquery(0,posInChain[u],k));
        u = pa[0][chainHead[uchain]]; //Then move to chainhead's parent
    }
    return ans;
}
 
int LCA(int u, int v) {
    if(depth[u] < depth[v]) swap(u,v);
    int diff = depth[u] - depth[v];
    for(int i=0; i<LN; i++) if( (diff>>i)&1 ) u = pa[i][u];
    if(u == v) {return u;}
    for(int i=LN-1; i>=0; i--) if(pa[i][u] != pa[i][v]) {
        u = pa[i][u];
        v = pa[i][v];
    }
    return pa[0][u];
}
 
void query(int u, int v, int k, MST * T) {
    if(u==v){
        printf("%d\n", 0);
        return;
    }
    int lca = LCA(u, v);
    // cout<<"lca:"<<lca<<endl;
    int ans1 = query_up2(u, lca, k, T);
    int ans2 = query_up2(v, lca, k, T);
    printf("%d\n", ans1^ans2);
}
 
int ind;
void HLD(int curNode, int cost, int prev) {
    // cout<<"HLD:"<<curNode+1<<' '<<cost<<' ';
    if(chainHead[chainNo] == -1){
        chainHead[chainNo] = curNode; // Assign chain head
        ind = 0;
    }
    chainArray[chainNo].push_back(cost);
    chainInd[curNode] = chainNo;
    posInChain[curNode] = ind;
    ++ind;
 
    int sc = -1, ncost;
    // Loop to find special child
    for(int i=0; i<adj[curNode].size(); i++) 
        if(adj[curNode][i] != prev) {
            if(sc == -1 || subsize[sc] < subsize[adj[curNode][i]]) {
                sc = adj[curNode][i];
                ncost = costs[curNode][i];
            }
        }
 
    if(sc != -1)
        HLD(sc, ncost, curNode);
 
    for(int i=0; i<adj[curNode].size(); i++) 
        if(adj[curNode][i] != prev) {
            if(sc != adj[curNode][i]) {
            // New chains at each normal node
                chainNo++;
                HLD(adj[curNode][i], costs[curNode][i], curNode);
            }
        }
}
 
void dfs(int cur, int prev, int _depth=0){
    pa[0][cur] = prev;
    depth[cur] = _depth;
    subsize[cur] = 1;
    for(int i=0; i<adj[cur].size(); i++)
        if(adj[cur][i] != prev){
            dfs(adj[cur][i], cur, _depth+1);
            subsize[cur] += subsize[adj[cur][i]];
        }
}
 
int main(){
    int t;
    scanf("%d", &t);
    // scanint(t);
    // cin>>t;
    while(t--){
        int n;
        scanf("%d", &n);
        // scanint(n);
        // cin>>n;
        // Cleaning step, new test case
        for(int i=0; i<N; i++) {
            adj[i].clear();
            costs[i].clear();
            chainArray[i].clear();
            for(int j=0; j<LN; j++) pa[j][i] = -1;
            chainHead[i] = -1;   
        }
        int u,v,c;
        scanf("%d %d %d", &u, &v, &c);
        // scanint(u);
        // scanint(v);
        // scanint(c);
        // cin>>u>>v>>c;
        root = u;
        adj[u].push_back(v);
        costs[u].push_back(c);
        adj[v].push_back(u);
        costs[v].push_back(c);
        for(int i=2; i<n; i++) {
            scanf("%d %d %d", &u, &v, &c);
            // scanint(u);
            // scanint(v);
            // scanint(c);
            // cin>>u>>v>>c;
            adj[u].push_back(v);
            costs[u].push_back(c);
            adj[v].push_back(u);
            costs[v].push_back(c);
        }
        // cout<<"root:"<<root<<endl;
        chainNo = 0;
        dfs(root, -1); // set up subsize, depth and parent for each node
        HLD(root, 0, -1); // decomposed the tree and create chains
 
        // Below Dynamic programming code is for LCA.
        for(int i=1; i<LN; i++)
            for(int j=0; j<N; j++)
                if(pa[i-1][j] != -1)
                    pa[i][j] = pa[i-1][pa[i-1][j]];
        
        MST * T = new MST[chainNo+1];
        for(int i=0;i<=chainNo;++i){
            T[i].setup(i);
            // T[i].printTree();
        }
        int q;
        scanf("%d", &q);
        // scanint(q);
        // cin>>q;
        int a, b, k;
        while(q--){
            scanf("%d %d %d", &a, &b, &k);
            // scanint(a);
            // scanint(b);
            // scanint(k);
            // cin>>a>>b>>k;
            query(a, b, k, T);
        }
        // delete[] T;
    }
} 
