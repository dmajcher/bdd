FLAGS = -std=c++14 -Wpedantic -fPIC -Wall -Wextra -Winit-self -Winline -Wconversion -Wold-style-cast  -Wctor-dtor-privacy -Woverloaded-virtual -Wconversion -Wsign-promo -ltinyxml -l sqlite3
GCC = FALSE
COMPILATORG=g++-5
COMPILATORC=gcc-5

ifeq ($(GCC),TRUE)
	COMPILATORG=g++
	COMPILATORC=gcc 
endif

links: database.o user.o etablissement.o restaurant.o bar.o hotel.o commentaire.o gui

database.o: DataBase.hpp DataBase.cpp
	$(COMPILATORG) -c DataBase.cpp -o DataBase.o $(FLAGS)
	
user.o: User.cpp User.hpp
	$(COMPILATORG) -c User.cpp -o User.o $(FLAGS)

etablissement.o: Etablissement.cpp Etablissement.hpp
	$(COMPILATORG) -c Etablissement.cpp -o Etablissement.o $(FLAGS)
 
restaurant.o: Restaurant.cpp Restaurant.hpp
	$(COMPILATORG) -c Restaurant.cpp -o Restaurant.o $(FLAGS)

bar.o: Bar.cpp Bar.hpp
	$(COMPILATORG) -c Bar.cpp -o Bar.o $(FLAGS)

hotel.o: Hotel.cpp Hotel.hpp
	$(COMPILATORG) -c Hotel.cpp -o Hotel.o $(FLAGS)

commentaire.o: Commentaire.cpp Commentaire.hpp
	$(COMPILATORG) -c Commentaire.cpp -o Commentaire.o $(FLAGS)

gui:
	cd qt && $(MAKE)

clean: 
	cd qt && $(MAKE) clean

mrproper: clean
	rm -f links