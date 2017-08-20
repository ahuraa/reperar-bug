#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "Spell.h"
#include "SpellAuraEffects.h"
#include "PassiveAI.h"

enum Events
{
	// Lord Jaraxxus
	EVENT_FEL_FIREBALL = 1,
	EVENT_FEL_LIGHTNING = 2,
	EVENT_INCINERATE_FLESH = 3,
	EVENT_NETHER_POWER = 4,
	EVENT_LEGION_FLAME = 5,
	EVENT_SUMMONO_NETHER_PORTAL = 6,
	EVENT_SUMMON_INFERNAL_ERUPTION = 7,

	// Mistress of Pain
	EVENT_SHIVAN_SLASH = 8,
	EVENT_SPINNING_STRIKE = 9,
	EVENT_MISTRESS_KISS = 10,
	EVENT_SUMMON_SHAMBLING_HORROR = 11,
	EVENT_PANIC = 12,
	EVENT_FRENZY = 13,
	EVENT_VENT = 14,
	EVENT_WARN_BONE_STORM = 15,
	EVENT_BONE_STORM_BEGIN = 14,
	EVENT_GROUP_SPECIAL = 1
};

enum Summons
{
	NPC_LEGION_FLAME = 34784,
	NPC_INFERNAL_VOLCANO = 34813,
	NPC_FEL_INFERNAL = 34815, // immune to all CC on Heroic (stuns, banish, interrupt, etc)
	NPC_NETHER_PORTAL = 34825,
	NPC_MISTRESS_OF_PAIN = 34826
};

enum BossSpells
{
	SPELL_LEGION_FLAME = 66197, // player should run away from raid because he triggers Legion Flame
	SPELL_LEGION_FLAME_EFFECT = 66201, // used by trigger npc
	SPELL_NETHER_POWER = 66228, // +20% of spell damage per stack, stackable up to 5/10 times, must be dispelled/stealed
	SPELL_FEL_LIGHTING = 66528, // jumps to nearby targets
	SPELL_FEL_FIREBALL = 66532, // does heavy damage to the tank, interruptable
	SPELL_INCINERATE_FLESH = 66237, // target must be healed or will trigger Burning Inferno
	SPELL_BURNING_INFERNO = 66242, // triggered by Incinerate Flesh
	SPELL_INFERNAL_ERUPTION = 66258, // summons Infernal Volcano
	SPELL_INFERNAL_ERUPTION_EFFECT = 66252, // summons Felflame Infernal (3 at Normal and inifinity at Heroic)
	SPELL_NETHER_PORTAL = 66269, // summons Nether Portal
	SPELL_NETHER_PORTAL_EFFECT = 66263, // summons Mistress of Pain (1 at Normal and infinity at Heroic)

	SPELL_BERSERK = 64238, // unused

						   // Mistress of Pain spells
	SPELL_SHIVAN_SLASH = 67098,
	SPELL_SPINNING_STRIKE = 66283,
	SPELL_MISTRESS_KISS = 66336,
	SPELL_FEL_INFERNO = 67047,
	SPELL_FEL_STREAK = 66494,
    SPELL_LORD_HITTIN = 66326,   // special effect preventing more specific spells be cast on the same player within 10 seconds
    SPELL_MISTRESS_KISS_DAMAGE_SILENCE = 66359,

};


enum Yells
{

	SAY_INTRO = 0,
	SAY_AGGRO = 1,
	EMOTE_LEGION_FLAME = 2,
	EMOTE_NETHER_PORTAL = 3,
	SAY_MISTRESS_OF_PAIN = 4,
	EMOTE_INCINERATE = 5,
	SAY_INCINERATE = 6,
	EMOTE_INFERNAL_ERUPTION = 7,
	SAY_INFERNAL_ERUPTION = 8,
	SAY_KILL_PLAYER = 9,
	SAY_DEATH = 10,
	SAY_BERSERK = 11
};


enum Spells
{
	SPELL_WILFRED_PORTAL = 68424,
	SPELL_JARAXXUS_CHAINS = 67924,
	SPELL_CORPSE_TELEPORT = 69016,
	SPELL_DESTROY_FLOOR_KNOCKUP = 68193,
	SPELL_NECROTIC_PLAGUE = 70337,
	SPELL_SUMMON_SHAMBLING_HORROR = 70372,
	SPELL_PANIC = 19408,
	SPELL_FRENZY = 19451,
	SPELL_FLAME_VENTS = 62396,

	// Lord Marrowgar
	SPELL_BONE_SLICE = 69055,
	SPELL_BONE_STORM = 69076,


};

bool _enraged;


enum DataTypes
{
	BOOS_ZEROS = 1
};

enum Texts { EMOTE_FRENZY = 0 };


class boss_zeros : public CreatureScript
{
public:
	boss_zeros() : CreatureScript("boss_zeros") { }
	
	struct boss_zerosAI  : public WorldBossAI
	{
		boss_zerosAI(Creature* creature) : WorldBossAI(creature)
		{
			_enraged = false;
		}

		void Reset() override
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/) override
		{
			events.ScheduleEvent(EVENT_SUMMON_SHAMBLING_HORROR, 5 * IN_MILLISECONDS);
			events.ScheduleEvent(EVENT_FEL_FIREBALL, 5 * IN_MILLISECONDS);
			events.ScheduleEvent(EVENT_FEL_LIGHTNING, urand(10 * IN_MILLISECONDS, 15 * IN_MILLISECONDS));
			events.ScheduleEvent(EVENT_INCINERATE_FLESH, urand(20 * IN_MILLISECONDS, 25 * IN_MILLISECONDS));
			events.ScheduleEvent(EVENT_NETHER_POWER, 40 * IN_MILLISECONDS);
			events.ScheduleEvent(EVENT_LEGION_FLAME, 30 * IN_MILLISECONDS);
			events.ScheduleEvent(EVENT_SUMMONO_NETHER_PORTAL, 20 * IN_MILLISECONDS);
			events.ScheduleEvent(EVENT_SUMMON_INFERNAL_ERUPTION, 80 * IN_MILLISECONDS);
			events.ScheduleEvent(EVENT_PANIC, 20000);
			events.ScheduleEvent(EVENT_FRENZY, 30000);
			events.ScheduleEvent(EVENT_VENT, 20 * IN_MILLISECONDS);
			me->RemoveAurasDueToSpell(SPELL_BONE_STORM);
			events.ScheduleEvent(EVENT_WARN_BONE_STORM, urand(45000, 50000));
		}



		void KilledUnit(Unit* who) override
		{
			if (who->GetTypeId() == TYPEID_PLAYER)
				Talk(SAY_KILL_PLAYER);
		}

		void JustDied(Unit* /*killer*/) override
		{
			_JustDied();
			Talk(SAY_DEATH);
		}

		void UpdateAI(uint32 diff) override
		{
			if (!UpdateVictim())
				return;

			events.Update(diff);

			if (me->HasUnitState(UNIT_STATE_CASTING))
				return;

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_FEL_FIREBALL:
					DoCastVictim(SPELL_FEL_FIREBALL);
					events.ScheduleEvent(EVENT_FEL_FIREBALL, urand(10 * IN_MILLISECONDS, 15 * IN_MILLISECONDS));
					return;
				case EVENT_FEL_LIGHTNING:
					if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true, -SPELL_LORD_HITTIN))
						DoCast(target, SPELL_FEL_LIGHTING);
					events.ScheduleEvent(EVENT_FEL_LIGHTNING, urand(10 * IN_MILLISECONDS, 15 * IN_MILLISECONDS));
					return;
				case EVENT_INCINERATE_FLESH:
					if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 0.0f, true, -SPELL_LORD_HITTIN))
					{
						Talk(EMOTE_INCINERATE, target);
						Talk(SAY_INCINERATE);
						DoCast(target, SPELL_INCINERATE_FLESH);
					}
					events.ScheduleEvent(EVENT_INCINERATE_FLESH, urand(20 * IN_MILLISECONDS, 25 * IN_MILLISECONDS));
					return;
				case EVENT_NETHER_POWER:
					me->CastCustomSpell(SPELL_NETHER_POWER, SPELLVALUE_AURA_STACK, RAID_MODE<uint32>(5, 10, 5, 10), me, true);
					events.ScheduleEvent(EVENT_NETHER_POWER, 40 * IN_MILLISECONDS);
					return;
				case EVENT_LEGION_FLAME:
					if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 0.0f, true, -SPELL_LORD_HITTIN))
					{
						Talk(EMOTE_LEGION_FLAME, target);
						DoCast(target, SPELL_LEGION_FLAME);
					}
					events.ScheduleEvent(EVENT_LEGION_FLAME, 30 * IN_MILLISECONDS);
					return;
				case EVENT_SUMMONO_NETHER_PORTAL:
					Talk(EMOTE_NETHER_PORTAL);
					Talk(SAY_MISTRESS_OF_PAIN);
					DoCast(SPELL_NETHER_PORTAL);
					events.ScheduleEvent(EVENT_SUMMONO_NETHER_PORTAL, 2 * MINUTE*IN_MILLISECONDS);
					return;
				case EVENT_SUMMON_INFERNAL_ERUPTION:
					Talk(EMOTE_INFERNAL_ERUPTION);
					Talk(SAY_INFERNAL_ERUPTION);
					DoCast(SPELL_INFERNAL_ERUPTION);
					events.ScheduleEvent(EVENT_SUMMON_INFERNAL_ERUPTION, 2 * MINUTE*IN_MILLISECONDS);
					return;
				case EVENT_SUMMON_SHAMBLING_HORROR:
					DoCast(SPELL_SUMMON_SHAMBLING_HORROR);
					events.ScheduleEvent(EVENT_SUMMON_SHAMBLING_HORROR, 2 * MINUTE*IN_MILLISECONDS);
					return;
				case EVENT_PANIC:
					DoCastVictim(SPELL_PANIC);
					events.ScheduleEvent(EVENT_PANIC, 35000);
					return;
				case EVENT_FRENZY:
					Talk(EMOTE_FRENZY);
					DoCast(me, SPELL_FRENZY);
					events.ScheduleEvent(EVENT_FRENZY, 15000);
					return;
				case EVENT_VENT:
					DoCastAOE(SPELL_FLAME_VENTS);
					events.ScheduleEvent(EVENT_VENT, 20 * IN_MILLISECONDS);
					return;
				case EVENT_WARN_BONE_STORM:
					me->FinishSpell(CURRENT_MELEE_SPELL, false);
					DoCast(me, SPELL_BONE_STORM);
					events.DelayEvents(3000, EVENT_GROUP_SPECIAL);
					events.ScheduleEvent(EVENT_BONE_STORM_BEGIN, 3050);
					events.ScheduleEvent(EVENT_WARN_BONE_STORM, urand(90000, 95000));
					return;
				}
			}


			DoMeleeAttackIfReady();
		}

	};

	CreatureAI* GetAI(Creature* creature) const override
	{
		return new boss_zerosAI(creature);
	}


};



void AddSC_World_Boss()
{  
	new boss_zeros();
}
