#include <vector>
#include <string>
#include <algorithm>

#include "ingredient.hpp"

class Recipe
{
	public:
		Recipe(const std::string &name, const std::vector<Ingredient> &ingredients, const std::vector<std::string> &tags);
		~Recipe();

		std::string get_name();
		std::vector<Ingredient> get_ingredients();
		std::vector<std::string> get_tags();

		void add_tag(const std::string &tag);
		void add_ingredient(const Ingredient &ingredient);

	private:
		std::string name;
		std::vector<Ingredient> ingredients;
		std::vector<std::string> tags;
};
