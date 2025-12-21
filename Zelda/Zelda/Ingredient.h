#pragma once
#include<iostream>
#include<string>
#include "AllStruct.h"
class Ingredient;
extern BaseHashList<int, Ingredient> ingredientMapID;
extern List<Ingredient> unitList;
enum class IngredientType { Fruit, Meat, Mushroom, Vegetable, Nut, Fish, Monster,Insect,Other };
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
	ParalysisDef
};
static BaseHashList<EffectType,std::string>EffectBaseName;
extern BaseHashList<EffectType,std::string>EffectNameInDisk;
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
	int num=0;
	Ingredient(std::string name, int id, float basicHV,float duration,  IngredientType ty, std::string desc="", Effect eft = {EffectType::None, 0, ""}) :ID(id), name(name), basicHealValue(basicHV),duration(duration), cookedHealValue(2 * basicHV), description(desc), type(ty), effect(eft) { num=0; }
	Ingredient() { num=0; }
	std::string GetName()const;
	std::string GetDesc()const;
	EffectType GetCookedEffectType() const;
	int GetID() const;
	float GetDuration() const;
	int GetHealValue() const;
	float GetCookHealValue() const;
	Effect GetEffect()const;
	IngredientType GetType() const{ return type; }
	bool operator == (const Ingredient& ohterIngredient);
};

int FindMinID(ListNode<Ingredient>* f);
int FindMinID(ListNode<int>* f);


struct RecipeTypeNeed{
	IngredientType type;
	int num;
	RecipeTypeNeed(IngredientType type, int num) :type(type), num(num) {  }
};//存储代表需要多少什么种类的要求的结构体
class Recipe//菜谱
{
public:
	bool Rule(const List<Ingredient>& foods)
	{
		int* ptr;
		cout << "可选数量" << this->specialIngredientNeedsAlternative.size() << endl;
		foods.size();
		for(int i=0;i<foods.size();i++)
		{
			bool r=false;
			cout << "当前食材:" << foods[i].GetName()<<endl;
			ptr=specialIngredientNeeds[foods[i].GetID()];
			if (ptr != nullptr)
			{
				(*ptr)++; 
				r = true;
				cout << "相同匹配" << endl;
			}
			if (r)
				continue;
			for(int j=0;j<specialIngredientNeedsAlternative.size();j++)
			{
				
				ptr = specialIngredientNeedsAlternative[j][foods[i].GetID()];
				if (ptr != nullptr)
				{
				cout << "可选匹配" << endl;
					(*ptr)++; 
					r = true;
					break;
				}
			}
			if (r)
				continue;
			ptr=typeNeeds[foods[i].GetType()];
			if (ptr != nullptr)
			{
				cout << "种类匹配" << endl;
				(*ptr)++; 
				r = true;
			}
			if (!r)
				return false;
		}
		//待做项：检测哈希表中的数据是否全部都+1.
		//1 特定项
		for(int i=0;i<allSpecialIngredients.size();i++)
		{
			if(*(specialIngredientNeeds[allSpecialIngredients[i]])<=0)
			{
				return false;
			}
			else
			{
				*(specialIngredientNeeds[allSpecialIngredients[i]]) = 0;
			}
		}
		//2 可选特定项
		for (int i = 0;i < specialIngredientNeedsAlternative.size();i++)
		{
			bool r = false;
			for(int j=0;j<allAlterNativeSpecialIngredients[i].size();j++)
			{
				if (*(specialIngredientNeedsAlternative[i][allAlterNativeSpecialIngredients[i][j]]) > 0)
					r = true;
				*(specialIngredientNeedsAlternative[i][allAlterNativeSpecialIngredients[i][j]]) = 0;
			}
			if (!r)
				return false;
		}
		//3 类别项
		for(int i=0;i<allTypeNeeds.size();i++)
		{
			if (*(typeNeeds[allTypeNeeds[i]]) <= 0)
				return false;
			*(typeNeeds[allTypeNeeds[i]]) = 0;
		}
		return true;
	}
	string GetName()
	{
		return name;
	}
	Recipe()
	{
		minID = 0;
	}
	Recipe(string name,List<int> allSPneeds, List<List<int>> allASPneeds,List<IngredientType> allTypeNeeds, BaseHashList<int, int> specialIngredientNeeds, List<BaseHashList<int, int>> specialIngredientNeedsAlternative, BaseHashList<IngredientType, int>typeNeeds):specialIngredientNeedsAlternative(specialIngredientNeedsAlternative), specialIngredientNeeds(specialIngredientNeeds), typeNeeds(typeNeeds),allAlterNativeSpecialIngredients(allASPneeds),allSpecialIngredients(allSPneeds),allTypeNeeds(allTypeNeeds),name(name)
	{
		aSI = List<int>();
		InitMinID();
		InitTypeSum();
	}
	int GetMinID() const
	{
		return minID;
	}
	int GetTypeNum() const
	{
		return typeNum;
	}
private: 
	void InitMinID()
	{
		List<int> tmpList;
		tmpList.push_back(FindMinID(allSpecialIngredients.GetHead()));
		for (int i = 0;i < allSpecialIngredients.size();i++)
			aSI.push_back(allSpecialIngredients[i]);
		for(int i=0;i<allAlterNativeSpecialIngredients.size();i++)
		{
			for(int j=0;j<allAlterNativeSpecialIngredients[i].size();j++)
			aSI.push_back(allAlterNativeSpecialIngredients[i][j]);
		}
		if (tmpList.size() != 0)
		{
			minID = FindMinID(tmpList.GetHead());
		}
		else
		{
			minID = 0;
		}
	}
	void InitTypeSum()
	{
		List<int> types;
		for(int i=0;i<allTypeNeeds.size();i++)
		{
			types.push_back(static_cast<int>(allTypeNeeds[i]));
		}
		for(int i=0;i<aSI.size();i++)
		{
			int chec = static_cast<int>(ingredientMapID[aSI[i]]->GetType());
			bool same=false;
			for(int j=0;j<types.size();j++)
			{
				if(chec==types[j])
				{
					same = true;
					break;
				}
			}
			if(!same)
				types.push_back(chec);
		}
		int num=0;
		for(int i=0;i<types.size();i++)
		{
			num += types[i] * 5 + 3;
		}
		typeNum = num;
	}
	int minID;
	int typeNum;
	List<int> aSI;//所有的特殊要求，包括可选
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
	RecipeHashList():BaseHashList()
	{
		
	}
	virtual void Insert(const Recipe& disk)
	{
		;
	}
private:
};

class RecipeHashListID:public RecipeHashList
{
public:
	RecipeHashListID() :RecipeHashList()
	{}
	void Insert(const Recipe& disk) override
	{
		int id = HashFunc(disk.GetMinID());
		int order = id%mapSize;
		if (Node[order].size() == 0)
		{
			Node[order].push_back(HashData(id, List<Recipe>(), false));
			Node[order][0].data.push_back(disk);
		}
		else
		{
			for (int i = 0;i < Node[order].size();i++)
			{
				if (Node[order][i].key == id)
				{
					Node[order][i].data.push_back(disk);
					return;
				}
			}
			Node[order].push_back(HashData(id, List<Recipe>(), false));
			Node[order][Node[order].size() - 1].data.push_back(disk);
		}
	}
};
class RecipeHashListType:public RecipeHashList
{
public:
	void Insert(const Recipe& disk) override
	{
		int id = HashFunc(disk.GetTypeNum());
		int order = id%mapSize;
		if (Node[order].size() == 0)
		{
			Node[order].push_back(HashData(id, List<Recipe>(), false));
			Node[order][0].data.push_back(disk);
		}
		else
		{
			for (int i = 0;i < Node[order].size();i++)
			{
				if (Node[order][i].key == id)
				{
					Node[order][i].data.push_back(disk);
					return;
				}
			}
			Node[order].push_back(HashData(id, List<Recipe>(), false));
			Node[order][Node[order].size() - 1].data.push_back(disk);
		}
	}
};

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
	void AddUnit(Ingredient unit,int nums)
	{
		ListNode<Ingredient>* tmp = head;
		while (tmp != nullptr)
		{
			if (tmp->data.GetID() == unit.GetID())
			{
				tmp->data.num+=nums;
				break;
			}
			tmp = tmp->next;
		}
		if (tmp == nullptr)
		{
			push_back(unit);
			(*this)[length - 1].num=nums;
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
struct Disk
{
	string name;
	float HealValue;
	float duration;
	int level;
	EffectType type;
	std::string description;
};
void DisplayDisk(const Disk& disk);
Disk GetFinalDisk(const List<Ingredient>& foods, string name);
extern Bag bag;
extern RecipeHashListID IDRecipeMap;
extern RecipeHashListType TypeRecipeMap;
void InitAllUnits();
void InitAllRecipes();
extern BaseHashList<string, Ingredient> ingredientMap;