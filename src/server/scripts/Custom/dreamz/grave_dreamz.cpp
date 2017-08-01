#include "ScriptPCH.h"
#include "Player.h"
#include "Battlefield.h"
#include "SharedDefines.h"
#include "Unit.h"

class deus_grave : public PlayerScript
{
public:
	deus_grave() : PlayerScript("deus_grave") {}

	void OnPVPKill(Player* killer, Player* killed)
	{
		if (killed->GetMapId() == 0 || killed->GetZoneId() == 33)
		{
			killed->TeleportTo(0, -3473.298584f, -1738.979370f, 47.451416f, 4.454378f);
			killed->CastSpell(killed, 31719, 1);
			killer->AddItem(26045, -1);
			ChatHandler(killed->GetSession()).SendSysMessage("|cffff0000Un Token Fue Removido de tus Bolsas!");
			killed->ResurrectPlayer(true);
			killer->AddItem(26045, 1);
			killer->DurabilityRepairAll(false, 0, false);
			killer->DurabilityRepairAll(false, 0, false);
			ChatHandler(killer->GetSession()).SendSysMessage("|cffff0000Un Token Fue Agregado de tus Bolsas!");
		}
	}
};

void AddSC_deus_grave()
{
	new deus_grave();
}