#include "Program.h"

using namespace std;
using Collection::List;
using graph_homework_1::Graph;


int main()
{
	Graph b({ 'b', 'c', 'd', 'f' });

	b.add_edge('b', 'a');
	b.add_edge('a', 'd');
	b.add_edge('c', 'b');
	b.add_edge('d', 'b');
	b.add_edge('f', 'a');
	b.add_edge('f', 'c');

	cout << b << endl;

	b.bfs('a');
	return EXIT_SUCCESS;
}