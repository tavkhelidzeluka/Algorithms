#include "Program.h"

using namespace std;
using Collection::List;
using Collection::LinkedList;
using Homework_2::Graph;


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
		
	/*LinkedList<> lst;


	for (int i = -500; i < 500; i++)
		lst.push(i);
	

	cout << lst << endl;

	for (int i = 0; i < 995; i++)
		lst.pop();

	cout << lst << endl;*/

	Graph a(5, false);

	a.add_edge('a', 'b');
	a.add_edge('b', 'c');
	a.add_edge('d', 'e');
	a.add_edge('c', 'd');
	a.add_edge('c', 'f');




	cout << a << endl;

	a.topological_sort();
	return EXIT_SUCCESS;
}