#include <bits/stdc++.h>
using namespace std;
#define vvi vector<vector<int>>
#define endl "\n"

struct puzzle{
    int loc0x;
    int loc0y;
    vvi currState;
    vector<vvi> movesuntilnow;
    puzzle(){};
    puzzle(vvi &currState){
        this->currState = currState;
        getloc0();
    }
    void getloc0()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (!currState[i][j])
                {
                    loc0x = i;
                    loc0y = j;
                    return;
                }
            }
        }
    }
};

set<vvi> visited;
void inputPuzzle(struct puzzle &p){
    for (int i = 0; i < 3; i++){
        vector<int> temp;
        for (int j = 0; j < 3; j++){
            int x;
            cin >> x;
            temp.push_back(x);
        }
        p.currState.push_back(temp);
    }
    p.getloc0();
    visited.insert(p.currState);
}

void displayPuzzle(struct puzzle &p){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++)
            cout << p.currState[i][j] << " ";
        cout << endl;
    }
}

void displayMovesTillNow(struct puzzle &p){
    for (int k = 0; k < p.movesuntilnow.size(); ++k){
        cout << "\nMove " << k + 1 << endl;
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++)
                cout << p.movesuntilnow[k][i][j] << " ";
            cout << endl;
        }
    }
}

vector<vvi> generateMoves(struct puzzle &final){
    vector<vvi> moves;
    vvi temp = final.currState;
    int x = final.loc0x, y = final.loc0y;
    if (x != 0){
        temp[x][y] = temp[x - 1][y];
        temp[x - 1][y] = 0;
        moves.push_back(temp);
        temp = final.currState;
    }
    if (x != 2){
        temp[x][y] = temp[x + 1][y];
        temp[x + 1][y] = 0;
        moves.push_back(temp);
        temp = final.currState;
    }
    if (y != 0){
        temp[x][y] = temp[x][y - 1];
        temp[x][y - 1] = 0;
        moves.push_back(temp);
        temp = final.currState;
    }
    if (y != 2){
        temp[x][y] = temp[x][y + 1];
        temp[x][y + 1] = 0;
        moves.push_back(temp);
        temp = final.currState;
    }
    return moves;
}

void solvePuzzle(struct puzzle &initial, struct puzzle &final){
    queue<puzzle> q;
    q.push(initial);
    while (!q.empty()){
        puzzle curr = q.front();
        q.pop();
        vector<vvi> moves = generateMoves(curr);
        for (int i = 0; i < moves.size(); i++){
            if (moves[i] == final.currState){
                curr.movesuntilnow.push_back(moves[i]);
                displayMovesTillNow(curr);
                cout << "Total number of steps to reach the final state: 
                        "<<curr.movesuntilnow.size()<<endl;
                    return;
            }
            if (visited.find(moves[i]) == visited.end()){
                puzzle temp(moves[i]);
                temp.movesuntilnow = curr.movesuntilnow;
                temp.movesuntilnow.push_back(moves[i]);
                visited.insert(moves[i]);
                q.push(temp);
            }
        }
    }
}

int main(){
    cout << endl;
    puzzle initial;
    cout << "Enter the initial puzzle state (Denote blank space using 0):" << endl;
    inputPuzzle(initial);
    cout << endl;
    puzzle final;
    cout << "Enter the final puzzle state (Denote blank space using 0):" << endl;
    inputPuzzle(final);
    cout << endl;
    cout << "The initial puzzle state is: " << endl;
    displayPuzzle(initial);
    cout << endl;
    solvePuzzle(initial, final);
    return 0;
}