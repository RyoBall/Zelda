#pragma once
#include<iostream>
#include<string>
#include<functional>
using namespace std;
class Player;


template<typename T>
struct ListNode //节点
{
	ListNode<T>* next;
	T data;
	ListNode<T>(T data) :data(data)
	{
		next = nullptr;
	}
	ListNode<T>() { 
		next = nullptr;
	}
};

template<typename T>
class Stack
{
public:
	T& operator[](int index)
	{
		if (index > length - 1 || index < 0)
		{
			throw std::out_of_range("Index out of bounds");
		}
		ListNode<T>* tmp = head;
		for (int i = 0;i < index;i++)
			tmp = tmp->next;
		return tmp->data;
	}
	void Display()
	{
		;
	}
	int size()
	{
		return length;
	}
	void Push(T data)
	{
		length++;
		ListNode<T>* node = new ListNode<T>(data);
		if(head==nullptr)
		{
			head = node;
		}
		else
		{
			node->next = head;
			head = node;
		}
	}
	void Pop(T& data)
	{
		if (head == nullptr)
			return;
		else
		{
			length--;
			ListNode<T>* tmp = head;
			head = head->next;
			data = tmp->data;
			delete tmp;
		}
	}
	void Pop()
	{
		if (head == nullptr)
			return;
		else
		{
			length--;
			ListNode<T>* tmp = head;
			head = head->next;
			delete tmp;
		}
	}
	ListNode<T>* GetHead()
	{
		return head;
	}
	Stack()
	{
		head = nullptr;
	}
private:
	int length;
	ListNode<T>* head;
};

template<typename T>
class List
{
public:
	T& operator[](int index)
	{
		if (index > length - 1||index<0)
		{
			throw std::out_of_range("Index out of bounds");
		}
		ListNode<T>* tmp = head;
		if (index == length - 1)
			return last->data;
		for (int i = 0;i < index;i++)
			tmp = tmp->next;
		return tmp->data;
	}
	const T& operator[](int index)const
	{
		if (index > length - 1||index<0)
		{
			throw std::out_of_range("Index out of bounds");
		}
		ListNode<T>* tmp = head;
		if (index == length - 1)
			return last->data;
		for (int i = 0;i < index;i++)
			tmp = tmp->next;
		return tmp->data;
	}
	void Insert(int pos,T data)
	{
		if (pos > length + 1 || pos < 1)
		{
			return;
		}
		else if (pos == length + 1)
			push_back(data);
		else
		{
			length++;
			ListNode<T>* node = new ListNode<T>(data);
			if(length==1)
			{
				head = last = node;
			}
			if(pos==1)
			{
				node->next = head;
				head = node;
				return;
			}
			ListNode<T>* tmp = head;
			for(int i=1;i<pos-1;i++)
			{
				tmp = tmp->next;
			}
			node->next = tmp->next;
			tmp->next = node;
		}
	}
	void push_back(T data)
	{
		length++;
		ListNode<T>* node = new ListNode<T>(data);
		if (length == 1)
			last = head = node;
		else
		{
			last->next = node;
			last = node;
		}
	}
	void Delete(int pos)//pos从1开始数
	{
		if (pos > length + 1 || pos < 1||length==0)
		{
			return;
		}
		else if(pos==length+1)
		{
			length--;
			delete last;
			ListNode<T>* tmp = head;
			for (int i = 1;i < length;i++)
				tmp = tmp->next;
			last = tmp;
		}
		else
		{
			length--;
			ListNode<T>* tmp = head;
			for (int i = 1;i < pos - 1;i++)
			{
				tmp = tmp->next;
			}
			if(tmp->next!=nullptr)
			tmp -> next = tmp->next->next;
			else
			{
				tmp->next = nullptr;
			}
		}
	}
	List<T>() { length = 0 ;head = last = nullptr; }
	List<T>(std::initializer_list<T> datas)
	{
		length = 0;head = last = nullptr;
		for (const auto& item : datas) {
			push_back(item);
		}
	}
	ListNode<T>* GetHead()
	{
		return head;
	}
	int size()const {return length;}
protected:
	int length;
	ListNode<T>* head;
	ListNode<T>* last;
};
//目前思路，需要一个map，然后把菜肴的数组放进map里
template<typename K,typename T>
class BaseHashList
{
public:
	struct HashData
	{
		T data;
		int key;
		HashData() : data(T()), key(0) {}
		HashData(int key, T data,bool in) :data(data), key(key) {}
		HashData(K key, T data) :data(data), key(BaseHashList<K, T>::HashFunc(key)) {}
	};
	BaseHashList(std::initializer_list<std::pair<K, T>> datas)
	{
		Node = new List<HashData>[mapSize];
		for (auto& item : datas)
		{
			InsertByKey(item.first, item.second);
		}
	}
	BaseHashList()
	{
		Node = new List<HashData>[mapSize];
	}
	void InsertByKey(K key, T data)
	{
		int id = HashFunc(key);
		if (id < 0)
			id = -id;
		Insert(id, data);
	}
	void InsertByKey(K key, T data,bool is)
	{
		int id = HashFunc(key);
		Insert(id, data);
	}
	T* operator[](K key)
	{
		int id = HashFunc(key);
		int order = id% 30;
		for (int i = 0;i < Node[order].size();i++)
		{
			if (Node[order][i].key == id)
				return &(Node[order][i].data);
		}
		return nullptr;
	}
protected:
	bool Insert(int id,T data)
	{
		int order = id % mapSize;
		if (Node[order].size() == 0)
		{
			Node[order].push_back(HashData(id, data,false));
		}
		else
		{
			for (int i = 0;i < Node[order].size();i++)
			{
				if (Node[order][i].key == id)
				{
					Node[order][i].data = data;
					return false;
				}
			}
			Node[order].push_back(HashData(id, data,false));
		}
		return true;
	}
	static int HashFunc(K key)
	{
		int id=std::hash<K>{}(key);
		if (id < 0)
			id = -id;
		return id;
	}
	const int mapSize=30;
	List<HashData>* Node;
};
//简单实现一个类哈希表，哈希函数不太实用，甚至由于ID数量可能不太够导致只是一个数组而已

template<typename T>
List<T> StackToList(Stack<T> stack) {
	List<T> list;
	T food;
	int size = stack.size();
	for (int i = 0;i < size;i++)
	{
		stack.Pop(food);
		list.push_back(food);
	}
	return list;
}
