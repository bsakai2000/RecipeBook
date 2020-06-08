#include <vector>
#include <cstdio>
#include <iostream>

#include "recipe.hpp"
#include "files.hpp"

// The name of the file where recipes are stored
#ifndef RECIPE_BOOK
#define RECIPE_BOOK "recipes.json"
#endif

// Get the list of recipe names that have all of these tags
std::vector<std::string> search_by_tag(const std::vector<Recipe> &recipes, const std::vector<std::string> &tag)
{
	std::vector<std::string> results;
	// Loop through each recipe and check if it has all the tags
	for(size_t i = 0; i < recipes.size(); ++i)
	{
		if(recipes[i].has_tag(tag))
		{
			results.push_back(recipes[i].get_name());
		}
	}
	return results;
}

// Get the list of recipe names that have all of these ingredients
std::vector<std::string> search_by_ingredient(const std::vector<Recipe> &recipes, const std::vector<std::string> &ingredient)
{
	std::vector<std::string> results;
	// Loop through each recipe and check if it has all the ingredients
	for(size_t i = 0; i < recipes.size(); ++i)
	{
		if(recipes[i].has_ingredient(ingredient))
		{
			results.push_back(recipes[i].get_name());
		}
	}
	return results;
}

// Create a new recipe
Recipe add_recipe()
{
	// Ask for the recipe name
	printf("Recipe Name:\n");
	std::string recipe_name;
	getline(std::cin, recipe_name);
	
	// Ask for each ingredient
	printf("Please input ingredients one at a time\n");
	printf("Leave name field empty to move on\n");
	std::vector<Ingredient> ingredients;
	while(1)
	{
		// Get the ingredient name
		printf("Ingredient name:\n");
		std::string ingredient_name;
		getline(std::cin, ingredient_name);

		// Stop collecting ingredients when name is empty
		if(ingredient_name == "")
		{
			break;
		}

		// Get the ingredient quantity
		printf("Ingredient quantity:\n");
		std::string ingredient_quantity;
		getline(std::cin, ingredient_quantity);

		// Add this ingredient to our list
		ingredients.push_back(Ingredient(ingredient_name, ingredient_quantity));
	}
	
	// Ask for instructions in order
	printf("Please input instructions one at a time\n");
	printf("Leave field empty to move on\n");
	std::vector<std::string> steps;
	int i = 0;
	while(++i)
	{
		// Get the step
		printf("Step %d:\n", i);
		std::string step;
		getline(std::cin, step);

		// If the step is empty, stop collecting the steps
		if(step == "")
		{
			break;
		}

		// Add this step to our list
		steps.push_back(step);
	}

	// Ask for tags
	printf("Please input tags one at a time\n");
	printf("Leave field empty to finish\n");
	std::vector<std::string> tags;
	while(1)
	{
		// Get the tag
		printf("Tag:\n");
		std::string tag;
		getline(std::cin, tag);

		// If the tag is empty, stop collecting tags
		if(tag == "")
		{
			break;
		}

		// Add this tag to our list
		tags.push_back(tag);
	}

	// Create a recipe with the required qualities
	return Recipe(recipe_name, ingredients, tags, steps);
}

// Print usage information
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
	// We need at least 2 arguments
	if(argc < 3)
	{
		usage(argv[0]);
		return 1;
	}

	// Collect arguments in args
	std::vector<std::string> args;
	args.assign(argv + 1, argv + argc);

	// Put all the recipes in our vector
	std::vector<Recipe> recipes = read_recipes(RECIPE_BOOK);
	if(args[0] == "search")
	{
		// We need a search term and method
		if(args.size() < 3)
		{
			usage(argv[0]);
			return 1;
		}

		// Collect search terms
		std::vector<std::string> search_terms(args.begin() + 2, args.end());
		std::vector<std::string> search_results;
		// Get the results in search_results
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

		// If we don't have any results, give up
		if(search_results.size() == 0)
		{
			fprintf(stderr, "No results found\n");
			return 1;
		}

		// If we have results, print them
		for(size_t i = 0; i < search_results.size(); ++i)
		{
			printf("%s\n", search_results[i].c_str());
		}

	}
	else if(args[0] == "recipe")
	{
		// List all recipe names
		if(args[1] == "list")
		{
			for(size_t i = 0; i < recipes.size(); ++i)
			{
				printf("%s\n", recipes[i].get_name().c_str());
			}
			return 0;
		}
		// Create a new recipe and write back to disk
		if(args[1] == "add")
		{
			Recipe new_recipe = add_recipe();
			recipes.push_back(new_recipe);
			write_recipes(RECIPE_BOOK, recipes);
			return 0;
		}

		// If this is a bad argument list, give up
		if((args.size() < 3) || (args[1] != "all" && args[1] != "ingredients" && args[1] != "instructions"))
		{
			usage(argv[0]);
			return 1;
		}

		// Create the recipe name from args
		std::string recipe_name = "";
		for(size_t i = 2; i < args.size(); ++i)
		{
			recipe_name += args[i] + " ";
		}
		recipe_name.pop_back();

		// Find the recipe named recipe_name
		Recipe* recipe = NULL;
		for(size_t i = 0; i < recipes.size(); ++i)
		{
			if(recipes[i].get_name() == recipe_name)
			{
				recipe = &(recipes[i]);
				break;
			}
		}

		// If we don't have a recipe with that name, give up
		if(recipe == NULL)
		{
			fprintf(stderr, "No recipe called %s\n", recipe_name.c_str());
			return 1;
		}

		// Target "all" requires labelling sections
		if(args[1] == "all")
		{
			printf("Ingredients:\n");
		}

		if(args[1] == "ingredients" || args[1] == "all")
		{
			std::vector<Ingredient> ingredients = recipe->get_ingredients();
			// Get the maximum size of the quantity
			int max_size = 0;
			for(size_t i = 0; i < ingredients.size(); ++i)
			{
				if((int) ingredients[i].quantity.size() > max_size)
				{
					max_size = (int) ingredients[i].quantity.size();
				}
			}
			// Print each ingredient
			for(size_t i = 0; i < ingredients.size(); ++i)
			{
				printf("%*s  %s\n", max_size + 2, ingredients[i].quantity.c_str(), ingredients[i].name.c_str());
			}
		}

		// Target "all" requires labelling sections
		if(args[1] == "all")
		{
			printf("\nInstructions:\n");
		}

		if(args[1] == "instructions" || args[1] == "all")
		{
			// Print each instruction
			std::vector<std::string> instructions = recipe->get_instructions();
			for(size_t i = 0; i < instructions.size(); ++i)
			{
				printf("%3ld. %s\n", i, instructions[i].c_str());
			}
		}
	}
	else
	{
		// If we got bad arguments, print usage
		usage(argv[0]);
		return 1;
	}

	return 0;
}
