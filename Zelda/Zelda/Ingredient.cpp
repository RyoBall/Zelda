#include "Ingredient.h"
using namespace std;
std::string Effect::GetName()
{
	{
		auto it = EffectBaseName.find(effectType);
		if (it == EffectBaseName.end())
			return "";

		std::string name = it->second;

		if (level > 0) {
			name += " Lv.";
			name += std::to_string(level);
		}

		if (duration > 0) {
			int totalSeconds = duration;
			int minutes = totalSeconds / 60;
			int seconds = totalSeconds % 60;

			name += " ";

			if (minutes > 0) {
				name += std::to_string(minutes);
				name += "·Ö";
			}

			if (seconds > 0) {
				name += std::to_string(seconds);
				name += "Ãë";
			}
		}
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

int Ingredient::GetID()
{
	return ID;
}

bool Ingredient::operator==(const Ingredient& otherIngredient)
{
	return ID == otherIngredient.ID;
}
