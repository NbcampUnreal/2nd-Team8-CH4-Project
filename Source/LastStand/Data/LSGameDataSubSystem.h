// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LSGameDataSubsystem.generated.h"

class ULSMapDataAsset;
class ULSCharacterDataAsset;
/**
 * 
 */
UCLASS()
class LASTSTAND_API ULSGameDataSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    
private:
    void LoadData();
    
public:
    UPROPERTY(BlueprintReadOnly)
    TObjectPtr<ULSCharacterDataAsset> Character;
    
    UPROPERTY(BlueprintReadOnly)
    TObjectPtr<ULSMapDataAsset> Map;
};
