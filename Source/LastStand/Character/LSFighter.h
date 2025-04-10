// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LSFighter.generated.h"

class UUserWidget;
class UInputComponent;

UCLASS()
class LASTSTAND_API ALSFighter : public ACharacter
{
    GENERATED_BODY()

public:
    ALSFighter();

    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
    virtual void BeginPlay() override;

};
