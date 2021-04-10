#include <iostream>
#include <map>
#include <stack>
#include "Homework_1.h"
#include <functional>

namespace Homework_2
{
	/*
		Task 1: implement Topological sort method.
			1. in this method determine whether it is 
				possible to sort topologically or not.
			2. output sorted contents
	*/

	class Graph : public Homework_1::Graph
	{
	public:

		Graph(unsigned vertex_count, bool is_oriented = false)
			: Homework_1::Graph(vertex_count, is_oriented) {}

		void topological_sort()
		{
			std::map<char, int> status;
			/*
				status -
					0: not visited
					1: visited
					2: finished
			*/

			std::stack<char> finished;
			int time = 0;
			bool can_be_sorted = true;
			int linked_components = 0;

			std::function<void (char)> visit = [&, this](auto vertex)
			{
				status[vertex]++;
				time++;

				for (const auto& neighbour_vertex : this->adjacency_list[vertex])
				{
					if (status[neighbour_vertex] == 0)
						visit(neighbour_vertex);
					else if (status[neighbour_vertex] == 2)
					{
						can_be_sorted = false;
						return;
					}
				}

				status[vertex]++;
				finished.push(vertex);
				return;
			};

			if (this->is_oriented)
			{
				goto cannot_be_sorted;
			}

			for (const auto& [vertex, _] : this->adjacency_list)
			{
				status[vertex] = 0;
			}

			for (const auto& [vertex, _] : this->adjacency_list)
			{
				if (status[vertex] == 0)
				{
					if (linked_components >= 1 or not can_be_sorted)
					{
						can_be_sorted = false;
						break;
					}
					visit(vertex);
					linked_components++;
				}
			}

			if (not can_be_sorted)
			{
			cannot_be_sorted: // statement
				std::cout << "Can't be sorted" << std::endl;
				return;
			}

			for (unsigned i = 0; i < finished.size(); i++)
			{
				i--;
				std::cout << finished.top() << ' ';
				finished.pop();
			}
		}
	};
}
