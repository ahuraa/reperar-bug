#include "AccountMgr.h"
#include "Chat.h"
#include "Config.h"
#include "premium_system.h"
#include "World.h"

class PremiumLogin : public PlayerScript
{
public:
PremiumLogin() : PlayerScript("PremiumLogin") { }


void OnLogin(Player* player, bool /* firstLogin */)
{
    ChatHandler(player->GetSession()).PSendSysMessage("|cffff0000BIENVENIDO A WOWDREAMZ BY BEATER");
	{
    std::ostringstream ss;
	uint32 PremiumLevel_1 = sConfigMgr->GetIntDefault("Premium.VIP.Level.1", 80);
	uint32 PremiumLevel_2 = sConfigMgr->GetIntDefault("Premium.VIP.Level.2", 80);
	uint32 PremiumLevel_3 = sConfigMgr->GetIntDefault("Premium.VIP.Level.3", 80);
		{	
			if (player->GetSession()->IsPremium() == 1)
			{
				ss << "|cff00ff00[Premium VIP 1]|r " << player->GetName() << " has logged in!"; 
				player->GiveLevel(PremiumLevel_1); //player->GiveLevel(PremiumLevel_1);
			}
			if (player->GetSession()->IsPremium() == 2)
			{
				ss << "|cff00ff00[Premium VIP 2]|r " << player->GetName() << " has logged in!"; 
				player->GiveLevel(PremiumLevel_2); //player->GiveLevel(PremiumLevel_2);
			}
			if (player->GetSession()->IsPremium() == 3)
			{
				ss << "|cff00ff00[Premium VIP 3]|r " << player->GetName() << " has logged in!"; 
				player->GiveLevel(PremiumLevel_3); //player->GiveLevel(PremiumLevel_3);
			}
		}
		if (player->GetSession()->IsPremium() == 0)
		{
		ss << "[Player]|r: " << player->GetName() << "|cffff0000Llegó! Carne Fresca!!!";	
		//player->GiveLevel(80); //-- U can Remove The player->GiveLevel  with //player->GiveLevel(80);
		}
		sWorld->SendServerMessage(SERVER_MSG_STRING, ss.str().c_str());
	}
}
};


void AddSC_PremiumLogin()
{
new PremiumLogin;
}