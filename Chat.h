#pragma once
#include <vector>
#include <memory>
#include <unordered_map> 
#include "Message.h"

class Chat
{

public:
	void StartChat() { _isChatWork = true; }; // начало работы чата, установка _isChatWork в true
	bool IsChatWork() const { return _isChatWork; } // возвращает текущее состояние чата работает/не работает
	int GetCurrentUser() const { return _currentUser; } // возвращает ключ текущего пользователя

	void ShowLoginMenu();  // меню авторизации
	void ShowUserMenu();  // меню авторизированного пользователя

private:

	bool _isChatWork = false; // переменная, отвечающая за прекращение работы чата (в начале работы чата переходит в true)
	std::unordered_map<int, User> _users; // контейнер, содержащий всех зарегистрированных пользователей
	std::vector<Message> _messages; // вектор - массив, содержащий все отправленные в чат сообщения
	int _currentUser = -1; // указатель на текущего пользователя
	int _data_count = 0; // количество зарегистрированных пользователей
	int _mem_size = 8;

	void UserLogin(); // меню авторизации пользователя
	void UserRegistration(); // меню регистрации нового пользователя
	void AddUser(std::string login, uint* password); // добавление пользователя в unordered_map
	int Hash_func(const std::string& login, int offset); // хеш-функция, вычисляющая ключ для unordered_map
	int Hf_multiply(int val);
	void ShowAllUsers(); // показать всех пользователей, зарегистрованных в чате
	void ShowChat(); // показать все сообщения в чате
	void AddMessage(); // написать сообщение всем / конкретному пользователю
	void СhangePassword(); // изменение пароля текущего пользователя

	int GetUserLogin(const std::string& login) const; // найти пользователя по логину, возвращает ключ в unordered_map

};