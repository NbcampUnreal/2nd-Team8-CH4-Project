// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LSMapDataAsset.generated.h"

UENUM(BlueprintType)
enum class EMapMode : uint8
{
    Normal,
    
};

USTRUCT(BlueprintType)
struct FMapData
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FString Name;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSoftObjectPtr<UWorld> Level;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TObjectPtr<UTexture2D> Image;   //미리보기

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    EMapMode MapMode;               //맵 모드, 기본적으론 Normal임
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 MaxTime = 300;            //제한 시간, 0이하면 무한

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 PlayerLifeCount = 3;      //플레이어 목숨, 0이하면 무한

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 ItemSpawnDelay = 60;      //아이템 스폰 딜레이, 0이하면 스폰하지 않음    
};

/**
 * 
 */
UCLASS()
class LASTSTAND_API ULSMapDataAsset : public UDataAsset
{
    GENERATED_BODY()

    
public:
    UPROPERTY(EditAnywhere)
    TArray<FMapData> MapDatas;

public:
    UFUNCTION(BlueprintCallable)
    FMapData GetMapData(FString MapName);

    UFUNCTION(BlueprintCallable)
    FMapData GetRandomMapData();
};
