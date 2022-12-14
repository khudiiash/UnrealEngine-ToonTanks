// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "DrawDebugHelpers.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::HandleDestruction()
{
	// TODO: Visual & Sound effects
	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathParticles, GetActorLocation());
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector LookAtLocation = LookAtTarget - TurretMesh->GetComponentLocation();
	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(TurretMesh->GetComponentRotation(), 
		LookAtLocation.Rotation(), 
		GetWorld()->DeltaTimeSeconds, 25.f)
	);
}

void ABasePawn::RotateBase(FVector LookAtTarget)
{
	FVector LookAtLocation = LookAtTarget - BaseMesh->GetComponentLocation();
	FRotator LookAtRotation = LookAtLocation.Rotation();
	LookAtRotation.Pitch = 0.f;
	LookAtRotation.Roll = 0.f;
	BaseMesh->SetWorldRotation(
		FMath::RInterpTo(BaseMesh->GetComponentRotation(), 
		LookAtRotation, 
		GetWorld()->DeltaTimeSeconds, 25.f)
	);
}

void ABasePawn::Fire()
{
	FVector Location = ProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
	Projectile->SetOwner(this);
}
