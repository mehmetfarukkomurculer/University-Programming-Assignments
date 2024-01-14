#include <iostream>
#include <iomanip>
#include <string>
#include "strutils.h"

using namespace std;

// created by Mehmet Faruk Komurculer


bool CheckInput(string colour1, string colour2)
{
	ToLower (colour1);
	ToLower (colour2);
	if (colour1 == colour2)
	{
		return true;
	}
	else
	{
		return false;
	}	
}
void CheckCubeandDisplay(string s3, double x1, double x2, double x3)
{
	
	if (x3 < x2 ||x3 < x1 || x2 < x1 || x2 < x3 || x1 < x3 || x1 < x2 )
	{
		cout << s3 << " cuboid is not a cube." << endl;
	}
	else
	{
		cout << s3 << " cuboid is a cube." << endl;
	}
}
void Display(string s4, double x7, double x8)
{
	cout << "Results for the " << s4 << " cuboid:" << endl;
	cout << "Area: " << x7 << endl;
	cout << "Volume: " << x8 << endl;
}
void Calculation(string s5, double x4, double x5, double x6, double& x_area, double& x_volume)
{
	x_area =  (x4 * x5 * 2) + (x5 * x6 * 2) + (x4 * x6 * 2);
	x_volume = x4 * x5 * x6;
	Display(s5, x_area, x_volume);
	CheckCubeandDisplay(s5, x4, x5, x6);
}
string Comparison(string s6, string s7, double alan1, double alan2, double hacim1, double hacim2)
{
	cout << "Comparison of the two cuboids:" << endl;
	if (alan1 == alan2 & hacim1 == hacim2)
	{
		cout << "Two cuboids have the same volume." << endl;
		cout << "Two cuboids have the same area." << endl;
		return "";
	}
	else if (alan1 > alan2 & hacim1 == hacim2)
	{
		cout << "Two cuboids have the same volume." << endl;
		cout << s6 << " has the largest area." << endl;
		return "";
	}
	else if (alan1 < alan2 & hacim1 == hacim2)
	{
		cout << "Two cuboids have the same volume." << endl;
		cout << s7 << " has the largest area." << endl;
		return "";
	}
	else if (alan1 == alan2 & hacim1 > hacim2)
	{
		cout << s6 << " has the largest volume." << endl;
		cout << "Two cuboids have the same area." << endl;
		return "";
	}
	else if (alan1 == alan2 & hacim1 < hacim2)
	{
		cout << s7 << " has the largest volume." << endl;
		cout << "Two cuboids have the same area." << endl;
		return "";
	}
	else if (alan1 > alan2 & hacim1 > hacim2)
	{
		cout << s6 << " has the largest volume." << endl;
		cout << s6 << " has the largest area." << endl;
		return "";
	}
	else if (alan1 > alan2 & hacim1 < hacim2)
	{
		cout << s7 << " has the largest volume." << endl;
		cout << s6 << " has the largest area." << endl;
		return "";
	}
	else if (alan1 < alan2 & hacim1 > hacim2)
	{
		cout << s6 << " has the largest volume." << endl;
		cout << s7 << " has the largest area." << endl;
		return "";
	}
	else if (alan1 < alan2 & hacim1 < hacim2)
	{
		cout << s7 << " has the largest volume." << endl;
		cout << s7 << " has the largest area." << endl;
		return "";
	}
}
int main()
{
	cout.setf(ios::fixed);
	cout.precision(2);

	string colorI, colorII;
	double l1, w1, h1, l2, w2, h2;
	double area1, area2, volume1, volume2;
	cout << "Hello! This program compares two cuboids..." << endl;
	cout << "Please enter colors for the two cuboids: ";
	cin >> colorI >> colorII;
	if (CheckInput(colorI, colorII))
	{
		cout << "Color names cannot be the same, good bye..." << endl;
	}
	else
	{
		cout << "Please enter length, width and height of the " << colorI << " cuboid: ";
		cin >> l1 >> w1 >> h1;
		if (l1 == -92559631349317830000000000000000000000000000000000000000000000.00 || w1 == -92559631349317830000000000000000000000000000000000000000000000.00 || h1 == -92559631349317830000000000000000000000000000000000000000000000.00)
		{
			cout << "Invalid entry for " << colorI << " cuboid. Dimensions should be positive real numbers!" << endl;
		}
		else if (l1 <= 0 || w1 <= 0 || h1 <= 0)
		{
			cout << "Invalid entry for " << colorI << " cuboid. Dimensions should be positive real numbers!" << endl;
		}
		else
		{
			cout << "Please enter length, width and height of the " << colorII << " cuboid: ";
			cin >> l2 >> w2 >> h2;
			if (l2 == -92559631349317830000000000000000000000000000000000000000000000.00 || w2 == -92559631349317830000000000000000000000000000000000000000000000.00 || h2 == -92559631349317830000000000000000000000000000000000000000000000.00)
			{
			cout << "Invalid entry for " << colorII << " cuboid. Dimensions should be positive real numbers!" << endl;
			}
			else if (l2 <= 0 || w2 <= 0 || h2 <= 0)
			{
			cout << "Invalid entry for " << colorII << " cuboid. Dimensions should be positive real numbers!" << endl;
			}
			else
			{
				Calculation(colorI, l1, w1, h1, area1, volume1);
				cout << "" << endl;
				Calculation(colorII, l2, w2, h2, area2, volume2);
				cout << "" << endl;
				Comparison(colorI, colorII, area1, area2, volume1, volume2);
			}
		}
	}
	return 0;
}