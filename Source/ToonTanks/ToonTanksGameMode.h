// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintCallable)
	void SetGameOver();
	
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);
public:
	void ActorDied(AActor* DeadActor);

	UPROPERTY(EditAnywhere, Category = "Game Loop")
	bool bGameOver = false;
	
private:
	class ATank* Tank;
	class AToonTanksPlayerController* ToonTanksPlayerController;
	
	void HandleTankDeath();
	void HandleGameStart();
	int32 GetEnemiesCount() const;

	float StartDelay = 3.f;
	int32 Enemies = 0;
};
