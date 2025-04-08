// Fill out your copyright notice in the Description page of Project Settings.


#include "LSMatchmakingGameMode.h"

#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "Interfaces/OnlineSessionInterface.h"


void ALSMatchmakingGameMode::BeginPlay()
{
    Super::BeginPlay();

    
}

void ALSMatchmakingGameMode::PostLogin(APlayerController* NewPlayerController)
{
    Super::PostLogin(NewPlayerController);

    UE_LOG(LogTemp, Log, TEXT("Player joined: %s"), *NewPlayerController->GetName());
    NumberOfPlayers++;
    if (NumberOfPlayers >= MaxNumberOfPlayers)
    {
        const FString Map = "/Game/LastStand/Maps/CharacterPick";
        GetWorld()->ServerTravel(Map,false);
    }
}