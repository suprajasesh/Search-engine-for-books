#include<bits/stdc++.h>
using namespace  std;
struct Node {
	char data;
	int end;
	struct Node* left;
	struct Node* eq;
	struct Node* right;
};

// Function to create a Node
Node* createNode(char newData)
{
	struct Node* newNode = new Node();
	newNode->data = newData;
	newNode->end = 0;
	newNode->left = NULL;
	newNode->eq = NULL;
	newNode->right = NULL;
	return newNode;
}

// Function to insert a word in the tree
void insertTST(Node** root,string word, int pos = 0)
{
	if (!(*root))
		*root = createNode(word[pos]);
	if ((*root)->data > word[pos])
		insertTST(&((*root)->left), word,pos);
	else if ((*root)->data < word[pos])
		insertTST(&((*root)->right), word,pos);
	else {
		if (pos + 1 == word.size())
			(*root)->end = 1;
		else
			insertTST(&((*root)->eq), word, pos + 1);
	}
}

void traverseTST(Node* root,vector<string>& ret,char* buff,int depth = 0)
{
	if (!root)
		return;
	traverseTST(root->left, ret,buff, depth);
	buff[depth] = root->data;
	if (root->end) {
		buff[depth + 1] = '\0';
		ret.push_back(string(buff));
	}
	traverseTST(root->eq, ret,buff, depth + 1);
	traverseTST(root->right, ret,buff, depth);
}

// Utility function to find all the words
vector<string> util(Node* root, string pattern)
{
	char buffer[1001];
	vector<string> ret;
	traverseTST(root, ret, buffer);
	if (root->end == 1)
		ret.push_back(pattern);
	return ret;
}

// Function to autocomplete based on the given prefix
vector<string> autocomplete(Node* root, string pattern)
{
	vector<string> words;
	int pos = 0;
	if (pattern.empty())
		return words;
	while (root && pos < pattern.length()) {
		if (root->data > pattern[pos])
			root = root->left;
		else if (root->data < pattern[pos])
			root = root->right;
		else if (root->data == pattern[pos]) {
			root = root->eq;
			pos++;
		}
		else
			return words;
	}
	words = util(root, pattern);
	return words;
}
// Function to print suggested words
void print(vector<string> sugg, string pat)
{
	for (int i = 0; i < sugg.size();i++)
		cout << pat << sugg[i].c_str()<< "\n";
}

void check(int a)
{
  if('a'<=(char)a && (char)a<='z')
    cout<<"Invalid choice";
}