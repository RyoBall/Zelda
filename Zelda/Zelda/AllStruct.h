#pragma once
#include<iostream>
#include<vector>
#include<string>
using namespace std;
class Data;
struct BagUnit
{
	string name;
	int ID;
	int num;
	BagUnit();
};
template<typename T>
struct ListNode
{
	ListNode<T>* next;
	T& data;
	ListNode<T>(T data) { this->data = data; }
	ListNode<T>() { }
};
template<typename T>
class Stack
{
public:
	void Display()
	{
		;
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
	void Insert(int pos,T data)
	{
		if(pos>length+1||pos<1)
		{
			return;
		}
		else
		{
			length++;
			ListNode<T>* node = new ListNode<T>(data);
			if(pos==1)
			{
				node->next = head;
				head = node;
				return;
			}
			ListNode<T>* tmp = head;;
			for(int i=1;i<pos-1;i++)
			{
				tmp = tmp->next;
			}
			node->next = tmp->next;
			tmp->next = node;
		}
	}
	void Delete(int pos)
	{
		if (pos > length + 1 || pos < 1)
		{
			return;
		}
		else
		{
			length--;
			ListNode<T>* tmp = head;;
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
protected:
	int length;
	ListNode<T>* head;
};
class Bag:public List<BagUnit>
{
public:
	void AddUnit(int ID)
	{
		ListNode<BagUnit>* tmp = head;
		while (tmp!=nullptr)
		{
			if(tmp->data.ID==ID)
			{
				tmp->data.num++;
			}
		}
		if (tmp == nullptr)
			;
	}
private:
};