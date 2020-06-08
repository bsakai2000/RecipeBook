#include "recipe.hpp"

Recipe::Recipe(const std::string &name, const std::vector<Ingredient> &ingredients, const std::vector<std::string> &tags)
{
	this->name = name;
	this->ingredients = ingredients;
	this->tags = tags;
}

Recipe::~Recipe()
{
}

std::string Recipe::get_name()
{
	return this->name;
}

std::vector<Ingredient> Recipe::get_ingredients()
{
	return this->ingredients;
}

std::vector<std::string> Recipe::get_tags()
{
	return this->tags;
}

void Recipe::add_tag(const std::string &tag)
{
	if(std::find(this->tags.begin(), this->tags.end(), tag) != this->tags.end())
	{
		this->tags.push_back(tag);
	}
}

void Recipe::add_ingredient(const Ingredient &ingredient)
{
	if(std::find(this->ingredients.begin(), this->ingredients.end(), ingredient) != this->ingredients.end())
	{
		this->ingredients.push_back(ingredient);
	}
}
