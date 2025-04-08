// Fill out your copyright notice in the Description page of Project Settings.


#include "LSGameDataSubsystem.h"
#include "LSCharacterDataAsset.h"
#include "LSGameDataSubsystemSettings.h"
#include "LSMapDataAsset.h"


void ULSGameDataSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    LoadData();
}

void ULSGameDataSubsystem::LoadData()
{
    const ULSGameDataSubsystemSettings* DataSettings = GetDefault<ULSGameDataSubsystemSettings>();
    Character = DataSettings->CharacterDataAsset.LoadSynchronous();
    Map = DataSettings->MapDataAsset.LoadSynchronous();
    
    check(Character)
    check(Map)
}
