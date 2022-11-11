// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	


public:
	ATank();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;	
	void HandleDestruction();
	bool isAlive() const;
	
	// update health bar
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHealthBar(float HealthPercentage);

	APlayerController* GetPlayerController() const { return TankPlayerController; };
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed = 600.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnSpeed = 100.f;

	void Move(float Value);
	void Turn(float Value);

	APlayerController* TankPlayerController;
	class AToonTanksGameMode* GameModeRef;
};
