#include<iostream>
#include<string>
using namespace std;
#include "AllStruct.h"
#include "Ingredient.h"
List<Disk> disks;
void DisplayFoods(Stack<Ingredient> foods);
int GetTypeNum(const List<Ingredient>& foods)
{
	List<IngredientType> types;
	types.push_back(foods[0].GetType());
	for (int i = 1;i < foods.size();i++)
	{
		IngredientType chec = foods[i].GetType();
		bool same = false;
		for (int j = 0;j < types.size();j++)
		{
			if (chec == types[j])
			{
				same = true;
				break;
			}
		}
		if (!same)
			types.push_back(chec);
	}
	int num = 0;
	for (int i = 0;i < types.size();i++)
	{
		num += static_cast<int>(types[i]) * 5 + 3;
	}
	return num;
}
void Cook()
{
	string name = "";
	Stack<Ingredient> foods;
	while (true)
	{
		cout << "===请选择操作===" << endl;
		cout << "1.添加食材" << endl;
		cout << "2.移除食材" << endl;
		cout << "3.开始烹饪" << endl;
		cout << "4.结束烹饪" << endl;
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
		else if (order == 2)
		{
			foods.Pop();
			cout << "已移除" << endl;
			DisplayFoods(foods);
		}
		else if (order == 3)
		{
			int minID = FindMinID(foods.GetHead());//找到列表最小的ID
			List<Recipe>* rightRecipes = IDRecipeMap[minID];//通过ID寻找菜谱
			List<Ingredient>foodList = StackToList<Ingredient>(foods);//把栈转换成链表，方便后续操作
			if (rightRecipes != nullptr)
			{
				for (int i = 0;i < rightRecipes->size();i++)
				{
					cout << "IDFind:" << (*rightRecipes)[i].GetName() << endl;
					if ((*rightRecipes)[i].Rule(foodList))
					{
						name = (*rightRecipes)[i].GetName();
						cout << "成功制作:" << name << endl;
						Disk disk = GetFinalDisk(foodList, name);
						disks.push_back(disk);
						foods.Clear();
						break;
					}
				}
			}
			if (name == "")
			{
				int num = GetTypeNum(foodList);
				rightRecipes = TypeRecipeMap[num];
				if (rightRecipes == nullptr)
				{
					cout << "未找到同类菜谱" << endl;
				}
				else
				{
					for (int i = 0;i < rightRecipes->size();i++)
					{
						cout << "TypeFind:" << (*rightRecipes)[i].GetName() << endl;
						if ((*rightRecipes)[i].Rule(foodList))
						{
							name = (*rightRecipes)[i].GetName();
							cout << "成功制作:" << name << endl;
							Disk disk = GetFinalDisk(foodList, name);
							disks.push_back(disk);
							foods.Clear();
							break;
						}
					}
				}
				if (name == "")
				{
					cout << "未找到菜谱" << endl;
					foods.Clear();
				}
				else
					cout << name << endl;
			}
		}
		else if (order == 4)
			break;
		else
			cout << "无效输入" << endl;
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
	while (true)
	{
		cin >> order;
		if (order<1 || order>unitList.size())
		{
			cout << "无效选择" << endl;
			continue;
		}
		break;
	}
	int num;
	cout << "请输入添加数量" << endl;
	cin >> num;
	if (num < 0)
	{
		cout << "无效输入，默认为1" << endl;
		num = 1;
	}
	bag.AddUnit(unitList[order - 1], num);
	bag.Display();
}
void DisplayDisks(const List<Disk>& disks)
{
	cout << "====菜肴====" << endl;
	for(int i=0;i<disks.size();i++)
	{
		cout << i + 1 << '.' << disks[i].name << endl;
	}
	while(true)
	{
	cout << "请选择操作" << endl;
	cout << "0.结束" << endl;
	cout << "1.展示详细属性" << endl;
	int order;
	cin >> order;
	if (order == 0)
		break;
	else if(order==1)
	{
		cout << "请选择要展示的菜肴" << endl;
		cin >> order;
		if(order>0&&order<=disks.size())
		{
			DisplayDisk(disks[order-1]);
		}
	}
	}
}
int main()
{
	InitAllUnits();
	InitEffectBaseName();
	InitAllRecipes();
	int order;
	while (true)
	{
		cout << "欢迎来到旷野之息烹饪模拟,请选择操作" << endl;
		cout << "1. 查看食材背包" << endl;
		cout << "2. 添加食材" << endl;
		cout << "3. 开始烹饪" << endl;
		cout << "4. 查看菜肴背包" << endl;
		cin >> order;
		if (order == 1)
			bag.Display();
		else if (order == 2)
			AddUnit();
		else if (order == 3)
			Cook();
		else if (order == 4)
			DisplayDisks(disks);
		else
			cout << "无效输入" << endl;
	}
	AddUnit();
}
//2 34 2 2 49 2 3 1 1 1 2 3
//2 32 5 2 70 5 2 73 5 2 82 5 3 1 1 1 2 1 3 1 4 3