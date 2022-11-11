// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "EnemyTank.h"
#include "ToonTanksPlayerController.h"
#include "Tower.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
    bool IsTank = DeadActor == Tank;
    ATower* Tower = Cast<ATower>(DeadActor);
    AEnemyTank* EnemyTank = Cast<AEnemyTank>(DeadActor);
    if (IsTank) HandleTankDeath();
    if (Tower || EnemyTank) {
        if (Tower) Tower->HandleDestruction();
        if (EnemyTank) EnemyTank->HandleDestruction();
        Enemies--;
        if (Enemies <= 0) GameOver(true);
    }
}

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();
    Enemies = GetEnemiesCount();
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

void AToonTanksGameMode::HandleGameStart()
{
    StartGame();
    if (!ToonTanksPlayerController) return;
    ToonTanksPlayerController->SetPlayerEnabledState(false);
    FTimerHandle PlayerEnableTimerHandle;
    FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);
    GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, StartDelay, false);
}

int32 AToonTanksGameMode::GetEnemiesCount() const
{
    TArray<AActor*> EnemyTanks;
    TArray<AActor*> Towers;
    UGameplayStatics::GetAllActorsOfClass(this, AEnemyTank::StaticClass(), EnemyTanks);
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
    return EnemyTanks.Num() + Towers.Num();
}

void AToonTanksGameMode::SetGameOver()
{
    bGameOver = true;
}