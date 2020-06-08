#include "ingredient.hpp"

Ingredient::Ingredient(const std::string &name, const std::string &quantity)
{
	this->name = name;
	this->quantity = quantity;
}

bool Ingredient::operator==(const Ingredient &ingredient)
{
	return (this->name == ingredient.name) && (this->quantity == ingredient.quantity);
}
