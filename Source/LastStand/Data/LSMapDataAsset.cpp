// Fill out your copyright notice in the Description page of Project Settings.


#include "LSMapDataAsset.h"

FMapData ULSMapDataAsset::GetMapData(FString MapName)
{
    FMapData* FindData = MapDatas.FindByPredicate([MapName](const FMapData& Data)
    {
        return Data.Name == MapName;
    });

    return *FindData;
}

FMapData ULSMapDataAsset::GetRandomMapData()
{
    return MapDatas[FMath::RandRange(0, MapDatas.Num() - 1)];
}
