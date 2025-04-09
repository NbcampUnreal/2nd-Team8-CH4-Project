// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "LSSessionSubsystem.generated.h"

class FOnlineSessionSearch;
class FOnlineSessionSearchResult;

DECLARE_MULTICAST_DELEGATE_OneParam(FEOSSessionSearchComplete, TSharedRef<FOnlineSessionSearch>);

UCLASS()
class LASTSTAND_API ULSSessionSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    void JoinSession(const FName SessionName);
    void FindMatchmakingSession();
    void FindCustomSession(const FString SessionName);
    int32 GetNumOfPlayersInSession();
    int32 GetIndexOfPlayerInSession();
    int32 GetIndexOfPlayerInSession(const APlayerController* Controller);

private:
    void CreateSession(const FName KeyName = "KeyName", const FString KeyValue = "KeyValue");
    void HandleCreateSessionCompleted(FName SessionName, bool bWasSuccessful);
    void HandleFindMatchmakingSessionsComplete(bool bWasSuccessful, TSharedRef<FOnlineSessionSearch> Search);
    void HandleFindCustomSessionsComplete(bool bWasSuccessful, TSharedRef<FOnlineSessionSearch> Search);
    void HandleJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
 
public:
    FEOSSessionSearchComplete OnEOSSessionSearchComplete;
    
private:
    FDelegateHandle CreateSessionDelegateHandle;
    FDelegateHandle FindMatchmakingSessionsDelegateHandle;
    FDelegateHandle FindCustomSessionsDelegateHandle;
    FDelegateHandle JoinSessionDelegateHandle;
    FDelegateHandle EndSessionDelegateHandle;
    FDelegateHandle DestroySessionDelegateHandle; 
    FOnlineSessionSearchResult* SessionToJoin;
};
