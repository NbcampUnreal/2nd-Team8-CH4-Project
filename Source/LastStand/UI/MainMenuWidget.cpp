// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"

#include "Components/Button.h"
#include "EOS/LSLoginSubsystem.h"

void UMainMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();
    
    BindButtonEvents();
    BindDelegates();
    
    DisableMultiplayerModeButton();
}

void UMainMenuWidget::BindButtonEvents()
{
    if (ArcadeModeButton)
    {
        ArcadeModeButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnArcadeModeButtonClicked);
    }

    if (MultiplayerModeButton)
    {
        MultiplayerModeButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnMultiplayerModeButtonClicked);
    }

    if (LoginButton)
    {
        LoginButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnLoginButtonClicked);
    }

    if (ExitButton)
    {
        ExitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnExitButtonClicked);
    }
}

void UMainMenuWidget::BindDelegates()
{
    if (ULSLoginSubsystem *LoginSubsystem = GetGameInstance()->GetSubsystem<ULSLoginSubsystem>())
    {
        LoginSubsystem->OnEOSLoginComplete.AddDynamic(this, &UMainMenuWidget::EnableMultiplayerModeButton);
    }
}

void UMainMenuWidget::OnArcadeModeButtonClicked()
{
}

void UMainMenuWidget::OnMultiplayerModeButtonClicked()
{
    if (ChoseMultiplayerModeWidget)
    {
        ChoseMultiplayerModeWidget->AddToViewport();
    }
}

void UMainMenuWidget::OnLoginButtonClicked()
{
    if (ULSLoginSubsystem *LoginSubsystem = GetGameInstance()->GetSubsystem<ULSLoginSubsystem>())
    {
        // For dev authentication
        LoginSubsystem->LoginWithEOS("127.0.0.1:8081", "Admin", "developer");
    }
}

void UMainMenuWidget::OnExitButtonClicked()
{
    FGenericPlatformMisc::RequestExit(false);
}

void UMainMenuWidget::EnableMultiplayerModeButton()
{
    if (MultiplayerModeButton)
    {
        MultiplayerModeButton->SetIsEnabled(true);
    }
}

void UMainMenuWidget::DisableMultiplayerModeButton()
{
    if (MultiplayerModeButton)
    {
        MultiplayerModeButton->SetIsEnabled(false);
    }
}

