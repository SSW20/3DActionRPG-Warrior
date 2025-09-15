// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace WarriorGameplayTags
{
	/* Input Tags */
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move)
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look)
	
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_EquipWeapon)
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UnEquipWeapon)

	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_LightAttack_Axe)
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_HeavyAttack_Axe)

	/* Player Tags */
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_EquipWeapon)
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_UnEquipWeapon)
	
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_UnEquip_Axe)
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Axe)

	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_LightAttack_Axe)
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_HeavyAttack_Axe)
	
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_JumpToFinisher)
	
	/* Weapon Tags */
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(WeaponTag_Axe)
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Weapon);

	/* Event Tags */
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_MeleeHit)
}