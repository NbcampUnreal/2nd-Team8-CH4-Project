// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LSLoginSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class LASTSTAND_API ULSLoginSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "LSEOSSubsystem")
    void LoginWithEOS(const FString& UserId, const FString& Token, const FString& LoginType);
    UFUNCTION(BlueprintCallable, Category = "LSEOSSubsystem")
    void GetPlayerUse(const FString& UserId, const FString& Token, const FString& LoginType);
    
private:
    void LoginWithEOSComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& ErrorString);

public:
    FDelegateHandle LoginDelegateHandle;
};
