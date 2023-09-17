// Fill out your copyright notice in the Description page of Project Settings.


#include "RollingBallControllerBase.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "RollingBallCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Math/UnitConversion.h"

void ARollingBallControllerBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
}

void ARollingBallControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();
	// Get the local player subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// Clear out existing mapping, and add our mapping
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Get the EnhancedInputComponent
	if (UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Bind the actions
		PEI->BindAction(MoveAction.Get(), ETriggerEvent::Triggered, this, &ThisClass::Move);
		PEI->BindAction(LookAction.Get(), ETriggerEvent::Triggered, this, &ThisClass::Look);
	}
}

void ARollingBallControllerBase::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ARollingBallControllerBase::Move(const FInputActionValue& Value)
{
	if (TObjectPtr<ARollingBallCharacter> RollingBallCharacter = Cast<ARollingBallCharacter>(GetCharacter()))
	{
		
		RotationSpeed = RollingBallCharacter->GetCharacterMovement()->MaxWalkSpeed;
		 
		FVector2D MoveValue = Value.Get<FVector2D>();
		const FRotator MovementRotation(0, GetControlRotation().Yaw, 0);
		
		// Forward/Backward direction
		if (MoveValue.X != 0.f)
		{
			// Get forward vector
			FVector Direction = MovementRotation.RotateVector(FVector::ForwardVector);
			
			MoveValue.X *= -1.f;
			float Rotation = RotationSpeed * MoveValue.X;
			Direction *= Rotation;
			
			RollingBallCharacter->AddMovementInput(Direction, MoveValue.Y, true);
			RollingBallCharacter->GetCapsuleComponent()->AddAngularImpulseInDegrees(Direction, NAME_None, true);
		}

		// Right/Left direction 
		if (MoveValue.Y != 0.f)
		{
			// Get right vector
			FVector Direction = MovementRotation.RotateVector(FVector::RightVector);
			
			float Rotation = RotationSpeed * MoveValue.Y;
			Direction *= Rotation;
			
			RollingBallCharacter->AddMovementInput(Direction, MoveValue.X);
			RollingBallCharacter->GetCapsuleComponent()->AddAngularImpulseInDegrees(Direction, NAME_None, true);
		}
	}
}

void ARollingBallControllerBase::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (ACharacter* LCharacter = GetCharacter())
	{
		// add yaw and pitch input to controller
		LCharacter->AddControllerYawInput(LookAxisVector.X);
		LCharacter->AddControllerPitchInput(LookAxisVector.Y);
	}
}
