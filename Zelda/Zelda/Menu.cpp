#include "Menu.h"
#include "AllStruct.h"
std::string RecipeKey::Cook(const std::vector<int>& ingredientIDs)
{
	if (ingredientIDs.empty())
	{
		return "";
	}
	std::vector<int> ids = ingredientIDs;
	SortIngredientIDs(ids);

	std::string  key;
	for (int i = 0; i < ids.size(); ++i)
	{
		key += std::to_string(ids[i]);
		if (i + 1 < ids.size())
			key += "_";
	}
	return key;
}
