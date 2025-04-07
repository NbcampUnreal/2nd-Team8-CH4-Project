// Fill out your copyright notice in the Description page of Project Settings.


#include "LSSelectCharacterWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Data/LSCharacterDataAsset.h"
#include "Data/LSGameDataSubSystem.h"


void ULSSelectCharacterWidget::NativeConstruct()
{
    Super::NativeConstruct();

    SetCharacter(NowKeyName);
}

void ULSSelectCharacterWidget::SetCharacter_Implementation(FName KeyName)
{
    if (KeyName == "" || KeyName == "None")
    {
        return;
    }

    FCharacterData Data = GetGameInstance()->GetSubsystem<ULSGameDataSubsystem>()->Character->GetCharacterData(KeyName);
    
    if (Data.KeyName == "")
    {
        UE_LOG(LogTemp, Warning, TEXT("Can't Find Character Data"))
        return;
    }
    
    NowKeyName = KeyName;
    
    PortImage->SetBrushFromTexture(Data.Image);
    NameText->SetText(FText::FromString(Data.DisplayName));
}

void ULSSelectCharacterWidget::VisibleBorder(int PlayerNumber)
{
    if (BorderImages.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("BorderImages가 설정되어있지 않습니다."))
        return;
    }

    const int MaxPlayerCount = BorderImages.Num();
    if (PlayerNumber < MaxPlayerCount)
    {
        BorderImages[PlayerNumber]->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("플레이어는 %d명을 넘을 수 없습니다."), MaxPlayerCount)
    }
}

void ULSSelectCharacterWidget::HiddenBorder(int PlayerNumber)
{
    if (BorderImages.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("BorderImages가 설정되어있지 않습니다."))
        return;
    }
    
    if (PlayerNumber == INDEX_NONE)
    {
        for (auto& Widget : BorderImages)
        {
            Widget->SetVisibility(ESlateVisibility::Hidden);
        }
    }
    else
    {
        BorderImages[PlayerNumber]->SetVisibility(ESlateVisibility::Hidden);
    }
}
