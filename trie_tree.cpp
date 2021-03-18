// Trie Tree
#include <bits/stdc++.h>
using namespace std;
const int ALPHABET_SIZE = 26;

// trie node
struct TrieNode
{
    struct TrieNode* children[ALPHABET_SIZE];
    // isEndOfWord is true if the node represents end of a word
    bool isEndOfWord;
};

// returns new trie node (initialized to NULLs)
struct TrieNode* getNode(void)
{
    struct TrieNode* pNode = new TrieNode;
    pNode->isEndOfWord = false;
    for(int i=0; i<ALPHABET_SIZE; i++){
        pNode->children[i] = NULL;
    }
    return pNode;
};

// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(struct TrieNode* root, string key)
{
    struct TrieNode* pCrawl = root;
    for(int i=0; i<key.size(); i++){
        int index = key[i] - 'a';
        if(!pCrawl->children[index]){
            pCrawl->children[index] = getNode();
        }
        pCrawl = pCrawl->children[index];
    }
    // mark last node as leaf
    pCrawl->isEndOfWord = true;
}

// returns true if key present in trie, else false
bool search(struct TrieNode* root, string key)
{
    struct TrieNode* pCrawl = root;
    for(int i=0; i<key.size(); i++){
        int index = key[i] - 'a';
        if(!pCrawl->children[index]){
            return false;
        }
        pCrawl = pCrawl->children[index];
    }
    return (pCrawl != NULL && pCrawl->isEndOfWord);
}

// returns true if root has no children, else false
bool isEmpty(TrieNode* root)
{
    for(int i=0; i<ALPHABET_SIZE; i++){
        if(root->children[i]){
            return false;
        }
    }
    return true;
}

// recursive function to delete a key from given trie
TrieNode* remove(TrieNode* root, string key, int depth = 0)
{
    // if tree is empty
    if(!root){
        return NULL;
    }
    // if last character of key is being processed
    if(depth == key.size()){
        // this node is no more end of word after removal of given key
        if(root->isEndOfWord){
            root->isEndOfWord = false;
        }
        // if key is not prefix of any other word
        if(isEmpty(root)){
            delete(root);
            root = NULL;
        }
        return root;
    }

    // if not last character, recur for the child obtained using ASCII value
    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);

    // if root does not have any child (its only child got deleted) and it is not end of another word.
    if(isEmpty(root) && root->isEndOfWord == false){
        delete(root);
        root = NULL;
    }
    return root;
}

// Driver program
int main()
{
    // input keys (use only 'a' to 'z' and lower case)
    string keys[] = {"the", "a", "there", "answer", "any",
                "by", "bye", "their", "hero", "heroplane"};
    int n = sizeof(keys)/sizeof(keys[0]);
    struct TrieNode* root = getNode();

    // construct trie
    for(int i=0; i<n; i++){
        insert(root, keys[i]);
    }

    // search for different keys
    search(root, "the") ? cout << "Yes\n" : cout << "No\n";
    search(root, "these") ? cout << "Yes\n" : cout << "No\n";

    remove(root, "heroplane");
    search(root, "hero") ? cout << "Yes\n" : cout << "No\n";
    search(root, "heroplane") ? cout << "Yes\n" : cout << "No\n";

    return 0;
}
