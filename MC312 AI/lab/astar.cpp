#include <bits/stdc++.h>
using namespace std;
#define vvi vector<vector<int>>
#define endl "\n"
vvi finalState;
struct puzzle
{
    int loc0x;
    int loc0y;
    int gn;
    int hn;
    int fn;
    vvi currState;
    vector<pair<vvi, int>> movestillnow;
    bool compare(vvi &v1, vvi &v2)
    {
        if (v1 == v2)
            return true;
        else
            return false;
    }
};
set<vvi> visited;
struct compareFn
{
    bool operator()(puzzle &p1, puzzle &p2)
    {
        return p1.fn > p2.fn;
    }
};
void calcLoc0AndFn(puzzle &p)
{
    p.hn = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            if (p.currState[i][j] != finalState[i][j])
                p.hn++;
    }
    p.gn = 0;
    p.fn = p.hn + p.gn;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (p.currState[i][j] == 0)
            {
                p.loc0x = i;
                p.loc0y = j;
                return;
            }
        }
    }
}
void inputPuzzle(puzzle &p)
{
    cout << "Enter the intial puzzle state(use 0 for empty space):" << endl;
    for (int i = 0; i < 3; i++)
    {
        vector<int> temp(3);
        for (int j = 0; j < 3; j++)
            cin >> temp[j];
        p.currState.push_back(temp);
    }
    calcLoc0AndFn(p);
    p.movestillnow.push_back({p.currState, p.fn});
}
void displayPuzzle(puzzle &p)
{
    cout << "The puzzle state is: " << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            cout << p.currState[i][j] << " ";
        cout << endl;
    }
}
void displayMovesTillNow(puzzle &p){
    for (int k = 0; k < p.movestillnow.size(); ++k){
        if (k == 0)
            cout << "Intial State, f(n)= " << p.movestillnow[k].second << ":\n";
        else if (k == p.movestillnow.size() - 1)
            cout << "Final State, f(n)= " << p.movestillnow[k].second << ":\n";
        else 
            cout << "Move " << k << ", f(n)= " << p.movestillnow[k].second << ":\n";
        for (int i = 0; i < 3; i++){
            cout << setw(25);
            for (int j = 0; j < 3; j++)
                cout << (p.movestillnow[k].first)[i][j] << " ";
            cout << endl;
        }
        if (k != p.movestillnow.size() - 1){
            cout << setw(29) << " | \n";
            cout << setw(30) << " V \n";
        }
    }
}
vector<vvi> generateMoves(puzzle &p){
    vector<vvi> moves;
    vvi temp = p.currState;
    int cloc0x = p.loc0x, cloc0y = p.loc0y;
    if (cloc0x != 0){
        temp[cloc0x][cloc0y] = temp[cloc0x - 1][cloc0y];
        temp[cloc0x - 1][cloc0y] = 0;
        moves.push_back(temp);
        temp = p.currState;
    }
    if (cloc0x != 2){
        temp[cloc0x][cloc0y] = temp[cloc0x + 1][cloc0y];
        temp[cloc0x + 1][cloc0y] = 0;
        moves.push_back(temp);
        temp = p.currState;
    }
    if (cloc0y != 0){
        temp[cloc0x][cloc0y] = temp[cloc0x][cloc0y - 1];
        temp[cloc0x][cloc0y - 1] = 0;
        moves.push_back(temp);
        temp = p.currState;
    }
    if (cloc0y != 2){
        temp[cloc0x][cloc0y] = temp[cloc0x][cloc0y + 1];
        temp[cloc0x][cloc0y + 1] = 0;
        moves.push_back(temp);
        temp = p.currState;
    }
    return moves;
}

void solvePuzzle(struct puzzle &p){
    puzzle currentState = p;
    priority_queue<puzzle, vector<puzzle>, compareFn> pq;
    pq.push(currentState);
    while (!pq.empty()){
        currentState = pq.top();
        pq.pop();
        if (visited.find(currentState.currState) != visited.end())
            continue;
        if (currentState.currState == finalState){
            displayMovesTillNow(currentState);
            cout << "Total number of steps to reach the final state: " << currentState.movestillnow.size() - 1 << endl;
            return;
        }
        vector<vvi> moves = generateMoves(currentState);
        for (int i = 0; i < moves.size(); i++){
            puzzle temp = currentState;
            temp.currState = moves[i];
            calcLoc0AndFn(temp);
            temp.movestillnow.push_back({moves[i], temp.fn});
            pq.push(temp);
        }
        visited.insert(currentState.currState);
    }
}

int main(){
    cout << "\n\nEnter the final puzzle state(use 0 for empty space):" << endl;
    for (int i = 0; i < 3; i++){
        vector<int> temp;
        for (int j = 0; j < 3; j++){
            int x;
            cin >> x;
            temp.push_back(x);
        }
        finalState.push_back(temp);
    }
    cout << endl;
    struct puzzle initialState;
    inputPuzzle(initialState);
    cout << endl;
    solvePuzzle(initialState);
    cout << endl;
    return 0;
}