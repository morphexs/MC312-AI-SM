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

float prob(vector<bool> &v1, vector<bool> &v2, vector<vector<char>> simplified_function){
    int T = 10;
    int dE = heuristicFunc(v2, simplified_function) - heuristicFunc(v1, simplified_function);
    float res = 1 / (1 + exp(-dE * 1.0 / T));
    return res;
}

pair<int, vector<bool>> generateRand(vector<bool> v){
    int n = v.size(), randInd = rand() % n;
    v[randInd] = v[randInd] ^ 1;
    return {randInd, v};
}

void displayMoves(vector<vector<bool>> &asf){
    int sz = asf.size(), x = 0;
    for (auto vec : asf){
        int n = vec.size(), counter = 0;
        cout << "(";
        for (auto i : vec){
            counter++;
            cout << i;
            if (counter == n)
                cout << ") ";
            else
                cout << ",";
        }
        x++;
        if (x == sz)
            cout << endl;
        else
            cout << "-> ";
    }
}

bool solve(vector<bool> &v, vector<vector<bool>> &asf, vector<vector<char>> simplified_function, string function, float thresholdProb){
    asf.push_back(v);
    cout << "\n\nCurr State: ";
    for (auto i : v)
        cout << i << ' ';
    int currHueCount = heuristicFunc(v, simplified_function);
    if (currHueCount == 6){
        cout << "\n\nTotal number of steps to reach the final values: " << asf.size() - 1 << endl;
        cout << "\nSteps: ";
        displayMoves(asf);
        cout << "\nFinal values of the variables so that all clauses of the function are true are: "<<endl;
        for (int i = 0; i < v.size(); i++) 
            cout << char(i + 'a') << " = " << asf[asf.size() - 1][i] << endl;
        return true;
    }

    set<int> visited;
    while (true){
        pair<int, vector<bool>> resPair = generateRand(v);
        vector<bool> nextRandomState = resPair.second;
        cout << "\nNext Generated Random State :";
        for (auto i : nextRandomState)
            cout << i << ' ';
        cout << "\nProbability = " << prob(v, nextRandomState, simplified_function);
        int indexChanged = resPair.first, lastSize = visited.size();
        visited.insert(indexChanged);
        if (visited.size() != lastSize && prob(v, nextRandomState, simplified_function) > thresholdProb){
            cout << "\nThe found probability is greater than the threshold probability, hence we select this and move on to a new state.";
            return solve(nextRandomState, asf, simplified_function, function, thresholdProb);
        }
        if (visited.size() == v.size())
            break;
    }
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
    float thresholdProb;
    cout << "Enter the threshold probability: ";
    cin >> thresholdProb;
    vector<vector<bool>> asf;
    if (!solve(v, asf, simplified_function, function, thresholdProb))
        cout << "\n\nProgram Terminated! As there are no further states available with probability greater than the threshold probability, hence we will be unable to reach the goal state.\n ";
}