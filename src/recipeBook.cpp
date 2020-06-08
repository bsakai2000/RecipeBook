#include <vector>
#include <cstdio>

#include "recipe.hpp"
#include "files.hpp"

#ifndef RECIPE_BOOK
#define RECIPE_BOOK "recipe.json"
#endif

std::vector<std::string> search_by_tag(const std::vector<Recipe> &recipes, const std::vector<std::string> &tag)
{
	std::vector<std::string> results;
	for(size_t i = 0; i < recipes.size(); ++i)
	{
		if(recipes[i].has_tag(tag))
		{
			results.push_back(recipes[i].get_name());
		}
	}
	return results;
}

std::vector<std::string> search_by_ingredient(const std::vector<Recipe> &recipes, const std::vector<std::string> &ingredient)
{
	std::vector<std::string> results;
	for(size_t i = 0; i < recipes.size(); ++i)
	{
		if(recipes[i].has_ingredient(ingredient))
		{
			results.push_back(recipes[i].get_name());
		}
	}
	return results;
}

void usage(char* filename)
{
	fprintf(stderr, "Usage:\n");
	fprintf(stderr, "%s search [tag|ingredient] term1 [term2 ...]\n", filename);
	fprintf(stderr, "%s recipe list\n", filename);
	fprintf(stderr, "%s recipe [ingredients|instructions|all] recipename\n", filename);
}

int main(int argc, char* argv[])
{
	std::vector<std::string> args;
	args.assign(argv + 1, argv + argc);

	std::vector<Recipe> recipes = read_recipes(RECIPE_BOOK);
	if(args[0] == "search")
	{
		std::vector<std::string> search_terms(args.begin() + 2, args.end());
		std::vector<std::string> search_results;
		if(args[1] == "tag")
		{
			search_results = search_by_tag(recipes, search_terms);
		}
		else if(args[1] == "ingredient")
		{
			search_results = search_by_ingredient(recipes, search_terms);
		}
		else
		{
			usage(argv[0]);
			return 1;
		}

		if(search_results.size() == 0)
		{
			fprintf(stderr, "No results found\n");
			return 1;
		}

		for(size_t i = 0; i < search_results.size(); ++i)
		{
			printf("%s\n", search_results[i].c_str());
		}

	}
	if(args[0] == "recipe")
	{
		std::string recipe_name = "";
		for(size_t i = 2; i < args.size(); ++i)
		{
			recipe_name += args[i] + " ";
		}
		recipe_name.pop_back();

		Recipe* recipe = NULL;
		for(size_t i = 0; i < recipes.size(); ++i)
		{
			if(recipes[i].get_name() == recipe_name)
			{
				recipe = &(recipes[i]);
				break;
			}
		}

		if(recipe == NULL)
		{
			fprintf(stderr, "No recipe called %s\n", recipe_name.c_str());
			return 1;
		}

		if(args[1] == "all")
		{
			printf("Ingredients:\n");
		}

		if(args[1] == "ingredients" || args[1] == "all")
		{
			std::vector<Ingredient> ingredients = recipe->get_ingredients();
			int max_size = 0;
			for(size_t i = 0; i < ingredients.size(); ++i)
			{
				if((int) ingredients[i].quantity.size() > max_size)
				{
					max_size = (int) ingredients[i].quantity.size();
				}
			}
			for(size_t i = 0; i < ingredients.size(); ++i)
			{
				printf("%*s  %s\n", max_size, ingredients[i].quantity.c_str(), ingredients[i].name.c_str());
			}
		}

		if(args[1] == "all")
		{
			printf("\nInstructions:\n");
		}

		if(args[1] == "instructions" || args[1] == "all")
		{
			std::vector<std::string> instructions = recipe->get_instructions();
			for(size_t i = 0; i < instructions.size(); ++i)
			{
				printf("%3ld. %s\n", i, instructions[i].c_str());
			}
		}
	}

	return 0;
}
