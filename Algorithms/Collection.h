#pragma once
#include <iostream>
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
			using ListEmpty = Abstract::List::ListEmpty;
		protected:
			T* data = nullptr;
			unsigned capacity = 0;

			virtual void push(T value) = 0;
			virtual void pop() = 0;
		public:
			~DynamicList()
			{
				delete[] data;
			}

			T& operator[](int index)
			{
				if (this->is_empty())
					throw ListEmpty();

				index = abs(index);
				if (index < 0)
					while (unsigned(index) >= this->actual_size)
					{
						index += this->actual_size;
					}
				else
					while (unsigned(index) >= this->actual_size)
					{
						index -= this->actual_size;
					}
				return this->data[index];
			}

			std::ostream& __repr__(std::ostream& output)
			{
				if (this->is_empty())
					return output << "[]";
				output << "[ ";
				for (unsigned i = 0; i < this->actual_size - 1; i++)
					output << this->data[i] << ", ";
				output << this->data[this->actual_size - 1];
				output << " ]";
				return output;
			}

			friend std::ostream& operator <<(std::ostream& output, DynamicList<T> object)
			{
				object.__repr__(output);
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
			Node(T value, Node<T>* next) : data(value), next(next) { }

			friend std::ostream& operator <<(std::ostream& output, Node& object)
			{
				return output << object.data;
			}
		};

		template <typename T>
		class LinkedList : public Abstract::List
		{
			using NodePointer = Node<T>*;

		protected:
			NodePointer first_node = nullptr;
			NodePointer last_node = nullptr;
			virtual void push(T value) = 0;
			virtual void pop() = 0;
		public:
			~LinkedList()
			{
				this->clear();
			}

			bool is_empty() { return this->first_node == nullptr; }

			void clear()
			{
				this->actual_size = 0;

				NodePointer current_node = this->first_node;
				NodePointer next_node = nullptr;

				while (not this->is_empty())
				{
					next_node = current_node->next;
					delete current_node;
					current_node = next_node;
					this->first_node = next_node;
				}
			}

			T operator [](int index)
			{
				while (unsigned(abs(index)) >= this->actual_size)
				{
					if (index < 0)
						index += this->actual_size;
					else
						index -= this->actual_size;
				}

				int start_index = 0;
				int up_to = index;
				NodePointer current_node = this->first_node;

				if (index < 0)
					up_to = this->actual_size + index;

				while (start_index++ != up_to)
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
				NodePointer current_node = this->first_node;
				for (unsigned i = 0; i < this->actual_size - 1; i++) 
				{
					output << *current_node << ", ";
					current_node = current_node->next;
				}

				output << this->last_node->data;
				output << " ]";
				return output;
			}

			friend std::ostream& operator <<(std::ostream& output, LinkedList& object)
			{
				object.__repr__(output);
				return output;
			}
		};
	}

	template <typename T = int>
	class List : public Abstract::DynamicList<T>
	{
		using ListEmpty = Abstract::List::ListEmpty;
		using IndexOutOfRange = Abstract::List::IndexOutOfRange;
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
		List()
		{
			this->capacity = 0;
			this->actual_size = 0;
			this->data = new T[0];
		}

		List(int size)
		{
			this->capacity = size;
			this->actual_size = 0;
			this->data = new T[size];
		}

		void erase(unsigned index)
		{
			if (this->is_empty())
				throw ListEmpty();

			if (index < 0 or index >= this->actual_size)
				throw IndexOutOfRange();

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

		T pop_back()
		{
			if (this->is_empty())
				throw ListEmpty();

			T deleted_value = this->data[--this->actual_size];

			this->increase_capacity(-1);
			return deleted_value;
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
		using ListEmpty = Abstract::List::ListEmpty;
		using Node = Abstract::Node<T>;
		using NodePointer = Node*;

	private:
		bool is_double_linked = false;
	public:
		LinkedList(bool is_double_linked = false) 
			: is_double_linked(is_double_linked)
		{
			this->actual_size = 0;
		}

		bool is_empty() { return this->first_node == nullptr; }

		void push(T value)
		{
			if (this->is_empty())
			{
				this->first_node = this->last_node = new Node(value);
				this->actual_size++;
				return;
			}

			this->first_node = new Node(value, this->first_node);

			if (this->is_double_linked and this->first_node->next)
				this->first_node->next->prev = this->first_node;

			this->actual_size++;
		}

		void push_back(T value)
		{
			if (this->is_empty())
			{
				this->first_node = this->last_node = new Node(value);
				this->actual_size++;
				return;
			}
			
			NodePointer new_node = new Node(value);
			this->last_node->next = new_node;

			if (this->is_double_linked)
				new_node->prev = this->last_node;

			this->last_node = new_node;

			this->actual_size++;
		}

		void pop() 
		{
			if (this->is_empty())
				throw ListEmpty();

			NodePointer deleted_node = this->first_node;
			this->first_node = this->first_node->next;
			if (this->is_double_linked)
				this->first_node->prev = nullptr;

			this->actual_size--;
			delete deleted_node;
		}

		void pop_back()
		{
			if (this->is_empty())
				throw ListEmpty();

			NodePointer deleted_node = this->last_node;

			//this->last_node = this[-1];
		}


		T first() { return this->first_node->data; }
		T last() { return this->last_node->data; }

	};

	template <typename T = int>
	class Stack : public LinkedList<T>
	{
	private:
		void push_back(T value) {};
	public:
	};
}
