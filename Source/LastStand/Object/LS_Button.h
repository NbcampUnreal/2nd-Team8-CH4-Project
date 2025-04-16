// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LS_Button.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class USoundBase;
class ALS_ObjectSpawnBox;

UCLASS()
class LASTSTAND_API ALS_Button : public AActor
{
	GENERATED_BODY()
	
public:
    ALS_Button();

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);

    void ActivateButton();
    void SpawnSnowballStep();

    FTimerHandle SpawnTimerHandle;
    int32 SnowballSpawnCount = 0;

public:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* Cube;

    UPROPERTY(VisibleAnywhere)
    UBoxComponent* Box;

    UPROPERTY(EditAnywhere, Category = "Visual")
    UStaticMesh* UnpressedMesh;

    UPROPERTY(EditAnywhere, Category = "Visual")
    UStaticMesh* PressedMesh;

    UPROPERTY(EditAnywhere, Category = "Sound")
    USoundBase* ActivateSound;

    UPROPERTY(EditAnywhere, Category = "Spawn")
    TSubclassOf<AActor> SnowballClass;

    UPROPERTY(EditAnywhere, Category = "Spawn")
    ALS_ObjectSpawnBox* SpawnBoxRef;

    UPROPERTY(EditAnywhere, Category = "Spawn")
    int32 TotalSnowballsToSpawn = 30;

    UPROPERTY(EditAnywhere, Category = "Spawn")
    float SpawnInterval = 0.5f;

    bool bActivated = false;
};
