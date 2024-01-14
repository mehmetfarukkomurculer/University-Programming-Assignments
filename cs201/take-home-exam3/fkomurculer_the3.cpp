#include <iostream>
#include <string>
using namespace std;

//created by Mehmet Faruk Komurculer

void CreateSourceInput(string s2, string& s3)
{
	s3 = "";
	while ( s2 != "END" && s2 != "end")
	{
		s3 += s2 + " ";
		cin >> s2;
	}
}
bool CheckSourceInput(string s1) 
{
	int length = s1.length();
	s1.erase(length-1,1);
	int new_length = s1.length();
	int k = 0;
	int k2 = 0;
	for (int i = 0; i < new_length; i++)
	{
		if ((int)s1[i] == 32 || ( (int)s1[i] >= 48 && (int)s1[i]<=57 ) || ( (int)s1[i] >=65 && (int)s1[i] <=90 ) || ( (int)s1[i] >=97 && (int)s1[i] <=122 ))
		{
			k++;
		}
		else
		{
			k2++;
		}	
	}
	if (k2 > 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}
int WordsAndIndexes(string s6, string s7) 
{
	string new_s7;
	string s8 = "";
	int substridx;
	int count1 = 0;
	int x6 = s6.length();
	int x7 = s7.length();
	if (s7.substr(x7-1,1) == "+")
	{
		new_s7 = s7.substr(0,x7-1);
		for (int w = 0; w < x6; w++)
		{
			substridx = s6.find(new_s7, w);
			if (substridx != -1 && s6.find(new_s7, w) != s6.find(new_s7, w+1))
			{
				int l1 = new_s7.length();
				int bosluk1 = s6.rfind(" ",w);
				int bosluk2 = s6.find(" ",w);
				string bulunan_kelime = s6.substr(bosluk1+1, bosluk2-bosluk1-1);
				if (w == 0 || bosluk1+1 == w)
				{
					cout << "index: " << w << " word: " << bulunan_kelime << endl;
					count1++;
				}
			}
		}
	}
	else if (s7.substr(x7-1,1)  == ".")
	{
		new_s7 = s7.substr(0,x7-1);
		for (int w = 0; w < x6; w++)
		{
			substridx = s6.find(new_s7, w);
			if (substridx != -1 && s6.find(new_s7, w) != s6.find(new_s7, w+1))
			{
				int l1 = new_s7.length();
				int bosluk1 = s6.rfind(" ",w);
				int bosluk2 = s6.find(" ",w);
				string bulunan_kelime = s6.substr(bosluk1+1, bosluk2-bosluk1-1);
				if (new_s7.length() + w == bosluk2)
				{
					cout << "index: " << w << " word: " << bulunan_kelime << endl;
					count1++;
				}
			}
		}
	}
	else if (s7.substr(x7-2,2) != "**" && s7.substr(x7-1,1)  == "*")
	{
		new_s7 = s7.substr(0,x7-1);
		for (int w = 0; w < x6; w++)
		{
			substridx = s6.find(new_s7, w);
			if (substridx != -1 && s6.find(new_s7, w) != s6.find(new_s7, w+1))
			{
				int l1 = new_s7.length();
				int bosluk1 = s6.rfind(" ",w);
				int bosluk2 = s6.find(" ",w);
				string bulunan_kelime = s6.substr(bosluk1+1, bosluk2-bosluk1-1);
				if ( (w > bosluk1+1 && w < bosluk2-1) && bosluk2-1 != w && w != 0 && bosluk1+1 != w && new_s7.length() + w != bosluk2)
				{
					if (bulunan_kelime.substr(0,l1) != new_s7 && bulunan_kelime.substr(bulunan_kelime.length()-l1, l1) != new_s7)
					{
						cout << "index: " << w << " word: " << bulunan_kelime << endl;
						count1++;
					}
				}
			}
		}
	}
	else if (s7.substr(x7-2,2) == "**")
	{
		new_s7 = s7.substr(0,x7-2);
		for (int w = 0; w < x6; w++)
		{
			substridx = s6.find(new_s7, w);
			if (substridx != -1 && s6.find(new_s7, w) != s6.find(new_s7, w+1))
			{
				int l1 = new_s7.length();
				int bosluk1 = s6.rfind(" ",w);
				int bosluk2 = s6.find(" ",w);
				string bulunan_kelime = s6.substr(bosluk1+1, bosluk2-bosluk1-1);
				cout << "index: " << w << " word: " << bulunan_kelime << endl;
				count1++;
			}
		}
	}
	return count1;
}
int main()
{
	string word, word2;
	string main_string;
	cout << "Enter source string: ";
	cin >> word;
	CreateSourceInput(word, main_string);
	while (!(CheckSourceInput(main_string)))
	{
		cout << "Enter source string: ";
		cin >> word;
		CreateSourceInput(word, main_string);
		if ((CheckSourceInput(main_string)))
		{
			break;
		}
	}
	cout << "Enter search string: ";
	cin >> word2;
	while (word2 != "quit" && word2 != "QUIT")
	{
		(WordsAndIndexes(main_string, word2));
		cout << "Enter search string: ";
		cin >> word2;
	}
	return 0;
}