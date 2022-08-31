#include<bits/stdc++.h>
using namespace  std;
const int ALPHABET_SIZE=55;
int CHAR_TO_INDEX(char c) 
{
  int index;
  if(c==' ')
    index=51;
  else if(c=='\'')
    index=52;
  else if(c=='-')
    index=53;
  else if(c=='.')
    index=54;
  else if('A'<=c && c<='Z')
    index=c-'A';
  else if('a'<=c && c<='z')
    index=c-'A'-6;
  return index;
}
// trie node
struct TrieNode
{
	TrieNode *children[ALPHABET_SIZE];
	// isEndOfWord is true if the node represents
	// end of a word
	bool isEndOfWord;
};

// Returns new trie node (initialized to NULLs)
TrieNode *getNode()
{
	TrieNode *pNode = new TrieNode;
	pNode->isEndOfWord = false;
	for (int i = 0; i < ALPHABET_SIZE; i++)
		pNode->children[i] = NULL;
	return pNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just
// marks leaf node
void insert(TrieNode *root, string key)
{
	TrieNode *pCrawl = root;
	for (int i = 0; i < key.length(); i++)
	{
		int index=CHAR_TO_INDEX(key[i]);
		if (!pCrawl->children[index])
			pCrawl->children[index] = getNode();
		pCrawl = pCrawl->children[index];
	}

	// mark last node as leaf
	pCrawl->isEndOfWord = true;
}

void suggestionsRec(TrieNode* root, string currPrefix)
{
    // found a string in Trie with the given prefix
  if (root->isEndOfWord)
    cout << currPrefix << endl;
  for (int i = 0; i < ALPHABET_SIZE; i++)
    if (root->children[i])
    {
        // child node character value
      char child;
      if(i==51)
        child=' ';
      else if(i==52)
        child='\'';
      else if(i==53)
        child='-';
      else if(i==54)
        child='.';
      else if(0<=i && i<=25)
        child='A'+i;
      else if(i>25 && i<=50)
        child='A'+i+6;
      suggestionsRec(root->children[i],currPrefix + child);
    }
}

bool isLastNode(struct TrieNode* root)
{
  for (int i = 0; i < ALPHABET_SIZE; i++)
    if (root->children[i])
      return 0;
  return 1;
}

// print suggestions for given query prefix.
int printAutoSuggestions(TrieNode* root, string query)
{
  TrieNode* pCrawl = root;
  for (int i=0;i<query.length();i++) 
  {
    int ind = CHAR_TO_INDEX(query[i]);
    // no string in the Trie has this prefix
    if (!pCrawl->children[ind])
      return 0;
    pCrawl = pCrawl->children[ind];
  }
  // If prefix is present as a word, but
  // there is no subtree below the last
  // matching node.
  if (isLastNode(pCrawl))
  {
    cout << query << endl;
    return -1;
  }
  suggestionsRec(pCrawl, query);
  return 1;
}