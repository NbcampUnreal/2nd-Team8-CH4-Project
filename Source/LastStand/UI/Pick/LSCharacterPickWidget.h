// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LSCharacterPickWidget.generated.h"

/**
 * 
 */
UCLASS()
class LASTSTAND_API ULSCharacterPickWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetPlayerCount(int PlayerCount);
    
    UFUNCTION(BlueprintImplementableEvent)
    void PlayStartButtonAnimation();
};
