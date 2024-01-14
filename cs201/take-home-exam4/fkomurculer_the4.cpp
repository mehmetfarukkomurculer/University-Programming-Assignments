
#include <string>
#include <fstream>

#include <iostream>
#include "strutils.h"

using namespace std;
#include <sstream>


void OutputAdd (string  word, string posCor)
{
	if  (posCor != "" )
	{		
		if( posCor.find( "," )	== string::npos )
		{
			cout  << posCor;
		}
		else
		{
			cout  << "(";
			cout  << posCor << ")";
		}			
	}
	else
	{
		cout  << "{"  << word;
		cout  << "}";
	}
}

void Checkingspell ( ifstream&  wrdPlFl,string word)
{
	wrdPlFl.clear();
	wrdPlFl.seekg(0);
	int ind;

	string  dLine2;
	int  mis;

	string  plWrd;
	int  curMis;

	string  posCor;		
	mis  = 15;

	while( getline(wrdPlFl ,dLine2))
	{		
		istringstream  stringSt ( dLine2 );
		while ( stringSt >>	plWrd)
		{
			ToLower ( plWrd );	

			if (plWrd.length()	== word.length())				
			{
				curMis	= 0;
				int  i = 0;
				while  ( i < plWrd.length())
				{
					if( plWrd.at(i)	!=  word.at(i))
					{
						curMis++;
					}
					i+= 1;
				}
				if	(curMis	<= (double(word.length()) / 2 ) ) 				
				{
					if 	(curMis == mis )
					{	
						if (posCor.find(plWrd) == string::npos)
						{
							posCor = posCor + plWrd + ",";
						}									
					}
					else if	( curMis< mis)
					{				
						posCor = plWrd +  ",";		
						mis = 	curMis;
					}
				}
			}				
		}
	}

	if (posCor != "")
	{
		int len = posCor.length();
		posCor  = posCor.substr(0, len - 1);
	}		
	OutputAdd (word, posCor);	
}


void LookFiles( string wrdPlFlName , string txtFlName)

{
	ifstream wrdPlFl,txtFl;

	string dLine ,word;
	
	wrdPlFl.open( wrdPlFlName);

	txtFl.open( txtFlName);	

	while (getline( txtFl,dLine ))
	{
		int cnt = 1;
		istringstream stringSt (dLine);
		while ( stringSt >> word)
		{
			ToLower	(word);
			if (cnt > 1)
			{
				cout << " ";
			}				
			Checkingspell( wrdPlFl,word) ;
			cnt += 1;
		}
		cout << endl;	

	}
	wrdPlFl.close();

	txtFl.close();	
	
}

int main()
{
	string  wrdPlFlName;
	string 	txtFlName;
	bool  res = 0;
	cout << "Please enter a filename for the word pool: ";
	cin  >>	wrdPlFlName;

	while( res == false )
	{
		ifstream fl;
		fl.open (wrdPlFlName );
		if ( fl.fail() ==  true)
		{
			res =  false;
		}			
		else
		{	
			fl.	close();
			res =  true;
		}
		if 	(res == false )
		{
			cout  << "Cannot open the word pool file.";
			cout  << endl;

			cout  << "Please enter a filename for the word pool: ";
			cin   >> wrdPlFlName;	
		}
	}	
	res =  false;
	cout <<  "Please enter a filename for the main text: ";
	cin >>  txtFlName;

	while ( res == 0 )
	{
		ifstream fl;
		fl.open (txtFlName );
		if (fl.fail() == true)
		{
			res = 0;
		}			
		else
		{
			fl.close();
			res = 1;
		}
		if ( res ==  false )
		{
			cout <<  "Cannot open the main text file.";
			cout <<  endl;

			cout <<	 "Please enter a filename for the main text: ";
			cin  >>  txtFlName;	

		}
	}	

	cout  <<  "You may find the results below:";

	cout  << endl <<  endl;

	LookFiles (  wrdPlFlName ,txtFlName);

	return 0;
}
