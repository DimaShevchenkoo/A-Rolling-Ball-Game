// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeCleaner.h"

#include "RollingBallCharacter.h"

void ACubeCleaner::BeginPlay()
{
	Super::BeginPlay();
	
	CubeMesh->OnComponentHit.AddDynamic(this, &ACubeCleaner::OnComponentHit);
}



void ACubeCleaner::OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                  FVector NormalImpulse, const FHitResult& Hit)
{
	if (TObjectPtr<ACubeCleaner> CubeCleaner = Cast<ACubeCleaner>(OtherActor))
	{
		if (GetCurrentMaterial() == GetDefaultPlayerMaterial() && CubeCleaner->GetCurrentMaterial() == GetDefaultCleanerCubeMaterial() )
		{
			SetMaterialOnMesh(CubeMesh, GetDefaultCleanerCubeMaterial(), 0);
			SpawnParticle();
			RemoveTag(this);
		}
		else if (CubeCleaner->GetCurrentMaterial() == GetDefaultPlayerMaterial() && GetCurrentMaterial() == GetDefaultCleanerCubeMaterial())
		{
			SetMaterialOnMesh(CubeCleaner->GetMesh(), GetDefaultCleanerCubeMaterial(), 0);
			SpawnParticle();
			RemoveTag(CubeCleaner);
		}
	}
	else if (TObjectPtr<ARollingBallCharacter> RollingBallCharacter = Cast<ARollingBallCharacter>(OtherActor))
	{
		SetMaterialOnMesh(CubeMesh, GetDefaultPlayerMaterial(), 0);
		SpawnParticle();
		AddTag(this);
	}
	else if (TObjectPtr<ACubeBase> CubeBase = Cast<ACubeBase>(OtherActor))
	{
		if (GetCurrentMaterial() == GetDefaultPlayerMaterial() && CubeBase->GetCurrentMaterial() == GetDefaultBaseCubeMaterial())
		{
			SetMaterialOnMesh(CubeBase->GetMesh(), GetDefaultPlayerMaterial(), 0);
			SpawnParticle();
			AddTag(CubeBase);
		}
		else if (CubeBase->GetCurrentMaterial() == GetDefaultPlayerMaterial() && GetCurrentMaterial() == GetDefaultCleanerCubeMaterial())
		{
			SetMaterialOnMesh(CubeBase->GetMesh(), GetDefaultBaseCubeMaterial(), 0);
			SpawnParticle();
			RemoveTag(CubeBase);
		}
	}
}




