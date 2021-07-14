//sushaan shetty-20BCB0150
#include <iostream>
#include <unordered_map>
#include <cstring>
#include <bits/stdc++.h>
using namespace std;
//SPELL CHECKER STRUCTURE
struct TrieNodes {

	TrieNodes* Trie[256];

	bool isEnd;

	TrieNodes()
	{

		for (int i = 0; i < 256; i++) {

			Trie[i] = NULL;
		}
		isEnd = false;
	}
};
struct phonebook{//PHONEBOOK 
string name[100] ;
 string num[100];

};
string lookup;
struct TrieNode
{
 unordered_map<char,TrieNode*>child;
 bool lastLetter   ;

TrieNode()
    {
        for (char i = 'a'; i <= 'z'; i++)
            child[i] = NULL;

        lastLetter = false;
    }
};
TrieNode *root = NULL;


void AddContact(string s)
{
    int length = s.length();

   
    TrieNode *head = root;
    for (int i = 0; i < length; i++)
    {
     
        TrieNode *nextNode = head->child[s[i]];
        if (nextNode == NULL)
        {
       
            nextNode = new TrieNode();

       
            head->child[s[i]] = nextNode;
        }

        head = nextNode;
        if (i == length - 1)
            head->lastLetter = true;
    }
}

void DispContactsTill(TrieNode *currentNode, string pre)
{
    if (currentNode->lastLetter)
        {cout << pre << endl;}

   for (char i = 'a'; i <= 'z'; i++)
    {
        TrieNode *next = currentNode->child[i];
        if (next != NULL)
            DispContactsTill(next, pre + (char)i);
    }
}

   
void DispContacts(string str)
{
    TrieNode *previousNode = root;

    string pre = "";
    int length = str.length();

    int i;
    for (i=0; i<length; i++)
    {
        pre += (char)str[i];

        char lastChar = pre[i];

      
        TrieNode *currentNode = previousNode->child[lastChar];

       
        if (currentNode == NULL)
        {
            cout << "No result found "<<" " << pre
                 << endl;
            i++;
            break;
        }


        if(lookup==pre)
        {cout << "Suggestions for" <<" "<< pre<<" "
             << "are "<< endl;
        DispContactsTill(currentNode, pre);}

        previousNode = currentNode;
    }


    for (; i<length; i++)
    {
        pre += (char)str[i];
        cout << "no contact found for"<<" " << pre
             << endl;
    }
}


void DirectoryBuild(string contacts[],int n)
{
  root = new TrieNode();

   
    for (int i = 0; i < n; i++)
        AddContact(contacts[i]);
}
//SPELL CHECKER FUNCTIONS
void AddWord(TrieNodes* root, string s)
{

	TrieNodes* temp = root;

	
	for (int i = 0; i < s.length(); i++) {

		if (temp->Trie[s[i]] == NULL) {

			
			temp->Trie[s[i]] = new TrieNodes();
		}

		temp = temp->Trie[s[i]];
	}

	temp->isEnd = true;
}


void SuggestWords(TrieNodes* root, string res)
{

	if (root->isEnd == true) {

		cout << res << endl;
	}


	for (int i = 0; i < 256; i++) {


		if (root->Trie[i] != NULL) {


			res.push_back(i);
			SuggestWords(root->Trie[i], res);
			res.pop_back();
		}
	}
}


bool SpellCheck(TrieNodes* root, string key)
{

	for (int i = 0; i < key.length(); i++) {


		if (root->Trie[key[i]] == NULL) {

			SuggestWords(root, key.substr(0, i));

			return false;
		}

	
		root = root->Trie[key[i]];
	}
	if (root->isEnd == true) {

		return true;
	}
	SuggestWords(root, key);

	return false;
}
int main()
{
    string Search,x ;
    phonebook b;
    int z; char y;

     cout<<"                           WELCOME  TO  THE TRIE APPLICATIONS PROGRAM       "<<endl;
 do{   cout<<"                   _________________________________________________________   "<<endl;
     cout<<"                   |     Applications      |     MENU option to enter      |     "<<endl;
     cout<<"                   _________________________________________________________     "<<endl;
     cout<<"                   |      Phonebook        |                 1             |     "<<endl;
     cout<<"                   |    Spell Checker      |                 2             |     "<<endl;
     cout<<"                   |         Exit          |  anything other than 1 & 2    |     "<<endl;
     cout<<"                   _________________________________________________________   "<<endl;
    cin>>z;
 switch(z){
    case 1:
          {int n=0,i,check=0;
              char a;
      
     
         cout<<"enter a list of contact members, first the member name then that member's respective number:"<<endl;
   
        do {
            cin>>b.name[n];
              transform(b.name[n].begin(), b.name[n].end(), b.name[n].begin(), ::tolower);
            cin>>b.num[n];
            n++;
            cout<<"if u wanna continue enter Y or y , if u are done entering all the contact members , enter N or n: "<<endl;
            cin>>a;
           }while(a=='y'||a=='Y');

   


           DirectoryBuild(b.name, n);
   
             
          
           do {  
            cout<<"enter the starting few letters of the contact that you wanna lookup:"<<endl;
            cin>>Search ;
               transform(Search.begin(), Search.end(), Search.begin(), ::tolower);
               lookup=Search;
               DispContacts(Search);
                   cout<<"enter the name of the user whose number you want to lookup:"<<endl;
                 cin>>x;

              for(i=0;i<n;i++)
                 {
                       if(x==b.name[i])
                        {cout<<b.num[i]<<endl; check++;}
                       
                 }
                 if(check==0){cout<<"couldnt find user"<<endl;}
                 cout<<"if u wanna continue enter Y or y , if u are done entering all the contact members , enter N or n: "<<endl;
                cin>>a;
               }while(a=='y'||a=='Y');
             break;}
     case 2:
             {        string key ;
                 cout<<"which word do you wanna check the spelling for ? enter here:";
                 cin>>key;       
                   transform(key.begin(), key.end(), key.begin(), ::tolower);
                 	TrieNodes* root = new TrieNodes();
  
                     std::ifstream file("dictionary.txt");
                          std::string str;
                      while (std::getline(file, str)) {
                          AddWord(root,str);
                                                }

                     if (SpellCheck(root, key)) {

                         		cout << "the spelling seems fine!"<<endl;
                                            	}
                                    else 
                              cout<<endl<<"you might have  meant to say any of the above suggested words^^"<<endl;
             break;
             }
             default:
               break;   
    }   
     cout<<"if u wanna continue and view the menu again enter Y or y , if u are done exploring the applications of trie then , enter N or n: "<<endl;
            cin>>y; 
           }while(y=='y'||y=='Y');

    return 0;
}
