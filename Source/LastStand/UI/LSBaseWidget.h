// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "LSBaseWidget.generated.h"

/**
 *
 */
UCLASS()
class LASTSTAND_API ULSBaseWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    ULSBaseWidget(const FObjectInitializer& ObjectInitializer);

protected:
    virtual bool Initialize() override;
    virtual void NativeConstruct() override;//위젯이 AddToViewport 될때마다 호출
    virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "UI")
    TArray<UButton*> NavigationButtons;//사용할 버튼들은 블루프린트에서 추가

    UPROPERTY(BlueprintReadWrite, Category = "UI")
    int32 CurrentButtonIndex = 0;

    void SelectButton(int32 Direction);
    void FocusCurrentButton();

    UFUNCTION(BlueprintCallable, Category = "UI")
    void Enter();

    UFUNCTION(BlueprintImplementableEvent, Category = "UI")//블루프린트에서 구현(뒤로가기)
        void GoBack();
};
