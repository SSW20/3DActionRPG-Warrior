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

	UE_DEFINE_GAMEPLAY_TAG(InputTag_Rolling, "InputTag.Rolling")

	UE_DEFINE_GAMEPLAY_TAG(InputTag_Held,"InputTag.Held")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Held_Block,"InputTag.Held.Block")

	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggle,"InputTag.Toggle")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggle_TargetLock,"InputTag.Toggle.TargetLock")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggle_Rage,"InputTag.Toggle.Rage")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_SwitchTarget, "InputTag.SwitchTarget")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_SpecialWeaponAbility_Light,"InputTag.SpecialWeaponAbility.Light");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_SpecialWeaponAbility_Heavy,"InputTag.SpecialWeaponAbility.Heavy");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_PickUp_Stone,"InputTag.PickUp.Stone");
	

	/* Player Tags */
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_EquipWeapon, "Player.Event.EquipWeapon")
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_UnEquipWeapon, "Player.Event.UnEquipWeapon")
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_HitPause, "Player.Event.HitPause")
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_SuccessfulBlock, "Player.Event.SuccessfulBlock")
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_RageActive, "Player.Event.RageActive")
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_SwitchTarget_Left,"Player.Event.SwitchTarget.Left");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_SwitchTarget_Right,"Player.Event.SwitchTarget.Right");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_PickUp_Stone,"Player.Event.PickUp.Stone");

	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_Axe, "Player.Ability.Equip.Axe")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_UnEquip_Axe,"Player.Ability.UnEquip.Axe")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_LightAttack_Axe, "Player.Ability.LightAttack.Axe")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_HeavyAttack_Axe,"Player.Ability.HeavyAttack.Axe")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_HitPause, "Player.Ability.HitPause")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Rolling, "Player.Ability.Rolling")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Block,"Player.Ability.Block")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_TargetLock,"Player.Ability.TargetLock")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Rage,"Player.Ability.Rage")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_SpecialWeaponAbility_Light,"Player.Ability.SpecialWeaponAbility.Light");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_SpecialWeaponAbility_Heavy,"Player.Ability.SpecialWeaponAbility.Heavy");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_PickUp,"Player.Ability.PickUp");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_PickUp_Stone,"Player.Ability.PickUp.Stone");


	
	UE_DEFINE_GAMEPLAY_TAG(Player_Cooldown_SpecialWeaponAbility_Light,"Player.Cooldown.SpecialWeaponAbility.Light");
	UE_DEFINE_GAMEPLAY_TAG(Player_Cooldown_SpecialWeaponAbility_Heavy,"Player.Cooldown.SpecialWeaponAbility.Heavy")

	UE_DEFINE_GAMEPLAY_TAG(Player_Status_JumpToFinisher,"Player.Status.JumpToFinisher")
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Rolling, "Player.Status.Rolling")
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Block,"Player.Status.Block")
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_TargetLock,"Player.Status.TargetLock")
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Rage,"Player.Status.Rage")
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Rage_Active, "Player.Status.Rage.Active")
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Rage_Activating, "Player.Status.Rage.Activating")
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Rage_Full,"Player.Status.Rage.Full")
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Rage_None,"Player.Status.Rage.None")



	/* Attack Types Tags*/
	UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_AttackType_Light,"Player.SetByCaller.AttackType.Light");
	UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_AttackType_Heavy, "Player.SetByCaller.AttackType.Heavy");
	
	/* Weapon Tags */
	UE_DEFINE_GAMEPLAY_TAG(WeaponTag_Axe, "WeaponTag.Axe")
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Weapon, "Enemy.Weapon")

	/* Shared Tags */
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_MeleeHit, "Shared.Event.MeleeHit")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact, "Shared.Event.HitReact")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_SpawnProjectile, "Shared.Event.SpawnProjectile")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_Summon, "Shared.Event.Summon")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_AOE, "Shared.Event.AOE")

	
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_BaseDamage,"Shared.SetByCaller.BaseDamage");
	
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_HitReact, "Shared.Ability.HitReact")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Death,"Shared.Ability.Death")
	
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Death,"Shared.Status.Death")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Front,"Shared.Status.HitReact.Front");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Left,"Shared.Status.HitReact.Left");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Right,"Shared.Status.HitReact.Right");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Back,"Shared.Status.HitReact.Back");
	
	/* Enemy tags */
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee, "Enemy.Ability.Melee")
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Range, "Enemy.Ability.Range")
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Summon, "Enemy.Ability.Summon")
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_SpawnStone, "Enemy.Ability.SpawnStone")
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_Patrol,"Enemy.Status.Patrol")
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_UnderAttack,"Enemy.Status.UnderAttack")
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_UnBlockable,"Enemy.Status.UnBlockable")

	/* Map tag */
	UE_DEFINE_GAMEPLAY_TAG(GameMode_Map_Survival,"GameMode.Map.Survival")
	UE_DEFINE_GAMEPLAY_TAG(GameMode_Map_MainMenu,"GameMode.Map.MainMenu")

	UE_DEFINE_GAMEPLAY_TAG(GameData_SaveGame_Slot_1,"GameData.SaveGame.Slot.1");

}