#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

ATower::ATower()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ATower::BeginPlay()
{
    Super::BeginPlay();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);

}

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (IsTankInTange()) RotateTurret(Tank->GetActorLocation());
}

bool ATower::IsTankInTange()
{
    if (!Tank) return false;
    float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
    return Distance <= FireRange;
}

void ATower::CheckFireCondition()
{
    if (!Tank || !Tank->isAlive()) return;
    if (IsTankInTange()) Fire();
}

void ATower::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}