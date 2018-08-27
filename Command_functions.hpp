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

map<string, int> commandID;
void declareID(){
	commandID.insert(pair <string, int> ("exit", 0));
	commandID.insert(pair <string, int> ("ndir", 1));
	commandID.insert(pair <string, int> ("cd", 3));
	commandID.insert(pair <string, int> ("yash", 4));
	commandID.insert(pair <string, int> ("lst", 5));
	commandID.insert(pair <string, int> ("guide", 6));
	commandID.insert(pair <string, int> ("pdr", 7));
	commandID.insert(pair <string, int> ("ddir", 8));
	commandID.insert(pair <string, int> ("clr", 9));
	commandID.insert(pair <string, int> ("fnd", 11));
	commandID.insert(pair <string, int> ("cp", 12));
	commandID.insert(pair <string, int> ("pst", 13));
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
	if(path==".")return current;
	if(path==".."){
		if(current->parent!=NULL)return current->parent;
		else{
			HANDLE  hConsole;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 1);
			cout<<"\t This is main Directory"<<endl;
			return current;
		}
	}
	if(path=="/")return root;
	path+='`';
	string dir="";
	node * q = new node;
	q=current;
	for(string::iterator it=path.begin();it!=path.end();++it){
		if(*it!='/' && *it!='`')dir=dir+*it;
		else{
			if(dir=="main")q=root;
			else{
				if(q->firstChild!=NULL){
					q=q->firstChild;
					while(q->sibling!=NULL){
						if(q->name==dir)break;
						q=q->sibling;
					}
					if(q->sibling==NULL&&q->name!=dir)q=current;
				}
				else{
					HANDLE  hConsole;
					hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(hConsole, 1);
					cout<<"\t No such path found Found!"<<endl;
					q=current;
					return q;
				}
			}
			dir="";
		}
	}
	if(q!=current)return q;
	else{
		HANDLE  hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 1);
		cout<<"\t No such path found Found!"<<endl;
		return q;
	}
}

static vector<node*> copyAdress;

void copier(string nameList, node* current){
	copyAdress.clear();
	node * q = new node;
	q=current;
	if(nameList=="#"){
		if(q->firstChild!=NULL){
			q=q->firstChild;
			while(q->sibling!=NULL){
				copyAdress.push_back(q);
				q=q->sibling;
			}
			copyAdress.push_back(q);
		}
	}
	else{
		nameList+='`';
		string::iterator it;
		string dir="";
		for(it=nameList.begin();it!=nameList.end();++it){
			if(*it!=' '&&*it!='`')dir+=*it;
			else{
				q=current;
				if(q->firstChild!=NULL){
					q=q->firstChild;
					while(q->sibling!=NULL){
						if(q->name==dir)copyAdress.push_back(q);
						else q=q->sibling;
					}
					if(q->sibling==NULL && q->name==dir)copyAdress.push_back(q);
					else{
						HANDLE  hConsole;
						hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
						SetConsoleTextAttribute(hConsole, 1);
						cout<<"\t"<<dir<<" do not exists in current directory!"<<endl;
					}
				}
				else{
					HANDLE  hConsole;
					hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(hConsole, 1);
					cout<<"\t Directory is Empty!"<<endl;
				}
				dir="";
			}
		}
	}
}

//node * newTree(node * newroot){
//	node * newtemp = new node;
//	newtemp->name=newroot->name;
//	newtemp->firstChild=NULL;
//	newtemp->sibling=NULL;
//	newtemp->parent=NULL;
//	queue<node *> bfs;
//	if(newroot->firstChild==NULL)return newtemp;
//	else{
//		node * q = new node;
//		node * p = new node;
//		p=newtemp;
//		bfs.push(newroot->firstChild);
//		while(!bfs.empty()){
//			q=bfs.front();
//			bfs.pop();
//			insert(q->name, );
//		}
//	}
//}
//
//void paste(node * detination){
//	if(!copyAdress.empty()){
//		vector<node *>::iterator it;
//		for(it=copyAdress.begin();it!=copyAdress.end();++it){
//			node * tempRoot
//		}
//	}
//	else{
//		HANDLE  hConsole;
//		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//		SetConsoleTextAttribute(hConsole, 1);
//		cout<<"\t Nothing has been copied!"<<endl;
//	}
//}

void printGuid(){
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 2);
	cout<<"\t ndir: Create new directory\n"
	"\t cd ..: Move to parent directory\n"
	"\t cd: Change directory\n"
	"\t cd /: Go to main directory directly\n"
	"\t clr: Clear screen\n"
	"\t fnd: Find the directory by name\n"
	"\t yash: Greets Yash Srivastava (Creator)\n"
	"\t lst: List directories\n"
	"\t pdr: Present location\n"
	"\t ddir: Delete the named directory\n"
	"\t exit: Exit the terminal"<<endl;
}
