/*
 * Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

// This is where scripts' loading functions should be declared:
void AddSC_Transmogrification();
void AddSC_npc_1v1arena();
void AddSC_NPC_TransmogDisplayVendor();
//void AddSC_premium_commandscript();
//void AddSC_PremiumLogin();
void AddSC_telenpc();
void AddSC_Npc_Enchants();
void AddSC_Professions_NPC();
void AddSC_Npc_Tools();
//void AddSC_cs_world_chat();
void AddSC_announce_login();

void AddSC_World_Chat();
void AddSC_System_Censure();
void AddSC_Boss_Announcer();
void AddSC_Beastmaster_NPC();
void AddSC_SpellRegulator();
void AddSC_npc_welcome();
void AddSC_World_Boss();


// The name of this function should match:
// void Add${NameOfDirectory}Scripts()
void AddCustomScripts()
{
    AddSC_Transmogrification();
	AddSC_npc_1v1arena();
	AddSC_NPC_TransmogDisplayVendor();
	//AddSC_premium_commandscript();
	//AddSC_PremiumLogin();
	AddSC_telenpc();
	AddSC_Npc_Enchants();
	AddSC_Professions_NPC();
	AddSC_Npc_Tools();
	//AddSC_cs_world_chat();
	AddSC_announce_login();
	
	AddSC_World_Chat();
	AddSC_System_Censure();
	AddSC_Boss_Announcer();
	AddSC_Beastmaster_NPC();
	AddSC_SpellRegulator();
	AddSC_npc_welcome();
	AddSC_World_Boss();
}