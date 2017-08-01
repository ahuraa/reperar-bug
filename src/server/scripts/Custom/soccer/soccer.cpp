#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "Player.h"

using namespace std;

int ScoreB = 0;
int ScoreR = 0;

class ball : public CreatureScript
{
public:
    ball() : CreatureScript("ball") { }	

	struct ball_passivesAI : public ScriptedAI
	{
		ball_passivesAI(Creature * c) : ScriptedAI(c){ }

		uint32 Timer;

		void Reset()
		{
			Timer = 15;
		}
		
        void MoveInLineOfSight(Unit* who)
		{
			int random = urand(0, 3);
			
			if (who->GetTypeId() == TYPEID_PLAYER && me->IsWithinDistInMap(who, 0.1f))
			{
				if (Player * player = who->ToPlayer())
				{
					if(random == 3)
						player->CastSpell(me, 10689, true);
					else
						player->CastSpell(me, 54080, true);
				}
			}  
			ScriptedAI::MoveInLineOfSight(who);
	    }
		   
		void UpdateAI(uint32 diff)
		{
			if (Timer <= diff)
			{
				if (me->GetPositionX() > -3648.69f && me->GetPositionX() < -3640.57f && me->GetPositionY() < -1304.29f)	
	            {
					sWorld->SendZoneText(17, "|TInterface\\ICONS\\INV_Jewelcrafting_Gem_22:50|t");
					me->Say("The red team scores a goal !", LANG_UNIVERSAL);
					++ScoreR;
					me->Respawn(true);
					me->NearTeleportTo(-3644.593018f, -1270.614990f, 233.497833f, 1.550308f);
	            }
	            else if (me->GetPositionX() > -3648.69f && me->GetPositionX() < -3640.57f && me->GetPositionY() > -1238.21f)
	            {
					sWorld->SendZoneText(17, "|TInterface\\ICONS\\INV_Jewelcrafting_Gem_24:50|t");
					me->Say("The blue team scores a goal !", LANG_UNIVERSAL);
					++ScoreB;
					me->Respawn(true);
					me->NearTeleportTo(-3644.593018f, -1270.614990f, 233.497833f, 1.550308f);
	            }
	            else if (me->GetPositionX() < -3661.32f)
	            {
					me->Say("Out !", LANG_UNIVERSAL);
					me->Respawn(true);
					me->NearTeleportTo(-3644.593018f, -1270.614990f, 233.497833f, 1.550308f);
	            }
	            else if (me->GetPositionX() > -3628.39f)
	            {
					me->Say("Out !", LANG_UNIVERSAL);
					me->Respawn(true);
					me->NearTeleportTo(-3644.593018f, -1270.614990f, 233.497833f, 1.550308f);
	            }     
		        else if (me->GetPositionY() > -1238.0f)
		        {
					me->Say("Out !", LANG_UNIVERSAL);
					me->Respawn(true);
					me->NearTeleportTo(-3644.593018f, -1270.614990f, 233.497833f, 1.550308f);
	 	        }
	   	        else if (me->GetPositionY() < -1304.37f)
		  	    {
					me->Say("Out !", LANG_UNIVERSAL);
					me->Respawn(true);
					me->NearTeleportTo(-3644.593018f, -1270.614990f, 233.497833f, 1.550308f);
	  	  	    }
				
				Timer = 15;
			}
			else
				Timer -= diff;

		}
	};

	CreatureAI * GetAI(Creature * pCreature) const
	{
		return new ball_passivesAI(pCreature);
	}
};

class referee : public CreatureScript
{
public:
	referee() : CreatureScript("referee") { }
		
	bool OnGossipHello(Player* player, Creature* creature)
	{
        char msg[100];
        char msg2[100];
        sprintf(msg, "Blue team : %u", ScoreB);	
        sprintf(msg2, "Red team : %u", ScoreR);	
        player->ADD_GOSSIP_ITEM(7, "                           |TInterface\\ICONS\\Ability_GolemStormBolt:50|t", GOSSIP_SENDER_MAIN, 0);				
	    player->ADD_GOSSIP_ITEM(7, "                          SOCCER", GOSSIP_SENDER_MAIN, 0);
		player->ADD_GOSSIP_ITEM(7, "----------------------------------------------", GOSSIP_SENDER_MAIN, 0);
		player->ADD_GOSSIP_ITEM(0, "Score of the game :", GOSSIP_SENDER_MAIN, 0);
		player->ADD_GOSSIP_ITEM(0, msg, GOSSIP_SENDER_MAIN, 0);
		player->ADD_GOSSIP_ITEM(0, msg2, GOSSIP_SENDER_MAIN, 0);
		player->ADD_GOSSIP_ITEM(4, "Reset score", GOSSIP_SENDER_MAIN, 1);
		player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 uiAction)
	{
		player->PlayerTalkClass->ClearMenus();

		switch(uiAction)
		{
			case 0:
				OnGossipHello(player, creature);
			break;
			
			case 1:
				ScoreB = 0;
				ScoreR = 0;
				ChatHandler(player->GetSession()).PSendSysMessage("Score reset");
				player->CLOSE_GOSSIP_MENU();
			break;
			
		}
		return true;
	}

	struct referee_passivesAI : public ScriptedAI
	{
		referee_passivesAI(Creature * c) : ScriptedAI(c){ }

		uint32 Timer;
		
		void Reset()
		{
			Timer = 1000;
		}
		
		void UpdateAI(uint32 diff)
		{

			if (Timer <= diff)
			{
                char msg[100];
                sprintf(msg, "Blue : %u | Red : %u", ScoreB, ScoreR);			
				me->Say(msg, LANG_UNIVERSAL);
				me->HandleEmoteCommand(EMOTE_ONESHOT_EXCLAMATION);
				Timer = 50000;
			}
			else
				Timer -= diff;
		}
	};

	CreatureAI * GetAI(Creature * pCreature) const
	{
		return new referee_passivesAI(pCreature);
	}
};

void AddSC_soccer()
{
	new ball();
	new referee();
}