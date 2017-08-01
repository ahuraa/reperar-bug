#include "Channel.h"
#include "Language.h"


class Boss_Announcer : public PlayerScript
{
    public:
    Boss_Announcer() : PlayerScript ("Boss_Announcer") {} 

    void OnCreatureKill(Player* player, Creature* boss) 
    {
        std::string plr = player->GetName();
        std::string boss_n = boss->GetName();
        std::string gender = player->getGender() == GENDER_FEMALE ? "her" : "his";
        bool ingroup = player->GetGroup();
        std::string tag_colour = "7bbef7";
        std::string plr_colour = "ff0000";
        std::string boss_colour = "18be00";

        if (boss->isWorldBoss())
        {
            std::ostringstream stream;
            stream << "|CFF" << tag_colour << 
                      "[Boss Announcer]|r:|cff" << plr_colour << " " << plr <<
                      "|r ha matado al Boss |CFF" << boss_colour << "[" << boss_n << "]|r " << 
                      (ingroup ? "by " : "with ") << gender << (ingroup ? " group" : "self") << "!";
            sWorld->SendServerMessage(SERVER_MSG_STRING, stream.str().c_str());
        }
    };
};

void AddSC_Boss_Announcer()
{
    new Boss_Announcer;
}