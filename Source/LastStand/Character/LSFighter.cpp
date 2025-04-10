// Fill out your copyright notice in the Description page of Project Settings.


#include "LSFighter.h"

#include "Blueprint/UserWidget.h"
#include "EOS/LSSessionSubsystem.h"


ALSFighter::ALSFighter()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ALSFighter::BeginPlay()
{
    Super::BeginPlay();

}

void ALSFighter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ALSFighter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}
