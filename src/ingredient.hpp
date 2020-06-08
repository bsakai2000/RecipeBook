#include <string>

class Ingredient
{
	public:
		Ingredient(const std::string &name, const std::string &quantity);

		bool operator==(const Ingredient &ingredient);
		
		std::string name;
		std::string quantity;
};

