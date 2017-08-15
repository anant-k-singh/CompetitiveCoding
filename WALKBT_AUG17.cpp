#include <bits/stdc++.h>
using namespace std;

long long ans;

struct node{
    node * left;
    node * right;
};

void BinAdd(bool * X, int n, int c){
    if(X[n-c] == 1)
        for(int i=n-c; i>0; --i){
            if(X[i] == 1)
                X[i] = 0;
            else{
                X[i] = 1;
                break;
            }
        }
    else
        X[n-c] = 1;
    X[0] = 0;
}

void Insert(node * &root, bool * X, int n){
    node * temp = root;
    for(int i=1;i<=n;++i){
        // left
        if(X[i] == 0){
            if(temp->left != NULL)
                temp = temp->left;
            else{
                temp->left = new node;
                temp = temp->left;
                temp->left = NULL;
                temp->right = NULL;
                ++ans;
            }
        }
        // right
        else{
            if(temp->right != NULL)
                temp = temp->right;
            else{
                temp->right = new node;
                temp = temp->right;
                temp->left = NULL;
                temp->right = NULL;
                ++ans;
            }
        }
    }
}

int main(){
    int t,c,N,Q;
    cin>>t;
    while(t--){
        cin>>N>>Q;
        bool X[N+1] = {0};
        node * root = new node;
        root->left = NULL;
        root->right = NULL;
        ans = 1;
        char type;
        while(Q--){
            cin>>type;
            if(type == '?')
                cout<<ans<<endl;
            else{
                cin>>c;
                BinAdd(X,N,c);
                Insert(root,X,N);
            }
        }
    }
}
