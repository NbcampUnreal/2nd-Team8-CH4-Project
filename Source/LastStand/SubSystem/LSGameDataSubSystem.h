// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LSGameDataSubSystem.generated.h"

/**
 * 
 */
UCLASS()
class LASTSTAND_API ULSGameDataSubSystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    ULSGameDataSubSystem();

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    
private:
    void LoadData();
    
public:
    UPROPERTY(BlueprintReadOnly)
    TObjectPtr<UDataTable> CharacterTable;
};
