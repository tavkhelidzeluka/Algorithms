#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <queue>


namespace graph_homework_1 {
	/*
		Lab 3 homework N1
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
		void add_edge(char from, char to)
		{
			for (const auto& vertex : this->adjacency_list[from])
				if (vertex == to)
					return;

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

		void bfs(char start)
		{
			std::queue<char> active_vertecies;
			std::map<char, bool> visited;
			char current_vertex;

			for (const auto& [key, value] : visited)
				visited[key] = false;

			active_vertecies.push(start);
			visited[start] = true;

			while (not active_vertecies.empty())
			{
				current_vertex = active_vertecies.front();
				active_vertecies.pop();

				for (const auto& v : adjacency_list[current_vertex])
				{
					if (not visited[v])
					{
						visited[v] = true;
						active_vertecies.push(v);
					}
				}
			}

			std::cout << "visited vertecies: ";
			for (const auto& [vertex, _] : visited)
				std::cout << vertex << " | ";
		}

		friend std::ostream& operator <<(std::ostream& output, Graph& object)
		{
			object.__repr__(output);
			return output;
		}

	};

}

