#include "Program.h"
#include <vector>
using namespace std;
using Collection::List;
using Collection::LinkedList;
using Collection::Stack;


int main()
{
	// graph_homework_1::test_homework_1();
	/*List<> a(5);
	a.push_back(25);
	a.push_back(13);
	

	cout << a.size() << endl;
	try {
		a.insert(3, 3);

	}
	catch(List<>::IndexOutOfRange& e)
	{
		cerr << e.what() << endl;
	}
	try {
		a.erase(1);
	}
	catch(List<>::IndexOutOfRange& e)
	{
		cerr << e.what() << endl;
	}

	for(unsigned i = 0; i < a.size(); i++)
	{
		cout << a[i] << endl;
	}*/
		
	cout << "Linked List" << endl;

	LinkedList<int> lst(false);

	
	for (int i = -5; i < 15; i++) 
	{
		if (i % 2 == 0)
			lst.push_back(i);
		else
			lst.push(i);
	}

	cout << lst << endl;

	lst.clear();

	cout << lst << endl;

	try {
		lst.pop_back();
	}
	catch (Collection::Abstract::List::ListEmpty& e)
	{
		cout << e.what() << endl;
	}

	lst.push_back(5);
	lst.push(255);
	lst.push_back(-42324);
	lst.push_back(137);

	cout << lst << endl;

	lst.pop();
	lst.pop();
	lst.pop();
	lst.pop_back();

	lst.push_back(52);
	lst.push(15);
	cout << lst << endl;

	lst.pop_back();

	cout << lst << endl;

	return EXIT_SUCCESS;
}