#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
static const std::unordered_map<EffectType, std::string>EffectBaseName = {
{ EffectType::Attack,        "攻击力提升" },
{ EffectType::Defence,       "防御提升" },
{ EffectType::Speed,         "移动力提升" },
{ EffectType::Health,        "完全生命回复" },
{ EffectType::Sneaky,        "安静性提升" },
{ EffectType::WarmDef,       "耐热防护" },
{ EffectType::ColdDef,       "耐寒防护" },
{ EffectType::ParalysisDef,  "电麻防护" },
{ EffectType::None,          "" }
};
enum class IngredientType { Fruit, Meat, Mushroom, Vegetable, Nut, Fish, Monster };
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
struct Effect
{
	EffectType effectType;
	float duration;
	int level;
	std::string name;
	std::string GetName();
};
class Ingredient
{
private:
	int ID;
	std::string name;
	int basicHealValue;
	int cookedHealValue;
	Effect effect;
	IngredientType type;
	std::string description;
public:
	Ingredient(int id, std::string name, int basicHV, Effect eft = { EffectType::None, 0.f, 0, "" }, std::string desc,IngredientType ty) :ID(id), name(name), basicHealValue(basicHV), cookedHealValue(2 * basicHV), description(desc),type(ty) {};
	std::string GetName()const;
	std::string GetDesc()const;
	EffectType GetCookedEffect();
	int GetHealValue();
	int GetID();
	bool operator == (const Ingredient& ohterIngredient);
};