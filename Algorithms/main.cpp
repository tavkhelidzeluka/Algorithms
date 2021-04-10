#include "Program.h"

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
		
	LinkedList<> lst(false);

	lst.push(1);
	lst.push(2);
	lst.push(3);
	lst.push(4);
	lst.push_back(5);

	cout << lst << endl;

	lst.clear();

	lst.push(1);
	cout << lst << endl;

	return EXIT_SUCCESS;
}