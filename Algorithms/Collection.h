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
			virtual T pop() = 0;
		public:
			~DynamicList()
			{
				delete[] data;
			}

			void clear()
			{
				delete this->data;
				this->data = nullptr;
				this->capacity = 0;
				this->actual_size = 0;
			}

			T& operator[](int index)
			{
				if (this->is_empty())
					throw ListEmpty();

				while (unsigned(abs(index)) >= this->actual_size)
				{
					if (index > 0)
						index -= this->actual_size;
					else
						index += this->actual_size;
				}
				if (index < 0)
					index = this->actual_size + index;

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

		void push(T value)
		{
			if (this->actual_size == this->capacity)
				this->increase_capacity();

			for (unsigned i = this->actual_size++; i > 0; i--)
				this->data[i] = this->data[i - 1];

			this->data[0] = value;
		}

		T pop_back()
		{
			if (this->is_empty())
				throw ListEmpty();

			T deleted_value = this->data[--this->actual_size];

			this->increase_capacity(-1);
			return deleted_value;
		}

		T pop()
		{
			if (this->is_empty())
				throw ListEmpty();

			T deleted_value = this->data[0];

			for (unsigned i = 0; i < this->actual_size; i++)
				this->data[i] = this->data[i + 1];

			this->actual_size--;
			this->increase_capacity(-1);
			return deleted_value;
		}

		template <typename obj_tpye>
		friend std::ostream& operator <<(std::ostream& output, List<obj_tpye>& object)
		{
			return object.__repr__(output);
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

		LinkedList(LinkedList& object)
		{
			this->operator=(object);
		}

		void operator =(LinkedList& object)
		{
			if (not object.is_empty())
			{
				this->~LinkedList();
				this->first_node = new Node(object.first_node->data);

				NodePointer current_node = this->first_node;
				NodePointer other_node = object.first_node;
				this->actual_size = object.actual_size;
				this->is_double_linked = object.is_double_linked;

				for (unsigned i = 0; i < object.actual_size - 1; i++)
				{
					current_node->next = new Node(other_node->next->data);
					if (object.is_double_linked)
						current_node->next->prev = current_node;
					current_node = current_node->next;
					other_node = other_node->next;
				}
				this->last_node = current_node;
			}
		}

		~LinkedList() = default;

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

			if (this->actual_size == 1) {
				this->actual_size = 0;
				delete this->first_node, this->last_node;
				this->first_node = this->last_node = nullptr;
				return;
			}

			NodePointer deleted_node = this->last_node;
			NodePointer current_node = this->first_node;
			
			this->actual_size--;

			while (current_node->next != this->last_node)
				current_node = current_node->next;

			current_node->next = nullptr;
			this->last_node = current_node;
			delete deleted_node;
		}


		T first() { return this->first_node->data; }
		T last() { return this->last_node->data; }

	};

	template <typename T = int>
	class Stack : private LinkedList<T>
	{
		using LinkedList = LinkedList<T>;
	private:
		bool add_from_back = true;
	public:

		Stack() = default;
		Stack(bool add_from_back)
			: add_from_back(add_from_back)
		{}

		void push(T value) 
		{
			this->add_from_back ? LinkedList::push_back(value) : LinkedList::push(value);
		}

		void pop()
		{
			this->add_from_back ? LinkedList::pop_back() : LinkedList::pop();
		}

		T top()
		{
			return this->add_from_back ? LinkedList::last() : LinkedList::first();
		}

		using LinkedList::clear;
		using LinkedList::__repr__;
		using LinkedList::is_empty;
		using LinkedList::size;

		friend std::ostream& operator << (std::ostream& output, Stack& object)
		{
			return object.__repr__(output);
		}
	};

	template <typename T = int>
	class Queue : private LinkedList<T>
	{
		using LinkedList = LinkedList<T>;

	private:
		bool add_from_back = true;
	public:
		Queue() = default;
		Queue(bool add_from_back)
			: add_from_back(add_from_back)
		{

		}

		void pop()
		{
			this->add_from_back ? LinkedList::pop() : LinkedList::pop_back();
		}

		void push(T value)
		{
			this->add_from_back ? LinkedList::push_back(value) : LinkedList::push(value);
		}

		T first()
		{
			this->add_from_back ? LinkedList::first() : LinkedList::Last();
		}

		using LinkedList::clear;
		using LinkedList::__repr__;
		using LinkedList::is_empty;
		using LinkedList::size;

		friend std::ostream& operator <<(std::ostream& output, Queue& object)
		{
			return object.__repr__(output);
		}
	};

	namespace Generic
	{
		template <typename T = int>
		class Stack : private List<T>
		{
			using List = List<T>;
		private:
			bool add_from_back = true;
		public:

			void push(T value)
			{
				this->add_from_back ? List::push_back(value) : List::push(value);
			}

			T pop()
			{
				return this->add_from_back ? List::pop_back() : List::pop();
			}

			T top()
			{
				return this->add_from_back ? this->operator[](-1) : this->operator[](0);
			}

			using List::clear;
			using List::size;
			using List::__repr__;
			using List::operator[];

			friend std::ostream& operator <<(std::ostream& output, Stack& object)
			{
				return object.__repr__(output);
			}
		};
	}
}
