// Fill out your copyright notice in the Description page of Project Settings.


#include "WarriorGameInstance.h"

#include "MoviePlayer.h"
#include "Blueprint/UserWidget.h"


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

void UWarriorGameInstance::Init()
{
	Super::Init();

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this,&ThisClass::OnPreLoadMap);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this,&ThisClass::OnDestinationWorldLoaded);
}
void UWarriorGameInstance::OnPreLoadMap(const FString& MapName)
{
	FLoadingScreenAttributes LoadingScreenAttributes;
	LoadingScreenAttributes.bAutoCompleteWhenLoadingCompletes = true;
	LoadingScreenAttributes.MinimumLoadingScreenDisplayTime = 2.f;
	// 2. 커스텀 위젯 클래스가 유효한지 확인하고 연결합니다.
	if (CustomLoadingScreenWidgetClass)
	{
		// 3. FLoadingScreenAttributes에 UMG 위젯을 연결하는 람다 함수 생성
		// 이 함수는 로딩 스크린이 시작될 때 위젯을 생성하고 반환합니다.
		
		UUserWidget* Widget = CreateWidget<UUserWidget>(this, CustomLoadingScreenWidgetClass);
		if (Widget)
		{
			LoadingScreenAttributes.WidgetLoadingScreen = Widget->TakeWidget(); // UUserWidget을 Slate 위젯으로 변환
		}
	}
	// else { /* 유효하지 않은 경우, 여기에 기본 로딩 화면 로직 (예: 테스트 위젯 사용)을 남겨둘 수 있습니다. */ }

	// 4. 무비 플레이어에 로딩 스크린 설정
	GetMoviePlayer()->SetupLoadingScreen(LoadingScreenAttributes);
}

void UWarriorGameInstance::OnDestinationWorldLoaded(UWorld* LoadedWorld)
{
	GetMoviePlayer()->StopMovie();
}
