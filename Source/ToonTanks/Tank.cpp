// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "ToonTanksGameMode.h"
#include "Camera/CameraComponent.h"

ATank::ATank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

void ATank::BeginPlay()
{
    Super::BeginPlay();
    TankPlayerController = Cast<APlayerController>(GetController());
    GameModeRef = Cast<AToonTanksGameMode>(GetWorld()->GetAuthGameMode());
}

void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    if (TankPlayerController)
    {
        FHitResult HitResult;
        TankPlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
        // if actor is not self, rotate turret
        if (HitResult.GetActor() && HitResult.GetActor() != this)
        {
            FVector HitLocation = HitResult.ImpactPoint;
            RotateTurret(HitLocation);
        }
    }
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::Move(float Value)
{
    FVector Movement = FVector(Value * Speed * GetWorld()->DeltaTimeSeconds, 0, 0);
    AddActorLocalOffset(Movement, true);
}

void ATank::Turn(float Value)
{
    FRotator Rotation = FRotator(0, Value * TurnSpeed * GetWorld()->DeltaTimeSeconds, 0);
    AddActorLocalRotation(Rotation, true);
}

void ATank::HandleDestruction()
{
    Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
}

bool ATank::isAlive() const
{
    if (!GameModeRef)
    {
        UE_LOG(LogTemp, Error, TEXT("GameModeRef is null"));
        return false;
    }
    return GameModeRef->bGameOver == false;
}