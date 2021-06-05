#include "files.hpp"

std::vector<Recipe> read_recipes(const std::string &file_name)
{
	// Open the file
	const char* c_file_name = file_name.c_str();
	FILE* file = fopen(c_file_name, "r");
	if(!file)
	{
		fprintf(stderr, "Could not open %s\n", c_file_name);
		exit(1);
	}

	// Get the size of the file
	fseek(file, 0, SEEK_END);
	size_t file_size = ftell(file);
	rewind(file);

	// Read the whole file into file_buffer
	char* file_buffer = (char*) calloc(file_size + 1, 1);
	if(fread(file_buffer, 1, file_size, file) != file_size)
	{
		fprintf(stderr, "Read wrong number of bytes from %s\n", c_file_name);
		exit(1);
	}

	// Close the file
	fclose(file);

	// Parse the buffer to create JSON object
	Json::CharReaderBuilder builder;
	builder["collectComments"] = false;
	Json::CharReader* reader = builder.newCharReader();
	Json::Value recipes_tree;
	std::string errs;
	if(!reader->parse(file_buffer, file_buffer + file_size, &recipes_tree, &errs))
	{
		fprintf(stderr, "Failed to parse tree!\n");
		fprintf(stderr, "%s\n", errs.c_str());
		exit(1);
	}

	// Release unused memory
	free(file_buffer);
	delete reader;

	// Put the JSON into our class structure
	std::vector<Recipe> recipes; 
	for(Json::ValueConstIterator it = recipes_tree.begin(); it != recipes_tree.end(); ++it)
	{
		// Get the recipe name
		const Json::Value recipe_name = (*it)["name"];
		
		// Create an Ingredient object for each ingredient in the dish
		const Json::Value recipe_ingredients = (*it)["ingredients"];
		std::vector<Ingredient> ingredients;
		for(Json::ValueConstIterator ingredient_it = recipe_ingredients.begin(); ingredient_it != recipe_ingredients.end(); ++ingredient_it)
		{
			ingredients.push_back(Ingredient((*ingredient_it)["name"].asString(), (*ingredient_it)["quantity"].asString()));
		}

		// Get the list of instructions
		const Json::Value recipe_instructions = (*it)["instructions"];
		std::vector<std::string> instructions;
		for(Json::ValueConstIterator instruction_it = recipe_instructions.begin(); instruction_it != recipe_instructions.end(); ++instruction_it)
		{
			instructions.push_back(instruction_it->asString());
		}

		// Get the list of tags
		const Json::Value recipe_tags = (*it)["tags"];
		std::vector<std::string> tags;
		for(Json::ValueConstIterator tag_it = recipe_tags.begin(); tag_it != recipe_tags.end(); ++tag_it)
		{
			tags.push_back(tag_it->asString());
		}

		// Create our Recipe and add it to the list
		recipes.push_back(Recipe(recipe_name.asString(), ingredients, tags, instructions));
	}

	return recipes;
}

void write_recipes(const std::string &file_name, const std::vector<Recipe> &recipes)
{
	// Create the root array
	Json::Value recipes_tree(Json::arrayValue);
	for(size_t i = 0; i < recipes.size(); ++i)
	{
		Json::Value recipe(Json::objectValue);
		// Get the recipe name
		recipe["name"] = recipes[i].get_name();

		// Get the recipe ingredients
		Json::Value ingredients_tree(Json::arrayValue);
		std::vector<Ingredient> ingredients = recipes[i].get_ingredients();

		// Sort the recipe ingredients
		std::sort(ingredients.begin(), ingredients.end());

		for(size_t j = 0; j < ingredients.size(); ++j)
		{
			Json::Value ingredient(Json::objectValue);
			ingredient["name"] = ingredients[j].name;
			ingredient["quantity"] = ingredients[j].quantity;
			ingredients_tree.append(ingredient);
		}
		recipe["ingredients"] = ingredients_tree;
		
		// Get the recipe instructions
		recipe["instructions"] = Json::Value(Json::arrayValue);
		std::vector<std::string> instructions = recipes[i].get_instructions();
		for(size_t j = 0; j < instructions.size(); ++j)
		{
			recipe["instructions"].append(instructions[j]);
		}

		// Get the recipe tags
		recipe["tags"] = Json::Value(Json::arrayValue);
		std::vector<std::string> tags = recipes[i].get_tags();

		// Sort the recipe tags
		std::sort(tags.begin(), tags.end());

		for(size_t j = 0; j < tags.size(); ++j)
		{
			recipe["tags"].append(tags[j]);
		}

		// Add this recipe to the JSON tree
		recipes_tree.append(recipe);
	}

	// Create our writer 
	Json::StreamWriterBuilder builder;
	Json::StreamWriter* writer = builder.newStreamWriter();

	// Write the JSON tree to output_buffer
	std::ostringstream stream;
	writer->write(recipes_tree, &stream);
	std::string stream_str = stream.str();
	size_t buffer_size = stream_str.size();
	const char* output_buffer = stream_str.c_str();

	// Write the JSON tree to disk
	const char* c_file_name = file_name.c_str();
	FILE* file = fopen(c_file_name, "w");
	if(!file)
	{
		fprintf(stderr, "Could not open %s\n", c_file_name);
		exit(1);
	}

	if(fwrite(output_buffer, 1, buffer_size, file) != buffer_size)
	{
		fprintf(stderr, "Wrote wrong number of bytes to %s\n", c_file_name);
		exit(1);
	}

	// Clean up
	fclose(file);
	delete writer;
}
