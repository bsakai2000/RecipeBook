CFLAGS = -g -Wall -Werror
CFLAGS += `pkg-config --cflags jsoncpp`
LFLAGS = `pkg-config --libs jsoncpp`
CXX = g++

.PHONY: clean

recipeBook: recipeBook.o recipe.o ingredient.o files.o
	$(CXX) recipeBook.o recipe.o ingredient.o files.o -o recipeBook $(LFLAGS)

recipeBook.o: recipeBook.cpp
	$(CXX) recipeBook.cpp -c -o recipeBook.o $(CFLAGS)

recipe.o: recipe.cpp recipe.hpp ingredient.hpp
	$(CXX) recipe.cpp -c -o recipe.o $(CFLAGS)

ingredient.o: ingredient.cpp ingredient.hpp
	$(CXX) ingredient.cpp -c -o ingredient.o $(CFLAGS)

files.o: files.cpp files.hpp recipe.hpp ingredient.hpp
	$(CXX) files.cpp -c -o files.o $(CFLAGS)

clean:
	rm -f *.o recipeBook
