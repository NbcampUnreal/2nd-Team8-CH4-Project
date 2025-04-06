// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UEditableTextBox;
class UButton;
/**
 * 
 */
UCLASS()
class LASTSTAND_API UMainMenuWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION()
    void OnArcadeModeButtonClicked();
    UFUNCTION()
    void OnMultiplayerModeButtonClicked();
    UFUNCTION()
    void OnLoginButtonClicked();
    UFUNCTION()
    void OnExitButtonClicked();
    UFUNCTION()
    void EnableMultiplayerModeButton();
    UFUNCTION()
    void DisableMultiplayerModeButton();

protected:
    virtual void NativeConstruct() override;

private:
    void BindButtonEvents();
    void BindDelegates();
    
private:
    UPROPERTY(EditAnywhere, category = "UI")
    UUserWidget *ChoseMultiplayerModeWidget;
    UPROPERTY(meta = (BindWidget))
    UButton* ArcadeModeButton;
    UPROPERTY(meta = (BindWidget))
    UButton* MultiplayerModeButton;
    UPROPERTY(meta = (BindWidget))
    UButton* LoginButton;
    UPROPERTY(meta = (BindWidget))
    UButton* ExitButton;
    
    //Dev only
    UPROPERTY(meta = (BindWidget))
    UEditableTextBox* CredentialTextBox;
};
