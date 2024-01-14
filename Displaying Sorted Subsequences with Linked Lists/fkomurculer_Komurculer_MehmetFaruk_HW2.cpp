#include <iostream>
#include <string>
#include <sstream>
#include "fkomurculer_Komurculer_MehmetFaruk_HW2_strutils.h"

using namespace std;

//mehmet faruk komurculer 

struct node
//linked list for values
{
	int value;
	node * next;
	node::node ()
		:value(0), next(NULL)
	{}
	node::node (int i,node *n)
		:value(i), next(n)
	{}	
};

string getOrder()
// this function gets the order correctly ("D" or "A")
{
    string order, first;
    cout << "Please enter the order mode (A/D): ";
	getline(cin, order);
	stringstream strStream;
	strStream << order;
	strStream >> first;
	while (first != "A" && first != "D")
	{
		strStream.clear();
		cout << "Please enter the order mode again (A/D): ";
		getline(cin, order);
		stringstream strStream;
		strStream << order;
		strStream >> first;
		if (first == "A" || first == "D")
		{
			break;
		}
	}
	return first;
}

void ListContent(node* head) 
// this prints the node values. Also this is used to print deleted nodes. 
{
	node* ptr;
	ptr = head;
	while (ptr != NULL) 
	{
		cout<< ptr->value << " ";
		ptr = ptr->next;
	}
}

void DeleteList (node *&head)
// this deletes all nodes if input is head. 
{
	node *temp = new node;
	while (head != NULL) 
	{
		temp = head->next;
        delete head;
        head = temp;
	}
}
bool CheckSameContent(node *head, int number)
// this checks whether the number is already in the list. 
{
	while (head != NULL)
	{
		if(head->value == number)
			return true;			
		head = head->next;
	}
	return false;
}

bool SpaceCounter(string str)
// this counts space in the string (created for the integer line input. If input's all characters are space, returns false. )
{
	int len = str.length();
	int count = 0;
	for (int i = 0; i < len; i++)
	{
		if (str.at(i) == ' ')
		{
			count++;
		}
	}
	if (count == len)
	{
		return false;
	}
	else
	{
		return true;
	}
}

int GetFirst(string& line)
// this gets the first integer from the line (useful for the initializing of head->value)
// also deletes the first integer from the line. Other integers become ready to be read by stringstream. 
{
	int index = 0;
	int foundIdx, realFirst;
	string firstNumber;
	if (line.at(index) != ' ')
	{
		foundIdx = line.find(" ");
		firstNumber = line.substr(0,foundIdx); // getting the first integer as string.
		line.erase(0,foundIdx); // deletion of first integer
	}
	else
	{
		while (line.at(index) == ' ')
		{
			index++;
			if (line.at(index) != ' ')
			{
				foundIdx = line.find(" ",index);
				firstNumber = line.substr(index,foundIdx); // getting the first integer as string. 
				break;
			}
		}
		line.erase(0,foundIdx); // deletion of first integer
	}
	realFirst = atoi(firstNumber); // converting string into integer. 
	return realFirst;
}

void Process(node*head, string order)
// The status/acts/comparisons (idk how to call :(( .) of the nodes is determined in this function.
{
	string line;
	
	cout << "Please enter the numbers in a line: ";
	getline(cin, line);
	if (line.length() < 1)
	{
		cout << "The list is empty at the end of the program and nothing is deleted" << endl;
	}
	else if (!(SpaceCounter(line)))
	{
		cout << "The list is empty at the end of the program and nothing is deleted" << endl;
	}
	else
	{
		head ->value = GetFirst(line); // head value is initialized. 
		int number;
		cout << endl;
		cout << "Next number: " << head ->value << endl;
		cout << "Deleted nodes: None" << endl;
		cout << "Appended: " << head ->value << endl;
		cout << "List content: ";
		ListContent(head); 
		cout << endl;
		cout << endl;
		stringstream strStream2(line); // remaining line is sent to the stringstream to get other numbers in the line. 
		node *temp; 
		temp = head;
		node *temp2;
		temp2 = head;
		if (order == "A")
		{
			while (strStream2 >> number)
			{
				if (CheckSameContent(head, number))// condition to be in list.
				{
					cout << "Next number: " << number << endl;
					cout << number <<" is already in the list!" << endl;
					cout << "List content: ";
					ListContent(head);
					cout << endl;
					cout << endl;
				}
				else if (number < head->value) // if the given number is the smaller than head value
				// make this number the head value. and delete remaining nodes. 
				{
					cout << "Next number: " << number << endl;
					cout << "Deleted nodes: ";
					ListContent(head);
					temp->next = new node(head->value, NULL);
					head -> value = number;
					temp = head;
					cout << endl;
					cout << "Appended: " << number << endl;
					cout << "List content: ";
					if (temp2->next != NULL)
					{
						DeleteList(temp2->next);
					}
					ListContent(head);
					cout << endl;
					cout << endl;
				}
				else if (number > temp->value) // if the given number is the biggest compared to values in the list.
				// adds this number to the list. 
				{
					cout << "Next number: " << number << endl;
					cout << "Deleted nodes: None" << endl;
					cout << "Appended: " << number << endl;
					cout << "List content: ";
					temp->next = new node(number, NULL);
					ListContent(head);
					temp = temp->next;
					cout << endl;
					cout << endl;
				}
				else if (number > head->value && number < temp->value)
				// number is not bigger than last value of the list and not smaller than head value. 
				{
					while (number > temp2->value && number < temp->value)
					{
						if (number < temp2->next->value)
						{
							cout << "Next number: " << number << endl;
							cout << "Deleted nodes: ";
							ListContent(temp2->next);
							cout << endl;
							temp2->next->value = number;
							cout << "Appended: " << number << endl;
							if (temp2->next->next != NULL)
							{
								DeleteList(temp2->next->next);
							}
							cout << "List content: ";
							ListContent(head);
							cout << endl;
							cout << endl;
							temp2 = head;
							temp->value = number;
						}
						else
						{
							temp2 = temp2->next;
						}
					}
				}
			}
		}
		else if (order == "D")
		{
			while (strStream2 >> number)
			{
				if (CheckSameContent(head, number))// condition to be in list.
				{
					cout << "Next number: " << number << endl;
					cout << number <<" is already in the list!" << endl;
					cout << "List content: ";
					ListContent(head);
					cout << endl;
					cout << endl;
				}
				else if (number > head->value) // if the given number is the bigger than head value
				// make this number the head value. and delete remaining nodes. 
				{
					cout << "Next number: " << number << endl;
					cout << "Deleted nodes: ";
					ListContent(head);
					temp->next = new node(head->value, NULL);
					head -> value = number;
					temp = head;
					cout << endl;
					cout << "Appended: " << number << endl;
					cout << "List content: ";
					if (temp2->next != NULL)
					{
						DeleteList(temp2->next);
					}
					ListContent(head);
					cout << endl;
					cout << endl;
				}
				else if (number < temp->value) // if the given number is the smaller than last value in the list.
				// adds this number to the list. 
				{
					temp->next = new node(number, NULL);
					temp = temp->next;
					cout << "Next number: " << number << endl;
					cout << "Deleted nodes: None" << endl;
					cout << "Appended: " << number << endl;
					cout << "List content: ";
					ListContent(head);
					cout << endl;
					cout << endl;
				}
				else if (number < head->value && number > temp->value)
				// number is  bigger than last value of the list and smaller than head value. 
				{
					while (number < temp2->value && number > temp->value)
					{
						if (number > temp2->next->value)
						{
							cout << "Next number: " << number << endl;
							cout << "Deleted nodes: ";
							ListContent(temp2->next);
							cout << endl;
							temp2->next->value = number;
							cout << "Appended: " << number << endl;
							if (temp2->next->next != NULL)
							{
								DeleteList(temp2->next->next);
							}
							cout << "List content: ";
							ListContent(head);
							cout << endl;
							cout << endl;
							temp2 = head;
							temp->value = number;
						}
						else
						{
							temp2 = temp2->next;
						}
					}
				}
			}
		}
		cout << "All the nodes are deleted at the end of the program: ";
		ListContent(head);
		cout << endl;
	}
}

int main()
{
	node* head;
	head = new node;
	string order = getOrder();
	Process(head, order);
	return 0;
}