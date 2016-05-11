class Trie{
    public:
        class Node{
            public:
                int cnt, depth;
                vector<int> ID;
                Node *child[2];
                Node(int _depth = 0){
                    cnt = 0;
                    depth = _depth;
                    memset(child, 0, sizeof(child));
                }
        };

        Node *root, *pool;
        int pp;

        Trie(){
            pool = new Node[1048576];
            pp = 0;
            root = &pool[pp++];
        }

        ~Trie(){
            delete pool;
        }

        void insert(const string &s, int id, Node *nd = NULL , int pos = 0){
            if(nd == NULL)
                nd = root;
            if(pos >= (int) s.size()){
                nd->cnt++;
                nd->ID.push_back(id);
                return;
            }
            int c = s[pos];
            if(nd->child[c] == NULL){
                pool[pp] = Node(nd->depth + 1);
                nd->child[c] = &pool[pp++];
            }
            insert(s, id, nd->child[c], pos+1);
        }

        int find(const string &s, Node *nd = NULL, int pos = 0) {
            if (nd == NULL)
                nd = root;
            if (pos >= (int) s.size()) {
                return nd->ID.front();
            }
            int c = s[pos];
            if(nd->child[c] == NULL) {
                return -1;
            } else {
                return find(s, nd->child[c], pos + 1);
            }
        }
};
