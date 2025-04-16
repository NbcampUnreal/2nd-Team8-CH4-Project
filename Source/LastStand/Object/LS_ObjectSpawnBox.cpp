// Fill out your copyright notice in the Description page of Project Settings.


#include "LS_ObjectSpawnBox.h"
#include "Components/BoxComponent.h"

ALS_ObjectSpawnBox::ALS_ObjectSpawnBox()
{
    PrimaryActorTick.bCanEverTick = false;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

    SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
    SpawnBox->SetupAttachment(RootComponent);
    SpawnBox->SetBoxExtent(FVector(50.f, 50.f, 50.f));
    SpawnBox->SetHiddenInGame(false); // 항상 보여지게
    SpawnBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}



