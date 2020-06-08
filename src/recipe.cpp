#include "recipe.hpp"

Recipe::Recipe(const std::string &name, const std::vector<Ingredient> &ingredients, const std::vector<std::string> &tags, const std::vector<std::string> &instructions)
{
	this->name = name;
	this->ingredients = ingredients;
	this->tags = tags;
	this->instructions = instructions;
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

std::vector<std::string> Recipe::get_instructions()
{
	return this->instructions;
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

bool Recipe::has_tag(const std::string &tag)
{
	return (std::find(this->tags.begin(), this->tags.end(), tag) != tags.end());
}

bool Recipe::has_ingredient(const std::string &ingredient)
{
	for(size_t i = 0; i < ingredients.size(); ++i)
	{
		if(ingredients[i].name == ingredient)
		{
			return true;
		}
	}
	return false;
}
