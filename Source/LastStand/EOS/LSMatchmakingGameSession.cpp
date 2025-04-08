// Fill out your copyright notice in the Description page of Project Settings.


#include "LSMatchmakingGameSession.h"

#include "LSSessionSubsystem.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystemTypes.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlineStatsInterface.h"


ALSMatchmakingGameSession::ALSMatchmakingGameSession()
{
    PrimaryActorTick.bCanEverTick = true;
    SessionName = "MatchmakingSession";
}

void ALSMatchmakingGameSession::BeginPlay()
{
    Super::BeginPlay();
    CreateSession("Matchmaking", "MatchmakingSession");
}
