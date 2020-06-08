#ifndef FILES_HPP
#define FILES_HPP

#include <string>
#include <cstdio>
#include <vector>
#include <json/reader.h>
#include <json/writer.h>

#include "ingredient.hpp"
#include "recipe.hpp"

// Read the JSON in file_name and return a vector of Recipe objects
std::vector<Recipe> read_recipes(const std::string &file_name);
// Write the list of recipes to file_name
void write_recipes(const std::string &file_name, const std::vector<Recipe> &recipes);

#endif
