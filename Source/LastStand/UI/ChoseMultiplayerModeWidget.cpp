// Fill out your copyright notice in the Description page of Project Settings.


#include "ChoseMultiplayerModeWidget.h"
#include "Components/Button.h"
#include "EOS/LSSessionSubsystem.h"

void UChoseMultiplayerModeWidget::NativeConstruct()
{
    Super::NativeConstruct();

    BindButtonEvents();
}

void UChoseMultiplayerModeWidget::BindButtonEvents()
{
    if (MatchingGameButton)
    {
        MatchingGameButton->OnClicked.AddDynamic(this, &UChoseMultiplayerModeWidget::OnMatchingGameButtonClicked);
    }
    if (CustomGameButton)
    {
        CustomGameButton->OnClicked.AddDynamic(this, &UChoseMultiplayerModeWidget::OnCustomGameButtonClicked);
    }
}

void UChoseMultiplayerModeWidget::OnMatchingGameButtonClicked()
{
    if (ULSSessionSubsystem *LSSessionSubsystem = GetGameInstance()->GetSubsystem<ULSSessionSubsystem>())
    {
        LSSessionSubsystem->FindMatchmakingSession();
    }
}

void UChoseMultiplayerModeWidget::OnCustomGameButtonClicked()
{
    if (ULSSessionSubsystem *LSSessionSubsystem = GetGameInstance()->GetSubsystem<ULSSessionSubsystem>())
    {
        // LSSessionSubsystem->FindCustomSession();
    }
}

