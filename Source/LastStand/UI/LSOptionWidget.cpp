// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/LSOptionWidget.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "GameInstance/LSGameInstance.h"
#include "Kismet/GameplayStatics.h"

void ULSOptionWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (ULSGameInstance* GI = Cast<ULSGameInstance>(GetGameInstance()))
    {
        TempMasterVolume = GI->MasterVolume;

        if (MasterVolumeSlider)
        {
            MasterVolumeSlider->SetValue(TempMasterVolume);
            MasterVolumeSlider->OnValueChanged.AddDynamic(this, &ULSOptionWidget::OnMasterVolumeChanged);
        }

        if (VolumeText)
        {
            VolumeText->SetText(FText::FromString(FString::Printf(TEXT("Master Volume: %.2f"), TempMasterVolume)));
        }
    }

    if (SaveButton)
    {
        SaveButton->OnClicked.AddDynamic(this, &ULSOptionWidget::OnSaveClicked);
    }

    if (ResetButton)
    {
        ResetButton->OnClicked.AddDynamic(this, &ULSOptionWidget::OnResetClicked);
    }
}

void ULSOptionWidget::OnMasterVolumeChanged(float Value)
{
    TempMasterVolume = Value;

    if (VolumeText)
    {
        VolumeText->SetText(FText::FromString(FString::Printf(TEXT("Master Volume: %.2f"), Value)));
    }
}

void ULSOptionWidget::OnSaveClicked()
{
    if (ULSGameInstance* GI = Cast<ULSGameInstance>(GetGameInstance()))
    {
        GI->MasterVolume = TempMasterVolume;
        GI->ApplyVolumeSettings();
    }
}

void ULSOptionWidget::OnResetClicked()
{
    TempMasterVolume = 1.0f;

    if (MasterVolumeSlider)
    {
        MasterVolumeSlider->SetValue(TempMasterVolume);
    }

    if (VolumeText)
    {
        VolumeText->SetText(FText::FromString(FString::Printf(TEXT("Master Volume: %.2f"), TempMasterVolume)));
    }
}
