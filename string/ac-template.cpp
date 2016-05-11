#include<bits/stdc++.h>
using namespace std;

class ACautomaton{
    public:
        class Node{
            public:
                int cnt, depth;
                Node *child[26], *fail;
                Node(int _depth = 0){
                    cnt = 0;
                    depth = _depth;
                    fail = NULL;
                    memset(child, 0, sizeof(child));
                }
        };

        Node *root, *pool;
        int pp;

        ACautomaton(){
            pool = new Node[1048576];
            pp = 0;
            root = &pool[pp++];
        }

        ~ACautomaton(){
            delete pool;
        }

        void insert(const string &s, Node *nd = NULL , int pos = 0){
            if(nd == NULL)
                nd = root;
            if(pos >= (int) s.size()){
                nd->cnt++;
                return;
            }
            int c = s[pos] - 'a';
            if(nd->child[c] == NULL){
                pool[pp] = Node(nd->depth + 1);
                nd->child[c] = &pool[pp++];
            }
            insert(s, nd->child[c], pos+1);
        }

        void build_fail(){
            queue<Node*> q;
            q.push(root);
            while(!q.empty()){
                Node *nd = q.front();
                q.pop();
                for(int i = 0; i < 26; i++){
                    if(nd->child[i]){
                        Node *pt = nd->fail;
                        while(pt && !pt->child[i])
                            pt = pt->fail;
                        nd->child[i]->fail = pt ? pt->child[i] : root;
                        nd->child[i]->cnt += nd->child[i]->fail->cnt;
                        q.push(nd->child[i]);
                    }
                }
            }
        }

        int match(const string &s){
            Node *nd = root;
            int r = 0;
            for(int i = 0; i < (int) s.size(); i++){
                int c = s[i] - 'a';
                while(nd && !nd->child[c])
                    nd = nd->fail;
                if(nd){
                    r += nd->child[c]->cnt;
                    nd = nd->child[c];
                }
                else
                    nd = root;
            }
            return r;
        }
};



int main(){
    string a, b[160];
    int n;
    while(cin >> n){
        ACautomaton ac;
        for(int i = 0; i < n; i++){
            cin >> b[i];
            ac.insert(b[i]);
        }
        ac.build_fail();
        cout << ac.match(a) << endl;
    }
}
