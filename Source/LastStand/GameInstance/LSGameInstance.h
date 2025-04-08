// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LSGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class LASTSTAND_API ULSGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Audio")
    float MasterVolume = 1.0f;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Audio")
    class USoundMix* MasterSoundMix;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Audio")
    class USoundClass* MasterSoundClass;

    void ApplyVolumeSettings();
};
