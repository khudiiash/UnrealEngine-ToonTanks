#include "EnemyTank.h"
#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

AEnemyTank::AEnemyTank()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AEnemyTank::BeginPlay()
{
    Super::BeginPlay();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &AEnemyTank::CheckFireCondition, FireRate, true);

}

void AEnemyTank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (IsTankInRange(FollowRange)) FollowPlayer();
}

bool AEnemyTank::IsTankInRange(float Range)
{
    if (!Tank) return false;
    float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
    return Distance <= Range;
}


void AEnemyTank::CheckFireCondition()
{
    if (!Tank) return;
    if (IsTankInRange(FireRange)) Fire();
}

void AEnemyTank::FollowPlayer()
{
    if (!Tank) return;
    RotateBase(Tank->GetActorLocation());
    if (IsTankInRange(FireRange)) return;
    
    FVector PlayerLocation = Tank->GetActorLocation();
    FVector Direction = PlayerLocation - GetActorLocation();
    Direction.Normalize();
    FVector MoveLocation = GetActorLocation() + (Direction * MoveSpeed * GetWorld()->DeltaTimeSeconds);
    SetActorLocation(MoveLocation);
    
}

void AEnemyTank::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}