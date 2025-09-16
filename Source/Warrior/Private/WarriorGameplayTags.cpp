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

	UE_DEFINE_GAMEPLAY_TAG(InputTag_LightAttack_Axe, "InputTag.LightAttack.Axe")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_HeavyAttack_Axe, "InputTag.HeavyAttack.Axe")
	

	/* Player Tags */
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_EquipWeapon, "Player.Event.EquipWeapon")
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_UnEquipWeapon, "Player.Event.UnEquipWeapon")
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_HitPause, "Player.Event.HitPause")
	
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_Axe, "Player.Ability.Equip.Axe")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_UnEquip_Axe,"Player.Ability.UnEquip.Axe")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_LightAttack_Axe, "Player.Ability.LightAttack.Axe")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_HeavyAttack_Axe,"Player.Ability.HeavyAttack.Axe")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_HitPause, "Player.Ability.HitPause")


	UE_DEFINE_GAMEPLAY_TAG(Player_Status_JumpToFinisher,"Player.Status.JumpToFinisher")

	/* Attack Types Tags*/
	UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_AttackType_Light,"Player.SetByCaller.AttackType.Light");
	UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_AttackType_Heavy, "Player.SetByCaller.AttackType.Heavy");
	
	/* Weapon Tags */
	UE_DEFINE_GAMEPLAY_TAG(WeaponTag_Axe, "WeaponTag.Axe")
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Weapon, "Enemy.Weapon")

	/* Shared Tags */
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_MeleeHit, "Shared.Event.MeleeHit")
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_BaseDamage,"Shared.SetByCaller.BaseDamage");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact, "Shared.Event.HitReact")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_HitReact, "Shared.Ability.HitReact")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Death,"Shared.Ability.Death")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Death,"Shared.Status.Death")
	/* Enemy tags */
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee, "Enemy.Ability.Melee")
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Range, "Enemy.Ability.Range")
}