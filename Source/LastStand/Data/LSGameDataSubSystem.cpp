// Fill out your copyright notice in the Description page of Project Settings.


#include "LSGameDataSubsystem.h"
#include "LSCharacterDataAsset.h"


ULSGameDataSubsystem::ULSGameDataSubsystem()
{
    LoadData();
}

void ULSGameDataSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    checkf(Character, TEXT("Failed to Load CharacterTable"));
}

void ULSGameDataSubsystem::LoadData()
{
    static ConstructorHelpers::FObjectFinder<ULSCharacterDataAsset> CharacterDataLoader(
        TEXT("/Script/LastStand.LSCharacterDataAsset'/Game/LastStand/Data/DA_Character.DA_Character'"));

    if (CharacterDataLoader.Object)
        Character = CharacterDataLoader.Object;
}
