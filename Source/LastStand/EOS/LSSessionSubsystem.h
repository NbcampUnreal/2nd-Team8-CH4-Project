// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "LSSessionSubsystem.generated.h"

class FOnlineSessionSearch;
class FOnlineSessionSearchResult;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEOSSessionDestroyComplte);

UCLASS()
class LASTSTAND_API ULSSessionSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "LSSessionSubsystem")
    void JoinSession(const FName SessionName);
    UFUNCTION(BlueprintCallable, Category = "LSSessionSubsystem")
    void FindMatchmakingSession();
    UFUNCTION(BlueprintCallable, Category = "LSSessionSubsystem")
    void FindCustomSession(const FString SessionName);
    UFUNCTION(BlueprintCallable, Category = "LSSessionSubsystem")
    void DestroySession();
    
    int32 GetNumOfPlayersInSession();
    int32 GetIndexOfPlayerInSession();
    int32 GetIndexOfPlayerInSession(const APlayerController* Controller);

private:
    void CreateSession(const FName KeyName = "KeyName", const FString KeyValue = "KeyValue");
    void HandleCreateSessionCompleted(FName SessionName, bool bWasSuccessful);
    void HandleFindMatchmakingSessionsComplete(bool bWasSuccessful, TSharedRef<FOnlineSessionSearch> Search);
    void HandleFindCustomSessionsComplete(bool bWasSuccessful, TSharedRef<FOnlineSessionSearch> Search);
    void HandleJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
    void HandleDestroySessionCompleted(FName SessionName, bool bWasSuccessful);
    
public:
    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "LSSessionSubsystem")
    FEOSSessionDestroyComplte OnEOSSessionDestroyComplete;
    
private:
    FName CurrentSessionName;
    FDelegateHandle CreateSessionDelegateHandle;
    FDelegateHandle FindMatchmakingSessionsDelegateHandle;
    FDelegateHandle FindCustomSessionsDelegateHandle;
    FDelegateHandle JoinSessionDelegateHandle;
    FDelegateHandle EndSessionDelegateHandle;
    FDelegateHandle DestroySessionDelegateHandle;
    FOnlineSessionSearchResult* SessionToJoin;
};
