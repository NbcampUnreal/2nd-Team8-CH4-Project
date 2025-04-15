// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LS_Floor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LASTSTAND_API ULS_Floor : public UActorComponent
{
	GENERATED_BODY()

public:
    ULS_Floor();

protected:
    virtual void BeginPlay() override;

public:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    class ACharacter* OwnerCharacter;
    class UCharacterMovementComponent* MoveComp;

    void UpdateIceSurfaceResponse();

public:
    UPROPERTY(EditAnywhere, Category = "Speed Control")
    UPhysicalMaterial* FastMaterial;

    UPROPERTY(EditAnywhere, Category = "Speed Control")
    UPhysicalMaterial* SlowMaterial;

    UPROPERTY(EditAnywhere, Category = "Ice Floor")
    UPhysicalMaterial* IceMaterial;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ice Movement")
    float IceGroundFriction = 0.0001f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ice Movement")
    float IceBrakingFrictionFactor = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ice Movement")
    float IceBrakingDeceleration = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ice Movement")
    float DefaultGroundFriction = 8.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ice Movement")
    float DefaultBrakingFrictionFactor = 2.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ice Movement")
    float DefaultBrakingDeceleration = 2048.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed Control")
    float FastSpeed = 800.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed Control")
    float SlowSpeed = 200.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed Control")
    float DefaultSpeed = 600.f;
};
