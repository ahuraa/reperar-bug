/*
//Trinitycore//
Creditos a sus respectivos dueños.
Adaptado por Clowned para WOWREX
core 3.3.5a
http://wow-rex.com

//Spell List % Complete//
Warrior : 100 %
Mage : 100 %
Druid : 100 %
Paladin : 100 %
Warlock : 100 %
Hunter : 100 %
Shaman : 100 %
Rogue : 100 %
Priest : 100 %
DK : 100 %
Mount spells : 100 %

//Talent List Spell % Complete//
Warrior : 100 %
Mage : 100 %
Druid : 100 %
Paladin : 100 %
Warlock : 100 %
Hunter : 100 %
Shaman : 100 %
Rogue : 100 %
Priest : 100 %
DK : 100 %

//====SQL NPC====//
Set
@NPC_ENTRY = YOUR_ID,
@NPC_MORPH = YOUR_ID,
@NPC_SCRIPTNAME = "npc_welcome",
@NPC_NAME = "Welcome NPC 2.0",
@NPC_SUBNAME = "<Server Name>";

INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES
(@NPC_ENTRY, 0, 0, 0, 0, 0, @NPC_MORPH, 0, 0, 0, @NPC_NAME, @NPC_SUBNAME, '', 0, 80, 80, 0, 35, 35, 129, 1, 1.14286, 1, 3, 13, 17, 0, 42, 1, 1500, 0, 1, 515, 2048, 8, 0, 0, 0, 0, 0, 9, 13, 100, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 7, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2147483647, 2, @NPC_SCRIPTNAME, 12340);
*/

#include "ScriptPCH.h"

enum eIcons
{
	CHAT_ICON = 0,
	VENDOR_ICON = 1,
	FLIGHT_ICON = 2,
	TRAINER_ICON = 3,
	GEAR_ICON = 4,
	GEAR_ICON_2 = 5,
	BANK_ICON = 6,
	CHAT_DOTS_ICON = 7,
	TABARD_ICON = 8,
	SWORDS_ICON = 9,
	GOLD_DOT_ICON = 10
};

enum war_spell
{
	war_spell_Overpower = 7384,
	war_spell_Battle_Shout = 47436,
	war_spell_Heroic_Strike = 47450,
	war_spell_Charge = 11578,
	war_spell_Rend = 47465,
	war_spell_Thunder_Clap = 47502,
	war_spell_Victory_Rush = 34428,
	war_spell_Hamstring = 1715,
	war_spell_Bloodrage = 2687,
	war_spell_Defensive_Stance = 71,
	war_spell_Sunder_Armor = 7386,
	war_spell_Taunt = 355,
	war_spell_Shield_Bash = 72,
	war_spell_Demoralizing_Shout = 47437,
	war_spell_Revenge = 57823,
	war_spell_Mocking_Blow = 694,
	war_spell_Shield_Block = 2565,
	war_spell_Disarm = 676,
	war_spell_Cleave = 47520,
	war_spell_Retaliation = 20230,
	war_spell_Stance_Mastery = 12678,
	war_spell_Execute = 47471,
	war_spell_Challenging_Shout = 1161,
	war_spell_Shield_Wall = 871,
	war_spell_Berserker_Stance = 2458,
	war_spell_Intercept = 20252,
	war_spell_Slam = 47475,
	war_spell_Berserker_Rage = 18499,
	war_spell_Whirlwind = 1680,
	war_spell_Pummel = 6552,
	war_spell_Sheild_Slam = 47488,
	war_spell_Recklessness = 1719,
	war_spell_Spell_Reflection = 23920,
	war_spell_Commanding_Shout = 47440,
	war_spell_Intervene = 3411,
	war_spell_Shattering_Throw = 64382,
	war_spell_Enraged_Regeneration = 55694,
	war_spell_Heroic_Throw = 57755,
	war_spell_Dual_Wield = 42459,
	war_spell_Intimidating_Shout = 5246,
	war_spell_Parry = 3127,

	//Talent - War 
	war_spell_Devastate = 47498, // Talent - Proto
	war_spell_Mortal_Strike = 47486 // Talent - Arms

};

enum pala_spell
{
	pala_spell_Parry = 3127,
	pala_spell_Concentration_Aura = 19746,
	pala_spell_Divine_Intervention = 19752,
	pala_spell_Plate_Mail_skill = 750,
	pala_spell_Devotion_Aura = 48942,
	pala_spell_Holy_Light = 48782,
	pala_spell_Blessing_of_Might = 48932,
	pala_spell_Judgement_of_Light = 20271,
	pala_spell_Divine_Protection = 498,
	pala_spell_Hammer_of_Justice = 10308,
	pala_spell_Purify = 1152,
	pala_spell_Hand_of_Protection = 10278,
	pala_spell_Lay_on_Hands = 48788,
	pala_spell_Judgement_of_Wisdom = 53408,
	pala_spell_Redemption = 48950,
	pala_spell_Blessing_of_Wisdom = 48936,
	pala_spell_Righteous_Defense = 31789,
	pala_spell_Hand_of_Reckoning = 62124,
	pala_spell_Retribution_Aura = 54043,
	pala_spell_Righteous_Fury = 25780,
	pala_spell_Hand_of_Freedom = 1044,
	pala_spell_Blessing_of_Kings = 20217,
	pala_spell_Consecration = 48819,
	pala_spell_Exorcism = 48801,
	pala_spell_Flash_of_Light = 48785,
	pala_spell_Sense_Undead = 5502,
	pala_spell_Seal_of_Justice = 20164,
	pala_spell_Turn_Evil = 10326,
	pala_spell_Hand_of_Salvation = 1038,
	pala_spell_Judgement_of_Justice = 53407,
	pala_spell_Shadow_Resistance_Aura = 48943,
	pala_spell_Seal_of_Light = 20165,
	pala_spell_Frost_Resistance_Aura = 48945,
	pala_spell_Divine_Shield = 642,
	pala_spell_Fire_Resistance_Aura = 48947,
	pala_spell_Seal_of_Wisdom = 20166,
	pala_spell_Cleanse = 4987,
	pala_spell_Hammer_of_Wrath = 48806,
	pala_spell_Hand_of_Sacrifice = 6940,
	pala_spell_Holy_Wrath = 48817,
	pala_spell_Greater_Blessing_of_Might = 48934,
	pala_spell_Greater_Blessing_of_Wisdom = 48938,
	pala_spell_Greater_Blessing_of_Kings = 25898,
	pala_spell_Crusader_Aura = 32223,
	pala_spell_Avenging_Wrath = 31884,
	pala_spell_Divine_Plea = 54428,
	pala_spell_Shield_of_Righteousness = 61411,
	pala_spell_Sacred_Shield = 53601,
	pala_spell_Seal_of_Vengeance = 31801, // Alliance
	pala_spell_Warhorse = 13819, // Alliance
	pala_spell_Charger = 23214, // Alliance
	pala_spell_Seal_of_Corruption = 53736, // Horde
	pala_spell_Thalassian_Warhorse = 34769, // Horde
	pala_spell_Thalassian_Charger = 34767, // Horde

										   //Talent - Paladin
										   pala_spell_Holy_Shield = 48952,  // Talent - Protection
										   pala_spell_Avengers_Shield = 48827,  // Talent - Protection
										   pala_spell_Greater_Blessing_of_Sanctuary = 25899, // Talents - Protection
										   pala_spell_Holy_Shock = 48825, // Talents - Holy



};

enum mage_spell
{
	mage_spell_Arcane_Explosion = 42921,
	mage_spell_Frostbolt = 42842,
	mage_spell_Arcane_Intellect = 42995,
	mage_spell_Fireball = 42833,
	mage_spell_Conjure_Water = 27090,
	mage_spell_Conjure_Food = 33717,
	mage_spell_Fire_Blast = 42873,
	mage_spell_Arcane_Missiles = 42846,
	mage_spell_Polymorph = 12826,
	mage_spell_Polymorph_Turtle = 28271,
	mage_spell_Polymorph_Turkey = 61780,
	mage_spell_Polymorph_Rabbit = 61721,
	mage_spell_Polymorph_Pig = 28272,
	mage_spell_Frost_Nova = 42917,
	mage_spell_Dampen_Magic = 43015,
	mage_spell_Slow_Fall = 130,
	mage_spell_Flamestrike = 42926,
	mage_spell_Amplify_Magic = 43017,
	mage_spell_Remove_Curse = 475,
	mage_spell_Blink = 1953,
	mage_spell_Blizzard = 42940,
	mage_spell_Evocation = 12051,
	mage_spell_Fire_Ward = 43010,
	mage_spell_Mana_Shield = 43020,
	mage_spell_Frost_Ward = 43012,
	mage_spell_Scorch = 42859,
	mage_spell_Counterspell = 2139,
	mage_spell_Cone_of_Cold = 42931,
	mage_spell_Conjure_Mana_Gem = 42985,
	mage_spell_Ice_Armor = 43008,
	mage_spell_Ice_Block = 45438,
	mage_spell_Mage_Armor = 43024,
	mage_spell_Arcane_Brilliance = 43002,
	mage_spell_Molten_Armor = 43046,
	mage_spell_Arcane_Blast = 42897,
	mage_spell_Ice_Lance = 42914,
	mage_spell_Invisibility = 66,
	mage_spell_Ritual_of_Refreshment = 58659,
	mage_spell_Spellsteal = 30449,
	mage_spell_Conjure_Refreshment = 42956,
	mage_spell_Frostfire_Bolt = 47610,
	mage_spell_Dalaran_Brilliance = 61316,
	mage_spell_Dalaran_Intellect = 61024,
	mage_spell_Mirror_Image = 55342,
	mage_spell_Portal_Dalaran = 53142,
	mage_spell_Frost_Armor = 7301,

	mage_spell_Teleport_Exodar = 32271, // Alliance
	mage_spell_Teleport_Theramore = 49359, // Alliance
	mage_spell_Teleport_Darnassus = 3565, // Alliance
	mage_spell_Teleport_Shattrath = 33690, // Alliance
	mage_spell_Teleport_Ironforge = 3562, // Alliance
	mage_spell_Teleport_Stromwind = 3561, // Alliance
	mage_spell_Portal_Darnassus = 11419, // Alliance
	mage_spell_Portal_Exodar = 32266, // Alliance
	mage_spell_Portal_Ironforge = 11416, // Alliance
	mage_spell_Portal_Shattrath = 33691, // Alliance
	mage_spell_Portal_Theramore = 49360, // Alliance

	mage_spell_Teleport_Orgrimmar = 3567, // Horde
	mage_spell_Teleport_Shattrath_H = 35715, // Horde
	mage_spell_Teleport_Thunder_Bluff = 3566, // Horde
	mage_spell_Teleport_Stonard = 49358, // Horde
	mage_spell_Teleport_Silvermoon = 32272, // Horde
	mage_spell_Teleport_Undercity = 3563, // Horde
	mage_spell_Portal_Orgrimmar = 11417, // Horde
	mage_spell_Portal_Shattrath_H = 35717, // Horde
	mage_spell_Portal_Silvermoon = 32267, // Horde
	mage_spell_Portal_Stonard = 49361, // Horde
	mage_spell_Portal_Thunder_Bluff = 11420, // Horde
	mage_spell_Portal_Undercity = 11418, // Horde	


										 //Talent - Mage
										 mage_spell_Pyroblast = 42891, // Talent - Fire
										 mage_spell_Ice_Barrier = 43039, // Talent - Frost
										 mage_spell_Living_Bomb = 55360, // Talent - Fire
										 mage_spell_Dragons_Breath = 42950, // Talent - Fire
										 mage_spell_Blast_Wave = 42945, // Talent - Fire
										 mage_spell_Arcane_Barrage = 44781 // Talent - Arcane

};

enum dk_spell
{
	dk_spell_Parry = 3127,
	dk_spell_Pestilence = 50842,
	dk_spell_Blood_Boil = 49941,
	dk_spell_Blood_Strike = 49930,
	dk_spell_Strangulate = 47476,
	dk_spell_Blood_Tap = 45529,
	dk_spell_Path_of_Frost = 3714,
	dk_spell_Dark_Command = 56222,
	dk_spell_Death_Pact = 48743,
	dk_spell_Frost_Presence = 48263,
	dk_spell_Icy_Touch = 49909,
	dk_spell_Mind_Freeze = 47528,
	dk_spell_Chains_of_Ice = 45524,
	dk_spell_Icebound_Fortitude = 48792,
	dk_spell_Horn_of_Winter = 57623,
	dk_spell_Rune_Strike = 56815,
	dk_spell_Empower_Rune_Weapon = 47568,
	dk_spell_Death_Coil = 49895,
	dk_spell_Death_Gate = 50977,
	dk_spell_Plague_Strike = 49921,
	dk_spell_Death_Grip = 49576,
	dk_spell_Raise_Dead = 46584,
	dk_spell_Death_and_Decay = 49938,
	dk_spell_Anti_Magic_Shell = 48707,
	dk_spell_Unholy_Presence = 48265,
	dk_spell_Raise_Ally = 61999,
	dk_spell_Army_of_the_Dead = 42650,
	dk_spell_Runeforging_skill = 53428,
	dk_spell_Uknowas = 53331,
	dk_spell_Uknowah = 54447,
	dk_spell_Uknowai = 53342,
	dk_spell_Uknowaz = 54446,
	dk_spell_Uknowan = 53323,
	dk_spell_Uknowab = 53344,
	dk_spell_Uknowav = 70164,
	dk_spell_Uknowaj = 62158,
	dk_spell_Uknowaq = 33391,
	dk_spell_Acherus_Deathcharger = 48778,
	dk_spell_Obliterate = 51425,
	dk_spell_Death_Strike = 49924,

	//Talent - Deathknight
	dk_spell_Heart_Strike = 55262, // Talent - Blood
	dk_spell_Frost_Strike = 55268, // Talent - Frost
	dk_spell_Howling_Blast = 51411, // Talent - Frost
	dk_spell_Scourge_Strike = 55271, // Talent - Unholy
	dk_spell_Corpse_Explosion = 51328 // Talent - Unholy

};

enum druid_spell
{
	druid_spell_Healing_Touch = 48378,
	druid_spell_Mark_of_the_Wild = 48469,
	druid_spell_Wrath = 48461,
	druid_spell_Moonfire = 48463,
	druid_spell_Rejuvenation = 48441,
	druid_spell_Thorns = 53307,
	druid_spell_Entangling_Roots = 53308,
	druid_spell_Bear_Form = 5487,
	druid_spell_Demoralizing_Roar = 48560,
	druid_spell_Growl = 6795,
	druid_spell_Maul = 48480,
	druid_spell_Natures_Grasp = 53312,
	druid_spell_Teleport_Moonglade = 18960,
	druid_spell_Enrage = 5229,
	druid_spell_Regrowth = 48443,
	druid_spell_Revive = 50763,
	druid_spell_Bash = 8983,
	druid_spell_Cure_Poison = 8946,
	druid_spell_Aquatic_Form = 1066,
	druid_spell_Swipe_Bear = 48562,
	druid_spell_Travel_Form = 783,
	druid_spell_Faerie_Fire = 770,
	druid_spell_Faerie_Fire_Feral = 16857,
	druid_spell_Hibernate = 18658,
	druid_spell_Cat_Form = 768,
	druid_spell_Feral_Charge_Bear = 16979,
	druid_spell_Feral_Charge_Cat = 49376,
	druid_spell_Prowl = 5215,
	druid_spell_Rebirth = 48477,
	druid_spell_Rip = 49800,
	druid_spell_Starfire = 48465,
	druid_spell_Shred = 48572,
	druid_spell_Soothe_Animal = 26995,
	druid_spell_Rake = 48574,
	druid_spell_Remove_Curse = 2782,
	druid_spell_Tigers_Fury = 50213,
	druid_spell_Abolish_Poison = 2893,
	druid_spell_Dash = 33357,
	druid_spell_Challenging_Roar = 5209,
	druid_spell_Cower = 48575,
	druid_spell_Tranquility = 48447,
	druid_spell_Ferocious_Bite = 48577,
	druid_spell_Ravage = 48579,
	druid_spell_Track_Humanoids = 5225,
	druid_spell_Frenzied_Regeneration = 22842,
	druid_spell_Pounce = 49803,
	druid_spell_Dire_Bear_Form = 9634,
	druid_spell_Feline_Grace = 20719,
	druid_spell_Hurricane = 48467,
	druid_spell_Innervate = 29166,
	druid_spell_Savage_Defense = 62600,
	druid_spell_Barkskin = 22812,
	druid_spell_Gift_of_the_Wild = 48470,
	druid_spell_Mangle_Bear = 48564,
	druid_spell_Mangle_Cat = 48566,
	druid_spell_Flight_Form = 33943,
	druid_spell_Maim = 49802,
	druid_spell_Lifebloom = 48451,
	druid_spell_Lacerate = 48568,
	druid_spell_Cyclone = 33786,
	druid_spell_Swift_Flight_Form = 40120,
	druid_spell_Swipe_Cat = 62078,
	druid_spell_Savage_Roar = 52610,
	druid_spell_Nourish = 50464,
	druid_spell_Claw_1 = 1082,
	druid_spell_Claw = 48570,

	//Talent - Druid
	druid_spell_Typhoon = 61384, // Talent - Balance
	druid_spell_Starfall = 53201, // Talent - Balance
	druid_spell_Wild_Growth = 53251, // Talent - Restoration
	druid_spell_Insect_Swarm = 48468 // Talent - Balance

};

enum shaman_spell
{
	shaman_spell_Earth_Elemental_Totem = 2062,
	shaman_spell_Healing_Wave = 49273,
	shaman_spell_Lightning_Bolt = 49238,
	shaman_spell_Rockbiter_Weapon = 10399,
	shaman_spell_Earth_Shock = 49231,
	shaman_spell_Stoneskin_Totem = 58753,
	shaman_spell_Earthbind_Totem = 2484,
	shaman_spell_Lightning_Shield = 49281,
	shaman_spell_Stoneclaw_Totem = 58582,
	shaman_spell_Flame_Shock = 49233,
	shaman_spell_Flametongue_Weapon = 58790,
	shaman_spell_Searing_Totem = 58704,
	shaman_spell_Strength_of_Earth_Totem = 58643,
	shaman_spell_Ancestral_Spirit = 49277,
	shaman_spell_Fire_Nova = 61657,
	shaman_spell_Purge = 8012,
	shaman_spell_Cure_Toxins = 526,
	shaman_spell_Ghost_Wolf = 2645,
	shaman_spell_Wind_Shear = 57994,
	shaman_spell_Tremor_Totem = 8143,
	shaman_spell_Frost_Shock = 49236,
	shaman_spell_Frostbrand_Weapon = 58796,
	shaman_spell_Healing_Stream_Totem = 58757,
	shaman_spell_Lesser_Healing_Wave = 49276,
	shaman_spell_Water_Shield = 57960,
	shaman_spell_Water_Breathing = 131,
	shaman_spell_Frost_Resistance_Totem = 58745,
	shaman_spell_Far_Sight = 6196,
	shaman_spell_Magma_Totem = 58734,
	shaman_spell_Mana_Spring_Totem = 58774,
	shaman_spell_Fire_Resistance_Totem = 58739,
	shaman_spell_Flametongue_Totem = 58656,
	shaman_spell_Water_Walking = 546,
	shaman_spell_Astral_Recall = 556,
	shaman_spell_Call_of_the_Elements = 66842,
	shaman_spell_Earthliving_Weapon = 51994,
	shaman_spell_Grounding_Totem = 8177,
	shaman_spell_Nature_Resistance_Totem = 58749,
	shaman_spell_Reincarnation = 20608,
	shaman_spell_Totemic_Recall = 36936,
	shaman_spell_Windfury_Weapon = 58804,
	shaman_spell_Chain_Lightning = 49271,
	shaman_spell_Windfury_Totem = 8512,
	shaman_spell_Sentry_Totem = 6495,
	shaman_spell_Cleansing_Totem = 8170,
	shaman_spell_Call_of_the_Ancestors = 66843,
	shaman_spell_Chain_Heal = 55459,
	shaman_spell_Call_of_the_Spirits = 66844,
	shaman_spell_Wrath_of_Air_Totem = 3738,
	shaman_spell_Fire_Elemental_Totem = 2894,
	shaman_spell_Lava_Burst = 60043,
	shaman_spell_Hex = 51514,
	shaman_spell_Bloodlust = 2825, // Horde
	shaman_spell_Heroism = 32182, // Alliance

								  //Talent - Shaman
								  shaman_spell_Riptide = 61301, // Talent - Restoration
								  shaman_spell_Earth_Shield = 49284, // Talent - Restoration
								  shaman_spell_Totem_of_Wrath = 57722, // Talent - Elemental
								  shaman_spell_Thunderstorm = 59159   // Talent - Elemental

};

enum hunter_spell
{
	hunter_spell_Scorpid_Sting = 3043,
	hunter_spell_Parry = 3127,
	hunter_spell_Rapid_Fire = 3045,
	hunter_spell_Viper_Sting = 3034,
	hunter_spell_Track_Beasts = 1494,
	hunter_spell_Aspect_of_the_Monkey = 13163,
	hunter_spell_Raptor_Strike = 48996,
	hunter_spell_Serpent_Sting = 49001,
	hunter_spell_Arcane_Shot = 49045,
	hunter_spell_Hunters_Mark = 53338,
	hunter_spell_Concussive_Shot = 5116,
	hunter_spell_Aspect_of_the_Hawk = 27044,
	hunter_spell_Call_Pet = 883,
	hunter_spell_Dismiss_Pet = 2641,
	hunter_spell_Feed_Pet = 6991,
	hunter_spell_Revive_Pet = 982,
	hunter_spell_Tame_Beast = 1515,
	hunter_spell_Track_Humanoids = 19883,
	hunter_spell_Distracting_Shot = 20736,
	hunter_spell_Mend_Pet = 48990,
	hunter_spell_Wing_Clip = 2974,
	hunter_spell_Eagle_Eye = 6197,
	hunter_spell_Eyes_of_the_Beast = 1002,
	hunter_spell_Scare_Beast = 14327,
	hunter_spell_Aspect_of_the_Cheetah = 5118,
	hunter_spell_Immolation_Trap = 49056,
	hunter_spell_Mongoose_Bite = 53339,
	hunter_spell_Multi_Shot = 49048,
	hunter_spell_Track_Undead = 19884,
	hunter_spell_Aspect_of_the_Viper = 34074,
	hunter_spell_Disengage = 781,
	hunter_spell_Freezing_Trap = 14311,
	hunter_spell_Beast_Lore = 1462,
	hunter_spell_Track_Hidden = 19885,
	hunter_spell_Track_Elementals = 19880,
	hunter_spell_Frost_Trap = 13809,
	hunter_spell_Aspect_of_the_Beast = 13161,
	hunter_spell_Feign_Death = 5384,
	hunter_spell_Flare = 1543,
	hunter_spell_Track_Demons = 19878,
	hunter_spell_Explosive_Trap = 49067,
	hunter_spell_Aspect_of_the_Pack = 13159,
	hunter_spell_Track_Giants = 19882,
	hunter_spell_Volley = 58434,
	hunter_spell_Aspect_of_the_Wild = 49071,
	hunter_spell_Steady_Shot = 49052,
	hunter_spell_Track_Dragonkin = 19879,
	hunter_spell_Deterrence = 19263,
	hunter_spell_Tranquilizing_Shot = 19801,
	hunter_spell_Kill_Command = 34026,
	hunter_spell_Snake_Trap = 34600,
	hunter_spell_Misdirection = 34477,
	hunter_spell_Kill_Shot = 61006,
	hunter_spell_Aspect_of_the_Dragonhawk = 61847,
	hunter_spell_Masters_Call = 53271,
	hunter_spell_Freezing_Arrow = 60192,
	hunter_spell_Call_Stabled_Pet = 62757,
	hunter_spell_Dual_Wield = 42459,

	//Talent - Hunter
	hunter_spell_Wyvern_Sting = 49012,  // Talent - Survival
	hunter_spell_Explosive_Shot = 60053, // Talent - Survival
	hunter_spell_Conterattack = 48999, // Talent - Survival
	hunter_spell_Aimed_Shot = 49050  // Talent - Marksmanship


};

enum rogue_spell
{
	rogue_spell_Parry = 3127,
	rogue_spell_Dual_Wield = 42459,
	rogue_spell_Eviscerate = 48668,
	rogue_spell_Sinister_Strike = 48638,
	rogue_spell_Stealth = 1784,
	rogue_spell_Backstab = 48657,
	rogue_spell_Pick_Pocket = 921,
	rogue_spell_Gouge = 1776,
	rogue_spell_Evasion = 26669,
	rogue_spell_Sap = 51724,
	rogue_spell_Slice_and_Dice = 6774,
	rogue_spell_Sprint = 11305,
	rogue_spell_Kick = 1766,
	rogue_spell_Garrote = 48676,
	rogue_spell_Feint = 48659,
	rogue_spell_Lockpicking_skill = 1804,
	rogue_spell_Expose_Armor = 8647,
	rogue_spell_Ambush = 48691,
	rogue_spell_Dismantle = 51722,
	rogue_spell_Rupture = 48672,
	rogue_spell_Distract = 1725,
	rogue_spell_Vanish = 26889,
	rogue_spell_Detect_Traps = 2836,
	rogue_spell_Cheap_Shot = 1833,
	rogue_spell_Disarm_Trap = 1842,
	rogue_spell_Kidney_Shot = 8643,
	rogue_spell_Blind = 2094,
	rogue_spell_Safe_Fall = 1860,
	rogue_spell_Envenom = 57993,
	rogue_spell_Deadly_Throw = 48674,
	rogue_spell_Cloak_of_Shadows = 31224,
	rogue_spell_Shiv = 5938,
	rogue_spell_Tricks_of_the_Trade = 57934,
	rogue_spell_Fan_of_Knives = 51723,

	//Talent - Rogue
	rogue_spell_Hemorrhage = 48660, // Talent - Subtlety
	rogue_spell_Mutilate = 48666 // Talent - Assassination


};

enum priest_spell
{
	priest_spell_Cure_Disease = 528,
	priest_spell_Lesser_Heal = 2053,
	priest_spell_Power_Word_Fortitude = 48161,
	priest_spell_Smite = 48123,
	priest_spell_Shadow_Word_Pain = 48125,
	priest_spell_Power_Word_Shield = 48066,
	priest_spell_Fade = 586,
	priest_spell_Renew = 48068,
	priest_spell_Mind_Blast = 48127,
	priest_spell_Resurrection = 48171,
	priest_spell_Inner_Fire = 48168,
	priest_spell_Psychic_Scream = 10890,
	priest_spell_Heal = 6064,
	priest_spell_Dispel_Magic = 988,
	priest_spell_Devouring_Plague = 48300,
	priest_spell_Fear_Ward = 6346,
	priest_spell_Flash_Heal = 48071,
	priest_spell_Holy_Fire = 48135,
	priest_spell_Holy_Nova = 48078,
	priest_spell_Mind_Soothe = 453,
	priest_spell_Shackle_Undead = 10955,
	priest_spell_Mind_Vision = 10909,
	priest_spell_Mana_Burn = 8129,
	priest_spell_Divine_Spirit = 48073,
	priest_spell_Mind_Control = 605,
	priest_spell_Prayer_of_Healing = 48072,
	priest_spell_Shadow_Protection = 48169,
	priest_spell_Abolish_Disease = 552,
	priest_spell_Levitate = 1706,
	priest_spell_Greater_Heal = 48063,
	priest_spell_Prayer_of_Fortitude = 48162,
	priest_spell_Prayer_of_Shadow_Protection = 48170,
	priest_spell_Prayer_of_Spirit = 48074,
	priest_spell_Shadow_Word_Death = 48158,
	priest_spell_Binding_Heal = 48120,
	priest_spell_Shadowfiend = 34433,
	priest_spell_Prayer_of_Mending = 48113,
	priest_spell_Mass_Dispel = 32375,
	priest_spell_Divine_Hymn = 64843,
	priest_spell_Hymn_of_Hope = 64901,
	priest_spell_Mind_Sear = 53023,

	//Talent - Priest
	priest_spell_Vampiric_Touch = 48160, // Talent - Shadow
	priest_spell_Penance = 53007, // Talent - Discipline
	priest_spell_Lightwell = 48087, // Talent - Holy
	priest_spell_Desperate_Prayer = 48173, // Talent - Holy
	priest_spell_Circle_of_Healing = 48089, // Talent - Holy
	priest_spell_Mind_Flay = 48156 // Talent - Shadow

};

enum warlock_spell
{
	warlock_spell_Demon_Skin = 696,
	warlock_spell_Immolate = 47811,
	warlock_spell_Shadow_Bolt = 47809,
	warlock_spell_Summon_Imp = 688,
	warlock_spell_Corruption = 47813,
	warlock_spell_Curse_of_Weakness = 50511,
	warlock_spell_Life_Tap = 57946,
	warlock_spell_Curse_of_Agony = 47864,
	warlock_spell_Fear = 6215,
	warlock_spell_Create_Healthstone = 47878,
	warlock_spell_Drain_Soul = 47855,
	warlock_spell_Summon_Voidwalker = 697,
	warlock_spell_Health_Funnel = 47856,
	warlock_spell_Drain_Life = 47857,
	warlock_spell_Unending_Breath = 5697,
	warlock_spell_Create_Soulstone = 47884,
	warlock_spell_Searing_Pain = 47815,
	warlock_spell_Demon_Armor = 47889,
	warlock_spell_Rain_of_Fire = 47820,
	warlock_spell_Ritual_of_Summoning = 698,
	warlock_spell_Summon_Succubus = 712,
	warlock_spell_Eye_of_Kilrogg = 126,
	warlock_spell_Drain_Mana = 5138,
	warlock_spell_Sense_Demons = 5500,
	warlock_spell_Curse_of_Tongues = 11719,
	warlock_spell_Detect_Invisibility = 132,
	warlock_spell_Create_Firestone = 60220,
	warlock_spell_Banish = 18647,
	warlock_spell_Enslave_Demon = 61191,
	warlock_spell_Hellfire = 47823,
	warlock_spell_Summon_Felhunter = 691,
	warlock_spell_Curse_of_the_Elements = 47865,
	warlock_spell_Shadow_Ward = 47891,
	warlock_spell_Create_Spellstone = 47888,
	warlock_spell_Howl_of_Terror = 17928,
	warlock_spell_Death_Coil = 47860,
	warlock_spell_Soul_Fire = 47825,
	warlock_spell_Inferno = 1122,
	warlock_spell_Curse_of_Doom = 47867,
	warlock_spell_Ritual_of_Doom = 18540,
	warlock_spell_Fel_Armor = 47893,
	warlock_spell_Incinerate = 47838,
	warlock_spell_Soulshatter = 29858,
	warlock_spell_Ritual_of_Souls = 58887,
	warlock_spell_Seed_of_Corruption = 47836,
	warlock_spell_Shadowflame = 61290,
	warlock_spell_Demonic_Circle_Summon = 48018,
	warlock_spell_Demonic_Circle_Teleport = 48020,
	warlock_spell_Dreadsteed = 23161,

	//Talent - Warlock
	warlock_spell_Shadowburn = 47827, // Talent - Destruction
	warlock_spell_Shadowfury = 47847, // Talent - Destruction
	warlock_spell_Unstable_Affliction = 47843, // Talent - Affliction
	warlock_spell_Chaos_Bolt = 59172, // Talent - Destruction
	warlock_spell_Haunt = 59164, // Talent - Affliction
	warlock_spell_Dark_Pact = 59092 // Talent - Affliction

};


enum mount_spell
{
	mount_spell_Aprendiz_de_Jinete = 33388,
	mount_spell_Oficial_De_Jinete = 33392,
	mount_spell_Experto_Jinete = 34090,
	mount_spell_Artesano_Jinete = 34091,
	mount_spell_Vuelo_en_Clima_Frio = 54197
};

enum mount_item_id
{
	relentless_gladiators_frost_wyrm = 54860,
};

//////////////////////WELCOME MENU/////////////////////////////////
#define Class_Skills  "Me gustaria Aprender todo sobre mi clase"	   
//#define Glyph_Menu    "Quiero Comprar Glifos"
#define Talent_Skills "Maxskill y ResetTalents"
#define Riding_Skills "Deseo aprender a usar monturas"
#define nevermind 	  "[nevermind]"		 
#define back 		  "[back]"
//SUB WELCOME MENU//
#define SUB_MENU_TALENT_OPTION_1 "Maxskill"
#define SUB_MENU_TALENT_OPTION_2 "ResetTalent"
/////////////////////NPC ID MENU////////////////////////////////
/*You need to do 10 npc for this (Experimental)*/
//Change 0 To your NPC Vendor ID
enum GLYPH_NPC_ID
{
	GLYPH_NPC_ID_WARRIOR = 0,
	GLYPH_NPC_ID_PALADIN = 0,
	GLYPH_NPC_ID_HUNTER = 0,
	GLYPH_NPC_ID_MAGE = 0,
	GLYPH_NPC_ID_PRIEST = 0,
	GLYPH_NPC_ID_ROGUE = 0,
	GLYPH_NPC_ID_DRUID = 0,
	GLYPH_NPC_ID_WARLOCK = 0,
	GLYPH_NPC_ID_DK = 0,
	GLYPH_NPC_ID_SHAMAN = 0
};
enum CLASSES_MENU_ID
{
	MENU_WARRIOR = 1,
	MENU_PALADIN = 2,
	MENU_HUNTER = 3,
	MENU_ROGUE = 4,
	MENU_PRIEST = 5,
	MENU_DEATH_K = 6,
	MENU_SHAMAN = 7,
	MENU_MAGE = 8,
	MENU_WARLOCK = 9,
	MENU_DRUID = 10
};

enum OPTION_MENU_ID //11->50
{
	OPTION_MENU_ID_1 = 11,
	OPTION_MENU_ID_2 = 12,
	OPTION_MENU_ID_3 = 13,
	OPTION_MENU_ID_4 = 14
};

enum SUB_OPTION_MENU_ID //51->100
{
	SUB_OPTION_MENU_ID_1 = 51,
	SUB_OPTION_MENU_ID_2 = 52,
	SUB_OPTION_MENU_ID_3 = 53,
	SUB_OPTION_MENU_ID_4 = 54
};

enum BACK_OPTION //1000->
{
	BACK_OPTION_MENU_1 = 1000, //Main Menu
	BACK_OPTION_MENU_2 = 1001, //Other
};

class npc_welcome : public CreatureScript
{
public:
	npc_welcome() : CreatureScript("npc_welcome") { }

	bool OnGossipHello(Player* player, Creature* creature)
	{
		if (player->getLevel() >= 1)
		{
			{
				player->PrepareQuestMenu(creature->GetGUID());
				player->SendPreparedQuest(creature->GetGUID());
			}
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

			player->ADD_GOSSIP_ITEM(TRAINER_ICON, Talent_Skills, GOSSIP_SENDER_MAIN, OPTION_MENU_ID_1);
			player->ADD_GOSSIP_ITEM(TRAINER_ICON, Riding_Skills, GOSSIP_SENDER_MAIN, OPTION_MENU_ID_2);
			//player->ADD_GOSSIP_ITEM(VENDOR_ICON, Glyph_Menu, GOSSIP_SENDER_MAIN, OPTION_MENU_ID_3);
			player->SEND_GOSSIP_MENU(60025, creature->GetGUID());
		}
		else
		{
			player->PlayerTalkClass->SendCloseGossip();
			return false;
		}
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
	{
		WorldSession * PGS = player->GetSession();

		player->PlayerTalkClass->ClearMenus();
		{
			//	/**DUAL SPEC*////////////////////////////////////////////////
			player->CastSpell(player, 63680, true, NULL, NULL, player->GetGUID());
			player->CastSpell(player, 63624, true, NULL, NULL, player->GetGUID());
			//	/**//////////////////////////////////////////////////////////
			switch (action)
			{
				//=============================================WARRIOR=================================================//
			case MENU_WARRIOR:
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
				player->LearnSpell(202, false);	//?	 		
												//Spell Learned for different factions..
				if (player->GetTeam() == ALLIANCE) {
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
				if (player->GetTeam() == ALLIANCE) {
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
				if (player->GetTeam() == ALLIANCE) {
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
				else {
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
					//	player->LearnSpell(druid_spell_Feral_Charge_Bear, false); // charge farouche 2
					//	player->LearnSpell(druid_spell_Feral_Charge_Cat, false); // charge farouche
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
					//	player->LearnSpell(druid_spell_Mangle_Bear, false); mutilation farouche 2
					//	player->LearnSpell(druid_spell_Mangle_Cat, false); mutilation farouche
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
				player->SEND_GOSSIP_MENU(60025, creature->GetGUID());
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

			case SUB_OPTION_MENU_ID_2:
				player->ResetTalents(true);
				player->SendTalentsInfoData(false);
				//player->Monster("Your talents has been reset!", 0, true);
				player->SaveToDB();
				player->PlayerTalkClass->SendCloseGossip();
				break;

			case OPTION_MENU_ID_2:
				player->LearnSpell(mount_spell_Aprendiz_de_Jinete, false);
				player->LearnSpell(mount_spell_Oficial_De_Jinete, false);
				player->LearnSpell(mount_spell_Experto_Jinete, false);
				player->LearnSpell(mount_spell_Artesano_Jinete, false);
				player->LearnSpell(mount_spell_Vuelo_en_Clima_Frio, false);
				player->AddItem(relentless_gladiators_frost_wyrm, 1); //Flying-Ground
				player->PlayerTalkClass->SendCloseGossip();
				break;

			case OPTION_MENU_ID_3:
				if (player->getClass() == CLASS_WARRIOR)
				{
					PGS->SendListInventory(creature->GetGUID(), GLYPH_NPC_ID_WARRIOR);
				}
				if (player->getClass() == CLASS_PALADIN)
				{
					PGS->SendListInventory(creature->GetGUID(), GLYPH_NPC_ID_PALADIN);
				}
				if (player->getClass() == CLASS_MAGE)
				{
					PGS->SendListInventory(creature->GetGUID(), GLYPH_NPC_ID_MAGE);
				}
				if (player->getClass() == CLASS_HUNTER)
				{
					PGS->SendListInventory(creature->GetGUID(), GLYPH_NPC_ID_HUNTER);
				}
				if (player->getClass() == CLASS_DRUID)
				{
					PGS->SendListInventory(creature->GetGUID(), GLYPH_NPC_ID_DRUID);
				}
				if (player->getClass() == CLASS_WARLOCK)
				{
					PGS->SendListInventory(creature->GetGUID(), GLYPH_NPC_ID_WARLOCK);
				}
				if (player->getClass() == CLASS_PRIEST)
				{
					PGS->SendListInventory(creature->GetGUID(), GLYPH_NPC_ID_PRIEST);
				}
				if (player->getClass() == CLASS_ROGUE)
				{
					PGS->SendListInventory(creature->GetGUID(), GLYPH_NPC_ID_ROGUE);
				}
				if (player->getClass() == CLASS_DEATH_KNIGHT)
				{
					PGS->SendListInventory(creature->GetGUID(), GLYPH_NPC_ID_DK);
				}
				if (player->getClass() == CLASS_SHAMAN)
				{
					PGS->SendListInventory(creature->GetGUID(), GLYPH_NPC_ID_SHAMAN);
				}
				break;


			case BACK_OPTION_MENU_1://Main Menu
				if (player->getLevel() >= 1)
				{
					{
						player->PrepareQuestMenu(creature->GetGUID());
						player->SendPreparedQuest(creature->GetGUID());
					}
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

					player->ADD_GOSSIP_ITEM(TRAINER_ICON, Talent_Skills, GOSSIP_SENDER_MAIN, OPTION_MENU_ID_1);
					player->ADD_GOSSIP_ITEM(TRAINER_ICON, Riding_Skills, GOSSIP_SENDER_MAIN, OPTION_MENU_ID_2);
					//player->ADD_GOSSIP_ITEM(VENDOR_ICON, Glyph_Menu, GOSSIP_SENDER_MAIN, OPTION_MENU_ID_3);
					player->SEND_GOSSIP_MENU(60025, creature->GetGUID());
				}
				else
				{
					player->PlayerTalkClass->SendCloseGossip();
					return false;
				}
				break;

			}
		}
		return true;
	}
};



void AddSC_npc_welcome()
{
	new npc_welcome();
}