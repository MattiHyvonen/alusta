#creates the static library to lib/libalusta.a
#creates a test program to ./test

#dependencies: 
#   gtkmm 3.0 
#   glew


#TODO:
# .o files to a separate folder, now they are in src/

CFLAGS = `pkg-config gtkmm-3.0 glew --cflags` -std=c++14
LFLAGS = `pkg-config gtkmm-3.0 glew --libs`
OBJ =	src/mesh.o\
	src/shaders.o\
	src/mainApp.o

all: clean mkdirs alusta test

clean:
	rm -Rf lib src/*.o test

mkdirs:
	mkdir -p lib

%.o: %.cpp
	g++ -c $^ -o $@ $(CFLAGS)

alusta: $(OBJ)
	ar rcs lib/libalusta.a $^

test:
	g++ src/test.cpp -Llib -lalusta $(CFLAGS) $(LFLAGS) -o test 
