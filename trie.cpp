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
