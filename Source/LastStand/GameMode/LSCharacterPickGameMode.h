// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "LSCharacterPickGameMode.generated.h"

class ALSCharacter;
/**
 * 
 */
UCLASS()
class LASTSTAND_API ALSCharacterPickGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ALSCharacterPickGameMode();
    
    UFUNCTION(BlueprintCallable)
	void GameStart();

    void CheckAllLoaded();

    
};
