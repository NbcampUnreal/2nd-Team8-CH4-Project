// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LSBaseGameSession.h"
#include "GameFramework/GameSession.h"
#include "LSMatchmakingGameSession.generated.h"

UCLASS()
class LASTSTAND_API ALSMatchmakingGameSession : public ALSBaseGameSession
{
    GENERATED_BODY()
    ALSMatchmakingGameSession();

protected:
    virtual void BeginPlay() override;
};
