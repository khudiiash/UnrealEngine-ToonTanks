// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
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
}

void AToonTanksGameMode::HandleTankDeath()
{
    Tank->HandleDestruction();
    if (!Tank->GetPlayerController()) return;
    
    Tank->DisableInput(Tank->GetPlayerController());
    Tank->GetPlayerController()->bShowMouseCursor = false;
}

void AToonTanksGameMode::HandleTowerDeath(ATower* Tower)
{
    Tower->HandleDestruction();
}