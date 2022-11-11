// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "EnemyTank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AEnemyTank : public ABasePawn
{
	GENERATED_BODY()

public:
	AEnemyTank();
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();
protected:
	virtual void BeginPlay() override;
private:
	class ATank* Tank;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	float FireRange = 1500.f; // 1000.f = 10 meters fire range
	UPROPERTY(EditAnywhere, Category = "Combat")
	float FollowRange = 3000.f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed = 300.f;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float FireRate = 1.5f;

	bool IsTankInRange(float Range);
	void FollowPlayer();
	void CheckFireCondition();

	FTimerHandle FireRateTimerHandle;
};
