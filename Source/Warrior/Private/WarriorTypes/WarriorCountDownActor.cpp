// Fill out your copyright notice in the Description page of Project Settings.


#include "WarriorTypes/WarriorCountDownActor.h"

#include "WarriorDebugHelper.h"
#include "Algo/Count.h"
#include "Kismet/GameplayStatics.h"
#include "WarriorTypes/WarriorEnumTypes.h"

void FWarriorCountDownAction::CancelAction()
{
	bNeedCancel = true;
}

void FWarriorCountDownAction::UpdateOperation(FLatentResponse& Response)
{
	if (UGameplayStatics::IsGamePaused(CallbackTarget.Get()))
	{
		// 일시 정지 상태라면 아무 작업도 하지 않고 리턴합니다.
		// ElapsedTimeSinceStart나 ElapsedInterval을 업데이트하지 않습니다.
		return;
	}
	
	if (bNeedCancel)
	{
		CountDownOutput = EWarriorCountDownActionOutput::Cancelled;

		Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
		return;
	}
	if (ElapsedTimeSinceStart >= TotalCountDownTime)
	{
		CountDownOutput = EWarriorCountDownActionOutput::Completed;

		Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
		return;
	}

	if (ElapsedInterval < UpdateInterval)
	{
		ElapsedInterval += Response.ElapsedTime();
	}
	else
	{
			// 실제 업데이트 반복
			ElapsedTimeSinceStart += UpdateInterval > 0.f ? UpdateInterval : Response.ElapsedTime();
		
			OutRemainingTime = TotalCountDownTime - ElapsedTimeSinceStart;

			CountDownOutput = EWarriorCountDownActionOutput::Updated;

			Response.TriggerLink(ExecutionFunction, OutputLink, CallbackTarget);

			ElapsedInterval = 0.f;
	}
	
}
