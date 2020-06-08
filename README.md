# RecipeBook
Read and explore JSON-encoded recipes

Usage is as follows:
```
./recipeBook search [tag|ingredient] term1 [term2 ...]
./recipeBook recipe list
./recipeBook recipe add
./recipeBook recipe [ingredients|instructions|all] recipename

```
The search allows searching by tag or ingredient, so to find all recipes that use chicken one would say `./recipeBook search ingredient Chicken`

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
