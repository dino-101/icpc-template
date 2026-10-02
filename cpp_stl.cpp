
// ==================== SET ====================
// Sorted + unique elements
set<int> st;
st.insert(10);                       // insert x
st.erase(10);                        // remove x
auto it = st.find(10);               // iterator to x, or end()
int cnt = st.count(10);              // 0 or 1
auto it1 = st.lower_bound(10);       // first element >= x
auto it2 = st.upper_bound(10);       // first element > x
int mn = *st.begin();                // smallest element
int mx = *st.rbegin();               // largest element
st.size();                           // number of elements
st.empty();                          // true if empty
st.clear();                          // remove all elements
st.erase(it);                        // remove element at iterator
st.begin();                          // iterator to smallest
st.end();                            // iterator after largest
st.rbegin();                         // reverse iterator to largest
st.rend();                           // reverse iterator before smallest

// ==================== MULTISET ====================
// Sorted + duplicates allowed
multiset<int> mst;
mst.insert(10);                      // insert x
mst.count(10);                       // number of occurrences
auto it = mst.find(10);              // iterator to one occurrence
mst.erase(10);                       // remove ALL occurrences
mst.erase(it);                       // remove ONE occurrence
auto it1 = mst.lower_bound(10);      // first element >= x
auto it2 = mst.upper_bound(10);      // first element > x
int mn = *mst.begin();               // smallest element
int mx = *mst.rbegin();              // largest element
mst.size();                          // total elements including duplicates
mst.empty();                         // true if empty
mst.clear();                         // remove all elements
mst.begin();                         // iterator to smallest
mst.end();                           // iterator after largest
mst.rbegin();                        // reverse iterator to largest
mst.rend();                          // reverse iterator before smallest

// ==================== MAP ====================
// Sorted key-value pairs + unique keys
map<int,int> mp;
mp[10] = 100;                        // access/insert key
mp[10]++;                            // increment value
mp.insert({20,200});                 // insert {key,value}
mp.emplace(30,300);                  // insert {key,value}
mp.erase(20);                        // remove key
auto it = mp.find(10);               // iterator to key, or end()
int cnt = mp.count(10);              // 0 or 1
auto it1 = mp.lower_bound(10);       // first key >= x
auto it2 = mp.upper_bound(10);       // first key > x
auto first = mp.begin();             // smallest key
auto last = mp.rbegin();             // largest key
mp.size();                            // number of pairs
mp.empty();                           // true if empty
mp.clear();                           // remove all pairs
mp.erase(it);                         // remove pair at iterator
it->first;                             // key
it->second;                            // value
for(auto [key,val] : mp) {}          // traverse

// ==================== MULTIMAP ====================
// Sorted key-value pairs + duplicate keys allowed
multimap<int,int> mmp;
mmp.insert({1,100});                  // insert {key,value}
mmp.emplace(1,200);                   // insert {key,value}
auto it = mmp.find(1);                // iterator to first pair with key
int cnt = mmp.count(1);               // number of pairs with key
auto it1 = mmp.lower_bound(1);        // first key >= x
auto it2 = mmp.upper_bound(1);        // first key > x
auto [l,r] = mmp.equal_range(1);      // range of all pairs with key
mmp.erase(1);                          // remove ALL pairs with key
mmp.erase(it);                         // remove ONE pair
auto first = mmp.begin();             // smallest key
auto last = mmp.rbegin();              // largest key
mmp.size();                            // total pairs
mmp.empty();                           // true if empty
mmp.clear();                           // remove all pairs
for(auto [key,val] : mmp) {}          // traverse

====================================

// rotate func
// std::rotate(vec.begin(), vec.end() - 2, vec.end());
// This rotates the last 2 elements to the beginning.

// // to convert a string to upper case

// string s1 = "abcde"; 
  
// // using transform() function and ::toupper in STL 
// transform(s1.begin(), s1.end(), s1.begin(), ::toupper); 
// cout<<s1<<endl; 

// // to do it manually (i.e character by character)
// string s = "ankit";
// for(int i = 0; i < s.size(); i++){
//     s[i] = toupper(s[i]);
// }
// cout << s << endl;


// // String Funcs

// isalpha(ch) -->	Checks if the character is an alphabetic character (a-z or A-Z).
// isdigit(ch) -->	Checks if the character is a digit (0-9).
// isalnum(ch) -->	Checks if the character is alphanumeric (either a letter or a digit).
// islower(ch) -->	Checks if the character is a lowercase alphabetic character (a-z).
// isupper(ch) -->	Checks if the character is an uppercase alphabetic character (A-Z).
// isxdigit(ch) -->	Checks if the character is a hexadecimal digit (0-9, A-F, a-f).
// isspace(ch) -->	Checks if the character is a whitespace character (' ', '\t', '\n', '\r', '\f', or '\v').
// ispunct(ch) -->	Checks if the character is a punctuation character (neither alphanumeric nor a space).
// isprint(ch) -->	Checks if the character is printable (includes space but not control characters).
// isgraph(ch) -->	Checks if the character has a graphical representation (printable but excludes space).
// iscntrl(ch) -->	Checks if the character is a control character (non-printable, e.g., '\n', '\r').
// tolower(ch) -->	Converts an uppercase letter to a lowercase letter (if applicable).
// toupper(ch)	--> Converts a lowercase letter to an uppercase letter (if applicable).