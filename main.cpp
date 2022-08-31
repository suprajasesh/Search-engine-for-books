#include <bits/stdc++.h>
#include <fstream>
#include <ctype.h>
#include "trie.cpp"
#include "ternary.cpp"
#include <string.h>
using namespace std;
#define MAX 50
// Driver
int main()
{
  time_t start,end;
	fstream f("books.txt",ios::in);
	string book[700],author[700],text;
  int i=0;
  vector<string>bnames;
  vector<string>anames;
	while(getline(f,text))
	{
	  int start=text.find("- "),end=text.find("\n");
    string temp=text.substr(start+2,end - start);
    temp+="- ";
    temp+=text.substr(0,start);
    bnames.push_back(text);
		book[i].append(text);
    anames.push_back(temp);
    author[i].append(temp);
   	i++;
  }
	int n=sizeof(book)/sizeof(book[0]);
  Node* rootbTST=NULL;
  Node* rootaTST=NULL;
	TrieNode *rootb=getNode();
  TrieNode *roota=getNode();
	// Construct trie
	for(int i = 0; i < n; i++)
	{
    insert(rootb,book[i]);
    insert(roota,author[i]);
	}
  //construct ternary tree
  for(string str:bnames)
    insertTST(&rootbTST,str);
  for(string str:anames)
    insertTST(&rootaTST,str);
  int choice;
  cout<<"\n\t\t\t\tMENU FOR SEARCH ENGINE\n\t\t1.Search using trie tree\n\t\t2.Search using ternary search tree\n\t\t3.Exit\n";
  cout<<"\nEnter choice:";
  cin>>choice;
  check(choice);
  if(choice==1)
  {
    int ch;
    time(&start);
    do{
      cout<<"\n\t\t\t\tMENU FOR SEARCH ENGINE - TRIE TREE\n\t\t1.Search by book\n\t\t2.Search by author\n\t\t3.Exit\n";
      cout<<"\nEnter choice:";
      cin>>ch;
      check(ch);
      if(ch==1)
      {
        string booktosearch;
        cout<<"Enter name of book to be searched:";
        cin.clear();
        cin.ignore(INT_MAX,'\n');
        getline(cin,booktosearch);
        booktosearch[0]=toupper(booktosearch[0]);
        for(int i=1;i<booktosearch.length();i++)
          if(isupper(booktosearch[i]))
            booktosearch[i]=tolower(booktosearch[i]);
        for(int i=1;i<booktosearch.length();i++)
          if(booktosearch[i]==' ')
            booktosearch[i+1]=toupper(booktosearch[i+1]);
  
        cout<<"\nBOOK NAME- AUTHOR\n";
  
        int comp=printAutoSuggestions(rootb, booktosearch);
        if (comp==-1)
          cout<<"No other books found with this prefix\n";
        else if (comp==0)      
          cout<<"No books found with this prefix\n";
      }
      else if(ch==2)
      {
        string autosearch;
        cin.clear();
        cin.ignore(INT_MAX,'\n');
        cout<<"Enter name of author to be searched:";
        getline(cin,autosearch,'\n');
        autosearch[0]=toupper(autosearch[0]);
        for(int i=1;i<autosearch.length();i++)
          if(isupper(autosearch[i]))
            autosearch[i]=tolower(autosearch[i]);
        for(int i=1;i<autosearch.length();i++)
          if(autosearch[i]==' ')
            autosearch[i+1]=toupper(autosearch[i+1]);
  
        cout<<"\nAUTHOR- BOOK NAME\n";
        
        int comp=printAutoSuggestions(roota,autosearch);
        if (comp==-1)
          cout<<"\nNo other author found with this prefix\n";
        else if (comp==0)
          cout<<"\nNo authors found with this prefix\n";
      }
      else if(ch==3)
        cout<<"Exiting...\n";
      else
      {cout<<"\nInvalid choice\n";
        break;}
    }while(ch!=3);
   time(&end);
  cout<<"Time taken for execution of trie tree:"<<end-start<<" s\n";
  }
  else if(choice==2)
  {
    int ch;
    time(&start);
      do{
        cout<<"\n\t\t\t\tMENU FOR SEARCH ENGINE - TERNARY SEARCH TREE \n\t\t1.Search by book\n\t\t2.Search by author\n\t\t3.Exit\n";
        cout<<"\nEnter choice:";
        cin>>ch;
        if(ch==1)
        {
          string booktosearch;
          cout<<"Enter name of book to be searched:";
          cin.clear();
          cin.ignore(INT_MAX,'\n');
          getline(cin,booktosearch);
          booktosearch[0]=toupper(booktosearch[0]);
          for(int i=1;i<booktosearch.length();i++)
            if(isupper(booktosearch[i]))
              booktosearch[i]=tolower(booktosearch[i]);
          for(int i=1;i<booktosearch.length();i++)
            if(booktosearch[i]==' ')
              booktosearch[i+1]=toupper(booktosearch[i+1]);
    
          cout<<"\nBOOK NAME- AUTHOR\n";
          vector<string>listb=autocomplete(rootbTST, booktosearch);
          if (listb.size()==0)
            cout<<"No other books found with this prefix\n";
          else 
            print(listb,booktosearch);
        }
        else if(ch==2)
        {
          string autosearch;
          cin.clear();
          cin.ignore(INT_MAX,'\n');
          cout<<"Enter name of author to be searched:";
          getline(cin,autosearch,'\n');
          autosearch[0]=toupper(autosearch[0]);
          for(int i=1;i<autosearch.length();i++)
            if(isupper(autosearch[i]))
              autosearch[i]=tolower(autosearch[i]);
          for(int i=1;i<autosearch.length();i++)
            if(autosearch[i]==' ')
              autosearch[i+1]=toupper(autosearch[i+1]);
    
          cout<<"\nAUTHOR- BOOK NAME\n";

          vector<string>lista=autocomplete(rootaTST, autosearch);
          if (lista.size()==0)
            cout<<"No other books found with this prefix\n";
          else 
            print(lista,autosearch);
        }
        else if(ch==3)
          cout<<"Exiting...\n";
        else
        {cout<<"\nInvalid choice\n";
          break;}
      }while(ch!=3);
     time(&end);
  cout<<"Time taken for execution of ternary search tree:"<<end-start<<" s\n";
  }
  else if(choice==3)
    cout<<"Exiting..\n";
  else
    cout<<"Invalid choice";
  f.close();
  return 0;
}
