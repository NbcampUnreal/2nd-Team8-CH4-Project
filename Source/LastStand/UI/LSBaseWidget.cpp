// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LSBaseWidget.h"
#include "Components/Button.h"
#include "Blueprint/WidgetTree.h"

ULSBaseWidget::ULSBaseWidget(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    bIsFocusable = true;
}

bool ULSBaseWidget::Initialize()
{
    bool Success = Super::Initialize();
    if (!Success) return false;

    
    if (NavigationButtons.Num() > 0)
    {
        CurrentButtonIndex = 0;
        FocusCurrentButton();
    }

    return true;
}

void ULSBaseWidget::NativeConstruct()
{
    Super::NativeConstruct();

    NavigationButtons.Empty();

    TArray<UWidget*> Widgets;
    WidgetTree->GetAllWidgets(Widgets);

    for (UWidget* Widget : Widgets)//언리얼 자체 네비게이션룰 끄기
    {
        UButton* Button = Cast<UButton>(Widget);
        if (Button)
        {
            NavigationButtons.Add(Button);

            Button->SetNavigationRule(EUINavigation::Up, EUINavigationRule::Escape, NAME_None);
            Button->SetNavigationRule(EUINavigation::Down, EUINavigationRule::Escape, NAME_None);
            Button->SetNavigationRule(EUINavigation::Left, EUINavigationRule::Escape, NAME_None);
            Button->SetNavigationRule(EUINavigation::Right, EUINavigationRule::Escape, NAME_None);
        }
    }

    if (NavigationButtons.Num() > 0)
    {
        CurrentButtonIndex = 0;
        FocusCurrentButton();
    }

    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (PC)
    {
        FInputModeUIOnly InputMode;
        InputMode.SetWidgetToFocus(TakeWidget());
        PC->SetInputMode(InputMode);
        PC->bShowMouseCursor = true;
    }
}

FReply ULSBaseWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{


    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (PC)
    {
        this->SetKeyboardFocus();
        PC->SetInputMode(FInputModeUIOnly());
    }

    FKey Key = InKeyEvent.GetKey();

    if (Key == EKeys::Up || Key == EKeys::Left)
    {
        SelectButton(-1);
    }
    else if (Key == EKeys::Down || Key == EKeys::Right)
    {
        SelectButton(1);
    }
    else if (Key == EKeys::Enter || Key == EKeys::SpaceBar)
    {
        Enter();
    }
    else if (Key == EKeys::Escape)
    {
        GoBack();
    }

    return FReply::Handled();
}

void ULSBaseWidget::SelectButton(int32 Direction)
{

    int32 PrevIndex = CurrentButtonIndex;
    CurrentButtonIndex = (CurrentButtonIndex + Direction + NavigationButtons.Num()) % NavigationButtons.Num();

    FocusCurrentButton();
}

void ULSBaseWidget::FocusCurrentButton()
{
    if (!NavigationButtons.IsValidIndex(CurrentButtonIndex)) return;

    UButton* CurrentButton = NavigationButtons[CurrentButtonIndex];
    if (!CurrentButton) return;

    for (UButton* Button : NavigationButtons)
    {
        if (Button)
        {
            Button->SetRenderScale(FVector2D(1.0f, 1.0f));
        }
    }
    CurrentButton->SetRenderScale(FVector2D(1.1f, 1.1f));
    CurrentButton->SetKeyboardFocus();

    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (PC)
    {
        PC->SetInputMode(FInputModeUIOnly());
        this->SetUserFocus(PC);
    }
}

void ULSBaseWidget::Enter()
{
    UButton* CurrentButton = NavigationButtons[CurrentButtonIndex];
    
    CurrentButton->OnClicked.Broadcast();
}
