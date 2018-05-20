
class SCC{
public:
    vector<int> adj[Mn];
    vector<int> rev[Mn];
    int scc[Mn];
    int vis[Mn];
    int ord[Mn];
    int vn;
    int clk = 0;
    int ccn = 0;
    void init(int n){
        vn = n;
        for(int i=0;i<n;i++){
            adj[i].clear(); rev[i].clear();
        }
    }
    void addEdge(int u, int v){
        adj[u].push_back(v);
        rev[v].push_back(u);
    }
    void dfs1(int i){
        vis[i] = 1;
        for(auto &x : rev[i]){
            if(vis[x]) continue;
            dfs1(x);
        }
        ord[clk++] = i;
    }
    void dfs2(int i){
        vis[i] = 1;
        scc[i] = ccn;
        for(auto &x :adj[i]){
            if(!vis[x]) dfs2(x);
        }
    }
    void exe(){
        memset(vis,0,sizeof(vis));
        clk = 0;
        for(int i=0;i<vn;i++){
            if(!vis[i]) dfs1(i);
        }
        ccn = 0;
        memset(vis,0,sizeof(vis));
        for(int i=vn-1;i>=0;i--){
            if(!vis[ord[i]]) {
                dfs2(ord[i]);
                ccn++;
            }
        }
    }
};