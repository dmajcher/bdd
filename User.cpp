#include "User.hpp"

User::User(char* name, char* password, char* email, int dateCreation) {
	_name = name;
	_password = password;
	_email = email;
	_creationDate = dateCreation;
}


char* User::getName() {return _name;}

char* User::getPassword() {return _password;}

char* User::getEmail() {return _email;}

int User::getCreationDate() {return _creationDate;}
