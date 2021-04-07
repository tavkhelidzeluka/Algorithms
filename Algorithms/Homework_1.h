#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <queue>


namespace graph_homework_1 {
	/*
		Lab 3 Tasks :
		N1
		N2
		N3
		N4
	*/
	class Graph
	{
	public:
		unsigned vertex_count = NULL;
		std::map<char, std::vector<char>> adjacency_list;

		Graph(unsigned vertex_count)
		{
			this->vertex_count = vertex_count;
			int char_code = 97;
			for (unsigned i = 0; i < vertex_count; i++)
				adjacency_list[char_code++] = std::vector<char>{};
		}

		Graph(const std::vector<char>& vertex_names)
		{
			this->vertex_count = vertex_names.size();
			for (const auto& vertex_name : vertex_names)
				this->adjacency_list[vertex_name] = std::vector<char>{};
		}
		void add_edge(char from, char to, bool oriented = true)
		{
			for (const auto& vertex : this->adjacency_list[from])
				if (vertex == to)
					return;

			if (not oriented)
			{
				for (const auto& vertex : this->adjacency_list[to])
					if (vertex == from)
						return;
				adjacency_list[to].push_back(from);
			}

			adjacency_list[from].push_back(to);
		}

		std::ostream& __repr__(std::ostream& output)
		{
			output << this << " {\n";
			for (const auto& [key, value] : this->adjacency_list)
			{
				output << '\t' << key << " -> ";
				for (const auto& vertex : value)
				{
					output << vertex << " ";
				}
				output << std::endl;
			}
			output << "}\n";
			return output;
		}

		void bfs(char start, int homework = 1)
		{
			std::queue<char> active_vertecies;
			std::map<char, bool> visited;
			std::map<char, int> depth;

			char current_vertex;

			for (const auto& [vertex, _] : this->adjacency_list) 
			{
				visited[vertex] = false;
				depth[vertex] = 9999999;
			}

			active_vertecies.push(start);
			visited[start] = true;
			depth[start] = 0;

			while (not active_vertecies.empty())
			{
				current_vertex = active_vertecies.front();
				active_vertecies.pop();

				for (const auto& v : adjacency_list[current_vertex])
				{
					if (not visited[v])
					{
						depth[v] = depth[current_vertex] + 1;
						visited[v] = true;
						active_vertecies.push(v);
					}
				}
			}

			if (homework == 1)
			{
				std::cout << "visited vertecies: ";
				for (const auto& [vertex, _] : visited)
					std::cout << vertex << " | ";
			}
			else if (homework == 2)
			{
				unsigned count = 0;
				std::cout << "vertecies that can't be reached: ";
				for (const auto& [vertex, _] : this->adjacency_list) 
				{
					if (not visited[vertex])
					{
						count++;
						std::cout << vertex << " | ";
					}
				}

				if (count == 0)
					std::cout << "There are no such vertecies";
			}
			else if (homework == 3)
			{
				unsigned count = 0;
				std::cout << "vertecies that are 2 depth far from starting vertex: ";
				for (const auto& [vertex, _] : visited)
				{
					if (depth[vertex] == 2)
					{
						count++;
						std::cout << vertex << " | ";
					}
				}
				if (count == 0)
					std::cout << "There are no such vertecies";
			}

			std::cout << std::endl;
		}

		void bfs_task_4()
		{
			std::queue<char> active_vertecies;
			std::map<char, bool> visited;
			std::map<char, bool> finished;
			std::map<char, bool> colored;

			char current_vertex;

			for (const auto& [vertex, _] : this->adjacency_list)
			{
				visited[vertex] = false;
				finished[vertex] = false;
				colored[vertex] = false;
			}

			for (const auto& [start, _] : this->adjacency_list)
			{
				if (not visited[start]) 
				{
					active_vertecies.push(start);
					visited[start] = true;
					colored[start] = true;

					while (not active_vertecies.empty())
					{
						current_vertex = active_vertecies.front();
						active_vertecies.pop();

						for (const auto& v : adjacency_list[current_vertex])
						{
							if (not visited[v])
							{
								colored[v] = not colored[current_vertex];
								visited[v] = true;
								active_vertecies.push(v);
							}
							else if (not finished[v] and colored[v] == colored[current_vertex])
							{
								std::cout << "Graph can't be colored in 2 colors" << std::endl;
								return;
							}
						}
						finished[current_vertex] = true;
					}
				}
			}

			for (const auto& [vertex, color] : colored)
				std::cout << vertex << " " << color << ", ";
		}

		friend std::ostream& operator <<(std::ostream& output, Graph& object)
		{
			object.__repr__(output);
			return output;
		}

	};

	void test_homework_1()
	{
		Graph b({ 'b', 'c', 'd', 'f' });

		b.add_edge('b', 'a');
		b.add_edge('a', 'd');
		b.add_edge('c', 'b');
		b.add_edge('d', 'b');
		b.add_edge('f', 'a');
		b.add_edge('f', 'c');

		std::cout << b << std::endl;

		// N1
		b.bfs('a');
		std::cout << std::endl;

		// N2
		b.bfs('d', 2);
		std::cout << std::endl;

		// N3
		b.bfs('a', 3);
		std::cout << std::endl;

		// N4
		Graph color_it(6);

		color_it.add_edge('a', 'c', false);
		color_it.add_edge('a', 'd', false);
		color_it.add_edge('c', 'b', false);
		color_it.add_edge('b', 'd', false);	
		color_it.add_edge('f', 'd', false);

		std::cout << color_it << std::endl;

		color_it.bfs_task_4();
	}
}

