// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"
#include "GameFramework/Pawn.h"

void AToonTanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
    if (bPlayerEnabled)
    {
        GetPawn()->EnableInput(this);
        GetPawn()->SetActorTickEnabled(true);
    }
    else
    {
        GetPawn()->DisableInput(this);
        GetPawn()->SetActorTickEnabled(false);
    }

    bShowMouseCursor = bPlayerEnabled;
}