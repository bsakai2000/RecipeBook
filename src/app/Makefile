CXXFLAGS = -Wall -Werror -O2
CXXFLAGS += `pkg-config --cflags jsoncpp`
LDFLAGS = `pkg-config --libs jsoncpp`
CC = g++

recipeBook: recipeBook.o recipe.o ingredient.o files.o

clean:
	rm -f *.o recipeBook
