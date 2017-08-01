#include "Channel.h"
#include "Chat.h"
#include "ScriptMgr.h"
#include "Language.h"
#include "chat_censor.h"
#include "Player.h"
#include "promo.h"


filtrochat* filtrochat::instance()
{
	static filtrochat instance;
	return &instance;
}
void filtrochat::Iniciar()
{
	if (sfiltrochat->Iniciado)
		return;
	sfiltrochat->Iniciado = true;
	TC_LOG_INFO("server.loading", "Cargando configuraciones del filtro de chat");
	QueryResult r = LoginDatabase.PQuery("select count(*) from chat_censor;");
	filtro fi;
	Field* f = r->Fetch();
	if (f[0].GetInt8() == 0)
	{
		sfiltrochat->Activar = false;
		return;
	}
	fi.SCantidad(f[0].GetInt8());
	QueryResult rr = LoginDatabase.PQuery("select text, action from chat_censor;");
	int i = 0;
	while (Field* fr = rr->Fetch())
	{
		fi.Texto[i] = fr[0].GetString();
		fi.Accion[i] = fr[1].GetInt8();
		i++;
		rr->NextRow();
	}
	sfiltrochat->Censura = fi;
	sfiltrochat->Activar = true;
}

class System_Censure : public PlayerScript
{
public:
    System_Censure() : PlayerScript("System_Censure") { }

    void CheckMessage(Player* player, string& msg, uint32 lang)
    {
		if (player->GetSession()->GetSecurity() > 1)
            return;
		if (!sfiltrochat->Iniciado)
			sfiltrochat->Iniciar();
		if (!sfiltrochat->Activar)
			return;
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
				sWorld->SendGMText(LANG_PERSONALIZADO,m.c_str());
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
    };

    void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg) override
    {
        CheckMessage(player, msg, lang);
    }

    void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Player* /*receiver*/) override
    {
        CheckMessage(player, msg, lang);
    }

    void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Group* /*group*/) override
    {
        CheckMessage(player, msg, lang);
    }

    void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Guild* /*guild*/) override
    {
        CheckMessage(player, msg, lang);
    }

    void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Channel* /*channel*/) override
    {
        CheckMessage(player, msg, lang);
    }
};

class cs_filtro : public CommandScript
{
public:
	cs_filtro() : CommandScript("cs_filtro") { }

	vector<ChatCommand> GetCommands() const override
	{
		static vector<ChatCommand> ev_filtroCommandTable =
		{
			{ "reload", rbac::RBAC_PERM_COMMAND_FILTRO, true, &Handleev_reload, "" },
		};
		static vector<ChatCommand> Handleev_filtroCommandTable =
		{
			{ "filtro", rbac::RBAC_PERM_COMMAND_FILTRO, true, NULL, "", ev_filtroCommandTable },
		};
		return Handleev_filtroCommandTable;
	}

	static bool Handleev_reload(ChatHandler * handler, const char * args)
	{
		handler->SendGlobalGMSysMessage("DB tables `Filtros*` reloaded.");
		sfiltrochat->Iniciado = false;
		sfiltrochat->Iniciar();
		return true;
	}
};

void AddSC_System_Censure()
{
    new System_Censure();
	new cs_filtro();
}