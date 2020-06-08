#include <vector>
#include <cstdio>

#include "recipe.hpp"
#include "files.hpp"

int main(int argc, char* argv[])
{
	std::vector<Recipe> read = read_recipes("recipe.json");
	printf("Recipes:\n");
	for(size_t i = 0; i < read.size(); ++i)
	{
		printf("\t%s\n", read[i].get_name().c_str());
		printf("\t\tIngredients:\n");
		std::vector<Ingredient> ingredients = read[i].get_ingredients();
		for(size_t j = 0; j < ingredients.size(); ++j)
		{
			printf("\t\t\t%s\t%s\n", ingredients[j].quantity.c_str(), ingredients[j].name.c_str());
		}
		printf("\t\tInstructions:\n");
		std::vector<std::string> instructions = read[i].get_instructions();
		for(size_t j = 0; j < instructions.size(); ++j)
		{
			printf("\t\t\t%s\n", instructions[j].c_str());
		}
		printf("\t\tTags:\n");
		std::vector<std::string> tags = read[i].get_tags();
		for(size_t j = 0; j < tags.size(); ++j)
		{
			printf("\t\t\t%s\n", tags[j].c_str());
		}

	}

	return 0;
}
