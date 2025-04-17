// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LS_MovingActor.generated.h"

UCLASS()
class LASTSTAND_API ALS_MovingActor : public AActor
{
	GENERATED_BODY()
	
public:
    ALS_MovingActor();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
    void MoveActor(float DeltaTime);
    void StartMoving(FVector NewStartLocation);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float MoveRange = 1000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float MoveSpeed = 200.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
    UStaticMesh* MeshAsset;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
    UStaticMeshComponent* MeshComponent;

    UPROPERTY(EditAnywhere, Category = "Knockback")
    class UParticleSystemComponent* KnockbackEffect;

    UFUNCTION()
    void OnKnockbackOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);

    void ActivateKnockbackEffect();

private:
    FVector InitialStartLocation;
    FVector EndLocation;
    FVector CurrentTarget;
};