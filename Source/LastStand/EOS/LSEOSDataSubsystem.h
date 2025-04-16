// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineLeaderboardInterface.h"
#include "LSEOSDataSubsystem.generated.h"

USTRUCT(BlueprintType)
struct FLeaderboardEntry
{
    GENERATED_USTRUCT_BODY()
    
    UPROPERTY(BlueprintReadWrite)
    FString NickName;

    UPROPERTY(BlueprintReadWrite)
    int32 Rank;

    UPROPERTY(BlueprintReadWrite)
    FString Value;

    FLeaderboardEntry()
    {
        
    }
    
    FLeaderboardEntry(const FString& InNickName, int32 InRank, const FString& InValue)
        : NickName(InNickName), Rank(InRank), Value(InValue)
    {
    }
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEOSLeaderboardUpdated, const TArray<FLeaderboardEntry>&, LeaderboardEntries);

UCLASS()
class LASTSTAND_API ULSEOSDataSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "LSEOSDataSubsystem")
    void UpdateStat(FString StatName, int32 StatValue);
    UFUNCTION(BlueprintCallable, Category = "LSEOSDataSubsystem")
    void QueryLeaderboardGlobal(FName LeaderboardName = "WINLEADERBOARD");
    void QueryLeaderboardFriends(FString StatName, FName LeaderboardName = "WINLEADERBOARD" );
    
private:
    void HandleQueryLeaderboarComplete(bool bWasSuccessful, FOnlineLeaderboardReadRef LeaderboardReadRef);	
    TArray<FLeaderboardEntry> ParseLeaderboardToArray(const FOnlineLeaderboardReadRef& LeaderboardReadRef);

public:
    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "LSEOSDataSubsystem")
    FOnEOSLeaderboardUpdated OnEOSLeaderboardUpdated;
    
private:
    FDelegateHandle QueryLeaderboardDelegateHandle;
    FString CurrentStatName;
    
};
