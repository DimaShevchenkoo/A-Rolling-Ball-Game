// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RollingBallGameMode.generated.h"

UCLASS(minimalapi)
class ARollingBallGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ARollingBallGameMode();
	void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	int32 MinBaseCubeNumber{10};
	UPROPERTY(EditAnywhere)
	int32 MaxBaseCubeNumber{15};
	

};



