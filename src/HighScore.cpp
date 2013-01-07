#include "Highscore.h"
#include <iostream>
#include <fstream>
#include <string>

// @date 2012-08-07

using namespace std;

// reads the list and sorts it
FillHighScore::FillHighScore()
{
	// Reset the highscore array
	int ArraySize = sizeof(list) / sizeof(list[0]);
	for( int i = 0; i < ArraySize; i++ )
	{
		list[ i ].name = "";
		list[ i ].Score = 0;
	}

	// Read information from highscore file into highscore array 
	ReadHighscoreFile();
/*
	for( int i = 0; i < 6; i++ )
	{
		for( int j = 0; j < 6; j++ )
		{
			if( list[ i ].Score > list[ j ].Score )
			{
				string temp;
				temp = list[ i ].name;
				list[ i ].name = list[ j ].name;
				list[ j ].name = temp;
				swap( list[ i ].Score, list[ j ].Score );
			}
		}
	}
	*/
}

void FillHighScore::ReadHighscoreFile()
{
	ifstream infile( "Highscore.txt" );

	for( int i = 0; i < 6 && infile && infile.peek() != EOF; i++)
	{
		infile >> list[ i ].name;
		infile >> list[ i ].Score;
	}
}

void FillHighScore::Save()
{
	ofstream ofile("Highscore.txt");	
										
	int ArraySize = sizeof(list) / sizeof(list[0]);
	for( int i = 0; i < ArraySize; i++ )
	{
		ofile << list[ i ].name << endl;
		ofile << list[ i ].Score << endl;
	} 
}


void FillHighScore::sort( string a, unsigned long int x )
{
	if( x > list[ 5 ].Score )// if score is bigger
	{
		list[ 5 ].Score = x;
		list[ 5 ].name = a;	// the last one in the list gets value
	}

	for( int i = 0; i < 5; i++ )
	{
		if(list[ i ].Score < list[ i+1 ].Score)
		{
			string temp = list[ i+1 ].name;
			list[ i+1 ].name = list[ i ].name;	
			list[ i ].name = temp;

			swap( list[ i+1 ].Score, list[ i ].Score );
		}
	}	
}