// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/LSBaseWidget.h"
#include "LSMatchingWidget.generated.h"

/**
 * 
 */
UCLASS()
class LASTSTAND_API ULSMatchingWidget : public ULSBaseWidget
{
	GENERATED_BODY()
	
protected:
    virtual void NativeConstruct() override;

private:
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* MatchingTimerText;

    FTimerHandle TimerHandle;
    int32 ElapsedTime = 0;

    void UpdateTimerText();
};
