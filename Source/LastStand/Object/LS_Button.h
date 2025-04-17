// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LS_Button.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class USoundBase;
class ALS_ObjectSpawnBox;
class ALS_MovingActor;

UCLASS()
class LASTSTAND_API ALS_Button : public AActor
{
	GENERATED_BODY()
	
public:
    ALS_Button();

protected:
    virtual void BeginPlay() override;

public:
    UFUNCTION()
    void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);


    void ActivateButton();
    void SpawnSnowballStep();

    UPROPERTY()
    bool bActivated = false;

    UFUNCTION()
    void StartMovingActor();


private:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* Cube;

    UPROPERTY(VisibleAnywhere)
    UBoxComponent* Box;

    UPROPERTY(EditAnywhere, Category = "Sound")
    USoundBase* ActivateSound;

    UPROPERTY(EditAnywhere, Category = "Meshes")
    UStaticMesh* UnpressedMesh;

    UPROPERTY(EditAnywhere, Category = "Meshes")
    UStaticMesh* PressedMesh;

    UPROPERTY(EditAnywhere, Category = "Snowball")
    TSubclassOf<AActor> SnowballClass;  // 기존 Snowball 클래스

    UPROPERTY(EditAnywhere, Category = "MoveActor")
    TSubclassOf<ALS_MovingActor> MoveActorClass; // MoveActor 클래스

    UPROPERTY(EditAnywhere, Category = "Snowball")
    float TotalSnowballsToSpawn = 3.0f;

    UPROPERTY(EditAnywhere, Category = "Snowball")
    float SpawnInterval = 1.0f;

    UPROPERTY()
    int32 SnowballSpawnCount;

    FTimerHandle SpawnTimerHandle;

    // Spawn Box Reference
    UPROPERTY(EditAnywhere, Category = "Snowball")
    class ALS_ObjectSpawnBox* SpawnBoxRef;
};