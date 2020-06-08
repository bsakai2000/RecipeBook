#ifndef INGREDIENT_HPP
#define INGREDIENT_HPP

#include <string>

class Ingredient
{
	public:
		Ingredient(const std::string &name, const std::string &quantity);

		// Two ingredients are equal if they have the same name
		bool operator==(const Ingredient &ingredient);
		
		std::string name;
		std::string quantity;
};

#endif
