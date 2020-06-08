# RecipeBook
Read and explore JSON-encoded recipes

Usage is as follows:
```
./recipeBook search [tag|ingredient] term1 [term2 ...]
./recipeBook recipe list
./recipeBook recipe add
./recipeBook recipe [ingredients|instructions|all] recipename

```
Tags are used to categorize recipes. The search allows searching by tag or ingredient, so to find all recipes that use chicken one would say `./recipeBook search ingredient Chicken`

The JSON recipe book is encoded like
```
[
	{
		"name":"recipename",
		"ingredients":
		[
			{
				"name": "ingredientname",
				"quantity": 'ingredientquantity"
			}
		],
		"instructions":
		[
			"step 1",
			"step 2"
		],
		"tags":
		[
			"tag1",
			"tag2"
		]
	}
]
```

Example output
```
$ ./recipeBook recipe all Honey Sriracha Chicken
Ingredients:
      3-4 breasts  Chicken
  1/3 cup; 2 tbsp  Corn Starch
    1 cup; 2 tbsp  Water
         2-3 tbsp  Sriracha
           5 tbsp  Soy Sauce
           1 tbsp  Garlic
          1/4 cup  Sugar
         2-3 tbsp  Honey
         To taste  Red Pepper Flakes

Instructions:
  0. Combine water, sriracha, soy sauce, garlic, sugar, and honey in a saucepan, and bring to boil
  1. Whisk together 2 tbsp cornstarch and 2 tbsp water until dissolved, and add to saucepan. Reduce to low heat
  2. Dice chicken and coat in cornstarch
  3. Heat oil in a skillet, and sautee coated chicken
  4. Combine chicken and sauce, and add red peppers to taste
```

Files:
 - files.cpp, files.hpp: Utilities for reading and writing our JSON recipe book
 - ingredient.cpp, ingredient.hpp: The Ingredient class, holding a name and a quantity
 - recipeBook.cpp: The main that provides a way to interact with our recipe book JSON file
 - recipe.cpp, recipe.hpp: The Recipe class that represents one recipe as a name, list of ingredients, list of steps, and list of tags
 - recipes.json: A sample recipe book
