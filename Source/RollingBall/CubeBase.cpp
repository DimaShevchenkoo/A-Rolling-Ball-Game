// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeBase.h"
#include "CubeCleaner.h"
#include "NavigationSystem.h"
#include "RollingBallCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ACubeBase::ACubeBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube Mesh"));
	CubeMesh->SetupAttachment(GetRootComponent());
	
	CubeCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Cube Collision"));
	CubeCollision->SetupAttachment(CubeMesh);
	
}


void ACubeBase::BeginPlay()
{
	Super::BeginPlay();
	CubeMesh->OnComponentHit.AddDynamic(this, &ACubeBase::OnComponentHit);
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ACubeBase::MoveTo, 1.f, true);
}

void ACubeBase::MoveTo()
{
	FVector StartLocation = GetActorLocation();
	
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (NavSystem)
	{
		FVector RandomOffset = FMath::VRand() * NavRadius;
		RandomOffset.Z = StartLocation.Z;
		FVector TargetLocation = StartLocation + RandomOffset;
		FVector ImpulseDirection = (TargetLocation - StartLocation).GetSafeNormal();
		
		CubeMesh->AddImpulse(ImpulseDirection * FMath::RandRange(20000.f, 30000.f));
	}
}

void ACubeBase::OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                               FVector NormalImpulse, const FHitResult& Hit)
{
	TObjectPtr<ACubeBase> CubeBase = Cast<ACubeBase>(OtherActor);
	
	if (CubeBase && !CubeBase.IsA(ACubeCleaner::StaticClass()))
	{
		if (GetCurrentMaterial() == GetDefaultPlayerMaterial()) 
		{
			SetMaterialOnMesh(CubeBase->GetMesh(), GetDefaultPlayerMaterial(), 0);
			SpawnParticle();
			AddTag(CubeBase);
		}
		else if (CubeBase->GetCurrentMaterial() == GetDefaultPlayerMaterial())
		{
			SetMaterialOnMesh(CubeMesh, GetDefaultPlayerMaterial(), 0);
			SpawnParticle();
			AddTag(this);
		}
	}
	else if (TObjectPtr<ARollingBallCharacter> RollingBallCharacter = Cast<ARollingBallCharacter>(OtherActor))
	{
		SetMaterialOnMesh(CubeMesh, GetDefaultPlayerMaterial(), 0);
		SpawnParticle();
		AddTag(this);
	}
	else if (TObjectPtr<ACubeCleaner> CubeCleaner = Cast<ACubeCleaner>(OtherActor))
	{
		if (GetCurrentMaterial() == GetDefaultPlayerMaterial() && CubeCleaner->GetCurrentMaterial() == GetDefaultCleanerCubeMaterial()) 
		{
			SetMaterialOnMesh(CubeMesh, GetDefaultBaseCubeMaterial(), 0);
			SpawnParticle();
			RemoveTag(this);
		}
		else if (CubeCleaner->GetCurrentMaterial() == GetDefaultPlayerMaterial())
		{
			SetMaterialOnMesh(CubeMesh, GetDefaultPlayerMaterial(), 0);
			SpawnParticle();
			AddTag(this);
		}
	}
}

void ACubeBase::SetMaterialOnMesh(UStaticMeshComponent* MeshForApplyingMaterial, UMaterialInterface* MaterialToApply, int32 ElementIndex)
{
	MeshForApplyingMaterial->SetMaterial(ElementIndex, MaterialToApply);
}

void ACubeBase::SpawnParticle()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OnHitParticle, GetActorTransform());
}

void ACubeBase::RemoveTag(AActor* Actor)
{
	if (Actor->ActorHasTag("Marked"))
	{
		Actor->Tags.Remove("Marked");
	}
}

void ACubeBase::AddTag(AActor* Actor)
{
	if (Actor->ActorHasTag("Marked"))
	{
		__fallthrough;
	}
	else
	{
		Actor->Tags.Add("Marked");
	}
}

