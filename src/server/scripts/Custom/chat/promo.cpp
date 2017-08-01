#include "promo.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "ObjectMgr.h"

using namespace std;

promo* promo::instance()
{
	static promo instance;
	return &instance;
}

void promo::SIniciar()
{
	if (spromo->iniciado)
		return;
	TC_LOG_INFO("server.loading", "Cargando configuraciones de Promo");
	QueryResult TC = CharacterDatabase.PQuery("SELECT activa, rango, player, vip, moderador, gm, pvp, pvp_rango, pvp_limite, pve, pve_rango, pve_limite, prof, proflimite, proflimiterece FROM `promo_conf`;");
	Field *c = TC->Fetch();
	Config CC;
	CC.Activa = (c[0].GetInt8() == 0 ? false : true);
	CC.ActivaRango = c[1].GetInt8();
	CC.Players = c[2].GetInt8();
	CC.VIP = c[3].GetInt8();
	CC.Moderadores = c[4].GetInt8();
	CC.GM = c[5].GetInt8();
	CC.PVP = (c[6].GetInt8() == 0 ? false : true);
	CC.PVPRango = c[7].GetInt8();
	CC.PVPLimite = c[8].GetInt8();
	CC.PVE = (c[9].GetInt8() == 0 ? false : true);
	CC.PVERango = c[10].GetInt8();
	CC.PVELimite = c[11].GetInt8();
	CC.Prof = (c[12].GetInt8() == 0 ? false : true);
	CC.ProfLimite = c[13].GetInt8();
	CC.ProfLimiteRece = c[14].GetInt8();
	spromo->Configuraciones = CC;

	TC_LOG_INFO("server.loading", "Cargando lista de Sets del sistema Promo");
	QueryResult TS = CharacterDatabase.PQuery("SELECT (SELECT count(*) FROM promo_sets WHERE `set` = 'pve') AS PVE, (SELECT count(*) FROM promo_sets WHERE `set` = 'pvp') AS PVP;");
	Sets pve;
	Sets pvp;
	Field *s = TS->Fetch();
	pve.Scantidad(s[0].GetInt8());
	pvp.Scantidad(s[1].GetInt8());
	QueryResult Tsets = CharacterDatabase.PQuery("SELECT `set`, id, class, npc_text FROM promo_sets;");
	int xp = 0, xe = 0;
	while (Field *f = Tsets->Fetch())
	{
		if (f[0].GetString()=="pvp")
		{
			pvp.id[xp] = f[1].GetInt8();
			pvp.clase[xp] = f[2].GetInt8();
			pvp.npc_text[xp] = f[3].GetString();
			xp++;
		} 
		else
		{
			pve.id[xe] = f[1].GetInt8();
			pve.clase[xe] = f[2].GetInt8();
			pve.npc_text[xe] = f[3].GetString();
			xe++;
		}
		Tsets->NextRow();
	}
	spromo->PVE = pve;
	spromo->PVP = pvp;

	TC_LOG_INFO("server.loading", "Cargando lista de items del sistema Promo");
	SetsItems pvei;
	SetsItems pvpi;
	QueryResult Ti = CharacterDatabase.PQuery("select (select count(*) from promo_items where `set` = 'pve') as pve, (select count(*) from promo_items where `set` = 'pvp') as pvp");
	Field *fi = Ti->Fetch();
	pvei.scantidad(fi[0].GetInt32());
	pvpi.scantidad(fi[1].GetInt32());
	QueryResult Titems = CharacterDatabase.PQuery("select `set`, id, item, hitem, cantidad from promo_items");
	int ie = 0; int ip = 0;
	while (Field* fit = Titems->Fetch())
	{
		if (fit[0].GetString()=="pvp")
		{
			pvpi.id[ip] = fit[1].GetInt32();
			pvpi.item[ip] = fit[2].GetInt32();
			pvpi.itemh[ip] = 0;
			pvpi.cantidad[ip] = fit[4].GetInt32();
			ip++;
		}
		else
		{
			pvei.id[ie] = fit[1].GetInt32();
			pvei.item[ie] = fit[2].GetInt32();
			pvei.itemh[ie] = fit[3].GetInt32();
			pvei.cantidad[ie] = fit[4].GetInt32();
			ie++;
		}
		Titems->NextRow();
	}
	spromo->PVPitems = pvpi;
	spromo->PVEitems = pvei;

	TC_LOG_INFO("server.loading", "Cargando lista de Spells del sistema Promo");
	Spells S;
	QueryResult ts = CharacterDatabase.PQuery("select class, spell from promo_spells");
	S.registros(ts->GetRowCount()); int xs = 0;
	while (Field* fs = ts->Fetch())
	{
		S.clase[xs] = fs[0].GetInt32();
		S.spell[xs] = fs[1].GetInt32();
		ts->NextRow();
	}
	spromo->PSpells = S;
	spromo->iniciado = true;
}

void promo::GetPjInfo(PjInfo &pjinfo, Player* player)
{
	pjinfo.player = player;
	pjinfo.pjid = player->GetGUID();
	pjinfo.pjname = player->GetName();
	pjinfo.pjlevel = player->getLevel();
	pjinfo.pjclase = player->getClass();
	pjinfo.accID = player->GetSession()->GetAccountId();
	pjinfo.ip = player->GetSession()->GetRemoteAddress();
	string* excluir_ip = Excluir_ip(pjinfo);
	pjinfo.noip = excluir_ip[0] == "si";

	GetUsername(pjinfo);
	LimitesPromo(pjinfo);
	EsAlianza(pjinfo);

	AccPromo(pjinfo);
	if (pjinfo.AccConPromo)
	{
		if (spromo->Configuraciones.Prof)
		{
			AccProfes(pjinfo);
		}
		PjPromo(pjinfo);
	}
}
void promo::GetUsername(PjInfo &pjinfo)
{
	string qacc = "SELECT username FROM `account` where id = " + to_string(pjinfo.accID) + ";";
	QueryResult racc = LoginDatabase.PQuery(qacc.c_str());
	Field* facc = racc->Fetch();

	pjinfo.acc = facc[0].GetString();
}
void promo::LimitesPromo(PjInfo &pjinfo)
{
	int limite = 0; 
	bool gm = false;
	switch (pjinfo.player->GetSession()->GetSecurity())
	{
	case SEC_PLAYER: 
		limite = spromo->Configuraciones.Players;
		break;
	case SEC_MODERATOR: 
		limite = spromo->Configuraciones.Moderadores;
		break;
	default: 
		limite = spromo->Configuraciones.GM;
		gm = true; 
		break;
	}
	pjinfo.plimit = limite;
	pjinfo.EsGM = gm;
}
void promo::EsAlianza(PjInfo &pjinfo)
{
	bool r = false;
	switch (pjinfo.player->getRace())
	{
	case 1: /*humano*/ case 3: /*enano*/ case 4: /*elfo de la noche*/ case 7: /*gnomo*/ case 11: /*dranei*/
		r = true;
		break;
	}
	pjinfo.EsAlianza = r;
}

void promo::AccPromo(PjInfo &pjinfo)
{
	uint32 accID = pjinfo.player->GetSession()->GetAccountId();
	QueryResult r1 = CharacterDatabase.PQuery(string("SELECT count(*) FROM `promo` where account = " + to_string(accID)).c_str());
	Field* f1 = r1->Fetch();
	pjinfo.pmax = f1[0].GetInt8();
	if (pjinfo.pmax == 0)
	{
		if (!pjinfo.noip)
		{
			QueryResult r2 = CharacterDatabase.PQuery(string("SELECT count(*) FROM `promo` where ip = '" + pjinfo.ip + "'").c_str());
			Field* f2 = r2->Fetch();
			if (f2[0].GetInt8() != 0)
			{
				pjinfo.NpcText = 100005;
				pjinfo.Rechazada = true;
				return;
			}
		}
		
		pjinfo.AccConPromo = false;
		pjinfo.pmax = pjinfo.prest = pjinfo.plimit;
		AumentarPromos(pjinfo, pjinfo.plimit, "promo", "NPC Promo v3");
		return;
	}
	
	pjinfo.AccConPromo = true;
	
	QueryResult r3 = CharacterDatabase.PQuery("select(select count(*) from promo where account = %d) as accm, (select count(*) from promo where account = %d and pjid is NULL) as accr", pjinfo.accID, pjinfo.accID);
	Field* f3 = r3->Fetch();
	pjinfo.pmax = f3[0].GetInt8();
	pjinfo.prest = f3[1].GetInt8();

	int faltan;
	if (pjinfo.pmax < pjinfo.plimit)
	{
		faltan = pjinfo.plimit - pjinfo.pmax;
		AumentarPromos(pjinfo, faltan, "promo", "NPC Promo v3");
		pjinfo.pmax += faltan;
		pjinfo.prest += faltan;
	}
}
void promo::AccProfes(PjInfo &pjinfo)
{
	uint32 accID = pjinfo.player->GetSession()->GetAccountId();
	QueryResult r1 = CharacterDatabase.PQuery(string("SELECT count(*) FROM `promo_profe` where account = " + to_string(accID)).c_str());
	Field* f1 = r1->Fetch();
	int profes = f1[0].GetInt8();
	if (profes == 0)
	{
		AumentarProfes(pjinfo, 0, spromo->Configuraciones.ProfLimite, "promo", "NPC Promo v3");
		AumentarProfes(pjinfo, 1, spromo->Configuraciones.ProfLimiteRece, "promo", "NPC Promo v3");
		pjinfo.profm = pjinfo.profr = spromo->Configuraciones.ProfLimite;
		pjinfo.ProfConReceM = pjinfo.ProfConReceR = spromo->Configuraciones.ProfLimiteRece;
		return;
	}
	
	QueryResult r2 = CharacterDatabase.PQuery(string("SELECT pj, recetas FROM `promo_profe` where account = " + to_string(pjinfo.accID)).c_str());
	int pm = 0; int pr = 0;
	int rm = 0; int rr = 0;
	while (Field *f2 = r2->Fetch())
	{
		if (f2[1].GetInt8() == 0)
		{
			pm++;
			if (f2[0].IsNull())
			{
				pr++;
			}
		}
		else
		{
			rm++;
			if (f2[0].IsNull())
			{
				rr++;
			}
		}
		r2->NextRow();
	}
	pjinfo.profm = pm;
	pjinfo.profr = pr;
	pjinfo.ProfConReceM = rm;
	pjinfo.ProfConReceR = rr;

	int faltan;
	if (pjinfo.profm < spromo->Configuraciones.ProfLimite)
	{
		faltan = spromo->Configuraciones.ProfLimite - pjinfo.profm;
		AumentarProfes(pjinfo, 0, faltan, "promo", "NPC Promo v3+");
		pjinfo.profm += faltan;
		pjinfo.profr += faltan;
	}
	faltan = 0;
	if (pjinfo.ProfConReceM < spromo->Configuraciones.ProfLimiteRece)
	{
		faltan = spromo->Configuraciones.ProfLimiteRece - pjinfo.ProfConReceM;
		AumentarProfes(pjinfo, 1, faltan, "promo", "NPC Promo v3+");
		pjinfo.ProfConReceM += faltan;
		pjinfo.ProfConReceR += faltan;
	}
}
void promo::PjPromo(PjInfo &pjinfo)
{
	QueryResult r1 = CharacterDatabase.PQuery("select count(*), promo_id from promo where pjid = %d", pjinfo.pjid);
	Field* f1 = r1->Fetch();
	if (f1[0].GetInt32() == 0)
	{
		pjinfo.PjConPromo = false;
		return;
	}
	pjinfo.PjConPromo = true;
	pjinfo.pid = f1[1].GetInt32();


	int xp = 0; int xpr = 0;
	int xe = 0; int xer = 0;
	QueryResult r = CharacterDatabase.PQuery("select(select count(*) from promo_get where promo_id = %d and class = 'pve') as pve, (select count(*) from promo_get where promo_id = %d and class = 'pvp') as pvp", pjinfo.pid, pjinfo.pid);
	Field* f = r->Fetch();
	if (f[0].GetInt32() == 0)
	{
		xe = spromo->Configuraciones.PVELimite; xer = xe;
		AumentarSets(pjinfo, xe, "pve", "promo", "NPC Promo v3");
	}
	if (f[1].GetInt32() == 0)
	{
		xp = spromo->Configuraciones.PVPLimite; xpr = xp;
		AumentarSets(pjinfo, xp, "pvp", "promo", "NPC Promo v3");
	}

	if (xe == 0)
	{
		QueryResult re = CharacterDatabase.PQuery("select (select count(*) from promo_get where promo_id = %d and class = 'pve') as pve, (select count(*) from promo_get where promo_id = %d and class = 'pve' and `set`is null) as pver", pjinfo.pid, pjinfo.pid);
		Field* fe = re->Fetch();
		xe = fe[0].GetInt32();
		xer = fe[1].GetInt32();
	}
	if (xp == 0)
	{
		QueryResult rp = CharacterDatabase.PQuery("select (select count(*) from promo_get where promo_id = %d and class = 'pvp') as pvp, (select count(*) from promo_get where promo_id = %d and class = 'pvp' and `set`is null) as pvpr", pjinfo.pid, pjinfo.pid);
		Field* fp = rp->Fetch();
		xp = fp[0].GetInt32();
		xpr = fp[1].GetInt32();
	}
	
	pjinfo.pvpm = xp;
	pjinfo.pvpr = xpr;
	pjinfo.pvem = xe;
	pjinfo.pver = xer;
	int faltan;
	if (pjinfo.pvem < spromo->Configuraciones.PVELimite)
	{
		faltan = spromo->Configuraciones.PVELimite - pjinfo.pvem;
		AumentarSets(pjinfo, faltan, "pve", "promo", "NPC Promo v3+");
	}
	if (pjinfo.pvpm < spromo->Configuraciones.PVPLimite)
	{
		faltan = spromo->Configuraciones.PVPLimite - pjinfo.pvpm;
		AumentarSets(pjinfo, faltan, "pvp", "promo", "NPC Promo v3+");
	}
}
void promo::AumentarPromos(PjInfo &pjinfo, int cantidad, string motivo, string detalles)
{
	for (int i = 0; i < cantidad; i++)
	{
		CharacterDatabase.PExecute(string("INSERT INTO promo(ip, account, motivo, detalles) VALUES('" + pjinfo.ip + "', " + to_string(pjinfo.accID) + ", '" + motivo + "', '" + detalles + "');"));
	}
}
void promo::AumentarProfes(PjInfo &pjinfo, bool recetas, int cantidad, string motivo, string detalles)
{
	for (int i = 0; i < cantidad; i++)
	{
		CharacterDatabase.PExecute(string("INSERT INTO promo_profe(account, recetas, motivo, detalles) VALUES("+to_string(pjinfo.accID)+", "+(recetas ? "1" : "0")+", '"+motivo+"','"+detalles+"');"));
	}
}
void promo::AumentarSets(PjInfo &pjinfo, int cantidad, string clase, string motivo, string detalles)
{
	for (int i = 0; i < cantidad; i++)
	{
		CharacterDatabase.PExecute(string("INSERT INTO promo_get(promo_id, class, motivo, detalles) VALUES ("+to_string(pjinfo.pid)+",'"+clase+"','"+motivo+"', '" + detalles + "');"));
	}
}
string promo::FechayHora() 
{
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
	return buf;
}
string* promo::Excluir_ip(PjInfo &pjinfo)
{
	QueryResult r1 = CharacterDatabase.PQuery(string("SELECT count(*), lider, detalles FROM `promo_excluir_ip` where ip = '" + pjinfo.ip + "';").c_str());
	string* r = new string[3];
	Field* f1 = r1->Fetch();
	r[0] = (f1[0].GetInt8() < 1 ? "no" : "si");
	pjinfo.noip = (f1[0].GetInt8() < 1 ? false : true);
	r[1] = f1[1].GetString();
	r[2] = f1[2].GetString();
	return r;
}
void promo::StringToArray(string &str, vector<int> &items, char separador){
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == separador)
			str[i] = ' ';
	}
	stringstream ss(str);
	int temp;
	while (ss >> temp)
		items.push_back(temp);
}

void promo::PersonajesElimidados(PjInfo &pjinfo)
{
	QueryResult q = CharacterDatabase.PQuery("SELECT count(*) FROM promo INNER JOIN characters ON promo.pjid = characters.guid WHERE promo.account = %d AND deleteInfos_Account IS NOT NULL;", pjinfo.accID);
	Field* f = q->Fetch();
	pjinfo.PjSCantidad(f[0].GetInt8());
	if (pjinfo.PjEliminadosCantidad == 0)
		return;
	QueryResult q1 = CharacterDatabase.PQuery("SELECT promo.promo_id, promo.pjid, promo.pjname, characters.money FROM promo INNER JOIN characters ON promo.pjid = characters.guid WHERE promo.account = %d AND deleteInfos_Account IS NOT NULL;", pjinfo.accID);
	int i = 0;
	while (Field* f1 = q1->Fetch())
	{
		pjinfo.PjEliminadoPromoId[i]	= f1[0].GetInt32();
		pjinfo.PjEliminadoId[i]			= f1[1].GetInt32();
		pjinfo.PjEliminadoNombre[i]		= f1[2].GetString();
		pjinfo.PjEliminadoMoney[i]		= f1[3].GetInt32();
		i++;
		q1->NextRow();
	}
}
void promo::DarPromo(PjInfo &pjinfo, bool registrar){
	pjinfo.player->GetSession()->SendAreaTriggerMessage("Felicidades!! equipate tus bolsas y toma tus set's!.");
	pjinfo.player->ResetSpells(44415);
	pjinfo.player->GiveLevel(80);
	pjinfo.player->AddItem(38082, 4);
	pjinfo.player->LearnSpell(34092, false);
	pjinfo.player->LearnSpell(54197, false);
	pjinfo.player->LearnSpell(48025, false);
	pjinfo.player->LearnSpell(71342, false);
	pjinfo.player->RemoveSpell(44415, false);
	pjinfo.player->CastSpell(pjinfo.player, 63680, true);
	pjinfo.player->CastSpell(pjinfo.player, 45870, true); 
	pjinfo.player->CastSpell(pjinfo.player, 63624, true);
	pjinfo.player->SetMoney(50000000);
	pjinfo.player->SetHonorPoints(75000);
	pjinfo.player->AddItem(49426, 200);
	DarSpells(pjinfo);
	if (pjinfo.EsGM)
		registrar = false;
	if (registrar)
		CharacterDatabase.PExecute(string("update promo set pjid = %d, pjname = '"+pjinfo.pjname+"', class = %d, fecha = '"+FechayHora()+"' where account = %d and pjid is null LIMIT 1;").c_str(), pjinfo.pjid, pjinfo.pjclase, pjinfo.accID);
	pjinfo.player->SaveToDB();
}
void promo::DarSpells(PjInfo &pjinfo){
	QueryResult rs = CharacterDatabase.PQuery("SELECT class, spell FROM `promo_spells` WHERE class = %d", pjinfo.pjclase);
	while (Field *fs = rs->Fetch())
	{
		if (fs[1].GetInt32() != 0)
			pjinfo.player->LearnSpell(fs[1].GetInt32(), false);
		rs->NextRow();
	}
	pjinfo.player->SaveToDB();
}
void promo::DarSet(PjInfo &pjinfo, string clase, int setid, bool registrar)
{
	int buzon = 0; int entregados = 0;
	if (clase == "pvp")
	{
		setid -= SET_PVP;
		for (int i = 0; i < spromo->PVPitems.registros; i++)
		{
			if (setid == spromo->PVPitems.id[i])
			{
				int item = spromo->PVPitems.item[i]; int cantidad = spromo->PVPitems.cantidad[i];
				if (item != 0)
				{
					bool p = false;
					ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(item);
					if (itemTemplate)
					{
						entregados++;
						if (!pjinfo.player->AddItem(item, cantidad))
						{
							pjinfo.player->SendItemRetrievalMail(item, cantidad);
							buzon++;
						}
					}
				}
			}
		}
		int item = (pjinfo.EsAlianza ? 42124 : 42126);
		if (!pjinfo.player->AddItem(item, 1)) pjinfo.player->SendItemRetrievalMail(item, 1);
	}
	else if (clase == "pve")
	{
		setid -= SET_PVE;
		for (int i = 0; i < spromo->PVEitems.registros; i++)
		{
			if (setid == spromo->PVEitems.id[i])
			{
				int item;
				int cantidad;
				if (pjinfo.EsAlianza)
				{
					item = spromo->PVEitems.item[i];
					cantidad = spromo->PVEitems.cantidad[i];
				}
				else
				{
					item = spromo->PVEitems.itemh[i];
					cantidad = spromo->PVEitems.cantidad[i];
				}
				if (item != 0)
				{
					ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(item);
					if (itemTemplate)
					{
						entregados++;
						if (!pjinfo.player->AddItem(item, cantidad))
						{
							pjinfo.player->SendItemRetrievalMail(item, cantidad);
							buzon++;
						}
					}
				}
			}
		}
	}
	if (buzon != 0)
		pjinfo.player->SendChatMessage("Se enviaron %d objetos a su buzon porque no tenias espacio en las bolsas", buzon);
	if (registrar)
		RegistrarSet(pjinfo, clase, setid);
	pjinfo.player->SendChatMessage("Se entregaron %d objetos", entregados);
	pjinfo.player->SaveToDB();
}
void promo::RegistrarSet(PjInfo pjinfo, string clase, int setid)
{
	CharacterDatabase.PExecute(string("update promo_get set fecha = '" + FechayHora() + "', `set` = %d where promo_id = %d and class = '" + clase + "' and `set` is null LIMIT 1").c_str(), setid, pjinfo.pid);
}
void promo::RegistrarProfe(PjInfo pjinfo, SkillType skill)
{
	string profe;
	bool recetas = pjinfo.DarRecetas;
	switch (skill)
	{
	case SKILL_BLACKSMITHING:profe = "Herreria"; break;
	case SKILL_LEATHERWORKING:profe = "Peleteria"; break;
	case SKILL_ALCHEMY:profe = "Alquimia"; break;
	case SKILL_HERBALISM:profe = "Herbologia"; break;
	case SKILL_MINING:profe = "Mineria"; break;
	case SKILL_TAILORING:profe = "Sastreria"; break;
	case SKILL_ENGINEERING:profe = "Ingenieria"; break;
	case SKILL_ENCHANTING:profe = "Encantamiento"; break;
	case SKILL_SKINNING:profe = "Desuello"; break;
	case SKILL_JEWELCRAFTING:profe = "Joyeria"; break;
	case SKILL_INSCRIPTION:profe = "Inscripcion"; break;
	}
	if (!pjinfo.EsGM)
		CharacterDatabase.PExecute(string("update promo_profe set pj = %d, profe = '" + profe + "', fecha = '" + FechayHora() + "' where account = %d and pj is null and recetas = " + (recetas ? "1" : "0") + " limit 1;").c_str(), pjinfo.pjid, pjinfo.accID);
}

bool promo::nombre(PjInfo &pjinfo)
{
	if (pjinfo.pjname.find("evx") != string::npos || pjinfo.pjname.find("Evx") != string::npos)
		return true;
	return false;
}
/*
void Player::SendChatMessage(const char *format, ...)
{
	if (!IsInWorld())
		return;

	if (format)
	{
		va_list ap;
		char str[2048];
		va_start(ap, format);
		vsnprintf(str, 2048, format, ap);
		va_end(ap);

		ChatHandler(GetSession()).SendSysMessage(str);
	}
}*/