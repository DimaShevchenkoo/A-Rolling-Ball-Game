// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RollingBallControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class ROLLINGBALL_API ARollingBallControllerBase : public APlayerController
{
	GENERATED_BODY()
protected:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> DefaultMappingContext{nullptr};

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> JumpAction{nullptr};

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveAction{nullptr};

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> LookAction{nullptr};
	
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;

	void Move(const struct FInputActionValue& Value);
	void Look(const struct FInputActionValue& Value);
	
	float RotationSpeed{};
};
