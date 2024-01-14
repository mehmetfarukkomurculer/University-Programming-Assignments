
#include <vector>
#include <fstream>

#include "strutils.h"
#include "favoriteseries.h"

#include <iostream>
#include <sstream>

using namespace std;

void FileParsing( vector <series>  & seriesAll,  vector  <episode>& episodesAll)

{
	ifstream sFile;	
	string currentLine,code, name;

	int dy, mth;

	string c_nm, word;
	int inx;

	string  aName ;

	string strDate ,  slTime;
	ifstream eFile;

	string  epiCode;
	string epiName;
	
	int  yr;
	sFile.open ("series.txt");

	while  (getline(sFile , currentLine))
	{		
		code =  "";
		name =  "";			
		inx =  currentLine.find(";");
		vector <episode> episodes;

		c_nm  = currentLine.substr(0, inx);
		istringstream iss (c_nm);
		iss >>  code;

		while ( iss >> word)
			name = name + word + " ";

		vector<string> aNames;
		name =  name.substr( 0, name.length()-1);

		ToUpper(name);
		currentLine =  currentLine.substr(inx+1 , currentLine.length() );	
		
		while ( currentLine.find("," ) != string::npos)
		{
			aName = "";
			inx = currentLine.find(",");

			istringstream  issS( currentLine.substr( 0, inx));
		
			while ( issS >>  word)			
				aName =  aName + word  + " ";
			
			aName= aName.substr( 0, aName. length()-1) ;
			ToUpper(aName);

			aNames.push_back(aName);
			currentLine = currentLine.substr( inx+1 , currentLine.length() );

		}
		istringstream  issT(currentLine);
		aName =  "";
		while ( issT >>word )		
			aName += word+" ";
		
		aName= aName.substr( 0,aName.length()-1);
		ToUpper(aName);
		aNames.push_back(aName);
		
		eFile.open( "episodes.txt" );	
		while ( getline( eFile, currentLine) )
		{
			istringstream issF(currentLine);
			issF >>epiCode;

			issF >>strDate;
			issF >>slTime;

			epiName ="";
			while (issF >>word)			
				epiName += word+" ";
			
			epiName = epiName.substr( 0,  epiName.length()-1) ;
			ToUpper(epiName);
			ToUpper(slTime);

			inx= strDate.find( "/" );
			mth= atoi( strDate.substr(0 , inx));

			strDate = strDate.substr( inx+1,strDate.length());
			inx= strDate.find( "/" );

			dy= atoi( strDate.substr(0 ,inx));

			strDate = strDate.substr(inx+1 ,strDate.length());
			yr = atoi (strDate );

			Date myDate ( mth , dy, yr);

			episode  epi;
			epi.episodeName = epiName;
			epi.slot = slTime;

			epi.seriesCode = atoi (epiCode );
			epi.date =  myDate;
		
			if ( epiCode==code)
			{
				episodes.push_back(epi);
				episodesAll.push_back(epi);
			}
		}

		eFile.close();

		series serie ;
		serie.seriesName= name;
		serie.episodes = episodes;

		serie.seriesCode= atoi(code);
		
		serie.actorNames =aNames;

		seriesAll.push_back(serie);
	}

	sFile.close();	
}

void InputMenu()

{
	cout <<"---" << endl <<"MENU" <<endl;
	cout << "1. Print all TV series" <<endl;

	cout <<"2. Add TV series"<< endl;

	cout <<"3. Drop TV series"<< endl << "4. Print your favorite series with schedule"<< endl;
	cout << "5. Print all your favorite actors" <<endl;

	cout <<"6. Exit" << endl << "---" <<endl;

	cout <<  "Please enter your choice: ";
}

void  ListPrint( vector < series > seriesAll,vector  < episode > episodesAll)
{
	int i;
	int j;
	cout << "CODE,SERIES,EPISODE,DATE,SLOT"  << endl;

	for ( i = 0; i < episodesAll.size(); i= i+1 )
	{
		string seriesName;

		for ( j = 0;  j < seriesAll.size(); j=j+1 )
		{
			if ( seriesAll[j].seriesCode ==  episodesAll[i].seriesCode )
			{
				seriesName= seriesAll[j].seriesName;
			}
		}

		cout <<  episodesAll[i].seriesCode;
		cout << "," << seriesName  << "," << episodesAll[i].episodeName<< ",";
		cout  <<episodesAll[i].date.MonthName()<< " "  << episodesAll[i].date.Day()<<  " " << episodesAll[i].date.Year()  <<  ","<< episodesAll[i].slot <<endl;
	}
}

void AddToFavorites ( vector < series > seriesAll, vector < episode > episodesAll, FavoriteSeries & favs)
{
	bool favEx ;
	int codeAdd,i;

	series serie;
	favEx = false;

	cout  <<"Enter code for the TV series you want to add: ";
	cin  >>codeAdd;

	for ( i = 0; i < seriesAll.size(); i = i+1)
	{
		if ( seriesAll[i].seriesCode ==  codeAdd)
		{
			serie =  seriesAll[i];
			favEx =  true;
		}
	}

	if ( ! favEx)
	{
		cout<<  favs.getFullName()<<  ", there is no such TV series in the database!"<<  endl;
	}
	else if( favs.ifExists(codeAdd) )
	{
		cout <<  favs.getFullName()<< ", you can't add this TV series because you already added it!" <<endl;
	}
	else if( favs.isConflict(serie) )
	{
		cout  <<favs.getFullName()<<  ", you can't add this TV series because of a date and slot conflict!" <<endl;
	}
	else 
	{
		favs.addSeries( serie );
		cout<<  favs.getFullName()<< ", "  << serie.seriesName <<  " added to your schedule."  <<endl;
	}
}

void  FavDrop (vector < series > seriesAll, FavoriteSeries & favs)
{
	string seriesName;

	int codeD;
	
	if ( favs.isListEmpty() )
	{
		cout<< favs.getFullName()<<  ", you did not add any TV series yet!"<< endl;
	}
	else
	{
		cout << "Enter code for the TV series you want to drop: ";
		cin >>  codeD;

		if ( ! favs.ifExists(codeD))
		{
			cout << favs.getFullName();
			cout  << ", there is no such TV series in your favorite list!" <<endl;
		}
		else
		{	
			int i;
			for ( i= 0; i  < seriesAll.size(); i+=1 )
			{
				if(seriesAll[i].seriesCode  == codeD )
				{
					seriesName= seriesAll[i].seriesName;
				}
			}
			favs.dropSeriesSorted(codeD);

			cout <<favs.getFullName() << ", " <<seriesName;
			cout << " has been dropped from your favorite list!" <<endl;
		}
	}
}

void FavPrint( vector < series > seriesAll, vector < episode > episodesAll , FavoriteSeries & favs)
{
	string seriesName;
	int i;
	int j;
	
	if(favs.isListEmpty( ))
	{
		cout <<favs.getFullName()<< ", you did not add any TV series yet!" <<endl;
	}
	else
	{
		cout <<favs.getFullName() <<", here is your favorite TV series:" <<endl;
		cout <<"CODE,SERIES,EPISODE,DATE,SLOT" <<endl;

		for (i = 0;  i < episodesAll.size(); i+=1 )
		{			
			for ( j = 0; j < seriesAll.size(); j= j+1 )			
				if  (seriesAll[j].seriesCode  == episodesAll[i].seriesCode )				
					seriesName= seriesAll[j].seriesName;			
			
			if (favs.ifExists(episodesAll[i].seriesCode))			
				cout << episodesAll[i].seriesCode << "," << seriesName 
				<< "," <<  episodesAll[i].episodeName << "," 
				<<episodesAll[i].date.MonthName() << " "  << episodesAll[i].date.Day() 
				<<" " <<  episodesAll[i].date.Year()  << "," << episodesAll[i].slot  << endl;			
		}
	}
}

void ActorShow( FavoriteSeries & favs )
{
	if(favs.isListEmpty() )
	{
		cout <<favs.getFullName() 
			<<", you did not add any TV series yet!" <<endl;
	}
	else
	{
		cout <<favs.getFullName() 
			<<", here is your favorite actors:" <<endl;

		favs.displayFavoriteActors();
	}
}

int main ()

{   		
	string name;
	string surname;

    vector <series> seriesAll;
	int s1;
	int s2;

    vector <episode> episodesAll;
	int inp = 0;
	episode epiTmp;

	int j, k, mIndex;
	int len;

	
	FileParsing(seriesAll, episodesAll);

	len = episodesAll.size();

	for ( k = 0; k  < len-1; k = k+ 1)
	{
		mIndex = k;
		for (j = k + 1; j < len; j = j + 1)
		{

			if (episodesAll[j].slot == "MORNING")
				s1 = 0;
			if (episodesAll[j].slot == "AFTERNOON")
				s1 = 1;
			if (episodesAll[j].slot == "EVENING")
				s1 = 2;
			if (episodesAll[j].slot == "NIGHT")
				s1 = 3;
			if (episodesAll[mIndex].slot == "MORNING")
				s2 = 0;
			if (episodesAll[mIndex].slot == "AFTERNOON")
				s2 = 1;
			if (episodesAll[mIndex].slot == "EVENING")
				s2 = 2;
			if (episodesAll[mIndex].slot == "NIGHT")
				s2 = 3;

			if(episodesAll[j].date <  episodesAll[mIndex].date)
				mIndex= j;
			else if( episodesAll[j].date==episodesAll[mIndex].date
				&& s1<s2)
				mIndex= j;
			else if(episodesAll[j].date == episodesAll[mIndex].date
				&& s1 == s2 && episodesAll[j].seriesCode < episodesAll[mIndex].seriesCode)
				mIndex= j;
		}

		epiTmp =episodesAll[k];
		episodesAll[k] =  episodesAll[mIndex];
		episodesAll[mIndex]= epiTmp;
	}

	cout <<"Welcome to my favorite TV series schedule program!"<<endl;
    cout << "Please, enter your name and surname: " ;
	cin >> name;

	cin >> surname;
    ToUpper(name);
    ToUpper(surname);

    FavoriteSeries favs( name , surname);   
	
	while (inp != 6)
    {
		InputMenu();
        cin >> inp;
		if (inp== 1)
			ListPrint(seriesAll , episodesAll);
		if (inp== 2)
			AddToFavorites(seriesAll , episodesAll , favs);
		if (inp== 3)
			FavDrop(seriesAll, favs);
		if (inp== 4)
			FavPrint(seriesAll , episodesAll , favs);
		if (inp== 5)
			ActorShow( favs );
        if (inp== 6)        
            cout << "Goodbye, "<< name << " " << surname<< "!" <<endl;        
        if (inp != 1 && inp != 2 && inp != 3 && inp != 4 && inp != 5 && inp != 6  )
            cout <<"Invalid option!"<< endl;        
    }   
    return 0;    
}


