#include <vector>
#include <cstdio>
#include <iostream>

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

Recipe add_recipe()
{
	printf("Recipe Name:\n");
	std::string recipe_name;
	getline(std::cin, recipe_name);
	
	printf("Please input ingredients one at a time\n");
	printf("Leave name field empty to move on\n");
	std::vector<Ingredient> ingredients;
	while(1)
	{
		printf("Ingredient name:\n");
		std::string ingredient_name;
		getline(std::cin, ingredient_name);
		if(ingredient_name == "")
		{
			break;
		}
		printf("Ingredient quantity:\n");
		std::string ingredient_quantity;
		getline(std::cin, ingredient_quantity);
		ingredients.push_back(Ingredient(ingredient_name, ingredient_quantity));
	}
	
	printf("Please input ingredients one at a time\n");
	printf("Leave field empty to move on\n");
	std::vector<std::string> steps;
	int i = 0;
	while(++i)
	{
		printf("Step %d:\n", i);
		std::string step;
		getline(std::cin, step);
		if(step == "")
		{
			break;
		}
		steps.push_back(step);
	}

	printf("Please input tags one at a time\n");
	printf("Leave field empty to finish\n");
	std::vector<std::string> tags;
	while(1)
	{
		printf("Tag:\n");
		std::string tag;
		getline(std::cin, tag);
		if(tag == "")
		{
			break;
		}
		tags.push_back(tag);
	}
	return Recipe(recipe_name, ingredients, tags, steps);
}

void usage(char* filename)
{
	fprintf(stderr, "Usage:\n");
	fprintf(stderr, "%s search [tag|ingredient] term1 [term2 ...]\n", filename);
	fprintf(stderr, "%s recipe list\n", filename);
	fprintf(stderr, "%s recipe add\n", filename);
	fprintf(stderr, "%s recipe [ingredients|instructions|all] recipename\n", filename);
}

int main(int argc, char* argv[])
{

	if(argc < 3)
	{
		usage(argv[0]);
		return 1;
	}

	std::vector<std::string> args;
	args.assign(argv + 1, argv + argc);

	std::vector<Recipe> recipes = read_recipes(RECIPE_BOOK);
	if(args[0] == "search")
	{
		if(argc < 4)
		{
			usage(argv[0]);
			return 1;
		}

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
	else if(args[0] == "recipe")
	{
		if(args[1] == "list")
		{
			for(size_t i = 0; i < recipes.size(); ++i)
			{
				printf("%s\n", recipes[i].get_name().c_str());
			}
			return 0;
		}
		if(args[1] == "add")
		{
			Recipe new_recipe = add_recipe();
			recipes.push_back(new_recipe);
			write_recipes(RECIPE_BOOK, recipes);
			return 0;
		}

		if(argc < 4)
		{
			usage(argv[0]);
			return 1;
		}

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
				printf("%*s  %s\n", max_size + 2, ingredients[i].quantity.c_str(), ingredients[i].name.c_str());
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
	else
	{
		usage(argv[0]);
		return 1;
	}

	return 0;
}
