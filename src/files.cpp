#include "files.hpp"

std::vector<Recipe> read_recipes(const std::string &file_name)
{
	const char* c_file_name = file_name.c_str();

	FILE* file = fopen(c_file_name, "r");
	if(!file)
	{
		fprintf(stderr, "Could not open %s\n", c_file_name);
		exit(1);
	}

	fseek(file, 0, SEEK_END);
	size_t file_size = ftell(file);
	rewind(file);

	char* file_buffer = (char*) calloc(file_size + 1, 1);
	if(fread(file_buffer, 1, file_size, file) != file_size)
	{
		fprintf(stderr, "Read wrong number of bytes from %s\n", c_file_name);
		exit(1);
	}
	fclose(file);

	Json::CharReaderBuilder builder;
	builder["collectComments"] = false;
	Json::CharReader* reader = builder.newCharReader();
	Json::Value recipes_tree;
	std::string errs;
	if(!reader->parse(file_buffer, file_buffer + file_size, &recipes_tree, &errs))
	{
		fprintf(stderr, "Failed to parse tree!\n");
		exit(1);
	}

	std::vector<Recipe> recipes; 
	for(Json::ValueConstIterator it = recipes_tree.begin(); it != recipes_tree.end(); ++it)
	{
		const Json::Value recipe_name = (*it)["name"];
		const Json::Value recipe_ingredients = (*it)["ingredients"];
		std::vector<Ingredient> ingredients;
		for(Json::ValueConstIterator ingredient_it = recipe_ingredients.begin(); ingredient_it != recipe_ingredients.end(); ++ingredient_it)
		{
			ingredients.push_back(Ingredient((*ingredient_it)["name"].asString(), (*ingredient_it)["quantity"].asString()));
		}
		const Json::Value recipe_instructions = (*it)["instructions"];
		std::vector<std::string> instructions;
		for(Json::ValueConstIterator instruction_it = recipe_instructions.begin(); instruction_it != recipe_instructions.end(); ++instruction_it)
		{
			instructions.push_back(instruction_it->asString());
		}
		const Json::Value recipe_tags = (*it)["tags"];
		std::vector<std::string> tags;
		for(Json::ValueConstIterator tag_it = recipe_tags.begin(); tag_it != recipe_tags.end(); ++tag_it)
		{
			tags.push_back(tag_it->asString());
		}
		recipes.push_back(Recipe(recipe_name.asString(), ingredients, tags, instructions));
	}

	free(file_buffer);
	delete reader;
	return recipes;
}
