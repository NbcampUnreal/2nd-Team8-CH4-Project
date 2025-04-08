// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/LSOptionWidget.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "GameInstance/LSGameInstance.h"
#include "Kismet/GameplayStatics.h"

void ULSOptionWidget::NativeConstruct()
{
    Super::NativeConstruct();

<<<<<<< HEAD
<<<<<<< HEAD
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
=======
=======
>>>>>>> 28e7a37 ([add]비 로그인 시 멀티플레이 버튼 잠금)
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
<<<<<<< HEAD
>>>>>>> 2754f58335c4309b9588f979dad821e19cfaad30
=======
>>>>>>> 28e7a37 ([add]비 로그인 시 멀티플레이 버튼 잠금)
    }
}

void ULSOptionWidget::OnMasterVolumeChanged(float Value)
{
<<<<<<< HEAD
<<<<<<< HEAD
    TempMasterVolume = Value;
=======
=======
>>>>>>> 28e7a37 ([add]비 로그인 시 멀티플레이 버튼 잠금)
    ULSGameInstance* GI = Cast<ULSGameInstance>(GetGameInstance());
    if (GI)
    {
        GI->MasterVolume = Value;
        GI->ApplyVolumeSettings();
    }
<<<<<<< HEAD
>>>>>>> 2754f58335c4309b9588f979dad821e19cfaad30
=======
>>>>>>> 28e7a37 ([add]비 로그인 시 멀티플레이 버튼 잠금)

    if (VolumeText)
    {
        VolumeText->SetText(FText::FromString(FString::Printf(TEXT("Master Volume: %.2f"), Value)));
    }
<<<<<<< HEAD
<<<<<<< HEAD
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
=======
}
>>>>>>> 2754f58335c4309b9588f979dad821e19cfaad30
=======
}
>>>>>>> 28e7a37 ([add]비 로그인 시 멀티플레이 버튼 잠금)
