// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LSMapPickWidget.generated.h"

class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class LASTSTAND_API ULSMapPickWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetMapPreview(const FString& MapName);

protected:
    UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
    UTextBlock* MapPreviewText;

    UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
    UImage* MapPreviewImage;
};
