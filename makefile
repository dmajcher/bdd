FLAGS = -std=c++14 -lsqlite3 -Wall xml2-config --cflags xml2-config --libs
GCC = FALSE
COMPILATORG=g++-5
COMPILATORC=gcc-5

ifeq ($(GCC),TRUE)
	COMPILATORG=g++
	COMPILATORC=gcc 
endif

links: database.o user.o etablissement.o restaurant.o bar.o hotel.o main.o
	$(COMPILATORG) $(FLAGS) -o $@ database.o user.o etablissement.o restaurant.o bar.o hotel.o main.o

user.o: User.cpp User.hpp
	$(COMPILATORG) $(FLAGS) -c User.cpp -o user.o

etablissement.o: Etablissement.cpp Etablissement.hpp
	$(COMPILATORG) $(FLAGS) -c Etablissement.cpp -o etablissement.o

restaurant.o: Restaurant.cpp Restaurant.hpp
	$(COMPILATORG) $(FLAGS) -c Restaurant.cpp -o restaurant.o

bar.o: Bar.cpp Bar.hpp
	$(COMPILATORG) $(FLAGS) -c Bar.cpp -o bar.o

hotel.o: Hotel.cpp Hotel.hpp
	$(COMPILATORG) $(FLAGS) -c Hotel.cpp -o hotel.o

database.o: DataBase.hpp DataBase.cpp
	$(COMPILATORG) $(FLAGS) -c DataBase.cpp -o database.o

main.o: main.cpp
	$(COMPILATORG) $(FLAGS) -c main.cpp -o main.o

clean: 
	rm -rf *.o

mrproper: clean
	rm -f links