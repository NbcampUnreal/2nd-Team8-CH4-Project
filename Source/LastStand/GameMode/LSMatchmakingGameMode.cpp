// Fill out your copyright notice in the Description page of Project Settings.


#include "LSMatchmakingGameMode.h"

#include "EOS/LSMatchmakingGameSession.h"

ALSMatchmakingGameMode::ALSMatchmakingGameMode()
{
    GameSessionClass = ALSMatchmakingGameSession::StaticClass();
}
