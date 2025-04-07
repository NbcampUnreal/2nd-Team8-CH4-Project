// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LSMatchingWidget.h"
#include "Components/TextBlock.h"

void ULSMatchingWidget::NativeConstruct()
{
    Super::NativeConstruct();

    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ULSMatchingWidget::UpdateTimerText, 1.0f, true);
}

void ULSMatchingWidget::UpdateTimerText()
{
    ElapsedTime++;

    int32 Minutes = ElapsedTime / 60;
    int32 Seconds = ElapsedTime % 60;
    FString TimerString = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);

    if (MatchingTimerText)
    {
        MatchingTimerText->SetText(FText::FromString(TimerString));
    }
}
