#include "Ingredient.h"
#include "AllStruct.h"
using namespace std;
RecipeHashListID IDRecipeMap;
RecipeHashListType TypeRecipeMap;
BaseHashList<string, Ingredient> ingredientMap;
List<Ingredient> unitList;
Bag bag;
std::string Effect::GetName()
{
	{
		string name = *(EffectBaseName[effectType]);

		if (level > 0) {
			name += " Lv.";
			name += std::to_string(level);
		}

		/*if (duration > 0) {
			int totalSeconds = duration;
			int minutes = totalSeconds / 60;
			int seconds = totalSeconds % 60;

			name += " ";

			if (minutes > 0) {
				name += std::to_string(minutes);
				name += "分";
			}

			if (seconds > 0) {
				name += std::to_string(seconds);
				name += "秒";
			}
		}*/
		return name;
	}
}

std::string Ingredient::GetName() const
{
	return name;
}

std::string Ingredient::GetDesc() const
{
	return description;
}

EffectType Ingredient::GetCookedEffectType() const
{
	return effect.effectType;
}

int Ingredient::GetHealValue() const
{
	return basicHealValue;
}

int Ingredient::GetID() const
{
	return ID;
}

float Ingredient::GetDuration() const
{
	return duration;
}

float Ingredient::GetCookHealValue() const
{
	return cookedHealValue;
}

Effect Ingredient::GetEffect() const
{
	return effect;
}

bool Ingredient::operator==(const Ingredient& otherIngredient)
{
	return ID == otherIngredient.ID;
}

BaseHashList<EffectType, std::string> EffectNameInDisk{
	{EffectType::None, ""},
	{EffectType::ColdDef, "冰冷"},
	{EffectType::Attack, "力量"},
	{EffectType::Defence, "坚硬"},
	{EffectType::Speed, "速速"},
	{EffectType::Health, "生命"},
	{EffectType::Sneaky, "潜行"},
	{EffectType::WarmDef, "暖暖"},
	{EffectType::FireDef, "耐火"},
	{EffectType::ParalysisDef, "酥麻"}
};

void InitEffectBaseName()
{
	EffectBaseName.InsertByKey(EffectType::Attack, "攻击力提升");
	EffectBaseName.InsertByKey(EffectType::Defence, "防御提升");
	EffectBaseName.InsertByKey(EffectType::Speed, "移动力提升");
	EffectBaseName.InsertByKey(EffectType::Health, "完全生命回复");
	EffectBaseName.InsertByKey(EffectType::Sneaky, "安静性提升");
	EffectBaseName.InsertByKey(EffectType::WarmDef, "耐热防护");
	EffectBaseName.InsertByKey(EffectType::ColdDef, "耐寒防护");
	EffectBaseName.InsertByKey(EffectType::FireDef, "耐火防护");
	EffectBaseName.InsertByKey(EffectType::ParalysisDef, "电麻防护");
	EffectBaseName.InsertByKey(EffectType::None, "");
}
int FindMinID(ListNode<Ingredient>* f)
{
	if (f == nullptr)
		return 0;
	if (f->next == nullptr)
	{
		return f->data.GetID();
	}
	else
	{
		int minID = FindMinID(f->next);
		if (f->data.GetID() < minID)
			return f->data.GetID();
		else
			return minID;
	}
}
int FindMinID(ListNode<int>* f)
{
	if (f == nullptr)
		return 0;
	if (f->next == nullptr)
	{
		return f->data;
	}
	else
	{
		int minID = FindMinID(f->next);
		if (f->data < minID)
			return f->data;
		else
			return minID;
	}
}

BaseHashList<int, Ingredient> ingredientMapID;

void InitIngredientMap()
{
	for (int i = 0; i < unitList.size(); i++)
	{
		ingredientMap.InsertByKey(unitList[i].GetName(), unitList[i]);
		ingredientMapID.InsertByKey(unitList[i].GetID(), unitList[i]);
	}
}

int GetEffectLevel(int level, EffectType type)
{
	switch (type)
	{
	case EffectType::None:
		return 0;
		break;
	case EffectType::Attack:
		if (level < 5)
			return 1;
		else if (level >= 5 && level < 7)
			return 2;
		else
			return 3;
		break;
	case EffectType::Defence:
		if (level < 5)
			return 1;
		else if (level >= 5 && level < 7)
			return 2;
		else
			return 3;
		break;
	case EffectType::Speed:
		if (level < 5)
			return 1;
		else if (level >= 5 && level < 7)
			return 2;
		else
			return 3;
		break;
	case EffectType::Health:
		return 0;
		break;
	case EffectType::Sneaky:
		if (level < 6)
			return 1;
		else if (level >= 6 && level < 9)
			return 2;
		else
			return 3;
		break;
	case EffectType::WarmDef:
		if (level < 6)
			return 1;
		else
			return 2;
		break;
	case EffectType::ColdDef:
		if (level < 6)
			return 1;
		else
			return 2;
		break;
	case EffectType::FireDef:
		if (level < 7)
			return 1;
		else
			return 2;
		break;
	case EffectType::ParalysisDef:
		if (level < 4)
			return 1;
		else if (level >= 4 && level < 6)
			return 2;
		else
			return 3;
		break;
	default:
		break;
	}
}

Disk GetFinalDisk(const List<Ingredient>& foods, string name)
{
	Disk disk = Disk();
	int levelNums = 0;
	bool typeContract = false;

	for (int i = 0; i < foods.size(); i++)
	{
		disk.HealValue += foods[i].GetCookHealValue();
		disk.duration += foods[i].GetDuration();
		if (!typeContract)
		{
			if (disk.type == EffectType::None)
			{
				disk.type = foods[i].GetCookedEffectType();
			}
			else
			{
				if (disk.type != foods[i].GetCookedEffectType())
				{
					typeContract = true;
					disk.type == EffectType::None;
				}
			}
		}
		levelNums += foods[i].GetEffect().level;
	}
	string* firstName = EffectNameInDisk[disk.type];
	if (firstName != nullptr)
		disk.name = *firstName + name;
	else
	{
		disk.name = *firstName + name;
	}
	disk.level = GetEffectLevel(levelNums, disk.type);
	return disk;
}



void InitAllRecipes()
{
	// ==================== VEGETABLE RECIPES 蔬菜类菜谱 ====================
	// 炒野菜（蔬菜）
	Recipe FriedWildVegetables(
		"炒野菜",
		*(new List<int>{}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Vegetable }),
		*(new BaseHashList<int, int>{}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{
			{IngredientType::Vegetable, 0}
			})
	);
	IDRecipeMap.Insert(FriedWildVegetables);
	TypeRecipeMap.Insert(FriedWildVegetables);
	// 甘露炖蔬菜（蔬菜 + 精力蜂的蜂蜜）
	Recipe SweetStewedVegetables(
		"甘露炖蔬菜",
		*(new List<int>{ ingredientMap["精力蜂的蜂蜜"]->GetID() }),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Vegetable }),
		*(new BaseHashList<int, int>{ std::make_pair(ingredientMap["精力蜂的蜂蜜"]->GetID(), 0) }),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{ {{IngredientType::Vegetable, 0}} })
	);
	IDRecipeMap.Insert(SweetStewedVegetables);


	// 野菜饭团（蔬菜 + 海拉鲁米）
	Recipe VegetableRiceBalls(
		"野菜饭团",
		*(new List<int>{ ingredientMap["海拉鲁米"]->GetID() }),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Vegetable }),
		*(new BaseHashList<int, int>{ std::make_pair(ingredientMap["海拉鲁米"]->GetID(), 0) }),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{ {{IngredientType::Vegetable, 0}} })
	);
	IDRecipeMap.Insert(VegetableRiceBalls);

	// 蔬菜煎蛋卷（蔬菜 + 禽蛋 + 山羊黄油 + 岩盐）
	Recipe VegetableOmelette(
		"蔬菜煎蛋卷",
		*(new List<int>{
			ingredientMap["禽蛋"]->GetID(),
			ingredientMap["山羊黄油"]->GetID(),
			ingredientMap["岩盐"]->GetID()
			}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Vegetable }),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["禽蛋"]->GetID(), 0),
			std::make_pair(ingredientMap["山羊黄油"]->GetID(), 0),
			std::make_pair(ingredientMap["岩盐"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{ {{IngredientType::Vegetable, 0}} })
	);
	IDRecipeMap.Insert(VegetableOmelette);

	// 炒香菜（蔬菜 + 鼓隆的调味粉）
	Recipe FriedSpicyVegetables(
		"炒香菜",
		*(new List<int>{ ingredientMap["鼓隆的调味粉"]->GetID() }),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Vegetable }),
		*(new BaseHashList<int, int>{ std::make_pair(ingredientMap["鼓隆的调味粉"]->GetID(), 0) }),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{ {{IngredientType::Vegetable, 0}} })
	);
	IDRecipeMap.Insert(FriedSpicyVegetables);

	// 盐烤野菜（蔬菜 + 岩盐）
	Recipe SaltRoastedVegetables(
		"盐烤野菜",
		*(new List<int>{ ingredientMap["岩盐"]->GetID() }),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Vegetable }),
		*(new BaseHashList<int, int>{ std::make_pair(ingredientMap["岩盐"]->GetID(), 0) }),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{ {{IngredientType::Vegetable, 0}} })
	);
	IDRecipeMap.Insert(SaltRoastedVegetables);

	// 闷胡萝卜（萝卜 + 塔邦挞小麦 + 鲜奶 + 山羊黄油）
	Recipe StewedCarrots(
		"闷胡萝卜",
		*(new List<int>{
			ingredientMap["塔邦挞小麦"]->GetID(),
			ingredientMap["鲜奶"]->GetID(),
			ingredientMap["山羊黄油"]->GetID()
			}),
		*(new List<List<int>>{
			*(new List<int>{
				ingredientMap["生命小萝卜"]->GetID(),
				ingredientMap["生命大萝卜"]->GetID(),
				ingredientMap["毅力胡萝卜"]->GetID(),
				ingredientMap["速速胡萝卜"]->GetID()
			})
			}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["塔邦挞小麦"]->GetID(), 0),
			std::make_pair(ingredientMap["鲜奶"]->GetID(), 0),
			std::make_pair(ingredientMap["山羊黄油"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{
			*(new BaseHashList<int, int>{
				std::make_pair(ingredientMap["生命小萝卜"]->GetID(), 0),
				std::make_pair(ingredientMap["生命大萝卜"]->GetID(), 0),
				std::make_pair(ingredientMap["毅力胡萝卜"]->GetID(), 0),
				std::make_pair(ingredientMap["速速胡萝卜"]->GetID(), 0)
			})
			}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(StewedCarrots);

	// 胡萝卜蛋糕（萝卜 + 塔邦挞小麦 + 蔗糖 + 山羊黄油）
	Recipe CarrotCake(
		"胡萝卜蛋糕",
		*(new List<int>{
			ingredientMap["塔邦挞小麦"]->GetID(),
			ingredientMap["蔗糖"]->GetID(),
			ingredientMap["山羊黄油"]->GetID()
			}),
		*(new List<List<int>>{
			*(new List<int>{
				ingredientMap["生命小萝卜"]->GetID(),
				ingredientMap["生命大萝卜"]->GetID(),
				ingredientMap["毅力胡萝卜"]->GetID(),
				ingredientMap["速速胡萝卜"]->GetID()
			})
			}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["塔邦挞小麦"]->GetID(), 0),
			std::make_pair(ingredientMap["蔗糖"]->GetID(), 0),
			std::make_pair(ingredientMap["山羊黄油"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{
			*(new BaseHashList<int, int>{
				std::make_pair(ingredientMap["生命小萝卜"]->GetID(), 0),
				std::make_pair(ingredientMap["生命大萝卜"]->GetID(), 0),
				std::make_pair(ingredientMap["毅力胡萝卜"]->GetID(), 0),
				std::make_pair(ingredientMap["速速胡萝卜"]->GetID(), 0)
			})
			}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(CarrotCake);

	// 心心牛奶汤（生命大萝卜/生命小萝卜 + 冰冷蜜瓜 + 酥麻水果 + 鲜奶）
	Recipe HeartyMilkSoup(
		"心心牛奶汤",
		*(new List<int>{
			ingredientMap["冰冷蜜瓜"]->GetID(),
			ingredientMap["酥麻水果"]->GetID(),
			ingredientMap["鲜奶"]->GetID()
			}),
		*(new List<List<int>>{
			*(new List<int>{
				ingredientMap["生命大萝卜"]->GetID(),
				ingredientMap["生命小萝卜"]->GetID()
			})
			}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["冰冷蜜瓜"]->GetID(), 0),
			std::make_pair(ingredientMap["酥麻水果"]->GetID(), 0),
			std::make_pair(ingredientMap["鲜奶"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{
			*(new BaseHashList<int, int>{
				std::make_pair(ingredientMap["生命大萝卜"]->GetID(), 0),
				std::make_pair(ingredientMap["生命小萝卜"]->GetID(), 0)
			})
			}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(HeartyMilkSoup);

	// 蔬菜浓汤（毅力胡萝卜/速速胡萝卜/铠甲南瓜 + 鲜奶 + 岩盐）
	Recipe ThickVegetableSoup(
		"蔬菜浓汤",
		*(new List<int>{
			ingredientMap["鲜奶"]->GetID(),
			ingredientMap["岩盐"]->GetID()
			}),
		*(new List<List<int>>{
			*(new List<int>{
				ingredientMap["毅力胡萝卜"]->GetID(),
				ingredientMap["速速胡萝卜"]->GetID(),
				ingredientMap["铠甲南瓜"]->GetID()
			})
			}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["鲜奶"]->GetID(), 0),
			std::make_pair(ingredientMap["岩盐"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{
			*(new BaseHashList<int, int>{
				std::make_pair(ingredientMap["毅力胡萝卜"]->GetID(), 0),
				std::make_pair(ingredientMap["速速胡萝卜"]->GetID(), 0),
				std::make_pair(ingredientMap["铠甲南瓜"]->GetID(), 0)
			})
			}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(ThickVegetableSoup);

	// 蔬菜牛奶汤（除毅力胡萝卜/速速胡萝卜/铠甲南瓜外的蔬菜 + 鲜奶 + 岩盐）
	Recipe VegetableMilkSoup(
		"蔬菜牛奶汤",
		*(new List<int>{
			ingredientMap["鲜奶"]->GetID(),
			ingredientMap["岩盐"]->GetID()
			}),
		*(new List<List<int>>{
			*(new List<int>{
				ingredientMap["海拉鲁米"]->GetID(),
				ingredientMap["塔邦挞小麦"]->GetID()
				// 添加其他蔬菜类食材
			})
			}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["鲜奶"]->GetID(), 0),
			std::make_pair(ingredientMap["岩盐"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{
			*(new BaseHashList<int, int>{
				std::make_pair(ingredientMap["海拉鲁米"]->GetID(), 0),
				std::make_pair(ingredientMap["塔邦挞小麦"]->GetID(), 0)
			})
			}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(VegetableMilkSoup);

	// 蔬菜烩饭（毅力胡萝卜/速速胡萝卜/铠甲南瓜 + 海拉鲁米 + 山羊黄油 + 岩盐）
	Recipe VegetableRisotto(
		"蔬菜烩饭",
		*(new List<int>{
			ingredientMap["海拉鲁米"]->GetID(),
			ingredientMap["山羊黄油"]->GetID(),
			ingredientMap["岩盐"]->GetID()
			}),
		*(new List<List<int>>{
			*(new List<int>{
				ingredientMap["毅力胡萝卜"]->GetID(),
				ingredientMap["速速胡萝卜"]->GetID(),
				ingredientMap["铠甲南瓜"]->GetID()
			})
			}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["海拉鲁米"]->GetID(), 0),
			std::make_pair(ingredientMap["山羊黄油"]->GetID(), 0),
			std::make_pair(ingredientMap["岩盐"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{
			*(new BaseHashList<int, int>{
				std::make_pair(ingredientMap["毅力胡萝卜"]->GetID(), 0),
				std::make_pair(ingredientMap["速速胡萝卜"]->GetID(), 0),
				std::make_pair(ingredientMap["铠甲南瓜"]->GetID(), 0)
			})
			}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(VegetableRisotto);

	// 蔬菜咖喱饭（毅力胡萝卜/速速胡萝卜/铠甲南瓜 + 海拉鲁米 + 鼓隆的调味粉）
	Recipe VegetableCurry(
		"蔬菜咖喱饭",
		*(new List<int>{
			ingredientMap["海拉鲁米"]->GetID(),
			ingredientMap["鼓隆的调味粉"]->GetID()
			}),
		*(new List<List<int>>{
			*(new List<int>{
				ingredientMap["毅力胡萝卜"]->GetID(),
				ingredientMap["速速胡萝卜"]->GetID(),
				ingredientMap["铠甲南瓜"]->GetID()
			})
			}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["海拉鲁米"]->GetID(), 0),
			std::make_pair(ingredientMap["鼓隆的调味粉"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{
			*(new BaseHashList<int, int>{
				std::make_pair(ingredientMap["毅力胡萝卜"]->GetID(), 0),
				std::make_pair(ingredientMap["速速胡萝卜"]->GetID(), 0),
				std::make_pair(ingredientMap["铠甲南瓜"]->GetID(), 0)
			})
			}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(VegetableCurry);

	// 闷南瓜（铠甲南瓜 + 塔邦挞小麦 + 鲜奶 + 山羊黄油）
	Recipe StewedPumpkin(
		"闷南瓜",
		*(new List<int>{
			ingredientMap["铠甲南瓜"]->GetID(),
			ingredientMap["塔邦挞小麦"]->GetID(),
			ingredientMap["鲜奶"]->GetID(),
			ingredientMap["山羊黄油"]->GetID()
			}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["铠甲南瓜"]->GetID(), 0),
			std::make_pair(ingredientMap["塔邦挞小麦"]->GetID(), 0),
			std::make_pair(ingredientMap["鲜奶"]->GetID(), 0),
			std::make_pair(ingredientMap["山羊黄油"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(StewedPumpkin);

	// 南瓜蛋糕（铠甲南瓜 + 塔邦挞小麦 + 蔗糖 + 山羊黄油）
	Recipe PumpkinCake(
		"南瓜蛋糕",
		*(new List<int>{
			ingredientMap["铠甲南瓜"]->GetID(),
			ingredientMap["塔邦挞小麦"]->GetID(),
			ingredientMap["蔗糖"]->GetID(),
			ingredientMap["山羊黄油"]->GetID()
			}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["铠甲南瓜"]->GetID(), 0),
			std::make_pair(ingredientMap["塔邦挞小麦"]->GetID(), 0),
			std::make_pair(ingredientMap["蔗糖"]->GetID(), 0),
			std::make_pair(ingredientMap["山羊黄油"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(PumpkinCake);
	// ==================== FRUIT RECIPES 水果类菜谱 ====================

// 炖水果（任意水果）
	Recipe StewedFruit(
		"炖水果",
		*(new List<int>{}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Fruit }),
		*(new BaseHashList<int, int>{}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{ std::make_pair(IngredientType::Fruit, 0) })
	);
	IDRecipeMap.Insert(StewedFruit);

	// 蒸水果（水果 + 蔬菜）
	Recipe SteamedFruit(
		"蒸水果",
		*(new List<int>{}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{
			IngredientType::Fruit,
			IngredientType::Vegetable
			}),
		*(new BaseHashList<int, int>{}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{
			std::make_pair(IngredientType::Fruit, 0),
			std::make_pair(IngredientType::Vegetable, 0)
			})
	);
	IDRecipeMap.Insert(SteamedFruit);

	// 水果蛋糕（水果 + 苹果/草莓 + 塔邦挞小麦 + 蔗糖）
	Recipe FruitCake(
		"水果蛋糕",
		*(new List<int>{
			ingredientMap["塔邦挞小麦"]->GetID(),
			ingredientMap["蔗糖"]->GetID()
			}),
		*(new List<List<int>>{
			*(new List<int>{
				ingredientMap["苹果"]->GetID(),
				ingredientMap["草莓"]->GetID()
			})
			}),
		*(new List<IngredientType>{ IngredientType::Fruit }),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["塔邦挞小麦"]->GetID(), 0),
			std::make_pair(ingredientMap["蔗糖"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{
			*(new BaseHashList<int, int>{
				std::make_pair(ingredientMap["苹果"]->GetID(), 0),
				std::make_pair(ingredientMap["草莓"]->GetID(), 0)
			})
			}),
		*(new BaseHashList<IngredientType, int>{ std::make_pair(IngredientType::Fruit, 0) })
	);
	IDRecipeMap.Insert(FruitCake);

	// 水果派（水果 + 塔邦挞小麦 + 山羊黄油 + 蔗糖）
	Recipe FruitPie(
		"水果派",
		*(new List<int>{
			ingredientMap["塔邦挞小麦"]->GetID(),
			ingredientMap["山羊黄油"]->GetID(),
			ingredientMap["蔗糖"]->GetID()
			}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Fruit }),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["塔邦挞小麦"]->GetID(), 0),
			std::make_pair(ingredientMap["山羊黄油"]->GetID(), 0),
			std::make_pair(ingredientMap["蔗糖"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{ std::make_pair(IngredientType::Fruit, 0) })
	);
	IDRecipeMap.Insert(FruitPie);

	// 蜂蜜苹果（苹果 + 精力蜂的蜂蜜）
	Recipe HoneyApple(
		"蜂蜜苹果",
		*(new List<int>{
			ingredientMap["苹果"]->GetID(),
			ingredientMap["精力蜂的蜂蜜"]->GetID()
			}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["苹果"]->GetID(), 0),
			std::make_pair(ingredientMap["精力蜂的蜂蜜"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(HoneyApple);

	// 苹果派（苹果 + 塔邦挞小麦 + 山羊黄油 + 蔗糖）
	Recipe ApplePie(
		"苹果派",
		*(new List<int>{
			ingredientMap["苹果"]->GetID(),
			ingredientMap["塔邦挞小麦"]->GetID(),
			ingredientMap["山羊黄油"]->GetID(),
			ingredientMap["蔗糖"]->GetID()
			}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["苹果"]->GetID(), 0),
			std::make_pair(ingredientMap["塔邦挞小麦"]->GetID(), 0),
			std::make_pair(ingredientMap["山羊黄油"]->GetID(), 0),
			std::make_pair(ingredientMap["蔗糖"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(ApplePie);

	// 黄油苹果（苹果 + 山羊黄油）
	Recipe ButteredApple(
		"黄油苹果",
		*(new List<int>{
			ingredientMap["苹果"]->GetID(),
			ingredientMap["山羊黄油"]->GetID()
			}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["苹果"]->GetID(), 0),
			std::make_pair(ingredientMap["山羊黄油"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(ButteredApple);

	// 蜂蜜水果（苹果外的水果 + 精力蜂的蜂蜜）
	Recipe HoneyFruit(
		"蜂蜜水果",
		*(new List<int>{ ingredientMap["精力蜂的蜂蜜"]->GetID() }),
		*(new List<List<int>>{
			*(new List<int>{
				ingredientMap["椰子"]->GetID(),
				ingredientMap["草莓"]->GetID(),
				ingredientMap["冰冷蜜瓜"]->GetID(),
				ingredientMap["暖暖草果"]->GetID(),
				ingredientMap["酥麻水果"]->GetID(),
				ingredientMap["大剑香蕉"]->GetID(),
			})
			}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["精力蜂的蜂蜜"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{
			*(new BaseHashList<int, int>{
				std::make_pair(ingredientMap["椰子"]->GetID(), 0),
				std::make_pair(ingredientMap["草莓"]->GetID(), 0),
				std::make_pair(ingredientMap["冰冷蜜瓜"]->GetID(), 0),
				std::make_pair(ingredientMap["暖暖草果"]->GetID(), 0),
				std::make_pair(ingredientMap["酥麻水果"]->GetID(), 0),
				std::make_pair(ingredientMap["大剑香蕉"]->GetID(), 0),
			})
			}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(HoneyFruit);

	// 草莓可丽饼（草莓 + 塔邦挞小麦 + 禽蛋 + 鲜奶 + 蔗糖）
	Recipe StrawberryCrepe(
		"草莓可丽饼",
		*(new List<int>{
			ingredientMap["草莓"]->GetID(),
			ingredientMap["塔邦挞小麦"]->GetID(),
			ingredientMap["禽蛋"]->GetID(),
			ingredientMap["鲜奶"]->GetID(),
			ingredientMap["蔗糖"]->GetID()
			}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["草莓"]->GetID(), 0),
			std::make_pair(ingredientMap["塔邦挞小麦"]->GetID(), 0),
			std::make_pair(ingredientMap["禽蛋"]->GetID(), 0),
			std::make_pair(ingredientMap["鲜奶"]->GetID(), 0),
			std::make_pair(ingredientMap["蔗糖"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(StrawberryCrepe);

	// 炒暖暖草果（暖暖草果）
	Recipe FriedWarmSedge(
		"炒暖暖草果",
		*(new List<int>{ ingredientMap["暖暖草果"]->GetID() }),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["暖暖草果"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(FriedWarmSedge);

	// 炸香蕉（大剑香蕉 + 塔邦挞小麦 + 蔗糖）
	Recipe FriedBanana(
		"炸香蕉",
		*(new List<int>{
			ingredientMap["大剑香蕉"]->GetID(),
			ingredientMap["塔邦挞小麦"]->GetID(),
			ingredientMap["蔗糖"]->GetID()
			}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["大剑香蕉"]->GetID(), 0),
			std::make_pair(ingredientMap["塔邦挞小麦"]->GetID(), 0),
			std::make_pair(ingredientMap["蔗糖"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(FriedBanana);
	// ==================== SEAFOOD RECIPES 海鲜类菜谱 ====================

	// 烤鱼（任意鱼类）
	Recipe GrilledFish(
		"烤鱼",
		*(new List<int>{}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Fish }),
		*(new BaseHashList<int, int>{}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{ std::make_pair(IngredientType::Fish, 0) })
	);
	IDRecipeMap.Insert(GrilledFish);

	// 香辣煎鱼（鱼类 + 暖暖草果）
	Recipe SpicyFriedFish(
		"香辣煎鱼",
		*(new List<int>{ ingredientMap["暖暖草果"]->GetID() }),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Fish }),
		*(new BaseHashList<int, int>{ std::make_pair(ingredientMap["暖暖草果"]->GetID(), 0) }),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{ std::make_pair(IngredientType::Fish, 0) })
	);
	IDRecipeMap.Insert(SpicyFriedFish);

	// 烤鱼蘑菇串（鱼类 + 菌类）
	Recipe FishMushroomSkewers(
		"烤鱼蘑菇串",
		*(new List<int>{}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{
			IngredientType::Fish,
			IngredientType::Mushroom
			}),
		*(new BaseHashList<int, int>{}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{
			std::make_pair(IngredientType::Fish, 0),
			std::make_pair(IngredientType::Mushroom, 0)
			})
	);
	IDRecipeMap.Insert(FishMushroomSkewers);

	// 蒸鱼（鱼类 + 蔬菜）
	Recipe SteamedFish(
		"蒸鱼",
		*(new List<int>{}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{
			IngredientType::Fish,
			IngredientType::Vegetable
			}),
		*(new BaseHashList<int, int>{}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{
			std::make_pair(IngredientType::Fish, 0),
			std::make_pair(IngredientType::Vegetable, 0)
			})
	);
	IDRecipeMap.Insert(SteamedFish);

	// 海鲜牛奶汤（鱼类 + 蔬菜 + 鲜奶 + 岩盐）
	Recipe SeafoodMilkSoup(
		"海鲜牛奶汤",
		*(new List<int>{
			ingredientMap["鲜奶"]->GetID(),
			ingredientMap["岩盐"]->GetID()
			}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{
			IngredientType::Fish,
			IngredientType::Vegetable
			}),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["鲜奶"]->GetID(), 0),
			std::make_pair(ingredientMap["岩盐"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{
			std::make_pair(IngredientType::Fish, 0),
			std::make_pair(IngredientType::Vegetable, 0)
			})
	);
	IDRecipeMap.Insert(SeafoodMilkSoup);

	// 甘露炖鱼（鱼类 + 精力蜂的蜂蜜）
	Recipe SweetStewedFish(
		"甘露炖鱼",
		*(new List<int>{ ingredientMap["精力蜂的蜂蜜"]->GetID() }),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Fish }),
		*(new BaseHashList<int, int>{ std::make_pair(ingredientMap["精力蜂的蜂蜜"]->GetID(), 0) }),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{ std::make_pair(IngredientType::Fish, 0) })
	);
	IDRecipeMap.Insert(SweetStewedFish);

	// 海鲜饭团（鱼类 + 海拉鲁米）
	Recipe SeafoodRiceBalls(
		"海鲜饭团",
		*(new List<int>{ ingredientMap["海拉鲁米"]->GetID() }),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Fish }),
		*(new BaseHashList<int, int>{ std::make_pair(ingredientMap["海拉鲁米"]->GetID(), 0) }),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{ std::make_pair(IngredientType::Fish, 0) })
	);
	IDRecipeMap.Insert(SeafoodRiceBalls);

	// 干煎鱼（鱼类 + 塔邦挞小麦 + 山羊黄油）
	Recipe PanFriedFish(
		"干煎鱼",
		*(new List<int>{
			ingredientMap["塔邦挞小麦"]->GetID(),
			ingredientMap["山羊黄油"]->GetID()
			}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Fish }),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["塔邦挞小麦"]->GetID(), 0),
			std::make_pair(ingredientMap["山羊黄油"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{ std::make_pair(IngredientType::Fish, 0) })
	);
	IDRecipeMap.Insert(PanFriedFish);

	// 鱼肉派（鱼类 + 塔邦挞小麦 + 山羊黄油 + 岩盐）
	Recipe FishPie(
		"鱼肉派",
		*(new List<int>{
			ingredientMap["塔邦挞小麦"]->GetID(),
			ingredientMap["山羊黄油"]->GetID(),
			ingredientMap["岩盐"]->GetID()
			}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Fish }),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["塔邦挞小麦"]->GetID(), 0),
			std::make_pair(ingredientMap["山羊黄油"]->GetID(), 0),
			std::make_pair(ingredientMap["岩盐"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{ std::make_pair(IngredientType::Fish, 0) })
	);
	IDRecipeMap.Insert(FishPie);

	// 盐烤鱼（鱼类 + 岩盐）
	Recipe SaltGrilledFish(
		"盐烤鱼",
		*(new List<int>{ ingredientMap["岩盐"]->GetID() }),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Fish }),
		*(new BaseHashList<int, int>{ std::make_pair(ingredientMap["岩盐"]->GetID(), 0) }),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{ std::make_pair(IngredientType::Fish, 0) })
	);
	IDRecipeMap.Insert(SaltGrilledFish);

	// 三文鱼烩饭（生命鲈鱼 + 海拉鲁米 + 山羊黄油 + 岩盐）
	Recipe SalmonRisotto(
		"三文鱼烩饭",
		*(new List<int>{
			ingredientMap["海拉鲁米"]->GetID(),
			ingredientMap["山羊黄油"]->GetID(),
			ingredientMap["岩盐"]->GetID(),
			ingredientMap["生命三文鱼"]->GetID()
			}),
		*(new List<List<int>>{
			}),
			*(new List<IngredientType>{}),
			*(new BaseHashList<int, int>{
				std::make_pair(ingredientMap["海拉鲁米"]->GetID(), 0),
				std::make_pair(ingredientMap["山羊黄油"]->GetID(), 0),
				std::make_pair(ingredientMap["岩盐"]->GetID(), 0),
				std::make_pair(ingredientMap["生命三文鱼"]->GetID(), 0)
				}),
		*(new List<BaseHashList<int, int>>{
			}),
			*(new BaseHashList<IngredientType, int>{})
			);
	IDRecipeMap.Insert(SalmonRisotto);

	// 生命干煎三文鱼（生命鲈鱼 + 塔邦挞小麦 + 山羊黄油）
	Recipe PanFriedSalmon(
		"生命干煎三文鱼",
		*(new List<int>{
			ingredientMap["塔邦挞小麦"]->GetID(),
			ingredientMap["山羊黄油"]->GetID(),
			ingredientMap["生命三文鱼"]->GetID()
			}),
		*(new List<List<int>>{
			}),
			*(new List<IngredientType>{}),
			*(new BaseHashList<int, int>{
				std::make_pair(ingredientMap["塔邦挞小麦"]->GetID(), 0),
				std::make_pair(ingredientMap["山羊黄油"]->GetID(), 0),
				std::make_pair(ingredientMap["生命三文鱼"]->GetID(), 0)
				}),
		*(new List<BaseHashList<int, int>>{
			}),
			*(new BaseHashList<IngredientType, int>{})
			);
	IDRecipeMap.Insert(PanFriedSalmon);

	// 贝肉杂烩（生命海螺 + 塔邦挞小麦 + 鲜奶 + 山羊黄油）
	Recipe ClamChowder(
		"贝肉杂烩",
		*(new List<int>{
			ingredientMap["塔邦挞小麦"]->GetID(),
			ingredientMap["鲜奶"]->GetID(),
			ingredientMap["山羊黄油"]->GetID(),
			ingredientMap["生命海螺"]->GetID()
			}),
		*(new List<List<int>>{
			}),
			*(new List<IngredientType>{}),
			*(new BaseHashList<int, int>{
				std::make_pair(ingredientMap["塔邦挞小麦"]->GetID(), 0),
				std::make_pair(ingredientMap["鲜奶"]->GetID(), 0),
				std::make_pair(ingredientMap["山羊黄油"]->GetID(), 0),
				std::make_pair(ingredientMap["生命海螺"]->GetID(), 0)
				}),
		*(new List<BaseHashList<int, int>>{
			}),
			*(new BaseHashList<IngredientType, int>{})
			);
	IDRecipeMap.Insert(ClamChowder);

	// 串烤海鲜（生命海螺/大剑鲈鱼/铠甲鲈鱼）
	Recipe SeafoodSkewers(
		"串烤海鲜",
		*(new List<int>{}),
		*(new List<List<int>>{
			*(new List<int>{
				ingredientMap["生命海螺"]->GetID(),
				ingredientMap["大剑鲈鱼"]->GetID(),
				ingredientMap["铠甲鲈鱼"]->GetID()
			})
			}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{}),
		*(new List<BaseHashList<int, int>>{
			*(new BaseHashList<int, int>{
				std::make_pair(ingredientMap["生命海螺"]->GetID(), 0),
				std::make_pair(ingredientMap["大剑鲈鱼"]->GetID(), 0),
				std::make_pair(ingredientMap["铠甲鲈鱼"]->GetID(), 0)
			})
			}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(SeafoodSkewers);

	// 海鲜杂烩饭（生命海螺/大剑鲈鱼/铠甲鲈鱼 + 海拉鲁米 + 山羊黄油 + 岩盐）
	Recipe SeafoodPaella(
		"海鲜杂烩饭",
		*(new List<int>{
			ingredientMap["海拉鲁米"]->GetID(),
			ingredientMap["山羊黄油"]->GetID(),
			ingredientMap["岩盐"]->GetID()
			}),
		*(new List<List<int>>{
			*(new List<int>{
				ingredientMap["生命海螺"]->GetID(),
				ingredientMap["大剑鲈鱼"]->GetID(),
				ingredientMap["铠甲鲈鱼"]->GetID()
			})
			}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["海拉鲁米"]->GetID(), 0),
			std::make_pair(ingredientMap["山羊黄油"]->GetID(), 0),
			std::make_pair(ingredientMap["岩盐"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{
			*(new BaseHashList<int, int>{
				std::make_pair(ingredientMap["生命海螺"]->GetID(), 0),
				std::make_pair(ingredientMap["大剑鲈鱼"]->GetID(), 0),
				std::make_pair(ingredientMap["铠甲鲈鱼"]->GetID(), 0)
			})
			}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(SeafoodPaella);

	// 海鲜咖喱饭（生命海螺/大剑鲈鱼/铠甲鲈鱼 + 海拉鲁米 + 鼓隆的调味粉）
	Recipe SeafoodCurry(
		"海鲜咖喱饭",
		*(new List<int>{
			ingredientMap["海拉鲁米"]->GetID(),
			ingredientMap["鼓隆的调味粉"]->GetID()
			}),
		*(new List<List<int>>{
			*(new List<int>{
				ingredientMap["生命海螺"]->GetID(),
				ingredientMap["大剑鲈鱼"]->GetID(),
				ingredientMap["铠甲鲈鱼"]->GetID()
			})
			}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["海拉鲁米"]->GetID(), 0),
			std::make_pair(ingredientMap["鼓隆的调味粉"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{
			*(new BaseHashList<int, int>{
				std::make_pair(ingredientMap["生命海螺"]->GetID(), 0),
				std::make_pair(ingredientMap["大剑鲈鱼"]->GetID(), 0),
				std::make_pair(ingredientMap["铠甲鲈鱼"]->GetID(), 0)
			})
			}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(SeafoodCurry);

	// 海鲜炒饭（生命海螺/大剑鲈鱼/铠甲鲈鱼 + 海拉鲁米 + 岩盐）
	Recipe SeafoodFriedRice(
		"海鲜炒饭",
		*(new List<int>{
			ingredientMap["海拉鲁米"]->GetID(),
			ingredientMap["岩盐"]->GetID()
			}),
		*(new List<List<int>>{
			*(new List<int>{
				ingredientMap["生命海螺"]->GetID(),
				ingredientMap["大剑鲈鱼"]->GetID(),
				ingredientMap["铠甲鲈鱼"]->GetID()
			})
			}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["海拉鲁米"]->GetID(), 0),
			std::make_pair(ingredientMap["岩盐"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{
			*(new BaseHashList<int, int>{
				std::make_pair(ingredientMap["生命海螺"]->GetID(), 0),
				std::make_pair(ingredientMap["大剑鲈鱼"]->GetID(), 0),
				std::make_pair(ingredientMap["铠甲鲈鱼"]->GetID(), 0)
			})
			}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(SeafoodFriedRice);

	// 干煎鲈鱼（大剑鲈鱼/铠甲鲈鱼 + 塔邦挞小麦 + 山羊黄油）
	Recipe PanFriedBream(
		"干煎鲈鱼",
		*(new List<int>{
			ingredientMap["塔邦挞小麦"]->GetID(),
			ingredientMap["山羊黄油"]->GetID()
			}),
		*(new List<List<int>>{
			*(new List<int>{
				ingredientMap["大剑鲈鱼"]->GetID(),
				ingredientMap["铠甲鲈鱼"]->GetID()
			})
			}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["塔邦挞小麦"]->GetID(), 0),
			std::make_pair(ingredientMap["山羊黄油"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{
			*(new BaseHashList<int, int>{
				std::make_pair(ingredientMap["大剑鲈鱼"]->GetID(), 0),
				std::make_pair(ingredientMap["铠甲鲈鱼"]->GetID(), 0)
			})
			}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(PanFriedBream);

	// 蟹肉蛋炒饭（蟹类 + 海拉鲁米 + 禽蛋 + 岩盐）
	Recipe CrabFriedRice(
		"蟹肉蛋炒饭",
		*(new List<int>{
			ingredientMap["海拉鲁米"]->GetID(),
			ingredientMap["禽蛋"]->GetID(),
			ingredientMap["岩盐"]->GetID()
			}),
		*(new List<List<int>>{
			*(new List<int>{
				ingredientMap["大剑螃蟹"]->GetID(),
				ingredientMap["铠甲螃蟹"]->GetID()
			})
			}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["海拉鲁米"]->GetID(), 0),
			std::make_pair(ingredientMap["禽蛋"]->GetID(), 0),
			std::make_pair(ingredientMap["岩盐"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{
			*(new BaseHashList<int, int>{
				std::make_pair(ingredientMap["大剑螃蟹"]->GetID(), 0),
				std::make_pair(ingredientMap["铠甲螃蟹"]->GetID(), 0)
			})
			}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(CrabFriedRice);

	// 蟹肉烩饭（蟹类 + 海拉鲁米 + 山羊黄油 + 岩盐）
	Recipe CrabRisotto(
		"蟹肉烩饭",
		*(new List<int>{
			ingredientMap["海拉鲁米"]->GetID(),
			ingredientMap["山羊黄油"]->GetID(),
			ingredientMap["岩盐"]->GetID()
			}),
		*(new List<List<int>>{
			*(new List<int>{
				ingredientMap["大剑螃蟹"]->GetID(),
				ingredientMap["铠甲螃蟹"]->GetID()
			})
			}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["海拉鲁米"]->GetID(), 0),
			std::make_pair(ingredientMap["山羊黄油"]->GetID(), 0),
			std::make_pair(ingredientMap["岩盐"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{
			*(new BaseHashList<int, int>{
				std::make_pair(ingredientMap["大剑螃蟹"]->GetID(), 0),
				std::make_pair(ingredientMap["铠甲螃蟹"]->GetID(), 0)
			})
			}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(CrabRisotto);

	// 炒螃蟹（蟹类 + 鼓隆的调味粉）
	Recipe FriedCrab(
		"炒螃蟹",
		*(new List<int>{ ingredientMap["鼓隆的调味粉"]->GetID() }),
		*(new List<List<int>>{
			*(new List<int>{
				ingredientMap["大剑螃蟹"]->GetID(),
				ingredientMap["铠甲螃蟹"]->GetID()
			})
			}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{ std::make_pair(ingredientMap["鼓隆的调味粉"]->GetID(), 0) }),
		*(new List<BaseHashList<int, int>>{
			*(new BaseHashList<int, int>{
				std::make_pair(ingredientMap["大剑螃蟹"]->GetID(), 0),
				std::make_pair(ingredientMap["铠甲螃蟹"]->GetID(), 0)
			})
			}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(FriedCrab);

	// 岩盐烤蟹（蟹类 + 岩盐）
	Recipe SaltGrilledCrab(
		"岩盐烤蟹",
		*(new List<int>{ ingredientMap["岩盐"]->GetID() }),
		*(new List<List<int>>{
			*(new List<int>{
				ingredientMap["大剑螃蟹"]->GetID(),
				ingredientMap["铠甲螃蟹"]->GetID()
			})
			}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{ std::make_pair(ingredientMap["岩盐"]->GetID(), 0) }),
		*(new List<BaseHashList<int, int>>{
			*(new BaseHashList<int, int>{
				std::make_pair(ingredientMap["大剑螃蟹"]->GetID(), 0),
				std::make_pair(ingredientMap["铠甲螃蟹"]->GetID(), 0)
			})
			}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(SaltGrilledCrab);

	// 烤海鲜串（蟹类/螺类）
	Recipe SeafoodSkewers2(
		"烤海鲜串",
		*(new List<int>{}),
		*(new List<List<int>>{
			*(new List<int>{
				ingredientMap["大剑螃蟹"]->GetID(),
				ingredientMap["铠甲螃蟹"]->GetID(),
				ingredientMap["生命海螺"]->GetID()
			})
			}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{}),
		*(new List<BaseHashList<int, int>>{
			*(new BaseHashList<int, int>{
				std::make_pair(ingredientMap["大剑螃蟹"]->GetID(), 0),
				std::make_pair(ingredientMap["铠甲螃蟹"]->GetID(), 0),
				std::make_pair(ingredientMap["生命海螺"]->GetID(), 0)
			})
			}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(SeafoodSkewers2);

	// ==================== OTHER RECIPES 其他类菜谱 ====================

	// 煎蛋饭（海拉鲁米 + 禽蛋）
	Recipe FriedEggRice(
		"煎蛋饭",
		*(new List<int>{
			ingredientMap["海拉鲁米"]->GetID(),
			ingredientMap["禽蛋"]->GetID()
			}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["海拉鲁米"]->GetID(), 0),
			std::make_pair(ingredientMap["禽蛋"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(FriedEggRice);

	// 咖喱饭（海拉鲁米 + 鼓隆的调味粉）
	Recipe CurryRice(
		"咖喱饭",
		*(new List<int>{
			ingredientMap["海拉鲁米"]->GetID(),
			ingredientMap["鼓隆的调味粉"]->GetID()
			}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["海拉鲁米"]->GetID(), 0),
			std::make_pair(ingredientMap["鼓隆的调味粉"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(CurryRice);

	// 咖喱菜饭（海拉鲁米 + 鼓隆的调味粉 + 山羊黄油）
	Recipe CurryVegetableRice(
		"咖喱菜饭",
		*(new List<int>{
			ingredientMap["海拉鲁米"]->GetID(),
			ingredientMap["鼓隆的调味粉"]->GetID(),
			ingredientMap["山羊黄油"]->GetID()
			}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["海拉鲁米"]->GetID(), 0),
			std::make_pair(ingredientMap["鼓隆的调味粉"]->GetID(), 0),
			std::make_pair(ingredientMap["山羊黄油"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(CurryVegetableRice);

	// 原味可丽饼（塔邦挞小麦 + 禽蛋 + 鲜奶 + 蔗糖）
	Recipe PlainCrepe(
		"原味可丽饼",
		*(new List<int>{
			ingredientMap["塔邦挞小麦"]->GetID(),
			ingredientMap["禽蛋"]->GetID(),
			ingredientMap["鲜奶"]->GetID(),
			ingredientMap["蔗糖"]->GetID()
			}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["塔邦挞小麦"]->GetID(), 0),
			std::make_pair(ingredientMap["禽蛋"]->GetID(), 0),
			std::make_pair(ingredientMap["鲜奶"]->GetID(), 0),
			std::make_pair(ingredientMap["蔗糖"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(PlainCrepe);

	// 蜂蜜可丽饼（塔邦挞小麦 + 禽蛋 + 鲜奶 + 蔗糖 + 精力蜂的蜂蜜）
	Recipe HoneyCrepe(
		"蜂蜜可丽饼",
		*(new List<int>{
			ingredientMap["塔邦挞小麦"]->GetID(),
			ingredientMap["禽蛋"]->GetID(),
			ingredientMap["鲜奶"]->GetID(),
			ingredientMap["蔗糖"]->GetID(),
			ingredientMap["精力蜂的蜂蜜"]->GetID()
			}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["塔邦挞小麦"]->GetID(), 0),
			std::make_pair(ingredientMap["禽蛋"]->GetID(), 0),
			std::make_pair(ingredientMap["鲜奶"]->GetID(), 0),
			std::make_pair(ingredientMap["蔗糖"]->GetID(), 0),
			std::make_pair(ingredientMap["精力蜂的蜂蜜"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(HoneyCrepe);

	// 蛋挞（塔邦挞小麦 + 禽蛋 + 蔗糖 + 山羊黄油）
	Recipe EggTart(
		"蛋挞",
		*(new List<int>{
			ingredientMap["塔邦挞小麦"]->GetID(),
			ingredientMap["禽蛋"]->GetID(),
			ingredientMap["蔗糖"]->GetID(),
			ingredientMap["山羊黄油"]->GetID()
			}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["塔邦挞小麦"]->GetID(), 0),
			std::make_pair(ingredientMap["禽蛋"]->GetID(), 0),
			std::make_pair(ingredientMap["蔗糖"]->GetID(), 0),
			std::make_pair(ingredientMap["山羊黄油"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(EggTart);

	// 小麦面包（塔邦挞小麦 + 岩盐）
	Recipe WheatBread(
		"小麦面包",
		*(new List<int>{
			ingredientMap["塔邦挞小麦"]->GetID(),
			ingredientMap["岩盐"]->GetID()
			}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["塔邦挞小麦"]->GetID(), 0),
			std::make_pair(ingredientMap["岩盐"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(WheatBread);

	// 热牛奶（鲜奶）
	Recipe HotMilk(
		"热牛奶",
		*(new List<int>{ ingredientMap["鲜奶"]->GetID() }),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{ std::make_pair(ingredientMap["鲜奶"]->GetID(), 0) }),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(HotMilk);

	// 煎蛋卷（禽蛋）
	Recipe Omelette(
		"煎蛋卷",
		*(new List<int>{ ingredientMap["禽蛋"]->GetID() }),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{ std::make_pair(ingredientMap["禽蛋"]->GetID(), 0) }),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(Omelette);

	// 蜂蜜糖（精力蜂的蜂蜜）
	Recipe HoneyCandy(
		"蜂蜜糖",
		*(new List<int>{ ingredientMap["精力蜂的蜂蜜"]->GetID() }),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{ std::make_pair(ingredientMap["精力蜂的蜂蜜"]->GetID(), 0) }),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(HoneyCandy);

	// 鲜蛋布丁（禽蛋 + 鲜奶 + 蔗糖）
	Recipe EggPudding(
		"鲜蛋布丁",
		*(new List<int>{
			ingredientMap["禽蛋"]->GetID(),
			ingredientMap["鲜奶"]->GetID(),
			ingredientMap["蔗糖"]->GetID()
			}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["禽蛋"]->GetID(), 0),
			std::make_pair(ingredientMap["鲜奶"]->GetID(), 0),
			std::make_pair(ingredientMap["蔗糖"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(EggPudding);

	// 炒坚果（小鸟的树果/橡子）
	Recipe FriedNuts(
		"炒坚果",
		*(new List<int>{}),
		*(new List<List<int>>{
			*(new List<int>{
				ingredientMap["小鸟的树果"]->GetID(),
				ingredientMap["橡子"]->GetID()
			})
			}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{}),
		*(new List<BaseHashList<int, int>>{
			*(new BaseHashList<int, int>{
				std::make_pair(ingredientMap["小鸟的树果"]->GetID(), 0),
				std::make_pair(ingredientMap["橡子"]->GetID(), 0)
			})
			}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(FriedNuts);

	// 坚果蛋糕（塔邦挞小麦 + 蔗糖 + 山羊黄油 + 小鸟的树果/橡子）
	Recipe NutCake(
		"坚果蛋糕",
		*(new List<int>{
			ingredientMap["塔邦挞小麦"]->GetID(),
			ingredientMap["蔗糖"]->GetID(),
			ingredientMap["山羊黄油"]->GetID()
			}),
		*(new List<List<int>>{
			*(new List<int>{
				ingredientMap["小鸟的树果"]->GetID(),
				ingredientMap["橡子"]->GetID()
			})
			}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["塔邦挞小麦"]->GetID(), 0),
			std::make_pair(ingredientMap["蔗糖"]->GetID(), 0),
			std::make_pair(ingredientMap["山羊黄油"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{
			*(new BaseHashList<int, int>{
				std::make_pair(ingredientMap["小鸟的树果"]->GetID(), 0),
				std::make_pair(ingredientMap["橡子"]->GetID(), 0)
			})
			}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(NutCake);

	// 怪物蛋糕（怪物精华 + 塔邦挞小麦 + 蔗糖 + 山羊黄油）
	Recipe MonsterCake(
		"怪物蛋糕",
		*(new List<int>{
			ingredientMap["怪物精华"]->GetID(),
			ingredientMap["塔邦挞小麦"]->GetID(),
			ingredientMap["蔗糖"]->GetID(),
			ingredientMap["山羊黄油"]->GetID()
			}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["怪物精华"]->GetID(), 0),
			std::make_pair(ingredientMap["塔邦挞小麦"]->GetID(), 0),
			std::make_pair(ingredientMap["蔗糖"]->GetID(), 0),
			std::make_pair(ingredientMap["山羊黄油"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(MonsterCake);

	// 怪物饭团（怪物精华 + 海拉鲁米 + 岩盐）
	Recipe MonsterRiceBall(
		"怪物饭团",
		*(new List<int>{
			ingredientMap["怪物精华"]->GetID(),
			ingredientMap["海拉鲁米"]->GetID(),
			ingredientMap["岩盐"]->GetID()
			}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["怪物精华"]->GetID(), 0),
			std::make_pair(ingredientMap["海拉鲁米"]->GetID(), 0),
			std::make_pair(ingredientMap["岩盐"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(MonsterRiceBall);

	// 怪物汤（怪物精华 + 塔邦挞小麦 + 鲜奶 + 山羊黄油）
	Recipe MonsterSoup(
		"怪物汤",
		*(new List<int>{
			ingredientMap["怪物精华"]->GetID(),
			ingredientMap["塔邦挞小麦"]->GetID(),
			ingredientMap["鲜奶"]->GetID(),
			ingredientMap["山羊黄油"]->GetID()
			}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["怪物精华"]->GetID(), 0),
			std::make_pair(ingredientMap["塔邦挞小麦"]->GetID(), 0),
			std::make_pair(ingredientMap["鲜奶"]->GetID(), 0),
			std::make_pair(ingredientMap["山羊黄油"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{})
	);
	IDRecipeMap.Insert(MonsterSoup);

	// 怪物咖喱饭（怪物精华 + 海拉鲁米 + 鼓隆的调味粉）
	Recipe MonsterCurry(
		"怪物咖喱饭",
		*(new List<int>{
			ingredientMap["怪物精华"]->GetID(),
			ingredientMap["海拉鲁米"]->GetID(),
			ingredientMap["鼓隆的调味粉"]->GetID()
			}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{}),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["怪物精华"]->GetID(), 0),
			std::make_pair(ingredientMap["海拉鲁米"]->GetID(), 0),
			std::make_pair(ingredientMap["鼓隆的调味粉"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{})
	);
	// ===================肉类=================
	// 烤肉串（任意肉类）
	Recipe MeatSkewers(
		"烤肉串",
		*(new List<int>{}), // 不需要特定食材
		*(new List<List<int>>{}), // 没有可选食材组
		*(new List<IngredientType>{ IngredientType::Meat }), // 需要肉类
		*(new BaseHashList<int, int>{}), // 对应第一个参数的数量
		*(new List<BaseHashList<int, int>>{}), // 对应第二个参数的数量
		*(new BaseHashList<IngredientType, int>{ {IngredientType::Meat, 0} }) // 肉类数量至少1个（0表示至少1个）
	);
	IDRecipeMap.Insert(MeatSkewers);

	// 香辣煎肉（肉类+暖暖草果）
	Recipe SpicyFriedMeat(
		"香辣煎肉",
		*(new List<int>{ ingredientMap["暖暖草果"]->GetID() }), // 必须有暖暖草果
		*(new List<List<int>>{}), // 没有可选食材组
		*(new List<IngredientType>{ IngredientType::Meat }), // 需要肉类
		*(new BaseHashList<int, int>{ std::make_pair(ingredientMap["暖暖草果"]->GetID(), 0) }), // 暖暖草果至少1个
		*(new List<BaseHashList<int, int>>{}), // 对应第二个参数的数量
		*(new BaseHashList<IngredientType, int>{ {IngredientType::Meat, 0} }) // 肉类数量至少1个
	);
	IDRecipeMap.Insert(SpicyFriedMeat);
	// 烤肉蘑菇串（肉类+菌类）
	Recipe MeatMushroomSkewers(
		"烤肉蘑菇串",
		*(new List<int>{}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Meat, IngredientType::Mushroom }),
		*(new BaseHashList<int, int>{}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{
			{IngredientType::Meat, 0},
			{IngredientType::Mushroom, 0}
			})
	);
	IDRecipeMap.Insert(MeatMushroomSkewers);

	// 蒸肉（肉类+蔬菜）
	Recipe SteamedMeat(
		"蒸肉",
		*(new List<int>{}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Meat, IngredientType::Vegetable }),
		*(new BaseHashList<int, int>{}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{
			{IngredientType::Meat, 0},
			{IngredientType::Vegetable, 0}
			})
	);
	IDRecipeMap.Insert(SteamedMeat);

	// 鲜肉牛奶汤（肉类+蔬菜+鲜奶+岩盐）
	Recipe MeatMilkSoup(
		"鲜肉牛奶汤",
		*(new List<int>{
			ingredientMap["鲜奶"]->GetID(),
			ingredientMap["岩盐"]->GetID()
			}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Meat, IngredientType::Vegetable }),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["鲜奶"]->GetID(), 0),
			std::make_pair(ingredientMap["岩盐"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{
			{IngredientType::Meat, 0},
			{IngredientType::Vegetable, 0}
			})
	);
	IDRecipeMap.Insert(MeatMilkSoup);

	// 南瓜酿肉（肉类+铠甲南瓜）
	Recipe PumpkinStuffedMeat(
		"南瓜酿肉",
		*(new List<int>{ ingredientMap["铠甲南瓜"]->GetID() }),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Meat }),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["铠甲南瓜"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{
			{IngredientType::Meat, 0}
			})
	);
	IDRecipeMap.Insert(PumpkinStuffedMeat);

	// 海陆煎烧（肉类+鱼类）
	Recipe LandAndSeaPanFry(
		"海陆煎烧",
		*(new List<int>{}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Meat, IngredientType::Fish }),
		*(new BaseHashList<int, int>{}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{
			{IngredientType::Meat, 0},
			{IngredientType::Fish, 0}
			})
	);
	IDRecipeMap.Insert(LandAndSeaPanFry);

	// 甘露炖肉（肉类+精力蜂的蜂蜜）
	Recipe SweetStewedMeat(
		"甘露炖肉",
		*(new List<int>{ ingredientMap["精力蜂的蜂蜜"]->GetID() }),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Meat }),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["精力蜂的蜂蜜"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{
			{IngredientType::Meat, 0}
			})
	);
	IDRecipeMap.Insert(SweetStewedMeat);

	// 鲜肉饭团（肉类+海拉鲁米）
	Recipe MeatRiceBalls(
		"鲜肉饭团",
		*(new List<int>{ ingredientMap["海拉鲁米"]->GetID() }),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Meat }),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["海拉鲁米"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{
			{IngredientType::Meat, 0}
			})
	);
	IDRecipeMap.Insert(MeatRiceBalls);

	// 禽肉菜饭（禽肉+海拉鲁米+禽蛋+山羊黄油）
	Recipe PoultryVegetableRice(
		"禽肉菜饭",
		*(new List<int>{
			ingredientMap["海拉鲁米"]->GetID(),
			ingredientMap["禽蛋"]->GetID(),
			ingredientMap["山羊黄油"]->GetID()
			}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Meat }),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["海拉鲁米"]->GetID(), 0),
			std::make_pair(ingredientMap["禽蛋"]->GetID(), 0),
			std::make_pair(ingredientMap["山羊黄油"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{
			{IngredientType::Meat, 0}
			})
	);
	IDRecipeMap.Insert(PoultryVegetableRice);

	// 兽肉盖饭（兽肉+海拉鲁米+岩盐）
	Recipe BeastMeatRiceBowl(
		"兽肉盖饭",
		*(new List<int>{
			ingredientMap["海拉鲁米"]->GetID(),
			ingredientMap["岩盐"]->GetID()
			}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Meat }),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["海拉鲁米"]->GetID(), 0),
			std::make_pair(ingredientMap["岩盐"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{
			{IngredientType::Meat, 0}
			})
	);
	IDRecipeMap.Insert(BeastMeatRiceBowl);

	// 兽肉咖喱饭（兽肉+海拉鲁米+鼓隆的调味粉）
	Recipe BeastMeatCurry(
		"兽肉咖喱饭",
		*(new List<int>{
			ingredientMap["海拉鲁米"]->GetID(),
			ingredientMap["鼓隆的调味粉"]->GetID()
			}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Meat }),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["海拉鲁米"]->GetID(), 0),
			std::make_pair(ingredientMap["鼓隆的调味粉"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{
			{IngredientType::Meat, 0}
			})
	);
	IDRecipeMap.Insert(BeastMeatCurry);

	// 禽肉咖喱饭（禽肉+海拉鲁米+鼓隆的调味粉）
	Recipe PoultryCurry(
		"禽肉咖喱饭",
		*(new List<int>{
			ingredientMap["海拉鲁米"]->GetID(),
			ingredientMap["鼓隆的调味粉"]->GetID()
			}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Meat }),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["海拉鲁米"]->GetID(), 0),
			std::make_pair(ingredientMap["鼓隆的调味粉"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{
			{IngredientType::Meat, 0}
			})
	);
	IDRecipeMap.Insert(PoultryCurry);

	// 焖肉（肉类+塔邦挞小麦+鲜奶+山羊黄油）
	Recipe StewedMeat(
		"焖肉",
		*(new List<int>{
			ingredientMap["塔邦挞小麦"]->GetID(),
			ingredientMap["鲜奶"]->GetID(),
			ingredientMap["山羊黄油"]->GetID()
			}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Meat }),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["塔邦挞小麦"]->GetID(), 0),
			std::make_pair(ingredientMap["鲜奶"]->GetID(), 0),
			std::make_pair(ingredientMap["山羊黄油"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{
			{IngredientType::Meat, 0}
			})
	);
	IDRecipeMap.Insert(StewedMeat);

	// 鲜肉派（肉类+塔邦挞小麦+山羊黄油+岩盐）
	Recipe MeatPie(
		"鲜肉派",
		*(new List<int>{
			ingredientMap["塔邦挞小麦"]->GetID(),
			ingredientMap["山羊黄油"]->GetID(),
			ingredientMap["岩盐"]->GetID()
			}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Meat }),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["塔邦挞小麦"]->GetID(), 0),
			std::make_pair(ingredientMap["山羊黄油"]->GetID(), 0),
			std::make_pair(ingredientMap["岩盐"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{
			{IngredientType::Meat, 0}
			})
	);
	IDRecipeMap.Insert(MeatPie);

	// 烤兽肉串（兽肉类+鼓隆的调味粉）
	Recipe GrilledBeastMeatSkewers(
		"烤兽肉串",
		*(new List<int>{ ingredientMap["鼓隆的调味粉"]->GetID() }),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Meat }),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["鼓隆的调味粉"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{
			{IngredientType::Meat, 0}
			})
	);
	IDRecipeMap.Insert(GrilledBeastMeatSkewers);

	// 烤禽肉串（禽肉类+鼓隆的调味粉）
	Recipe GrilledPoultrySkewers(
		"烤禽肉串",
		*(new List<int>{ ingredientMap["鼓隆的调味粉"]->GetID() }),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Meat }),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["鼓隆的调味粉"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{
			{IngredientType::Meat, 0}
			})
	);
	IDRecipeMap.Insert(GrilledPoultrySkewers);

	// 岩盐烤肉（肉类+岩盐）
	Recipe SaltRoastedMeat(
		"岩盐烤肉",
		*(new List<int>{ ingredientMap["岩盐"]->GetID() }),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Meat }),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["岩盐"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{
			{IngredientType::Meat, 0}
			})
	);
	// 烤蘑菇串（任意菌类）
	Recipe GrilledMushroomSkewers(
		"烤蘑菇串",
		*(new List<int>{}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Mushroom }),
		*(new BaseHashList<int, int>{}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{
			{IngredientType::Mushroom, 0}
			})
	);
	IDRecipeMap.Insert(GrilledMushroomSkewers);

	// 水果拌蘑菇（菌类+水果）
	Recipe FruitMushroomSalad(
		"水果拌蘑菇",
		*(new List<int>{}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Mushroom, IngredientType::Fruit }),
		*(new BaseHashList<int, int>{}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{
			{IngredientType::Mushroom, 0},
			{IngredientType::Fruit, 0}
			})
	);
	IDRecipeMap.Insert(FruitMushroomSalad);

	// 蒸蘑菇（菌类+蔬菜）
	Recipe SteamedMushrooms(
		"蒸蘑菇",
		*(new List<int>{}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Mushroom, IngredientType::Vegetable }),
		*(new BaseHashList<int, int>{}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{
			{IngredientType::Mushroom, 0},
			{IngredientType::Vegetable, 0}
			})
	);
	IDRecipeMap.Insert(SteamedMushrooms);

	// 蘑菇牛奶汤（菌类+蔬菜+鲜奶+岩盐）
	Recipe MushroomMilkSoup(
		"蘑菇牛奶汤",
		*(new List<int>{
			ingredientMap["鲜奶"]->GetID(),
			ingredientMap["岩盐"]->GetID()
			}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Mushroom, IngredientType::Vegetable }),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["鲜奶"]->GetID(), 0),
			std::make_pair(ingredientMap["岩盐"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{
			{IngredientType::Mushroom, 0},
			{IngredientType::Vegetable, 0}
			})
	);
	IDRecipeMap.Insert(MushroomMilkSoup);

	// 甘露蘑菇（菌类+精力蜂的蜂蜜）
	Recipe SweetMushrooms(
		"甘露蘑菇",
		*(new List<int>{ ingredientMap["精力蜂的蜂蜜"]->GetID() }),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Mushroom }),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["精力蜂的蜂蜜"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{
			{IngredientType::Mushroom, 0}
			})
	);
	IDRecipeMap.Insert(SweetMushrooms);

	// 蘑菇饭团（菌类+海拉鲁米）
	Recipe MushroomRiceBalls(
		"蘑菇饭团",
		*(new List<int>{ ingredientMap["海拉鲁米"]->GetID() }),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Mushroom }),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["海拉鲁米"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{
			{IngredientType::Mushroom, 0}
			})
	);
	IDRecipeMap.Insert(MushroomRiceBalls);

	// 蘑菇烩饭（菌类+海拉鲁米+山羊黄油+岩盐）
	Recipe MushroomRisotto(
		"蘑菇烩饭",
		*(new List<int>{
			ingredientMap["海拉鲁米"]->GetID(),
			ingredientMap["山羊黄油"]->GetID(),
			ingredientMap["岩盐"]->GetID()
			}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Mushroom }),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["海拉鲁米"]->GetID(), 0),
			std::make_pair(ingredientMap["山羊黄油"]->GetID(), 0),
			std::make_pair(ingredientMap["岩盐"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{
			{IngredientType::Mushroom, 0}
			})
	);
	IDRecipeMap.Insert(MushroomRisotto);

	// 蘑菇煎蛋卷（菌类+禽蛋+山羊黄油+岩盐）
	Recipe MushroomOmelette(
		"蘑菇煎蛋卷",
		*(new List<int>{
			ingredientMap["禽蛋"]->GetID(),
			ingredientMap["山羊黄油"]->GetID(),
			ingredientMap["岩盐"]->GetID()
			}),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Mushroom }),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["禽蛋"]->GetID(), 0),
			std::make_pair(ingredientMap["山羊黄油"]->GetID(), 0),
			std::make_pair(ingredientMap["岩盐"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{
			{IngredientType::Mushroom, 0}
			})
	);
	IDRecipeMap.Insert(MushroomOmelette);

	// 炒香蘑菇（菌类+鼓隆的调味粉）
	Recipe FriedSpicyMushrooms(
		"炒香蘑菇",
		*(new List<int>{ ingredientMap["鼓隆的调味粉"]->GetID() }),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Mushroom }),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["鼓隆的调味粉"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{
			{IngredientType::Mushroom, 0}
			})
	);
	IDRecipeMap.Insert(FriedSpicyMushrooms);

	// 盐烤蘑菇（菌类+岩盐）
	Recipe SaltRoastedMushrooms(
		"盐烤蘑菇",
		*(new List<int>{ ingredientMap["岩盐"]->GetID() }),
		*(new List<List<int>>{}),
		*(new List<IngredientType>{ IngredientType::Mushroom }),
		*(new BaseHashList<int, int>{
			std::make_pair(ingredientMap["岩盐"]->GetID(), 0)
			}),
		*(new List<BaseHashList<int, int>>{}),
		*(new BaseHashList<IngredientType, int>{
			{IngredientType::Mushroom, 0}
			})
	);
	IDRecipeMap.Insert(SaltRoastedMushrooms);
	IDRecipeMap.Insert(SaltRoastedMeat);
	TypeRecipeMap.Insert(MonsterCurry);
	TypeRecipeMap.Insert(SweetStewedVegetables);
	TypeRecipeMap.Insert(VegetableRiceBalls);
	TypeRecipeMap.Insert(VegetableOmelette);
	TypeRecipeMap.Insert(FriedSpicyVegetables);
	TypeRecipeMap.Insert(SaltRoastedVegetables);
	TypeRecipeMap.Insert(StewedCarrots);
	TypeRecipeMap.Insert(CarrotCake);
	TypeRecipeMap.Insert(HeartyMilkSoup);
	TypeRecipeMap.Insert(ThickVegetableSoup);
	TypeRecipeMap.Insert(VegetableMilkSoup);
	TypeRecipeMap.Insert(VegetableRisotto);
	TypeRecipeMap.Insert(VegetableCurry);
	TypeRecipeMap.Insert(StewedPumpkin);
	TypeRecipeMap.Insert(PumpkinCake);
	TypeRecipeMap.Insert(StewedFruit);
	TypeRecipeMap.Insert(SteamedFruit);
	TypeRecipeMap.Insert(FruitCake);
	TypeRecipeMap.Insert(FruitPie);
	TypeRecipeMap.Insert(HoneyApple);
	TypeRecipeMap.Insert(ApplePie);
	TypeRecipeMap.Insert(ButteredApple);
	TypeRecipeMap.Insert(HoneyFruit);
	TypeRecipeMap.Insert(StrawberryCrepe);
	TypeRecipeMap.Insert(FriedWarmSedge);
	TypeRecipeMap.Insert(FriedBanana);
	TypeRecipeMap.Insert(GrilledFish);
	TypeRecipeMap.Insert(SpicyFriedFish);
	TypeRecipeMap.Insert(FishMushroomSkewers);
	TypeRecipeMap.Insert(SteamedFish);
	TypeRecipeMap.Insert(SeafoodMilkSoup);
	TypeRecipeMap.Insert(SweetStewedFish);
	TypeRecipeMap.Insert(SeafoodRiceBalls);
	TypeRecipeMap.Insert(PanFriedFish);
	TypeRecipeMap.Insert(FishPie);
	TypeRecipeMap.Insert(SaltGrilledFish);
	TypeRecipeMap.Insert(SalmonRisotto);
	TypeRecipeMap.Insert(PanFriedSalmon);
	TypeRecipeMap.Insert(ClamChowder);
	TypeRecipeMap.Insert(SeafoodSkewers);
	TypeRecipeMap.Insert(SeafoodPaella);
	TypeRecipeMap.Insert(SeafoodCurry);
	TypeRecipeMap.Insert(SeafoodFriedRice);
	TypeRecipeMap.Insert(PanFriedBream);
	TypeRecipeMap.Insert(CrabFriedRice);
	TypeRecipeMap.Insert(CrabRisotto);
	TypeRecipeMap.Insert(FriedCrab);
	TypeRecipeMap.Insert(SaltGrilledCrab);
	TypeRecipeMap.Insert(SeafoodSkewers2);
	TypeRecipeMap.Insert(FriedEggRice);
	TypeRecipeMap.Insert(CurryRice);
	TypeRecipeMap.Insert(CurryVegetableRice);
	TypeRecipeMap.Insert(PlainCrepe);
	TypeRecipeMap.Insert(HoneyCrepe);
	TypeRecipeMap.Insert(EggTart);
	TypeRecipeMap.Insert(WheatBread);
	TypeRecipeMap.Insert(HotMilk);
	TypeRecipeMap.Insert(Omelette);
	TypeRecipeMap.Insert(HoneyCandy);
	TypeRecipeMap.Insert(EggPudding);
	TypeRecipeMap.Insert(FriedNuts);
	TypeRecipeMap.Insert(NutCake);
	TypeRecipeMap.Insert(MonsterCake);
	TypeRecipeMap.Insert(MonsterRiceBall);
	TypeRecipeMap.Insert(MonsterSoup);
	TypeRecipeMap.Insert(MonsterCurry);
	TypeRecipeMap.Insert(MeatSkewers);
	TypeRecipeMap.Insert(SpicyFriedMeat);
	TypeRecipeMap.Insert(MeatMushroomSkewers);
	TypeRecipeMap.Insert(SteamedMeat);
	TypeRecipeMap.Insert(MeatMilkSoup);
	TypeRecipeMap.Insert(PumpkinStuffedMeat);
	TypeRecipeMap.Insert(LandAndSeaPanFry);
	TypeRecipeMap.Insert(SweetStewedMeat);
	TypeRecipeMap.Insert(MeatRiceBalls);
	TypeRecipeMap.Insert(PoultryVegetableRice);
	TypeRecipeMap.Insert(BeastMeatRiceBowl);
	TypeRecipeMap.Insert(BeastMeatCurry);
	TypeRecipeMap.Insert(PoultryCurry);
	TypeRecipeMap.Insert(StewedMeat);
	TypeRecipeMap.Insert(MeatPie);
	TypeRecipeMap.Insert(GrilledBeastMeatSkewers);
	TypeRecipeMap.Insert(GrilledPoultrySkewers);
	TypeRecipeMap.Insert(SaltRoastedMeat);
	TypeRecipeMap.Insert(GrilledMushroomSkewers);
	TypeRecipeMap.Insert(FruitMushroomSalad);
	TypeRecipeMap.Insert(SteamedMushrooms);
	TypeRecipeMap.Insert(MushroomMilkSoup);
	TypeRecipeMap.Insert(SweetMushrooms);
	TypeRecipeMap.Insert(MushroomRiceBalls);
	TypeRecipeMap.Insert(MushroomRisotto);
	TypeRecipeMap.Insert(MushroomOmelette);
	TypeRecipeMap.Insert(FriedSpicyMushrooms);
	TypeRecipeMap.Insert(SaltRoastedMushrooms);
}

ListNode<Disk>* Merge(ListNode<Disk>* a, ListNode<Disk>* b,
	std::function<bool(const Disk&, const Disk&)> comp)
{
	if (!a) return b;
	if (!b) return a;

	if (comp(a->data, b->data)) {
		a->next = Merge(a->next, b, comp);
		return a;
	}
	else {
		b->next = Merge(a, b->next, comp);
		return b;
	}
}

ListNode<Disk>* MergeSort(ListNode<Disk>* head, std::function<bool(const Disk&, const Disk&)> comp)
{
	if (!head || !head->next)
		return head;

	ListNode<Disk>* slow = head;
	ListNode<Disk>* fast = head->next;

	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
	}

	ListNode<Disk>* mid = slow->next;
	slow->next = nullptr;

	ListNode<Disk>* left = MergeSort(head, comp);
	ListNode<Disk>* right = MergeSort(mid, comp);

	return Merge(left, right, comp);
}
ListNode<Disk>* MergeSortByDishType(List<Disk>& dishes) 
{
	auto comp = [](const Disk& a, const Disk& b) {
		return static_cast<int>(a.type) <= static_cast<int>(b.type);};
	return MergeSort(dishes.GetHead(), comp);
}
ListNode<Disk>* MergeSortDishByBuffLevel(List<Disk>& dishes) {
	auto comp = [](const Disk& a, const Disk& b) {
		return a.level <= b.level;
		};
	return MergeSort(dishes.GetHead(), comp);
}
ListNode<Disk>* MergeSortByHeal(List<Disk>& dishes)
{
	auto comp = [](const Disk& a, const Disk& b) {
		return a.HealValue <= b.HealValue;
		};
	return MergeSort(dishes.GetHead(), comp);
}
ListNode<Disk>* MergeSortByTime(ListNode<Disk>* head) {
	auto comp = [](const Disk& a, const Disk& b) {
		return a.duration <= b.duration;
		};
	return MergeSort(head, comp);
}
std::string GetEffectTypeName(EffectType type)
{
	std::string* name = EffectBaseName[type];
	if (name != nullptr)
		return *name;
	return "UnknownEffect";
}

void DisplayDisk(const Disk& disk)
{
	cout << "名字:" << disk.name << endl;
	cout << "回血量:" << disk.HealValue << endl;
	cout << "效果类型:" << GetEffectTypeName(disk.type) << endl;
	cout << "效果等级:" << disk.level << endl;
	cout << "持续时间:" << disk.duration << endl;
}

void InitAllUnits()
{
	// ==================== FRUIT 水果类 ====================
	unitList.push_back(Ingredient("苹果", 1, 0.5, 0, IngredientType::Fruit, "海拉鲁最常见的果实，可以恢复少量体力"));
	unitList.push_back(Ingredient("椰子", 2, 0.5, 0, IngredientType::Fruit, "热带海岸的果实，坚硬外壳内有清甜汁液"));
	unitList.push_back(Ingredient("草莓", 3, 0.5, 0, IngredientType::Fruit, "小巧的红色果实，生长在草地和森林中"));
	unitList.push_back(Ingredient("冰冷蜜瓜", 4, 1, 30, IngredientType::Fruit, "格鲁德地区特产，能提供抗热效果", Effect(EffectType::WarmDef, 1)));
	unitList.push_back(Ingredient("暖暖草果", 5, 0.5, 30, IngredientType::Fruit, "散发温暖的红色果实，能抵御寒冷", Effect(EffectType::ColdDef, 1)));
	unitList.push_back(Ingredient("酥麻水果", 6, 1, 30, IngredientType::Fruit, "费罗尼地区的特殊水果，提供电击防护", Effect(EffectType::ParalysisDef, 1)));
	unitList.push_back(Ingredient("大剑香蕉", 7, 1, 30, IngredientType::Fruit, "依盖队最爱的水果，能提升攻击力", Effect(EffectType::Attack, 1)));
	unitList.push_back(Ingredient("生命福禄", 66, 3, 0, IngredientType::Fruit, "能增加体力上限的珍贵水果", Effect(EffectType::Health, 4)));
	unitList.push_back(Ingredient("速速莲蓬", 67, 0.5, 60, IngredientType::Fruit, "能大幅提升移动速度的水果", Effect(EffectType::Speed, 2)));

	// ==================== MEAT 肉类 ====================
	unitList.push_back(Ingredient("生肉", 12, 1.0, 0, IngredientType::Meat, "普通动物的肉，基础食材"));
	unitList.push_back(Ingredient("高级生肉", 13, 1.5, 0, IngredientType::Meat, "优质动物的肉，恢复更多体力"));
	unitList.push_back(Ingredient("顶级生肉", 14, 2, 0, IngredientType::Meat, "稀有动物的顶级肉质"));
	unitList.push_back(Ingredient("禽肉", 15, 1, 0, IngredientType::Meat, "鸟类的肉，比兽肉更轻"));
	unitList.push_back(Ingredient("高级禽肉", 16, 1.5, 0, IngredientType::Meat, "优质鸟类的肉"));
	unitList.push_back(Ingredient("顶级禽肉", 17, 2, 0, IngredientType::Meat, "稀有鸟类的顶级肉"));
	unitList.push_back(Ingredient("兽肉", 18, 1, 0, IngredientType::Meat, "野兽的肉，比禽肉更厚实"));
	unitList.push_back(Ingredient("高级兽肉", 19, 1.5, 0, IngredientType::Meat, "强壮野兽的优质肉"));
	unitList.push_back(Ingredient("顶级兽肉", 20, 2, 0, IngredientType::Meat, "最强野兽的顶级肉"));

	// ==================== MUSHROOM 蘑菇类 ====================
	unitList.push_back(Ingredient("海拉鲁蘑菇", 21, 1, 0, IngredientType::Mushroom, "海拉鲁最常见的蘑菇品种"));
	unitList.push_back(Ingredient("精力蘑菇", 22, 1, 0, IngredientType::Mushroom, "能恢复少量精力的蘑菇", Effect(EffectType::Health, 1)));
	unitList.push_back(Ingredient("铠甲蘑菇", 23, 0.5, 30, IngredientType::Mushroom, "能提升防御力的坚固蘑菇", Effect(EffectType::Defence, 1)));
	unitList.push_back(Ingredient("冰冷蘑菇", 24, 0.5, 30, IngredientType::Mushroom, "生长在寒冷地区的抗热蘑菇", Effect(EffectType::WarmDef, 1)));
	unitList.push_back(Ingredient("暖暖蘑菇", 25, 0.5, 30, IngredientType::Mushroom, "生长在温暖地区的抗寒蘑菇", Effect(EffectType::ColdDef, 1)));
	unitList.push_back(Ingredient("酥麻蘑菇", 26, 0.5, 30, IngredientType::Mushroom, "能在雷雨天找到的防电蘑菇", Effect(EffectType::ParalysisDef, 1)));
	unitList.push_back(Ingredient("潜行蘑菇", 27, 0.5, 60, IngredientType::Mushroom, "能让行动更安静的蘑菇", Effect(EffectType::Sneaky, 1)));
	unitList.push_back(Ingredient("大剑蘑菇", 28, 1, 30, IngredientType::Mushroom, "能提升攻击力的强力蘑菇", Effect(EffectType::Attack, 1)));
	unitList.push_back(Ingredient("速速蘑菇", 29, 0.5, 30, IngredientType::Mushroom, "能让移动更快的蘑菇", Effect(EffectType::Speed, 1)));
	unitList.push_back(Ingredient("毅力蘑菇", 30, 2, 0, IngredientType::Mushroom, "能提供额外黄心的稀有蘑菇", Effect(EffectType::Health, 4)));
	unitList.push_back(Ingredient("大个生命松露", 68, 3, 0, IngredientType::Mushroom, "巨大的松露，能大幅增加体力上限", Effect(EffectType::Health, 4)));
	unitList.push_back(Ingredient("生命松露", 69, 2, 0, IngredientType::Mushroom, "珍贵的松露，能增加体力上限", Effect(EffectType::Health, 1)));

	// ==================== VEGETABLE 蔬菜类 ====================
	unitList.push_back(Ingredient("铠甲南瓜", 31, 1, 30, IngredientType::Vegetable, "卡卡利科村特产，能提升防御力", Effect(EffectType::Defence, 1)));
	unitList.push_back(Ingredient("海拉鲁米", 90, 1, 0, IngredientType::Vegetable, "海拉鲁主要粮食作物"));
	unitList.push_back(Ingredient("塔邦挞小麦", 91, 1, 0, IngredientType::Vegetable, "塔邦挞地区种植的优质小麦"));
	unitList.push_back(Ingredient("生命小萝卜", 8, 4, 0, IngredientType::Vegetable, "能恢复大量体力的珍贵植物"));
	unitList.push_back(Ingredient("生命大萝卜", 9, 12, 0, IngredientType::Vegetable, "极其稀有的超级萝卜，能恢复巨量体力"));
	unitList.push_back(Ingredient("毅力胡萝卜", 10, 2, 0, IngredientType::Vegetable, "能提供额外黄心的神奇胡萝卜", Effect(EffectType::Health, 4)));
	unitList.push_back(Ingredient("速速胡萝卜", 11, 0.5, 30, IngredientType::Vegetable, "能让食用者移动更快的胡萝卜", Effect(EffectType::Speed, 1)));


	// ==================== GRASS 草类 ====================
	unitList.push_back(Ingredient("海拉鲁草", 72, 1, 0, IngredientType::Vegetable, "海拉鲁常见的草，基础草药"));
	unitList.push_back(Ingredient("冰冷香草", 73, 0, 150, IngredientType::Vegetable, "生长在寒冷地区的抗热香草", Effect(EffectType::WarmDef, 1)));
	unitList.push_back(Ingredient("暖暖香草", 74, 0, 150, IngredientType::Vegetable, "生长在温暖地区的抗寒香草", Effect(EffectType::ColdDef, 1)));
	unitList.push_back(Ingredient("酥麻香草", 75, 0, 150, IngredientType::Vegetable, "生长在雷雨地区的防电香草", Effect(EffectType::ParalysisDef, 1)));
	unitList.push_back(Ingredient("速递紫罗兰", 76, 0, 60, IngredientType::Vegetable, "能大幅提升移动速度的紫罗兰", Effect(EffectType::Speed, 2)));
	unitList.push_back(Ingredient("大剑草", 77, 0, 50, IngredientType::Vegetable, "能提升攻击力的草", Effect(EffectType::Attack, 1)));
	unitList.push_back(Ingredient("铠甲草", 78, 0, 50, IngredientType::Vegetable, "能提升防御力的草", Effect(EffectType::Defence, 1)));
	unitList.push_back(Ingredient("潜行草", 79, 0, 120, IngredientType::Vegetable, "能让行动更安静的草", Effect(EffectType::Sneaky, 1)));
	unitList.push_back(Ingredient("静谧公主", 80, 0, 120, IngredientType::Vegetable, "极其稀有的花朵，大幅提升潜行能力", Effect(EffectType::Sneaky, 3)));

	// ==================== NUT 坚果类 ====================
	unitList.push_back(Ingredient("橡子", 34, 0.25, 0, IngredientType::Nut, "击打树木获得的小坚果"));
	unitList.push_back(Ingredient("小鸟的树果", 35, 0.5, 0, IngredientType::Nut, "鸟类喜欢吃的树果"));

	// ==================== FISH 鱼类 ====================
	unitList.push_back(Ingredient("精力鲈鱼", 36, 1, 0, IngredientType::Fish, "能恢复精力的鱼类", Effect(EffectType::Health, 1)));
	unitList.push_back(Ingredient("铠甲鲈鱼", 37, 1, 30, IngredientType::Fish, "能提升防御力的鱼类", Effect(EffectType::Defence, 1)));
	unitList.push_back(Ingredient("冰冷鲈鱼", 38, 1, 30, IngredientType::Fish, "能提供抗热效果的鱼类", Effect(EffectType::WarmDef, 1)));
	unitList.push_back(Ingredient("暖暖鲈鱼", 39, 1, 30, IngredientType::Fish, "能提供抗寒效果的鱼类", Effect(EffectType::ColdDef, 1)));
	unitList.push_back(Ingredient("酥麻鲈鱼", 40, 1, 30, IngredientType::Fish, "能提供电击防护的鱼类", Effect(EffectType::ParalysisDef, 1)));
	unitList.push_back(Ingredient("生命鲈鱼", 41, 4, 0, IngredientType::Fish, "能恢复大量体力的稀有鱼类"));
	unitList.push_back(Ingredient("大剑鲈鱼", 42, 2, 30, IngredientType::Fish, "能提升攻击力的强力鱼类", Effect(EffectType::Attack, 1)));
	unitList.push_back(Ingredient("速速鲈鱼", 43, 1, 30, IngredientType::Fish, "能让移动更快的鱼类", Effect(EffectType::Speed, 1)));
	unitList.push_back(Ingredient("潜行鳟鱼", 44, 1, 60, IngredientType::Fish, "能让行动更安静的鱼类", Effect(EffectType::Sneaky, 1)));
	unitList.push_back(Ingredient("生命三文鱼", 81, 4, 0, IngredientType::Fish, "能增加体力上限的三文鱼", Effect(EffectType::Health, 4)));
	unitList.push_back(Ingredient("生命海螺", 82, 3, 0, IngredientType::Fish, "能增加体力上限的海螺", Effect(EffectType::Health, 3)));
	unitList.push_back(Ingredient("海拉鲁鲈鱼", 83, 1, 30, IngredientType::Fish, "海拉鲁常见的鲈鱼"));
	unitList.push_back(Ingredient("三色鲈鱼", 84, 1, 30, IngredientType::Fish, "色彩斑斓的鲈鱼"));
	// ==================== MONSTER 怪物材料类 ====================
	unitList.push_back(Ingredient("怪物精华", 45, 0, 0, IngredientType::Monster, "使料理效果随机化的神秘精华"));
	unitList.push_back(Ingredient("莱尼尔的肝脏", 46, 9, 0, IngredientType::Monster, "莱尼尔掉落的珍贵内脏"));
	unitList.push_back(Ingredient("莱尼尔的蹄子", 47, 3, 0, IngredientType::Monster, "莱尼尔强壮的蹄子"));
	unitList.push_back(Ingredient("古代螺丝", 48, 0, 0, IngredientType::Monster, "守护者掉落的古代零件"));
	unitList.push_back(Ingredient("丘丘胶", 49, 0, 0, IngredientType::Monster, "丘丘掉落的胶状物质"));
	unitList.push_back(Ingredient("莫力布林的肝脏", 50, 5, 0, IngredientType::Monster, "莫力布林掉落的巨大内脏"));
	unitList.push_back(Ingredient("蜥蜴战士的尾巴", 51, 2, 0, IngredientType::Monster, "蜥蜴战士灵活的尾巴"));

	// ==================== 其他重要食材（分类补充） ====================
	// 谷物/调料（归为Nut）
	unitList.push_back(Ingredient("蔗糖", 52, 0, 0, IngredientType::Nut, "从甘蔗提炼的甜味剂"));
	unitList.push_back(Ingredient("山羊黄油", 53, 0.5, 0, IngredientType::Nut, "山羊奶制成的黄油"));
	unitList.push_back(Ingredient("鲜奶", 54, 0.5, 0, IngredientType::Nut, "新鲜的山羊奶"));
	unitList.push_back(Ingredient("禽蛋", 55, 1, 0, IngredientType::Nut, "鸟类的蛋"));
	unitList.push_back(Ingredient("岩盐", 56, 0, 0, IngredientType::Nut, "从岩壁采集的天然盐"));
	unitList.push_back(Ingredient("鼓隆的调味粉", 65, 0, 0, IngredientType::Nut, "鼓隆族特制的调味料"));
	// 补充图片中的配料
	unitList.push_back(Ingredient("精力蜂的蜂蜜", 88, 2, 0, IngredientType::Nut, "精力蜂采集的蜂蜜，能恢复精力", Effect(EffectType::Health, 0.4)));

	// 主食/辅食补充
	unitList.push_back(Ingredient("橙子", 89, 0.5, 50, IngredientType::Nut, "香甜的橙子"));

	// 昆虫/蜥蜴
	unitList.push_back(Ingredient("精力蚱蜢", 57, 0, 0, IngredientType::Insect, "能恢复精力的昆虫", Effect(EffectType::Health, 1)));
	unitList.push_back(Ingredient("冷静蜥蜴", 58, 0, 60, IngredientType::Insect, "能提供抗热效果的蜥蜴", Effect(EffectType::WarmDef, 1)));
	unitList.push_back(Ingredient("暖暖蜥蜴", 59, 0, 60, IngredientType::Insect, "能提供抗寒效果的蜥蜴", Effect(EffectType::ColdDef, 1)));
	unitList.push_back(Ingredient("酥麻蜥蜴", 60, 0, 60, IngredientType::Insect, "能提供电击防护的蜥蜴", Effect(EffectType::ParalysisDef, 1)));
	unitList.push_back(Ingredient("潜行田螺", 61, 0, 60, IngredientType::Insect, "能让行动更安静的田螺", Effect(EffectType::Sneaky, 1)));
	unitList.push_back(Ingredient("大剑螃蟹", 62, 1, 30, IngredientType::Insect, "能提升攻击力的螃蟹", Effect(EffectType::Attack, 1)));
	unitList.push_back(Ingredient("铠甲螃蟹", 63, 1, 30, IngredientType::Insect, "能提升防御力的螃蟹", Effect(EffectType::Defence, 1)));
	unitList.push_back(Ingredient("速速青蛙", 64, 0, 60, IngredientType::Insect, "能让移动更快的青蛙", Effect(EffectType::Speed, 1)));
	InitIngredientMap();
}