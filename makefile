FLAGS = -std=c++14 -Wpedantic -fPIC -Wall -Wextra -Winit-self -Winline -Wconversion -Wold-style-cast  -Wctor-dtor-privacy -Woverloaded-virtual -Wconversion -Wsign-promo -ltinyxml -l sqlite3
GCC = FALSE
COMPILATORG=g++-5
COMPILATORC=gcc-5

ifeq ($(GCC),TRUE)
	COMPILATORG=g++
	COMPILATORC=gcc 
endif

links: database.o user.o etablissement.o restaurant.o bar.o hotel.o commentaire.o main.o
	$(COMPILATORG) -o $@ database.o user.o etablissement.o restaurant.o bar.o hotel.o commentaire.o main.o $(FLAGS)

database.o: DataBase.hpp DataBase.cpp
	$(COMPILATORG) -c DataBase.cpp -o database.o $(FLAGS)
	
user.o: User.cpp User.hpp
	$(COMPILATORG) -c User.cpp -o user.o $(FLAGS)

etablissement.o: Etablissement.cpp Etablissement.hpp
	$(COMPILATORG) -c Etablissement.cpp -o etablissement.o $(FLAGS)
 
restaurant.o: Restaurant.cpp Restaurant.hpp
	$(COMPILATORG) -c Restaurant.cpp -o restaurant.o $(FLAGS)

bar.o: Bar.cpp Bar.hpp
	$(COMPILATORG) -c Bar.cpp -o bar.o $(FLAGS)

hotel.o: Hotel.cpp Hotel.hpp
	$(COMPILATORG) -c Hotel.cpp -o hotel.o $(FLAGS)

commentaire.o: Commentaire.cpp Commentaire.hpp
	$(COMPILATORG) -c Commentaire.cpp -o commentaire.o $(FLAGS)

main.o: main.cpp
	$(COMPILATORG) -c main.cpp -o main.o $(FLAGS)

clean: 
	rm -rf *.o

mrproper: clean
	rm -f links
