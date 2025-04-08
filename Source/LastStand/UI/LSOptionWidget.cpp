// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/LSOptionWidget.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "GameInstance/LSGameInstance.h"
#include "Kismet/GameplayStatics.h"

void ULSOptionWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (MasterVolumeSlider)
    {
        ULSGameInstance* GI = Cast<ULSGameInstance>(GetGameInstance());
        if (GI)
        {
            MasterVolumeSlider->SetValue(GI->MasterVolume);

            if (VolumeText)
            {
                VolumeText->SetText(FText::FromString(FString::Printf(TEXT("Master Volume: %.2f"), GI->MasterVolume)));
            }
        }

        MasterVolumeSlider->OnValueChanged.AddDynamic(this, &ULSOptionWidget::OnMasterVolumeChanged);
    }
}

void ULSOptionWidget::OnMasterVolumeChanged(float Value)
{
    ULSGameInstance* GI = Cast<ULSGameInstance>(GetGameInstance());
    if (GI)
    {
        GI->MasterVolume = Value;
        GI->ApplyVolumeSettings();
    }

    if (VolumeText)
    {
        VolumeText->SetText(FText::FromString(FString::Printf(TEXT("Master Volume: %.2f"), Value)));
    }
}