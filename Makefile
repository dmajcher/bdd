CXXFLAGS = -Wall

links: database.o user.o etablissement.o restaurant.o bar.o hotel.o main.o
	g++ -o $@ database.o user.o etablissement.o restaurant.o bar.o hotel.o main.o

database.o: Database.cpp Database.hpp
	g++ -c Database.cpp

user.o: User.cpp User.hpp
	g++ -c User.cpp

etablissement.o: Etablissement.cpp Etablissement.hpp
	g++ -c Etablissement.cpp

restaurant.o: Restaurant.cpp Restaurant.hpp
	g++ -c Restaurant.cpp

bar.o: Bar.cpp Bar.hpp
	g++ -c Bar.cpp

hotel.o: Hotel.cpp Hotel.hpp
	g++ -c Hotel.cpp

main.o: main.cpp
	g++ -c main.cpp
