// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "LSMatchmakingGameMode.generated.h"

/**
 * 
 */
UCLASS()
class LASTSTAND_API ALSMatchmakingGameMode : public AGameMode
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;
    virtual void PostLogin(APlayerController* NewPlayerController) override;
    
private:
    FDelegateHandle JoinPlayerDelegateHandle;
    int32 MaxNumberOfPlayers = 6;
    int32 NumberOfPlayers = 0;
};
