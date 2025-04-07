// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LSCharacterDataAsset.generated.h"

USTRUCT()
struct FCharacterData
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
    FName KeyName;
    
    UPROPERTY(EditAnywhere)
    FString DisplayName;

    UPROPERTY(EditAnywhere)
    TObjectPtr<UTexture2D> Image;
};


UCLASS()
class LASTSTAND_API ULSCharacterDataAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
    TArray<FCharacterData> CharacterDatas;

public:
    FCharacterData GetCharacterData(FName Key);
};
