#pragma once
#include <exception>

namespace Collection
{
	namespace Abstract 
	{
		class List
		{
		protected:
			unsigned actual_size = 0;
		public:
			bool is_empty() { return this->actual_size == 0; }
			unsigned size() { return this->actual_size; }

			struct IndexOutOfRange : public std::exception
			{
				const char* what() const throw ()
				{
					return "index out of range";
				}
			};
			struct ListEmpty : public std::exception
			{
				const char* what() const throw()
				{
					return "List is empty";
				}
			};
		};

		template <typename T>
		class DynamicList : public Abstract::List
		{
		protected:
			T* data = nullptr;
			unsigned capacity = 0;
		public:
			~DynamicList()
			{
				delete[] data;
			}

			virtual void push(T value) = 0;
			virtual void pop() = 0;

			T& operator[](int index)
			{
				if (index == this->capacity)
					throw DynamicList::IndexOutOfRange();
				return this->data[index];
			}

			std::ostream& __repr__(std::ostream& output)
			{
				if (this->is_empty())
					return output << "[]";
				output << "[ ";
				for (int i = 0; i < this->actual_size - 1; i++)
					output << this->data[i] << ", ";
				output << this->data[this->actual_size - 1];
				output << " ]";
				return output;
			}
		};

		template <typename T>
		class Node
		{
		public:
			T data;
			Node* next = nullptr;
			Node* prev = nullptr;
			Node(T value) : data(value) { }
		};

		template <typename T>
		class LinkedList : public Abstract::List
		{
		protected:
			Node<T>* first_node = nullptr;
			Node<T>* last_node = nullptr;
		public:
			~LinkedList()
			{
				if (this->is_empty())
					return;
				if (not this->first_node->next) 
				{
					delete this->first_node, this->last_node;
					return;
				}

				Node<T>* current_node = this->first_node->next;

				while (current_node->next != nullptr)
				{
					delete this->first_node;
					this->first_node = current_node;
					current_node = current_node->next;
				}
			}

			virtual void push(T value) = 0;
			virtual void pop() = 0;

			T operator [](unsigned index)
			{
				if (index < 0 or index > this->actual_size)
					throw LinkedList::IndexOutOfRange();

				unsigned start_index = 0;
				Node<T>* current_node = this->first_node;
				while (start_index++ != index)
				{
					current_node = current_node->next;
				}
				return current_node->data;
			}

			std::ostream& __repr__(std::ostream& output)
			{
				if (this->is_empty())
					return output << "[]";
				output << "[ ";
				Node<T>* current_node = this->first_node;
				for (unsigned i = 0; i < this->actual_size - 1; i++) 
				{
					output << current_node->data << ", ";
					current_node = current_node->next;
				}

				output << this->last_node->data;
				output << " ]";
				return output;
			}
		};
	}

	template <typename T = int>
	class List : public Abstract::DynamicList<T>
	{
	private:
		void push(T value) {}
		void pop() {}

		void increase_capacity(int increase_by = 1)
		{
			T* temp = new T[this->capacity];
			for (unsigned i = 0; i < this->capacity; i++)
				temp[i] = this->data[i];
			delete[] this->data;

			this->capacity += increase_by;
			this->data = new T[this->capacity];
			for (unsigned i = 0; i < this->capacity; i++)
				this->data[i] = temp[i];

			delete[] temp;
		}
	public:
		List(int size)
		{
			this->capacity = size;
			this->actual_size = 0;
			this->data = new T[size];
		}

		void erase(unsigned index)
		{
			if (this->is_empty())
				throw Abstract::List::ListEmpty();

			if (index < 0 or index >= this->actual_size)
				throw Abstract::List::IndexOutOfRange();

			for (unsigned i = index; i < this->actual_size; i++)
			{
				this->data[i] = this->data[i + 1];
			}
			this->actual_size--;
		}

		void insert(T value, unsigned index)
		{
			if (this->actual_size == this->capacity)
				this->increase_capacity();
			if (index < 0 or index > this->actual_size)
				throw Abstract::List::IndexOutOfRange();

			for (unsigned i = this->actual_size; i > index; i--)
			{
				this->data[i] = this->data[i - 1];
			}

			this->data[index] = value;
			this->actual_size++;
		}

		void push_back(T value)
		{
			if (this->actual_size == this->capacity)
				this->increase_capacity();

			this->data[this->actual_size++] = value;
		}

		template <typename obj_tpye>
		friend std::ostream& operator <<(std::ostream& output, List<obj_tpye>& object)
		{
			object.__repr__(output);
			return output;
		}
	};

	template <typename T = int>
	class LinkedList : public Abstract::LinkedList<T>
	{
	private:

	public:
		LinkedList(int size = 0)
		{
			this->actual_size = size;
		}

		bool is_empty() { return this->first_node == nullptr; }

		void push(T value)
		{
			if (this->is_empty())
			{
				this->first_node = this->last_node = new Abstract::Node<T>(value);
				this->actual_size++;
				return;
			}

			Abstract::Node<T>* new_node = new Abstract::Node<T>(value);
			new_node->next = this->first_node;
			this->first_node = new_node;
			this->actual_size++;
		}

		void pop() 
		{
			if (this->is_empty())
				throw Abstract::List::ListEmpty();

			if (not this->first_node->next) 
			{
				delete this->first_node, this->last_node;
				this->actual_size--;
				return;
			}

			Abstract::Node<T>* deleted_node = this->first_node;
			this->first_node = this->first_node->next;
			this->actual_size--;
			delete deleted_node;
			
		}

		template <typename obj_tpye>
		friend std::ostream& operator <<(std::ostream& output, LinkedList<obj_tpye>& object)
		{
			object.__repr__(output);
			return output;
		}
	};
}
