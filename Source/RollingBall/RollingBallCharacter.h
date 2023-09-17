// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "RollingBallCharacter.generated.h"


UCLASS(config=Game)
class ARollingBallCharacter : public ACharacter
{
	GENERATED_BODY()
	
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom{nullptr};

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCamera{nullptr};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> StaticMeshComponent{nullptr};

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UParticleSystem> OnHitParticle{nullptr};
	
	
	FString MaterialPlayerPath = TEXT("/Script/Engine.Material'/Game/Materials/RollingBallMaterial.RollingBallMaterial'");
	
	UPROPERTY()
	TObjectPtr<class UMaterialInterface> DefaultPlayerMaterial = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), UMaterialInterface::StaticClass(), *MaterialPlayerPath));
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USoundBase> Sound{};
	
protected:
	virtual void BeginPlay();
	
public:
	ARollingBallCharacter();
	
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	TObjectPtr<UMaterialInterface> GetDefaultPlayerMaterial() {return DefaultPlayerMaterial;}

	void RemoveTag(AActor* Actor);
	void AddTag(AActor* Actor);
	void SpawnParticle();
	void SetMaterialOnMesh(UStaticMeshComponent* MeshForApplyingMaterial, UMaterialInterface* MaterialToApply, int32 ElementIndex );
};

