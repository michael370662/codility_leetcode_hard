// A memory optimized C++ implementation of trie 
// using unordered_map 
#include <iostream> 
#include <unordered_map> 
#include <string>
#include <iterator>
using namespace std; 
  
class Trie { 
    public: 
    //Empty constructor
    Trie(){}
    
    Trie(string& str){
        
        Trie* root = nullptr;
    
        for(string::iterator sIt = str.begin();sIt != str.end() ;sIt++)
        {
            if(*sIt == ' ')
                continue;
            
            string temp;    
            while((*sIt != ' ') && (sIt != str.end()))
            {
                temp+=(*sIt);
                sIt++;
            }
            root->insert(root,temp);
            if(sIt == str.end())
                break;
        }
        *this = *root;
    }
    //function to make a new trie
    Trie* getNewTrieNode() 
    { 
        Trie* node = new Trie; 
        node->isEndOfWord = false; 
        return node; 
    }
    //function to insert in trie
    void insert(Trie*& root, const string& str) 
    { 
        if (root == nullptr) 
            root = getNewTrieNode(); 
      
        Trie* temp = root; 
        for (int i = 0; i < str.length(); i++) { 
            char x = str[i]; 
      
            // make a new node if there is no path
            if (temp->map.find(x) == temp->map.end()) 
                temp->map[x] = getNewTrieNode(); 
      
            temp = temp->map[x]; 
        } 
      
    temp->isEndOfWord = true; 
    }
    //function to search in trie
    bool search(Trie*& root, const string& str) 
    { 
        //return false if Trie is empty
        if (root == nullptr) 
            return false; 
      
        Trie* temp = root; 
        for (int i = 0; i < str.length(); i++) { 
      
            // go to next node
            temp = temp->map[str[i]]; 
      
            if (temp == nullptr) 
                return false; 
        } 
      
    return temp->isEndOfWord; 
    }
     
    Trie* remove(Trie*& root, string& str, int depth = 0) 
    { 
        // If tree is empty 
        if (root == nullptr) 
            return nullptr; 
      
        // If last character of key is being processed 
        if (depth == str.size()) { 
      
            // This node is no more end of word after 
            // removal of given key 
            if (root->isEndOfWord) 
                root->isEndOfWord = false; 
      
            // If given is not prefix of any other word 
            if (root->map.empty()) { 
                delete (root); 
                root = nullptr; 
            } 
      
            return root; 
        } 
      
        // If not last character, recur for the child 
        Trie* temp = root;
        temp = temp->map[str[depth]];
        root->map[str[depth]] = remove(temp, str, ++depth); 
      
        // If root does not have any child (its only child got  
        // deleted), and it is not end of another word. 
        if (root->map.empty() && root->isEndOfWord == false) { 
            delete (root); 
            root = nullptr; 
        } 
      
        return root; 
    }
    Trie* deleteall(Trie*& root)
    {
        if(root == nullptr)
            return root;
        if(root->map.empty())
        {
            delete (root);
            root = nullptr;
            return root;
        }
        
        for(unordered_map<char, Trie*>::iterator mIt = root->map.begin(); mIt != map.end(); mIt++)
        {
            Trie* temp;
            temp = mIt->second;
            const char c = mIt->first;
            root->map[c] = deleteall(temp);
        }
    }
    //Destructor
    ~Trie()
    {
        Trie* root = this;
        if(!root->map.empty())
            root = deleteall(root);
    }
    private:
    // nodes store a map to child node
    unordered_map<char, Trie*> map;
    // isEndOfWord is true if the node 
    // represents end of a word 
    bool isEndOfWord;
}; 
  
//Driver function
int main() 
{ 
    string str = "by metal owl egg mr crow worm my ate";
    
    string temp = "metal";
    
    Trie* root = new Trie(str); 

    root->remove(root,temp,0);
    cout << root->search(root, "metal") << " "; 
   
    cout << root->search(root, "crow") << endl; 
    
    delete root;
  
    return 0; 
} 