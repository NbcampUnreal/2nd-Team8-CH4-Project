// Fill out your copyright notice in the Description page of Project Settings.


#include "LSFighter.h"

#include "Actor_Component/LS_InputMappingContext.h"
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

    if (ULS_InputMappingContext *InputMappingContext = Cast<ULS_InputMappingContext>(GetComponentByClass(ULS_InputMappingContext::StaticClass())))
    {
        EnableInput(GetWorld()->GetFirstPlayerController());
        InputMappingContext->InitializeInput();
    }
}