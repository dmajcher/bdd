FLAGS = -std=c++14 -Wpedantic -fPIC -Wall -Wextra -Winit-self -Winline -Wconversion -Wold-style-cast  -Wctor-dtor-privacy -Woverloaded-virtual -Wconversion -Wsign-promo -ltinyxml -l sqlite3
GCC = FALSE
COMPILATORG=g++-5
COMPILATORC=gcc-5

ifeq ($(GCC),TRUE)
	COMPILATORG=g++
	COMPILATORC=gcc 
endif

links: database.o user.o etablissement.o restaurant.o bar.o hotel.o commentaire.o label.o gui

database.o: ../database/DataBase.hpp ../database/DataBase.cpp
	$(COMPILATORG) -c ../database/DataBase.cpp -o ../objects/DataBase.o $(FLAGS)
	
user.o: ../database/User.cpp ../database/User.hpp
	$(COMPILATORG) -c ../database/User.cpp -o ../objects/User.o $(FLAGS)

etablissement.o: ../database/Etablissement.cpp ../database/Etablissement.hpp
	$(COMPILATORG) -c ../database/Etablissement.cpp -o ../objects/Etablissement.o $(FLAGS)
 
restaurant.o: ../database/Restaurant.cpp ../database/Restaurant.hpp
	$(COMPILATORG) -c ../database/Restaurant.cpp -o ../objects/Restaurant.o $(FLAGS)

bar.o: ../database/Bar.cpp ../database/Bar.hpp
	$(COMPILATORG) -c ../database/Bar.cpp -o ../objects/Bar.o $(FLAGS)

hotel.o: ../database/Hotel.cpp ../database/Hotel.hpp
	$(COMPILATORG) -c ../database/Hotel.cpp -o ../objects/Hotel.o $(FLAGS)

commentaire.o: ../database/Commentaire.cpp ../database/Commentaire.hpp
	$(COMPILATORG) -c ../database/Commentaire.cpp -o ../objects/Commentaire.o $(FLAGS)

label.o: ../database/Label.cpp ../database/Label.hpp
	$(COMPILATORG) -c ../database/Label.cpp -o ../objects/Label.o $(FLAGS)

gui:
	cd ../qt && $(MAKE)

newdb:
	cd .. && rm database.db
	$(MAKE)

clean: 
	cd ../objects && rm -rf *.o && rm -rf moc*

reset: clean
	cd ../qt && qmake 
	cd .. && rm database.db
	$(MAKE)

newgui:
	cd ../qt && qmake && $(MAKE)

mrproper: clean
	rm -f links