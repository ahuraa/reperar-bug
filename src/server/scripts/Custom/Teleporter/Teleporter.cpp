#include "ScriptMgr.h"
#include "GossipDef.h"
#include "Player.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
 
class hell_telenpc : public CreatureScript
{
    public:
 
        hell_telenpc()
            : CreatureScript("npc_teleport")
        {
        }
 
bool OnGossipHello(Player* player, Creature* creature)
{
 
        // Main Menu for Alliance
       if (player->GetTeam() == ALLIANCE)
        {
                player->ADD_GOSSIP_ITEM( 7, "|TInterface/ICONS/spell_arcane_portalthunderbluff:35:35|t|cffff0000Ciudades"                                  , GOSSIP_SENDER_MAIN , 1000);
                player->ADD_GOSSIP_ITEM( 7, "|TInterface/ICONS/Achievement_Arena_5v5_6:35:35|t|cffff0000PvP|r Zone"                                 , GOSSIP_SENDER_MAIN , 3000);
                player->ADD_GOSSIP_ITEM( 7, "|TInterface/ICONS/inv_mace_116:35:35|t|cffff0000Estancias |r PvE"                        , GOSSIP_SENDER_MAIN , 3800);
        }
        else // Main Menu for Horde
        {
                player->ADD_GOSSIP_ITEM( 7, "|TInterface/ICONS/spell_arcane_portalthunderbluff:35:35|t|cffff0000Ciudades"                          , GOSSIP_SENDER_MAIN , 2000);
                player->ADD_GOSSIP_ITEM( 7, "|TInterface/ICONS/Achievement_Arena_5v5_6:35:35|t|cffff0000PvP|r Zone"                         , GOSSIP_SENDER_MAIN , 3000);
                player->ADD_GOSSIP_ITEM( 7, "|TInterface/ICONS/inv_mace_116:35:35|t|cffff0000Estancias |r PvE"                        , GOSSIP_SENDER_MAIN , 3800);
        }
 
    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
 
return true;
}
 
void SendDefaultMenu(Player* player, Creature* creature, uint32 action)
{
 
// Not allow in combat
if (player->IsInCombat())
{
    player->CLOSE_GOSSIP_MENU();
    creature->Say("Estas en combate!", LANG_UNIVERSAL, NULL);
        return;
}
 
switch (action)
{
 
case 1000: //Cities - Alliance
            player->ADD_GOSSIP_ITEM( 5, "Ventormenta"                    , GOSSIP_SENDER_MAIN , 1015);
                player->ADD_GOSSIP_ITEM( 5, "Forjaz"                               , GOSSIP_SENDER_MAIN , 1010);
                player->ADD_GOSSIP_ITEM( 5, "Darnassus"                    , GOSSIP_SENDER_MAIN , 1001);
                player->ADD_GOSSIP_ITEM( 5, "Exodar"                       , GOSSIP_SENDER_MAIN , 1005);
                player->ADD_GOSSIP_ITEM( 5, "Shattrath"               , GOSSIP_SENDER_MAIN , 3035);
                player->ADD_GOSSIP_ITEM( 5, "Dalaran"                 , GOSSIP_SENDER_MAIN , 3010);
                player->ADD_GOSSIP_ITEM( 5, "Bahia del Botin"                    , GOSSIP_SENDER_MAIN , 3005);
                player->ADD_GOSSIP_ITEM( 5, "Gadegetzan"                   , GOSSIP_SENDER_MAIN , 3020);
                player->ADD_GOSSIP_ITEM( 5, "Isla de Quel'Danas"           , GOSSIP_SENDER_MAIN , 3040);
                player->ADD_GOSSIP_ITEM( 7, "<-- Menu"                , GOSSIP_SENDER_MAIN , 5005);
 
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
break;
 
case 2000: //Cities - Horde
                player->ADD_GOSSIP_ITEM( 5, "Orgrimmar"                            , GOSSIP_SENDER_MAIN , 2001);
                player->ADD_GOSSIP_ITEM( 5, "Entranas"                    , GOSSIP_SENDER_MAIN , 2015);
                player->ADD_GOSSIP_ITEM( 5, "Cima del Trueno"                , GOSSIP_SENDER_MAIN , 2010);
                player->ADD_GOSSIP_ITEM( 5, "Lunargenta"                   , GOSSIP_SENDER_MAIN , 2005);
                player->ADD_GOSSIP_ITEM( 5, "Tierras Inhospitas"                     , GOSSIP_SENDER_MAIN , 2020);
                player->ADD_GOSSIP_ITEM( 5, "Shattrath"               , GOSSIP_SENDER_MAIN , 3035);
                player->ADD_GOSSIP_ITEM( 5, "Dalaran"                 , GOSSIP_SENDER_MAIN , 3010);
                player->ADD_GOSSIP_ITEM( 5, "Bahia del Botin"                    , GOSSIP_SENDER_MAIN , 3005);
                player->ADD_GOSSIP_ITEM( 5, "Gadegetzan"                   , GOSSIP_SENDER_MAIN , 3020);
                player->ADD_GOSSIP_ITEM( 5, "Isla de Quel'Danas"           , GOSSIP_SENDER_MAIN , 3040);
                player->ADD_GOSSIP_ITEM( 7, "<-- Menu"                , GOSSIP_SENDER_MAIN , 5005);
 
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
break;
 
case 3000: //Arenas
                player->ADD_GOSSIP_ITEM( 5, "|TInterface/ICONS/ACHIEVEMENT_ARENA_2V2_1:35:35|t|cffff0000Duel Zone"               , GOSSIP_SENDER_MAIN , 8000);
                player->ADD_GOSSIP_ITEM( 5, "|TInterface/ICONS/ACHIEVEMENT_ARENA_2V2_1:35:35|t|cffff0000PVP Zone(This is War)"                          , GOSSIP_SENDER_MAIN , 7999);
                player->ADD_GOSSIP_ITEM( 5, "|TInterface/ICONS/spell_arcane_portalthunderbluff:35:35|t|cffff0000Custom Zone"                      , GOSSIP_SENDER_MAIN , 7998);
                player->ADD_GOSSIP_ITEM( 7, "<-- Menu"                 , GOSSIP_SENDER_MAIN , 5005);
 
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
break;
 
case 5005: //Back To Main Menu
        /* 11/05/2010 niteowl57:  For 3.3.5a, fix menu functionality  */
         player->PlayerTalkClass->ClearMenus();
         OnGossipHello(player, creature);
break;
 
case 3800: //Instances Zones
        player->ADD_GOSSIP_ITEM( 5, "Instancias Kalimdor"           , GOSSIP_SENDER_MAIN , 5010);
        player->ADD_GOSSIP_ITEM( 5, "Instancias Reinos del Este"     , GOSSIP_SENDER_MAIN , 5015);
        player->ADD_GOSSIP_ITEM( 5, "Instancias Terrallende"              , GOSSIP_SENDER_MAIN , 5025);
        player->ADD_GOSSIP_ITEM( 5, "Instancias Rasganorte"            , GOSSIP_SENDER_MAIN , 5030);
        player->ADD_GOSSIP_ITEM( 7, "<-- Menu"                    , GOSSIP_SENDER_MAIN , 5005);
 
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
break;
 
case 5010: //Kalimdor
        player->ADD_GOSSIP_ITEM( 5, "Profundidades Brazanegra"                , GOSSIP_SENDER_MAIN , 6001);
        player->ADD_GOSSIP_ITEM( 5, "Cavernas del Tiempo"                  , GOSSIP_SENDER_MAIN , 6005);
        player->ADD_GOSSIP_ITEM( 5, "La Masacre"                        , GOSSIP_SENDER_MAIN , 6010);
        player->ADD_GOSSIP_ITEM( 5, "Maraudon"                         , GOSSIP_SENDER_MAIN , 6015);
        player->ADD_GOSSIP_ITEM( 5, "Sima Ignea"                   , GOSSIP_SENDER_MAIN , 6020);
        player->ADD_GOSSIP_ITEM( 5, "Zahurda Rajacieno"                   , GOSSIP_SENDER_MAIN , 6025);
        player->ADD_GOSSIP_ITEM( 5, "Horado Rajacieno"                   , GOSSIP_SENDER_MAIN , 6030);
        player->ADD_GOSSIP_ITEM( 5, "Ruinas de Ahn'Qiraj"               , GOSSIP_SENDER_MAIN , 6035);
        player->ADD_GOSSIP_ITEM( 5, "Templo de Ahn'Qiraj"              , GOSSIP_SENDER_MAIN , 6040);
        player->ADD_GOSSIP_ITEM( 5, "Cuevas de los Lamentos"                  , GOSSIP_SENDER_MAIN , 6045);
        player->ADD_GOSSIP_ITEM( 5, "Zul'Farrak"                       , GOSSIP_SENDER_MAIN , 6050);
        player->ADD_GOSSIP_ITEM( 7, "<-- Atras"                                            , GOSSIP_SENDER_MAIN , 3800);
        player->ADD_GOSSIP_ITEM( 7, "<-- Menu"                    , GOSSIP_SENDER_MAIN , 5005);
 
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
break;
 
case 5015: //Eastern Kingdoms 1
        player->ADD_GOSSIP_ITEM( 5, "Profundidades de Roca Negra"                 , GOSSIP_SENDER_MAIN , 7001);
        player->ADD_GOSSIP_ITEM( 5, "Cumbre de Roca Negra"                  , GOSSIP_SENDER_MAIN , 7005);
        player->ADD_GOSSIP_ITEM( 5, "Guarida Alanegra"                   , GOSSIP_SENDER_MAIN , 7010);
        player->ADD_GOSSIP_ITEM( 5, "Minas de la Muerte"                        , GOSSIP_SENDER_MAIN , 7015);
        player->ADD_GOSSIP_ITEM( 5, "Gnomeregan"                       , GOSSIP_SENDER_MAIN , 7020);
        player->ADD_GOSSIP_ITEM( 5, "Isla de Quel'Danas"               , GOSSIP_SENDER_MAIN , 7025);
        player->ADD_GOSSIP_ITEM( 5, "Karazhan"                         , GOSSIP_SENDER_MAIN , 7030);
        player->ADD_GOSSIP_ITEM( 5, "Nucleo de Magma"                      , GOSSIP_SENDER_MAIN , 7035);
        player->ADD_GOSSIP_ITEM( 7, "Pagina 2 -->"                       , GOSSIP_SENDER_MAIN , 5020);
        player->ADD_GOSSIP_ITEM( 7, "<-- Atras"                         , GOSSIP_SENDER_MAIN , 3800);
 
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
break;
 
case 5020: //Eastern Kingdoms 2
        player->ADD_GOSSIP_ITEM( 5, "Monasterio Escarlata"                , GOSSIP_SENDER_MAIN , 7040);
        player->ADD_GOSSIP_ITEM( 5, "Scholomance"                      , GOSSIP_SENDER_MAIN , 7045);
        player->ADD_GOSSIP_ITEM( 5, "Castillo de Colmillo Oscuro"                  , GOSSIP_SENDER_MAIN , 7050);
        player->ADD_GOSSIP_ITEM( 5, "Stratholme"                       , GOSSIP_SENDER_MAIN , 7055);
        player->ADD_GOSSIP_ITEM( 5, "Templo Sumergido"                    , GOSSIP_SENDER_MAIN , 7060);
        player->ADD_GOSSIP_ITEM( 5, "Las Mazmorras"                     , GOSSIP_SENDER_MAIN , 7065);
        player->ADD_GOSSIP_ITEM( 5, "Uldaman"                          , GOSSIP_SENDER_MAIN , 7070);
        player->ADD_GOSSIP_ITEM( 5, "Zul'Aman"                         , GOSSIP_SENDER_MAIN , 7075);
        player->ADD_GOSSIP_ITEM( 5, "Zul'Gurub"                        , GOSSIP_SENDER_MAIN , 7080);
        player->ADD_GOSSIP_ITEM( 7, "<-- Pagina 1"                       , GOSSIP_SENDER_MAIN , 5015);
        player->ADD_GOSSIP_ITEM( 7, "<-- Menu"                    , GOSSIP_SENDER_MAIN , 5005);
 
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
break;
 
case 5025: //Outland
        player->ADD_GOSSIP_ITEM( 5, "Auchindoun"                       , GOSSIP_SENDER_MAIN , 8001);
        player->ADD_GOSSIP_ITEM( 5, "Templo Oscuro"                     , GOSSIP_SENDER_MAIN , 8005);
        player->ADD_GOSSIP_ITEM( 5, "Reserva Colmillo Torcido"               , GOSSIP_SENDER_MAIN , 8010);
        player->ADD_GOSSIP_ITEM( 5, "Guarida de Gruul"                     , GOSSIP_SENDER_MAIN , 8015);
        player->ADD_GOSSIP_ITEM( 5, "Ciudadela del Fuego Infernal"                 , GOSSIP_SENDER_MAIN , 8020);
        player->ADD_GOSSIP_ITEM( 5, "Castillo de la Tempestad"                     , GOSSIP_SENDER_MAIN , 8025);
        player->ADD_GOSSIP_ITEM( 7, "<-- Atras"                         , GOSSIP_SENDER_MAIN , 3800);
        player->ADD_GOSSIP_ITEM( 7, "<-- Menu"                    , GOSSIP_SENDER_MAIN , 5005);
 
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
break;
 
case 5030: //Northrend
        player->ADD_GOSSIP_ITEM( 5, "Ahn'Kahet"                        , GOSSIP_SENDER_MAIN , 9001);
        player->ADD_GOSSIP_ITEM( 5, "Azjol-Nerub"                      , GOSSIP_SENDER_MAIN , 9005);
        player->ADD_GOSSIP_ITEM( 5, "Fortaleza Drak'Tharon"                 , GOSSIP_SENDER_MAIN , 9010);
        player->ADD_GOSSIP_ITEM( 5, "Gun'Drak"                         , GOSSIP_SENDER_MAIN , 9015);
        player->ADD_GOSSIP_ITEM( 5, "Ciudadela Corona de Hielo"                 , GOSSIP_SENDER_MAIN , 9020);
        player->ADD_GOSSIP_ITEM( 5, "Naxxramas"                        , GOSSIP_SENDER_MAIN , 9025);
        player->ADD_GOSSIP_ITEM( 5, "Guarida de Onyxia"                    , GOSSIP_SENDER_MAIN , 9030);
        player->ADD_GOSSIP_ITEM( 5, "El Nexo"                        , GOSSIP_SENDER_MAIN , 9035);
        player->ADD_GOSSIP_ITEM( 5, "El Sagrario Obsidiano"             , GOSSIP_SENDER_MAIN , 9040);
        player->ADD_GOSSIP_ITEM( 5, "Fortaleza de Utgarde"                     , GOSSIP_SENDER_MAIN , 9045);
        player->ADD_GOSSIP_ITEM( 5, "Pinaculo de Utgarde"                 , GOSSIP_SENDER_MAIN , 9050);
        player->ADD_GOSSIP_ITEM( 5, "Ulduar"                           , GOSSIP_SENDER_MAIN , 9055);
        player->ADD_GOSSIP_ITEM( 5, "El Bastion Violeta"                      , GOSSIP_SENDER_MAIN , 9060);
        player->ADD_GOSSIP_ITEM( 7, "<-- Atras"                         , GOSSIP_SENDER_MAIN , 3800);
        player->ADD_GOSSIP_ITEM( 7, "<-- Menu"                    , GOSSIP_SENDER_MAIN , 5005);
 
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
break;
 
 
//////////////////////////////////////////////////ALLIANCE///////////////////////////////////////////////////////////////
 
case 1001: // Darnassus
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(1, 9947.52f, 2482.73f, 1316.21f, 0.0f);
break;
 
case 1005: // Exodar
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(530, -3954.20f, -11656.54f, -138.69f, 0.0f);
break;
 
case 1010: // Ironforge
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(0, -4924.07f, -951.95f, 501.55f, 5.40f);
break;
 
case 1015: // Stormwind
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(0, -8960.14f, 516.266f, 96.3568f, 0.0f);
break;
 
//////////////////////////////////////////////////HORDE///////////////////////////////////////////////////////////////
 
case 2001: // Orgrimmar
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(1, 1552.5f, -4420.66f, 8.94802f, 0.0f);
break;
 
case 2005: // Silvermoon
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(530, 9338.74f, -7277.27f, 13.7895f, 0.0f);
break;
 
case 2010: // Thunder Bluff
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(1, -1290.0f, 147.033997f, 129.682007f, 4.919000f);
break;
 
case 2015: // Undercity
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(0, 1819.71f, 238.79f, 60.5321f, 0.0f);
break;
 
case 2020: // Badlands
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(0, -6640.17f, -2200.31f, 244.144f, 1.2031f);
break;
//////////////////////////////////////////////////Arenas///////////////////////////////////////////////////////////////
 
case 8000:// Duel Zone
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(1, 5243.806152f, -4791.785645f, 690.152161f, 3.763503f);
break;
 
case 7999:// Warr Zone
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(0, -3357.641846f, -1809.218018f, 24.221224f, 3.458224f);
break;
 
case 7998:// Custom
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(1, 16222.599609f, 16265.900391f, 13.209357f, 1.65007f);
break;
 
 
 
//////////////////////////////////////////////////NEUTRAL///////////////////////////////////////////////////////////////
 
case 3001:// Ebon Hold
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(0, 2353.530029f, -5665.819824f, 426.028015f, 0.596f);
break;
 
case 3005:// Booty Bay
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(0, -14438.2f, 472.22f, 15.32f, 0.65f);
break;
 
case 3010: //Dalaran
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(571, 5819.08f, 643.99f, 647.80f, 3.32f);
break;
 
case 3015: //Everlook
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(1, 6724.77f, -4610.68f, 720.78f, 4.78f);
break;
 
case 3020: //Gadgetzan
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(1, -7173.26f, -3785.60f, 8.37f, 6.13f);
break;
 
case 3025: //Mudsprocket
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(1, -4564.79f, -3172.38f, 33.93f, 3.21f);
break;
 
case 3030: //Ratchet
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(1, -956.664f, -3754.71f, 5.33239f, 0.996637f);
break;
 
case 3035:// Shattrath City
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(530, -1850.209961f, 5435.821777f, -10.961435f, 3.403913f);
break;
 
case 3040:// Isle Of Quel'Danas
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(530, 12947.4f, -6893.31f, 5.68398f, 3.09154f);
break;
 
 
//////////////////////////////////////////////////OUTLAND LOCATION///////////////////////////////////////////////////////////////
 
case 3601:// Blade's Edge Mountains
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(530, 1589.919312f, 6784.039063f, 135.167633f, 0.506582f);
break;
 
case 3605:// Hellfire Peninsula
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(530, -248.0f, 956.0f, 84.362808f, 1.549591f);
break;
 
case 3610: //Nagrand
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(530, -604.137146f, 8436.199219f, 61.776058f, 3.019857f);
break;
 
case 3615: //Netherstorm
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(530, 3386.022217f, 4225.194824f, 123.685989f, 5.153f);
break;
 
case 3620: //Shadowmoon Valley
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(530, -2901.471680f, 3125.052734f, 26.8999f, 4.464991f);
break;
 
case 3625: //Terokkar Forest
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(530, -2000.469971f, 4451.540039f, 8.379014f, 4.464991f);
break;
 
case 3630: //Zangarmarsh
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(530, -225.6577f, 5435.426270f, 21.574932f, 1.533886f);
break;
 
//////////////////////////////////////////////////NORTHREND LOCATION///////////////////////////////////////////////////////////////
 
case 3701:// Borean Tundra
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(571, 3256.570068f, 5278.229980f, 40.804588f, 0.246367f);
break;
 
case 3705:// Crystalsong Forest
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(571, 5766.373047f, 655.131287f, 160.944641f, 4.135118f);
break;
 
case 3710: //Dragonblight
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(571, 4103.359863f, 264.477997f, 50.501900f, 3.093490f);
break;
 
case 3715: //Grizzly Hills
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(571, 4391.729980f, -3587.919922f, 238.531006f, 3.575260f);
break;
 
case 3720: //Howling Fjord
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(571, 1902.150024f, -4883.910156f, 171.363007f, 3.115370f);
break;
 
case 3725: //Hrothgar's Landing
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(571, 9982.508789f, 1037.768188f, 15.307539f, 5.512708f);
break;
 
case 3730: //Icecrown
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(571, 7253.640137f, 1644.780029f, 433.679901f, 4.834120f);
break;
 
case 3735:// Sholazar Basin
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(571, 5572.285156f, 5737.171387f, -75.440643f, 1.514785f);
break;
 
case 3740:// The Storm Peaks
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(571, 6119.275391f, -1015.613464f, 408.683258f, 5.175134f);
break;
 
case 3745:// Wintergrasp
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(571, 5212.746582f, 2821.331787f, 409.666840f, 1.840724f);
break;
 
case 3750:// Zul'Drak
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(571, 5560.229980f, -3211.659912f, 371.709015f, 5.550550f);
break;
 
//////////////////////////////////////////////////KALIMDOR///////////////////////////////////////////////////////////////
 
case 6001:// Blackfathom Deeps
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(1, 4248.72f, 744.35f, -24.67f, 1.34f);
break;
 
case 6005:// Caverns of Time
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(1, -8173.66f, -4746.36f, 33.84f, 4.94f);
break;
 
case 6010:// Dire Maul
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(1, -3960.95f, 1130.64f, 161.05f, 0.0f);
break;
 
case 6015:// Maraudon
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(1, -1431.33f, 2962.34f, 98.23f, 4.74f);
break;
 
case 6020:// Ragefire Chasm
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(1, 1814.47f, -4419.46f, -18.78f, 5.28f);
break;
 
case 6025:// Razorfen Downs
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(1, -4657.88f, -2525.59f, 81.4f, 4.16f);
break;
 
case 6030:// Razorfen Kraul
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(1, -4463.6f, -1664.53f, 82.26f, 0.85f);
break;
 
case 6035:// Ruins of Ahn'Qiraj
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(1, -8413.33f, 1501.27f, 29.64f, 2.61f);
break;
 
case 6040:// Temple of Ahn'Qiraj
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(1, -8245.837891f, 1983.736206f, 129.071686f, 0.936195f);
break;
 
case 6045:// Wailing Caverns
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(1, -722.53f,-2226.30f,16.94f,2.71f);
break;
 
case 6050:// Zul'Farrak
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(1, -6801.9f, -2890.22f, 8.88f, 6.25f);
break;
 
//////////////////////////////////////////////////EASTERN KINGDOMS///////////////////////////////////////////////////////////////
 
case 7001:// Blackrock Depths
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(0, -7180.57f, -920.04f, 165.49f, 5.02f);
break;
 
case 7005:// Blackrock Spire
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(0, -7526.77f, -1225.64f, 285.73f, 5.31f);
break;
 
case 7010:// Blackwing Lair
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(469, -7672.61f, -1107.21f, 396.65f, 3.75f);
break;
 
case 7015:// Deadmines
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(0, -11208.2f, 1675.92f, 24.57f, 1.48f);
break;
 
case 7020:// Gnomeregan
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(0, -5163.32f, 927.18f, 257.158f, 1.44f);
break;
 
case 7025:// Isle Of Quel'Danas
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(530, 13010.00f, -6907.64f, 9.58f, 4.58f);
break;
 
case 7030:// Karazhan
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(0, -11119.6f, -2011.42f, 47.09f, 0.65f);
break;
 
case 7035:// Molten Core
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(230, 1114.85f, -457.76f, -102.81f, 3.83f);
break;
 
case 7040:// Scarlet Monastery
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(0, 2843.89f,-693.74f,139.32f,5.11f);
break;
 
case 7045:// Scholomance
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(0, 1273.06f, -2574.01f, 92.66f, 2.06f);
break;
 
case 7050:// Shadowfang Keep
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(0, -239.54f, 1550.8f, 76.89f, 1.18f);
break;
 
case 7055:// Stratholme
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(0, 3370.76f, -3343.63f, 142.26f, 5.23f);
break;
 
case 7060:// Sunken Temple
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(0, -10346.92f, -3851.90f, -43.41f, 6.09f);
break;
 
case 7065:// The Stockade
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(0, -8766.89f, 844.6f, 88.43f, 0.69f);
break;
 
case 7070:// Uldaman
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(0, -6070.72f, -2955.33f, 209.78f, 0.05f);
break;
 
case 7075:// Zul'Aman
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(530, 6851.09f, -7979.71f, 183.54f, 4.72f);
break;
 
case 7080:// Zul'Gurub
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(0, -11916.4f, -1216.23f, 92.28f, 4.75f);
break;
 
//////////////////////////////////////////////////OUTLAND///////////////////////////////////////////////////////////////
 
case 8001:// Auchindoun
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(530, -3322.92f, 4931.02f, -100.56f, 1.86f);
break;
 
case 8005:// Black Temple
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(530, -3649.1f, 317.33f, 35.19f, 2.97f);
break;
 
case 8010:// Coilfang Reservoir
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(530, 721.08f, 6846.77f, -68.75f, 0.34f);
break;
 
case 8015:// Gruul's Lair
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(530, 3539.01f, 5082.36f, 1.69f, 0.0f);
break;
 
case 8020:// Hellfire Citadel
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(530, -292.71f, 3146.77f, 31.60f, 2.05f);
break;
 
case 8025:// Tempest Keep
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(530, 3087.62f, 1376.27f, 184.8f, 4.63f);
break;
 
//////////////////////////////////////////////////NORTHREND///////////////////////////////////////////////////////////////
 
case 9001:// Ahn'Kahet
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(571, 3646.76f, 2045.17f, 1.79f, 4.37f);
break;
 
case 9005:// Azjol-Nerub
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(571, 3675.43f, 2169.00f, 35.90f, 2.29f);
break;
 
case 9010:// Drak'Tharon Keep
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(571, 4450.86f, -2045.25f, 162.83f, 0.00f);
break;
 
case 9015:// Gun'Drak
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(571, 6937.54f, -4455.98f, 450.68f, 1.00f);
break;
 
case 9020:// Icecrown Citadel
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(571, 6139.24f, 2233.72f, 510.79f, 3.56f);
break;
 
case 9025:// Naxxramas
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(571, 3668.72f, -1262.46f, 243.622f, 4.785f);
break;
 
case 9030:// Onyxia's Lair
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(1, -4707.44f, -3726.82f, 54.6723f, 3.8f);
break;
 
case 9035:// The Nexus
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(571, 3789.95f, 6961.48f, 104.23f, 0.28f);
break;
 
case 9040:// The Obsidian Sanctum
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(571, 3625.78f, 280.4f, -120.14f, 3.25f);
break;
 
case 9045:// Ulduar
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(571, 1219.72f, -4865.28f, 41.25f, 0.31f);
break;
 
case 9050:// Utgarde Keep
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(571, 1245.69f, -4856.59f, 216.86f, 3.45f);
break;
 
case 9055:// Utgarde Pinnacle
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(571, 8976.24f, -1281.33f, 1059.01f, 0.58f);
break;
 
case 9060:// Violet Hold
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(571, 5679.82f, 486.80f, 652.40f, 4.08f);
break;
 
 
} // end of switch
} //end of function
 
 
 
bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
{
        // Main menu
      if (sender == GOSSIP_SENDER_MAIN)
      {
        /* 11/05/2010 niteowl57:  For 3.3.5a, fix menu functionality  */
        player->PlayerTalkClass->ClearMenus();
        SendDefaultMenu(player, creature, action);
        }
 
return true;
}
 
};
 
void AddSC_telenpc()
{
        new hell_telenpc;
}