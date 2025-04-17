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

    void UpdateSurfaceResponse();


    void HandleIceMaterial();
    void HandleFastMaterial();
    void HandleSlowMaterial();
    void HandleHighJump();
    void HandleLowJump();
    void HandleTickJump();
    void RestoreDefaultValues();

public:
  
    UPROPERTY(EditAnywhere, Category = "Materials")
    UPhysicalMaterial* IceMaterial;

    UPROPERTY(EditAnywhere, Category = "Materials")
    UPhysicalMaterial* FastMaterial;

    UPROPERTY(EditAnywhere, Category = "Materials")
    UPhysicalMaterial* SlowMaterial;

    UPROPERTY(EditAnywhere, Category = "Materials")
    UPhysicalMaterial* HighJumpMaterial;

    UPROPERTY(EditAnywhere, Category = "Materials")
    UPhysicalMaterial* LowJumpMaterial;

    UPROPERTY(EditAnywhere, Category = "Materials")
    UPhysicalMaterial* TickJumpMaterial;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ice Movement")
    float IceGroundFriction = 0.0001f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ice Movement")
    float IceBrakingFrictionFactor = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ice Movement")
    float IceBrakingDeceleration = 1.0f;

   
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ice Movement")
    float NormalGroundFriction = 8.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ice Movement")
    float NormalBrakingFrictionFactor = 2.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ice Movement")
    float NormalBrakingDeceleration = 2048.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed Control")
    float FastSpeed = 800.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed Control")
    float SlowSpeed = 200.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed Control")
    float NormalSpeed = 600.f;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump Settings")
    float NormalJumpZVelocity = 600.f;

  
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump Settings")
    float HighJumpZVelocity = 1200.f;   

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump Settings")
    float LowJumpZVelocity = 200.f;    

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump Settings")
    float TickJumpZVelocity = 1000.0f;  
   
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    USoundBase* JumpSound;
};