#include<bits/stdc++.h>
using namespace std;

vector<int> build_Z_value(const string &s){
    vector<int> Z;
    Z.push_back(0);
    int L = 0, R = 0;       //閉開區間
    for(int i = 1; i < (int) s.size(); i++){
        Z.push_back(0);
        if(i < R){
            int i2 = i - L;
            if(i + Z[i2] < R)
                Z[i] = Z[i2];
            else
                Z[i] = R - i;
        }
        while(i + Z[i] < (int) s.size() && s[i + Z[i]] == s[Z[i]])
            Z[i]++;
        if(i + Z[i] > R){
            L = i;
            R = i + Z[i];
        }
    }
    return Z;
}

vector<int> match(const string &a, const string &b){
    vector<int> Z = build_Z_value(b + '#' + a);
    vector<int> match_point;
    for(int i = b.size() + 1; i < (int) Z.size(); i++){
        if(Z[i] == (int) b.size()){
            match_point.push_back(i - b.size() - 1);
        }
    }
    return match_point;
}


int main(){
    string a, b;
    while(cin >> a >> b){
        vector<int> match_point = match(a, b);
        for(int i = 0; i < (int) match_point.size(); i++){
            if(i > 0)
                cout << ' ';
            cout << match_point[i];
        }
        cout << endl;
    }
}
