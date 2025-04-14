// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "LSGameDataSubsystemSettings.generated.h"

class ULSMapDataAsset;
class ULSCharacterDataAsset;
/**
 * 
 */
UCLASS(Config = Game, DefaultConfig)
class LASTSTAND_API ULSGameDataSubsystemSettings : public UDeveloperSettings
{
    GENERATED_BODY()

public:
    ULSGameDataSubsystemSettings(const FObjectInitializer& ObjectInitializer);
    
public:
    UPROPERTY(Config, EditAnywhere)
    TSoftObjectPtr<ULSCharacterDataAsset> CharacterDataAsset;
    
    UPROPERTY(Config, EditAnywhere)
    TSoftObjectPtr<ULSMapDataAsset> MapDataAsset;
};
