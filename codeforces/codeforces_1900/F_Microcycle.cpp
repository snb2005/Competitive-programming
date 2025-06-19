#include<bits/stdc++.h>

using namespace std;

#define int long long
#define ll long long

const int mod=1e9+7;

void make(int v,vector<int>& parent,vector<int>& size){
    parent[v]=v;
    size[v]=1;
}

int find(int v,vector<int>& parent){
    if(parent[v]==v) return v;
    return parent[v]=find(parent[v],parent);
}

void unite(int a,int b,vector<int>& parent,vector<int>& size){
    a=find(a,parent);
    b=find(b,parent);
    if(size[a]>=size[b]){
        parent[b]=a;
        size[a]+=size[b];
    }
    else{
        parent[a]=b;
        size[b]+=size[a];
    }
}

void dfs(int u,int destination,int parent,vector<int>& pr,vector<int>& vis,vector<vector<int>>& adj){
    vis[u]=1;
    pr[u]=parent;
    for(auto it:adj[u]){
        if(!vis[it]){
            dfs(it,destination,u,pr,vis,adj);
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin>>t;
    while(t--){
        int n,m;
        cin>>n>>m;
        vector<vector<int>> adj(n+1);
        vector<int> parent(n+1),size(n+1);
        vector<pair<int,pair<int,int>>> edge;
        for(int i=0;i<m;i++){
            int x,y,z;
            cin>>x>>y>>z;
            edge.push_back({z,{x,y}});
        }
        for(int i=1;i<=n;i++){
            make(i,parent,size);
        }
        sort(edge.begin(), edge.end(),greater<pair<int,pair<int,int>>>());
        int source=-1,destination=-1;
        int mn=LLONG_MAX;
        for(int i=0;i<m;i++){
            int x=edge[i].second.first,y=edge[i].second.second,z=edge[i].first;
            if(find(x,parent)!=find(y,parent)){
                unite(x,y,parent,size);
                adj[x].push_back(y);
                adj[y].push_back(x);
            }
            else{
                source=x;
                destination=y;
                mn=min(mn,z);
            }
        }
        vector<int> path;
        vector<int> pr(n+1);
        vector<int> vis(n+1);
        int flag=0;
        dfs(source,destination,-1,pr,vis,adj);
        int curr=destination;
        while(curr!=source){
            path.push_back(curr);
            curr=pr[curr];
        }
        path.push_back(source);
        cout<<mn<<" "<<path.size()<<endl;
        for(auto it:path){
            cout<<it<<" ";
        }
        cout<<endl;
    }
}
