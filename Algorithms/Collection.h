#pragma once
#include <exception>

namespace Collection
{

	class AbstractList
	{
	protected:
		int actual_size = NULL;
		int capacity = NULL;
	public:
		bool is_empty() { return this->actual_size == 0; }
		int size() { return this->actual_size; }

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
	class AbstractDynamicList : public AbstractList
	{
	protected:
		T* data = nullptr;
	public:
		~AbstractDynamicList()
		{
			delete[] data;
		}

		virtual void push() = 0;
		virtual void pop() = 0;

		T& operator[](int index)
		{
			if (index == this->capacity)
				throw AbstractList::IndexOutOfRange();
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

	/*template <typename T>
	class AbstractLinkedList : public AbstractList
	{
	protected:
		class Node 
		{
		public:
			T data;
			Node* next = nullptr;
			Node* prev = nullptr;
		};
		Node* first_node = nullptr;
		Node* last_node = nullptr;
	public:

		virtual void push() = 0;
		virtual void pop() = 0;

		T operator [](int index)
		{
			if (index < 0 or index > this->actual_size)
				throw AbstractLinkedList::IndexOutOfRange();

			int start_index = 0;
			Node* current_node = this->first_node;
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
			Node* current_node = this->first_node;
			while (current_node != this->last_node->prev)
				output << current_node.data << ", ";

			output << this->last_node.data;
			output << " ]";
			return output;
		}
	};*/
	

	template <typename T = int>
	class List : public AbstractDynamicList<T>
	{
	private:
		void push() {}
		void pop() {}

		void increase_capacity(int increase_by = 1)
		{
			T* temp = new T[this->capacity];
			for (int i = 0; i < this->capacity; i++)
				temp[i] = this->data[i];
			delete[] this->data;

			this->capacity += increase_by;
			this->data = new T[this->capacity];
			for (int i = 0; i < this->capacity; i++)
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

		void erase(int index)
		{
			if (this->is_empty())
				throw List::ListEmpty();

			if (index < 0 or index > this->actual_size)
				throw List::IndexOutOfRange();

			for (int i = index; i < this->actual_size; i++)
			{
				this->data[i] = this->data[i + 1];
			}
			this->actual_size--;
		}

		void insert(T value, int index)
		{
			if (this->actual_size == this->capacity)
				this->increase_capacity();
			if (index < 0 or index > this->actual_size)
				throw List::IndexOutOfRange();

			for (int i = this->actual_size; i > index; i--)
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

	/*template <typename T = int>
	class LinkedList : public AbstractLinkedList<T>
	{
	private:

	public:
		LinkedList(int size)
		{
			this->capacity = size;
			this->actual_size = 0;
		}

		void push(T value)
		{
			if (not this->first_node)
			{
				this->first_node = new Node(value);
				return;
			}

			Node* new_node = new Node(value);
			this->first_node->next = this->first_node;
			this->first_node = new_node;
		}
		void pop() 
		{

		}
	};*/
}
