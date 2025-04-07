// Fill out your copyright notice in the Description page of Project Settings.


#include "LSCharacterDataAsset.h"

FCharacterData ULSCharacterDataAsset::GetCharacterData(FName Key)
{
    FCharacterData* FindData = CharacterDatas.FindByPredicate([Key](const FCharacterData& Data)
    {
        return Data.KeyName == Key;
    });

    return *FindData;
}
