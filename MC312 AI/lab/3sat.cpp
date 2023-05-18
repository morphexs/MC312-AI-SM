#include <bits/stdc++.h>
using namespace std;

vector<vector<char>> simplify(string function){
    vector<vector<char>> result;
    int i = 0, n = function.size();
    vector<char> temp;
    while (i < n){
        if (function[i] == ')'){
            result.push_back(temp);
            temp.clear();
            i++;
        }
        else if (function[i] == '^' || function[i] == '(' || function[i] == 'V'){
            i++;
        }
        else{
            if (function[i] == '\''){
                temp[temp.size() - 1] = char(toupper(temp[temp.size() - 1]));
            }
            else
                temp.push_back(function[i]);
            i++;
        }
    }
    return result;
}

int heuristicFunc(vector<bool> &v, vector<vector<char>> simplified_function){
    int count = 0;
    for (auto vec : simplified_function){
        bool flag = false;
        for (auto ch : vec){
            if (ch >= 'A' && ch <= 'Z'){
                if (v[ch - 'A'] == false){
                    flag = true;
                    break;
                }
            }
            else if (v[ch - 'a'] == true){
                flag = true;
                break;
            }
        }
        if (flag)
            count++;
    }
    return count;
}

vector<vector<bool>> moveGen1(vector<bool> &v, int prevHeuCount, vector<vector<char>> simplified_function){
    vector<vector<bool>> moves;
    for (int i = 0; i < v.size(); i++){
        v[i] = !v[i];
        if (heuristicFunc(v, simplified_function) > prevHeuCount)
            moves.push_back(v);
        v[i] = v[i];
    }
    return moves;
}

vector<vector<bool>> moveGen2(vector<bool> &v, int prevHeuCount, vector<vector<char>> simplified_function){
    vector<vector<bool>> moves;
    for (int i = 0; i < v.size(); i++){
        v[i] = !v[i];
        for (int j = i + 1; j < v.size(); j++){
            v[j] = !v[j];
            if (heuristicFunc(v, simplified_function) > prevHeuCount)
                moves.push_back(v);
            v[j] = !v[j];
        }
        v[i] = v[i];
    }
    return moves;
}

void displayMoves(vector<vector<bool>> &asf){
    int sz = asf.size(), x = 0;
    for (auto vec : asf){
        for (auto i : vec)
            cout << i << ' ';
        x++;
        if (x == sz)
            cout << endl;
        else
            cout << "-> ";
    }
}

bool solve(vector<bool> &v, vector<vector<bool>> &asf, vector<vector<char>> simplified_function, string function){
    asf.push_back(v);
    int currHueCount = heuristicFunc(v, simplified_function);
    if (currHueCount == simplified_function.size()){
        cout << "\n\nTotal number of steps to reach the final values: " << asf.size() << endl;
        cout << "\nSteps: ";
        displayMoves(asf);
        cout << "\nFinal values of the variables so that all clauses of the function are true are:"<<endl;
            for (int i = 0; i < v.size(); i++) cout
             << char(i + 'a') << " = " << asf[asf.size() - 1][i] << endl;
        return true;
    }
    vector<vector<bool>> moves;
    moves = moveGen1(v, currHueCount, simplified_function);
    for (int i = 0; i < moves.size(); i++)
        if (solve(moves[i], asf, simplified_function, function) == true)
            return true;
    moves = moveGen2(v, currHueCount, simplified_function);
    for (int i = 0; i < moves.size(); i++)
        if (solve(moves[i], asf, simplified_function, function) == true)
            return true;
    asf.pop_back();
    return false;
}

int main(){
    string function;
    cout << "Enter the function to be solved(without any spaces): ";
    getline(cin, function, '\n');
    int sz = function.size();
    unordered_set<char> variables;
    for (int i = 0; i < sz; i++){
        if ((function[i] >= 'a') && (function[i] <= 'z'))
            variables.insert(function[i]);
    }

    int n = variables.size();
    vector<bool> v(n, true);
    vector<vector<char>> simplified_function = simplify(function);
    cout << "\n\nPlease enter the Inital values of the variables:- \n";
    for (int i = 0; i < n; i++){
        cout << char(i + 97) << ": ";
        int t;
        cin >> t;
        if (t == 1)
            v[i] = true;
        else
            v[i] = false;
    }
    vector<vector<bool>> asf;
    solve(v, asf, simplified_function, function);
}