#include<iostream>
#include<vector>
#include<string>
using namespace std;
#include "AllStruct.h"
struct Effect
{
	string name;
	float duration;
};
int main()
{
	InitAllUnits();
	AddUnit();
}
void Cook()
{
	while (true)
	{
		cout << "请选择操作" << endl;
		cout << "1.添加食材" << endl;
		cout << "2.开始烹饪" << endl;
		Stack<Food> foods;
		int order;
		cin >> order;
		if (order == 1)
		{
			if (foods.size() == 5)
				cout << "食材已填满" << endl;
			else
			{
				cout << "当前食材:" << endl;
				if (foods.size() == 0)
					cout << "空" << endl;
				else
				{
					for (int i = 0;i < foods.size();i++)
					{
						cout << foods[i].name << ' ';
					}
					cout << endl;
				}
				cout << "请选择要添加的食材" << endl;
				for(int i=0;i<bag.size();i++)
				{
					cout<<i+1<<". "<< bag[i].name <<endl;
				}
				cin >> order;
				if (order > 0 && order <= bag.size())
				{
					foods.Push(bag[order-1]);
					bag.RemoveUnit(order);
					cout << "已添加" << endl;
				}
				else
					cout << "无效选择" << endl;
			}

		}
	}
}
void AddUnit()
{
	cout << "请选择要添加的物品" << endl;
	for (int i = 0;i < unitList.size();i++)
	{
		cout << i + 1 << ":" << unitList[i].name << endl;
	}
	int order;
	cin >> order;
	bag.AddUnit(unitList[order - 1]);
	bag.Display();
}