#include "Language.h"
#include "World.h"
//#include "AuctionHouseMgr.h"

uint32 auras[] = { 48162, 48074, 48170, 43223, 36880, 467, 48469 };

class premium_commandscript : public CommandScript
{
public:
    premium_commandscript() : CommandScript("premium_commandscript") { }

    std::vector<ChatCommand> GetCommands() const override
    {
        static std::vector<ChatCommand> premiumCommandTable =
        {
            { "bank",  SEC_PLAYER, false, &HandlePremiumBankCommand,    "" },
            { "mail",  SEC_PLAYER, false, &HandlePremiumMailCommand,    "" },
			{ "buff",  SEC_PLAYER, false, &HandlePremiumBuffCommand,    "" },
			{ "repair",  SEC_PLAYER, false, &HandlePremiumRepairCommand,    "" },
			
            //{ "auc",  SEC_PLAYER,  false, &HandlePremiumAuctionCommand, "", NULL },
        };

        static std::vector<ChatCommand> commandTable =
        {
            { "vip", SEC_PLAYER, false, NULL, "", premiumCommandTable },
        };

        return commandTable;
    }

    static bool HandlePremiumBankCommand(ChatHandler* handler, char const* /*args*/)
    {
        Player *player = handler->GetSession()->GetPlayer();
        if (player->GetSession()->IsPremium() && sWorld->getBoolConfig(COMMAND_BANK_PREMIUM))
        {
            //Different Checks
            if (player->IsInCombat() || player->IsInFlight() || player->GetMap()->IsBattlegroundOrArena() || player->HasStealthAura() || player->HasFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH) || player->isDead())
            {
                handler->SendSysMessage(LANG_PREMIUM_CANT_DO);
                handler->SetSentErrorMessage(true);
                return false;
            }

            handler->GetSession()->SendShowBank(handler->GetSession()->GetPlayer()->GetGUID());
        }
        return true;
    }

    static bool HandlePremiumMailCommand(ChatHandler* handler, char const* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->GetSession()->IsPremium() && sWorld->getBoolConfig(COMMAND_MAIL_PREMIUM))
        {
			//Different Checks
			if (player->IsInCombat() || player->IsInFlight() || player->GetMap()->IsBattlegroundOrArena() || player->HasStealthAura() || player->HasFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH) || player->isDead())
			{
				handler->SendSysMessage(LANG_PREMIUM_CANT_DO);
				handler->SetSentErrorMessage(true);
				return false;
			}
            handler->GetSession()->SendShowMailBox(player->GetGUID());
        }
        return true;
    }

	static bool HandlePremiumBuffCommand(ChatHandler * handler, const char * /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->GetSession()->IsPremium() && sWorld->getBoolConfig(COMMAND_BUFF_PREMIUM))
        {
			//Different Checks
			if (player->IsInCombat() || player->IsInFlight() || player->GetMap()->IsBattlegroundOrArena() || player->InArena() || player->HasStealthAura() || player->HasFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH) || player->isDead())
			{
				handler->SendSysMessage(LANG_PREMIUM_CANT_DO);
				handler->SetSentErrorMessage(true);
				return false;
			}
                for(int i = 0; i < 7; i++)
                player->AddAura(auras[i], player);
                handler->PSendSysMessage("|cffB400B4You have been buffed, enjoy!");
        }
        return true;
    }	
	
	static bool HandlePremiumRepairCommand(ChatHandler * handler, const char * /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->GetSession()->IsPremium() && sWorld->getBoolConfig(COMMAND_REPAIR_PREMIUM))
        {
			//Different Checks
			if (player->IsInCombat() || player->IsInFlight() || player->GetMap()->IsBattlegroundOrArena() || player->InArena() || player->HasStealthAura() || player->HasFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH) || player->isDead())
			{
				handler->SendSysMessage(LANG_PREMIUM_CANT_DO);
				handler->SetSentErrorMessage(true);
				return false;
			}
			player->DurabilityRepairAll(false, 0, false);
        }
        return true;
    }	
    //static bool HandlePremiumAuctionCommand(ChatHandler* handler, char const* /*args*/)
    //{
        //Player* player = handler->GetSession()->GetPlayer();
        //if(player->GetSession()->IsPremium())
        //{
            //Different Checks
            //if(player->IsInCombat() || player->IsInFlight() || player->GetMap()->IsBattlegroundOrArena() || player->HasStealthAura() || player->HasFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH) || player->isDead())
            //{
            //    handler->SendSysMessage(LANG_PREMIUM_CANT_DO);
            //    handler->SetSentErrorMessage(true);
            //    return false;
            //}

            //handler->GetSession()->SendAuctionHello(player->GetGUID());
            //handler->GetSession()->SendAuctionHello(player->getFaction());

        //}
        //return true;
    //}

};

void AddSC_premium_commandscript()
{
    new premium_commandscript();
}