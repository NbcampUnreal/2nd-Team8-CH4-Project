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

    UPROPERTY(meta = (BindWidget))
    USlider* MasterVolumeSlider;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* VolumeText;

    UFUNCTION()
    void OnMasterVolumeChanged(float Value);
};
