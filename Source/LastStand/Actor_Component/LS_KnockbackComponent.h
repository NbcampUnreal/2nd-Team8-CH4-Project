// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LS_KnockbackComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LASTSTAND_API ULS_KnockbackComponent : public UActorComponent
{
    GENERATED_BODY()


public:
    ULS_KnockbackComponent();

    UFUNCTION(BlueprintCallable)
    void ApplyKnockback(FVector SourceLocation, float Strength, float VerticalBoost);

    UFUNCTION(BlueprintCallable)
    void TriggerKnockbackFromParticle(AActor* InstigatorActor, float Strength = 1200.f, float VerticalBoost = 0.5f);
};