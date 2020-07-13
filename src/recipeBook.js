// Lists summaries of the recipes with required_tags from text
function list_recipes(text, required_tags)
{
	// Read the recipe book
	var recipe_book = JSON.parse(text);
	for(recipe of recipe_book)
	{
		// Check that this recipe has each tag
		var has_tags = true;
		for(tag of required_tags)
		{
			if(!(recipe.tags.includes(tag)))
			{
				has_tags = false;
			}
		}
		if(!has_tags)
		{
			continue;
		}
		// Create the div for the recipe
		var recipe_element = document.createElement("div");
		var recipe_name = document.createElement("h2");
		recipe_name.innerHTML = "<a href='?recipe=" + recipe.name + "'>" + recipe.name + "</a>";
		recipe_element.appendChild(recipe_name);

		// Create the list of tags
		var tag_list = document.createElement("ul");
		for(tag of recipe.tags)
		{
			var tag_bullet = document.createElement("li");
			tag_bullet.innerHTML = "<a href='?tag=" + tag + "'>" + tag + "</a>";
			tag_list.appendChild(tag_bullet);
		}
		recipe_element.appendChild(tag_list);

		// Add this recipe to the global recipe div
		document.getElementById("recipes").appendChild(recipe_element);
	}
}

// Print a single recipe with name name from text
function print_recipe(text, name)
{
	// Read the recipe book
	var recipe_book = JSON.parse(text);

	// Find the correct recipe
	for(recipe of recipe_book)
	{
		if(recipe.name == name)
		{
			// Create the div for the name of the recipe
			var recipe_element = document.createElement("div");
			var recipe_name = document.createElement("h3");
			recipe_name.innerHTML = "<a href='?recipe=" + recipe.name + "'>" + recipe.name + "</a>";
			recipe_element.appendChild(recipe_name);

			// Create the ingredients table
			var ingredient_header = document.createElement("h3");
			ingredient_header.innerHTML = "Ingredients";
			recipe_element.appendChild(ingredient_header);

			var ingredient_table = document.createElement("table");
			for(ingredient of recipe.ingredients)
			{
				// Create a row which has a quantity in one
				// cell and the name of the ingredient in the
				// other
				var ingredient_row = document.createElement("tr");
				var ingredient_amount = document.createElement("td");
				var ingredient_name = document.createElement("td");
				ingredient_amount.innerHTML = ingredient.quantity;
				ingredient_name.innerHTML = ingredient.name;
				ingredient_row.appendChild(ingredient_amount);
				ingredient_row.appendChild(ingredient_name);
				ingredient_table.appendChild(ingredient_row);
			}
			recipe_element.appendChild(ingredient_table);

			// Create the Instructions list
			var instruction_header = document.createElement("h3");
			instruction_header.innerHTML = "Instructions";
			recipe_element.appendChild(instruction_header);

			var instruction_list = document.createElement("ol");
			for(instruction of recipe.instructions)
			{
				var instruction_bullet = document.createElement("li");
				instruction_bullet.innerHTML = instruction;
				instruction_list.appendChild(instruction_bullet);
			}
			recipe_element.appendChild(instruction_list);

			// Create the tags list
			var tag_header = document.createElement("h3");
			tag_header.innerHTML = "Tags";
			recipe_element.appendChild(tag_header);

			var tag_list = document.createElement("ul");
			for(tag of recipe.tags)
			{
				var tag_bullet = document.createElement("li");
				tag_bullet.innerHTML = "<a href='?tag=" + tag + "'>" + tag + "</a>";
				tag_list.appendChild(tag_bullet);
			}
			recipe_element.appendChild(tag_list);

			// Add this recipe to the global div
			document.getElementById("recipes").appendChild(recipe_element);
			break;
		}
	}
}

// Returns the name of the recipe if we're displaying a single recipe,
// otherwise return null
function single_recipe()
{
	// Remove the ?
	var param_string = window.location.search.substr(1);
	// Return the name of the recipe
	var params = new URLSearchParams(param_string);
	for(pair of params.entries())
	{
		if(pair[0] == "recipe")
		{
			return pair[1];
		}
	}
	return null;
}

// Returns the list of tags from the URL parameters
function get_tags()
{
	// Remove the ?
	var param_string = window.location.search.substr(1);
	// Return comma-delineated tags as an array
	var params = new URLSearchParams(param_string);
	for(pair of params.entries())
	{
		if(pair[0] == "tag")
		{
			return pair[1].split(",");
		}
	}
	return [];
}

// Read recipes.json, and take the appropriate action
var request = new XMLHttpRequest();
request.onreadystatechange = function()
{
	if(request.readyState === XMLHttpRequest.DONE && (status == 200 || status == 0))
	{
		// If we have a single recipe, display it in full. Otherwise,
		// display a summary of all recipes
		var recipe_name = single_recipe();
		if(recipe_name != null)
		{
			print_recipe(request.responseText, recipe_name);
		}
		else
		{
			list_recipes(request.responseText, get_tags());
		}
	}
}
request.open("GET", "recipes.json", true);
request.send();
