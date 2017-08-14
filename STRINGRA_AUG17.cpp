// https://www.codechef.com/AUG17/problems/STRINGRA

#include <bits/stdc++.h>
using namespace std;
 
int main(){
    int t,a,b,n,m;
    cin>>t;
    while(t--){
        cin>>n>>m;
        vector<int> adj[n+1];
        while(m--){
            cin>>a>>b;
            if(a<b)
                adj[a].push_back(b);
        }
        int s[n+1]={-1,0}, MaxE = adj[0].size();
        int firstoccur[MaxE+1];
        for(int i=1;i<=MaxE;++i)
            firstoccur[i] = INT_MAX;
        // for(int i=0 ; i<=n; ++i)
            sort(adj[0].begin(),adj[0].end());
        
        for(int i=0; i < adj[0].size(); ++i){
            s[adj[0][i]] = i+1;
            firstoccur[i+1] = adj[0][i];
        }
        bool available[MaxE+1];
        memset(available, 1 , MaxE+1);

        // Main algo starts
        for(int i=1;i<n;++i){
            int emptyi = -1, toIndex;
            if(adj[i].size() > MaxE || adj[i].size() == 0)goto g;
            for(int j=0;j<adj[i].size();++j){
                toIndex = adj[i][j];
                if(s[toIndex] == 0)
                    if(emptyi == -1)
                        emptyi = toIndex;
                    else
                        goto g;
            }
            if(emptyi != -1){
                for(int k=1;k<=MaxE;++k){
                    if(available[k] && firstoccur[k]<=i){
                        s[emptyi] = k;
                        firstoccur[k] = emptyi;
                        break;
                    }
                }
            }
            memset(available, 0 , MaxE+1);
            for(int j=0;j<adj[i].size();++j)
                available[s[adj[i][j]]]=1;
        }
        // recheck
        for(int i=0;i<=n;++i){
            int count = 0;
            for(int j = 1; j<=MaxE;++j)
                if(firstoccur[j] > i)
                    ++count;
            if(count != adj[i].size())
                goto g;
        }
        for(int i=1;i<=n;++i)cout<<s[i]<<' ';cout<<endl;
        continue;
        g:;
        cout<<-1<<endl;
    }
}
