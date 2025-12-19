#include<iostream>
#include<vector>
#include<string>
using namespace std;
#include "AllStruct.h"
#include "Ingredient.h"
void DisplayFoods(Stack<Ingredient> foods);
void Cook()
{
	string name;
	while (true)
	{
		cout << "请选择操作" << endl;
		cout << "1.添加食材" << endl;
		cout << "2.移除食材" << endl;
		cout << "3.开始烹饪" << endl;
		Stack<Ingredient> foods;
		int order;
		cin >> order;
		if (order == 1)
		{
			if (foods.size() == 5)
				cout << "食材已填满" << endl;
			else
			{
				DisplayFoods(foods);
				cout << "请选择要添加的食材" << endl;
				for (int i = 0;i < bag.size();i++)
				{
					cout << i + 1 << ". " << bag[i].GetName() << endl;
				}
				cin >> order;
				if (order > 0 && order <= bag.size())
				{
					foods.Push(bag[order - 1]);
					bag.RemoveUnit(order);
					cout << "已添加" << endl;
				}
				else
					cout << "无效选择" << endl;
			}
		}
		else if(order==2)
		{
			foods.Pop();
			cout << "已移除" << endl;
			DisplayFoods(foods);
		}
		else if(order==3)
		{
			int minID=FindMinID(foods.GetHead());//找到列表最小的ID
			List<Recipe>* rightRecipes=recipes[minID];//通过ID寻找菜谱
			List<Ingredient>foodList = StackToList<Ingredient>(foods);//把栈转换成链表，方便后续操作
			for(int i=0;i<rightRecipes->size();i++)
			{
				if((*rightRecipes)[i].Rule(foodList));
				name = (*rightRecipes)[i].GetName();
			}
			break;
		}
	}
}
void DisplayFoods(Stack<Ingredient> foods)
{
	cout << "当前食材:" << endl;
	if (foods.size() == 0)
		cout << "空" << endl;
	else
	{
		for (int i = 0;i < foods.size();i++)
		{
			cout << foods[i].GetName() << ' ';
		}
		cout << endl;
	}
}
void AddUnit()
{
	cout << "请选择要添加的物品" << endl;
	for (int i = 0;i < unitList.size();i++)
	{
		cout << i + 1 << ":" << unitList[i].GetName() << endl;
	}
	int order;
	cin >> order;
	bag.AddUnit(unitList[order - 1]);
	bag.Display();
}
int main()
{
	InitAllUnits();
	AddUnit();
}