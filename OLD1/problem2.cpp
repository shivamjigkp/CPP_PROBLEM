#include <bits/stdc++.h>
using namespace std;

int N, M;
vector<string> grid;

// Directions: up/down/left/right
int dr[4] = {-1,1,0,0}, dc[4] = {0,0,-1,1};

bool inBounds(int r,int c){ return r>=0 && r<N && c>=0 && c<M; }

// We'll represent each cable/rod overlap cell by an index in [0..k-1].
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    grid.resize(N);
    for(int i=0;i<N;i++){
        cin >> grid[i];
    }

    // First, identify the cable path endpoints on the boundary.
    vector<pair<int,int>> ends;
    for(int r=0;r<N;r++){
        for(int c=0;c<M;c++){
            if(grid[r][c]=='C'){
                if(r==0 || r==N-1 || c==0 || c==M-1){
                    ends.emplace_back(r,c);
                }
            }
        }
    }
    if(ends.size()!=2){
        // Unexpected, but handle gracefully.
        cout << "0\n";
        return 0;
    }
    auto start = ends[0];
    auto target = ends[1];

    // Next: trace the cable path from start to target.
    vector<vector<bool>> visited(N, vector<bool>(M,false));
    vector<pair<int,int>> cablePath;
    function<bool(int,int)> dfs = [&](int r,int c)->bool {
        visited[r][c] = true;
        cablePath.emplace_back(r,c);
        if(r==target.first && c==target.second) return true;
        for(int d=0;d<4;d++){
            int nr = r + dr[d], nc = c + dc[d];
            if(inBounds(nr,nc) && !visited[nr][nc] && grid[nr][nc]=='C'){
                if(dfs(nr,nc)) return true;
            }
        }
        cablePath.pop_back();
        return false;
    };
    dfs(start.first, start.second);

    // Identify overlap/intersection cells: where the cable crosses a rod below/above.
    // For simplicity: assume any cell that is either 'C' or 'R' but is on the cable path *and*
    // a rod runs through it (we check grid[r][c]=='R' OR adjacent rod extension) counts.
    vector<pair<int,int>> inters;
    map<pair<int,int>, int> interIndex;
    for(auto & p : cablePath){
        int r = p.first, c = p.second;
        if(grid[r][c]=='R'){
            int idx = inters.size();
            inters.emplace_back(r,c);
            interIndex[{r,c}] = idx;
        }
    }
    int K = inters.size();

    // BFS on switch‐states (bitmask of size K)
    const int MAXS = 1<<K;
    vector<int> dist(MAXS, INT_MAX);
    queue<int>q;
    dist[0]=0;
    q.push(0);

    auto checkGood = [&](int mask)->bool {
        // Given mask of switches (1 = cable above rod at that intersection, 0 = rod above cable),
        // determine if cable is “unwrapable” i.e., no entanglement.
        // For this problem’s constraints we treat “unwrapable” as: at *all* intersections,
        // the cable must be above the rod (i.e., switch state = 1).
        // Because if at any intersection rod is above cable, cable may be trapped.
        for(int i=0;i<K;i++){
            if(((mask>>i)&1)==0) return false;
        }
        return true;
    };

    int answer = INT_MAX;
    while(!q.empty()){
        int mask = q.front(); q.pop();
        int d = dist[mask];
        if(checkGood(mask)){
            answer = d;
            break;
        }
        // Try flipping each intersection
        for(int i=0;i<K;i++){
            int nmask = mask ^ (1<<i);
            if(dist[nmask] > d+1){
                dist[nmask] = d+1;
                q.push(nmask);
            }
        }
    }

    if(answer==INT_MAX) answer = K; // worst case
    cout << answer << "\n";
    return 0;
}
