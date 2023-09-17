// Copyright Epic Games, Inc. All Rights Reserved.

#include "RollingBallGameMode.h"

#include "CubeBase.h"
#include "RollingBallCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARollingBallGameMode::ARollingBallGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ARollingBallGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	
		
}
