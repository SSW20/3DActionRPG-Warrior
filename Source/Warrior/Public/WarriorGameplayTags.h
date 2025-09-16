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
	
		/* Event Tags */
		WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_EquipWeapon)
		WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_UnEquipWeapon)
		WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_HitPause)


		/* Ability Tags */
		WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_UnEquip_Axe)
		WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Axe)
		WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_LightAttack_Axe)
		WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_HeavyAttack_Axe)
		WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_HitPause)
	
		/* Status Tags */
		WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_JumpToFinisher)
	
		/* Attack Types Tags*/
		WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Light);
		WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Heavy);

	
	/* Weapon Tags */
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(WeaponTag_Axe)
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Weapon);

	/* Shared Tags */
		/* Event Tags */
		WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_MeleeHit)
		WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_HitReact)

		/* Damage Tags */
		WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_HitReact)
		WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_Death)

		WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_Death)


		WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_SetByCaller_BaseDamage);

	/* Enemy tags */
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Melee)
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Range)
		
}