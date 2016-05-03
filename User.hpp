
class User {
	private:
		char* _name;
		char* _email;
		char* _password;
		int _userId;
		int _creationDate;
		int _adminId;
		bool _isAdmin;
		
	public:
		User(char*, char*, char*, int);
		char* getName();
		char* getEmail();
		char* getPassword();
		int getCreationDate();
};
