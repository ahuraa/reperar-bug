//CastleDEV
#include "ScriptPCH.h"

class announce_login : public PlayerScript
{
public:
	announce_login() : PlayerScript("announce_login") {}

	void OnLogin(Player* player, bool /*loginFirst*/)
	{
		std::string msg;

		if(player->GetTotalPlayedTime() < 5)
		{
			msg += "|cff54b5ffBienvenido a la comunidad WoW Dreamz|r ";
			msg += player->GetName();
			msg += "|cff54b5ff!|r";
			sWorld->SendServerMessage(SERVER_MSG_STRING, msg.c_str(), 0);
			player->CastSpell(player, 55420);
			return;
		}
		else
		{
		}
	}

};
 
void AddSC_announce_login()
{
	new announce_login;
}