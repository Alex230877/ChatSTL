#include <iostream>
#include "Chat.h"

using namespace std;

int Chat::GetUserLogin(const string& login) const
{
	for (auto& user : _users)
	{
		if (login == user.second.GetLogin())
		{
			return user.first;
		}
	}
	return -1;
}

void Chat::UserLogin()
{
	string login, password;
	string operation;
	do {
		cout << "Enter login : ";
		cin >> login; // логин пользователя
		_currentUser = GetUserLogin(login);
		if (_currentUser == -1)
		{
			cout << "Invalid login entered. Press 0 to exit, press any key to continue:" << endl;
			cin >> operation;
			if (operation == "0")
				return;
		}
		else
		{
			bool passOk = false;
			do
			{
		cout << "Enter password : ";
		cin >> password; // пароль пользователя
		for (size_t i = 0; i < _mem_size; i++)
		{
			int index = Hash_func(login, i);
			unordered_map<int, User>::iterator it = _users.find(index);
			uint* PasHash = sha1(password.c_str(), password.length());
			if (it != _users.end() && !memcmp(it->second.GetPassword(), PasHash, SHA1HASHLENGTHBYTES))
			{
				cout << "\n Hello, " << it->second.GetLogin() << "!\n " << endl;
				passOk = true;
				delete[] PasHash;
				break;
			}
			else
			{
				cout << "Wrong password entered. Press 0 to exit, press any key to continue:" << endl;
				cin >> operation;
				if (operation == "0")
				{
					_currentUser = -1;
					return;
				}
				break;
			}
		}
			} while (!passOk);
		}
	} while (!(_currentUser >= 0));
}

void Chat::UserRegistration()
{
	string login, password, name;
	bool passOk = false;
	cout << "\n User registration \n" << endl;
	cout << "Enter login: ";
	cin >> login; 
	if (GetUserLogin(login) != -1 || login == "All")
	{
		throw UserLoginException();
	}
	while (!(passOk))
	{
		cout << "Enter password: ";
		cin >> password;
		if (password.length() < 4 || password.length() > 8)
			throw UserPasswordException();
		else
		{
			passOk = true;
			uint* _pass_sha1_hash = sha1(password.c_str(), password.length());
			AddUser(login, _pass_sha1_hash);
		}
	}
}

void Chat::AddUser(string login, uint* password)
{
	if (_data_count >= _mem_size)
		_mem_size *= 2;

	int index = -1;
	int i = 0;
	for (; i < _mem_size; i++) {
		index = Hash_func(login, i);
		unordered_map<int, User>::iterator it = _users.find(index);
		if (it == _users.end() || !_users.size() || it->second.GetStatus() == 0)
			break;
	}
	if (i >= _mem_size)
	{
		_mem_size *= 2;
		AddUser(login, password);
	}
	else
	{
		User user = User(login, password);
		_users.emplace(index, user);
		unordered_map<int, User>::iterator it = _users.find(index);
		_currentUser = it->first;
		_data_count++;
	}
}

int Chat::Hash_func(const string& login, int offset) {
	long sum = 0;
	for (int i = 0; i < login.length(); i++)
	{
		sum += login[i];
	}
	return (Hf_multiply(sum) + offset * offset) % _mem_size;
}

int Chat::Hf_multiply(int val) {
	const double A = 0.7;
	return int(_mem_size * (A * val - int(A * val)));
}

void Chat::ShowUserMenu() 
{
	char menu;
	
	do 
	{
		cout << "\n User's menu\n" << endl;
		cout << "1 - read messages" << endl;
		cout << "2 - view Users" << endl;
		cout << "3 - to write a message" << endl;
		cout << "4 - change password" << endl;
		cout << "0 - exit" << endl;
		cin >> menu;

		switch (menu)
		{
		case '1':
			ShowChat();
			break;
		case '2':
			ShowAllUsers();
			break;
		case '3':
			AddMessage();
			break;
		case '4':
			СhangePassword();
			break;
		case '0':
			_currentUser = -1;
			break;
		default:
			cout << "\n Input Error! \n" << endl;
			break;
		}
	} while (_currentUser >= 0);
}

void Chat::СhangePassword()
{
	string password;
	cout << "Enter a new password: " << endl;
	cin >> password;
	if (password.length() < 4 || password.length() > 8)
		throw UserPasswordException();
	else
	{
		for (auto& user : _users)
		{
			uint* _pass_sha1_hash = sha1(password.c_str(), password.length());
			unordered_map<int, User>::iterator it = _users.find(GetCurrentUser());
			if (it->second.GetLogin() == user.second.GetLogin())
				user.second.SetPassword(_pass_sha1_hash);
		}
	}
}

void Chat::AddMessage() 
{
	string user, text;
	cout << "\nEnter the username to whom you want to send a message, to send to all users, type - all: ";
	cin >> user;  // пользователь
	cout << "Enter your message text: ";
	cin.ignore();
	getline(cin, text); // сообщение

	if (!(user == "all" || GetUserLogin(user) != -1))
	{
		cout << user << "\n Пользователь с данным именем не найден! \n"  << endl;
		return;
	}
	  unordered_map<int, User>::iterator it = _users.find(GetCurrentUser());
	  if (user == "all") // отправка сообщения всем пользователям
	  {
		_messages.push_back(Message{ it->second.GetLogin(), "all", text });
		cout << "\n Message sent to all users! \n" << endl;
	  }

	else  //отправка сообщения полльзователю
	{
		unordered_map<int, User>::iterator it2 = _users.find(GetUserLogin(user));
		_messages.push_back(Message{ it->second.GetLogin(), it2->second.GetLogin(), text });
		cout << "\n Message sent! \n" << endl;
	}
}

void Chat::ShowLoginMenu() 
{
	_currentUser = -1;
	char menu;
	do
	{
		cout << "\n Console CHAT \n " << endl;
		cout << "1 - entrance" << endl;
		cout << "2 - registration" << endl;
		cout << "0 - exit chat" << endl;
		cin >> menu;
 
		switch (menu)
		{
		case '1':
			UserLogin();
			break;
		case '2':
			try
			{
				UserRegistration();
			}
			catch (const exception& excep) // проверка
			{
				cout << excep.what() << endl;
			}
			break;
		case '0':
			_isChatWork = false;
			break;

		default:
			cout << "\n Input Error! \n" << endl;
		}
	} while (!_currentUser && _isChatWork);
}

void Chat::ShowChat()
{
	string Sender, Recipient;
	//cout << "\n Сообщения: \n" << endl;
	if (!(_messages.size()))
	{
		cout << " There are no messages in this chat! " << endl;
		return;
	}
	cout << "\n These are all messages in this chat " << endl;

	for (auto& message : _messages)
	{ 
	unordered_map<int, User>::iterator it = _users.find(GetCurrentUser());
	  {
		if (it->second.GetLogin() == message.GetSender() || it->second.GetLogin() == message.GetRecipient() || message.GetRecipient() == "всем")
		{
			unordered_map<int, User>::iterator it2 = _users.find(GetUserLogin(message.GetSender()));
			Sender = (it->second.GetLogin() == message.GetSender()) ? "me" : it2->second.GetLogin();
			if (message.GetRecipient() == "all")
			{
				Recipient = "all";
			}
			else
			{
				unordered_map<int, User>::iterator it3 = _users.find(GetUserLogin(message.GetRecipient()));
				Recipient = (it->second.GetLogin() == message.GetRecipient()) ? "me" : it3->second.GetLogin();
			}
			cout << "From: " << Sender << " For: " << Recipient << endl;
			cout << "Message: " << message.GetText() << "\n" << endl;
		}
	  }
	}
}

void Chat::ShowAllUsers() 
{
	cout << "\n Users: \n" << endl;

	for (auto& user : _users)
	{
		if (_currentUser == user.first)
		{
			cout << "-> " << user.second.GetLogin(); // указатель под кем зайдено
		}
		else
		{
			cout << user.second.GetLogin();
		}
		cout << endl;
	}
}