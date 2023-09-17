// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CubeBase.generated.h"



UCLASS()
class ROLLINGBALL_API ACubeBase : public APawn
{
	GENERATED_BODY()

public:
	ACubeBase();
	
	UFUNCTION()
	virtual void OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	TObjectPtr<UMaterialInterface> GetDefaultPlayerMaterial() {return DefaultPlayerMaterial;}
	TObjectPtr<UMaterialInterface> GetDefaultBaseCubeMaterial() {return DefaultBaseCubeMaterial;}
	TObjectPtr<UMaterialInterface> GetDefaultCleanerCubeMaterial() {return DefaultCleanerCubeMaterial;}
	TObjectPtr<UMaterialInterface> GetCurrentMaterial() {return CubeMesh->GetMaterial(0);}
	
	TObjectPtr<UStaticMeshComponent> GetMesh() {return CubeMesh;}
	
	

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UStaticMeshComponent> CubeMesh{nullptr};
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UBoxComponent> CubeCollision{nullptr};

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UParticleSystem> OnHitParticle{nullptr};
	
	
	void SetMaterialOnMesh(UStaticMeshComponent* MeshForApplyingMaterial, UMaterialInterface* MaterialToApply, int32 ElementIndex);
	void RemoveTag(AActor* Actor);
	void AddTag(AActor* Actor);
	void SpawnParticle();
	void MoveTo();
	
	virtual void BeginPlay() override;
	
private:
	FString MaterialBaseCubePath = TEXT("/Script/Engine.Material'/Game/Materials/CubeBaseMaterial.CubeBaseMaterial'");
	FString MaterialPlayerPath = TEXT("/Script/Engine.Material'/Game/Materials/RollingBallMaterial.RollingBallMaterial'");
	FString MaterialCleanerCubePath = TEXT("/Script/Engine.Material'/Game/Materials/CubeCleaner.CubeCleaner'");
	
	UPROPERTY()
	TObjectPtr<UMaterialInterface> DefaultPlayerMaterial = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), UMaterialInterface::StaticClass(), *MaterialPlayerPath));

	UPROPERTY()
	TObjectPtr<UMaterialInterface> DefaultCleanerCubeMaterial = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), UMaterialInterface::StaticClass(), *MaterialCleanerCubePath));
	
	UPROPERTY()
	TObjectPtr<UMaterialInterface> DefaultBaseCubeMaterial = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), UMaterialInterface::StaticClass(), *MaterialBaseCubePath));
	
	UPROPERTY(EditAnywhere, Category = "Navigation", meta=(AllowPrivateAccess = true))
	float NavRadius = 5000.0f;
	
	UPROPERTY(EditAnywhere, Category = "Movement", meta=(AllowPrivateAccess = true))
	float ImpulseStrength {};

	FTimerHandle TimerHandle;
};
