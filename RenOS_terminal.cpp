#include "Command_functions.hpp"
using namespace std;		

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
				case 3: cin>>naam;
						if(cin.get()=='\n');
						current = pathReader(naam, current);
						break;
				case 4: SetConsoleTextAttribute(hConsole, 14);
						cout<<"\t Hey YASH Its nice to meet you!!"<<endl;
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
				case 11: cin>>naam;
						if(cin.get()=='\n');
						SetConsoleTextAttribute(hConsole, 9);
						cout<<"\t"<<path(search(naam, current))<<endl;
						break;
				case 12: getline(cin, naam);
						copier(naam, current);
						break;
				case 13: cin>>naam;
						if(cin.get()=='\n');
						//paste(pathReader(naam, current));
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
