// Fill out your copyright notice in the Description page of Project Settings.


#include "LSGameDataSubSystem.h"


ULSGameDataSubSystem::ULSGameDataSubSystem()
{
    LoadData();
}

void ULSGameDataSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    
    checkf(CharacterTable, TEXT("Failed to Load CharacterTable"));
}

void ULSGameDataSubSystem::LoadData()
{
    static ConstructorHelpers::FObjectFinder<UDataTable> CharacterTableLoader(
        TEXT("/Script/Engine.DataTable'/Game/LastStand/Data/BT_Character.BT_Character'"));
    if (CharacterTableLoader.Succeeded())
        CharacterTable = CharacterTableLoader.Object;
}
