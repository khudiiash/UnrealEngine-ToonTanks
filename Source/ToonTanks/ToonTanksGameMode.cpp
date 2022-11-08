// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "ToonTanksPlayerController.h"
#include "Tower.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
    bool IsTank = DeadActor == Tank;
    ATower* Tower = Cast<ATower>(DeadActor);
    if (IsTank) HandleTankDeath();
    if (Tower) HandleTowerDeath(Tower); 
}

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
    HandleGameStart();
}

void AToonTanksGameMode::HandleTankDeath()
{
    Tank->HandleDestruction();
    if (!ToonTanksPlayerController) return;
    
    ToonTanksPlayerController->SetPlayerEnabledState(false);
}

void AToonTanksGameMode::HandleTowerDeath(ATower* Tower)
{
    Tower->HandleDestruction();
}

void AToonTanksGameMode::HandleGameStart()
{
    if (!ToonTanksPlayerController) return;
    ToonTanksPlayerController->SetPlayerEnabledState(false);
    FTimerHandle PlayerEnableTimerHandle;
    FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);
    GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, StartDelay, false);
}