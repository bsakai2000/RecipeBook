#include "recipe.hpp"

Recipe::Recipe(const std::string &name, const std::vector<Ingredient> &ingredients, const std::vector<std::string> &tags, const std::vector<std::string> &instructions, const std::vector<std::string> &notes)
{
	this->name = name;
	this->ingredients = ingredients;
	this->tags = tags;
	this->instructions = instructions;
	this->notes = notes;
}

Recipe::~Recipe()
{
}

std::string Recipe::get_name() const
{
	return this->name;
}

std::vector<Ingredient> Recipe::get_ingredients() const
{
	return this->ingredients;
}

std::vector<std::string> Recipe::get_tags() const
{
	return this->tags;
}

std::vector<std::string> Recipe::get_instructions() const
{
	return this->instructions;
}

std::vector<std::string> Recipe::get_notes() const
{
	return this->notes;
}

bool Recipe::has_tag(const std::string &tag) const
{
	// Returns true if the tag is in our list
	return (std::find(this->tags.begin(), this->tags.end(), tag) != this->tags.end());
}

bool Recipe::has_tag(const std::vector<std::string> &search_tags) const
{
	// Check each tag to see if we have it
	for(size_t i = 0; i < search_tags.size(); ++i)
	{
		if(!this->has_tag(search_tags[i]))
		{
			return false;
		}
	}
	return true;
}

bool Recipe::has_ingredient(const std::string &ingredient) const
{
	// Returns true if there is an ingredient with this name in the recipe
	for(size_t i = 0; i < ingredients.size(); ++i)
	{
		if(ingredients[i].name == ingredient)
		{
			return true;
		}
	}
	return false;
}

bool Recipe::has_ingredient(const std::vector<std::string> &search_ingredients) const
{
	// check each ingredient to see if we have it
	for(size_t i = 0; i < search_ingredients.size(); ++i)
	{
		if(!this->has_ingredient(search_ingredients[i]))
		{
			return false;
		}
	}
	return true;
}

bool Recipe::operator<(const Recipe &recipe)
{
	return this->name < recipe.name;
}
