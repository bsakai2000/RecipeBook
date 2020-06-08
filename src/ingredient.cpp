#include "ingredient.hpp"

Ingredient::Ingredient(const std::string &name, const std::string &quantity)
{
	this->name = name;
	this->quantity = quantity;
}

bool Ingredient::operator==(const Ingredient &ingredient)
{
	// Two ingredients are equal if the name matches
	return this->name == ingredient.name;
}
