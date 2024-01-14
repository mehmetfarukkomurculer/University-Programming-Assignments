#include <iostream>
#include <string>

using namespace std;

int main()
{
	string student_name, course_name, answer, for1st_current_grade, changing_answer, changing_answer2, for2ndprevious_grade, for2ndcurrent_grade, wanted_grade;
	cout << "Welcome to the Fall 2020-2021 Semester grading system. What is your name? " ;
	cin >> student_name;
	cout << "Hello " << student_name<<"! Please enter the name of the course to be processed: ";
	cin >> course_name;
	cout << "Hello " << student_name << "! If you take the " << course_name << " for the first time, enter YES otherwise NO: ";
	cin >> answer;
	if (answer == "YES")
	{
		cout << "What is your grade from (A,B,C,D,F)? ";
		cin >> for1st_current_grade;
		if ( for1st_current_grade == "A" || for1st_current_grade == "B" || for1st_current_grade == "C" || for1st_current_grade == "D" )
		{
			cout << "Do you want to switch your grade from " << for1st_current_grade << " to S (YES or NO)? ";
			cin >> changing_answer;
			if ( changing_answer == "YES")
			{
				cout << student_name << ", your final grade for " << course_name << " is S. Goodbye..." <<endl;
			}
			else if ( changing_answer == "NO")
			{
				cout << student_name << ", your final grade for " << course_name << " is " << for1st_current_grade <<". Goodbye..." <<endl;
			}
			else
			{
				cout << "Invalid grade selection. Goodbye..." << endl;

			}
		}
		else if (for1st_current_grade == "F")
		{
			cout << "Do you want to switch your grade from " << for1st_current_grade << " to U (YES or NO)? ";
			cin >> changing_answer2;
			if ( changing_answer2 == "YES")
			{
				cout << student_name << ", your final grade for " << course_name << " is U. Goodbye..." <<endl;
			}
			else if ( changing_answer2 == "NO")
			{
				cout << student_name << ", your final grade for " << course_name << " is " << for1st_current_grade <<". Goodbye..." <<endl;
			}
			else
			{
				cout << "Invalid grade selection. Goodbye..." << endl;
			}
		}
		else 
		{
			cout << "Invalid grade selection. Goodbye..." << endl;
		}
	}
	else if (answer == "NO")
	{
		cout << "Please enter your previous grade from (A,B,C,D,F,S,U): ";
		cin >> for2ndprevious_grade;
		cout << "Please enter your current grade from (A,B,C,D,F): ";
		cin >> for2ndcurrent_grade;
		if ( !(for2ndprevious_grade == "A" || for2ndprevious_grade == "B" || for2ndprevious_grade == "C" || for2ndprevious_grade == "D" || for2ndprevious_grade == "F" || for2ndprevious_grade == "S" || for2ndprevious_grade == "U") )
		{
			cout << "Invalid grade selection. Goodbye..." << endl;
		}
		else if ( !(for2ndcurrent_grade == "A" || for2ndcurrent_grade == "B" || for2ndcurrent_grade == "C" || for2ndcurrent_grade == "D" || for2ndcurrent_grade == "F") )
		{
			cout << "Invalid grade selection. Goodbye..." << endl;
		}
		else 
		{
			cout << "Please enter the grade you want to choose from (A,B,C,D,F,S,U): ";
			cin >> wanted_grade;
			if ( !( wanted_grade == "A" || wanted_grade == "B" || wanted_grade == "C" || wanted_grade == "D" || wanted_grade == "F" || wanted_grade == "S" || wanted_grade == "U" ) )
			{
				cout << "Invalid grade selection. Goodbye..." << endl;
			}
			else
			{
				if ( for2ndprevious_grade == "F" && for2ndcurrent_grade == "F" )
				{
					if ( !(wanted_grade == "F"))
					{
						cout << "Invalid grade selection. If you received F before, and fail this semester, you get F." << endl;
					}
					else
					{
						cout << student_name << ", your final grade for " << course_name << " is F. Goodbye..." << endl;
					}
				}
				else if ( for2ndprevious_grade == "U" && for2ndcurrent_grade == "F" )
				{
					if ( !(wanted_grade == "F" || wanted_grade == "U") )
					{
						cout << "Invalid grade selection. You cannot choose a higher or lower grade than you deserve." << endl;
					}
					else
					{
						cout << student_name << ", your final grade for " << course_name << " is " << wanted_grade << ". Goodbye..." << endl;
					}
				}
				else if ( (for2ndprevious_grade == "A" || for2ndprevious_grade == "B" || for2ndprevious_grade == "C" || for2ndprevious_grade == "D") && for2ndcurrent_grade == "F" )
				{
					if ( !(wanted_grade == "F" || wanted_grade == "U") )
					{
						cout << "Invalid grade selection. You cannot choose a higher or lower grade than you deserve." << endl;
					}
					else
					{
						cout << student_name << ", your final grade for " << course_name << " is " << wanted_grade << ". Goodbye..." << endl;
					}
				}
				else if ( for2ndprevious_grade == "S" && for2ndcurrent_grade == "F" )
				{
					if ( !(wanted_grade == "F") )
					{
						cout << "Invalid grade selection. If you received S before and fail this semester, you get F." << endl;
					}
					else 
					{
						cout << student_name << ", your final grade for " << course_name << " is " << wanted_grade << ". Goodbye..." << endl;
					}
				}
				else if ( for2ndprevious_grade == "U" && ( for2ndcurrent_grade == "A" || for2ndcurrent_grade == "B" || for2ndcurrent_grade == "C" || for2ndcurrent_grade == "D" ) )
				{
					if ( !(wanted_grade == for2ndcurrent_grade || wanted_grade == "S" ))
					{
						cout << "Invalid grade selection. If you received U before, you may choose S or current letter grade." << endl;
					}
					else
					{
						cout << student_name << ", your final grade for " << course_name << " is " << wanted_grade << ". Goodbye..." << endl;
					}

				}
				else if ( for2ndprevious_grade == "S" && ( for2ndcurrent_grade == "A" || for2ndcurrent_grade == "B" || for2ndcurrent_grade == "C" || for2ndcurrent_grade == "D" ) )
				{
					if ( !(wanted_grade == for2ndcurrent_grade || wanted_grade == "S" ))
					{
						cout << "Invalid grade selection. You cannot choose a higher or lower grade than you deserve." << endl;
					}
					else
					{
						cout << student_name << ", your final grade for " << course_name << " is " << wanted_grade << ". Goodbye..." << endl;
					}
				}
				else if ( for2ndprevious_grade == "F" && ( for2ndcurrent_grade == "A" || for2ndcurrent_grade == "B" || for2ndcurrent_grade == "C" || for2ndcurrent_grade == "D" ))
				{
					if ( !( wanted_grade == for2ndcurrent_grade || wanted_grade == "S" ))
					{
						cout << "Invalid grade selection. You cannot choose a higher or lower grade than you deserve." << endl;
					}
					else
					{
						cout << student_name << ", your final grade for " << course_name << " is " << wanted_grade << ". Goodbye..." << endl;
					}
				}
				else if ( (for2ndprevious_grade == "A" || for2ndprevious_grade == "B" || for2ndprevious_grade == "C" || for2ndprevious_grade == "D")  && ( for2ndcurrent_grade == "A" || for2ndcurrent_grade == "B" || for2ndcurrent_grade == "C" || for2ndcurrent_grade == "D" ))
				{
					if ( !( wanted_grade == for2ndcurrent_grade || wanted_grade == "S" ))
					{
						cout << "Invalid grade selection. You cannot choose a higher or lower grade than you deserve." << endl;
					}
					else
					{
						cout << student_name << ", your final grade for " << course_name << " is " << wanted_grade << ". Goodbye..." << endl;
					}
				}

			}

		}
	}

	return 0;
}
