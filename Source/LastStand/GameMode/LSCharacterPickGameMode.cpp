// Fill out your copyright notice in the Description page of Project Settings.


#include "LSCharacterPickGameMode.h"

#include "CharacterPick/LSCharacterPickPlayerController.h"
#include "Kismet/GameplayStatics.h"

ALSCharacterPickGameMode::ALSCharacterPickGameMode()
{
    PlayerControllerClass = ALSCharacterPickPlayerController::StaticClass();
}

void ALSCharacterPickGameMode::GameStart()
{
}

void ALSCharacterPickGameMode::CheckAllLoaded()
{
    bool bAllLoad = true;
    for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
        if (ALSCharacterPickPlayerController* PlayerController = Cast<ALSCharacterPickPlayerController>(Iter->Get()))
            bAllLoad &= PlayerController->IsLoaded();

    if (bAllLoad)
        for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
            if (ALSCharacterPickPlayerController* PlayerController = Cast<ALSCharacterPickPlayerController>(Iter->Get()))
                PlayerController->ClientStartPick();
}
