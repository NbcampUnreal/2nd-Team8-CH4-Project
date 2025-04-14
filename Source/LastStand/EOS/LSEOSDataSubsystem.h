// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineLeaderboardInterface.h"
#include "LSEOSDataSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class LASTSTAND_API ULSEOSDataSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    void UpdateStat(FString StatName, int32 StatValue);
    void QueryLeaderboardGlobal(FName LeaderboardName = "WINLEADERBOARD");
    void QueryLeaderboardFriends(FString StatName, FName LeaderboardName = "WINLEADERBOARD" );

private:
    FDelegateHandle QueryLeaderboardDelegateHandle; 
    void HandleQueryLeaderboarComplete(bool bWasSuccessful, FOnlineLeaderboardReadRef LeaderboardReadRef);	
};
