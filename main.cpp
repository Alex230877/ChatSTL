#include <iostream>
#include "Chat.h"

int main()
{
	Chat chat;
	chat.StartChat();

	while (chat.IsChatWork())
	{
	  chat.ShowLoginMenu();
		while (chat.GetCurrentUser() >= 0)
		{
		  chat.ShowUserMenu();
		}
	}
	return 0;
}