#include "promo.h"
#include "Chat.h"
#include "ScriptMgr.h"
#include "ObjectMgr.h"
#include "Language.h"

using namespace std;

class cs_promo : public CommandScript
{
public:
	cs_promo() : CommandScript("cs_promo") { }

	vector<ChatCommand> GetCommands() const override
	{
		static vector<ChatCommand> v_promo_add =
		{
			{ "character",	rbac::RBAC_PERM_COMMAND_PROMO, true, &Promo_Add_Character,	"" },
			//{ "set",		rbac::RBAC_PERM_COMMAND_PROMO, true, &Promo_Add_Set,		"" },
			//{ "profe",		rbac::RBAC_PERM_COMMAND_PROMO, true, &Promo_Add_Profe,		"" },
		};
		static vector<ChatCommand> ev_promoCommandTable =
		{
			{ "reload", rbac::RBAC_PERM_COMMAND_PROMO, true,	&Handleev_reload,	"" },
			{ "set",	rbac::RBAC_PERM_COMMAND_PROMO, false,	&Promo_Set,			"" },
			{ "add",	rbac::RBAC_PERM_COMMAND_PROMO, true,	NULL,				"", v_promo_add },
			{ "info",	rbac::RBAC_PERM_COMMAND_PROMO, false,	&Promo_Info,	"" },
		};
		static vector<ChatCommand> Handleev_promoCommandTable =
		{
			{ "promo", rbac::RBAC_PERM_COMMAND_PROMO, false, NULL, "", ev_promoCommandTable },
		};
		return Handleev_promoCommandTable;
	}

	static bool is_number(const string& s)
	{
		std::string::const_iterator it = s.begin();
		while (it != s.end() && std::isdigit(*it)) ++it;
		return !s.empty() && it == s.end();
	}
	static bool Handleev_promo(ChatHandler * handler, const char * args)
	{
		/*if (!*args)
		{
			//Obtener usuario desde la db
			Player* target = handler->getSelectedPlayer();
			uint32 accID = target->GetSession()->GetAccountId();
			string qacc = "SELECT username FROM `account` where id = " + to_string(accID) + ";";
			QueryResult racc = LoginDatabase.PQuery(qacc.c_str());
			Field* facc = racc->Fetch();

			string acc = facc[0].GetString();
			string ip = target->GetSession()->GetRemoteAddress().c_str();

			handler->SendSysMessage(string("AccID: " + to_string(accID) + " Acc: " + acc + " IP: " + ip).c_str());

			QueryResult rn = LoginDatabase.PQuery(string("select count(account) from promonoip where account = " + to_string(accID)).c_str());
			Field *fn = rn->Fetch();
			if (fn[0].GetInt32() != 0)
				handler->SendSysMessage(string("-- La cuenta puede burlar el bloqueo de IP --").c_str());

			//Registros de IP y cuenta
			handler->SendSysMessage(string("-- Para ver mas informacion de un pj en especifico usar .promo #id --").c_str());
			handler->SendSysMessage(string("-- Promociones encontradas en la cuenta e IP --").c_str());
			handler->SendSysMessage(string("#->accid | username | idpj | name | PVP | PVE | Profe1 | Profe2").c_str());
			int i2 = 0;
			QueryResult r1 = LoginDatabase.PQuery(string("select * from promo where ip = '" + ip + "' or account = " + to_string(accID) + ";").c_str());
			while (Field *f1 = r1->Fetch())
			{
				i2++;
				string rfecha = f1[2].GetString();
				int raccid = f1[4].GetInt32();
				QueryResult rr = LoginDatabase.PQuery(string("SELECT username FROM `account` where id = " + to_string(raccid) + ";").c_str());
				Field* fr = rr->Fetch();
				string racc = fr[0].GetString();
				int rpjid = f1[5].GetInt32();
				string rpj = f1[6].GetString();
				string rpvp = (!string(f1[8].GetString()).empty() ? "Si" : "No");
				string rpve = (!string(f1[10].GetString()).empty() ? "Si" : "No");
				string rpro1 = (!string(f1[14].GetString()).empty() ? "Si" : "No");
				string rpro2 = (!string(f1[16].GetString()).empty() ? "Si" : "No");
				handler->SendSysMessage(string(to_string(i2) + "-> " + to_string(raccid) + " | " + racc + " | " + to_string(rpjid) + " | " + rpj + " | " + rpvp + " | " + rpve + " | " + rpro1 + " | " + rpro2).c_str());
				r1->NextRow();
			}
		}
		else
		{
			string pjid = args;
			if (!is_number(pjid))
			{
				handler->SendSysMessage(".evc update #id, id es un valor numerico.");
				return true;
			}

			/*string qacc = "select * from promo where `character` = " + to_string(accID) + ";";
			QueryResult racc = LoginDatabase.PQuery(qacc.c_str());
			Field* facc = racc->Fetch();
			handler->SendSysMessage("Codigo en desarrollo, att: Cantload");

		}*/
		return true;
	}
	static bool Handleev_reload(ChatHandler * handler, const char * args)
	{
		spromo->iniciado = false;
		spromo->SIniciar();
		handler->SendGlobalGMSysMessage("DB tables `Promo*` reloaded.");
		return true;
	}
	static bool Promo_Info(ChatHandler * chat, const char * args)
	{
		Player* target;
		ObjectGuid targetGuid;
		std::string targetName;
		PreparedStatement* stmt = NULL;

		// To make sure we get a target, we convert our guid to an omniversal...
		ObjectGuid parseGUID(HighGuid::Player, uint32(atoul(args)));

		// ... and make sure we get a target, somehow.
		if (sObjectMgr->GetPlayerNameByGUID(parseGUID, targetName))
		{
			target = ObjectAccessor::FindPlayer(parseGUID);
			targetGuid = parseGUID;
		}

		else if (!chat->extractPlayerTarget((char*)args, &target, &targetGuid, &targetName))
			return false;

		PjInfo pjinfo;
		spromo->GetPjInfo(pjinfo, target);

		
		
		

		chat->PSendSysMessage("Comando sin terminar");
		return true;
	}
	static bool Promo_Set(ChatHandler * chat, const char * args)
	{
		if (!*args)
		{
			chat->SendSysMessage(LANG_CMD_SYNTAX);
			chat->SetSentErrorMessage(true);
			return false;
		}

		PjInfo pjinfo;
		spromo->GetPjInfo(pjinfo, chat->GetSession()->GetPlayer());

		uint32 setid = 0;
		string clase;

		char* arg1 = strtok((char*)args, " ");  //set
		char* arg2 = strtok(NULL, " ");		//set id

		if (!arg1 || !arg2)
			return false;
		clase = arg1;
		setid = atoi(arg2);

		spromo->DarSet(pjinfo, clase, setid, false);
		return true;
	}
	static bool Promo_Add_Character(ChatHandler * chat, const char * args)
	{
		if (!*args)
		{
			chat->SendSysMessage(LANG_CMD_SYNTAX);
			chat->SetSentErrorMessage(true);
			return false;
		}

		PjInfo pjinfo1;
		spromo->GetPjInfo(pjinfo1, chat->GetSession()->GetPlayer());

		string targetAccountName = "";
		uint32 targetAccountId = 0;
		uint32 cantidad = 0;
		string motivo = "Command " + pjinfo1.acc + " -> " + pjinfo1.pjname;
		string detalles;

		char* arg1 = strtok((char*)args, " ");  //acc
		char* arg2 = strtok(NULL, " ");		//cantidad
		char* arg3 = strtok(NULL, "");		//detalles
		bool isAccountNameGiven = true;
		if (!arg3)
		{
			if (!chat->getSelectedPlayer())
				return false;
			isAccountNameGiven = false;
		}
		if (!arg2)
			return false;
		if (!isAccountNameGiven && !arg1)
			return false;
		if (isAccountNameGiven)
		{
			targetAccountName = arg1;
			if (!Utf8ToUpperOnlyLatin(targetAccountName) || !AccountMgr::GetId(targetAccountName))
			{
				chat->PSendSysMessage(LANG_ACCOUNT_NOT_EXIST, targetAccountName.c_str());
				chat->SetSentErrorMessage(true);
				return false;
			}
		}
		cantidad = (isAccountNameGiven) ? atoi(arg2) : atoi(arg1);
		detalles = (isAccountNameGiven) ? arg3 : arg2;
		targetAccountId = (isAccountNameGiven) ? AccountMgr::GetId(targetAccountName) : chat->getSelectedPlayer()->GetSession()->GetAccountId();
		PjInfo pjinfo;
		pjinfo.ip = (isAccountNameGiven) ? "" : chat->getSelectedPlayer()->GetSession()->GetRemoteAddress();
		pjinfo.accID = targetAccountId;
		spromo->AumentarPromos(pjinfo, cantidad, motivo, detalles);
		chat->PSendSysMessage("Se realizado el aumento de %d promociones correctamente", cantidad);
		return true;
	}
	static bool Promo_Add_Set(ChatHandler * chat, const char * args)
	{
		if (!*args)
		{
			chat->SendSysMessage(LANG_CMD_SYNTAX);
			chat->SetSentErrorMessage(true);
			return false;
		}

		PjInfo pjinfo1;
		spromo->GetPjInfo(pjinfo1, chat->GetSession()->GetPlayer());

		string targetAccountName = "";
		uint32 targetAccountId = 0;
		string clase = "";
		uint32 cantidad = 0;
		string motivo = "Command " + pjinfo1.acc + " -> " + pjinfo1.pjname;
		string detalles;

		char* arg1 = strtok((char*)args, " ");  //acc
		char* arg2 = strtok(NULL, " ");		//cantidad
		char* arg3 = strtok(NULL, " ");		//clase
		char* arg4 = strtok(NULL, "");		//detalles
		bool isAccountNameGiven = true;
		if (!arg4)
		{
			if (!chat->getSelectedPlayer())
				return false;
			isAccountNameGiven = false;
		}
		if (!isAccountNameGiven && !arg1)
			return false;
		if (isAccountNameGiven)
		{
			targetAccountName = arg1;
			if (!Utf8ToUpperOnlyLatin(targetAccountName) || !AccountMgr::GetId(targetAccountName))
			{
				chat->PSendSysMessage(LANG_ACCOUNT_NOT_EXIST, targetAccountName.c_str());
				chat->SetSentErrorMessage(true);
				return false;
			}
		}
		cantidad = (isAccountNameGiven) ? atoi(arg2) : atoi(arg1);
		detalles = (isAccountNameGiven) ? arg3 : arg2;
		targetAccountId = (isAccountNameGiven) ? AccountMgr::GetId(targetAccountName) : chat->getSelectedPlayer()->GetSession()->GetAccountId();
		PjInfo pjinfo;
		pjinfo.ip = (isAccountNameGiven) ? "" : chat->getSelectedPlayer()->GetSession()->GetRemoteAddress();
		pjinfo.accID = targetAccountId;
		
		spromo->AumentarSets(pjinfo, cantidad, clase, motivo, detalles);
		return true;
	}
	static bool Promo_Add_Profe(ChatHandler * chat, const char * args)
	{
		PjInfo pjinfo;
		Player* player = chat->getSelectedPlayer();
		bool recetas;
		int cantidad;
		string motivo;
		string detalles;
		spromo->GetPjInfo(pjinfo, player);
		//spromo->AumentarProfes(pjinfo, recetas,cantidad, motivo, detalles);
		return true;
	}
};

void AddSC_cs_promo()
{
	new cs_promo();
}