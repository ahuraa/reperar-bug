#include "Custom/zeros/promo.h"
class Restart : public CreatureScript 
{ 
    public: 
        Restart() : CreatureScript("Restart") {} 

    bool OnGossipHello(Player* player, Creature* creature) 
    { 
        { 
            player->ADD_GOSSIP_ITEM(10, "Restart Incstance", GOSSIP_SENDER_MAIN, 1); 
            player->PlayerTalkClass->SendGossipMenu(68, creature->GetGUID()); 
            return true; 
        } 
    } 

    bool OnGossipSelect(Player* player, Creature* creature, uint32 Sender, uint32 Actions) 
    { 
        player->PlayerTalkClass->ClearMenus(); 

        switch(Actions) 
        { 
            case 1:
                 for (uint8 i = 0; i < MAX_DIFFICULTY; ++i) 
                { 
                    Player::BoundInstancesMap &binds = player->GetBoundInstances(Difficulty(i)); 
                    for (Player::BoundInstancesMap::iterator itr = binds.begin(); itr != binds.end();) 
                    { 
                        player->UnbindInstance(itr, Difficulty(i)); 
						player->SendChatMessage("Sus Cds De instancia sean Eliminado");
                    } 
                } 
            break; 
        } 
        return true; 
    } 
}; 

void AddSC_Creature_Script() 
{ 
    new Restart(); 
}  