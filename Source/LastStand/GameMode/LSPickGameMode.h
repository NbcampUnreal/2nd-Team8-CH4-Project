// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "LSPickGameMode.generated.h"

class ALSCharacter;
/**
 * 
 */
UCLASS()
class LASTSTAND_API ALSPickGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ALSPickGameMode();
    
    UFUNCTION(BlueprintCallable)
	void GameStart();

    void CheckAllLoaded();
    void CheckAllPlayerPick();

    
};
