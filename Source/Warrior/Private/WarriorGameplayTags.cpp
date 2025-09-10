// Fill out your copyright notice in the Description page of Project Settings.

#include "WarriorGameplayTags.h"
#include "NativeGameplayTags.h"

namespace WarriorGameplayTags
{
	/* Input Tags */
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_EquipWeapon, "InputTag.EquipWeapon")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_UnEquipWeapon, "InputTag.UnEquipWeapon")

	/* Player Tags */
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_EquipWeapon, "Player.Event.EquipWeapon")
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_UnEquipWeapon, "Player.Event.UnEquipWeapon")
	
	/* Weapon Tags */
	UE_DEFINE_GAMEPLAY_TAG(WeaponTag_Axe, "WeaponTag.Axe")
}