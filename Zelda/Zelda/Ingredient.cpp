#include "Ingredient.h"
#include "AllStruct.h"
using namespace std;
RecipeHashList recipes;
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

EffectType Ingredient::GetCookedEffect()
{
	return effect.effectType;
}

int Ingredient::GetHealValue()
{
	return basicHealValue;
}

int Ingredient::GetID() const
{
	return ID;
}

bool Ingredient::operator==(const Ingredient& otherIngredient)
{
	return ID == otherIngredient.ID;
}

void InitEffectBaseName()
{
	EffectBaseName.Insert(EffectType::Attack, "攻击力提升");
	EffectBaseName.Insert(EffectType::Defence, "防御提升");
	EffectBaseName.Insert(EffectType::Speed, "移动力提升");
	EffectBaseName.Insert(EffectType::Health, "完全生命回复");
	EffectBaseName.Insert(EffectType::Sneaky, "安静性提升");
	EffectBaseName.Insert(EffectType::WarmDef, "耐热防护");
	EffectBaseName.Insert(EffectType::ColdDef, "耐寒防护");
	EffectBaseName.Insert(EffectType::ParalysisDef, "电麻防护");
	EffectBaseName.Insert(EffectType::None, "");
}
int FindMinID(ListNode<Ingredient>* f)
{
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
void InitAllRecipes()
{
	// ==================== VEGETABLE RECIPES 蔬菜类菜谱 ====================

	// 炒野菜（蔬菜）
	Recipe StirFriedVegetables(
		List<Ingredient>{},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{RecipeTypeNeed(IngredientType::Vegetable, 1)}
	);
	recipes.Insert(StirFriedVegetables);

	// 大份炒野菜（4种不同蔬菜）
	Recipe LargeStirFriedVegetables(
		List<Ingredient>{},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{
		RecipeTypeNeed(IngredientType::Vegetable, 1),
			RecipeTypeNeed(IngredientType::Vegetable, 1),
			RecipeTypeNeed(IngredientType::Vegetable, 1),
			RecipeTypeNeed(IngredientType::Vegetable, 1)
	}
	);
	recipes.Insert(LargeStirFriedVegetables);

	// 甘露炖蔬菜（蔬菜 + 精力蜂的蜂蜜）
	Recipe SweetStewedVegetables(
		List<Ingredient>{*(ingredientMap["精力蜂的蜂蜜"])},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{RecipeTypeNeed(IngredientType::Vegetable, 1)}
	);
	recipes.Insert(SweetStewedVegetables);

	// 野菜饭团（蔬菜 + 海拉鲁米）
	Recipe VegetableRiceBalls(
		List<Ingredient>{*(ingredientMap["海拉鲁米"])},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{RecipeTypeNeed(IngredientType::Vegetable, 1)}
	);
	recipes.Insert(VegetableRiceBalls);

	// 蔬菜煎蛋卷（蔬菜 + 禽蛋 + 山羊黄油 + 岩盐）
	Recipe VegetableOmelette(
		List<Ingredient>{
		*(ingredientMap["禽蛋"]),
			* (ingredientMap["山羊黄油"]),
			* (ingredientMap["岩盐"])
	},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{RecipeTypeNeed(IngredientType::Vegetable, 1)}
	);
	recipes.Insert(VegetableOmelette);

	// 炒香菜（蔬菜 + 鼓隆的调味粉）
	Recipe FriedSpicyVegetables(
		List<Ingredient>{*(ingredientMap["鼓隆的调味粉"])},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{RecipeTypeNeed(IngredientType::Vegetable, 1)}
	);
	recipes.Insert(FriedSpicyVegetables);

	// 盐烤野菜（蔬菜 + 岩盐）
	Recipe SaltRoastedVegetables(
		List<Ingredient>{*(ingredientMap["岩盐"])},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{RecipeTypeNeed(IngredientType::Vegetable, 1)}
	);
	recipes.Insert(SaltRoastedVegetables);

	// 闷胡萝卜（萝卜 + 塔邦挞小麦 + 鲜奶 + 山羊黄油）
	Recipe StewedCarrots(
		List<Ingredient>{
		*(ingredientMap["塔邦挞小麦"]),
			* (ingredientMap["鲜奶"]),
			* (ingredientMap["山羊黄油"])
	},
		List<List<Ingredient>>{{
				// 多选一：各种萝卜
				*(ingredientMap["生命小萝卜"]),
					* (ingredientMap["生命大萝卜"]),
					* (ingredientMap["毅力胡萝卜"]),
					* (ingredientMap["速速胡萝卜"])
			}},
		List<RecipeTypeNeed>{}
	);
	recipes.Insert(StewedCarrots);

	// 胡萝卜蛋糕（萝卜 + 塔邦挞小麦 + 蔗糖 + 山羊黄油）
	Recipe CarrotCake(
		List<Ingredient>{
		*(ingredientMap["塔邦挞小麦"]),
			* (ingredientMap["蔗糖"]),
			* (ingredientMap["山羊黄油"])
	},
		List<List<Ingredient>>{{
				// 多选一：各种萝卜
				*(ingredientMap["生命小萝卜"]),
					* (ingredientMap["生命大萝卜"]),
					* (ingredientMap["毅力胡萝卜"]),
					* (ingredientMap["速速胡萝卜"])
			}},
		List<RecipeTypeNeed>{}
	);
	recipes.Insert(CarrotCake);

	// 心心牛奶汤（生命大萝卜/生命小萝卜 + 冰冷蜜瓜 + 酥麻水果 + 鲜奶）
	Recipe HeartyMilkSoup(
		List<Ingredient>{
		*(ingredientMap["冰冷蜜瓜"]),
			* (ingredientMap["酥麻水果"]),
			* (ingredientMap["鲜奶"])
	},
		List<List<Ingredient>>{{
				// 多选一：生命萝卜
				*(ingredientMap["生命大萝卜"]),
					* (ingredientMap["生命小萝卜"])
			}},
		List<RecipeTypeNeed>{}
	);
	recipes.Insert(HeartyMilkSoup);

	// 蔬菜浓汤（毅力胡萝卜/速速胡萝卜/铠甲南瓜 + 鲜奶 + 岩盐）
	Recipe ThickVegetableSoup(
		List<Ingredient>{
		*(ingredientMap["鲜奶"]),
			* (ingredientMap["岩盐"])
	},
		List<List<Ingredient>>{{
				// 多选一
				*(ingredientMap["毅力胡萝卜"]),
					* (ingredientMap["速速胡萝卜"]),
					* (ingredientMap["铠甲南瓜"])
			}},
		List<RecipeTypeNeed>{}
	);
	recipes.Insert(ThickVegetableSoup);

	// 蔬菜牛奶汤（除毅力胡萝卜/速速胡萝卜/铠甲南瓜外的蔬菜 + 鲜奶 + 岩盐）
	Recipe VegetableMilkSoup(
		List<Ingredient>{
		*(ingredientMap["鲜奶"]),
			* (ingredientMap["岩盐"])
	},
		List<List<Ingredient>>{{
				// 列出除毅力胡萝卜、速速胡萝卜、铠甲南瓜外的蔬菜
				*(ingredientMap["海拉鲁米"]),
					* (ingredientMap["塔邦挞小麦"])
			}},
		List<RecipeTypeNeed>{}
	);
	recipes.Insert(VegetableMilkSoup);

	// 蔬菜烩饭（毅力胡萝卜/速速胡萝卜/铠甲南瓜 + 海拉鲁米 + 山羊黄油 + 岩盐）
	Recipe VegetableRisotto(
		List<Ingredient>{
		*(ingredientMap["海拉鲁米"]),
			* (ingredientMap["山羊黄油"]),
			* (ingredientMap["岩盐"])
	},
		List<List<Ingredient>>{{
				// 多选一
				*(ingredientMap["毅力胡萝卜"]),
					* (ingredientMap["速速胡萝卜"]),
					* (ingredientMap["铠甲南瓜"])
			}},
		List<RecipeTypeNeed>{}
	);
	recipes.Insert(VegetableRisotto);

	// 蔬菜咖喱饭（毅力胡萝卜/速速胡萝卜/铠甲南瓜 + 海拉鲁米 + 鼓隆的调味粉）
	Recipe VegetableCurry(
		List<Ingredient>{
		*(ingredientMap["海拉鲁米"]),
			* (ingredientMap["鼓隆的调味粉"])
	},
		List<List<Ingredient>>{{
				// 多选一
				*(ingredientMap["毅力胡萝卜"]),
					* (ingredientMap["速速胡萝卜"]),
					* (ingredientMap["铠甲南瓜"])
			}},
		List<RecipeTypeNeed>{}
	);
	recipes.Insert(VegetableCurry);

	// 闷南瓜（铠甲南瓜 + 塔邦挞小麦 + 鲜奶 + 山羊黄油）
	Recipe StewedPumpkin(
		List<Ingredient>{
		*(ingredientMap["铠甲南瓜"]),
			* (ingredientMap["塔邦挞小麦"]),
			* (ingredientMap["鲜奶"]),
			* (ingredientMap["山羊黄油"])
	},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{}
	);
	recipes.Insert(StewedPumpkin);

	// 南瓜蛋糕（铠甲南瓜 + 塔邦挞小麦 + 蔗糖 + 山羊黄油）
	Recipe PumpkinCake(
		List<Ingredient>{
		*(ingredientMap["铠甲南瓜"]),
			* (ingredientMap["塔邦挞小麦"]),
			* (ingredientMap["蔗糖"]),
			* (ingredientMap["山羊黄油"])
	},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{}
	);
	recipes.Insert(PumpkinCake);
	// ==================== FRUIT RECIPES 水果类菜谱 ====================

// 炖水果（任意水果）
	Recipe StewedFruit(
		List<Ingredient>{},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{RecipeTypeNeed(IngredientType::Fruit, 1)}
	);
	recipes.Insert(StewedFruit);

	// 大份炖水果（4种不同水果）
	Recipe LargeStewedFruit(
		List<Ingredient>{},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{
		RecipeTypeNeed(IngredientType::Fruit, 1),
			RecipeTypeNeed(IngredientType::Fruit, 1),
			RecipeTypeNeed(IngredientType::Fruit, 1),
			RecipeTypeNeed(IngredientType::Fruit, 1)
	}
	);
	recipes.Insert(LargeStewedFruit);

	// 蒸水果（水果 + 蔬菜）
	Recipe SteamedFruit(
		List<Ingredient>{},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{
		RecipeTypeNeed(IngredientType::Fruit, 1),
			RecipeTypeNeed(IngredientType::Vegetable, 1)
	}
	);
	recipes.Insert(SteamedFruit);

	// 水果蛋糕（水果 + 苹果/草莓 + 塔邦挞小麦 + 蔗糖）
	Recipe FruitCake(
		List<Ingredient>{
		*(ingredientMap["塔邦挞小麦"]),
			* (ingredientMap["蔗糖"])
	},
		List<List<Ingredient>>{{
				// 多选一：苹果或草莓
				*(ingredientMap["苹果"]),
					* (ingredientMap["草莓"])
			}},
		List<RecipeTypeNeed>{RecipeTypeNeed(IngredientType::Fruit, 1)}
	);
	recipes.Insert(FruitCake);

	// 水果派（水果 + 塔邦挞小麦 + 山羊黄油 + 蔗糖）
	Recipe FruitPie(
		List<Ingredient>{
		*(ingredientMap["塔邦挞小麦"]),
			* (ingredientMap["山羊黄油"]),
			* (ingredientMap["蔗糖"])
	},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{RecipeTypeNeed(IngredientType::Fruit, 1)}
	);
	recipes.Insert(FruitPie);

	// 蜂蜜苹果（苹果 + 精力蜂的蜂蜜）
	Recipe HoneyApple(
		List<Ingredient>{
		*(ingredientMap["苹果"]),
			* (ingredientMap["精力蜂的蜂蜜"])
	},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{}
	);
	recipes.Insert(HoneyApple);

	// 苹果派（苹果 + 塔邦挞小麦 + 山羊黄油 + 蔗糖）
	Recipe ApplePie(
		List<Ingredient>{
		*(ingredientMap["苹果"]),
			* (ingredientMap["塔邦挞小麦"]),
			* (ingredientMap["山羊黄油"]),
			* (ingredientMap["蔗糖"])
	},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{}
	);
	recipes.Insert(ApplePie);

	// 黄油苹果（苹果 + 山羊黄油）
	Recipe ButteredApple(
		List<Ingredient>{
		*(ingredientMap["苹果"]),
			* (ingredientMap["山羊黄油"])
	},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{}
	);
	recipes.Insert(ButteredApple);

	// 蜂蜜水果（苹果外的水果 + 精力蜂的蜂蜜）
	Recipe HoneyFruit(
		List<Ingredient>{*(ingredientMap["精力蜂的蜂蜜"])},
		List<List<Ingredient>>{{
				// 多选一：所有非苹果的水果
				*(ingredientMap["椰子"]),
					* (ingredientMap["草莓"]),
					* (ingredientMap["冰冷蜜瓜"]),
					* (ingredientMap["暖暖草果"]),
					* (ingredientMap["酥麻水果"]),
					* (ingredientMap["大剑香蕉"]),
					* (ingredientMap["生命小萝卜"]),
					* (ingredientMap["生命大萝卜"]),
					* (ingredientMap["毅力胡萝卜"]),
					* (ingredientMap["速速胡萝卜"])
			}},
		List<RecipeTypeNeed>{}
	);
	recipes.Insert(HoneyFruit);

	// 草莓可丽饼（草莓 + 塔邦挞小麦 + 禽蛋 + 鲜奶 + 蔗糖）
	Recipe StrawberryCrepe(
		List<Ingredient>{
		*(ingredientMap["草莓"]),
			* (ingredientMap["塔邦挞小麦"]),
			* (ingredientMap["禽蛋"]),
			* (ingredientMap["鲜奶"]),
			* (ingredientMap["蔗糖"])
	},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{}
	);
	recipes.Insert(StrawberryCrepe);

	// 炒暖暖草果（暖暖草果）
	Recipe FriedWarmSedge(
		List<Ingredient>{*(ingredientMap["暖暖草果"])},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{}
	);
	recipes.Insert(FriedWarmSedge);

	// 炸香蕉（大剑香蕉 + 塔邦挞小麦 + 蔗糖）
	Recipe FriedBanana(
		List<Ingredient>{
		*(ingredientMap["大剑香蕉"]),
			* (ingredientMap["塔邦挞小麦"]),
			* (ingredientMap["蔗糖"])
	},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{}
	);
	recipes.Insert(FriedBanana);
	// ==================== MEAT RECIPES 肉类菜谱 ====================

// 烤肉串（任意肉类）
	Recipe MeatSkewers(
		List<Ingredient>{},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{RecipeTypeNeed(IngredientType::Meat, 1)}
	);
	recipes.Insert(MeatSkewers);

	// 大份烤肉串（4种不同肉类）
	Recipe LargeMeatSkewers(
		List<Ingredient>{},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{
		RecipeTypeNeed(IngredientType::Meat, 1),
			RecipeTypeNeed(IngredientType::Meat, 1),
			RecipeTypeNeed(IngredientType::Meat, 1),
			RecipeTypeNeed(IngredientType::Meat, 1)
	}
	);
	recipes.Insert(LargeMeatSkewers);

	// 香辣煎肉（肉类 + 暖暖草果）
	Recipe SpicyFriedMeat(
		List<Ingredient>{*(ingredientMap["暖暖草果"])},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{RecipeTypeNeed(IngredientType::Meat, 1)}
	);
	recipes.Insert(SpicyFriedMeat);

	// 烤肉蘑菇串（肉类 + 菌类）
	Recipe MeatMushroomSkewers(
		List<Ingredient>{},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{
		RecipeTypeNeed(IngredientType::Meat, 1),
			RecipeTypeNeed(IngredientType::Mushroom, 1)
	}
	);
	recipes.Insert(MeatMushroomSkewers);

	// 蒸肉（肉类 + 蔬菜）
	Recipe SteamedMeat(
		List<Ingredient>{},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{
		RecipeTypeNeed(IngredientType::Meat, 1),
			RecipeTypeNeed(IngredientType::Vegetable, 1)
	}
	);
	recipes.Insert(SteamedMeat);

	// 鲜肉牛奶汤（肉类 + 蔬菜 + 鲜奶 + 岩盐）
	Recipe MeatMilkSoup(
		List<Ingredient>{
		*(ingredientMap["鲜奶"]),
			* (ingredientMap["岩盐"])
	},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{
		RecipeTypeNeed(IngredientType::Meat, 1),
			RecipeTypeNeed(IngredientType::Vegetable, 1)
	}
	);
	recipes.Insert(MeatMilkSoup);

	// 南瓜酿肉（肉类 + 铠甲南瓜）
	Recipe StuffedPumpkin(
		List<Ingredient>{*(ingredientMap["铠甲南瓜"])},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{RecipeTypeNeed(IngredientType::Meat, 1)}
	);
	recipes.Insert(StuffedPumpkin);

	// 海陆煎烧（肉类 + 鱼类）
	Recipe LandAndSeaGrill(
		List<Ingredient>{},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{
		RecipeTypeNeed(IngredientType::Meat, 1),
			RecipeTypeNeed(IngredientType::Fish, 1)
	}
	);
	recipes.Insert(LandAndSeaGrill);

	// 甘露炖肉（肉类 + 精力蜂的蜂蜜）
	Recipe SweetStewedMeat(
		List<Ingredient>{*(ingredientMap["精力蜂的蜂蜜"])},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{RecipeTypeNeed(IngredientType::Meat, 1)}
	);
	recipes.Insert(SweetStewedMeat);

	// 鲜肉饭团（肉类 + 海拉鲁米）
	Recipe MeatRiceBalls(
		List<Ingredient>{*(ingredientMap["海拉鲁米"])},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{RecipeTypeNeed(IngredientType::Meat, 1)}
	);
	recipes.Insert(MeatRiceBalls);

	// 禽肉菜饭（禽肉 + 海拉鲁米 + 禽蛋 + 山羊黄油）
	Recipe PoultryVegetableRice(
		List<Ingredient>{
		*(ingredientMap["海拉鲁米"]),
			* (ingredientMap["禽蛋"]),
			* (ingredientMap["山羊黄油"])
	},
		List<List<Ingredient>>{{
				// 多选一：禽肉类
				*(ingredientMap["禽肉"]),
					* (ingredientMap["高级禽肉"]),
					* (ingredientMap["顶级禽肉"])
			}},
		List<RecipeTypeNeed>{}
	);
	recipes.Insert(PoultryVegetableRice);

	// 兽肉盖饭（兽肉 + 海拉鲁米 + 岩盐）
	Recipe BeastMeatRiceBowl(
		List<Ingredient>{
		*(ingredientMap["海拉鲁米"]),
			* (ingredientMap["岩盐"])
	},
		List<List<Ingredient>>{{
				// 多选一：兽肉类
				*(ingredientMap["兽肉"]),
					* (ingredientMap["高级兽肉"]),
					* (ingredientMap["顶级兽肉"])
			}},
		List<RecipeTypeNeed>{}
	);
	recipes.Insert(BeastMeatRiceBowl);

	// 兽肉咖喱饭（兽肉 + 海拉鲁米 + 鼓隆的调味粉）
	Recipe BeastMeatCurry(
		List<Ingredient>{
		*(ingredientMap["海拉鲁米"]),
			* (ingredientMap["鼓隆的调味粉"])
	},
		List<List<Ingredient>>{{
				// 多选一：兽肉类
				*(ingredientMap["兽肉"]),
					* (ingredientMap["高级兽肉"]),
					* (ingredientMap["顶级兽肉"])
			}},
		List<RecipeTypeNeed>{}
	);
	recipes.Insert(BeastMeatCurry);

	// 禽肉咖喱饭（禽肉 + 海拉鲁米 + 鼓隆的调味粉）
	Recipe PoultryCurry(
		List<Ingredient>{
		*(ingredientMap["海拉鲁米"]),
			* (ingredientMap["鼓隆的调味粉"])
	},
		List<List<Ingredient>>{{
				// 多选一：禽肉类
				*(ingredientMap["禽肉"]),
					* (ingredientMap["高级禽肉"]),
					* (ingredientMap["顶级禽肉"])
			}},
		List<RecipeTypeNeed>{}
	);
	recipes.Insert(PoultryCurry);

	// 焖肉（肉类 + 塔邦挞小麦 + 鲜奶 + 山羊黄油）
	Recipe BraisedMeat(
		List<Ingredient>{
		*(ingredientMap["塔邦挞小麦"]),
			* (ingredientMap["鲜奶"]),
			* (ingredientMap["山羊黄油"])
	},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{RecipeTypeNeed(IngredientType::Meat, 1)}
	);
	recipes.Insert(BraisedMeat);

	// 鲜肉派（肉类 + 塔邦挞小麦 + 山羊黄油 + 岩盐）
	Recipe MeatPie(
		List<Ingredient>{
		*(ingredientMap["塔邦挞小麦"]),
			* (ingredientMap["山羊黄油"]),
			* (ingredientMap["岩盐"])
	},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{RecipeTypeNeed(IngredientType::Meat, 1)}
	);
	recipes.Insert(MeatPie);

	// 烤兽肉串（兽肉类 + 鼓隆的调味粉）
	Recipe GrilledBeastSkewers(
		List<Ingredient>{*(ingredientMap["鼓隆的调味粉"])},
		List<List<Ingredient>>{{
				// 多选一：兽肉类
				*(ingredientMap["兽肉"]),
					* (ingredientMap["高级兽肉"]),
					* (ingredientMap["顶级兽肉"])
			}},
		List<RecipeTypeNeed>{}
	);
	recipes.Insert(GrilledBeastSkewers);

	// 烤禽肉串（禽肉类 + 鼓隆的调味粉）
	Recipe GrilledPoultrySkewers(
		List<Ingredient>{*(ingredientMap["鼓隆的调味粉"])},
		List<List<Ingredient>>{{
				// 多选一：禽肉类
				*(ingredientMap["禽肉"]),
					* (ingredientMap["高级禽肉"]),
					* (ingredientMap["顶级禽肉"])
			}},
		List<RecipeTypeNeed>{}
	);
	recipes.Insert(GrilledPoultrySkewers);

	// 岩盐烤肉（肉类 + 岩盐）
	Recipe SaltGrilledMeat(
		List<Ingredient>{*(ingredientMap["岩盐"])},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{RecipeTypeNeed(IngredientType::Meat, 1)}
	);
	recipes.Insert(SaltGrilledMeat);
	// ==================== SEAFOOD RECIPES 海鲜类菜谱 ====================

// 烤鱼（任意鱼类）
	Recipe GrilledFish(
		List<Ingredient>{},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{RecipeTypeNeed(IngredientType::Fish, 1)}
	);
	recipes.Insert(GrilledFish);

	// 大份烤鱼（4种不同的鱼）
	Recipe LargeGrilledFish(
		List<Ingredient>{},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{
		RecipeTypeNeed(IngredientType::Fish, 1),
			RecipeTypeNeed(IngredientType::Fish, 1),
			RecipeTypeNeed(IngredientType::Fish, 1),
			RecipeTypeNeed(IngredientType::Fish, 1)
	}
	);
	recipes.Insert(LargeGrilledFish);

	// 香辣煎鱼（鱼类 + 暖暖草果）
	Recipe SpicyFriedFish(
		List<Ingredient>{*(ingredientMap["暖暖草果"])},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{RecipeTypeNeed(IngredientType::Fish, 1)}
	);
	recipes.Insert(SpicyFriedFish);

	// 烤鱼蘑菇串（鱼类 + 菌类）
	Recipe FishMushroomSkewers(
		List<Ingredient>{},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{
		RecipeTypeNeed(IngredientType::Fish, 1),
			RecipeTypeNeed(IngredientType::Mushroom, 1)
	}
	);
	recipes.Insert(FishMushroomSkewers);

	// 蒸鱼（鱼类 + 蔬菜）
	Recipe SteamedFish(
		List<Ingredient>{},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{
		RecipeTypeNeed(IngredientType::Fish, 1),
			RecipeTypeNeed(IngredientType::Vegetable, 1)
	}
	);
	recipes.Insert(SteamedFish);

	// 海鲜牛奶汤（鱼类 + 蔬菜 + 鲜奶 + 岩盐）
	Recipe SeafoodMilkSoup(
		List<Ingredient>{
		*(ingredientMap["鲜奶"]),
			* (ingredientMap["岩盐"])
	},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{
		RecipeTypeNeed(IngredientType::Fish, 1),
			RecipeTypeNeed(IngredientType::Vegetable, 1)
	}
	);
	recipes.Insert(SeafoodMilkSoup);

	// 甘露炖鱼（鱼类 + 精力蜂的蜂蜜）
	Recipe SweetStewedFish(
		List<Ingredient>{*(ingredientMap["精力蜂的蜂蜜"])},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{RecipeTypeNeed(IngredientType::Fish, 1)}
	);
	recipes.Insert(SweetStewedFish);

	// 海鲜饭团（鱼类 + 海拉鲁米）
	Recipe SeafoodRiceBalls(
		List<Ingredient>{*(ingredientMap["海拉鲁米"])},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{RecipeTypeNeed(IngredientType::Fish, 1)}
	);
	recipes.Insert(SeafoodRiceBalls);

	// 干煎鱼（鱼类 + 塔邦挞小麦 + 山羊黄油）
	Recipe PanFriedFish(
		List<Ingredient>{
		*(ingredientMap["塔邦挞小麦"]),
			* (ingredientMap["山羊黄油"])
	},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{RecipeTypeNeed(IngredientType::Fish, 1)}
	);
	recipes.Insert(PanFriedFish);

	// 鱼肉派（鱼类 + 塔邦挞小麦 + 山羊黄油 + 岩盐）
	Recipe FishPie(
		List<Ingredient>{
		*(ingredientMap["塔邦挞小麦"]),
			* (ingredientMap["山羊黄油"]),
			* (ingredientMap["岩盐"])
	},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{RecipeTypeNeed(IngredientType::Fish, 1)}
	);
	recipes.Insert(FishPie);

	// 盐烤鱼（鱼类 + 岩盐）
	Recipe SaltGrilledFish(
		List<Ingredient>{*(ingredientMap["岩盐"])},
		List<List<Ingredient>>{},
		List<RecipeTypeNeed>{RecipeTypeNeed(IngredientType::Fish, 1)}
	);
	recipes.Insert(SaltGrilledFish);

	// 三文鱼烩饭（生命鲈鱼 + 海拉鲁米 + 山羊黄油 + 岩盐）
	Recipe SalmonRisotto(
		List<Ingredient>{
		*(ingredientMap["海拉鲁米"]),
			* (ingredientMap["山羊黄油"]),
			* (ingredientMap["岩盐"])
	},
		List<List<Ingredient>>{{*(ingredientMap["生命鲈鱼"])}},
		List<RecipeTypeNeed>{}
	);
	recipes.Insert(SalmonRisotto);

	// 生命干煎三文鱼（生命鲈鱼 + 塔邦挞小麦 + 山羊黄油）
	Recipe PanFriedSalmon(
		List<Ingredient>{
		*(ingredientMap["塔邦挞小麦"]),
			* (ingredientMap["山羊黄油"])
	},
		List<List<Ingredient>>{{*(ingredientMap["生命鲈鱼"])}},
		List<RecipeTypeNeed>{}
	);
	recipes.Insert(PanFriedSalmon);

	// 贝肉杂烩（生命海螺 + 塔邦挞小麦 + 鲜奶 + 山羊黄油）
	Recipe ClamChowder(
		List<Ingredient>{
		*(ingredientMap["塔邦挞小麦"]),
			* (ingredientMap["鲜奶"]),
			* (ingredientMap["山羊黄油"])
	},
		List<List<Ingredient>>{{*(ingredientMap["生命海螺"])}},
		List<RecipeTypeNeed>{}
	);
	recipes.Insert(ClamChowder);

	// 串烤海鲜（生命海螺/大剑鲷鱼/铠甲鲷鱼）
	Recipe SeafoodSkewers(
		List<Ingredient>{},
		List<List<Ingredient>>{{
				*(ingredientMap["生命海螺"]),
					* (ingredientMap["大剑鲷鱼"]),
					* (ingredientMap["铠甲鲷鱼"])
			}},
		List<RecipeTypeNeed>{}
	);
	recipes.Insert(SeafoodSkewers);

	// 海鲜杂烩饭（生命海螺/大剑鲷鱼/铠甲鲷鱼 + 海拉鲁米 + 山羊黄油 + 岩盐）
	Recipe SeafoodPaella(
		List<Ingredient>{
		*(ingredientMap["海拉鲁米"]),
			* (ingredientMap["山羊黄油"]),
			* (ingredientMap["岩盐"])
	},
		List<List<Ingredient>>{{
				*(ingredientMap["生命海螺"]),
					* (ingredientMap["大剑鲷鱼"]),
					* (ingredientMap["铠甲鲷鱼"])
			}},
		List<RecipeTypeNeed>{}
	);
	recipes.Insert(SeafoodPaella);

	// 海鲜咖喱饭（生命海螺/大剑鲷鱼/铠甲鲷鱼 + 海拉鲁米 + 鼓隆的调味粉）
	Recipe SeafoodCurry(
		List<Ingredient>{
		*(ingredientMap["海拉鲁米"]),
			* (ingredientMap["鼓隆的调味粉"])
	},
		List<List<Ingredient>>{{
				*(ingredientMap["生命海螺"]),
					* (ingredientMap["大剑鲷鱼"]),
					* (ingredientMap["铠甲鲷鱼"])
			}},
		List<RecipeTypeNeed>{}
	);
	recipes.Insert(SeafoodCurry);

	// 海鲜炒饭（生命海螺/大剑鲷鱼/铠甲鲷鱼 + 海拉鲁米 + 岩盐）
	Recipe SeafoodFriedRice(
		List<Ingredient>{
		*(ingredientMap["海拉鲁米"]),
			* (ingredientMap["岩盐"])
	},
		List<List<Ingredient>>{{
				*(ingredientMap["生命海螺"]),
					* (ingredientMap["大剑鲷鱼"]),
					* (ingredientMap["铠甲鲷鱼"])
			}},
		List<RecipeTypeNeed>{}
	);
	recipes.Insert(SeafoodFriedRice);

	// 干煎鲷鱼（大剑鲷鱼/铠甲鲷鱼 + 塔邦挞小麦 + 山羊黄油）
	Recipe PanFriedBream(
		List<Ingredient>{
		*(ingredientMap["塔邦挞小麦"]),
			* (ingredientMap["山羊黄油"])
	},
		List<List<Ingredient>>{{
				*(ingredientMap["大剑鲷鱼"]),
					* (ingredientMap["铠甲鲷鱼"])
			}},
		List<RecipeTypeNeed>{}
	);
	recipes.Insert(PanFriedBream);

	// 蟹肉蛋炒饭（蟹类 + 海拉鲁米 + 禽蛋 + 岩盐）
	Recipe CrabFriedRice(
		List<Ingredient>{
		*(ingredientMap["海拉鲁米"]),
			* (ingredientMap["禽蛋"]),
			* (ingredientMap["岩盐"])
	},
		List<List<Ingredient>>{{
				// 多选一：蟹类（假设有这些食材）
				*(ingredientMap["大剑螃蟹"]),
					* (ingredientMap["铠甲螃蟹"])
			}},
		List<RecipeTypeNeed>{}
	);
	recipes.Insert(CrabFriedRice);

	// 蟹肉烩饭（蟹类 + 海拉鲁米 + 山羊黄油 + 岩盐）
	Recipe CrabRisotto(
		List<Ingredient>{
		*(ingredientMap["海拉鲁米"]),
			* (ingredientMap["山羊黄油"]),
			* (ingredientMap["岩盐"])
	},
		List<List<Ingredient>>{{
				// 多选一：蟹类
				*(ingredientMap["大剑螃蟹"]),
					* (ingredientMap["铠甲螃蟹"])
			}},
		List<RecipeTypeNeed>{}
	);
	recipes.Insert(CrabRisotto);

	// 炒螃蟹（蟹类 + 鼓隆的调味粉）
	Recipe FriedCrab(
		List<Ingredient>{*(ingredientMap["鼓隆的调味粉"])},
		List<List<Ingredient>>{{
				// 多选一：蟹类
				*(ingredientMap["大剑螃蟹"]),
					* (ingredientMap["铠甲螃蟹"])
			}},
		List<RecipeTypeNeed>{}
	);
	recipes.Insert(FriedCrab);

	// 岩盐烤蟹（蟹类 + 岩盐）
	Recipe SaltGrilledCrab(
		List<Ingredient>{*(ingredientMap["岩盐"])},
		List<List<Ingredient>>{{
				// 多选一：蟹类
				*(ingredientMap["大剑螃蟹"]),
					* (ingredientMap["铠甲螃蟹"])
			}},
		List<RecipeTypeNeed>{}
	);
	recipes.Insert(SaltGrilledCrab);

	// 烤海鲜串（蟹类/螺类）
	Recipe SeafoodSkewers2(
		List<Ingredient>{},
		List<List<Ingredient>>{{
				// 多选一：蟹类或螺类
				*(ingredientMap["大剑螃蟹"]),
					* (ingredientMap["铠甲螃蟹"]),
					* (ingredientMap["生命海螺"])
			}},
		List<RecipeTypeNeed>{}
	);
	recipes.Insert(SeafoodSkewers2);
}
void InitIngredientMap()
{
	for(int i=0;i<unitList.size();i++)
	{
		ingredientMap.Insert(unitList[i].GetName(),unitList[i]);
	}
}

void InitAllUnits()
{
	// ==================== FRUIT 水果类 ====================
	unitList.push_back(Ingredient("苹果", 1, 0.5, 0, IngredientType::Fruit, "海拉鲁最常见的果实，可以恢复少量体力"));
	unitList.push_back(Ingredient("椰子", 2, 0.5, 0, IngredientType::Fruit, "热带海岸的果实，坚硬外壳内有清甜汁液"));
	unitList.push_back(Ingredient("草莓", 3, 0.5, 0, IngredientType::Fruit, "小巧的红色果实，生长在草地和森林中"));
	unitList.push_back(Ingredient("冰冷蜜瓜", 4, 1, 30, IngredientType::Fruit, "格鲁德地区特产，能提供抗热效果", Effect(EffectType::FireDef, 1)));
	unitList.push_back(Ingredient("暖暖草果", 5, 0.5, 30, IngredientType::Fruit, "散发温暖的红色果实，能抵御寒冷", Effect(EffectType::ColdDef, 1)));
	unitList.push_back(Ingredient("酥麻水果", 6, 1, 30, IngredientType::Fruit, "费罗尼地区的特殊水果，提供电击防护", Effect(EffectType::ParalysisDef, 1)));
	unitList.push_back(Ingredient("大剑香蕉", 7, 1, 30, IngredientType::Fruit, "依盖队最爱的水果，能提升攻击力", Effect(EffectType::Attack, 1)));
	unitList.push_back(Ingredient("生命小萝卜", 8, 4, 0, IngredientType::Fruit, "能恢复大量体力的珍贵植物"));
	unitList.push_back(Ingredient("生命大萝卜", 9, 12, 0, IngredientType::Fruit, "极其稀有的超级萝卜，能恢复巨量体力"));
	unitList.push_back(Ingredient("毅力胡萝卜", 10, 2, 0, IngredientType::Fruit, "能提供额外黄心的神奇胡萝卜", Effect(EffectType::Health, 4)));
	unitList.push_back(Ingredient("速速胡萝卜", 11, 0.5, 30, IngredientType::Fruit, "能让食用者移动更快的胡萝卜", Effect(EffectType::Speed, 1)));

	// ==================== MEAT 肉类 ====================
	unitList.push_back(Ingredient("生肉", 12, 1, 0, IngredientType::Meat, "普通动物的肉，基础食材"));
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
	unitList.push_back(Ingredient("冰冷蘑菇", 24, 0.5, 30, IngredientType::Mushroom, "生长在寒冷地区的抗热蘑菇", Effect(EffectType::FireDef, 1)));
	unitList.push_back(Ingredient("暖暖蘑菇", 25, 0.5, 30, IngredientType::Mushroom, "生长在温暖地区的抗寒蘑菇", Effect(EffectType::ColdDef, 1)));
	unitList.push_back(Ingredient("酥麻蘑菇", 26, 0.5, 30, IngredientType::Mushroom, "能在雷雨天找到的防电蘑菇", Effect(EffectType::ParalysisDef, 1)));
	unitList.push_back(Ingredient("潜行蘑菇", 27, 0.5, 60, IngredientType::Mushroom, "能让行动更安静的蘑菇", Effect(EffectType::Sneaky, 1)));
	unitList.push_back(Ingredient("大剑蘑菇", 28, 1, 30, IngredientType::Mushroom, "能提升攻击力的强力蘑菇", Effect(EffectType::Attack, 1)));
	unitList.push_back(Ingredient("速速蘑菇", 29, 0.5, 30, IngredientType::Mushroom, "能让移动更快的蘑菇", Effect(EffectType::Speed, 1)));
	unitList.push_back(Ingredient("毅力蘑菇", 30, 2, 0, IngredientType::Mushroom, "能提供额外黄心的稀有蘑菇", Effect(EffectType::Health, 4)));

	// ==================== VEGETABLE 蔬菜类 ====================
	unitList.push_back(Ingredient("铠甲南瓜", 31, 1, 30, IngredientType::Vegetable, "卡卡利科村特产，能提升防御力", Effect(EffectType::Defence, 1)));
	unitList.push_back(Ingredient("海拉鲁米", 32, 1, 0, IngredientType::Vegetable, "海拉鲁主要粮食作物"));
	unitList.push_back(Ingredient("塔邦挞小麦", 33, 1, 0, IngredientType::Vegetable, "塔邦挞地区种植的优质小麦"));

	// ==================== NUT 坚果类 ====================
	unitList.push_back(Ingredient("橡子", 34, 0.25, 0, IngredientType::Nut, "击打树木获得的小坚果"));
	unitList.push_back(Ingredient("小鸟的树果", 35, 0.5, 0, IngredientType::Nut, "鸟类喜欢吃的树果"));

	// ==================== FISH 鱼类 ====================
	unitList.push_back(Ingredient("精力鲈鱼", 36, 1, 0, IngredientType::Fish, "能恢复精力的鱼类", Effect(EffectType::Health, 1)));
	unitList.push_back(Ingredient("铠甲鲈鱼", 37, 1, 30, IngredientType::Fish, "能提升防御力的鱼类", Effect(EffectType::Defence, 1)));
	unitList.push_back(Ingredient("冰冷鲈鱼", 38, 1, 30, IngredientType::Fish, "能提供抗热效果的鱼类", Effect(EffectType::FireDef, 1)));
	unitList.push_back(Ingredient("暖暖鲈鱼", 39, 1, 30, IngredientType::Fish, "能提供抗寒效果的鱼类", Effect(EffectType::ColdDef, 1)));
	unitList.push_back(Ingredient("酥麻鲈鱼", 40, 1, 30, IngredientType::Fish, "能提供电击防护的鱼类", Effect(EffectType::ParalysisDef, 1)));
	unitList.push_back(Ingredient("生命鲈鱼", 41, 4, 0, IngredientType::Fish, "能恢复大量体力的稀有鱼类"));
	unitList.push_back(Ingredient("大剑鲈鱼", 42, 2, 30, IngredientType::Fish, "能提升攻击力的强力鱼类", Effect(EffectType::Attack, 1)));
	unitList.push_back(Ingredient("速速鲈鱼", 43, 1, 30, IngredientType::Fish, "能让移动更快的鱼类", Effect(EffectType::Speed, 1)));
	unitList.push_back(Ingredient("潜行鳟鱼", 44, 1, 60, IngredientType::Fish, "能让行动更安静的鱼类", Effect(EffectType::Sneaky, 1)));

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

	// 昆虫/蜥蜴
	unitList.push_back(Ingredient("精力蚱蜢", 57, 0, 0, IngredientType::Insect, "能恢复精力的昆虫", Effect(EffectType::Health, 1)));
	unitList.push_back(Ingredient("冷静蜥蜴", 58, 0, 60, IngredientType::Insect, "能提供抗热效果的蜥蜴", Effect(EffectType::FireDef, 1)));
	unitList.push_back(Ingredient("暖暖蜥蜴", 59, 0, 60, IngredientType::Insect, "能提供抗寒效果的蜥蜴", Effect(EffectType::ColdDef, 1)));
	unitList.push_back(Ingredient("酥麻蜥蜴", 60, 0, 60, IngredientType::Insect, "能提供电击防护的蜥蜴", Effect(EffectType::ParalysisDef, 1)));
	unitList.push_back(Ingredient("潜行田螺", 61, 0, 60, IngredientType::Insect, "能让行动更安静的田螺", Effect(EffectType::Sneaky, 1)));
	unitList.push_back(Ingredient("大剑螃蟹", 62, 1, 30, IngredientType::Insect, "能提升攻击力的螃蟹", Effect(EffectType::Attack, 1)));
	unitList.push_back(Ingredient("铠甲螃蟹", 63, 1, 30, IngredientType::Insect, "能提升防御力的螃蟹", Effect(EffectType::Defence, 1)));
	unitList.push_back(Ingredient("速速青蛙", 64, 0, 60, IngredientType::Insect, "能让移动更快的青蛙", Effect(EffectType::Speed, 1)));
	InitIngredientMap();
}