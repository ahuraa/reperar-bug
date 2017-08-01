#include "Player.h"
#include "PlayerDump.h"
#include "ScriptMgr.h"
#include "ScriptedGossip.h"
#include "ObjectMgr.h"
#include "Language.h"
#include "Chat.h"
#include "promo.h"

using namespace std;

class npc_promo : public CreatureScript
{
public:

	npc_promo() : CreatureScript("npc_promo") { }

	
	bool OnGossipHello(Player* player, Creature* creature)
	{
		spromo->SIniciar();
		if (player->IsInCombat())
			return false;
		PjInfo pjinfo;
		spromo->GetPjInfo(pjinfo, player);
		MenuPromo1(creature, pjinfo);
		return true;
	}

	void MenuPromo1(Creature* creature, PjInfo pjinfo){
		Player* player = pjinfo.player;
		player->PlayerTalkClass->ClearMenus();
		if (spromo->Configuraciones.Activa)
			player->SEND_GOSSIP_MENU(pjinfo.NpcText, creature->GetGUID());
		if (!pjinfo.Rechazada)
		{
			if (!spromo->Configuraciones.Activa)
			{
				player->SEND_GOSSIP_MENU(800006, creature->GetGUID());
				return;
			}
			pjinfo.NpcText = 800001;
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "De que trata la promocion? ", GOSSIP_SENDER_MAIN, PROMO_INFO);
			if (pjinfo.prest != 0 && pjinfo.pjlevel < 80 || pjinfo.EsGM && pjinfo.pjlevel < 80)
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, string("Recibir promo (Disponibles: " + (pjinfo.EsGM ? "Sin limite (GM)":to_string(pjinfo.prest) + " de " + to_string(pjinfo.pmax) + ", es por cuenta)")).c_str(), GOSSIP_SENDER_MAIN, PROMO_DAR);
			else 
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, string("Promos disponibles: " + (pjinfo.EsGM ? "Sin limite (GM) (Debe usar otro personaje o disminuir su nivel":to_string(pjinfo.prest) + " de " + to_string(pjinfo.pmax) + (pjinfo.prest != 0 ? " (Debe usar otro personaje)" : ""))).c_str(), GOSSIP_SENDER_MAIN, 0);
			if (pjinfo.PjConPromo && pjinfo.pjlevel == 80 || pjinfo.EsGM)
			{
				if(spromo->Configuraciones.PVP || pjinfo.EsGM)
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, string("Set PVP disponibles: " + (pjinfo.EsGM ? "Sin limite (GM)" : to_string(pjinfo.pvpr) + " de " + to_string(pjinfo.pvpm) + " (Por Pj)")).c_str(), GOSSIP_SENDER_MAIN, (pjinfo.EsGM ? PROMO_SET_PVP : (pjinfo.pvpr != 0 ? PROMO_SET_PVP : 0)));
				else
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Promocion PVP se encuentra desactivada temporalmente", GOSSIP_SENDER_MAIN, 0);
				if (spromo->Configuraciones.PVE || pjinfo.EsGM)
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, string("Set PVE disponibles: " + (pjinfo.EsGM ? "Sin limite (GM)" : to_string(pjinfo.pver) + " de " + to_string(pjinfo.pvem) + " (Por Pj)")).c_str(), GOSSIP_SENDER_MAIN, (pjinfo.EsGM ? PROMO_SET_PVE : (pjinfo.pver != 0 ? PROMO_SET_PVE : 0)));
				else
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Promocion PVE se encuentra desactivada temporalmente", GOSSIP_SENDER_MAIN, 0);
				pjinfo.NpcText = 800002;
			}
			if (pjinfo.AccConPromo && pjinfo.pjlevel == 80 || pjinfo.EsGM)
			{
				if (spromo->Configuraciones.Prof || pjinfo.EsGM)
				{
					if (pjinfo.profm != 0 || pjinfo.EsGM) player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, string("Profesiones disponibles: " + (pjinfo.EsGM ? "Sin limite (GM)" : to_string(pjinfo.profr) + " de " + to_string(pjinfo.profm) + " (Es por cuenta)")).c_str(), GOSSIP_SENDER_MAIN, (pjinfo.EsGM ? PROMO_PROFE : (pjinfo.profr != 0 ? PROMO_PROFE : 0)));
					if (pjinfo.ProfConReceM != 0 || pjinfo.EsGM) player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, string("Profesiones con recetas disponibles: " + (pjinfo.EsGM ? "Sin limite (GM)" : to_string(pjinfo.ProfConReceR) + " de " + to_string(pjinfo.ProfConReceM) + " (Es por cuenta)")).c_str(), GOSSIP_SENDER_MAIN, (pjinfo.EsGM ? PROMO_PROFE_R : (pjinfo.ProfConReceR != 0 ? PROMO_PROFE_R : 0)));
				}
				else
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Promocion de professiones se encuentran desactivadas temporalmente", GOSSIP_SENDER_MAIN, 0);
			}
			else if (pjinfo.AccConPromo)
			{
				if (spromo->Configuraciones.Prof || pjinfo.EsGM)
				{
					if (pjinfo.profm != 0) player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, string("Profesiones disponibles: " + to_string(pjinfo.profr) + " de " + to_string(pjinfo.profm) + " (Es por cuenta, req LVL 80)").c_str(), GOSSIP_SENDER_MAIN, 0);
					if (pjinfo.ProfConReceM != 0) player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, string("Profesiones con recetas disponibles: " + to_string(pjinfo.ProfConReceR) + " de " + to_string(pjinfo.ProfConReceM) + " (Es por cuenta, req LVL 80)").c_str(), GOSSIP_SENDER_MAIN, 0);
				}
				else
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Promocion de professiones se encuentran desactivadas temporalmente", GOSSIP_SENDER_MAIN, 0);
			}
			//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Recuperacion", GOSSIP_SENDER_MAIN, PROMO_RECUPERACION);
			if (player->getClass() != CLASS_DEATH_KNIGHT && player->getLevel() == 80 || player->getClass() == CLASS_DEATH_KNIGHT && player->GetMapId() != 609 && player->getLevel() == 80)
				player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_TAXI, "Ir a Dalaran?", GOSSIP_SENDER_MAIN, TELE_DALARAN);
			//player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_TAXI, "Teleport", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Buzon", GOSSIP_SENDER_MAIN, PROMO_BUZON);
			//Restart Instancia
		
		}
		player->SEND_GOSSIP_MENU(pjinfo.NpcText, creature->GetGUID());
	}
	void MenuProfes(PjInfo pjinfo, Creature* creature, uint32 actions)
	{
		Player* player = pjinfo.player;
		switch (actions)
		{
		case 1:
			pjinfo.DarRecetas = true;
			if (player->HasSkill(SKILL_ALCHEMY))
			{
				player->PlayerTalkClass->SendCloseGossip();
				break;
			}
			else
			{
				if (CompleteLearnProfession(pjinfo, creature, SKILL_ALCHEMY)){
					//player->LearnSpell(51304, false);
					player->AddItem(9149, 1);
					player->RemoveSpell(28672);
					player->RemoveSpell(28675);
					player->RemoveSpell(28677);
				}
				player->PlayerTalkClass->SendCloseGossip();
			}break;
		case 2:
			pjinfo.DarRecetas = true;
			if (player->HasSkill(SKILL_BLACKSMITHING))
			{
				player->PlayerTalkClass->SendCloseGossip();
				break;
			}
			else
			{
				if (CompleteLearnProfession(pjinfo, creature, SKILL_BLACKSMITHING)){
					//player->LearnSpell(51300, false);
					player->RemoveSpell(9788);
					player->RemoveSpell(9787);
					player->AddItem(5956, 1);
				}
				player->PlayerTalkClass->SendCloseGossip();
			}break;
		case 3:
			pjinfo.DarRecetas = true;
			if (player->HasSkill(SKILL_LEATHERWORKING))
			{
				player->PlayerTalkClass->SendCloseGossip();
				break;
			}
			else
			{
				if (CompleteLearnProfession(pjinfo, creature, SKILL_LEATHERWORKING)){
					//player->LearnSpell(51302, false);
					player->RemoveSpell(10660);
					player->RemoveSpell(10658);
					player->RemoveSpell(10656);
				}
				player->PlayerTalkClass->SendCloseGossip();
			}break;
		case 4:
			pjinfo.DarRecetas = true;
			if (player->HasSkill(SKILL_TAILORING))
			{
				player->PlayerTalkClass->SendCloseGossip();
				break;
			}
			else
			{
				if (CompleteLearnProfession(pjinfo, creature, SKILL_TAILORING)){
					//player->LearnSpell(51309, false);
					player->RemoveSpell(26797);
					player->RemoveSpell(26801);
					player->RemoveSpell(26798);
				}
				player->PlayerTalkClass->SendCloseGossip();
			}break;
		case 5:
			pjinfo.DarRecetas = true;
			if (player->HasSkill(SKILL_ENGINEERING))
			{
				player->PlayerTalkClass->SendCloseGossip();
				break;
			}
			else
			{
				if (CompleteLearnProfession(pjinfo, creature, SKILL_ENGINEERING)){
					//player->LearnSpell(51306, false);
					player->RemoveSpell(20219);
					player->RemoveSpell(20222);
					player->RemoveSpell(56273);
				}
				player->PlayerTalkClass->SendCloseGossip();
			}break;

		case 6:
			pjinfo.DarRecetas = true;
			if (player->HasSkill(SKILL_ENCHANTING))
			{
				player->PlayerTalkClass->SendCloseGossip();
				break;
			}
			else
			{
				if (CompleteLearnProfession(pjinfo, creature, SKILL_ENCHANTING))
					//player->LearnSpell(51313, false);
					player->AddItem(44452, 1);
				player->PlayerTalkClass->SendCloseGossip();
			}break;
		case 7:
			pjinfo.DarRecetas = true;
			if (player->HasSkill(SKILL_JEWELCRAFTING))
			{
				player->PlayerTalkClass->SendCloseGossip();
				break;
			}
			else
			{
				if (CompleteLearnProfession(pjinfo, creature, SKILL_JEWELCRAFTING))
					//player->LearnSpell(51311, false);
					player->RemoveSpell(55534);
				player->PlayerTalkClass->SendCloseGossip();
			}break;
		case 8:
			pjinfo.DarRecetas = true;
			if (player->HasSkill(SKILL_INSCRIPTION))
			{
				player->PlayerTalkClass->SendCloseGossip();
				break;
			}
			else
			{
				if (CompleteLearnProfession(pjinfo, creature, SKILL_INSCRIPTION))
					//player->LearnSpell(45363, false);
					player->RemoveSpell(52175);
				player->PlayerTalkClass->SendCloseGossip();
			}break;
		case 9:
			pjinfo.DarRecetas = true;
			if (player->HasSkill(SKILL_COOKING))
			{
				player->PlayerTalkClass->SendCloseGossip();
				break;
			}
			else
			{
				CompleteLearnProfession(pjinfo, creature, SKILL_COOKING);
				player->PlayerTalkClass->SendCloseGossip();
			}break;
		case 10:
			pjinfo.DarRecetas = true;
			if (player->HasSkill(SKILL_FIRST_AID))
			{
				player->PlayerTalkClass->SendCloseGossip();
				break;
			}
			else
			{
				CompleteLearnProfession(pjinfo, creature, SKILL_FIRST_AID);
				player->PlayerTalkClass->SendCloseGossip();
			}break;
		case 11:
			pjinfo.DarRecetas = true;
			if (player->HasSkill(SKILL_HERBALISM))
			{
				player->PlayerTalkClass->SendCloseGossip();
				break;
			}
			else
			{
				if (CompleteLearnProfession(pjinfo, creature, SKILL_HERBALISM))
					//player->LearnSpell(50300, false);
					player->RemoveSpell(8387);
				player->PlayerTalkClass->SendCloseGossip();
			}break;
		case 12:
			pjinfo.DarRecetas = true;
			if (player->HasSkill(SKILL_SKINNING))
			{
				player->PlayerTalkClass->SendCloseGossip();
				break;
			}
			else
			{
				CompleteLearnProfession(pjinfo, creature, SKILL_SKINNING);
				//player->LearnSpell(, false);
				player->PlayerTalkClass->SendCloseGossip();
			}break;
		case 13:
			pjinfo.DarRecetas = true;
			if (player->HasSkill(SKILL_MINING))
			{
				player->PlayerTalkClass->SendCloseGossip();
				break;
			}
			else
			{
				if (CompleteLearnProfession(pjinfo, creature, SKILL_MINING))
					//player->LearnSpell(50310, false);
					player->RemoveSpell(8388);
				player->PlayerTalkClass->SendCloseGossip();
			}
			break;
		}
	}
	bool TeleDalaran(Player* player){
		player->TeleportTo(571, 5804, 625, 648, 1);
		return true;
	}
	
	// RESET_ INSTANCIA
	
	
	bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 actions)
	{
		PjInfo pjinfo;
		spromo->GetPjInfo(pjinfo, player);
		
		int r = 0; int setid = 0;
		
		player->PlayerTalkClass->ClearMenus();
		
		if (actions > SET_PVP && actions < SET_PVE)
		{
			setid = actions;
			player->SendChatMessage("Opcion: %d", actions - 200);
			spromo->DarSet(pjinfo, "pvp", setid, !pjinfo.EsGM);
			player->CLOSE_GOSSIP_MENU();
		}
		if (actions > SET_PVE && actions < 1000)
		{
			setid = actions;
			player->SendChatMessage("Opcion: %d", actions - 200);
			spromo->DarSet(pjinfo, "pve", setid, !pjinfo.EsGM);
			player->CLOSE_GOSSIP_MENU();
		}
		switch (actions)
		{
		case PROMO_INFO:
			player->SEND_GOSSIP_MENU(800003, creature->GetGUID());
			break;
		case PROMO_DAR:
			pjinfo.player->SendChatMessage("Dar promo");
			spromo->DarPromo(pjinfo, true);
			spromo->DarSpells(pjinfo);
			player->CLOSE_GOSSIP_MENU();
			break;
		case PROMO_SET_PVP:
			setid = 0;
			MenuSetPVP(pjinfo, r, setid);
			if (r == 1)
			{
				spromo->DarSet(pjinfo, "pvp", setid, !pjinfo.EsGM);
				player->CLOSE_GOSSIP_MENU();
			}
			else
				player->SEND_GOSSIP_MENU(800004, creature->GetGUID()); 
			break;
		case PROMO_SET_PVE:
			setid = 0;
			MenuSetPVE(pjinfo, r, setid);
			if (r==1)
			{
				spromo->DarSet(pjinfo, "pve", setid, !pjinfo.EsGM);
				player->CLOSE_GOSSIP_MENU();
			}
			else
				player->SEND_GOSSIP_MENU(800004, creature->GetGUID()); 
			break;
		case PROMO_PROFE: 
			pjinfo.DarRecetas = false; MenuProfe(pjinfo, creature, actions);
			player->SEND_GOSSIP_MENU(800005, creature->GetGUID());
			break;
		case PROMO_PROFE_R: pjinfo.DarRecetas = true; MenuProfe(pjinfo, creature, actions);
			player->SEND_GOSSIP_MENU(800005, creature->GetGUID());
			break;
		case MENU_TELEPORT: MenuTeleport(pjinfo, creature, actions);
			break;
		case PROMO_BUZON: player->GetSession()->SendShowMailBox(player->GetGUID());
			break;
		case TELE_DALARAN:
			TeleDalaran(player); 
			player->CLOSE_GOSSIP_MENU();
			break;
		}

		MenuProfes(pjinfo, creature, actions);
		MenuRestaurar(pjinfo, creature, actions);
		AprenderSkills(pjinfo, actions, creature);
		return true;
	}
	void MenuRestaurar(PjInfo pjinfo, Creature* creature, uint32 actions)
	{
		spromo->PersonajesElimidados(pjinfo);
		Player* player = pjinfo.player;
		switch (actions)
		{
		case PROMO_RECUPERACION:
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Cambiar personaje eliminado por nueva promo. (En desarrollo)", GOSSIP_SENDER_MAIN, (pjinfo.PjEliminadosCantidad != 0 ? RECUPERACION_CAMBIAR_PJ_ELIMINADO : 0));
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, string("Recuperar personajes eliminados: " + to_string(pjinfo.PjEliminadosCantidad)).c_str() , GOSSIP_SENDER_MAIN, (pjinfo.PjEliminadosCantidad != 0 ? RECUPERACION_PJ_ELIMINADO_LISTA : 0));
			if (activarProfes(pjinfo))
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Cupos professiones (Solo de la falla del dia 03/04/2016)", GOSSIP_SENDER_MAIN, RECUPERACION_PROFE_RESET);
			if (activarSkills(pjinfo))
			{
				if (player->getClass() == CLASS_WARRIOR)
				{
					player->ADD_GOSSIP_ITEM(TRAINER_ICON, Class_Skills, GOSSIP_SENDER_MAIN, MENU_WARRIOR);
				}
				if (player->getClass() == CLASS_PALADIN)
				{
					player->ADD_GOSSIP_ITEM(TRAINER_ICON, Class_Skills, GOSSIP_SENDER_MAIN, MENU_PALADIN);
				}
				if (player->getClass() == CLASS_HUNTER)
				{
					player->ADD_GOSSIP_ITEM(TRAINER_ICON, Class_Skills, GOSSIP_SENDER_MAIN, MENU_HUNTER);
				}
				if (player->getClass() == CLASS_ROGUE)
				{
					player->ADD_GOSSIP_ITEM(TRAINER_ICON, Class_Skills, GOSSIP_SENDER_MAIN, MENU_ROGUE);
				}
				if (player->getClass() == CLASS_PRIEST)
				{
					player->ADD_GOSSIP_ITEM(TRAINER_ICON, Class_Skills, GOSSIP_SENDER_MAIN, MENU_PRIEST);
				}
				if (player->getClass() == CLASS_DEATH_KNIGHT)
				{
					player->ADD_GOSSIP_ITEM(TRAINER_ICON, Class_Skills, GOSSIP_SENDER_MAIN, MENU_DEATH_K);
				}
				if (player->getClass() == CLASS_SHAMAN)
				{
					player->ADD_GOSSIP_ITEM(TRAINER_ICON, Class_Skills, GOSSIP_SENDER_MAIN, MENU_SHAMAN);
				}
				if (player->getClass() == CLASS_MAGE)
				{
					player->ADD_GOSSIP_ITEM(TRAINER_ICON, Class_Skills, GOSSIP_SENDER_MAIN, MENU_MAGE);
				}
				if (player->getClass() == CLASS_WARLOCK)
				{
					player->ADD_GOSSIP_ITEM(TRAINER_ICON, Class_Skills, GOSSIP_SENDER_MAIN, MENU_WARLOCK);
				}
				if (player->getClass() == CLASS_DRUID)
				{
					player->ADD_GOSSIP_ITEM(TRAINER_ICON, Class_Skills, GOSSIP_SENDER_MAIN, MENU_DRUID);
				}
			}
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			break;
		case RECUPERACION_PROFE_RESET: 
			ProfesReset(pjinfo);
			player->PlayerTalkClass->SendCloseGossip();
			break;
		case RECUPERACION_PJ_ELIMINADO_LISTA:
			for (int i = 0; i < pjinfo.PjEliminadosCantidad; i++)
			{
				string p = "Restaurar PJ: " + pjinfo.PjEliminadoNombre[i];
				player->ADD_GOSSIP_ITEM(GOLD_DOT_ICON, p.c_str(), GOSSIP_SENDER_MAIN, PJ_ELIMINADO + i);
			}
			if (pjinfo.PjEliminadosCantidad==1)
				player->ADD_GOSSIP_ITEM(CHAT_DOTS_ICON, "-----------", GOSSIP_SENDER_MAIN, 0);
			player->SEND_GOSSIP_MENU(800007, creature->GetGUID());
			break;
		}
		if (actions >= PJ_ELIMINADO)
		{
			int i = actions - PJ_ELIMINADO;
			CharacterDatabase.PExecute(string("UPDATE characters SET `name` = '" + pjinfo.PjEliminadoNombre[i] + "', account = %d, deleteDate = NULL, deleteInfos_Account = NULL, deleteInfos_Name = NULL WHERE guid = %d;").c_str(), pjinfo.accID, pjinfo.PjEliminadoId[i]);
			player->SendChatMessage("El personaje ha sido restaurado correctamente.");
			player->PlayerTalkClass->SendCloseGossip();
		}
	}
	void SkillsLearn(PjInfo pjinfo)
	{
		pjinfo.player->LearnSpell(34091, false);
		pjinfo.player->LearnSpell(54197, false);

		if (pjinfo.PjConPromo)
			CharacterDatabase.PExecute("update promo set recskill = 1 where promo_id = %d;", pjinfo.pid);
		else
		{
			QueryResult q = CharacterDatabase.PQuery("select count(*), skills from promo_rest where pjid = %d", pjinfo.pjid);
			Field* f = q->Fetch();
			if (f[0].GetInt8() == 0)
			{
				CharacterDatabase.PExecute("insert into promo_rest(pjid, skills) values(%d,1)", pjinfo.pjid);
			}
			else
			{
				CharacterDatabase.PExecute("update promo_rest set skills = 1 where pjid = %d", pjinfo.pjid);
			}
		}
	}
	void ProfesReset(PjInfo pjinfo)
	{
		QueryResult q = CharacterDatabase.PQuery("select count(*) from promo_profe where account = %d and pj is not null", pjinfo.accID);
		Field* f = q->Fetch();
		int cantidad = f[0].GetInt8();
		if (cantidad == 1)
		{
			CharacterDatabase.PExecute("update promo_profe set pj = NULL, profe = NULL, fecha = NULL where account = %d limit 1;", pjinfo.accID);
			pjinfo.player->SendChatMessage("Se ha limpiado el registro de profesion");
		}
		else if (cantidad >= 2)
		{
			CharacterDatabase.PExecute("update promo_profe set pj = NULL, profe = NULL, fecha = NULL where account = %d limit 2;", pjinfo.accID);
			CharacterDatabase.PExecute("insert into promo_profe(account, recetas, motivo, detalles) VALUES (%d, 1, 'Falla', 'Prof Extra por falla 03-04-2016');", pjinfo.accID);
			CharacterDatabase.PExecute("insert into promo_profe(account, recetas, motivo, detalles) VALUES (%d, 1, 'Falla', 'Prof Extra por falla 03-04-2016');", pjinfo.accID);
			pjinfo.player->SendChatMessage("Se ha limpiado los registros de profesion y agregado 2 extra");
		}
	}
	bool activarProfes(PjInfo pjinfo)
	{
		int pjidmax = 4291;
		if (!pjinfo.PjConPromo)
			return false;
		if (pjinfo.pjid < pjidmax)
		{
			QueryResult q = CharacterDatabase.PQuery("select count(*) from promo_profe where account = %d and profe = 'restaurar'", pjinfo.accID);
			Field* f = q->Fetch();
			return (f[0].GetInt8() != 0 ? true : false);
		}
		return false;
	}
	bool activarSkills(PjInfo pjinfo)
	{
		int pjidmax = 4291;
		if (pjinfo.PjConPromo)
		{
			QueryResult q1 = CharacterDatabase.PQuery("select recskill from promo where promo_id = %d", pjinfo.pid);
			Field* f1 = q1->Fetch();
			return (f1[0].GetInt8() == 0 ? true : false);
		}
		else if (pjinfo.pjid < pjidmax && pjinfo.pjlevel == 80)
		{
			QueryResult q = CharacterDatabase.PQuery("select count(*), skills from promo_rest where pjid = %d", pjinfo.pjid);
			Field* f = q->Fetch();
			if (f[0].GetInt8() == 0)
				return true;
			else
			{
				return f[1].IsNull();
			}
		}
		return false;
	}
	void MenuTeleport(PjInfo &pjinfo, Creature* creature, uint32 actions)
	{
		Player* player = pjinfo.player;
		switch (actions)
			default:

				break;
	}
	void MenuProfe(PjInfo &pjinfo, Creature* creature, uint32 actions)
	{
		Player* player = pjinfo.player;
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Alquimia", GOSSIP_SENDER_MAIN, 1);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Herreria", GOSSIP_SENDER_MAIN, 2);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Peleteria", GOSSIP_SENDER_MAIN, 3);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Sastreria", GOSSIP_SENDER_MAIN, 4);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Ingenieria", GOSSIP_SENDER_MAIN, 5);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Encantamiento", GOSSIP_SENDER_MAIN, 6);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Joyeria", GOSSIP_SENDER_MAIN, 7);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Inscripcion", GOSSIP_SENDER_MAIN, 8);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Herbologia", GOSSIP_SENDER_MAIN, 11);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Desuello", GOSSIP_SENDER_MAIN, 12);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Mineria", GOSSIP_SENDER_MAIN, 13);
		//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Cooking", GOSSIP_SENDER_MAIN, 9);
		//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "First Aid", GOSSIP_SENDER_MAIN, 10);
	}
	void MenuSetPVP(PjInfo pjinfo, int &registros, int &setid)
	{
		registros = 0;
		for (int i = 0; i < spromo->PVP.registros; i++)
		{
			if (spromo->PVP.clase[i] == pjinfo.pjclase)
			{
				registros++;
				setid = 200 + spromo->PVP.id[i];
				string tpvp = spromo->PVP.npc_text[i];
				pjinfo.player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, tpvp.c_str(), GOSSIP_SENDER_MAIN, setid);
			}
		}
	}
	void MenuSetPVE(PjInfo pjinfo, int &registros, int &setid)
	{
		registros = 0;
		for (int i = 0; i < spromo->PVE.registros; i++)
		{
			if (spromo->PVE.clase[i] == pjinfo.pjclase)
			{
				registros++;
				setid = 600 + spromo->PVE.id[i];
				string tpve = spromo->PVE.npc_text[i];
				pjinfo.player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, tpve.c_str(), GOSSIP_SENDER_MAIN, setid);
			}
		}
	}



	bool PlayerAlreadyHasTwoProfessions(const PjInfo pjinfo) const
	{
		uint32 skillCount = 0;
		Player* player = pjinfo.player;
		if (player->HasSkill(SKILL_MINING))
			skillCount++;
		if (player->HasSkill(SKILL_SKINNING))
			skillCount++;
		if (player->HasSkill(SKILL_HERBALISM))
			skillCount++;

		if (skillCount >= 2)
			return true;

		for (uint32 i = 1; i < sSkillLineStore.GetNumRows(); ++i)
		{
			SkillLineEntry const *SkillInfo = sSkillLineStore.LookupEntry(i);
			if (!SkillInfo)
				continue;

			if (SkillInfo->categoryId == SKILL_CATEGORY_SECONDARY)
				continue;

			if ((SkillInfo->categoryId != SKILL_CATEGORY_PROFESSION) || !SkillInfo->canLink)
				continue;

			const uint32 skillID = SkillInfo->id;
			if (player->HasSkill(skillID))
				skillCount++;

			if (skillCount >= 2)
				return true;
		}
		return false;
	}
	bool IsSecondarySkill(SkillType skill) const
	{
		return skill == SKILL_COOKING || skill == SKILL_FIRST_AID;
	}
	bool CompleteLearnProfession(PjInfo pjinfo, Creature *creature, SkillType skill)
	{
		Player* player = pjinfo.player;
		if (PlayerAlreadyHasTwoProfessions(pjinfo) && !IsSecondarySkill(skill)){
			player->SendChatMessage("Ya tienes 2 professiones en este personaje!");
			return false;
		}
		else
		{
			if (!LearnAllRecipesInProfession(pjinfo, skill))
				player->SendChatMessage("Error interno #405");
			return true;
		}
	}
	bool LearnAllRecipesInProfession(PjInfo pjinfo, SkillType skill)
	{
		Player* player = pjinfo.player;
		ChatHandler handler(player->GetSession());
		char* skill_name;

		SkillLineEntry const *SkillInfo = sSkillLineStore.LookupEntry(skill);
		skill_name = SkillInfo->name[handler.GetSessionDbcLocale()];

		if (!SkillInfo)
		{
			player->SendChatMessage("NPC Promo: Error #418");
			return false;
		}

		LearnSkillRecipesHelper(pjinfo, SkillInfo->id);

		player->SetSkill(SkillInfo->id, player->GetSkillStep(SkillInfo->id), 450, 450);
		handler.PSendSysMessage(LANG_COMMAND_LEARN_ALL_RECIPES, skill_name);
		spromo->RegistrarProfe(pjinfo, skill);
		return true;
	}
	void LearnSkillRecipesHelper(PjInfo pjinfo, uint32 skill_id)
	{
		Player* player = pjinfo.player;
		uint32 classmask = player->getClassMask();
		for (uint32 j = 0; j < sSkillLineAbilityStore.GetNumRows(); ++j)
		{
			SkillLineAbilityEntry const *skillLine = sSkillLineAbilityStore.LookupEntry(j);
			if (!skillLine)
				continue;
			if (skillLine->skillId != skill_id)
				continue;
			if (skillLine->forward_spellid)
				continue;
			if (skillLine->racemask != 0)
				continue;
			if (skillLine->classmask && (skillLine->classmask & classmask) == 0)
				continue;

			SpellInfo const * spellInfo = sSpellMgr->GetSpellInfo(skillLine->spellId);
			if (!spellInfo || !SpellMgr::IsSpellValid(spellInfo, player, false))
				continue;

			player->LearnSpell(skillLine->spellId, false);
		}
	}
	bool AprenderSkills(PjInfo pjinfo, uint32 actions, Creature* creature)
	{
		Player* player = pjinfo.player;
		WorldSession * PGS = player->GetSession();
		//player->PlayerTalkClass->ClearMenus();
		{
			//      /**DUAL SPEC*////////////////////////////////////////////////
			//player->CastSpell(player, 63680, true, NULL, NULL, player->GetGUID());
			//player->CastSpell(player, 63624, true, NULL, NULL, player->GetGUID());
			//      /**//////////////////////////////////////////////////////////
			switch (actions)
			{
				//=============================================WARRIOR=================================================//
			case MENU_WARRIOR:
				SkillsLearn(pjinfo);
				player->LearnSpell(war_spell_Overpower, false),
				player->LearnSpell(war_spell_Battle_Shout, false),
				player->LearnSpell(war_spell_Heroic_Strike, false),
				player->LearnSpell(war_spell_Charge, false),
				player->LearnSpell(war_spell_Rend, false),
				player->LearnSpell(war_spell_Thunder_Clap, false),
				player->LearnSpell(war_spell_Victory_Rush, false),
				player->LearnSpell(war_spell_Hamstring, false),
				player->LearnSpell(war_spell_Bloodrage, false),
				player->LearnSpell(war_spell_Defensive_Stance, false),
				player->LearnSpell(war_spell_Sunder_Armor, false),
				player->LearnSpell(war_spell_Taunt, false),
				player->LearnSpell(war_spell_Shield_Bash, false),
				player->LearnSpell(war_spell_Demoralizing_Shout, false),
				player->LearnSpell(war_spell_Revenge, false),
				player->LearnSpell(war_spell_Mocking_Blow, false),
				player->LearnSpell(war_spell_Shield_Block, false),
				player->LearnSpell(war_spell_Disarm, false),
				player->LearnSpell(war_spell_Cleave, false),
				player->LearnSpell(war_spell_Retaliation, false),
				player->LearnSpell(war_spell_Stance_Mastery, false),
				player->LearnSpell(war_spell_Execute, false),
				player->LearnSpell(war_spell_Challenging_Shout, false),
				player->LearnSpell(war_spell_Shield_Wall, false),
				player->LearnSpell(war_spell_Berserker_Stance, false),
				player->LearnSpell(war_spell_Intercept, false),
				player->LearnSpell(war_spell_Slam, false),
				player->LearnSpell(war_spell_Berserker_Rage, false),
				player->LearnSpell(war_spell_Whirlwind, false),
				player->LearnSpell(war_spell_Pummel, false),
				player->LearnSpell(war_spell_Sheild_Slam, false),
				player->LearnSpell(war_spell_Recklessness, false),
				player->LearnSpell(war_spell_Spell_Reflection, false),
				player->LearnSpell(war_spell_Commanding_Shout, false),
				player->LearnSpell(war_spell_Intervene, false),
				player->LearnSpell(war_spell_Shattering_Throw, false),
				player->LearnSpell(war_spell_Enraged_Regeneration, false),
				player->LearnSpell(war_spell_Heroic_Throw, false),
				player->LearnSpell(war_spell_Dual_Wield, false),
				player->LearnSpell(war_spell_Intimidating_Shout, false);
				player->LearnSpell(war_spell_Parry, false);
				player->LearnSpell(54197, false); // ?
				/////////WEAPON/////////////
				player->LearnSpell(750, false); // ?
				player->LearnSpell(196, false); // ?
				player->LearnSpell(197, false); // ?
				player->LearnSpell(198, false); // ?
				player->LearnSpell(199, false); // ?
				player->LearnSpell(200, false); // ?
				player->LearnSpell(201, false); // ?
				player->LearnSpell(202, false); // ?
				player->LearnSpell(264, false); // ?
				player->LearnSpell(5011, false); // ?
				player->LearnSpell(266, false); // ?
				player->LearnSpell(2567, false); // ?
				player->UpdateSkillsToMaxSkillsForLevel();
				player->SaveToDB();
				player->PlayerTalkClass->SendCloseGossip();
				break;
				//=============================================PALADIN=================================================//
			case MENU_PALADIN:
				SkillsLearn(pjinfo);
				player->LearnSpell(pala_spell_Parry, false);
				player->LearnSpell(pala_spell_Concentration_Aura, false);
				player->LearnSpell(pala_spell_Divine_Intervention, false);
				player->LearnSpell(pala_spell_Plate_Mail_skill, false);
				player->LearnSpell(pala_spell_Devotion_Aura, false);
				player->LearnSpell(pala_spell_Holy_Light, false);
				player->LearnSpell(pala_spell_Blessing_of_Might, false);
				player->LearnSpell(pala_spell_Judgement_of_Light, false);
				player->LearnSpell(pala_spell_Divine_Protection, false);
				player->LearnSpell(pala_spell_Hammer_of_Justice, false);
				player->LearnSpell(pala_spell_Purify, false);
				player->LearnSpell(pala_spell_Hand_of_Protection, false);
				player->LearnSpell(pala_spell_Lay_on_Hands, false);
				player->LearnSpell(pala_spell_Judgement_of_Wisdom, false);
				player->LearnSpell(pala_spell_Redemption, false);
				player->LearnSpell(pala_spell_Blessing_of_Wisdom, false);
				player->LearnSpell(pala_spell_Righteous_Defense, false);
				player->LearnSpell(pala_spell_Hand_of_Reckoning, false);
				player->LearnSpell(pala_spell_Retribution_Aura, false);
				player->LearnSpell(pala_spell_Righteous_Fury, false);
				player->LearnSpell(pala_spell_Hand_of_Freedom, false);
				player->LearnSpell(pala_spell_Blessing_of_Kings, false);
				player->LearnSpell(pala_spell_Consecration, false);
				player->LearnSpell(pala_spell_Exorcism, false);
				player->LearnSpell(pala_spell_Flash_of_Light, false);
				player->LearnSpell(pala_spell_Sense_Undead, false);
				player->LearnSpell(pala_spell_Seal_of_Justice, false);
				player->LearnSpell(pala_spell_Turn_Evil, false);
				player->LearnSpell(pala_spell_Hand_of_Salvation, false);
				player->LearnSpell(pala_spell_Judgement_of_Justice, false);
				player->LearnSpell(pala_spell_Shadow_Resistance_Aura, false);
				player->LearnSpell(pala_spell_Seal_of_Light, false);
				player->LearnSpell(pala_spell_Frost_Resistance_Aura, false);
				player->LearnSpell(pala_spell_Divine_Shield, false);
				player->LearnSpell(pala_spell_Fire_Resistance_Aura, false);
				player->LearnSpell(pala_spell_Seal_of_Wisdom, false);
				player->LearnSpell(pala_spell_Cleanse, false);
				player->LearnSpell(pala_spell_Hammer_of_Wrath, false);
				player->LearnSpell(pala_spell_Hand_of_Sacrifice, false);
				player->LearnSpell(pala_spell_Holy_Wrath, false);
				player->LearnSpell(pala_spell_Greater_Blessing_of_Might, false);
				player->LearnSpell(pala_spell_Greater_Blessing_of_Wisdom, false);
				player->LearnSpell(pala_spell_Greater_Blessing_of_Kings, false);
				player->LearnSpell(pala_spell_Crusader_Aura, false);
				player->LearnSpell(pala_spell_Avenging_Wrath, false);
				player->LearnSpell(pala_spell_Divine_Plea, false);
				player->LearnSpell(pala_spell_Shield_of_Righteousness, false);
				player->LearnSpell(pala_spell_Sacred_Shield, false);
				player->LearnSpell(33388, false); //?
				player->LearnSpell(33391, false); //?
				/////////WEAPONS/////////////
				player->LearnSpell(750, false); //?
				player->LearnSpell(196, false); //?
				player->LearnSpell(197, false); //?
				player->LearnSpell(198, false); //?
				player->LearnSpell(199, false); //?
				player->LearnSpell(200, false); //?
				player->LearnSpell(201, false); //?
				player->LearnSpell(202, false); //?                    
				//Spell Learned for different factions..
				if (player->GetTeam() == ALLIANCE){
					player->LearnSpell(pala_spell_Seal_of_Vengeance, false);
					player->LearnSpell(pala_spell_Warhorse, false);
					player->LearnSpell(pala_spell_Charger, false);
				}
				else
				{
					player->LearnSpell(pala_spell_Seal_of_Corruption, false);
					player->LearnSpell(pala_spell_Thalassian_Warhorse, false);
					player->LearnSpell(pala_spell_Thalassian_Charger, false);
				}
				player->UpdateSkillsToMaxSkillsForLevel();
				player->SaveToDB();
				player->PlayerTalkClass->SendCloseGossip();
				break;
				//=============================================HUNTER=================================================//
			case MENU_HUNTER:
				SkillsLearn(pjinfo);
				player->LearnSpell(hunter_spell_Scorpid_Sting, false);
				player->LearnSpell(hunter_spell_Parry, false);
				player->LearnSpell(hunter_spell_Rapid_Fire, false);
				player->LearnSpell(hunter_spell_Viper_Sting, false);
				player->LearnSpell(hunter_spell_Track_Beasts, false);
				player->LearnSpell(hunter_spell_Aspect_of_the_Monkey, false);
				player->LearnSpell(hunter_spell_Raptor_Strike, false);
				player->LearnSpell(hunter_spell_Serpent_Sting, false);
				player->LearnSpell(hunter_spell_Arcane_Shot, false);
				player->LearnSpell(hunter_spell_Hunters_Mark, false);
				player->LearnSpell(hunter_spell_Concussive_Shot, false);
				player->LearnSpell(hunter_spell_Aspect_of_the_Hawk, false);
				player->LearnSpell(hunter_spell_Call_Pet, false);
				player->LearnSpell(hunter_spell_Dismiss_Pet, false);
				player->LearnSpell(hunter_spell_Feed_Pet, false);
				player->LearnSpell(hunter_spell_Revive_Pet, false);
				player->LearnSpell(hunter_spell_Tame_Beast, false);
				player->LearnSpell(hunter_spell_Track_Humanoids, false);
				player->LearnSpell(hunter_spell_Distracting_Shot, false);
				player->LearnSpell(hunter_spell_Mend_Pet, false);
				player->LearnSpell(hunter_spell_Wing_Clip, false);
				player->LearnSpell(hunter_spell_Eagle_Eye, false);
				player->LearnSpell(hunter_spell_Eyes_of_the_Beast, false);
				player->LearnSpell(hunter_spell_Scare_Beast, false);
				player->LearnSpell(hunter_spell_Aspect_of_the_Cheetah, false);
				player->LearnSpell(hunter_spell_Immolation_Trap, false);
				player->LearnSpell(hunter_spell_Mongoose_Bite, false);
				player->LearnSpell(hunter_spell_Multi_Shot, false);
				player->LearnSpell(hunter_spell_Track_Undead, false);
				player->LearnSpell(hunter_spell_Aspect_of_the_Viper, false);
				player->LearnSpell(hunter_spell_Disengage, false);
				player->LearnSpell(hunter_spell_Freezing_Trap, false);
				player->LearnSpell(hunter_spell_Beast_Lore, false);
				player->LearnSpell(hunter_spell_Track_Hidden, false);
				player->LearnSpell(hunter_spell_Track_Elementals, false);
				player->LearnSpell(hunter_spell_Frost_Trap, false);
				player->LearnSpell(hunter_spell_Aspect_of_the_Beast, false);
				player->LearnSpell(hunter_spell_Feign_Death, false);
				player->LearnSpell(hunter_spell_Flare, false);
				player->LearnSpell(hunter_spell_Track_Demons, false);
				player->LearnSpell(hunter_spell_Explosive_Trap, false);
				player->LearnSpell(hunter_spell_Aspect_of_the_Pack, false);
				player->LearnSpell(hunter_spell_Track_Giants, false);
				player->LearnSpell(hunter_spell_Volley, false);
				player->LearnSpell(hunter_spell_Aspect_of_the_Wild, false);
				player->LearnSpell(hunter_spell_Steady_Shot, false);
				player->LearnSpell(hunter_spell_Track_Dragonkin, false);
				player->LearnSpell(hunter_spell_Deterrence, false);
				player->LearnSpell(hunter_spell_Tranquilizing_Shot, false);
				player->LearnSpell(hunter_spell_Kill_Command, false);
				player->LearnSpell(hunter_spell_Snake_Trap, false);
				player->LearnSpell(hunter_spell_Misdirection, false);
				player->LearnSpell(hunter_spell_Kill_Shot, false);
				player->LearnSpell(hunter_spell_Aspect_of_the_Dragonhawk, false);
				player->LearnSpell(hunter_spell_Masters_Call, false);
				player->LearnSpell(hunter_spell_Freezing_Arrow, false);
				player->LearnSpell(hunter_spell_Call_Stabled_Pet, false);
				player->LearnSpell(hunter_spell_Dual_Wield, false);
				player->LearnSpell(8737, false); //?
				/////////ARRMES/////////////
				player->LearnSpell(15590, false); //?
				player->LearnSpell(8737, false); //?
				player->LearnSpell(196, false); //?
				player->LearnSpell(197, false); //?
				player->LearnSpell(200, false); //?
				player->LearnSpell(201, false); //?
				player->LearnSpell(202, false); //?
				player->LearnSpell(264, false); //?
				player->LearnSpell(266, false); //?
				player->LearnSpell(5011, false); //?
				player->UpdateSkillsToMaxSkillsForLevel();
				player->SaveToDB();
				player->PlayerTalkClass->SendCloseGossip();
				break;
				//=============================================ROGUE=================================================//
			case MENU_ROGUE:
				SkillsLearn(pjinfo);
				player->LearnSpell(rogue_spell_Parry, false);
				player->LearnSpell(rogue_spell_Dual_Wield, false); //  ambi
				player->LearnSpell(rogue_spell_Eviscerate, false);
				player->LearnSpell(rogue_spell_Sinister_Strike, false);
				player->LearnSpell(rogue_spell_Stealth, false);
				player->LearnSpell(rogue_spell_Backstab, false);
				player->LearnSpell(rogue_spell_Pick_Pocket, false);
				player->LearnSpell(rogue_spell_Gouge, false);
				player->LearnSpell(rogue_spell_Evasion, false);
				player->LearnSpell(rogue_spell_Sap, false);
				player->LearnSpell(rogue_spell_Slice_and_Dice, false);
				player->LearnSpell(rogue_spell_Sprint, false);
				player->LearnSpell(rogue_spell_Kick, false);
				player->LearnSpell(rogue_spell_Garrote, false);
				player->LearnSpell(rogue_spell_Feint, false);
				player->LearnSpell(rogue_spell_Lockpicking_skill, false);
				player->LearnSpell(rogue_spell_Expose_Armor, false);
				player->LearnSpell(rogue_spell_Ambush, false);
				player->LearnSpell(rogue_spell_Dismantle, false);
				player->LearnSpell(rogue_spell_Rupture, false);
				player->LearnSpell(rogue_spell_Distract, false);
				player->LearnSpell(rogue_spell_Vanish, false);
				player->LearnSpell(rogue_spell_Detect_Traps, false);
				player->LearnSpell(rogue_spell_Cheap_Shot, false);
				player->LearnSpell(rogue_spell_Disarm_Trap, false);
				player->LearnSpell(rogue_spell_Kidney_Shot, false);
				player->LearnSpell(rogue_spell_Blind, false);
				player->LearnSpell(rogue_spell_Safe_Fall, false);
				player->LearnSpell(rogue_spell_Envenom, false);
				player->LearnSpell(rogue_spell_Deadly_Throw, false);
				player->LearnSpell(rogue_spell_Cloak_of_Shadows, false);
				player->LearnSpell(rogue_spell_Shiv, false);
				player->LearnSpell(rogue_spell_Tricks_of_the_Trade, false);
				player->LearnSpell(rogue_spell_Fan_of_Knives, false);
				///////////WEAPON/////////////
				player->LearnSpell(196, false); //?
				player->LearnSpell(198, false); //?
				player->LearnSpell(201, false); //?
				player->LearnSpell(1180, false); //?
				player->LearnSpell(2567, false); //?
				player->LearnSpell(264, false); //?
				player->LearnSpell(266, false); //?
				player->LearnSpell(5011, false); //?
				player->LearnSpell(15590, false); //?
				//======================================//
				player->UpdateSkillsToMaxSkillsForLevel();
				player->SaveToDB();
				player->PlayerTalkClass->SendCloseGossip();
				break;
			case MENU_PRIEST:
				SkillsLearn(pjinfo);
				player->LearnSpell(priest_spell_Cure_Disease, false);
				player->LearnSpell(priest_spell_Lesser_Heal, false);
				player->LearnSpell(priest_spell_Power_Word_Fortitude, false);
				player->LearnSpell(priest_spell_Smite, false);
				player->LearnSpell(priest_spell_Shadow_Word_Pain, false);
				player->LearnSpell(priest_spell_Power_Word_Shield, false);
				player->LearnSpell(priest_spell_Fade, false);
				player->LearnSpell(priest_spell_Renew, false);
				player->LearnSpell(priest_spell_Mind_Blast, false);
				player->LearnSpell(priest_spell_Resurrection, false);
				player->LearnSpell(priest_spell_Inner_Fire, false);
				player->LearnSpell(priest_spell_Psychic_Scream, false);
				player->LearnSpell(priest_spell_Heal, false);
				player->LearnSpell(priest_spell_Dispel_Magic, false);
				player->LearnSpell(priest_spell_Devouring_Plague, false);
				player->LearnSpell(priest_spell_Fear_Ward, false);
				player->LearnSpell(priest_spell_Flash_Heal, false);
				player->LearnSpell(priest_spell_Holy_Fire, false);
				player->LearnSpell(priest_spell_Holy_Nova, false);
				player->LearnSpell(priest_spell_Mind_Soothe, false);
				player->LearnSpell(priest_spell_Shackle_Undead, false);
				player->LearnSpell(priest_spell_Mind_Vision, false);
				player->LearnSpell(priest_spell_Mana_Burn, false);
				player->LearnSpell(priest_spell_Divine_Spirit, false);
				player->LearnSpell(priest_spell_Mind_Control, false);
				player->LearnSpell(priest_spell_Prayer_of_Healing, false);
				player->LearnSpell(priest_spell_Shadow_Protection, false);
				player->LearnSpell(priest_spell_Abolish_Disease, false);
				player->LearnSpell(priest_spell_Levitate, false);
				player->LearnSpell(priest_spell_Greater_Heal, false);
				player->LearnSpell(priest_spell_Prayer_of_Fortitude, false);
				player->LearnSpell(priest_spell_Prayer_of_Shadow_Protection, false);
				player->LearnSpell(priest_spell_Prayer_of_Spirit, false);
				player->LearnSpell(priest_spell_Shadow_Word_Death, false);
				player->LearnSpell(priest_spell_Binding_Heal, false);
				player->LearnSpell(priest_spell_Shadowfiend, false);
				player->LearnSpell(priest_spell_Prayer_of_Mending, false);
				player->LearnSpell(priest_spell_Mass_Dispel, false);
				player->LearnSpell(priest_spell_Divine_Hymn, false);
				player->LearnSpell(priest_spell_Hymn_of_Hope, false);
				player->LearnSpell(priest_spell_Mind_Sear, false);
				///////////WEAPON/////////////
				player->LearnSpell(196, false); //?
				player->LearnSpell(198, false); //?
				player->LearnSpell(227, false); //?
				player->LearnSpell(1180, false); //?
				player->UpdateSkillsToMaxSkillsForLevel();
				player->SaveToDB();
				player->PlayerTalkClass->SendCloseGossip();
				break;
				//=============================================DEATH KNGIHTS=================================================//
			case MENU_DEATH_K:
				SkillsLearn(pjinfo);
				player->LearnSpell(dk_spell_Parry, false);
				player->LearnSpell(dk_spell_Pestilence, false);
				player->LearnSpell(dk_spell_Blood_Boil, false);
				player->LearnSpell(dk_spell_Blood_Strike, false);
				player->LearnSpell(dk_spell_Strangulate, false);
				player->LearnSpell(dk_spell_Blood_Tap, false);
				player->LearnSpell(dk_spell_Path_of_Frost, false);
				player->LearnSpell(dk_spell_Dark_Command, false);
				player->LearnSpell(dk_spell_Death_Pact, false);
				player->LearnSpell(dk_spell_Frost_Presence, false);
				player->LearnSpell(dk_spell_Icy_Touch, false);
				player->LearnSpell(dk_spell_Mind_Freeze, false);
				player->LearnSpell(dk_spell_Chains_of_Ice, false);
				player->LearnSpell(dk_spell_Icebound_Fortitude, false);
				player->LearnSpell(dk_spell_Horn_of_Winter, false);
				player->LearnSpell(dk_spell_Rune_Strike, false);
				player->LearnSpell(dk_spell_Empower_Rune_Weapon, false);
				player->LearnSpell(dk_spell_Death_Coil, false);
				player->LearnSpell(dk_spell_Death_Gate, false);
				player->LearnSpell(dk_spell_Plague_Strike, false);
				player->LearnSpell(dk_spell_Death_Grip, false);
				player->LearnSpell(dk_spell_Raise_Dead, false);
				player->LearnSpell(dk_spell_Death_and_Decay, false);
				player->LearnSpell(dk_spell_Anti_Magic_Shell, false);
				player->LearnSpell(dk_spell_Unholy_Presence, false);
				player->LearnSpell(dk_spell_Raise_Ally, false);
				player->LearnSpell(dk_spell_Army_of_the_Dead, false);
				player->LearnSpell(dk_spell_Runeforging_skill, false);
				player->LearnSpell(dk_spell_Acherus_Deathcharger, false);
				player->LearnSpell(dk_spell_Obliterate, false);
				player->LearnSpell(dk_spell_Death_Strike, false);
				player->LearnSpell(war_spell_Dual_Wield, false);
				//================RuneForge================//
				player->LearnSpell(dk_spell_Uknowas, false);
				player->LearnSpell(dk_spell_Uknowah, false);
				player->LearnSpell(dk_spell_Uknowai, false);
				player->LearnSpell(dk_spell_Uknowaz, false);
				player->LearnSpell(dk_spell_Uknowan, false);
				player->LearnSpell(dk_spell_Uknowab, false);
				player->LearnSpell(dk_spell_Uknowav, false);
				player->LearnSpell(dk_spell_Uknowaj, false);
				player->LearnSpell(dk_spell_Uknowaq, false);
				///////////WEAPON/////////////
				player->LearnSpell(750, false);
				player->LearnSpell(196, false);
				player->LearnSpell(197, false);
				player->LearnSpell(198, false);
				player->LearnSpell(199, false);
				player->LearnSpell(200, false);
				player->LearnSpell(201, false);
				player->LearnSpell(202, false);
				player->UpdateSkillsToMaxSkillsForLevel();
				player->SaveToDB();
				player->PlayerTalkClass->SendCloseGossip();
				break;
				//=============================================SHAMAN=================================================//
			case MENU_SHAMAN:
				SkillsLearn(pjinfo);
				player->LearnSpell(8737, false);//?
				player->LearnSpell(shaman_spell_Earth_Elemental_Totem, false);
				player->LearnSpell(shaman_spell_Healing_Wave, false);
				player->LearnSpell(shaman_spell_Lightning_Bolt, false);
				player->LearnSpell(shaman_spell_Rockbiter_Weapon, false);
				player->LearnSpell(shaman_spell_Earth_Shock, false);
				player->LearnSpell(shaman_spell_Stoneskin_Totem, false);
				player->LearnSpell(shaman_spell_Earthbind_Totem, false);
				player->LearnSpell(shaman_spell_Lightning_Shield, false);
				player->LearnSpell(shaman_spell_Stoneclaw_Totem, false);
				player->LearnSpell(shaman_spell_Flame_Shock, false);
				player->LearnSpell(shaman_spell_Flametongue_Weapon, false);
				player->LearnSpell(shaman_spell_Searing_Totem, false);
				player->LearnSpell(shaman_spell_Strength_of_Earth_Totem, false);
				player->LearnSpell(shaman_spell_Ancestral_Spirit, false);
				player->LearnSpell(shaman_spell_Fire_Nova, false);
				player->LearnSpell(shaman_spell_Purge, false);
				player->LearnSpell(shaman_spell_Cure_Toxins, false);
				player->LearnSpell(shaman_spell_Ghost_Wolf, false);
				player->LearnSpell(shaman_spell_Wind_Shear, false);
				player->LearnSpell(shaman_spell_Tremor_Totem, false);
				player->LearnSpell(shaman_spell_Frost_Shock, false);
				player->LearnSpell(shaman_spell_Frostbrand_Weapon, false);
				player->LearnSpell(shaman_spell_Healing_Stream_Totem, false);
				player->LearnSpell(shaman_spell_Lesser_Healing_Wave, false);
				player->LearnSpell(shaman_spell_Water_Shield, false);
				player->LearnSpell(shaman_spell_Water_Breathing, false);
				player->LearnSpell(shaman_spell_Frost_Resistance_Totem, false);
				player->LearnSpell(shaman_spell_Far_Sight, false);
				player->LearnSpell(shaman_spell_Magma_Totem, false);
				player->LearnSpell(shaman_spell_Mana_Spring_Totem, false);
				player->LearnSpell(shaman_spell_Fire_Resistance_Totem, false);
				player->LearnSpell(shaman_spell_Flametongue_Totem, false);
				player->LearnSpell(shaman_spell_Water_Walking, false);
				player->LearnSpell(shaman_spell_Astral_Recall, false);
				player->LearnSpell(shaman_spell_Call_of_the_Elements, false);
				player->LearnSpell(shaman_spell_Earthliving_Weapon, false);
				player->LearnSpell(shaman_spell_Grounding_Totem, false);
				player->LearnSpell(shaman_spell_Nature_Resistance_Totem, false);
				player->LearnSpell(shaman_spell_Reincarnation, false);
				player->LearnSpell(shaman_spell_Totemic_Recall, false);
				player->LearnSpell(shaman_spell_Windfury_Weapon, false);
				player->LearnSpell(shaman_spell_Chain_Lightning, false);
				player->LearnSpell(shaman_spell_Windfury_Totem, false);
				player->LearnSpell(shaman_spell_Sentry_Totem, false);
				player->LearnSpell(shaman_spell_Cleansing_Totem, false);
				player->LearnSpell(shaman_spell_Call_of_the_Ancestors, false);
				player->LearnSpell(shaman_spell_Chain_Heal, false);
				player->LearnSpell(shaman_spell_Call_of_the_Spirits, false);
				player->LearnSpell(shaman_spell_Wrath_of_Air_Totem, false);
				player->LearnSpell(shaman_spell_Fire_Elemental_Totem, false);
				player->LearnSpell(shaman_spell_Lava_Burst, false);
				player->LearnSpell(shaman_spell_Hex, false);
				///////////WEAPONS/////////////
				player->LearnSpell(8737, false);
				player->LearnSpell(196, false);
				player->LearnSpell(197, false);
				player->LearnSpell(198, false);
				player->LearnSpell(199, false);
				player->LearnSpell(227, false);
				player->LearnSpell(1180, false);
				player->LearnSpell(15590, false);
				//Faction
				if (player->GetTeam() == ALLIANCE){
					player->LearnSpell(shaman_spell_Heroism, false);
				}
				else
				{
					player->LearnSpell(shaman_spell_Bloodlust, false);
				}
				player->UpdateSkillsToMaxSkillsForLevel();
				player->SaveToDB();
				player->PlayerTalkClass->SendCloseGossip();
				break;
				//=============================================MAGE=================================================//
			case MENU_MAGE:
				SkillsLearn(pjinfo);
				player->LearnSpell(mage_spell_Arcane_Explosion, false);
				player->LearnSpell(mage_spell_Frostbolt, false);
				player->LearnSpell(mage_spell_Arcane_Intellect, false);
				player->LearnSpell(mage_spell_Fireball, false);
				player->LearnSpell(mage_spell_Conjure_Water, false);
				player->LearnSpell(mage_spell_Conjure_Food, false);
				player->LearnSpell(mage_spell_Fire_Blast, false);
				player->LearnSpell(mage_spell_Arcane_Missiles, false);
				player->LearnSpell(mage_spell_Polymorph, false);
				player->LearnSpell(mage_spell_Polymorph_Turtle, false);
				player->LearnSpell(mage_spell_Polymorph_Turkey, false);
				player->LearnSpell(mage_spell_Polymorph_Rabbit, false);
				player->LearnSpell(mage_spell_Polymorph_Pig, false);
				player->LearnSpell(mage_spell_Frost_Nova, false);
				player->LearnSpell(mage_spell_Dampen_Magic, false);
				player->LearnSpell(mage_spell_Slow_Fall, false);
				player->LearnSpell(mage_spell_Flamestrike, false);
				player->LearnSpell(mage_spell_Amplify_Magic, false);
				player->LearnSpell(mage_spell_Remove_Curse, false);
				player->LearnSpell(mage_spell_Blink, false);
				player->LearnSpell(mage_spell_Blizzard, false);
				player->LearnSpell(mage_spell_Evocation, false);
				player->LearnSpell(mage_spell_Fire_Ward, false);
				player->LearnSpell(mage_spell_Mana_Shield, false);
				player->LearnSpell(mage_spell_Frost_Ward, false);
				player->LearnSpell(mage_spell_Scorch, false);
				player->LearnSpell(mage_spell_Counterspell, false);
				player->LearnSpell(mage_spell_Cone_of_Cold, false);
				player->LearnSpell(mage_spell_Conjure_Mana_Gem, false);
				player->LearnSpell(mage_spell_Ice_Armor, false);
				player->LearnSpell(mage_spell_Ice_Block, false);
				player->LearnSpell(mage_spell_Mage_Armor, false);
				player->LearnSpell(mage_spell_Arcane_Brilliance, false);
				player->LearnSpell(mage_spell_Molten_Armor, false);
				player->LearnSpell(mage_spell_Arcane_Blast, false);
				player->LearnSpell(mage_spell_Ice_Lance, false);
				player->LearnSpell(mage_spell_Invisibility, false);
				player->LearnSpell(mage_spell_Ritual_of_Refreshment, false);
				player->LearnSpell(mage_spell_Spellsteal, false);
				player->LearnSpell(mage_spell_Conjure_Refreshment, false);
				player->LearnSpell(mage_spell_Frostfire_Bolt, false);
				player->LearnSpell(mage_spell_Dalaran_Brilliance, false);
				player->LearnSpell(mage_spell_Dalaran_Intellect, false);
				player->LearnSpell(mage_spell_Mirror_Image, false);
				player->LearnSpell(mage_spell_Portal_Dalaran, false);
				player->LearnSpell(mage_spell_Frost_Armor, false);
				player->LearnSpell(61305, false);//?
				player->SaveToDB();
				/////////WEAPON/////////////
				player->LearnSpell(201, false); //?
				player->LearnSpell(196, false); //?
				player->LearnSpell(227, false); //?
				player->LearnSpell(1180, false); //?
				player->SaveToDB();
				/////////RESTRICTION/////////////
				if (player->GetTeam() == ALLIANCE){
					player->LearnSpell(mage_spell_Teleport_Exodar, false);
					player->LearnSpell(mage_spell_Teleport_Theramore, false);
					player->LearnSpell(mage_spell_Teleport_Darnassus, false);
					player->LearnSpell(mage_spell_Teleport_Shattrath, false);
					player->LearnSpell(mage_spell_Teleport_Ironforge, false);
					player->LearnSpell(mage_spell_Teleport_Stromwind, false);
					player->LearnSpell(mage_spell_Portal_Darnassus, false);
					player->LearnSpell(mage_spell_Portal_Exodar, false);
					player->LearnSpell(mage_spell_Portal_Ironforge, false);
					player->LearnSpell(mage_spell_Portal_Shattrath, false);
					player->LearnSpell(mage_spell_Portal_Theramore, false);
				}
				else{
					player->LearnSpell(mage_spell_Teleport_Orgrimmar, false);
					player->LearnSpell(mage_spell_Teleport_Shattrath_H, false);
					player->LearnSpell(mage_spell_Teleport_Thunder_Bluff, false);
					player->LearnSpell(mage_spell_Teleport_Stonard, false);
					player->LearnSpell(mage_spell_Teleport_Silvermoon, false);
					player->LearnSpell(mage_spell_Teleport_Undercity, false);
					player->LearnSpell(mage_spell_Portal_Orgrimmar, false);
					player->LearnSpell(mage_spell_Portal_Shattrath_H, false);
					player->LearnSpell(mage_spell_Portal_Silvermoon, false);
					player->LearnSpell(mage_spell_Portal_Stonard, false);
					player->LearnSpell(mage_spell_Portal_Thunder_Bluff, false);
					player->LearnSpell(mage_spell_Portal_Undercity, false);
				}
				player->UpdateSkillsToMaxSkillsForLevel();
				player->SaveToDB();
				player->PlayerTalkClass->SendCloseGossip();
				break;
				//=============================================WARLOCK=================================================//
			case MENU_WARLOCK:
				SkillsLearn(pjinfo);
				player->LearnSpell(warlock_spell_Demon_Skin, false);
				player->LearnSpell(warlock_spell_Immolate, false);
				player->LearnSpell(warlock_spell_Shadow_Bolt, false);
				player->LearnSpell(warlock_spell_Summon_Imp, false);
				player->LearnSpell(warlock_spell_Corruption, false);
				player->LearnSpell(warlock_spell_Curse_of_Weakness, false);
				player->LearnSpell(warlock_spell_Life_Tap, false);
				player->LearnSpell(warlock_spell_Curse_of_Agony, false);
				player->LearnSpell(warlock_spell_Fear, false);
				player->LearnSpell(warlock_spell_Create_Healthstone, false);
				player->LearnSpell(warlock_spell_Drain_Soul, false);
				player->LearnSpell(warlock_spell_Summon_Voidwalker, false);
				player->LearnSpell(warlock_spell_Health_Funnel, false);
				player->LearnSpell(warlock_spell_Drain_Life, false);
				player->LearnSpell(warlock_spell_Unending_Breath, false);
				player->LearnSpell(warlock_spell_Create_Soulstone, false);
				player->LearnSpell(warlock_spell_Searing_Pain, false);
				player->LearnSpell(warlock_spell_Demon_Armor, false);
				player->LearnSpell(warlock_spell_Rain_of_Fire, false);
				player->LearnSpell(warlock_spell_Ritual_of_Summoning, false);
				player->LearnSpell(warlock_spell_Summon_Succubus, false);
				player->LearnSpell(warlock_spell_Eye_of_Kilrogg, false);
				player->LearnSpell(warlock_spell_Drain_Mana, false);
				player->LearnSpell(warlock_spell_Sense_Demons, false);
				player->LearnSpell(warlock_spell_Curse_of_Tongues, false);
				player->LearnSpell(warlock_spell_Detect_Invisibility, false);
				player->LearnSpell(warlock_spell_Create_Firestone, false);
				player->LearnSpell(warlock_spell_Banish, false);
				player->LearnSpell(warlock_spell_Enslave_Demon, false);
				player->LearnSpell(warlock_spell_Hellfire, false);
				player->LearnSpell(warlock_spell_Summon_Felhunter, false);
				player->LearnSpell(warlock_spell_Curse_of_the_Elements, false);
				player->LearnSpell(warlock_spell_Shadow_Ward, false);
				player->LearnSpell(warlock_spell_Create_Spellstone, false);
				player->LearnSpell(warlock_spell_Howl_of_Terror, false);
				player->LearnSpell(warlock_spell_Death_Coil, false);
				player->LearnSpell(warlock_spell_Soul_Fire, false);
				player->LearnSpell(warlock_spell_Inferno, false);
				player->LearnSpell(warlock_spell_Curse_of_Doom, false);
				player->LearnSpell(warlock_spell_Ritual_of_Doom, false);
				player->LearnSpell(warlock_spell_Fel_Armor, false);
				player->LearnSpell(warlock_spell_Incinerate, false);
				player->LearnSpell(warlock_spell_Soulshatter, false);
				player->LearnSpell(warlock_spell_Ritual_of_Souls, false);
				player->LearnSpell(warlock_spell_Seed_of_Corruption, false);
				player->LearnSpell(warlock_spell_Shadowflame, false);
				player->LearnSpell(warlock_spell_Demonic_Circle_Summon, false);
				player->LearnSpell(warlock_spell_Demonic_Circle_Teleport, false);
				player->LearnSpell(warlock_spell_Dreadsteed, false);
				player->LearnSpell(33388, false); //?
				player->LearnSpell(33391, false); //?
				///////////ARMES/////////////
				player->LearnSpell(196, false);//?
				player->LearnSpell(227, false);//?
				player->LearnSpell(1180, false);//?
				player->UpdateSkillsToMaxSkillsForLevel();
				player->SaveToDB();
				player->PlayerTalkClass->SendCloseGossip();
				break;
				//=============================================DRUID=================================================//
			case MENU_DRUID:
				if (player->getClass() == CLASS_DRUID)
				{
					SkillsLearn(pjinfo);
					player->LearnSpell(druid_spell_Healing_Touch, false);
					player->LearnSpell(druid_spell_Mark_of_the_Wild, false);
					player->LearnSpell(druid_spell_Wrath, false);
					player->LearnSpell(druid_spell_Moonfire, false);
					player->LearnSpell(druid_spell_Rejuvenation, false);
					player->LearnSpell(druid_spell_Thorns, false);
					player->LearnSpell(druid_spell_Entangling_Roots, false);
					player->LearnSpell(druid_spell_Bear_Form, false);
					player->LearnSpell(druid_spell_Demoralizing_Roar, false);
					player->LearnSpell(druid_spell_Growl, false);
					player->LearnSpell(druid_spell_Maul, false);
					player->LearnSpell(druid_spell_Natures_Grasp, false);
					player->LearnSpell(druid_spell_Teleport_Moonglade, false);
					player->LearnSpell(druid_spell_Enrage, false);
					player->LearnSpell(druid_spell_Regrowth, false);
					player->LearnSpell(druid_spell_Revive, false);
					player->LearnSpell(druid_spell_Bash, false);
					player->LearnSpell(druid_spell_Cure_Poison, false);
					player->LearnSpell(druid_spell_Aquatic_Form, false);
					player->LearnSpell(druid_spell_Swipe_Bear, false);
					player->LearnSpell(druid_spell_Travel_Form, false);
					player->LearnSpell(druid_spell_Faerie_Fire, false);
					player->LearnSpell(druid_spell_Faerie_Fire_Feral, false);
					player->LearnSpell(druid_spell_Hibernate, false);
					player->LearnSpell(druid_spell_Cat_Form, false);
					//      player->LearnSpell(druid_spell_Feral_Charge_Bear, false); // charge farouche 2
					//      player->LearnSpell(druid_spell_Feral_Charge_Cat, false); // charge farouche
					player->LearnSpell(druid_spell_Prowl, false);
					player->LearnSpell(druid_spell_Rebirth, false);
					player->LearnSpell(druid_spell_Rip, false);
					player->LearnSpell(druid_spell_Starfire, false);
					player->LearnSpell(druid_spell_Shred, false);
					player->LearnSpell(druid_spell_Soothe_Animal, false);
					player->LearnSpell(druid_spell_Rake, false);
					player->LearnSpell(druid_spell_Remove_Curse, false);
					player->LearnSpell(druid_spell_Tigers_Fury, false);
					player->LearnSpell(druid_spell_Abolish_Poison, false);
					player->LearnSpell(druid_spell_Dash, false);
					player->LearnSpell(druid_spell_Challenging_Roar, false);
					player->LearnSpell(druid_spell_Cower, false);
					player->LearnSpell(druid_spell_Tranquility, false);
					player->LearnSpell(druid_spell_Ferocious_Bite, false);
					player->LearnSpell(druid_spell_Ravage, false);
					player->LearnSpell(druid_spell_Track_Humanoids, false);
					player->LearnSpell(druid_spell_Frenzied_Regeneration, false);
					player->LearnSpell(druid_spell_Pounce, false);
					player->LearnSpell(druid_spell_Dire_Bear_Form, false);
					player->LearnSpell(druid_spell_Feline_Grace, false);
					player->LearnSpell(druid_spell_Hurricane, false);
					player->LearnSpell(druid_spell_Innervate, false);
					player->LearnSpell(druid_spell_Savage_Defense, false);
					player->LearnSpell(druid_spell_Barkskin, false);
					player->LearnSpell(druid_spell_Gift_of_the_Wild, false);
					//      player->LearnSpell(druid_spell_Mangle_Bear, false); mutilation farouche 2
					//      player->LearnSpell(druid_spell_Mangle_Cat, false); mutilation farouche
					player->LearnSpell(druid_spell_Flight_Form, false);
					player->LearnSpell(druid_spell_Maim, false);
					player->LearnSpell(druid_spell_Lifebloom, false);
					player->LearnSpell(druid_spell_Lacerate, false);
					player->LearnSpell(druid_spell_Cyclone, false);
					player->LearnSpell(druid_spell_Swift_Flight_Form, false);
					player->LearnSpell(druid_spell_Swipe_Cat, false);
					player->LearnSpell(druid_spell_Savage_Roar, false);
					player->LearnSpell(druid_spell_Nourish, false);
					player->LearnSpell(druid_spell_Claw, false);
					player->LearnSpell(druid_spell_Claw_1, false);//?
					///////////ARMES/////////////
					player->LearnSpell(198, false); //?
					player->LearnSpell(199, false); // ?
					player->LearnSpell(200, false); //?
					player->LearnSpell(227, false); //?
					player->SaveToDB();
				}
				player->UpdateSkillsToMaxSkillsForLevel();
				player->SaveToDB();
				player->PlayerTalkClass->SendCloseGossip();
				break;
			case OPTION_MENU_ID_1:
				player->ADD_GOSSIP_ITEM(TRAINER_ICON, SUB_MENU_TALENT_OPTION_1, GOSSIP_SENDER_MAIN, SUB_OPTION_MENU_ID_1);
				player->ADD_GOSSIP_ITEM(TRAINER_ICON, SUB_MENU_TALENT_OPTION_2, GOSSIP_SENDER_MAIN, SUB_OPTION_MENU_ID_2);
				player->ADD_GOSSIP_ITEM(CHAT_ICON, back, GOSSIP_SENDER_MAIN, BACK_OPTION_MENU_1);
				player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;

			case SUB_OPTION_MENU_ID_1:
				//=====WARRIOR TALENT=====//
				//Arms
				if (player->HasSpell(12294)) //Mortal Strike Rank 1
				{
					player->LearnSpell(war_spell_Mortal_Strike, false);
				}
				//Prot
				if (player->HasSpell(20243)) //Devastate Rank 1
				{
					player->LearnSpell(war_spell_Devastate, false);
				}
				//=====PALADIN TALENT=====//
				//Holy
				if (player->HasSpell(20925)) //Holy Shield Rank 1
				{
					player->LearnSpell(pala_spell_Holy_Shield, false);
				}
				if (player->HasSpell(20473)) //Holy Shock Rank 1
				{
					player->LearnSpell(pala_spell_Holy_Shock, false);
				}
				//Prot
				if (player->HasSpell(31935)) //Avengers Shield Rank 1
				{
					player->LearnSpell(pala_spell_Avengers_Shield, false);
				}
				if (player->HasSpell(20911)) //Blessing of Sanctuary Rank 1
				{
					player->LearnSpell(pala_spell_Greater_Blessing_of_Sanctuary, false);
				}
				//=====HUNTER  TALENT=====//
				//Survival
				if (player->HasSpell(19386)) //Wyvern String Rank 1
				{
					player->LearnSpell(hunter_spell_Wyvern_Sting, false);
				}
				if (player->HasSpell(53301)) //Explosive Shot Rank 1
				{
					player->LearnSpell(hunter_spell_Explosive_Shot, false);
				}
				if (player->HasSpell(19306)) //Conter Attack Rank 1
				{
					player->LearnSpell(hunter_spell_Conterattack, false);
				}
				//Marksmanship
				if (player->HasSpell(19434)) //Aimed Shot Rank 1
				{
					player->LearnSpell(hunter_spell_Aimed_Shot, false);
				}
				//=====ROGUE   TALENT=====//
				//Subtlety
				if (player->HasSpell(16511)) //Hemorrhage Rank 1
				{
					player->LearnSpell(rogue_spell_Hemorrhage, false);
				}
				//Assassination
				if (player->HasSpell(1329)) //Mutilate Rank 1
				{
					player->LearnSpell(rogue_spell_Mutilate, false);
				}
				//=====PRIEST  TALENT=====//
				//Shadow
				if (player->HasSpell(34914)) //Vampiric Touch Rank 1
				{
					player->LearnSpell(priest_spell_Vampiric_Touch, false);
				}
				//Discipline
				if (player->HasSpell(47540)) //Penance Rank 1
				{
					player->LearnSpell(priest_spell_Penance, false);
				}
				//Holy
				if (player->HasSpell(724)) //LightWell Rank 1
				{
					player->LearnSpell(priest_spell_Lightwell, false);
				}
				if (player->HasSpell(19236)) //Desperate Prayer Rank 1
				{
					player->LearnSpell(priest_spell_Desperate_Prayer, false);
				}
				if (player->HasSpell(34861)) //Circle Of healing Rank 1
				{
					player->LearnSpell(priest_spell_Circle_of_Healing, false);
				}
				//Shadow
				if (player->HasSpell(15407)) //Mind Flay Rank 1
				{
					player->LearnSpell(priest_spell_Mind_Flay, false);
				}
				//=====DEATH_K TALENT=====//
				//Blood
				if (player->HasSpell(55050)) //Heart Strike Rank 1
				{
					player->LearnSpell(dk_spell_Heart_Strike, false);
				}
				//Frost
				if (player->HasSpell(49143)) //Frost Strike Rank 1
				{
					player->LearnSpell(dk_spell_Frost_Strike, false);
				}
				if (player->HasSpell(49184)) //Howling Blast Rank 1
				{
					player->LearnSpell(dk_spell_Howling_Blast, false);
				}
				//UnHoly
				if (player->HasSpell(55090)) //Scourge Strike Rank 1
				{
					player->LearnSpell(dk_spell_Scourge_Strike, false);
				}
				if (player->HasSpell(49158)) //Corpse Explosion Rank 1
				{
					player->LearnSpell(dk_spell_Corpse_Explosion, false);
				}
				//=====SHAMAN  TALENT=====//
				//Restoration
				if (player->HasSpell(61295)) //Riptide Rank 1
				{
					player->LearnSpell(shaman_spell_Riptide, false);
				}
				if (player->HasSpell(974)) //Earth Shield Rank 1
				{
					player->LearnSpell(shaman_spell_Earth_Shield, false);
				}
				//Elemental
				if (player->HasSpell(30706)) //Totem of Wrath Rank 1
				{
					player->LearnSpell(shaman_spell_Totem_of_Wrath, false);
				}
				if (player->HasSpell(51490)) //TunderStorm Rank 1
				{
					player->LearnSpell(shaman_spell_Thunderstorm, false);
				}
				//=====MAGE    TALENT=====//
				//Arcane
				if (player->HasSpell(44425)) //Arcane Barrage Rank 1
				{
					player->LearnSpell(mage_spell_Arcane_Barrage, false);
				}
				//Fire
				if (player->HasSpell(11113)) //Blast Wave Rank 1
				{
					player->LearnSpell(mage_spell_Blast_Wave, false);
				}
				if (player->HasSpell(31661)) //Dragon Breath  Rank 1
				{
					player->LearnSpell(mage_spell_Dragons_Breath, false);
				}
				if (player->HasSpell(44457)) //Living Bomb Rank 1
				{
					player->LearnSpell(mage_spell_Living_Bomb, false);
				}
				if (player->HasSpell(11366)) //Pyroblast Rank 1
				{
					player->LearnSpell(mage_spell_Pyroblast, false);
				}
				//Frost
				if (player->HasSpell(11426)) //Ice Barrier Rank 1
				{
					player->LearnSpell(mage_spell_Ice_Barrier, false);
				}
				//=====WARLOCK TALENT=====//
				//Destruction
				if (player->HasSpell(17877)) //ShadowBurn Rank 1
				{
					player->LearnSpell(warlock_spell_Shadowburn, false);
				}
				if (player->HasSpell(30283)) //ShadowFury Rank 1
				{
					player->LearnSpell(warlock_spell_Shadowfury, false);
				}
				if (player->HasSpell(50796)) //Chaos Bolt Rank 1
				{
					player->LearnSpell(warlock_spell_Chaos_Bolt, false);
				}
				//Affliction
				if (player->HasSpell(30108)) //Unstable Affliction Rank 1
				{
					player->LearnSpell(warlock_spell_Unstable_Affliction, false);
				}
				if (player->HasSpell(48181)) //Spell Haunt Rank 1
				{
					player->LearnSpell(warlock_spell_Haunt, false);
				}
				if (player->HasSpell(18220)) //Dark Pact Rank 1
				{
					player->LearnSpell(warlock_spell_Dark_Pact, false);
				}
				//=====DRUID   TALENT=====//
				//Balance
				if (player->HasSpell(50516)) //Typhoon Rank 1
				{
					player->LearnSpell(druid_spell_Typhoon, false);
				}
				if (player->HasSpell(48505)) //Starfall Rank 1
				{
					player->LearnSpell(druid_spell_Starfall, false);
				}
				if (player->HasSpell(5570)) //Insect Swarm Rank 1
				{
					player->LearnSpell(druid_spell_Insect_Swarm, false);
				}
				//Restoration
				if (player->HasSpell(48438)) //Wild Growth Rank 1
				{
					player->LearnSpell(druid_spell_Wild_Growth, false);
				}
				player->SaveToDB();
				player->PlayerTalkClass->SendCloseGossip();
				break;
			}
			
			
		}
		return true;
	}
};

void AddSC_npc_promo()
{
	new npc_promo();
}