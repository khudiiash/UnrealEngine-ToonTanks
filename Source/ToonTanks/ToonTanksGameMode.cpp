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
    TargetTowers = GetTargetTowersCount();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
    HandleGameStart();
}

void AToonTanksGameMode::HandleTankDeath()
{
    Tank->HandleDestruction();
    GameOver(false);
    if (!ToonTanksPlayerController) return;
    
    ToonTanksPlayerController->SetPlayerEnabledState(false);
}

void AToonTanksGameMode::HandleTowerDeath(ATower* Tower)
{
    Tower->HandleDestruction();
    if (--TargetTowers <= 0) GameOver(true);
}

void AToonTanksGameMode::HandleGameStart()
{
    StartGame();
    if (!ToonTanksPlayerController) return;
    ToonTanksPlayerController->SetPlayerEnabledState(false);
    FTimerHandle PlayerEnableTimerHandle;
    FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);
    GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, StartDelay, false);
}

int32 AToonTanksGameMode::GetTargetTowersCount() const
{
    TArray<AActor*> Towers;
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
    return Towers.Num();
}