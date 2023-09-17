// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CubeBase.h"
#include "CubeCleaner.generated.h"

/**
 * 
 */
UCLASS()
class ROLLINGBALL_API ACubeCleaner : public ACubeBase
{
	GENERATED_BODY()
public:
	void OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

protected:
	virtual void BeginPlay() override;
	
};
