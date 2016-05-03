#include <string>


class User {
	private:
		std::string _name;
		std::string _email;
		std::string _password;
		int _userId;
		int _creationDate;
		int _adminId;
		bool _isAdmin;
		
	public:
		User(std::string, std::string, std::string, int);
		std::string getName();
		std::string getEmail();
		std::string getPassword();
		int getCreationDate();
};
