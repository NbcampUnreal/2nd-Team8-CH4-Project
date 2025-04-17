// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LS_ObjectSpawnBox.generated.h"

class UBoxComponent;

UCLASS()
class LASTSTAND_API ALS_ObjectSpawnBox : public AActor
{
	GENERATED_BODY()
	
public:
    
    ALS_ObjectSpawnBox();

    FVector GetBoxLocation() const;
 
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class UBoxComponent* SpawnBox;

    UPROPERTY(VisibleAnywhere)
    class USceneComponent* Root;
};