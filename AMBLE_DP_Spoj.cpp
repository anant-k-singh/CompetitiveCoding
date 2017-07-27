#include <bits/stdc++.h>
using namespace std;

struct point{
    int x;
    int y;
};

double dist(point p1, point p2){
    long long dx = p2.x-p1.x;
    long long dy = p2.y-p1.y;
    return sqrt(dx*dx + dy*dy);
}

double mindist(point* p, int n){
    double p1_value = 0.0, p2_value = 0.0;
    int p1_last = 0, p2_last = 0;
    for(int i=1;i<n-1;++i){
        double d1 = dist(p[i],p[p1_last]);
        double d2 = dist(p[i],p[p2_last]);
        if(d1 + p1_value < d2 + p2_value){
            p1_value += d1;
            p1_last = i; 
        }
        else{
            p2_value += d2;
            p2_last = i; 
        }
    }
    double ans = p1_value + p2_value;

    //visit destination on both paths
    ans += dist(p[n-1],p[p1_last]);
    ans += dist(p[n-1],p[p2_last]);
    return ans;
}

bool comp(point l, point r){
    return l.x<r.x;
}

int main(){
    int n,x;
    cin>>n;
    point p[n];
    for(int i=0;i<n;++i)
        cin>>p[i].x>>p[i].y;
    sort(p,p+n,comp);
    if(n==1){
        cout<<"0.00"<<endl;
        return 0;
    }
    cout<<std::fixed<<setprecision(2)<<mindist(p,n)<<endl;
    return 0;
}
