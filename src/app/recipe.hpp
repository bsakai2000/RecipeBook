#ifndef RECIPE_HPP
#define RECIPE_HPP

#include <vector>
#include <string>
#include <algorithm>

#include "ingredient.hpp"

class Recipe
{
	public:
		Recipe(const std::string &name, const std::vector<Ingredient> &ingredients, const std::vector<std::string> &tags, const std::vector<std::string> &instructions);
		~Recipe();

		std::string get_name() const;
		std::vector<Ingredient> get_ingredients() const;
		std::vector<std::string> get_tags() const;
		std::vector<std::string> get_instructions() const;

		// Returns true if the recipe has this tag
		bool has_tag(const std::string &tag) const;
		// Returns true if the recipe has all of these tags
		bool has_tag(const std::vector<std::string> &search_tags) const;
		// Returns true if the recipe has this ingredient
		bool has_ingredient(const std::string &ingredient) const;
		// Returns true if the recipe has all of these ingredients
		bool has_ingredient(const std::vector<std::string> &ingredients) const;

		// Recipe comparison is done by name
		bool operator<(const Recipe &recipe);

	private:
		std::string name;
		std::vector<Ingredient> ingredients;
		std::vector<std::string> tags;
		std::vector<std::string> instructions;
};

#endif
