#include <bits/stdc++.h>
using namespace std;
 
int n;
int ACMAP[20];
int WRMAP[20];
int Dp[1<<17 +1];
int solve(int mask, int index)
{
    // cout<<"F( "<<mask<<','<<index<<" )\n";
    if(index == n)
        return 0;
    else if(Dp[mask]!=-1)
        return Dp[mask];
 
    else
    {
        // cout<<"new\n";
        int ans=10000000;
        for(int i=0; i<n; i++)
            if(!(mask & (1<<i))){
                // cout<<i<<','<<index<<" - "<<abs(i-index)+abs(WRMAP[i]-ACMAP[index])<<endl;
                ans=min(ans,
                        abs(i-index)
                        +abs(ACMAP[index]-WRMAP[i])
                        +solve(  mask | (1<<i) , index +1 ) );
            }
        bitset<5> b(mask);
        //cout<<"Dp["<<b<<"] = "<<ans<<endl;//<<"---Done for "<<index<<endl;
        return Dp[mask]=ans;
    }
 
 
}
int main(){
    while(scanf("%d",&n))
    {
        if(n==0)
            break;
        memset(Dp,-1,sizeof (int)*(1<<n));
        for(int i=0; i<n; i++)
            scanf("%d",&WRMAP[i]);
 
        for(int i=0; i<n; i++)
            scanf("%d",&ACMAP[i]);
 
        printf("%d\n",solve(0,0));
 
    }
    return 0;
}
/*
5
3 1 3 5 1
1 3 5 1 3
0
*/
