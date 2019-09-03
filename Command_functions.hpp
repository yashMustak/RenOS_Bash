#include <vector>
#include <stack>
#include <queue>
#include <iostream>
#include <windows.h>

#include "mwayTree.hpp"
#include "idMap.hpp"

using namespace std;

struct Node *root = new Node;

void initialize(Node *base = root, string basename = "main")
{
	base->name = basename;
	base->firstChild = NULL;
	base->sibling = NULL;
	base->parent = NULL;
}

void insert(string nam, Node *par)
{
	Node *temp = new Node;
	temp->name = nam;
	temp->firstChild = NULL;
	temp->sibling = NULL;
	if (par->firstChild == NULL)
	{
		par->firstChild = temp;
		temp->parent = par;
	}
	else
	{
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		Node *q = new Node;
		Node *p = new Node;
		q = par->firstChild;
		p = par->firstChild;
		while (q->sibling != NULL)
		{
			if (q->name == nam)
			{
				SetConsoleTextAttribute(hConsole, 1);
				cout << "\t Duplicate name of directory is not allowed!!" << endl;
				return;
			}
			q = q->sibling;
		}
		if (q->name == nam)
		{
			SetConsoleTextAttribute(hConsole, 1);
			cout << "\t Duplicate name of directory is not allowed!!" << endl;
			return;
		}
		q->sibling = temp;
		temp->parent = par;
	}
}

void print(Node *par)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 9);
	Node *q = new Node;
	if (par->firstChild != NULL)
	{
		q = par->firstChild;
		cout << "\t";
		while (q->sibling != NULL)
		{
			cout << q->name << "\t";
			q = q->sibling;
		}
		cout << q->name << endl;
	}
	else
	{
		SetConsoleTextAttribute(hConsole, 1);
		cout << "\t Directory is Empty!" << endl;
	}
}

string path(Node *current, Node *basic = root)
{
	Node *q = new Node;
	q = current;
	vector<string> names;
	while (q->parent != NULL)
	{
		names.push_back(q->name);
		q = q->parent;
	}
	names.push_back(basic->name);
	string currentpath = "";
	int size = names.size();
	for (int i = size - 1; i >= 0; i--)
	{
		currentpath += names[i] + "/";
	}
	return currentpath;
}

void freemem(Node *dir)
{
	stack<Node *> stk;
	stk.push(dir);
	Node *del = new Node;
	del = dir;
	while (!stk.empty())
	{
		del = stk.top();
		stk.pop();
		if (del->firstChild != NULL)
		{
			Node *q = new Node;
			q = dir->firstChild;
			while (q->sibling != NULL)
			{
				stk.push(q);
				q = q->sibling;
			}
		}
		free(del);
	}
}

void removedir(string nam, Node *current)
{
	Node *q = new Node;
	q = current;
	Node *p = new Node;
	if (q->firstChild != NULL)
	{
		q = q->firstChild;
		p = q;
		while (q->name != nam && q->sibling != NULL)
		{
			p = q;
			q = q->sibling;
		}
		if (q->sibling != NULL)
		{
			if (p == q)
				current->firstChild = p->sibling;
			else
				p->sibling = q->sibling;
			freemem(q);
		}
		else
		{
			if (q->sibling == NULL && q->name == nam)
			{
				if (p == q)
					current->firstChild = NULL;
				else
					p->sibling = q->sibling;
				freemem(q);
			}
			else
			{
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 1);
				cout << "\t No such Directory Exists!" << endl;
			}
		}
	}
	else
	{
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 1);
		cout << "\t Directory is already empty!" << endl;
	}
}

Node *search(string nam, Node *current)
{
	stack<Node *> dfs;
	dfs.push(current);
	Node *dir = new Node;
	while (!dfs.empty())
	{
		dir = dfs.top();
		dfs.pop();
		if (dir->firstChild != NULL)
		{
			dir = dir->firstChild;
			while (dir->sibling != NULL)
			{
				if (dir->name == nam)
					return dir;
				dfs.push(dir);
				dir = dir->sibling;
			}
			if (dir->name == nam)
				return dir;
			else
				dfs.push(dir);
		}
	}
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 1);
	cout << "\t No match Found!" << endl;
	return current;
}

Node *pathReader(string path, Node *current, Node *base = root)
{
	if (path == ".")
		return current;
	if (path == "..")
	{
		if (current->parent != NULL)
			return current->parent;
		else
		{
			HANDLE hConsole;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 1);
			cout << "\t This is main Directory" << endl;
			return current;
		}
	}
	if (path == "/")
		return base;
	path += '`';
	string dir = "";
	Node *q = new Node;
	q = current;
	for (string::iterator it = path.begin(); it != path.end(); ++it)
	{
		if (*it != '/' && *it != '`')
			dir = dir + *it;
		else
		{
			if (dir == "main")
				q = base;
			else
			{
				if (q->firstChild != NULL)
				{
					q = q->firstChild;
					while (q->sibling != NULL)
					{
						if (q->name == dir)
							break;
						q = q->sibling;
					}
					if (q->sibling == NULL && q->name != dir)
						q = current;
				}
				else
				{
					HANDLE hConsole;
					hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(hConsole, 1);
					cout << "\t No such path found Found!" << endl;
					q = current;
					return q;
				}
			}
			dir = "";
		}
	}
	if (q != current)
		return q;
	else
	{
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 1);
		cout << "\t No such path found Found!" << endl;
		return q;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
static vector<Node *> copyAdress;

void copier(string nameList, Node *current)
{
	copyAdress.clear();
	Node *q = new Node;
	q = current;
	if (nameList == "#")
	{
		if (q->firstChild != NULL)
		{
			q = q->firstChild;
			while (q != NULL)
			{
				copyAdress.push_back(q);
				q = q->sibling;
			}
			//	copyAdress.push_back(q);
		}
	}
	else
	{
		nameList += '`';
		string::iterator it;
		string dir = "";
		for (it = nameList.begin(); it != nameList.end(); ++it)
		{
			if (*it != ' ' && *it != '`')
				dir += *it;
			else
			{
				int size_before = copyAdress.size();
				int size_after = 0;
				if (q->firstChild != NULL)
				{
					q = q->firstChild;
					//					while(q->sibling!=NULL){
					//						if(q->name==dir)copyAdress.push_back(q);
					//						else q=q->sibling;
					//					}
					//					if(q->sibling==NULL && q->name==dir)copyAdress.push_back(q);
					while (q != NULL)
					{
						if (q->name == dir)
							copyAdress.push_back(q);
						else
							q = q->sibling;
					}
					size_after = copyAdress.size();
					if (size_before == size_after)
					{
						HANDLE hConsole;
						hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
						SetConsoleTextAttribute(hConsole, 1);
						cout << "\t" << dir << " do not exists in current directory!" << endl;
					}
				}
				else
				{
					HANDLE hConsole;
					hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(hConsole, 1);
					cout << "\t Directory is Empty!" << endl;
				}
				dir = "";
			}
		}
	}
	vector<Node *>::iterator it;
	Node *p = new Node;
	for (it = copyAdress.begin(); it != copyAdress.end(); ++it)
	{
		p = *it;
		cout << q->name << endl;
	}
}

string copycode(Node *dir)
{
	string code = "";
	Node *q = new Node;
	q = dir;
	queue<Node *> bfs;
	bfs.push(q);
	while (!bfs.empty())
	{
		if (q->firstChild != NULL)
		{
			q = q->sibling;
			while (q->sibling != NULL)
			{
				bfs.push(q);
				q = q->sibling;
			}
			bfs.push(q);
		}
		q = bfs.front();
		code += path(q, dir) + ',';
	}
	return code;
}

Node *newtree(Node *dir)
{
	string code = copycode(dir);
	Node *treehead = new Node;
	string::iterator it;
	string tempPath = "";
	for (it = code.begin(); it != code.end(); ++it)
	{
		if (*it != ',')
			tempPath += *it;
		else
		{
			tempPath += '`';
			string::iterator it1;
			string dirname = "";
			vector<string> addressVector;
			for (it1 = tempPath.begin(); it1 != tempPath.end(); ++it1)
			{
				if (*it != '/' && *it != '`')
					dirname += *it;
				else
				{
					addressVector.push_back(dirname);
				}
				dirname = "";
			}
			dirname = addressVector[addressVector.size() - 1];
			if (addressVector.size() == 1)
			{
				Node *newroot = new Node;
				initialize(newroot, dir->name);
				treehead = newroot;
			}
			Node *q = new Node;
			q = treehead;
			for (int i = 0; i < addressVector.size() - 1; i++)
			{
				q = search(addressVector[i], q);
			}
			insert(dirname, q);
		}
		tempPath = "";
	}
}

void paste(Node *destination)
{
	if (!copyAdress.empty())
	{
		vector<Node *>::iterator it;
		Node *q = new Node;
		q = destination->firstChild;
		if (q != NULL)
		{
			while (q->sibling != NULL)
				q = q->sibling;
		}
		for (it = copyAdress.begin(); it != copyAdress.end(); ++it)
		{
			q->sibling = newtree(*it);
			q = q->sibling;
			q->parent = destination;
		}
	}
	else
	{
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 1);
		cout << "\t Nothing has been copied!" << endl;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void printGuid()
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 2);
	cout << "\t ndir: Create new directory\n"
			"\t cd ..: Move to parent directory\n"
			"\t cd: Change directory\n"
			"\t cd /: Go to main directory directly\n"
			"\t clr: Clear screen\n"
			"\t fnd: Find the directory by name\n"
			"\t yash: Greets Yash Srivastava (Creator)\n"
			"\t lst: List directories\n"
			"\t pdr: Present location\n"
			"\t ddir: Delete the named directory\n"
			"\t cp: To copy directories\n"
			"\t pst: To paste at current directory\n"
			"\t exit: Exit the terminal"
		 << endl;
}
