CXXFLAGS = -Wall -Werror -O2
CXXFLAGS += `pkg-config --cflags jsoncpp`
LDFLAGS = `pkg-config --libs jsoncpp`
CC = g++

recipeBook: recipeBook.o recipe.o ingredient.o files.o

files.o: files.cpp files.hpp ingredient.hpp recipe.hpp

ingredient.o: ingredient.cpp ingredient.hpp

recipe.o: recipe.cpp recipe.hpp

recipeBook.o: recipeBook.cpp recipe.hpp files.hpp

clean:
	rm -f *.o recipeBook
