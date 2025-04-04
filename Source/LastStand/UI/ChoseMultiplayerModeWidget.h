// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChoseMultiplayerModeWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class LASTSTAND_API UChoseMultiplayerModeWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;

private:
    void BindButtonEvents();
    
    UFUNCTION()
    void OnMatchingGameButtonClicked();
    UFUNCTION()
    void OnCustomGameButtonClicked();

private:
    UPROPERTY(meta = (BindWidget))
    UButton* MatchingGameButton;
    UPROPERTY(meta = (BindWidget))
    UButton* CustomGameButton;
    UPROPERTY(meta = (BindWidget))
    UButton* CloseButton;
};
