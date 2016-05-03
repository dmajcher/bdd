#include "User.hpp"

User::User(std::string name, std::string password, std::string email, int dateCreation) {
	_name = name;
	_password = password;
	_email = email;
	_creationDate = dateCreation;
}


std::string User::getName() {return _name;}

std::string User::getPassword() {return _password;}

std::string User::getEmail() {return _email;}

int User::getCreationDate() {return _creationDate;}

void User::setName(std::string name) {
	_name = name;
}

void User::setPassword(std::string password) {
	_password = password;
}

void User::setEmail(std::string email) {
	_email = email;
}

void User::setCreationDate(int date) {
	_creationDate = date;
}
