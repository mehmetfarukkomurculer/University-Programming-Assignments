#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;
// mehmet faruk komurculer

void Print(const vector<vector<string>> &strMatrix)
// this prints matrix.
{
	for (int j = 0; j < strMatrix.size(); j++)
	{ 
		for (int k = 0; k < strMatrix[0].size(); k++)
		{
			cout << setw(3) << strMatrix[j][k];
		}
		cout << endl;
	}
}

int CheckInput (int row, int column, string direction, string orientation, int &startingRow, int &startingColumn)
// this checks 2 things.  1-whether starting row and column are in the range or not, 2-whether direction and orientation are given in the correct format 
// if there is not an error, returns -5, else returns 1,2 or 3 depending on the type of error
{
	if (startingRow < 0 || startingRow > row || startingRow == row ||startingColumn < 0 || startingColumn > column || startingColumn == column)
	{
		return 1;
	}
	else if (direction != "r" && direction != "l" && direction != "d" && direction != "u") 
	{
		return 2;
	}
	else if (orientation != "CW" && orientation != "CCW")
	{
		return 3;
	}
	else
	{
		return -5;
	}
}

int Placement_rCW(string word, int startingRow, int startingColumn, int row, int column, vector<vector<string>> &strMatrix, string direction, string orientation)
// placement of the word when the direction is r, and orientation is CW
// this returns 0,if the word is put succesfully.  
// else returns 1. 
{
	int index = 0;
	int controlcount = 0;
	int returncount = 0;
	while (index < word.length())
	{
		if (strMatrix[startingRow][startingColumn] == "-" && (startingColumn <= column-1 && startingColumn >= 0) && (startingRow <= row-1 && startingRow >= 0))
		{ 
			strMatrix[startingRow][startingColumn] = word.at(index);
			index++;
			if (startingColumn + 1 < column && strMatrix[startingRow][startingColumn+1] == "-")
			// always checks right direction. Therefore after every placement of a letter of the word, starting column will be increased +1
			{
				startingColumn++;
			}
			else
			{
				controlcount++;
			}
		}
		else
		{
			if (startingRow + 1 < row && strMatrix[startingRow+1][startingColumn] == "-" && controlcount == 1)
			// if the function is here, that means right is not empty or column value +1 at current position is equal to column value of the matrix
			// here, down position is checked. 
			{
				controlcount = 0;
				startingRow++;
				strMatrix[startingRow][startingColumn] = word.at(index);
				index++;
				if (startingColumn + 1 < column && strMatrix[startingRow][startingColumn+1] == "-")
				{
					startingColumn++;
				}
				else
				{
					controlcount++;
				}
			}	
			else
			{
				if (startingColumn - 1 >= 0  && strMatrix[startingRow][startingColumn-1] == "-" && controlcount == 1)
				// here left position is checked. 
				{
					controlcount = 0;
					startingColumn--;
					strMatrix[startingRow][startingColumn] = word.at(index);
					index++;
					if (startingColumn + 1 < column && strMatrix[startingRow][startingColumn+1] == "-")
					{
						startingColumn++;
					}
					else
					{
						controlcount++;
					}	
				}	
				else
				{
					if (startingRow - 1 >= 0  && strMatrix[startingRow-1][startingColumn] == "-" && controlcount == 1)
					// here, up position is checked. 
					{
						controlcount = 0;
						startingRow--;
						strMatrix[startingRow][startingColumn] = word.at(index);
						index++;
						if (startingColumn + 1 < column && strMatrix[startingRow][startingColumn+1] == "-")
						{
							startingColumn++;
						}
						else
						{
							controlcount++;
						}
					}
					else
					{
						// if a letter of the word enters here, that means there is no empty position to be filled
						returncount++;
						break;
						// since a letter is could not put into the matrix, execution is broken. 
					}
				}
			}
		}
	}
	if (returncount == 1)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}


int Placement_rCCW(string word, int startingRow, int startingColumn, int row, int column, vector<vector<string>> &strMatrix, string direction, string orientation)
// placement of the word when the direction is r, and orientation is CCW
// this returns 0,if the word is put succesfully.  
// else returns 1. 
{
	int index = 0;
	int controlcount = 0;
	int returncount = 0;
	while (index < word.length())
	{
		if (strMatrix[startingRow][startingColumn] == "-" && (startingColumn <= column-1 && startingColumn >= 0) && (startingRow <= row-1 && startingRow >= 0))
		{ 
			strMatrix[startingRow][startingColumn] = word.at(index);
			index++;
			if (startingColumn + 1 < column && strMatrix[startingRow][startingColumn+1] == "-")
			{
				startingColumn++;
			}
			else
			{
				controlcount++;
			}
		}
		else
		{
			if (startingRow - 1 >= 0  && strMatrix[startingRow-1][startingColumn] == "-" && controlcount == 1)
			{
				controlcount = 0;
				startingRow--;
				strMatrix[startingRow][startingColumn] = word.at(index);
				index++;
				if (startingColumn + 1 < column && strMatrix[startingRow][startingColumn+1] == "-")
				{
					startingColumn++;
				}
				else
				{
					controlcount++;
				}
			}
			else
			{
				if (startingColumn - 1 >= 0  && strMatrix[startingRow][startingColumn-1] == "-" && controlcount == 1)
				{
					controlcount = 0;
					startingColumn--;
					strMatrix[startingRow][startingColumn] = word.at(index);
					index++;
					if (startingColumn + 1 < column && strMatrix[startingRow][startingColumn+1] == "-")
					{
						startingColumn++;
					}
					else
					{
						controlcount++;
					}	
				}	
				else
				{
					if (startingRow + 1 < row && strMatrix[startingRow+1][startingColumn] == "-" && controlcount == 1)
					{
						controlcount = 0;
						startingRow++;
						strMatrix[startingRow][startingColumn] = word.at(index);
						index++;
						if (startingColumn + 1 < column && strMatrix[startingRow][startingColumn+1] == "-")
						{
							startingColumn++;
						}
						else
						{
							controlcount++;
						}
					}	
					else
					{
						returncount++;
						break;
					}
				}
			}
		}
	}
	if (returncount == 1)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

int Placement_lCW(string word, int startingRow, int startingColumn, int row, int column, vector<vector<string>> &strMatrix, string direction, string orientation)
// placement of the word when the direction is l, and orientation is CW
// this returns 0,if the word is put succesfully.  
// else returns 1. 
{
	int index = 0;
	int controlcount = 0;
	int returncount = 0; 
	while (index < word.length())
	{
		if (strMatrix[startingRow][startingColumn] == "-" && (startingColumn <= column-1 && startingColumn >= 0) && (startingRow <= row-1 && startingRow >= 0))
		{ 
			strMatrix[startingRow][startingColumn] = word.at(index);
			index++;
			if (startingColumn - 1 >= 0 && strMatrix[startingRow][startingColumn-1] == "-")
			{
				startingColumn--;
			}
			else
			{
				controlcount++;
			}
		}
		else
		{
			if (startingRow - 1 >= 0  && strMatrix[startingRow-1][startingColumn] == "-" && controlcount == 1)
			{
				controlcount = 0;
				startingRow--;
				strMatrix[startingRow][startingColumn] = word.at(index);
				index++;
				if (startingColumn - 1 >= 0 && strMatrix[startingRow][startingColumn-1] == "-")
				{
					startingColumn--;
				}
				else
				{
					controlcount++;
				}
			}
			else
			{
				if (startingColumn + 1 < column  && strMatrix[startingRow][startingColumn+1] == "-" && controlcount == 1)
				{
					controlcount = 0;
					startingColumn++;
					strMatrix[startingRow][startingColumn] = word.at(index);
					index++;
					if (startingColumn - 1 >= 0 && strMatrix[startingRow][startingColumn-1] == "-")
					{
						startingColumn--;
					}
					else
					{
						controlcount++;
					}
				}	
				else
				{
					if (startingRow + 1 < row && strMatrix[startingRow+1][startingColumn] == "-" && controlcount == 1)
					{
						controlcount = 0;
						startingRow++;
						strMatrix[startingRow][startingColumn] = word.at(index);
						index++;
						if (startingColumn - 1 >= 0 && strMatrix[startingRow][startingColumn-1] == "-")
						{
							startingColumn--;
						}
						else
						{
							controlcount++;
						}
					}	
					else
					{
						returncount++;
						break;
					}
				}
			}
		}
	}
	if (returncount == 1)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

int Placement_lCCW(string word, int startingRow, int startingColumn, int row, int column, vector<vector<string>> &strMatrix, string direction, string orientation)
// placement of the word when the direction is l, and orientation is CCW
// this returns 0,if the word is put succesfully.  
// else returns 1. 
{
	int index = 0;
	int controlcount = 0;
	int returncount = 0;
	while (index < word.length())
	{
		if (strMatrix[startingRow][startingColumn] == "-" && (startingColumn <= column-1 && startingColumn >= 0) && (startingRow <= row-1 && startingRow >= 0))
		{ 
			strMatrix[startingRow][startingColumn] = word.at(index);
			index++;
			if (startingColumn - 1 >= 0 && strMatrix[startingRow][startingColumn-1] == "-")
			{
				startingColumn--;
			}
			else
			{
				controlcount++;
			}
		}
		else
		{
			if (startingRow + 1 < row  && strMatrix[startingRow+1][startingColumn] == "-" && controlcount == 1)
			{
				controlcount = 0;
				startingRow++;
				strMatrix[startingRow][startingColumn] = word.at(index);
				index++;
				if (startingColumn - 1 >= 0 && strMatrix[startingRow][startingColumn-1] == "-")
				{
					startingColumn--;
				}
				else
				{
					controlcount++;
				}
			}
			else
			{
				if (startingColumn + 1 < column  && strMatrix[startingRow][startingColumn+1] == "-" && controlcount == 1)
				{
					controlcount = 0;
					startingColumn++;
					strMatrix[startingRow][startingColumn] = word.at(index);
					index++;
					if (startingColumn - 1 >= 0 && strMatrix[startingRow][startingColumn-1] == "-")
					{
						startingColumn--;
					}
					else
					{
						controlcount++;
					}
				}	
				else
				{
					if (startingRow - 1 >= 0 && strMatrix[startingRow-1][startingColumn] == "-" && controlcount == 1)
					{
						controlcount = 0;
						startingRow--;
						strMatrix[startingRow][startingColumn] = word.at(index);
						index++;
						if (startingColumn - 1 >= 0 && strMatrix[startingRow][startingColumn-1] == "-")
						{
							startingColumn--;
						}
						else
						{
							controlcount++;
						}
					}	
					else
					{
						returncount++;
						break;
					}
				}
			}
		}
	}
	if (returncount == 1)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

int Placement_dCW(string word, int startingRow, int startingColumn, int row, int column, vector<vector<string>> &strMatrix, string direction, string orientation)
// placement of the word when the direction is d, and orientation is CW
// this returns 0,if the word is put succesfully.  
// else returns 1. 
{
	int index = 0;
	int controlcount = 0;
	int returncount = 0;
	while (index < word.length())
	{
		if (strMatrix[startingRow][startingColumn] == "-" && (startingColumn <= column-1 && startingColumn >= 0) && (startingRow <= row-1 && startingRow >= 0))
		{ 
			strMatrix[startingRow][startingColumn] = word.at(index);
			index++;
			if (startingRow + 1 < row && strMatrix[startingRow+1][startingColumn] == "-")
			{
				startingRow++;
			}
			else
			{
				controlcount++;
			}
		}
		else
		{
			if (startingColumn - 1 >= 0  && strMatrix[startingRow][startingColumn-1] == "-" && controlcount == 1)
			{
				controlcount = 0;
				startingColumn--;
				strMatrix[startingRow][startingColumn] = word.at(index);
				index++;
				if (startingRow + 1 < row && strMatrix[startingRow+1][startingColumn] == "-")
				{
					startingRow++;
				}
				else
				{
					controlcount++;
				}
			}
			else
			{
				if (startingRow - 1 >= 0  && strMatrix[startingRow-1][startingColumn] == "-" && controlcount == 1)
				{
					controlcount = 0;
					startingRow--;
					strMatrix[startingRow][startingColumn] = word.at(index);
					index++;
					if (startingRow + 1 < row && strMatrix[startingRow+1][startingColumn] == "-")
					{
						startingRow++;
					}
					else
					{
						controlcount++;
					}
				}	
				else
				{
					if (startingColumn + 1 < column && strMatrix[startingRow][startingColumn+1] == "-" && controlcount == 1)
					{
						controlcount = 0;
						startingColumn++;
						strMatrix[startingRow][startingColumn] = word.at(index);
						index++;
						if (startingRow + 1 < row && strMatrix[startingRow+1][startingColumn] == "-")
						{
							startingRow++;
						}
						else
						{
							controlcount++;
						}
					}	
					else
					{
						returncount++;
						break;
					}
				}
			}
		}
	}
	if (returncount == 1)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

int Placement_dCCW(string word, int startingRow, int startingColumn, int row, int column, vector<vector<string>> &strMatrix, string direction, string orientation)
// placement of the word when the direction is d, and orientation is CCW
// this returns 0,if the word is put succesfully.  
// else returns 1. 
{
	int index = 0;
	int controlcount = 0;
	int returncount = 0;
	while (index < word.length())
	{
		if (strMatrix[startingRow][startingColumn] == "-" && (startingColumn <= column-1 && startingColumn >= 0) && (startingRow <= row-1 && startingRow >= 0))
		{ 
			strMatrix[startingRow][startingColumn] = word.at(index);
			index++;
			if (startingRow + 1 < row && strMatrix[startingRow+1][startingColumn] == "-")
			{
				startingRow++;
			}
			else
			{
				controlcount++;
			}
		}
		else
		{
			if (startingColumn + 1 < column  && strMatrix[startingRow][startingColumn+1] == "-" && controlcount == 1)
			{
				controlcount = 0;
				startingColumn++;
				strMatrix[startingRow][startingColumn] = word.at(index);
				index++;
				if (startingRow + 1 < row && strMatrix[startingRow+1][startingColumn] == "-")
				{
					startingRow++;
				}
				else
				{
					controlcount++;
				}
			}
			else
			{
				if (startingRow - 1 >= 0  && strMatrix[startingRow-1][startingColumn] == "-" && controlcount == 1)
				{
					controlcount = 0;
					startingRow--;
					strMatrix[startingRow][startingColumn] = word.at(index);
					index++;
					if (startingRow + 1 < row && strMatrix[startingRow+1][startingColumn] == "-")
					{
						startingRow++;
					}
					else
					{
						controlcount++;
					}
				}	
				else
				{
					if (startingColumn -1 >= 0 && strMatrix[startingRow][startingColumn-1] == "-" && controlcount == 1)
					{
						controlcount = 0;
						startingColumn--;
						strMatrix[startingRow][startingColumn] = word.at(index);
						index++;
						if (startingRow + 1 < row && strMatrix[startingRow+1][startingColumn] == "-")
						{
							startingRow++;
						}
						else
						{
							controlcount++;
						}
					}	
					else
					{
						returncount++;
						break;
					}
				}
			}
		}
	}
	if (returncount == 1)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

int Placement_uCW(string word, int startingRow, int startingColumn, int row, int column, vector<vector<string>> &strMatrix, string direction, string orientation)
// placement of the word when the direction is u, and orientation is CW
// this returns 0,if the word is put succesfully.  
// else returns 1. 
{
	int index = 0;
	int controlcount = 0;
	int returncount = 0;
	while (index < word.length())
	{
		if (strMatrix[startingRow][startingColumn] == "-" && (startingColumn <= column-1 && startingColumn >= 0) && (startingRow <= row-1 && startingRow >= 0))
		{ 
			strMatrix[startingRow][startingColumn] = word.at(index);
			index++;
			if (startingRow -1 >= 0 && strMatrix[startingRow-1][startingColumn] == "-")
			{
				startingRow--;
			}
			else
			{
				controlcount++;
			}
		}
		else
		{
			if (startingColumn + 1 < column  && strMatrix[startingRow][startingColumn+1] == "-" && controlcount == 1)
			{
				controlcount = 0;
				startingColumn++;
				strMatrix[startingRow][startingColumn] = word.at(index);
				index++;
				if (startingRow -1 >= 0 && strMatrix[startingRow-1][startingColumn] == "-")
				{
					startingRow--;
				}
				else
				{
					controlcount++;
				}
			}
			else
			{
				if (startingRow + 1 < row  && strMatrix[startingRow+1][startingColumn] == "-" && controlcount == 1)
				{
					controlcount = 0;
					startingRow++;
					strMatrix[startingRow][startingColumn] = word.at(index);
					index++;
					if (startingRow -1 >= 0 && strMatrix[startingRow-1][startingColumn] == "-")
					{
						startingRow--;
					}
					else
					{
						controlcount++;
					}
				}	
				else
				{
					if (startingColumn -1 >= 0 && strMatrix[startingRow][startingColumn-1] == "-" && controlcount == 1)
					{
						controlcount = 0;
						startingColumn--;
						strMatrix[startingRow][startingColumn] = word.at(index);
						index++;
						if (startingRow -1 >= 0 && strMatrix[startingRow-1][startingColumn] == "-")
						{
							startingRow--;
						}
						else
						{
							controlcount++;
						}
					}	
					else
					{
						returncount++;
						break;
					}
				}
			}
		}
	}
	if (returncount == 1)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

int Placement_uCCW(string word, int startingRow, int startingColumn, int row, int column, vector<vector<string>> &strMatrix, string direction, string orientation)
// placement of the word when the direction is u, and orientation is CCW
// this returns 0,if the word is put succesfully.  
// else returns 1. 
{
	int index = 0;
	int controlcount = 0;
	int returncount = 0;
	while (index < word.length())
	{
		if (strMatrix[startingRow][startingColumn] == "-" && (startingColumn <= column-1 && startingColumn >= 0) && (startingRow <= row-1 && startingRow >= 0))
		{ 
			strMatrix[startingRow][startingColumn] = word.at(index);
			index++;
			if (startingRow -1 >= 0 && strMatrix[startingRow-1][startingColumn] == "-")
			{
				startingRow--;
			}
			else
			{
				controlcount++;
			}
		}
		else
		{
			if (startingColumn - 1 >= 0  && strMatrix[startingRow][startingColumn-1] == "-" && controlcount == 1)
			{
				controlcount = 0;
				startingColumn--;
				strMatrix[startingRow][startingColumn] = word.at(index);
				index++;
				if (startingRow -1 >= 0 && strMatrix[startingRow-1][startingColumn] == "-")
				{
					startingRow--;
				}
				else
				{
					controlcount++;
				}
			}
			else
			{
				if (startingRow + 1 < row  && strMatrix[startingRow+1][startingColumn] == "-" && controlcount == 1)
				{
					controlcount = 0;
					startingRow++;
					strMatrix[startingRow][startingColumn] = word.at(index);
					index++;
					if (startingRow -1 >= 0 && strMatrix[startingRow-1][startingColumn] == "-")
					{
						startingRow--;
					}
					else
					{
						controlcount++;
					}
				}	
				else
				{
					if (startingColumn +1 < column && strMatrix[startingRow][startingColumn+1] == "-" && controlcount == 1)
					{
						controlcount = 0;
						startingColumn++;
						strMatrix[startingRow][startingColumn] = word.at(index);
						index++;
						if (startingRow -1 >= 0 && strMatrix[startingRow-1][startingColumn] == "-")
						{
							startingRow--;
						}
						else
						{
							controlcount++;
						}
					}	
					else
					{
						returncount++;
						break;
					}
				}
			}
		}
	}
	if (returncount == 1)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

void Cleaning(vector<vector<string>> &strMatrix)
// this function  changes "?" with "-" if there is "?" in any position in the matrix.
// This function has been done so that if the word has 5 letters and the second letter could not be put into the matrix, the first letter placed in the matrix would not be left.
{
	for (int j = 0; j < strMatrix.size(); j++)
	{ 
		for (int k = 0; k < strMatrix[0].size(); k++)
		{
			if (strMatrix[j][k] == "?")
			{
				strMatrix[j][k] = "-";
			}
		}
	}
}


string Transforming(string& word)
// this function creates a word by converting its all character into "?". 
// To check whether there is empty position for the letters of the word or not, before putting the word itself.
{
	string s = "";
	for (int i = 0; i < word.length(); i++)
	{
		s += "?";
	}
	return s;
}

void openFile(const string& whichFile, ifstream& inFile)
//this opens the file. 
{
    string fName;
    cout << "Please enter the name of the file: ";
    cin >> fName;
    inFile.open(fName.c_str());
    while (inFile.fail())
	{
        cout << "File name is incorrect, please enter again: ";
        cin >> fName;
        inFile.open(fName.c_str());
    }
}

int countWords(string line) 
// this returns how many variables there are in the line to check 5 variable rule.  
{ 
	stringstream strStream(line);  
	string variable; 
	int count = 0; 
	while (strStream >> variable) 
	{
		count++; 
	}
	return count; 
}

int boslukcounter(vector<vector<string>> &strMatrix)
// this returns how many "-" there are in the matrix. If the word's length is larger than this value, word cannot be put. 
{
	int m = 0;
	for (int j = 0; j < strMatrix.size(); j++)
	{ 
		for (int k = 0; k < strMatrix[0].size(); k++)
		{
			if (strMatrix[j][k] == "-")
			{
				m++;
			}
		}
	}
	return m;
}

void readFile_process(ifstream &file, int &row, int &column)

// readin file, getting word, row, column, starting column, starting row, direction, orientation values are done in this function.
// and process of placement of the word is done in this function. 
{
	string line,variables;
	string word, direction, orientation;
	int startingRow, startingColumn;
	getline(file,line); // getting the first line of the text
	stringstream strStream;
    strStream << line;
	strStream >> row >> column;
	if (row <= 0 || column <= 0)
	{
		cout << "Invalid number for row and/or column!" << endl;
	}
	else
	{
		vector<vector<string>> strMatrix(row, vector<string> (column,"-"));
		stringstream strStream2;
		while (!file.eof()) 	
		{
			stringstream strStream2;
			strStream2.clear();
			getline(file, line); // getting other lines starting from 2nd line to end line. 
			strStream2 << line;
			if (countWords(line) != 5)
			{
				cout << "Invalid line! Number of values is different than 5." << endl;
			}
			else
			{
				strStream2 >> word >> startingRow >> startingColumn >> direction >> orientation;
				if (CheckInput(row, column, direction, orientation, startingRow, startingColumn) == 1)
				{
					cout << "Starting point is out of range! Point: " << startingRow << "," << startingColumn << endl;
				}
				else if (CheckInput(row, column, direction, orientation, startingRow, startingColumn) == 2) 
				{
					cout << "Invalid input for direction! Direction:" << direction << endl;
				}
				else if (CheckInput(row, column, direction, orientation, startingRow, startingColumn) == 3)
				{
					cout << "Invalid input for orientation! Orientation: " << orientation << endl;
				}
				// if row and colum values is valid, variable number is 5, starting point is in the range, direction and orientation is in the correct format,
				// after this line, the word is trying to be put into the matrix. 
				else if (CheckInput(row, column, direction,orientation,startingRow,startingColumn) == -5)
				{
					if (strMatrix[startingRow][startingColumn] != "-") // if initial point is not empty
					{
						cout << "\"" << word << "\" could not be put into the matrix with given starting point: " << startingRow << "," << startingColumn <<" direction: " << direction <<" orientation: " << orientation << endl;
						Print(strMatrix);
					}
					else if (boslukcounter(strMatrix) < word.length()) // this checks how many available points to put the letters there are in the matrix. i.e. if it is smaller than the word length, this means word cannot be put into the matrix. 
					{
						cout << "\"" << word << "\" could not be put into the matrix with given starting point: " << startingRow << "," << startingColumn <<" direction: " << direction <<" orientation: " << orientation << endl;
						Print(strMatrix);
					}
					else
					{
						string controlstring = Transforming(word); // word is converted into "?...?" (The main purpose is to easily delete the placed letters if the word does not fit into the matrix. )
						if (direction == "r" && orientation == "CW")
						{
							if (Placement_rCW(controlstring, startingRow, startingColumn, row, column, strMatrix, direction, orientation) == 1) // control string entered to the matrix and returned 1 value means that it does not fit into the matrix. 
							{
								Cleaning(strMatrix); // Since the word whose letters are turned into question marks cannot be placed in the matrix, it is cleared from the matrix with the "cleaning" function, which removes the question marks.
								cout << "\"" << word << "\" could not be put into the matrix with given starting point: " << startingRow << "," << startingColumn <<" direction: " << direction <<" orientation: " << orientation << endl;
								Print(strMatrix);
							}
							else
							// this means the word can be put into the matrix. 
							{
								Cleaning(strMatrix); // question marks are deleted. 
								Placement_rCW(word, startingRow, startingColumn, row, column, strMatrix, direction, orientation); // now the word itself is put into the matrix. 
								cout << "\"" << word << "\" was put into the matrix with given starting point: " << startingRow << "," << startingColumn  << " direction:"<< direction << " orientation:" << orientation << endl;
								Print(strMatrix);
							}
						}
						// same way continues in all else if conditions. 
						else if (direction == "r" && orientation == "CCW")
						{
							if (Placement_rCCW(controlstring, startingRow, startingColumn, row, column, strMatrix, direction, orientation) == 1)
							{
								Cleaning(strMatrix);
								cout << "\"" << word << "\" could not be put into the matrix with given starting point: " << startingRow << "," << startingColumn <<" direction: " << direction <<" orientation: " << orientation << endl;
								Print(strMatrix);
							}
							else
							{
								Cleaning(strMatrix);
								Placement_rCCW(word, startingRow, startingColumn, row, column, strMatrix, direction, orientation);
								cout << "\"" << word << "\" was put into the matrix with given starting point: " << startingRow << "," << startingColumn  << " direction:"<< direction << " orientation:" << orientation << endl;
								Print(strMatrix);
							}
						}
						else if (direction == "l" && orientation == "CW")
						{
							if (Placement_lCW(controlstring, startingRow, startingColumn, row, column, strMatrix, direction, orientation) == 1)
							{
								Cleaning(strMatrix);
								cout << "\"" << word << "\" could not be put into the matrix with given starting point: " << startingRow << "," << startingColumn <<" direction: " << direction <<" orientation: " << orientation << endl;
								Print(strMatrix);
							}
							else
							{
								Cleaning(strMatrix);
								Placement_lCW(word, startingRow, startingColumn, row, column, strMatrix, direction, orientation);
								cout << "\"" << word << "\" was put into the matrix with given starting point: " << startingRow << "," << startingColumn  << " direction:"<< direction << " orientation:" << orientation << endl;
								Print(strMatrix);
							}
						}
						else if (direction == "l" && orientation == "CCW")
						{
							if (Placement_lCCW(controlstring, startingRow, startingColumn, row, column, strMatrix, direction, orientation) == 1)
							{
								Cleaning(strMatrix);
								cout << "\"" << word << "\" could not be put into the matrix with given starting point: " << startingRow << "," << startingColumn <<" direction: " << direction <<" orientation: " << orientation << endl;
								Print(strMatrix);
							}
							else
							{
								Cleaning(strMatrix);
								Placement_lCCW(word, startingRow, startingColumn, row, column, strMatrix, direction, orientation);
								cout << "\"" << word << "\" was put into the matrix with given starting point: " << startingRow << "," << startingColumn  << " direction:"<< direction << " orientation:" << orientation << endl;
								Print(strMatrix);
							}
						}
						else if (direction == "d" && orientation == "CW")
						{
							if (Placement_dCW(controlstring, startingRow, startingColumn, row, column, strMatrix, direction, orientation) == 1)
							{
								Cleaning(strMatrix);
								cout << "\"" << word << "\" could not be put into the matrix with given starting point: " << startingRow << "," << startingColumn <<" direction: " << direction <<" orientation: " << orientation << endl;
								Print(strMatrix);
							}
							else
							{
								Cleaning(strMatrix);
								Placement_dCW(word, startingRow, startingColumn, row, column, strMatrix, direction, orientation);
								cout << "\"" << word << "\" was put into the matrix with given starting point: " << startingRow << "," << startingColumn  << " direction:"<< direction << " orientation:" << orientation << endl;
								Print(strMatrix);
							}
						}
						else if (direction == "d" && orientation == "CCW")
						{
							if (Placement_dCCW(controlstring, startingRow, startingColumn, row, column, strMatrix, direction, orientation) == 1)
							{
								Cleaning(strMatrix);
								cout << "\"" << word << "\" could not be put into the matrix with given starting point: " << startingRow << "," << startingColumn <<" direction: " << direction <<" orientation: " << orientation << endl;
								Print(strMatrix);
							}
							else
							{
								Cleaning(strMatrix);
								Placement_dCCW(word, startingRow, startingColumn, row, column, strMatrix, direction, orientation);
								cout << "\"" << word << "\" was put into the matrix with given starting point: " << startingRow << "," << startingColumn  << " direction:"<< direction << " orientation:" << orientation << endl;
								Print(strMatrix);
							}
						}
						else if (direction == "u" && orientation == "CW")
						{
							if (Placement_uCW(controlstring, startingRow, startingColumn, row, column, strMatrix, direction, orientation) == 1)
							{
								Cleaning(strMatrix);
								cout << "\"" << word << "\" could not be put into the matrix with given starting point: " << startingRow << "," << startingColumn <<" direction: " << direction <<" orientation: " << orientation << endl;
								Print(strMatrix);
							}
							else
							{
								Cleaning(strMatrix);
								Placement_uCW(word, startingRow, startingColumn, row, column, strMatrix, direction, orientation);
								cout << "\"" << word << "\" was put into the matrix with given starting point: " << startingRow << "," << startingColumn  << " direction:"<< direction << " orientation:" << orientation << endl;
								Print(strMatrix);
							}
						}
						else if (direction == "u" && orientation == "CCW")
						{
							if (Placement_uCCW(controlstring, startingRow, startingColumn, row, column, strMatrix, direction, orientation) == 1)
							{
								Cleaning(strMatrix);
								cout << "\"" << word << "\" could not be put into the matrix with given starting point: " << startingRow << "," << startingColumn <<" direction: " << direction <<" orientation: " << orientation << endl;
								Print(strMatrix);
							}
							else
							{
								Cleaning(strMatrix);
								Placement_uCCW(word, startingRow, startingColumn, row, column, strMatrix, direction, orientation);
								cout << "\"" << word << "\" was put into the matrix with given starting point: " << startingRow << "," << startingColumn  << " direction:"<< direction << " orientation:" << orientation << endl;
								Print(strMatrix);
							}
						}
					}
				}
			}
		}
	}
}

int main()
{
	ifstream file;
	int row, column, startingRow, startingColumn;
	string fileStr, word, direction, orientation;

	openFile(fileStr, file);
	readFile_process(file, row, column);
	
	file.close();
	return 0;
}