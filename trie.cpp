struct TrieNode {
    array<int,26> nxt;
    bool end = false;
    TrieNode(){ nxt.fill(-1); }
};
struct Trie {
    vector<TrieNode> t{TrieNode()};
    void insert(const string &s){
        int cur = 0;
        for(char ch : s){
            int c = ch - 'a';
            if(t[cur].nxt[c] == -1){
                t[cur].nxt[c] = t.size();
                t.emplace_back();
            }
            cur = t[cur].nxt[c];
        }
        t[cur].end = true;
    }
    bool contains(const string &s){
        int cur = 0;
        for(char ch : s){
            int c = ch - 'a';
            if(t[cur].nxt[c] == -1) return false;
            cur = t[cur].nxt[c];
        }
        return t[cur].end;
    }
    bool startsWith(const string &pref){
        int cur = 0;
        for(char ch : pref){
            int c = ch - 'a';
            if(t[cur].nxt[c] == -1) return false;
            cur = t[cur].nxt[c];
        }
        return true;
    }
};
// usage:
// Trie tr; tr.insert("hello"); tr.contains("hell") -> false;
tr.startsWith("hell")



// number xor

struct Node{
    Node *arr[2];
    Node(){
        arr[0] = nullptr;
        arr[1] = nullptr;
    }
    bool find(int val){
        return arr[val] != nullptr;
    }
    void put(int val, Node *new_node){
        arr[val] = new_node;
    }
    Node *pnt(int val){
        return arr[val];
    }
};

class Trie{
private:
    Node *root;
public:
    Trie(){
        root = new Node();
    }
    void insert(int num){
        Node *node = root;
        for(int i = 31; i >= 0; i--){
            int bit = (num >> i) & 1;
            if(!node->find(bit)){
                node->put(bit, new Node());
            }
            node = node->pnt(bit);
        }
    }
    int dfs(int num){
        Node *node = root;
        int temp = 0;
        for(int i = 31; i >= 0; i--){
            int bit = (num >> i) & 1;
            if(node->find(1 - bit)){
                temp |= (1 << i);
                node = node->pnt(1 - bit);
            }
            else node = node->pnt(bit);
        }
        return temp;
    }
};


class Solution {
public:
    int findMaximumXOR(vector<int>& arr) {
        Trie ank;
        int n = (int)arr.size();
        for(auto it : arr){
            ank.insert(it);
        }
        int ans = 0;
        for(auto it : arr){
            ans = max(ans, ank.dfs(it));
        }
        return ans;
    }
};