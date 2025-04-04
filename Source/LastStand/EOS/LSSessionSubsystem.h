// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "LSSessionSubsystem.generated.h"

class FOnlineSessionSearch;
class FOnlineSessionSearchResult;

UCLASS()
class LASTSTAND_API ULSSessionSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category= "LSSessionSubsystem")
    void CreateSession(FName KeyName = "KeyName", FString KeyValue= "KeyValue");
    UFUNCTION(BlueprintCallable, Category= "LSSessionSubsystem")
    void FindSessions(FName SearchKey = "KeyName", FString SearchValue = "KeyValue");
    UFUNCTION(BlueprintCallable, Category= "LSSessionSubsystem")
    void JoinSession(const FName SessionName);

    UFUNCTION(BlueprintCallable, Category= "LSSessionSubsystem")
    void FindMatchmakingSession();
    UFUNCTION(BlueprintCallable, Category= "LSSessionSubsystem")
    void FindCustomSession();

private:
    void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
    void OnFindSessionsComplete(bool bWasSuccessful, TSharedRef<FOnlineSessionSearch> Search);
    void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
public:
    FDelegateHandle CreateSessionDelegateHandle;
    FDelegateHandle FindSessionsDelegateHandle;
    FDelegateHandle JoinSessionDelegateHandle;
    
private:
    FOnlineSessionSearchResult* SessionToJoin;
};
