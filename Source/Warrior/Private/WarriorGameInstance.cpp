// Fill out your copyright notice in the Description page of Project Settings.


#include "WarriorGameInstance.h"

TSoftObjectPtr<UWorld> UWarriorGameInstance::GetMapByTag(FGameplayTag Tag) const
{
	if (Tag.IsValid())
	{
		for (const FWarriorMapInfo& MapInfo : MapInfos)
		{
			if (MapInfo.LevelTag.MatchesTagExact(Tag))
			{
				return MapInfo.Level;
			}
		}
	}
	return nullptr;
}
