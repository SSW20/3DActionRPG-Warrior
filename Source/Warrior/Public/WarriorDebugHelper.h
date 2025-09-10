#pragma once

namespace Debug
{
	static void Print(const FString& Message, FColor Color = FColor::Red, int32 InKey = -1)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(InKey, 7.f, Color, Message);
		}
	}
}