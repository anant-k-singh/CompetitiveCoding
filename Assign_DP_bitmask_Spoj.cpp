#include <bits/stdc++.h>
using namespace std;

long long dp[(1<<20)+1];

int main(){
    ios::sync_with_stdio(0);
    int t,n,x,y,z,i,j,k,idx;
    cin>>t;
    while(t--){
        cin>>n;
        int a[n][n];
        for(i=0;i<n;++i)
            for(j=0;j<n;++j)
                cin>>a[i][j];
        dp[0]=1;
        //mask is i
        for(i=1; i<(1<<n); ++i){
            dp[i]=0;
            //count number of 1's in i for index of student
            idx = 0;
            for(j=0;j<n;++j)
                idx += (i>>j) & 1;

            for(j=0;j<n;++j)
                // if the idx student likes jth topic and jth topic is also available
                if(a[idx-1][j] && ((i>>j) & 1))
                    // remove that jth topic from available
                    dp[i] += dp[i & ~(1<<j)];
        }
        cout<< dp[(1<<n)-1] <<endl;
    }
    return 0;
}
