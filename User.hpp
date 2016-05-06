#ifndef USER_HPP
#define USER_HPP


#include <string>
#include <iostream>


class User {
	private:
		std::string _name;
		std::string _email;
		std::string _password;
		int _userId;
		int _creationDate;
		int _adminId;
		
	public:
		User(std::string, std::string, std::string, int, int);
		std::string getName();
		std::string getEmail();
		std::string getPassword();
		int getAdminId();
		int getCreationDate();
		void setName(std::string);
		void setEmail(std::string);
		void setPassword(std::string);
		void setCreationDate(int);
		void setAdminId(int);
};


#endif /* USER_HPP */