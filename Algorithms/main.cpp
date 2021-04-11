#include "Program.h"
#include <vector>
using namespace std;
using Collection::List;
using Collection::LinkedList;
using Collection::Stack;
using Collection::Queue;

using Homework_2::Graph;


int main()
{
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

	Stack<int> stk(false);

	
	for (int i = -5; i < 50; i++)
		stk.push(i);
	
	int s = stk.size();
	for (int i = 0; i < s; i++)
		stk.pop();

	cout << stk << endl;

	Queue<> q;

	for (int i = -15; i < 15; i++)
	{
		q.push(i);
		cout << q << endl;
	}

	cout << endl;

	s = q.size();

	for (int i = 0; i < s; i++)
	{
		q.pop();
		cout << q << endl;
	}


	cout << endl;
	cout << q << endl;
	cout << lst << endl;*/
  
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  cout << "Algorithm Design" << endl;
  
	//Homework_1::test();
	Homework_2::test();
	return EXIT_SUCCESS;
}