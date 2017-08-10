#include <bits/stdc++.h>
using namespace std;
 
#define MOD 1000000007
#define N 101
#define MVal 155
int dp[N][MVal][MVal];
int a[N];
 
int main(){
    int t,siz;
    cin>>t;
    while(t--){
        for(int i=0;i<N;++i){
            a[i] = 0;
            for(int x = 0; x<MVal; ++x)
                for(int y = 0; y<MVal; ++y)
                    dp[i][x][y] = 0;
        }
        cin>>siz;
        for(int i=1;i<=siz;++i)
            cin>>a[i];
        if(siz<=1){
            cout<<"1\n";
            continue;
        }
        int ans = 0, n = siz, Max = max(a[1],a[2]), k;
        dp[2][a[1]][a[2]] = 1;
        for(int i=2; i<=n; ++i){
            int curMax = Max;
            // cout<<i<<endl;
            for(int x = 0; x<=Max; ++x)
                for(int y = 0; y<=Max; ++y)
                    if(dp[i][x][y] > 0){
                        for(k=0; k<=min(x,y); ++k){
                            // printf("f[%d][%d][%d] += f[%d][%d][%d] = %d\n",i+1,y-k,a[i+1]+k,i,x,y,dp[i+1][y-k][a[i+1]+k]);
                            dp[i+1][y-k][a[i+1]+k] = (dp[i+1][y-k][a[i+1]+k] + dp[i][x][y])%MOD;
                            curMax = max(curMax, a[i+1]+k);
                            if(x>0 && y>0)
                                n = max(n, i+1);
                        }
                    }
            Max = curMax;
        }
        for(int x=0; x<4; x++)
            for(int y=0; y<4; y++)
                ans = (ans+dp[n][x][y])%MOD;
        cout<<ans<<endl;
    }
}
/*
5
5
11 11 11 11 11 
3
50 50 50 
10
20 20 20 20 20 20 20 20 20 20 
50
20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 
11
43 43 43 43 43 43 43 43 43 43 43 
 
*/
