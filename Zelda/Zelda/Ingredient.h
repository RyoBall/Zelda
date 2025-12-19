#pragma once
#include<iostream>
#include<string>
#include<unordered_map>
#include "AllStruct.h"
class Ingredient;
extern List<Ingredient> unitList;
enum class IngredientType { Fruit, Meat, Mushroom, Vegetable, Nut, Fish, Monster,Insect };
enum class EffectType {
	None,
	Attack,
	Defence,
	Speed,
	Health,
	Sneaky,
	WarmDef,
	ColdDef,
	FireDef,
	IceDef,
	ParalysisDef
};
static BaseHashList<EffectType,std::string>EffectBaseName;
void InitEffectBaseName();
struct Effect
{
	EffectType effectType;
	int level;
	std::string name;
	std::string GetName();
	Effect(EffectType type, int level, std::string name = "") :effectType(type), level(level), name(name) {}
	Effect() {}
};
class Ingredient
{
private:
	int ID;
	std::string name;
	float basicHealValue;
	float cookedHealValue;
	float duration;
	Effect effect;
	IngredientType type;
	std::string description;
public:
	int num;
	Ingredient(std::string name, int id, float basicHV,float duration,  IngredientType ty, std::string desc="", Effect eft = {EffectType::None, 0, ""}) :ID(id), name(name), basicHealValue(basicHV),duration(duration), cookedHealValue(2 * basicHV), description(desc), type(ty), effect(eft) { num=0; }
	Ingredient() { num=0; }
	std::string GetName()const;
	std::string GetDesc()const;
	EffectType GetCookedEffect();
	int GetHealValue();
	int GetID() const;
	IngredientType GetType() const{ return type; }
	bool operator == (const Ingredient& ohterIngredient);
};

int FindMinID(ListNode<Ingredient>* f);

template<typename T>
List<T> StackToList(Stack<T> stack){
	List<T> list;
	T food;
	for (int i = 0;i < list.size();i++)
	{
		stack.Pop(food);
		list.push_back(food);
	}
	return list;
}


struct RecipeTypeNeed{
	IngredientType type;
	int num;
	RecipeTypeNeed(IngredientType type, int num) :type(type), num(num) {  }
};//存储代表需要多少什么种类的要求的结构体
class Recipe//菜谱
{
public:
	bool Rule(const List<Ingredient>& foods,const List<IngredientType>& foodTypes)
	{
		int* ptr;
		for(int i=0;i<foods.size();i++)
		{
			bool r=false;
			ptr=specialIngredientNeeds[foods[i].GetID()];
			if (ptr != nullptr)
			{
				*ptr++;
				r = true;
			}
			if (r)
				break;
			for(int j=0;j<specialIngredientNeedsAlternative.size();i++)
			{
				ptr = specialIngredientNeedsAlternative[j][foods[i].GetID()];
				if (ptr != nullptr)
				{
					*ptr++;
					r = true;
					break;
				}
			}
			if (r)
				break;
			ptr=typeNeeds[foods[i].GetType()];
			if (ptr != nullptr)
			{
				*ptr++;
				r = true;
			}
			if (!r)
				return false;
		}
		//待做项：检测哈希表中的数据是否全部都+1.
	 	/*if (specialIngredientNeedsAlternative.size()>0)
		{
			for(int i=0;i<specialIngredientNeedsAlternative.size();i++)
			{
				bool rc = false;
				for(int j=0;j<specialIngredientNeedsAlternative[i].size();j++)
				{
					for(int i_=0;i_<foods.size();i_++)
					{
						if(foods[i_].GetID()==specialIngredientNeedsAlternative[i][j].GetID())
						{
							rc = true;
							break;
						}
					}
					if (rc)
						break;
				}
				if (!rc)
					return false;
			}
		}
		//第一步，对比可选的项目
		if(specialIngredientNeeds.size()>0)
		{
			for(int i=0;i<specialIngredientNeeds.size();i++)
			{
				bool rc = false;
				for(int j=0;j<specialIngredientNeeds.size();j++)
				{
					if(specialIngredientNeeds[i].GetID()==foods[j].GetID())
					{
						rc = true;
						break;
					}
				}
				if (!rc)
					return false;
			}
		}
		//第二步,对比特定的项目
		if(typeNeeds.size()>0)
		{
			for(int i=0;i<typeNeeds.size();i++)
			{
				bool rc=false;
				for(int j=0;j<foodTypes.size();j++)
				{
					if(typeNeeds[i].type==foodTypes[j])
					{
						rc = true;break;
					}
				}
				if (!rc)
					return false;
			}
		}
		//第三步,对比类型需求
		for(int i=0;i<foods.size();i++)
		{
			for(int i1=0;i1<)
		}*/
		return true;
	}
	string GetName()
	{
		return name;
	}
	Recipe()
	{
		minID = FindMinID(allSpecialIngredients.GetHead());
	}
	Recipe(List<Ingredient> specialIngredientNeeds, List<List<Ingredient>> specialIngredientNeedsAlternative,List<RecipeTypeNeed> typeNeeds):specialIngredientNeedsAlternative(specialIngredientNeedsAlternative), specialIngredientNeeds(specialIngredientNeeds), typeNeeds(typeNeeds)
	{
		minID = FindMinID(allSpecialIngredients.GetHead());
	}
	int GetMinID()
	{
		return minID;
	}
private:
	int minID;
	List<int> allSpecialIngredients;
	List<List<int>> allAlterNativeSpecialIngredients;
	List<IngredientType> allTypeNeeds;
	BaseHashList<int,int> specialIngredientNeeds;
	List<BaseHashList<int,int>> specialIngredientNeedsAlternative;
	BaseHashList<IngredientType,int> typeNeeds;
	string name;
};

class RecipeHashList:public BaseHashList<int,List<Recipe>>
{
public:
	RecipeHashList()
	{
		
	}
	void Insert(Recipe disk)
	{
		int order = disk.GetMinID() % size;
		if (Node[order].GetLength() == 0)
		{
			Node[order].push_back(HashData(disk.GetMinID(), List<Recipe>(),false));
			Node[order][0].data.push_back(disk);
		}
		else
		{
			for (int i = 0;i < Node[order].GetLength();i++)
			{
				if (Node[order][i].data[0].GetMinID() == disk.GetMinID())
				{
					Node[order][i].data.push_back(disk);
					return;
				}
			}
			Node[order].push_back(HashData(disk.GetMinID(), List<Recipe>(),false));
			Node[order][Node[order].size() - 1].data.push_back(disk);
		}
	}
	const List<Recipe>* FindDisks(int ID)
	{
		return nullptr;
		int order = ID % size;
		for (int i = 0;i < Node[order].GetLength();i++)
		{
			if (Node[order][i].data[0].GetMinID() == ID)
				return &(Node[order][i].data);
		}
		return nullptr;
	}
private:
};

extern RecipeHashList recipes;

class Bag :public List<Ingredient>
{
public:
	void Display()
	{
		cout << "====== BAG ======" << endl;
		for (int i = 0;i < length;i++)
		{
			cout << (*this)[i].GetName() << "×" << (*this)[i].num << endl;
		}
	}
	void AddUnit(Ingredient unit)
	{
		ListNode<Ingredient>* tmp = head;
		while (tmp != nullptr)
		{
			if (tmp->data.GetID() == unit.GetID())
			{
				tmp->data.num++;
			}
		}
		if (tmp == nullptr)
		{
			push_back(unit);
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
extern Bag bag;
void InitAllUnits();
extern BaseHashList<string, Ingredient> ingredientMap;