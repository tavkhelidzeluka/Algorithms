#include "Program.h"
#include <ctime>

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

	//Stack<int> stk(false);

	//
	//for (int i = -5; i < 50; i++)
	//	stk.push(i);
	//
	//int s = stk.size();
	//for (int i = 0; i < s; i++)
	//	stk.pop();

	//cout << stk << endl;

	//Collection::Generic::Queue<> q;

	//for (int i = -15; i < 15; i++)
	//{
	//	q.push(i);
	//	cout << q << endl;
	//}

	//cout << endl;

	//s = q.size();

	//for (int i = 0; i < s; i++)
	//{
	//	q.pop();
	//	cout << q << endl;
	//}


	//cout << endl;
	//cout << q << endl;
 // 
	//cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	//cout << "Algorithm Design" << endl;
 // 
	////Homework_1::test();
	//Homework_2::test();

	//cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

	//
	//Collection::Generic::Stack<int> lst;

	//for(int i = 0; i < 10; i++)
	//	lst.push(i);

	//cout << lst << endl;
	//
	//s = int(lst.size());
	//for (int i = 0; i < s; i++)
	//{
	//	cout << lst.pop() << endl;
	//}

	//Stack<int> l;

	//for (int i = 0; i < 10; i++)
	//	l.push(i);

	//cout << l << endl;

	//s = int(l .size());
	//for (int i = 0; i < s; i++)
	//	cout << l.pop() << endl;

	LinkedList<> q;

	for (int i = 0; i < 1000000; i++)
	{
		q.push(i);
	}


	q.clear();

	cout << q << endl;




	return EXIT_SUCCESS;
}