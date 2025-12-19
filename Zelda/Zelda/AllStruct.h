#pragma once
#include<iostream>
#include<string>
#include<functional>
using namespace std;
class Player;

struct Food //背包单元,单个种类的物品
{
	string name;
	int ID;
	int num=0;
	float heal;
	float duration;
	function<void(Player&)> effect;
	Food(string name = "", int ID = 0, float heal = 0, float duraton = 0, function<void(Player&)> effect = [](Player& player) {;}) :name(name), ID(ID), heal(heal), duration(duration), effect(effect)
	{}
};

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

template<typename K,typename V>
struct HashData
{
	K key;
	V value;
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
	int size()
	{
		return length;
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
	ListNode<T>* GetHead()
	{
		return head;
	}
	int GetLength() { return length; }
protected:
	int length;
	ListNode<T>* head;
	ListNode<T>* last;
};
class Bag:public List<Food>
{
public:
	void Display()
	{
		cout << "====== BAG ======" << endl;
		for(int i=0;i<length;i++)
		{
			cout << (*this)[i].name<<"×"<<(*this)[i].num << endl;
		}
	}
	void AddUnit(Food unit)
	{
		ListNode<Food>* tmp = head;
		while (tmp!=nullptr)
		{
			if(tmp->data.ID==unit.ID)
			{
				tmp->data.num++;
			}
		}
		if (tmp == nullptr)
		{
			push_back(unit);
			Food t;
			(*this)[length - 1].num++;
		}
	}
	void RemoveUnit(int index)//index从1开始数
	{
		(*this)[index - 1].num--;
		if ((*this)[index - 1].num == 0)
		{
			(*this).Delete(index);
		}
	}
private:
};

extern List<Food> unitList;
extern Bag bag;
void InitAllUnits();

enum class FoodType {};
class Recipe//菜谱
{
public:
	bool rule(){}
	Recipe()
	{
		minID = FindMinID(specialFoodNeeds.GetHead());
	}
	int GetMinID()
	{
		return minID;
	}
private:
	int FindMinID(ListNode<Food>* f)
	{
		if(f->next==nullptr)
		{
			return f->data.ID;
		}
		else
		{
			int minID = FindMinID(f->next);
			if (f->data.ID < minID)
				return f->data.ID;
			else
				return minID;
		}
	}
	int minID;
	List<Food> specialFoodNeeds;
	function<bool(List<Food>)> checRule;
	string name;
};
//目前思路，需要一个map，然后把菜肴的数组放进map里

class HashList
{
public:
	HashList()
	{
		disks = new List<List<Recipe>>[size];
	}
	void Insert(Recipe disk)
	{
		int order=disk.GetMinID() % size;
		if(disks[order].GetLength()==0)
		{
			disks[order].push_back(List<Recipe>());
			disks[order][0].push_back(disk);
		}
		else
		{
			for(int i=0;i<disks[order].GetLength();i++)
			{
				if(disks[order][i][0].GetMinID() == disk.GetMinID())
				{
					disks[order][i].push_back(disk);
					return;
				}
			}
			disks[order].push_back(List<Recipe>());
			disks[order][disks[order].GetLength() - 1].push_back(disk);
		}
	}
	const List<Recipe>* FindDisks(int ID)
	{
		int order = ID % size;
		for(int i=0;i<disks[order].GetLength();i++)
		{
			if (disks[order][i][0].GetMinID() == ID)
				return &(disks[order][i]);
		}
		return nullptr;
	}
private:
	int size=30;
	List<List<Recipe>>* disks;
};//简单实现一个类哈希表，哈希函数不太实用，甚至由于ID数量可能不太够导致只是一个数组而已
void SortIngredientIDs(std::vector<int>ids)
{
	for (int i = 1; i < ids.size(); ++i)
	{
		int key = ids[i];
		int j = i - 1;
		while (j >= 0 && ids[j] > key)
		{
			ids[j + 1] = ids[j];
			--j;
		}
		ids[j + 1] = key;
	}
}