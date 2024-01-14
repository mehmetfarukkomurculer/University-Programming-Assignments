#ifndef favoriteseriest_h
#define favoriteseries_h

/******************************************************************** 

 Models a user watching TV Series in a particular schedule 

 This code is freely distributable and modifiable providing you
 leave this notice in it.

 Copyright @ Anil

********************************************************************/


#include <iostream>
#include <string>
#include <vector>
#include "date.h"
using namespace std;

struct actor
{
    string acNm;
    int ct;

};

struct episode 
{
	string episodeName;
	int seriesCode;
	Date date;
	string slot;
};

struct series
{
    string seriesName;
    int seriesCode;
    vector<episode> episodes;
	vector<string> actorNames;
};


class FavoriteSeries
{
	public:
		FavoriteSeries(string, string);		// constructor with parameter
    
		string getFullName() const;			// returns the full name (name&surname) of the user 
		void addSeries(const series &);		// add a TV series to the favorite list
		bool ifExists(int seriesCode);		// check if a series is in the favorite list or not
		bool isListEmpty() const;			// return trues if the favorite list is empty
		void dropSeriesSorted(int);			// drops the TV series with the given TV series code 
											// from the vector (favSeries) while keeping the vector sorted
		void displayFavoriteList() const;		// displays the favorite TV series list
		void displayFavoriteActors() const;		// calculates and displays the sorted favorite actors list
		bool isConflict(const series &) const;	// returns true if a given TV series has a time conflict
												// with another series from the user's schedule
			 // time conflict means same date and same time slot among (morning, afternoon, evening, night)
		
		// if needed you may add more functions here

	private:
		string userName;
		string userSurname;
		vector<series> favSeries;
};
FavoriteSeries :: FavoriteSeries(string name, string surname)
{
    userName = name;
    userSurname = surname;
}

void Sort(vector<actor> & actors)
{
	actor acTmp;
	int j, k;
	int m;
	int n;

	n = actors.size();

	for (k = 0; k < n - 1; k += 1)
	{
		m = k;
		for (j = k + 1; j < n; j += 1)
		{
			if (actors[j].ct  > actors[m].ct)
				m = j;
			else if (actors[j].ct == actors[m].ct  && actors[j].acNm  < actors[m].acNm)
				m = j;
		}

		acTmp = actors[k];

		actors[k] = actors[m];

		actors[m] = acTmp;

	}
}

string FavoriteSeries::getFullName()  const
{
    return  userName+ " "+userSurname;
}

void FavoriteSeries::addSeries( const series &  serie)

{
    favSeries.push_back(serie);
}


bool FavoriteSeries::  isListEmpty()  const
{
    if ( favSeries.size() ==  0 ) 
    {
        return  true ;
    }
    else
    {
        return false ;
    }
}

void FavoriteSeries::dropSeriesSorted ( int serieCode )
{
	int i;
	i = 0;
    vector <series>  serTmp;
    while  ( i < favSeries.size() )
    {
        if(  favSeries[i].seriesCode !=  serieCode)
        {
            serTmp.push_back( favSeries[i]);
        }
		i +=  1;
    }

    favSeries  = serTmp;
}

bool FavoriteSeries::ifExists(int seriesCode)
{
	int i = 0;
	while (i < favSeries.size())
	{
		if (favSeries[i].seriesCode == seriesCode)
		{
			return  true;
		}
		i += 1;
	}

	return  false;
}

bool FavoriteSeries::isConflict(const   series & serie)  const
{
	int i;
	int j;
	int k;

	for (i = 0; i < favSeries.size(); i = i + 1)
	{
		for (j = 0; j < favSeries[i].episodes.size(); j += 1)
		{
			for (k = 0; k < serie.episodes.size(); k++)
			{
				if (serie.episodes[k].date.Day() == favSeries[i].episodes[j].date.Day() &&
					serie.episodes[k].date.Month() == favSeries[i].episodes[j].date.Month() && serie.episodes[k].date.Year() == favSeries[i].episodes[j].date.Year() && serie.episodes[k].slot == favSeries[i].episodes[j].slot)
				{
					return  true;
				}
			}
		}
	}
	return false;
}

void  FavoriteSeries:: displayFavoriteList()  const
{
	int i;
	int j; 

    cout  << userName  << " " <<  userSurname <<  ", here is your favorite TV series:" <<  endl;

    cout <<  "CODE,SERIES,EPISODE,DATE,SLOT" <<  endl;

    for (  i = 0 ; i < favSeries.size(); i = i + 1 )
    {
        for ( j = 0 ; j < favSeries[i].episodes.size(); j = j+1 )
        {
			cout << favSeries[i].seriesCode;

			cout << ", " << favSeries[i].seriesName << ", " <<  favSeries[i].episodes[j].episodeName;

			cout << ","  <<  favSeries[i].episodes[j].date.ToString()  << "," <<   favSeries[i].episodes[j].slot << endl;
        }
    }
}



void  FavoriteSeries::displayFavoriteActors()  const
{
	int i;
	int j;
	int k;
	bool foundList;
    vector <actor> actors;

    for ( i = 0; i < favSeries.size() ; i+= 1 )
    {
		string acNm;
		j = 0;
        while  ( j < favSeries[i].actorNames.size())
        {
			foundList = false;
            acNm = favSeries[i].actorNames[j];
         
            for ( k = 0; k <  actors.size(); k++ )
            {
                if ( actors[k].acNm  == acNm)
                {
                    actors[k].ct++;
                    foundList =  true;
                    
                }
            }

            if ( foundList !=  true)
            {
                actor act;
				act.acNm =  acNm;

				act.ct =  1;
                actors.push_back(act);

            }
			j = j + 1;
        }
    }

    Sort( actors);

    for (i = 0 ; i < actors.size() ; i++ )    
        cout <<  actors[i].acNm  << ": "  << actors[i].ct  << endl;
    
}



#endif
