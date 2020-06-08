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

		std::string get_name();
		std::vector<Ingredient> get_ingredients();
		std::vector<std::string> get_tags();
		std::vector<std::string> get_instructions();

		void add_tag(const std::string &tag);
		void add_ingredient(const Ingredient &ingredient);
		void add_instruction(const std::string &instruction);

		bool has_tag(const std::string &tag);
		bool has_ingredient(const std::string &ingredient);

	private:
		std::string name;
		std::vector<Ingredient> ingredients;
		std::vector<std::string> tags;
		std::vector<std::string> instructions;
};

#endif
