#ifndef FILES_HPP
#define FILES_HPP

#include <string>
#include <cstdio>
#include <vector>
#include <json/reader.h>

#include "ingredient.hpp"
#include "recipe.hpp"

std::vector<Recipe> read_recipes(const std::string &file_name);

#endif
