// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "LSPickGameMode.generated.h"

struct FMapData;
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
    
    void CheckAllLoaded();
    void CheckAllPlayerPick();
	void GameStart(FMapData MapData);

    UFUNCTION(BlueprintImplementableEvent)
    void SetGameSettings(const TArray<FName>& PickCharacters, FMapData MapData);

private:
    UPROPERTY(VisibleDefaultsOnly)
    int32 TempPlayerSize = 6;
};
