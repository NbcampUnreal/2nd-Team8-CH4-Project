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

    UFUNCTION(BlueprintCallable, Category = "LSEOSLoginSubsystem")
    void LoginWithEOS(const FString& UserId, const FString& Token, const FString& LoginType);

    UFUNCTION(BlueprintCallable, Category = "LSEOSLoginSubsystem")
    void GetPlayerUse(const FString& UserId, const FString& Token, const FString& LoginType);

    void LoginWithEOSComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& ErrorString);
};
