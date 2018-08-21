#include<bits/stdc++.h>
#include <windows.h>
using namespace std;

struct node{
	string name;
	node * firstChild;
	node * sibling;
	node * parent;
};

struct node * root = new node;

void initialize(){
	root->name="main";
	root->firstChild = NULL;
	root->sibling = NULL;
	root->parent=NULL;
}		
	
void insert(string nam, node* par){
	node * temp = new node;
	temp->name=nam;
	temp->firstChild=NULL;
	temp->sibling=NULL;
	if(par->firstChild==NULL){
		par->firstChild=temp;
		temp->parent=par;
	}
	else{
		HANDLE  hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		node * q = new node;
		node * p = new node;
		q=par->firstChild;
		p=par->firstChild;
		while(q->sibling!=NULL){
			if(q->name==nam){
				SetConsoleTextAttribute(hConsole, 1);
				cout<<"\t Duplicate name of directory is not allowed!!"<<endl;
				return;
			}
			q=q->sibling;
		}
		if(q->name==nam){
			SetConsoleTextAttribute(hConsole, 1);
			cout<<"\t Duplicate name of directory is not allowed!!"<<endl;
			return;
		}
		q->sibling=temp;
		temp->parent=par;
	}
}
		
void print(node * par){
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 9);
	node * q = new node;
	if(par->firstChild!=NULL){
		q=par->firstChild;
		cout<<"\t";
		while(q->sibling!=NULL){
			cout<<q->name<<"\t";
			q=q->sibling;
		}
		cout<<q->name<<endl;
	}
	else{
		SetConsoleTextAttribute(hConsole, 1);
		cout<<"\t Directory is Empty!"<<endl;
	}
}

string path(node * current){
	node * q = new node;
	q=current;
	vector<string> names;
	while(q->parent!=NULL){
		names.push_back(q->name);
		q=q->parent;
	}
	names.push_back(root->name);
	string currentpath="";
	int size=names.size();
	for(int i=size-1;i>=0;i--){
		currentpath+=names[i]+"/";
	}
	return currentpath;
}

node * surfto(string naam, node* current){
	node * q = new node;
	if(current->firstChild!=NULL){
		q=current->firstChild;
		while(q->name!=naam && q->sibling!=NULL)q=q->sibling;
		if(q->sibling!=NULL)return q;
		else{
			if(q->sibling==NULL && q->name==naam)return q;
			else{
				HANDLE  hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 1);
				cout<<"\t No such file or directory exists!"<<endl;
				return current;
			}
		}
	}
	else{
		HANDLE  hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 1);
		cout<<"\t No such file or directory exists!"<<endl;
		return current;
	}
}

void freemem(node* dir){
	stack<node *> stk;
	stk.push(dir);
	node* del = new node;
	del=dir;
	while(!stk.empty()){
		del=stk.top();
		stk.pop();
		if(del->firstChild!=NULL){
			node* q = new node;
			q=dir->firstChild;
			while(q->sibling!=NULL){
				stk.push(q);
				q=q->sibling;
			}
		}
		free(del);
	}
}

void removedir(string nam, node* current){
	node* q = new node;
	q=current;
	node* p = new node;
	if(q->firstChild!=NULL){
		q=q->firstChild;
		p=q;
		while(q->name!=nam && q->sibling!=NULL){
			p=q;
			q=q->sibling;
		}
		if(q->sibling!=NULL){
			if(p==q)current->firstChild=p->sibling;
			else p->sibling=q->sibling;
			freemem(q);
		}
		else{
			if(q->sibling==NULL && q->name==nam){
				if(p==q)current->firstChild=NULL;
				else p->sibling=q->sibling;
				freemem(q);
			}
			else{
				HANDLE  hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 1);
				cout<<"\t No such Directory Exists!"<<endl;
			}
		}
	}
	else{
		HANDLE  hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 1);
		cout<<"\t Directory is already empty!"<<endl;
	}
}

//static node * copy = new node;
//void paste(node* current){
//	if(current->firstChild!=NULL){
//		node* q = new node;
//		q=current->firstChild;
//		while(q->sibling!=NULL){
//			q=q->sibling;
//		}
//		q->sibling=copy;
//		copy->parent=current;
//	}
//	else{
//		current->firstChild=copy;
//		copy->parent=current;
//	}
//}

node * search(string nam, node* current){
	stack<node*> dfs;
	dfs.push(current);
	node * dir = new node;
	while(!dfs.empty()){
		dir=dfs.top();
		dfs.pop();
		if(dir->firstChild!=NULL){
			dir=dir->firstChild;
			while(dir->sibling!=NULL){
				if(dir->name==nam)return dir;
				dfs.push(dir);
				dir=dir->sibling;
			}
			if(dir->name==nam)return dir;
			else dfs.push(dir);
		}	
	}
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 1);
	cout<<"\t No match Found!"<<endl;
	return current;
}

node * pathReader(string path, node* current){
	string dir="";
	node * q = new node;
	q=current;
	for(string::iterator it=path.begin();it!=path.end();++it){
		cout<<"in for loop"<<endl;
		if(*it!='/' && *it!='\0')dir=dir+*it;
		else{
			cout<<"detect yash"<<endl;
			if(dir=="main")q=root;
			else{
				cout<<"yash is not main"<<endl;
				if(q->firstChild!=NULL){
					cout<<"firstChild is not NULL"<<endl;
					node * p = new node;
					p=q;
					q=q->firstChild;
					while(q->sibling!=NULL){
						if(q->name==dir)break;
						q=q->sibling;
					}
					if(q->sibling==NULL&&q->name!=dir)q=p;
				}
				else{
					cout<<"firstChild is NULL"<<endl;
					HANDLE  hConsole;
					hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(hConsole, 1);
					cout<<"\t No such path found Found!"<<endl;
					return q;
				}
			}
			dir="";
		}
	}
	cout<<dir<<endl;
	if(q!=current)return q;
	else{
		cout<<"address is of current dir"<<endl;
		HANDLE  hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 1);
		cout<<"\t No such path found Found!"<<endl;
		return q;
	}
}

map<string, int> commandID;
void declareID(){
	commandID.insert(pair <string, int> ("exit", 0));
	commandID.insert(pair <string, int> ("ndir", 1));
	commandID.insert(pair <string, int> ("cd..", 2));
	commandID.insert(pair <string, int> ("cd", 3));
	commandID.insert(pair <string, int> ("yash", 4));
	commandID.insert(pair <string, int> ("lst", 5));
	commandID.insert(pair <string, int> ("guide", 6));
	commandID.insert(pair <string, int> ("pdr", 7));
	commandID.insert(pair <string, int> ("ddir", 8));
	commandID.insert(pair <string, int> ("clr", 9));
	commandID.insert(pair <string, int> ("cd/", 10));
	commandID.insert(pair <string, int> ("fnd", 11));
}

void printGuid(){
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 2);
	cout<<"\t ndir: Create new directory"<<endl;
	cout<<"\t cd..: Move to parent directory"<<endl;
	cout<<"\t cd: Change directory"<<endl;
	cout<<"\t cd/: Go to main directory directly"<<endl;
	cout<<"\t clr: Clear screen"<<endl;
	cout<<"\t fnd: Find the directory by name"<<endl;
	cout<<"\t yash: Greets Yash Srivastava (Creator)"<<endl;
	cout<<"\t lst: List directories"<<endl;
	cout<<"\t pdr: Present location"<<endl;
	cout<<"\t ddir: Delete the named directory"<<endl;
	cout<<"\t exit: Exit the terminal"<<endl;
}

int main(){
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	initialize();
	SetConsoleTextAttribute(hConsole, 236);
	cout<<"                             Welcom to RenOS terminal!!                              "<<endl;
	SetConsoleTextAttribute(hConsole, 2);
	cout<<"Type 'guide' to know about commands"<<endl<<endl;
	int flag=1;
	node * current = root;
	declareID();
	while(flag){
		string command;
		string naam;
		SetConsoleTextAttribute(hConsole, 8);
		cout<<path(current)<<">";
		SetConsoleTextAttribute(hConsole, 15);
		char a;
		a=cin.get();
		if(a=='\n')continue;
		cin>>command;
		command=a+command;
		if(cin.get()=='\n');
		if(commandID.find(command)!=commandID.end()){
			int ans=commandID[command];
			switch(ans){
				case 0: flag=0;
						break;
				case 1: cin>>naam;
						if(cin.get()=='\n');
						insert(naam, current);
						break;
				case 2: if(current!=root)current=current->parent;
						else{
							SetConsoleTextAttribute(hConsole, 1);
							cout<<"\t This is main Directory"<<endl;	
						}
						break;
				case 3: cin>>naam;
						if(cin.get()=='\n');
						current = pathReader(naam, current);
						break;
				case 4: SetConsoleTextAttribute(hConsole, 14);
						cout<<"\t Hey yash Its nice to meet you!!"<<endl;
						break;
				case 5: print(current);
						break;
				case 6: printGuid();
						break;
				case 7: SetConsoleTextAttribute(hConsole, 9);
						cout<<"\t "<<path(current)<<endl;
						break;
				case 8: cin>>naam;
						if(cin.get()=='\n');
						removedir(naam, current);
						break;
				case 9: system("CLS");
						SetConsoleTextAttribute(hConsole, 236);
						cout<<"                             RenOS terminal!!                              "<<endl<<endl;
						break;
				case 10: current=root;
						break;
				case 11: cin>>naam;
						if(cin.get()=='\n');
						SetConsoleTextAttribute(hConsole, 9);
						cout<<"\t"<<path(search(naam, current))<<endl;
						break;
			}
		}
		else{
			SetConsoleTextAttribute(hConsole, 4);
			cout<<"\t "<<command<<" is not a recognized command!"<<endl;
			continue;
		}
	}
	return 0;
}
