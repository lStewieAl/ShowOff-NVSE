﻿#pragma once

#include "MiscHooks.h"
#include "SafeWrite.h"
#include "GameSettings.h"
#include "MenuHooks.h"

DEFINE_COMMAND_ALT_PLUGIN(SetPlayerCanPickpocketEquippedItems, SetPCCanStealEqItems, "Toggles the ability to pickpocket equipped items.", false, kParams_OneInt);
DEFINE_CMD_ALT_COND_PLUGIN(GetPlayerCanPickpocketEquippedItems, GetPCCanStealEqItems, "Checks if the player can pickpocket equipped items.", false, NULL);
DEFINE_CMD_COND_PLUGIN(GetPCHasSleepWaitOverride, "Returns whether or not the player has a Sleep/Wait prevention override", false, NULL);
DEFINE_COMMAND_PLUGIN(SetPCHasSleepWaitOverride, "Sets whether or not the player has a Sleep/Wait prevention override", false, kParams_OneInt);
DEFINE_CMD_COND_PLUGIN(IsWeaponMelee, "Returns 1 if the weapon's base form is of one of the three weapon types belonging to melee-range weapons.", true, kParams_OneOptionalObjectID);
DEFINE_CMD_COND_PLUGIN(IsEquippedWeaponMelee, "Returns 1 if the calling actor's equipped weapon's base form is of one of the three weapon types belonging to melee-range weapons.", true, NULL);
DEFINE_CMD_COND_PLUGIN(IsWeaponRanged, "Returns 1 if the weapon's base form is one of the weapon types belonging to NON melee-range weapons.", true, kParams_OneOptionalObjectID);
DEFINE_CMD_COND_PLUGIN(IsEquippedWeaponRanged, "Returns 1 if the calling actor's equipped weapon's base form is one of the weapon types belonging to NON melee-range weapons.", true, NULL);
DEFINE_CMD_COND_PLUGIN(GetChallengeProgress, "Returns the progress made on a challenge.", false, kParams_OneChallenge)
DEFINE_CMD_COND_PLUGIN(GetPCHasScriptedFastTravelOverride, "Returns whether or not the player is restricted by EnableFastTravel", false, NULL);
DEFINE_CMD_COND_PLUGIN(GetPCCanFastTravel, "", false, NULL);
DEFINE_CMD_ALT_COND_PLUGIN(GetWeaponHasFlag, WeaponHasFlag, "", false, kParams_OneInt_OneOptionalObjectID);
DEFINE_COMMAND_ALT_PLUGIN(SetWeaponFlag, SetWeaponHasFlag, "", false, kParams_TwoInts_OneOptionalObjectID);
DEFINE_CMD_ALT_COND_PLUGIN(GetActorHasBaseFlag, ActorHasBaseFlag, "", false, kParams_OneInt_OneOptionalActorBase);
DEFINE_COMMAND_ALT_PLUGIN(ForceWeaponJamAnim, ForceJamAnim, "", true, NULL);
#if _DEBUG
DEFINE_COMMAND_ALT_PLUGIN(ForceWeaponJamAnimAlt, ForceJamAnimAlt, "", true, NULL);
#endif
DEFINE_CMD_ALT_COND_PLUGIN(GetCalculatedSkillPoints, GetCalculatedSkillPointsEarnedPerLevel, "Gets the amount of skill points the player would get for their current level.", false, kParams_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(GetLevelUpMenuPoints, "", false, kParams_TwoOptionalInts);
DEFINE_CMD_ALT_COND_PLUGIN(GetCalculatedPerkPoints, GetCalculatedPerkPointsEarnedPerLevel, "Gets the amount of perk points the player would get for their current level.", false, kParams_OneOptionalInt);
DEFINE_COMMAND_ALT_PLUGIN(GetLevelUpMenuCurrentPage, GetLevelUpMenuPage, "", false, NULL);
DEFINE_COMMAND_ALT_PLUGIN(SetLevelUpMenuCurrentPage, SetLevelUpMenuPage, "", false, kParams_OneInt);
DEFINE_COMMAND_ALT_PLUGIN(ShowPerkMenu, IfIDecideToGoWithYourFunctionWhatAreThePerks, "Opens the Level-Up menu to the Perk-menu page, and prevents going back to Skills tab.", false, kParams_JIP_OneOptionalInt_OneOptionalString);
DEFINE_COMMAND_ALT_PLUGIN(ShowSkillMenu, ShowSkillsMenu, "Opens the Level-Up menu to the Skills page, and sets that this is the last page (no visiting perks).", false, kParams_TwoOptionalInts_OneOptionalString);
DEFINE_COMMAND_PLUGIN(GetLevelUpMenuUnspentPoints, "", false, kParams_OneInt);
DEFINE_COMMAND_PLUGIN(SetLevelUpMenuCanExitEarly, "", false, kParams_OneInt);  //todo: Get is a WIP, also "SetLevelUpMenuCanExitEarly 0" does not work currently.
DEFINE_COMMAND_PLUGIN(SetLevelUpMenuPoints, "", false, kParams_TwoInts);
DEFINE_COMMAND_PLUGIN(GetExplosionRefSource, "", true, NULL);
DEFINE_COMMAND_PLUGIN(SetExplosionRefSource, "", true, kParams_OneActorRef);
DEFINE_COMMAND_PLUGIN(GetExplosionRefRadius, "Accounts for AdjustExplosionRadius perk entry point.", true, NULL);
DEFINE_COMMAND_PLUGIN(SetExplosionRefRadius, "", true, kParams_OneFloat);
DEFINE_COMMAND_ALT_PLUGIN(SetNoEquipShowOff, SetNoEquipSO, "Sets whether or not there's a prevention for an item baseform from being activated from an actor's inventory.", false, kParams_OneForm_OneInt_OneOptionalScript);
DEFINE_COMMAND_ALT_PLUGIN(GetNoEquipShowOff, GetNoEquipSO, "Returns whether or not there's a prevention for an item baseform from being activated from an actor's inventory.", false, kParams_OneForm_OneInt);
DEFINE_COMMAND_ALT_PLUGIN(SetOwnershipTemp, ImGoingToBorrowThis, "A mix of SetOwnership and SetCellOwnership, but non-savebaked.", false, kParams_TwoOptionalForms);
DEFINE_COMMAND_ALT_PLUGIN(GetCalculatedAPCost, GetCalculatedWeaponAttackAPCost, "", false, kParams_OneInt_OneOptionalForm);


bool Cmd_SetPlayerCanPickpocketEquippedItems_Execute(COMMAND_ARGS)
{
	UInt32 bOn;
	if (NUM_ARGS && ExtractArgsEx(EXTRACT_ARGS_EX, &bOn))
	{
		const bool bCheck = PickpocketEquippedItems::CanPlayerPickpocketEqItems();
		if (bOn && !bCheck)
		{
			// replace check in ContainerMenu::ShouldHideItem while pickpocketting for item being worn, with a check the target is a child
			//Courtesy of lStewieAl!
			WriteRelCall(0x75E87A, UInt32(ContainerMenuCheckIsTargetChild));
		}
		else if (!bOn && bCheck)
		{
			// revert the change to the check in ContainerMenu::ShouldHideItem.
			WriteRelCall(0x75E87A, 0x4BDDD0);
		}
	}
	return true;
}

bool Cmd_GetPlayerCanPickpocketEquippedItems_Eval(COMMAND_ARGS_EVAL)
{
	*result = PickpocketEquippedItems::CanPlayerPickpocketEqItems();
	return true;
}
bool Cmd_GetPlayerCanPickpocketEquippedItems_Execute(COMMAND_ARGS)
{
	*result = PickpocketEquippedItems::CanPlayerPickpocketEqItems();
	return true;
}

bool Cmd_GetPCHasSleepWaitOverride_Eval(COMMAND_ARGS_EVAL)
{
	*result = !g_thePlayer->canSleepWait;
	return true;
}
bool Cmd_GetPCHasSleepWaitOverride_Execute(COMMAND_ARGS)
{
	Cmd_GetPCHasSleepWaitOverride_Eval(thisObj, NULL, NULL, result);
	return true;
}

bool Cmd_SetPCHasSleepWaitOverride_Execute(COMMAND_ARGS)
{
	UInt32 bOn;
	if (ExtractArgs(EXTRACT_ARGS, &bOn))
		g_thePlayer->canSleepWait = !bOn;
	return true;
}

bool Cmd_IsWeaponMelee_Eval(COMMAND_ARGS_EVAL)
{
	//Console_Print("thisObj: [%0.8X]", thisObj->baseForm->GetId());
	*result = 0;
	TESForm* form;
	if (arg1)
		form = (TESForm*)arg1;
	else if (thisObj)
		form = thisObj->baseForm;
	else return true;

	auto const weapon = DYNAMIC_CAST(form, TESForm, TESObjectWEAP);
	if (!weapon) return true;

	const UINT8 weapType = weapon->eWeaponType;
	*result = weapType <= 2;
	return true;
}
bool Cmd_IsWeaponMelee_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESObjectWEAP* weapon = NULL;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &weapon)) return true;

	return Cmd_IsWeaponMelee_Eval(thisObj, weapon, 0, result);
}

bool Cmd_IsEquippedWeaponMelee_Eval(COMMAND_ARGS_EVAL)
{
	// Not recommended to use this function for certain perk effects, like Calculate Weap. Damage;
	// since it will affect the DAM that appears in the UI for other weapons, as long as the currently equipped weapon is a melee weap.
	*result = false;
	if (thisObj)
	{
		if (!thisObj->IsActor()) return true;
		TESObjectWEAP* weapon = ((Actor*)thisObj)->GetEquippedWeapon();
		if (weapon)
			*result = weapon->eWeaponType <= 2;
		else
		{
			*result = true;
			if (g_ShowFuncDebug)
				Console_Print("IsEquippedWeaponMelee >> 1 >> No equipped weapon found, assuming that the default unarmed is equipped.");
		}
	}
	return true;
}
bool Cmd_IsEquippedWeaponMelee_Execute(COMMAND_ARGS)
{
	return Cmd_IsEquippedWeaponMelee_Eval(thisObj, nullptr, nullptr, result);
}

bool Cmd_IsWeaponRanged_Eval(COMMAND_ARGS_EVAL)
{
	//Console_Print("thisObj: [%0.8X]", thisObj->baseForm->GetId());
	*result = 0;
	TESForm* form;
	if (arg1)
	{
		form = (TESForm*)arg1;
	}
	else if (thisObj)
	{
		form = thisObj->baseForm;
	}
	else return true;

	auto const weapon = DYNAMIC_CAST(form, TESForm, TESObjectWEAP);
	if (!weapon) return true;

	const UINT8 weapType = weapon->eWeaponType;
	*result = weapType >= 3 && weapType <= 13;

	return true;
}
bool Cmd_IsWeaponRanged_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESObjectWEAP* weapon = NULL;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &weapon)) return true;

	return Cmd_IsWeaponRanged_Eval(thisObj, weapon, 0, result);
}

bool Cmd_IsEquippedWeaponRanged_Eval(COMMAND_ARGS_EVAL)
{
	*result = 0;
	if (thisObj)
	{
		if (!thisObj->IsActor()) return true;
		if (const TESObjectWEAP* weapon = ((Actor*)thisObj)->GetEquippedWeapon())
		{
			const UINT8 weapType = weapon->eWeaponType;
			*result = weapType >= 3 && weapType <= 13;
		}
	}
	return true;
}
bool Cmd_IsEquippedWeaponRanged_Execute(COMMAND_ARGS)
{
	return Cmd_IsEquippedWeaponRanged_Eval(thisObj, nullptr, nullptr, result);
}


bool Cmd_GetChallengeProgress_Execute(COMMAND_ARGS)
{
	TESChallenge* challenge;
	if (ExtractArgs(EXTRACT_ARGS, &challenge) && IS_TYPE(challenge, TESChallenge))
		*result = challenge->progress;
	else *result = 0;
	return true;
}
bool Cmd_GetChallengeProgress_Eval(COMMAND_ARGS_EVAL)
{
	*result = 0;
	if (arg1)
	{
		const auto challenge = (TESChallenge*)arg1;
		if (IS_TYPE(challenge, TESChallenge))
			*result = challenge->progress;
	}
#if _DEBUG
	Console_Print("GetChallengeProgress >> %f", *result);
#endif
	return true;
}


bool Cmd_GetPCHasScriptedFastTravelOverride_Eval(COMMAND_ARGS_EVAL)
{
	*result = (g_thePlayer->byte66D & 1) == 0;
	return true;
}
bool Cmd_GetPCHasScriptedFastTravelOverride_Execute(COMMAND_ARGS)
{
	*result = (g_thePlayer->byte66D & 1) == 0;
	return true;
}

bool Cmd_GetPCCanFastTravel_Eval(COMMAND_ARGS_EVAL)
{
	// Credits to Jazz for the "silence QueueUIMessage" trick (see AddNoteNS).
	SafeWrite8((UInt32)QueueUIMessage, 0xC3);	// RETN
	const auto canFastTravelAddr = GetRelJumpAddr(0x798026); // call the function indirectly for compatibility with Stewie tweaks, kudos to Stewie.
	*result = ThisStdCall<bool>(canFastTravelAddr, g_thePlayer);
	//*result = ThisStdCall<bool>((UInt32)0x93D660, g_thePlayer);
	SafeWrite8((UInt32)QueueUIMessage, 0x55);	// PUSH EBP
	return true;
}
bool Cmd_GetPCCanFastTravel_Execute(COMMAND_ARGS)
{
	return Cmd_GetPCCanFastTravel_Eval(thisObj, 0, 0, result);
}

bool Cmd_GetWeaponHasFlag_Eval(COMMAND_ARGS_EVAL)
{
	*result = 0;
	UInt32 flagToCheck = (UInt32)arg1;
	if (flagToCheck > 21) return true;
	TESForm* form;
	if (arg2) form = (TESForm*)arg2;
	else if (thisObj) form = thisObj->baseForm;
	else return true;
	auto const weapon = DYNAMIC_CAST(form, TESForm, TESObjectWEAP);
	if (!weapon) return true;
	if (flagToCheck < 8)  //check Flags1 (0-7)
	{
		*result = weapon->weaponFlags1.Extract(flagToCheck);
	}
	else  //check Flags2 (0-13)
	{
		flagToCheck -= 8;  //set the base to 0. At flagToCheck == 8, this equals 0.
		*result = weapon->weaponFlags2.Extract(flagToCheck);
	}
	return true;
}
bool Cmd_GetWeaponHasFlag_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32 flagToCheck;
	TESObjectWEAP* weapon = NULL;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &flagToCheck, &weapon)) return true;
	return Cmd_GetWeaponHasFlag_Eval(thisObj, (void*)flagToCheck, weapon, result);
}

bool Cmd_SetWeaponFlag_Execute(COMMAND_ARGS)
{
	*result = false; //bSuccess
	UInt32 flag, bOn;
	TESObjectWEAP* weapon = nullptr;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &flag, &bOn, &weapon) || flag > 21)
		return true;
	if (weapon = DYNAMIC_CAST(TryExtractBaseForm(weapon, thisObj), TESForm, TESObjectWEAP))
	{
		if (flag < 8)  //change Flags1 (0-7)
		{
			weapon->weaponFlags1.WriteBit(flag, bOn);
		}
		else  //change Flags2 (0-13)
		{
			flag -= 8;  //set the base to 0. At flagToCheck == 8, this equals 0.
			weapon->weaponFlags2.WriteBit(flag, bOn);
		}
		*result = true;
	}
	return true;
}

bool Cmd_GetActorHasBaseFlag_Eval(COMMAND_ARGS_EVAL)
{
	*result = 0;
	UInt32 flagToCheck = (UInt32)arg1;
	if (flagToCheck > 31) return true;
	TESForm* form;
	if (arg2) form = (TESForm*)arg2;
	else if (thisObj) form = thisObj->baseForm;
	else return true;
	auto const actor = DYNAMIC_CAST(form, TESForm, TESActorBase);
	if (!actor) return true;
	if (flagToCheck < 16)  //check FlagsLow (0-15)
	{
		const UInt32 lowFlags = actor->baseData.flags & 0xFFFF;  //copied from NVSE's GetActorBaseFlagsLow
		*result = (lowFlags >> flagToCheck) & 1;
	}
	else  //check FlagsHigh (0-15)
	{
		flagToCheck -= 16;  //set the base to 0. At flagToCheck == 16, this equals 0.
		const UInt32 highFlags = (actor->baseData.flags >> 16) & 0xFFFF;  //copied from NVSE's GetActorBaseFlagsHigh
		*result = (highFlags >> flagToCheck) & 1;
	}
	return true;
}
bool Cmd_GetActorHasBaseFlag_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32 flagToCheck;
	TESActorBase* actor = NULL;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &flagToCheck, &actor)) return true;
	return Cmd_GetActorHasBaseFlag_Eval(thisObj, (void*)flagToCheck, actor, result);
}

bool Cmd_RemoveAllItemsShowOff_Execute(COMMAND_ARGS)
{
	*result = 0;
	enum FunctionFlags
	{
		kFlag_None = 0,
		kFlag_RetainOwnership =						1 << 0,  //only applies if a target is specified
		kFlag_SuppressMessages =					1 << 1,  //only applies if a target is specified
		kFlag_AllowRemovalOfQuestItemsFromPlayer =	1 << 2,
		kFlag_AllowRemovalOfUnplayableBipedItems =	1 << 3,
		kFlag_Unk1 =								1 << 4,  // todo: figure out what these two bools do for the vanilla function.
		kFlag_Unk2 =								1 << 5,
		kFlag_RunOnUnequipEvent =					1 << 6,
		kFlag_IgnoreAllUnplayableItems =			1 << 7,  // Overrides kFlag_AllowRemovalOfUnplayableBipedItems. TODO: not yet implemented.

		kFlag_Default = kFlag_RunOnUnequipEvent
	};
	UInt32 flags = kFlag_Default;
	SInt32 typeCode = -1;  //-1 = all
	TESObjectREFR* targetContainer = nullptr;
	BGSListForm* exceptionFormList = nullptr;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &flags, &typeCode, &targetContainer, &exceptionFormList)) return true;
	if (!thisObj || !typeCode || !thisObj->GetContainer() || (targetContainer && !targetContainer->GetContainer()))
		return true;
	//ExtraContainerChanges* xChanges = (ExtraContainerChanges*)thisObj->extraDataList.GetByType(kExtraData_ContainerChanges);  //ripped from NVSE's EquipItem2
	void* xChanges = ThisStdCall<void*>(0x418520, &thisObj->extraDataList);
	if (!xChanges) return true;

	// Extract flags
	bool const retainOwnership = flags & kFlag_RetainOwnership;
	bool const suppressMessages = flags & kFlag_SuppressMessages;
	bool const removeQuestItemsIfPlayer = flags & kFlag_AllowRemovalOfQuestItemsFromPlayer;
	bool const removeUnplayableBipedItems = flags & kFlag_AllowRemovalOfUnplayableBipedItems;
	bool const unk1 = flags & kFlag_Unk1;
	bool const unk2 = flags & kFlag_Unk2;
	bool const runOnUnequipEvent = flags & kFlag_RunOnUnequipEvent;
	bool const ignoreAllUnplayableItems = flags & kFlag_IgnoreAllUnplayableItems;

	// Modify the code for RemoveAllItems
	if (removeQuestItemsIfPlayer)
	{
		WriteRelJump(0x4CE4B8, 0x4CE559);  // make the long jump at 0x4CE4B8 unconditional
		WriteRelJump(0x4CEDCE, 0x4CEE75);  // same concept
	}
	if (!ignoreAllUnplayableItems)
	{
		if (removeUnplayableBipedItems)
		{
			SafeWrite8(0x4CE571, 0xEB);  // make short jump unconditional
			PatchMemoryNop(0x4CED5D, 6);  // make the long jump never happen
		}
	}
	else
	{
		//todo: Write a jmp to extract the form mid-loop.

		
		// Check the form via IsItemPlayable. If it passes, jmp back to removal, otherwise jmp to go to the next form.
	}

	if (runOnUnequipEvent)
	{
		//TODO
	}

	// Call RemoveAllItems with the new modifications
	ThisStdCall<void>(0x4CE340, xChanges, thisObj, targetContainer, unk1, retainOwnership, unk2, suppressMessages, typeCode, exceptionFormList);

	// Revert code modifications
	if (removeQuestItemsIfPlayer)
	{
		WriteRelJe(0x4CE4B8, 0x4CE559); // revert back to long Jump if Zero
		WriteRelJe(0x4CEDCE, 0x4CEE75); // same concept
	}
	if (!ignoreAllUnplayableItems)
	{
		if (removeUnplayableBipedItems)
		{
			SafeWrite8(0x4CE571, 0x74); // revert back to short Jump if Zero
			WriteRelJe(0x4CED5D, 0x4CFBCA); // re-write long Jump if Zero
		}
	}
	else
	{
		// TODO
	}
	
	// Wrap up
	ThisStdCall<void>(0x952C30, g_thePlayer, thisObj); // ComputeShouldRecalculateQuestTargets()
	*result = 1; //function worked as expected.
	return true;
}

bool Cmd_ForceWeaponJamAnim_Execute(COMMAND_ARGS)
{
	*result = false;
	if (IS_ACTOR(thisObj))
	{
		const auto actor = (Actor*)thisObj;
		if (auto const weapn = actor->GetEquippedWeapon())
		{
			// Copies the code at 0x89667E for post-reload jamming.
			const auto animGroupID = ThisStdCall<UInt32>(0x51E2A0, weapn, 0) + 23;  // TESObjectWEAP::GetReloadAnimGroup + 23
			const auto animKey = ThisStdCall<UInt16>(0x897910, actor, animGroupID, 0, 0, 0);  //Actor__GetAnimKey
			if (CdeclCall<UInt32>(0x5F2440, animKey) == animGroupID)  // calls AnimGroupID::GetGroupID, which gets the lowers bits of animKey.
			{
				if (const auto animData = actor->GetAnimData())
				{
					ThisStdCall<void*>(0x8B28C0, actor, animGroupID, animData);  // Actor::8B28C0
					auto const animSeqElem = animData->animSequence[4];  // 4 = kSequence_Weapon
					actor->SetAnimActionAndSequence(9, animSeqElem);  // 9 = kAnimAction_Reload
					actor->Unk_12C(animKey, true);
					*result = true;
				}
			}
		}
	}
	return true;
}

#if _DEBUG
bool Cmd_ForceWeaponJamAnimAlt_Execute(COMMAND_ARGS)
{
	*result = false;
	if (IS_ACTOR(thisObj))
	{
		const auto actor = (Actor*)thisObj;
		if (auto const weapn = actor->GetEquippedWeapon())
		{
			// Copies the code at 0x893884 for weapon condition jamming.
			const auto animGroupID = ThisStdCall<UInt32>(0x51E2A0, weapn, 0) + 23;  // TESObjectWEAP::GetReloadAnimGroup + 23
			const auto animKey = ThisStdCall<UInt16>(0x897910, actor, animGroupID, 0, 0, 0);  //Actor__GetAnimKey
			if (CdeclCall<UInt32>(0x5F2440, animKey) == animGroupID)  // calls AnimGroupID::GetGroupID, which gets the lowers bits of animKey.
			{
				if (actor->GetAnimData())
				{
					actor->animGroupID110 = animGroupID;  //still triggers JIP OnReload...
					*result = true;
				}
			}
		}
	}
	return true;
}
#endif


bool Cmd_GetCalculatedSkillPoints_Eval(COMMAND_ARGS_EVAL)
{
	// Vanilla code at 0x648BC0 replicated thanks to Nukem and lStewieAl's efforts (which I slightly tweaked).
	UInt32 levelOverride = 0;
	if (arg1) levelOverride = (UInt32)arg1;

	const auto avOwner = &g_thePlayer->avOwner;
	auto level = levelOverride ? levelOverride : avOwner->GetLevel();
	level += LevelUpMenu::GetSingleton() ? 0 : 1;  // Add +1 level to accurately predict the outcome for the next level up, if not in levelup menu.
	auto intelligence = avOwner->GetNormalizedPermanentAV(kAVCode_Intelligence);
	intelligence = std::min<decltype(intelligence)>(intelligence, 10);

	auto const calculateSkillPointsAddr = GetRelJumpAddr(0x648BF0); // get the function address indirectly for compatibility with lStewieAl's tweaks (see patchCustomSkillPointFormula())
	float skillPoints = CdeclCall<int>(calculateSkillPointsAddr, intelligence, level);
	ApplyPerkModifiers(kPerkEntry_AdjustGainedSkillPoints, g_thePlayer, &skillPoints);
	*result = skillPoints;
	return true;
}
bool Cmd_GetCalculatedSkillPoints_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32 levelOverride = 0;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &levelOverride))
		return true;
	return Cmd_GetCalculatedSkillPoints_Eval(thisObj, (void*)levelOverride, 0, result);
}


bool Cmd_GetLevelUpMenuPoints_Execute(COMMAND_ARGS)
{
	*result = -1;
	UInt32 bCheckPerks = false;  // if false, will check for Skills instead.
	UInt32 bCheckAssigned = false;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &bCheckPerks, &bCheckAssigned))
		return true;

	if (auto const menu = LevelUpMenu::GetSingleton())
	{
		if (bCheckPerks)
		{
			if (bCheckAssigned)
				*result = menu->numAssignedPerks;
			else
			{
				// menu->numPerksToAssign is always set to something in vanilla, it's the availablePerks.Empty() that determines if no perk menu is shown.
				*result = menu->perksList.Empty() ? 0 : menu->numPerksToAssign;
			}
		}
		else  // Check for Skills
		{
			if (bCheckAssigned)
				*result = menu->numAssignedSkillPoints;
			else
				*result = menu->numSkillPointsToAssign;
		}
	}
	return true;
}


bool Cmd_GetCalculatedPerkPoints_Eval(COMMAND_ARGS_EVAL)
{
	UInt32 levelOverride = 0;
	if (arg1) levelOverride = (UInt32)arg1;

	const auto avOwner = &g_thePlayer->avOwner;
	auto level = levelOverride ? levelOverride : avOwner->GetLevel();
	level += LevelUpMenu::GetSingleton() ? 0 : 1;  // Add +1 level to accurately predict the outcome for the next level up, if not in levelup menu.
	auto const gs_iLevelsPerPerk = GetIntGameSetting(0x11CD074);

	if (level % gs_iLevelsPerPerk)  // no perks can be chosen
		*result = 0;
	else
		*result = 1;

	return true;
}
bool Cmd_GetCalculatedPerkPoints_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32 levelOverride = 0;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &levelOverride))
		return true;
	return Cmd_GetCalculatedPerkPoints_Eval(thisObj, (void*)levelOverride, 0, result);
}


bool Cmd_GetLevelUpMenuCurrentPage_Execute(COMMAND_ARGS)
{
	*result = -1;
	if (auto const menu = LevelUpMenu::GetSingleton())
	{
		*result = menu->currentPage;
	}
	return true;
}

bool Cmd_SetLevelUpMenuCurrentPage_Execute(COMMAND_ARGS)
{
	*result = false;
	SInt32 page;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &page) || page > 2)  // Allow going to page = 2 in order to close the menu.
		return true;

	if (auto const menu = LevelUpMenu::GetSingleton())
	{
		if (menu->currentPage != page)
		{
			ThisStdCall<void>(0x785830, menu, page);  // LevelUpMenu::SetCurrentPage
			*result = true;
		}
	}
	return true;
}

class AcceptPerkIfPlayerCanPick
{
public:
	bool Accept(BGSPerk* item) { return item->GetActorCanPickPerk(g_thePlayer); }
};

bool Cmd_ShowPerkMenu_Execute(COMMAND_ARGS)
{
	*result = false;  // result = hasShownPerks
	SInt32 numPerks = -1;
	char menuTitleBuf[0x1000];  // allows changing the title of the Lvl-Up Menu to something more fitting.
	menuTitleBuf[0] = 0;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &numPerks, &menuTitleBuf))
		return true;

	const UInt16 oldCode = *(UInt16*)0x784F26;

	// Credits to Stewie for this piece of code (from bLevelUpAlwaysShowsPerks).
	// Create the perk list even if not on a perk level
	SafeWrite16(0x784F26, 0x25EB);

	if (auto const menu = LevelUpMenu::Create())
	{
		if (!menu->perksList.Empty())
		{
			if (numPerks > -1)  //non-default amount
			{
				AcceptPerkIfPlayerCanPick op;
				auto const numSelectablePerks = menu->perksList.CountIf(op);
				menu->SetNumPerksToAssign(std::min((UInt32)numPerks, numSelectablePerks));
			}
			
			menu->SetCurrentPage(LevelUpMenu::kPerkSelection);
			
			// Hide "Back" button
			// Credit to Stewie for this trick
			menu->tileBtnBack->SetFloat(kTileValue_visible, 0);  

			// Add compat. with GetLevelUpMenuUnspentPoints (avoid weirdness).
			menu->numSkillPointsToAssign = 0;
			
			// Change the title of the menu (sLevelUpTitleText gamesetting determines it by default).
			if (menuTitleBuf[0])
				menu->tileTitle->SetString(kTileValue_string, menuTitleBuf);
			
			*result = true;
		}
		else
		{
			menu->Close();
		}
	}

	// restore code change
	SafeWrite16(0x784F26, oldCode);

	return true;
}


SInt32 g_NumSkillsOverride = -1;

// Skills override must be done at this call addr or before, in order to take advantage of the numSkillPointsToAssign cap that occurs mid-func (0x7856CA).
void __fastcall SetupSkillAndPerkListBoxesHook(LevelUpMenu* menu, void* edx)
{
	menu->numSkillPointsToAssign = g_NumSkillsOverride;
	menu->SetupSkillAndPerkListBoxes();
}

bool g_ShowMenuDespiteNoPoints = true;

// Function structure ripped from Stewie's Tweaks.
void __fastcall LevelUpMenuSetInitialPageHook(LevelUpMenu* menu, void* edx, int pageNumber)
{
	auto const endPageID = Tile::TraitNameToID("_EndPage");
	menu->tile->SetFloat(endPageID, 0);  // prevent going to the Perk page.
	menu->numPerksToAssign = 0;  // compatibility with GetLevelUpMenuUnspentPoints
	
	menu->SetCurrentPage(pageNumber);
	if (!menu->numSkillPointsToAssign && !g_ShowMenuDespiteNoPoints)
	{
		//== Close the menu.
		// In order to pass the first check for the function called at 0x785265 (Menu::SetFadeOut, check at 0xA1D92A), set title tile visibility to non-null.
		// Menu still flashes in/out for a frame.
		menu->tile->SetFloat(kTileValue_visible, 1);
		menu->SetCurrentPage(LevelUpMenu::kCloseMenu);
	}
}

// Based around Stewie's SkipSkillMenuIfNoPointsToAssign.
bool Cmd_ShowSkillMenu_Execute(COMMAND_ARGS)
{
	*result = false;  // result = hasShownSkillMenu
	SInt32 numSkills = -1;
	UInt32 showMenuDespiteNoPoints = true;
	char menuTitleBuf[0x1000];  // allows changing the title of the Lvl-Up Menu to something more fitting.
	menuTitleBuf[0] = 0;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &numSkills, &showMenuDespiteNoPoints, &menuTitleBuf))
		return true;

	// Overwrite vanilla calls.
	auto const setupSkillBoxAddr = GetRelJumpAddr(0x7850D0);
	if (numSkills > -1)
	{
		g_NumSkillsOverride = numSkills;
		WriteRelCall(0x7850D0, (UInt32)SetupSkillAndPerkListBoxesHook);
	}
	auto const setupPageAddr = GetRelJumpAddr(0x7850DD);  // retain compatibility with Tweaks' bSkipSkillMenuIfNoPointsToAssign.
	WriteRelCall(0x7850DD, (UInt32)LevelUpMenuSetInitialPageHook);
	g_ShowMenuDespiteNoPoints = showMenuDespiteNoPoints != 0;

	if (auto const menu = LevelUpMenu::Create())
	{
		*result = true;

		// Change the title of the menu (sLevelUpTitleText game-setting determines it by default).
		if (menuTitleBuf[0])
			menu->tileTitle->SetString(kTileValue_string, menuTitleBuf);
	}

	// Restore calls.
	if (numSkills > -1)
	{
		WriteRelCall(0x7850D0, setupSkillBoxAddr);
		g_NumSkillsOverride = -1;  // just in case, though it shouldn't matter.
	}
	g_ShowMenuDespiteNoPoints = true;
	WriteRelCall(0x7850DD, setupPageAddr);
	
	return true;
}

bool Cmd_GetLevelUpMenuUnspentPoints_Execute(COMMAND_ARGS)
{
	*result = -1;
	UInt32 showSkills;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &showSkills))
		return true;
	if (showSkills)
		*result = GetLevelUpMenuUnspentPoints::g_LvlUpMenuUnspentPoints[0];
	else
		*result = GetLevelUpMenuUnspentPoints::g_LvlUpMenuUnspentPoints[1];
	return true;
}

bool Cmd_SetLevelUpMenuCanExitEarly_Execute(COMMAND_ARGS)
{
	*result = false;  // result = setSuccess
	UInt32 canExitEarly;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &canExitEarly))
		return true;
	if (auto const menu = LevelUpMenu::GetSingleton())
	{
		if (canExitEarly)
		{
			menu->tileBtnContinue->SetFloat(kTileValue_target, 1);
		}
		else
		{
			//todo: set up something to reset to normal behavior.
			// not that important for now, probably not something too useful.
		}
		*result = true;
	}
	return true;
}

bool Cmd_SetLevelUpMenuPoints_Execute(COMMAND_ARGS)
{
	*result = false;  // result = bSuccessfulChange
	UInt32 bChangeAssignedPoints;  // if false, change maxPoints
	UInt32 iNewPoints;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &bChangeAssignedPoints, &iNewPoints))
		return true;

	if (auto const menu = LevelUpMenu::GetSingleton())
	{

		
		// TODO: limit iNewPoints to prevent softlocking!!!!!!!!!!!!!
		// TODO: note that Tweaks' PerksPerLevel prevents the amount of perks from resetting when allotting one (?):
		/*
		 	// remove call resetting selected Perks when one is selected
			NopFunctionCall(0x785B2C, 1);
		*/
		auto const currentPage = menu->currentPage;
		if (bChangeAssignedPoints)
		{
			if (currentPage == LevelUpMenu::kPerkSelection)
			{
				iNewPoints = std::min(menu->numPerksToAssign, iNewPoints);
				menu->numAssignedPerks = iNewPoints;
			}
			else if (currentPage == LevelUpMenu::kSkillSelection)
			{
				iNewPoints = std::min(menu->numSkillPointsToAssign, iNewPoints);
				menu->numAssignedSkillPoints = iNewPoints;
			}
			else
				return true;

			// Change UI Traits.
			auto const g_CurrPoints = *(UInt32*)0x11D9FD8;  // g_levelUpMenu_Trait_CurrPoints
			menu->tile->SetFloat(g_CurrPoints, iNewPoints);  // changes whether or not the player can go to the next page.
			*result = true;
		}
		else
		{
			if (currentPage == LevelUpMenu::kPerkSelection && !menu->perksList.Empty())
			{
				// todo: ??
				menu->numPerksToAssign = iNewPoints;
			}
			else if (currentPage == LevelUpMenu::kSkillSelection)
			{
				// todo: skill point capping normally occurs around 0x7856B2
				menu->numSkillPointsToAssign = iNewPoints;
			}
			else
				return true;

			// Change UI Traits.
			auto const g_MaxPoints = *(UInt32*)0x11D9FD4;  // g_levelUpMenu_Trait_MaxPoints
			menu->tile->SetFloat(g_MaxPoints, iNewPoints);
			*result = true;
		}
		if (*result)
			menu->SetChooseSkillOrPerkNumberText();  // refresh the skill/perk amount text.
	}
	return true;
}


bool Cmd_GetExplosionRefSource_Execute(COMMAND_ARGS)
{
	*result = 0;
	if (auto const explosion = DYNAMIC_CAST(thisObj, TESObjectREFR, Explosion))
	{
		if (explosion->source)
			REFR_RES = explosion->source->refID;
	}
	return true;
}
bool Cmd_SetExplosionRefSource_Execute(COMMAND_ARGS)
{
	*result = false;
	Actor* newSource;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &newSource) || !IS_ACTOR(newSource))
		return true;
	if (auto const explosion = DYNAMIC_CAST(thisObj, TESObjectREFR, Explosion))
	{
		explosion->source = newSource;
		*result = true;
	}
	return true;
}

bool Cmd_GetExplosionRefRadius_Execute(COMMAND_ARGS)
{
	*result = -1;
	if (auto const explosion = DYNAMIC_CAST(thisObj, TESObjectREFR, Explosion))
	{
		*result = explosion->radius;
	}
	return true;
}
bool Cmd_SetExplosionRefRadius_Execute(COMMAND_ARGS)
{
	*result = false;
	float newRadius;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &newRadius))
		return true;
	if (auto const explosion = DYNAMIC_CAST(thisObj, TESObjectREFR, Explosion))
	{
		explosion->radius = newRadius;
		*result = true;
	}
	return true;
}

#if 0
ActorAndItemPairs g_noEquipMap;

bool TryExtractActorItemPair(TESObjectREFR* thisObj, TESForm* item, ActorAndItemPair& actorAndItemOut)
{
	if (IS_REFERENCE(item)) item = ((TESObjectREFR*)item)->baseForm;
	ActorRefID const actorID = IS_ACTOR(thisObj) ? thisObj->refID : NULL;
	ItemRefID const itemID = (item && item->IsItem()) ? item->refID : NULL;
	if (!itemID && !actorID)  // at least one must be there for filtering, otherwise useless/dangerous.
		return false;
	actorAndItemOut = { actorID, itemID };
	return true;
}
#endif

// Differs from NoUnequip extradata mechanic! It's also not savebaked.
bool Cmd_SetNoEquipShowOff_Execute(COMMAND_ARGS)
{
	*result = false;

#if 0 //deprecated
	TESForm* item;
	UInt32 bNoEquip;
	Script* function = nullptr;	// UDF event script which passes "this" = actor and 1 arg: baseItem. todo: ItemInvRef if possible!
	// This function is called whenever "NoEquip" is being checked.
	// If any functions that are called return false (SetFunctionValue), then the item cannot be equipped.

	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &item, &bNoEquip, &function))
		return true;

	// Don't need a valid actor + item if the function is specified.
	if (function && IS_TYPE(function, Script))
	{
		if (bNoEquip)
		{
			g_NoEquipFunctions.insert_or_assign(scriptObj->GetOverridingModIdx(), Function(function));
		}
		else
		{
			g_NoEquipFunctions.erase(scriptObj->GetOverridingModIdx());
		}
	}
	else
	{
		ActorAndItemPair noEquipData;
		if (!TryExtractActorItemPair(thisObj, item, noEquipData))
			return true;
		ScopedLock lock(g_Lock);
		if (bNoEquip)
		{
			*result = g_noEquipMap.insert(noEquipData).second;
		}
		else
		{
			*result = g_noEquipMap.erase(noEquipData);
		}
	}
#endif
	return true;
}

// Can return a bool or a ref.
bool Cmd_GetNoEquipShowOff_Execute(COMMAND_ARGS)
{
	*result = 0;
#if 0
	TESForm* item;
	UInt32 bGetFunction = false;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &item, &bGetFunction))
		return true;

	if (bGetFunction)
	{
		if (auto const &iter = g_NoEquipFunctions.find(scriptObj->GetOverridingModIdx()); iter != g_NoEquipFunctions.end())
		{
			REFR_RES = iter->second.Get()->refID;
		}
	}
	else
	{
		ActorAndItemPair noEquipData;
		if (!TryExtractActorItemPair(thisObj, item, noEquipData))
			return true;
		*result = g_noEquipMap.find(noEquipData) != g_noEquipMap.end();
	}
#endif
	return true;
}

bool Cmd_SetOwnershipTemp_Execute(COMMAND_ARGS)
{
	*result = false; //bSuccess
	TESForm* newOwner = g_thePlayer->baseForm;
	TESForm* baseForm = nullptr;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &newOwner, &baseForm) || !newOwner)
		return true;
	newOwner = newOwner->TryGetREFRParent();
	if (!newOwner->IsActorAlt() && !IS_ID(newOwner, TESFaction))
		return true;
	ExtraDataList* xData = nullptr;
	if (auto const cell = DYNAMIC_CAST(baseForm, TESForm, TESObjectCELL))
	{
		xData = &cell->extraDataList;
	}
	else if (thisObj)
	{
		xData = &thisObj->extraDataList;
	}
	if (xData)
	{
		ThisStdCall(0x419700, xData, newOwner); //ExtraDataList::UpdateExtraOwnership
		*result = true;
	}
	return true;
}

bool Cmd_GetCalculatedAPCost_Execute(COMMAND_ARGS)
{
	*result = 0;

	enum eMode : UInt32
	{
		GetDefaultAttackCost = 0,
		GetSpecialAttack1Cost,
		GetSpecialAttack2Cost
	} mode;

	TESObjectWEAP* weapon = nullptr;  // if omitted, use player's currently equipped weapon (could be fists)
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &mode, &weapon))
		return true;

	if (GetIsGodMode())
		return true; //every action is 0 AP.

	thisObj = g_thePlayer;
	if (!weapon)
	{
		weapon = ((Actor*)thisObj)->GetEquippedWeapon();
		if (!weapon)
			weapon = g_fistsWeapon;
	}

	if (mode == GetDefaultAttackCost)
	{
		//implicitly called on the player, so it accounts for ActionPointCost Perk Entry Point.
		*result = CdeclCall<double>(0x66DCE0, weapon);
	}
	else
	{
		if (VATSMenu::GetSingleton())
		{
			// Costs have been pre-calculated and stored in globals.
			if (mode == GetSpecialAttack1Cost)
			{
				*result = *reinterpret_cast<float*>(0x11DB0B8); // g_vatSpecialAttack1APCost
			}
			else
			{
				*result = *reinterpret_cast<float*>(0x11DB0C0); // g_vatSpecialAttack2APCost
			}
		}
		else
		{
			// TODO: Must calculate the cost ourselves. Won't account for hooks.
			// Replicate code at 0x7EB920
			/*
			if (mode == GetSpecialAttack1Cost)
			{
				
			}
			else
			{
				//todo: make result 0 if player does not have access to the attack.
				float apCost = GetFltGameSetting(0x11D12E4); //  gs_fCrossAPCost
				ApplyPerkModifiers(kPerkEntry_ActionPointCost, thisObj, weapon, &apCost);
				*result = apCost;
			}
			*/
		}
	}

	return true;
}











#ifdef _DEBUG












DEFINE_COMMAND_PLUGIN(ApplyAddictionEffect, "", true, kParams_OneForm_OneOptionalInt);
bool Cmd_ApplyAddictionEffect_Execute(COMMAND_ARGS)
{
	auto const actor = DYNAMIC_CAST(thisObj, TESObjectREFR, Actor);
	AlchemyItem* alchItem;
	UInt32 bShowMsg = true;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &alchItem, &bShowMsg)
		|| !actor || !alchItem || !IS_TYPE(alchItem, AlchemyItem))
	{
		return true;
	}

	//TODO: apply addiction effect, cuz that apparently doesn't happen where I thought it would...
	
	if (auto const umonEffInAlchItm = ThisStdCall<EffectItem*>(0x406200, &alchItem->magicItem.list))
	{
		ThisStdCall(0x824570, &actor->magicTarget, umonEffInAlchItm, &alchItem->magicItem, 0);
	}

	MagicItem* withdrawalMagicItem = nullptr;
	if (alchItem->withdrawalEffect) {
		withdrawalMagicItem = &alchItem->withdrawalEffect->magicItem;
	}
	// MagicTarget::HandleWithdrawal
	ThisStdCall(0x824DF0, &actor->magicTarget, &alchItem->magicItem, withdrawalMagicItem);

	if (const bool showAddictionEffect = actor->IsPlayerRef()
		&& !ThisStdCall_B(0x825610, &actor->magicTarget, &alchItem->magicItem, 1))
	{
		IncPCMiscStat(kMiscStat_TimesAddicted);

		// Apply imagespace modifier
		auto const kBloodISFXd = 0x19482;
		auto const imod = DYNAMIC_CAST(LookupFormByID(kBloodISFXd), TESForm, TESImageSpaceModifier);
		imod->Trigger(1.0, 0);

		if (bShowMsg)
		{
			auto const itemName = alchItem->magicItem.name.CStr();
			auto const sChemsAddicted = GetStrGameSetting(0x11D4CF0);
			auto const msgStr = FormatString(sChemsAddicted, itemName);
			QueueUIMessage(msgStr.c_str(), eEmotion::sad, nullptr, "UIHealthChemsAddicted", 2.0, 0);
		}
	}

	return true;
}


DEFINE_COMMAND_PLUGIN(SetPlantedExplosive, "", true, kParams_OneInt_OneOptionalForm);
bool Cmd_SetPlantedExplosive_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32 bPlanted;
	TESForm* itemToPlant = nullptr;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &bPlanted, &itemToPlant))
		return true;
	
	if (auto const actor = DYNAMIC_CAST(thisObj, TESObjectREFR, Actor))
	{
		const auto hiProc = (HighProcess*)actor->baseProcess;
		if (!hiProc || hiProc->processLevel)
			return true;

		if (auto const menu = ContainerMenu::GetSingleton())
		{
			//todo: call the check function before adding item.
			menu->list078.Insert(itemToPlant);
		}
		hiProc->plantedExplosive = bPlanted != 0;
		*result = 1;
	}
	return true;
}


//todo: GetLevelUpMenuMaxPoints


DEFINE_COMMAND_PLUGIN(GetHealthEffectsSum, "", true, NULL);
bool Cmd_GetHealthEffectsSum_Execute(COMMAND_ARGS)
{
	*result = -1;
	if (auto const actor = DYNAMIC_CAST(thisObj, TESObjectREFR, Actor))
	{
		*result = actor->GetHealthEffectsSum();
	}
	return true;
}






DEFINE_COMMAND_PLUGIN(GetLevelUpMenuCanExitEarly, "", false, NULL);
bool Cmd_GetLevelUpMenuCanExitEarly_Execute(COMMAND_ARGS)
{
	*result = -1;
	if (auto const menu = LevelUpMenu::GetSingleton())
	{
		// todo: figure out how to detect if the _target tilevalue was overriden.
	}
	return true;
}



// Kinda pointless in the face of JIP's IsMobile
DEFINE_CMD_ALT_COND_PLUGIN(CanBeMoved, , , true, NULL);
bool Cmd_CanBeMoved_Eval(COMMAND_ARGS_EVAL)
{
	*result = 0;
	if (!thisObj) return true;
	*result = ThisStdCall<bool>(0x572C80, thisObj);  //just does some formType check + allows any dynamic object
	return true;
}
bool Cmd_CanBeMoved_Execute(COMMAND_ARGS)
{
	return Cmd_CanBeMoved_Eval(thisObj, 0, 0, result);
}


DEFINE_COMMAND_PLUGIN(GetActorPreferredWeapon, "", true, kParams_OneOptionalInt);
bool Cmd_GetActorPreferredWeapon_Execute(COMMAND_ARGS)
{
	//todo: current configuration gives garbage forms, need to fix that. Perhaps not calling it right?
	*result = 0;
	UInt32 combatWeaponType = 6;
	if (!thisObj || NOT_ACTOR(thisObj) || !ExtractArgsEx(EXTRACT_ARGS_EX, &combatWeaponType))
		return true;
	const auto weapForm = ThisStdCall<TESObjectWEAP*>(0x891C80, thisObj, combatWeaponType); //Actor::GetPreferredWeapon
	if (weapForm)
		REFR_RES = weapForm->refID;  
	return true;
}

DEFINE_COMMAND_PLUGIN(TryDropWeapon, "", true, NULL);
bool Cmd_TryDropWeapon_Execute(COMMAND_ARGS)
{
	*result = 0;
	if (!thisObj || NOT_ACTOR(thisObj))
		return true;
	Actor* actor = (Actor*)thisObj;
	if (!actor->baseProcess) return true;
	//actor->GetEquippedWeapon()
	// Retrieve info about actor's weapon, for comparison later.
	ContChangesEntry* weaponInfo = actor->baseProcess->GetWeaponInfo();
	if (!weaponInfo || !weaponInfo->type) return true;  //actor has no weapon to unequip
	const SInt32 prevCount = weaponInfo->countDelta;
#if _DEBUG
	Console_Print("TryDropWeapon >> Count delta: %i", prevCount);
#endif

	ThisStdCall<void>(0x89F580, actor);  //Actor::TryDropWeapon. Triggers OnDrop blocktype.

	// Check if a weapon has been dropped.
	weaponInfo = actor->baseProcess->GetWeaponInfo();
	if (!weaponInfo || !weaponInfo->type || weaponInfo->countDelta != prevCount) *result = 1;  //weapon has been removed.
	return true;
}


DEFINE_CMD_COND_PLUGIN(IsWeaponTrowable, "", true, kParams_OneOptionalObjectID);
bool Cmd_IsWeaponTrowable_Eval(COMMAND_ARGS_EVAL)
{
	//Console_Print("thisObj: [%0.8X]", thisObj->baseForm->GetId());
	*result = 0;
	TESForm* form;
	if (arg1) form = (TESForm*)arg1;
	else if (thisObj) form = thisObj->baseForm;
	else return true;
	auto const weapon = DYNAMIC_CAST(form, TESForm, TESObjectWEAP);
	if (!weapon) return true;
	UINT8 weapType = weapon->eWeaponType;
	//*result = weapType <= 2;
	return true;
}
bool Cmd_IsWeaponTrowable_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESObjectWEAP* weapon = NULL;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &weapon)) return true;
	return Cmd_IsWeaponTrowable_Eval(thisObj, weapon, 0, result);
}

DEFINE_CMD_COND_PLUGIN(GetPCCanSleepWait, "", false, NULL);
bool Cmd_GetPCCanSleepWait_Eval(COMMAND_ARGS_EVAL)
{
	//todo: verify if it works with script overrides and stewie features.
	*result = g_thePlayer->canSleepWait;
	return true;
}
bool Cmd_GetPCCanSleepWait_Execute(COMMAND_ARGS)
{
	*result = g_thePlayer->canSleepWait;
	return true;
}


DEFINE_CMD_COND_PLUGIN(GetPCCanSleepInOwnedBeds, "", false, NULL);
bool Cmd_GetPCCanSleepInOwnedBeds_Eval(COMMAND_ARGS_EVAL)
{
	//*result = GetCanSleepInOwnedBeds();
	return true;
}
bool Cmd_GetPCCanSleepInOwnedBeds_Execute(COMMAND_ARGS)
{
	//*result = GetCanSleepInOwnedBeds();
	return true;
}

DEFINE_COMMAND_PLUGIN(SetPCCanSleepInOwnedBeds, "", false, kParams_OneInt);
bool Cmd_SetPCCanSleepInOwnedBeds_Execute(COMMAND_ARGS)
{
	UInt32 bOn;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &bOn)) return true;
	//SetCanSleepInOwnedBeds(bOn);
	return true;
}

/*Notes on GetChallengeProgress w/ other funcs:*/
//If the challenge is beaten...
//...and is NOT set to "Recurring", will return the max Threshold value.
//......If the value was changed using SetChallengeProgress / ModChallengeProgress, its "progress" will change, but it still won't budge naturally.
//...and is set to "Recurring", will return 0. Afterwards, will increment as normal.
//......When going over the threshold using Mod/SetChallengeProgress, leftover progress is kept to increase the progress. This amount can even go over the threshold.
//......However, those functions DO NOT manually trigger challenge completion.
//......Afterwards, once triggered normally, the challenge will be completed once more, doing "Progress -= Threshold". After this, you could still have Progress > Threshold.


DEFINE_COMMAND_PLUGIN(SetChallengeProgress, "Changes the progress made on a challenge to a specific value.", false, kParams_OneForm_OneInt)
DEFINE_COMMAND_PLUGIN(ModChallengeProgress, "Modifies the progress made on a challenge.", false, kParams_OneForm_OneInt)

//Going into negative seems to work fine, it just delays the challenge progress.
//It also looks weird since it shows "0/x" progress when it returns to 0.

//FLAW TO FIX: Find a way to forcefully activate the Challenge completion.



bool Cmd_SetChallengeProgress_Execute(COMMAND_ARGS)
{
	TESChallenge* challenge;
	UInt32 value;
	if (ExtractArgs(EXTRACT_ARGS, &challenge, &value) && IS_TYPE(challenge, TESChallenge))
	{
		//if (value > challenge->threshold )
		challenge->progress = value;
		*result = 1;
	}
	else *result = 0;
	return true;
}

bool Cmd_ModChallengeProgress_Execute(COMMAND_ARGS)
{
	TESChallenge* challenge;
	UInt32 value;
	if (ExtractArgs(EXTRACT_ARGS, &challenge, &value) && IS_TYPE(challenge, TESChallenge))
	{
		//UInt32 const test_amount = challenge->amount + value;
		challenge->progress += value;
		*result = 1;
	}
	else *result = 0;
	return true;
}

DEFINE_COMMAND_PLUGIN(CompleteChallenge, "Completes a challenge.", false, kParams_OneForm)
bool Cmd_CompleteChallenge_Execute(COMMAND_ARGS)
{
	TESChallenge* challenge;
	UInt32 value;
	if (ExtractArgs(EXTRACT_ARGS, &challenge, &value) && IS_TYPE(challenge, TESChallenge))
	{
		challenge->challengeflags |= 2;
		*result = 1; //success
	}
	else *result = 0;
	return true;
}



DEFINE_COMMAND_PLUGIN(GetProjectileRefFlag, "", false, NULL);
bool Cmd_GetProjectileRefFlag_Execute(COMMAND_ARGS)
{
	GrenadeProjectile* projectile = (GrenadeProjectile*)thisObj;
	//if (!(projectile->projFlags & 0x200) && (projectile->sourceRef != g_thePlayer) && ((((BGSProjectile*)thisObj->baseForm)->projFlags & 0x426) == 0x26))
	//if (!(projectile->projFlags & 0x200) && ((((BGSProjectile*)thisObj->baseForm)->projFlags & 0x426) == 0x26))
	//if (!(projectile->projFlags & 0x200))
	*result = ((Projectile*)thisObj)->projFlags;
	
	return true;
}

DEFINE_COMMAND_PLUGIN(SetProjectileRefFlag, "", true, kParams_OneInt);
bool Cmd_SetProjectileRefFlag_Execute(COMMAND_ARGS)
{
	UInt32 flag;
	if (ExtractArgs(EXTRACT_ARGS, &flag))
		((Projectile*)thisObj)->projFlags = flag;

	//if ((((BGSProjectile*)thisObj->baseForm)->projFlags & 0x426) == 0x26);
	//	Console_Print("Flag was set");
	return true;
}



DEFINE_COMMAND_PLUGIN(SetPCCanPickpocketInCombat, "", false, kParams_OneInt);
bool Cmd_SetPCCanPickpocketInCombat_Execute(COMMAND_ARGS)
{
	UInt32 bOn;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &bOn)) return true;
	g_canPlayerPickpocketInCombat = bOn;
	return true;
}

// Ripped code from JIPLN's "SetNoUnequip"
DEFINE_COMMAND_PLUGIN(SetNoEquip, "Returns 1 if the inventory ref was sucessfully set to NoEquip (or the flag was properly cleared). Returns 2 if it was already set.", true, kParams_OneInt);
bool Cmd_SetNoEquip_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32 noEquip;
	if (ExtractArgs(EXTRACT_ARGS, &noEquip))
	{
		InventoryRef* invRef = InventoryRefGetForID(thisObj->refID);
		if (!invRef) return true;
		ExtraDataList* xData = invRef ? invRef->data.xData : NULL;
		if (xData)
		{
			if (!noEquip)
			{
				RemoveExtraType(xData, kExtraData_CannotWear);
				*result = 1;
			}
			else if (!xData->HasType(kExtraData_CannotWear) && !xData->HasType(kExtraData_Worn))  //I just replaced the "IsEquipped" extra data check from JIP's SetNoUnequip.
			{
				AddExtraData(xData, ExtraCannotWear::Create());
				*result = 1;
			}
			else if (xData->HasType(kExtraData_CannotWear))
				*result = 2;
		}
	} 
	return true;
}

/*
DEFINE_COMMAND_PLUGIN(GetFastTravelFlags, , 0, 0, NULL);
bool Cmd_GetFastTravelFlags_Execute(COMMAND_ARGS)
{
	*result = (g_thePlayer->byte66D & 1) != 0;
	return true;
}
*/

/*
DEFINE_COMMAND_PLUGIN(SetParentRef, , 1, 1, kParams_OneOptionalForm);
bool Cmd_SetParentRef_Execute(COMMAND_ARGS)
{
	ExtraDataList* xData = thisObj ? thisObj->xData : NULL;
	if (xData)
	{
		if (!noEquip)
		{
			RemoveExtraType(xData, kExtraData_CannotWear);
			*result = 1;
		}
		else if (!xData->HasType(kExtraData_CannotWear) && !xData->HasType(kExtraData_Worn))  //I just replaced the "IsEquipped" extra data check from JIP's SetNoUnequip.
		{
			AddExtraData(xData, ExtraCannotWear::Create());
			*result = 1;
		}
		else if (xData->HasType(kExtraData_CannotWear))
			*result = 2;
	}
	
	return true;
}
*/

//DEFINE_CMD_ALT_COND_PLUGIN(GetEquippedWeaponType,, "Returns the type of weapon equipped by the calling actor, 0 if the calling ref isn't an actor.", 0, 1, kParams_OneOptionalObjectID);
bool GetEquippedWeaponInfo(TESObjectREFR* thisObj, float range, UInt32 flags)
{
	return true;
}




#endif
