// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LS_MovingActor.generated.h"

class UStaticMeshComponent;
class UParticleSystemComponent;
class USceneComponent;

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

    void StartMoving(FVector NewStartLocation);

    UFUNCTION(Server,Reliable)
    void  ServerActivateKnockbackEffect();  // 버튼 눌렸을 때 호출

private:
    void MoveActor(float DeltaTime);

    UFUNCTION(BlueprintCallable)
    void OnKnockbackOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);

public:

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    USceneComponent* SceneComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UStaticMeshComponent* MeshComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UParticleSystemComponent* KnockbackEffect;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float MoveRange = 1000.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float MoveSpeed = 200.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Knockback")
    float KnockbackStrength = 1200.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Knockback")
    float VerticalBoost = 0.6f;

private:
    FVector InitialStartLocation;
    FVector EndLocation;
    FVector CurrentTarget;
};