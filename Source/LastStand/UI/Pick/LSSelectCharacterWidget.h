// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LSSelectCharacterWidget.generated.h"

class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class LASTSTAND_API ULSSelectCharacterWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void SetCharacter(FName KeyName);

    UFUNCTION(BlueprintCallable)
    void VisibleBorder(int PlayerNumber);

    UFUNCTION(BlueprintCallable)
    void HiddenBorder(int PlayerNumber);

    FName GetKeyName() const { return NowKeyName; }

protected:
    virtual void NativeConstruct() override;

protected:
    UPROPERTY(meta=(BindWidget))
    TObjectPtr<UImage> PortImage;

    UPROPERTY(meta=(BindWidget))
    TObjectPtr<UTextBlock> NameText;

    UPROPERTY(BlueprintReadWrite)
    TArray<UWidget*> BorderImages;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName NowKeyName;
};
