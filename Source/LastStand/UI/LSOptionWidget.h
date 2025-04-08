// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/LSBaseWidget.h"
#include "LSOptionWidget.generated.h"

class USlider;
class UTextBlock;

UCLASS()
class LASTSTAND_API ULSOptionWidget : public ULSBaseWidget
{
	GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;

<<<<<<< HEAD
<<<<<<< HEAD

    UFUNCTION()
    void OnMasterVolumeChanged(float Value);

    UFUNCTION()
    void OnSaveClicked();

    UFUNCTION()
    void OnResetClicked();
    
    float TempMasterVolume = 1.0f;

=======
>>>>>>> 2754f58335c4309b9588f979dad821e19cfaad30
=======
>>>>>>> 28e7a37 ([add]비 로그인 시 멀티플레이 버튼 잠금)
    UPROPERTY(meta = (BindWidget))
    USlider* MasterVolumeSlider;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* VolumeText;

<<<<<<< HEAD
<<<<<<< HEAD
    UPROPERTY(meta = (BindWidget))
    UButton* SaveButton;

    UPROPERTY(meta = (BindWidget))
    UButton* ResetButton;
=======
    UFUNCTION()
    void OnMasterVolumeChanged(float Value);
>>>>>>> 2754f58335c4309b9588f979dad821e19cfaad30
=======
    UFUNCTION()
    void OnMasterVolumeChanged(float Value);
>>>>>>> 28e7a37 ([add]비 로그인 시 멀티플레이 버튼 잠금)
};
