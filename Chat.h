#pragma once
#include <vector>
#include <memory>
#include <unordered_map> 
#include "Message.h"

class Chat
{

public:
	void StartChat() { _isChatWork = true; }; // ������ ������ ����, ��������� _isChatWork � true
	bool IsChatWork() const { return _isChatWork; } // ���������� ������� ��������� ���� ��������/�� ��������
	int GetCurrentUser() const { return _currentUser; } // ���������� ���� �������� ������������

	void ShowLoginMenu();  // ���� �����������
	void ShowUserMenu();  // ���� ����������������� ������������

private:

	bool _isChatWork = false; // ����������, ���������� �� ����������� ������ ���� (� ������ ������ ���� ��������� � true)
	std::unordered_map<int, User> _users; // ���������, ���������� ���� ������������������ �������������
	std::vector<Message> _messages; // ������ - ������, ���������� ��� ������������ � ��� ���������
	int _currentUser = -1; // ��������� �� �������� ������������
	int _data_count = 0; // ���������� ������������������ �������������
	int _mem_size = 8;

	void UserLogin(); // ���� ����������� ������������
	void UserRegistration(); // ���� ����������� ������ ������������
	void AddUser(std::string login, uint* password); // ���������� ������������ � unordered_map
	int Hash_func(const std::string& login, int offset); // ���-�������, ����������� ���� ��� unordered_map
	int Hf_multiply(int val);
	void ShowAllUsers(); // �������� ���� �������������, ���������������� � ����
	void ShowChat(); // �������� ��� ��������� � ����
	void AddMessage(); // �������� ��������� ���� / ����������� ������������
	void �hangePassword(); // ��������� ������ �������� ������������

	int GetUserLogin(const std::string& login) const; // ����� ������������ �� ������, ���������� ���� � unordered_map

};