CXXFLAGS = -g -Wall -Werror
CXXFLAGS += `pkg-config --cflags jsoncpp`
LXXFLAGS = `pkg-config --libs jsoncpp`
CXX = g++

.PHONY: clean

recipeBook: recipeBook.o recipe.o ingredient.o files.o
	$(CXX) recipeBook.o recipe.o ingredient.o files.o -o recipeBook $(LXXFLAGS)

recipeBook.o: recipeBook.cpp
	$(CXX) recipeBook.cpp -c -o recipeBook.o $(CXXFLAGS)

recipe.o: recipe.cpp recipe.hpp ingredient.hpp
	$(CXX) recipe.cpp -c -o recipe.o $(CXXFLAGS)

ingredient.o: ingredient.cpp ingredient.hpp
	$(CXX) ingredient.cpp -c -o ingredient.o $(CXXFLAGS)

files.o: files.cpp files.hpp recipe.hpp ingredient.hpp
	$(CXX) files.cpp -c -o files.o $(CXXFLAGS)

clean:
	rm -f *.o recipeBook
