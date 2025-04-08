// Fill out your copyright notice in the Description page of Project Settings.


#include "LSMapPickWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Data/LSGameDataSubsystem.h"
#include "Data/LSMapDataAsset.h"


void ULSMapPickWidget::SetMapPreview(const FString& MapName)
{
    const FMapData MapData = GetGameInstance()->GetSubsystem<ULSGameDataSubsystem>()->Map->GetMapData(MapName);

    MapPreviewText->SetText(MapData.DisplayName);
    MapPreviewImage->SetBrushFromTexture(MapData.Image);
}
