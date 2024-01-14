#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "strutils.h"
#include <vector>
#include <algorithm>
using namespace std;

//Mehmet Faruk Komurculer

struct structt{
    string name_series;
    string name_actors;
    double rating;
	double avg;
	int counter;
};

bool Comparison(const structt& a, const structt& b){
    if (a.avg < b.avg)
        return false;
    else if (a.avg > b.avg)
        return true;

    if (a.name_series > b.name_series)
        return false;
    else if (a.name_series < b.name_series)
        return true;

    return false;
}

string SplitSpaces(string& s){
	while(!s.empty() && isspace(*s.begin()))
	{
		s.erase(s.begin());
	}
	while(!s.empty() && isspace(*s.rbegin()))
	{
		s.erase(s.length()-1);
	}
	return s;
}

void displayMenu(){
    cout << "---" << endl;
    cout << "MENU" << endl;
    cout << "1. Print the series" << endl;
    cout << "2. Search the series according to the rating" << endl;
    cout << "3. Add the series to the favorite list" << endl;
    cout << "4. Print the favorite list" << endl;
    cout << "5. Exit" << endl;
    cout << "---" << endl;
}

bool MenuOptions(string s1){
    if (s1.length() > 1)
        return false;
    if (s1<"1" || s1>"5")
        return false;
    return true;
}

int menuChoice(){
    bool Check = true;
    string choice;
    do{
        if (!Check){
            cout << "This is not a valid option!" << endl;
		}
        else{
            Check = false;
        }
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cout << "---" << endl;
    }while(!MenuOptions(choice));
    return atoi(choice);
}
void printList(const vector<structt>& liste){
    cout << "RANK,NAME,ACTOR,POINTS" << endl;
	for (unsigned int i=0; i<liste.size(); i++)
	{
		cout << i+1 << "," << liste[i].name_series << "," << liste[i].name_actors << "," << liste[i].avg << endl;
	}
}

int indexOfnameseries(const vector<structt>& liste, const string& name_series){
    for (int i=0; i<liste.size(); i++){
        if (liste[i].name_series == name_series){
            return i;
		}
	}
    return -1;
}

void printListWantedRating(const vector<structt>& liste){
	double wanted_rating;
	cout << "Please enter the minimum rating: ";
	if (cin >> wanted_rating){
		if (wanted_rating >= 0 && wanted_rating <= 10){
			cout << "RANK,NAME,ACTOR,POINTS" << endl;
			for (int i = 0; i < liste.size(); i++){
				if (liste[i].avg >= wanted_rating){
					cout << i+1 << "," << liste[i].name_series << "," << liste[i].name_actors << "," << liste[i].avg << endl;
				}
			}
		}
		else{
			cout << "This is not a valid rating!" << endl;
			cin.clear();
			while (cin.get() != '\n');
		}
	}
	else{
		cout << "This is not a valid rating!" << endl;
		cin.clear();
		while (cin.get() != '\n');
	}
}

void CreatingFavList(vector<structt>& liste, vector<structt> &favList){
	string add_series;
	int name_series_Index, favlist_Index, bos_Idx = 0;
	cout << "Please enter the name of series: ";
	getline(cin,add_series);
	getline(cin,add_series);
	SplitSpaces(add_series);
	ToUpper(add_series);
	name_series_Index = indexOfnameseries(liste,add_series);
	structt temp;
	if (name_series_Index != -1){
		if (favList.size() != 0){
			favlist_Index = indexOfnameseries(favList,add_series);
			if (favlist_Index != -1){
				cout << "Your favorite list already have " << add_series << endl;
			}
			else{
				temp.name_series = add_series;
				temp.avg = liste[name_series_Index].avg;
				temp.name_actors = liste[name_series_Index].name_actors;
				favList.push_back(temp);	
			}
		}
		else{
			temp.name_series = add_series;
			temp.avg = liste[name_series_Index].avg;
			temp.name_actors = liste[name_series_Index].name_actors;
			favList.push_back(temp);
		}
	}
	else{
		cout << "There is no such TV series!" << endl;
	}
}

void PrintFavList(vector<structt>& favList){
	if (favList.size() != 0){
		sort(favList.begin(), favList.end(), &Comparison);
		cout <<"RANK,NAME,ACTOR,POINTS" << endl;
		for (int i = 0; i < favList.size(); i++){
			cout << i+1 << "," << favList[i].name_series << "," << favList[i].name_actors << "," << favList[i].avg << endl;
		}
	}
	else{
		cout << "Your favorite list is currently empty!" << endl;
	}
}

void MainMenu(vector<structt>& liste){
    int choice;
	vector<structt> favList;
    do{
        choice = menuChoice();
        if (choice==1){
			printList(liste);
        }
        else if (choice==2){
            printListWantedRating(liste);
        }
        else if (choice==3){
			CreatingFavList(liste, favList);
        }
        else if (choice==4){
			PrintFavList(favList);
        }
    }while(choice!=5);
}

void readFile1(ifstream& inFile, vector<structt>& liste){
    string line, name_series, name_actors;
    int semicolonIdx, name_series_Idx;
    while(getline(inFile,line)){
		semicolonIdx = line.find(";");
        name_series = line.substr(semicolonIdx+2);
		SplitSpaces(name_series);
        ToUpper(name_series);
        name_actors = line.substr(0,semicolonIdx);
		SplitSpaces(name_actors);
		ToUpper(name_actors);
		name_series_Idx = indexOfnameseries(liste, name_series);
		structt temp;
		if (name_series_Idx != -1){
			liste[name_series_Idx].name_actors = name_actors;
		}
        else{
			temp.name_series = name_series;
            temp.name_actors = name_actors;
            liste.push_back(temp);
        }
	}
}

void readFile2(ifstream& inFile, vector<structt>& liste){
	inFile.clear();
	inFile.seekg(0);
    string line, name_series, str_value;
    int tabIdx, name_series_Idx;
    double value;
    structt temp;
    while(getline(inFile,line)){
		tabIdx = line.find("\t");
		name_series = line.substr(tabIdx+1);
		SplitSpaces(name_series);
        ToUpper(name_series);
		str_value = line.substr(0,tabIdx);
		SplitSpaces(str_value);
        value = atof(str_value);
        name_series_Idx = indexOfnameseries(liste, name_series);
        if (name_series_Idx != -1){
			if (liste[name_series_Idx].rating == -5){
				liste[name_series_Idx].rating = value;
				liste[name_series_Idx].counter = 1;
			}
			else if (liste[name_series_Idx].rating == -5 && liste[name_series_Idx].counter >= 1){
				liste[name_series_Idx].rating = value + liste[name_series_Idx].rating;
				liste[name_series_Idx].counter += 1;
			}
			else{
				liste[name_series_Idx].rating = value + liste[name_series_Idx].rating;
				liste[name_series_Idx].counter += 1;
			}
		}
        else{
			temp.name_series = name_series;
			temp.rating = 0;
			liste.push_back(temp);
        }
    }
	for (int i = 0; i < liste.size(); i++){
		liste[i].avg = liste[i].rating / liste[i].counter;
	}
}

void openFile(const string& whichFile, ifstream& inFile){
    string fName;
    cout << "Please enter a filename for " << whichFile << " file: ";
    cin >> fName;
    inFile.open(fName.c_str());
    while (inFile.fail()){
        cout << "Can not find the specified file." << endl;
        cout << "Please enter a filename for " << whichFile << " file: ";
        cin >> fName;
        inFile.open(fName.c_str());
    }
}

int main(){
	ifstream file1, file2;
	string s1 = "Series-Actor";
	string s2 = "Rating";
	cout << "Welcome to Netflix TV Series Ratings Calculator!" << endl;
	openFile(s1, file1);
	openFile(s2, file2);
	vector<structt> liste;
	readFile1(file1, liste);
	for (int i = 0; i < liste.size(); i++)
	{
		liste[i].rating = -5;
	}
	readFile2(file2, liste);
	sort(liste.begin(), liste.end(), &Comparison);
	MainMenu(liste);
	file1.close();
    file2.close();
	return 0;
}