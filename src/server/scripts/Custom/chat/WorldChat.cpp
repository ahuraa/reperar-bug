#include "Channel.h"
#include "Chat.h"
#include "ScriptMgr.h"
#include "Language.h"
#include "chat_censor.h"
#include "Player.h"
#include "promo.h"
#include "WorldChat.h"

using namespace std;

worldchat* worldchat::instance()
{
	static worldchat instance;
	return &instance;
}
void worldchat::iniciar()
{
	if (sworldchat->iniciado)
		return;
	TC_LOG_INFO("server.loading", "Cargando configuraciones de WorldChat");
	QueryResult rr = CharacterDatabase.PQuery("SELECT rango, rango_nombre, rango_color, chat_color FROM `worldchat_rango`");
	while (Field *fr = rr->Fetch())
	{
		rRango[fr[0].GetInt8()] = fr[1].GetString();
		rRangoColor[fr[0].GetInt8()] = fr[2].GetString();
		rRangoColorChat[fr[0].GetInt8()] = fr[3].GetString();
		rr->NextRow();
	}
	QueryResult rc = CharacterDatabase.PQuery("SELECT clase, color FROM `worldchat_clase`");
	while (Field *fc = rc->Fetch())
	{
		rClaseColor[fc[0].GetInt8()] = fc[1].GetString();
		rc->NextRow();
	}
	sworldchat->iniciado = true;
}



void worldchat::mensaje_db(uint32 account, std::string name, std::string  mensaje,std::string local)
{
	try
	{
		LoginDatabase.PExecute("INSERT INTO chat (account,name,mensaje,local) values('%d','%s','%s','%s');",account,name,mensaje,local);
	}
	catch (exception& e)
	{
		cout << e.what() << '\n';
	}

}

class World_Chat : public CommandScript
{
    public:
    World_Chat() : CommandScript("World_Chat") { }
    
    static string fac(uint8 race)
    {
		string r = "";
		switch(race)
		{
			case 1: case 3: case 4: case 7: case 11: r = Alianza1; break;
			case 2: case 5: case 6: case 8: case 10: r = Horda1; break;
		}
		return r;
	}


    static bool HandleWorldChatCommand(ChatHandler * pChat, const char * msg)
    {
	
		if (!sfiltrochat->Iniciado) 
			sfiltrochat->Iniciar();
		if (!sworldchat->iniciado)
			sworldchat->iniciar();
		if(!*msg)
            return false;
		
        Player * player = pChat->GetSession()->GetPlayer();
		uint32 account = player->GetSession()->GetAccountId();
	    string name = player->GetName();
		uint8 sec = player->GetSession()->GetSecurity();
		uint8 c = player->getClass();
		uint8 race = player->getRace();
		string Rango = sworldchat->GRango(sec);
		string RangoColor = sworldchat->GRangoColor(sec);
		string RangoColorChat = sworldchat->GRangoColorChat(sec);
		string ClaseColor = sworldchat->GClaseColor(c);
		string tt = "|cff" + ColorBase1 + "[" + Canal1 + "][|cff" + RangoColor + (sec>1 ? GM_ICON1 : "") + Rango + "|ccf" + ColorBase1 + "]" + fac(race) + "[|r|cff" + ClaseColor + "|Hplayer:" + name + "|h" + name + "|h|r|cff" + ColorBase1 + "]: |cff" + RangoColorChat + msg;
		if (player->GetSession()->GetSecurity() > 1) {
			sWorld->SendGlobalText(tt.c_str(), NULL);
			sworldchat->mensaje_db(account, name, msg, "server");
		}
		else {			
			PjInfo pjinfo;
			spromo->GetPjInfo(pjinfo, player);
			// remove all space characters and transform to lowercase for simpler checking
			string checkmsg = msg;
			string fx = "";
			checkmsg.erase(remove_if(checkmsg.begin(), checkmsg.end(), ::isspace), checkmsg.end());
			transform(checkmsg.begin(), checkmsg.end(), checkmsg.begin(), ::tolower);
			int accion = 0; bool filtro = false;
			for (int i = 0; i < sfiltrochat->Censura.Cantidad; i++)
			{
				if (checkmsg.find(sfiltrochat->Censura.Texto[i]) != string::npos)
				{
					fx = sfiltrochat->Censura.Texto[i];
					filtro = true;
					if (accion < sfiltrochat->Censura.Accion[i])
						accion = sfiltrochat->Censura.Accion[i];
				}
			}
			string m = "|cFFFFFC00[Filtro de chat][|r|cFF60FF00|Hplayer:" + pjinfo.pjname + "|h" + pjinfo.pjname + "|h|r|cFFFFFC00]:|cFF00FFFF " + msg;
			char* delayStr;
			string reasonStr;
			uint32 notSpeakTime;
			PreparedStatement* stmt = LoginDatabase.GetPreparedStatement(LOGIN_UPD_MUTE_TIME);
			string author = "Chat filter";
			WorldPacket data;
			int64 muteTime;
			if (filtro)
			{
				switch (accion)
				{
				case 1:
					sWorld->SendGMText(LANG_PERSONALIZADO, m.c_str());
					msg = "";
					ChatHandler(player->GetSession()).PSendSysMessage("El mensaje que intento enviar no esta permitido!");
					break;
				case 2:
					delayStr = "5m";
					reasonStr = "Spam";
					notSpeakTime = uint32(atoi(delayStr));
					muteTime = time(NULL) + notSpeakTime * MINUTE;
					player->GetSession()->m_muteTime = muteTime;
					stmt->setInt64(0, muteTime);

					if (sWorld->getBoolConfig(CONFIG_SHOW_MUTE_IN_WORLD))
						sWorld->SendWorldText(LANG_COMMAND_MUTEMESSAGE_WORLD, author.c_str(), pjinfo.pjname.c_str(), notSpeakTime, reasonStr.c_str());

					stmt->setString(1, reasonStr.c_str());
					stmt->setString(2, author.c_str());
					stmt->setUInt32(3, pjinfo.accID);
					LoginDatabase.Execute(stmt);
					stmt = LoginDatabase.GetPreparedStatement(LOGIN_INS_ACCOUNT_MUTE);
					stmt->setUInt32(0, pjinfo.accID);
					stmt->setUInt32(1, notSpeakTime);
					stmt->setString(2, author.c_str());
					stmt->setString(3, reasonStr.c_str());
					LoginDatabase.Execute(stmt);
					sWorld->SendGMText(LANG_PERSONALIZADO, m.c_str());
					player->SendChatMessage("El mensaje  %s que intento enviar no esta permitido!, seras penalizado con %d minutos, por haber promocionado el servidor %s, recuerda el no promocionar a otro servidor se bueno y difruta del servidor", fx.c_str(), notSpeakTime, fx.c_str());
					msg = "";
					break;
				case 3:
					delayStr = "-1";
					reasonStr = "Baneado por hacer spam de otros servidores";

					switch (sWorld->BanAccount(BAN_ACCOUNT, pjinfo.acc.c_str(), delayStr, reasonStr.c_str(), author))
					{
					case BAN_SUCCESS:
						if (atoi(delayStr) > 0)
						{
							if (sWorld->getBoolConfig(CONFIG_SHOW_BAN_IN_WORLD))
								sWorld->SendWorldText(LANG_BAN_ACCOUNT_YOUBANNEDMESSAGE_WORLD, author.c_str(), pjinfo.acc.c_str(), secsToTimeString(TimeStringToSecs(delayStr), true).c_str(), reasonStr.c_str());
						}
						else
						{
							if (sWorld->getBoolConfig(CONFIG_SHOW_BAN_IN_WORLD))
								sWorld->SendWorldText(LANG_BAN_ACCOUNT_YOUPERMBANNEDMESSAGE_WORLD, author.c_str(), pjinfo.acc.c_str(), reasonStr.c_str());
						}
						break;
					}
					msg = "";
					break;
				default:
					sWorld->SendGMText(LANG_PERSONALIZADO, m.c_str());
					break;
				}
			}
			else {
				sWorld->SendGlobalText(tt.c_str(), NULL);
				sworldchat->mensaje_db(account, name, msg, "server");
			}
		}

		return true;
    }

	static bool HandleWorldChatReload(ChatHandler * pChat, const char * msg)
	{
		sworldchat->iniciado = false;
		sworldchat->iniciar();
		pChat->SendGlobalGMSysMessage("DB tables `WorldChat*` reloaded.");
		return true;
	}

    std::vector<ChatCommand> GetCommands() const override
    {
		static std::vector<ChatCommand> HandleWorldChatCT =
		{
			{ "reload", rbac::RBAC_PERM_COMMAND_WORLDCHAT_RELOAD,	true, &HandleWorldChatReload, "" },
			{ "",		rbac::RBAC_PERM_COMMAND_WORLDCHAT,			true, &HandleWorldChatCommand, ""},
		};
		static std::vector<ChatCommand> HandleWorldChatCommandTable =
		{
			{ "world",	rbac::RBAC_PERM_COMMAND_WORLDCHAT, false, NULL, "", HandleWorldChatCT},
			{ "w",		rbac::RBAC_PERM_COMMAND_WORLDCHAT, false, NULL, "", HandleWorldChatCT},
			{ "chat",	rbac::RBAC_PERM_COMMAND_WORLDCHAT, false, NULL, "", HandleWorldChatCT},
		};
		return HandleWorldChatCommandTable;
	}
};


class Chat_Onli : public CommandScript
{
public:
	Chat_Onli() : CommandScript("Chat_Onli") { }

	static bool handleWorldChatWebCommand(ChatHandler * pChat, const char * msg) {
			if (!*msg)
				return false;
			//ChatHandler(player->GetSession()).PSendSysMessage(LANG_UNIVERSAL, "zeros",msg);
			sWorld->SendGlobalText(msg, NULL);
			return true;
	}


	std::vector<ChatCommand> GetCommands() const override
	{
		static std::vector<ChatCommand> HandleWorldChatCT =
		{
			
			{ "",		rbac::RBAC_PERM_COMMAND_WORLDCHAT_WEB,			true, &handleWorldChatWebCommand, "" },
		};
		static std::vector<ChatCommand> HandleWorldChatCommandTable =
		{
			{ "webchat",	rbac::RBAC_PERM_COMMAND_WORLDCHAT_WEB, false, NULL, "", HandleWorldChatCT },
		};
		return HandleWorldChatCommandTable;
	}
};


class Online_Announcer : public PlayerScript
{
public:
Online_Announcer() : PlayerScript("Online_Announcer") { }
	void OnLogin(Player* player, bool /* firstLogin */)
	{
		string name = player->GetName();
		string tt = "[Bienvenido!]|r: "+ name +", |cffff0000 Muchachos! ha llegado Carne Fresca!!!";
		sWorld->SendGlobalText(tt.c_str(), NULL);
	}
};


void AddSC_World_Chat()
{
        new World_Chat;
		new Chat_Onli;
		new Online_Announcer;
}