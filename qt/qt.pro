######################################################################
# Automatically generated by qmake (3.0) Tue May 10 21:33:21 2016
######################################################################

TEMPLATE = app
TARGET = qt
INCLUDEPATH += .
QT += widgets
LIBS += -ltinyxml -l sqlite3
QMAKE_CXX = g++-5
QMAKE_CXXFLAGS = -std=c++14 -Wpedantic -fPIC -Wall -Wextra -Winit-self -Winline -Wconversion -Wold-style-cast  -Wctor-dtor-privacy -Woverloaded-virtual -Wconversion -Wsign-promo
OBJECTS +=    ../objects/DataBase.o ../objects/Restaurant.o ../objects/Hotel.o ../objects/Bar.o ../objects/Etablissement.o ../objects/Commentaire.o ../objects/User.o
DESTDIR=../exec
OBJECTS_DIR=../objects
MOC_DIR=../objects
# Input
HEADERS += GuiInterface.hpp HomeWindow.hpp SearchWidget.hpp CelluleRecherche.hpp PageRecherche.hpp TableRecherche.hpp TaskBar.hpp LogWidget.hpp
SOURCES += GuiInterface.cpp HomeWindow.cpp SearchWidget.cpp CelluleRecherche.cpp PageRecherche.cpp TableRecherche.cpp TaskBar.cpp LogWidget.cpp main.cpp
