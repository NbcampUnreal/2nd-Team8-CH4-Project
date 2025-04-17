#include "LSBattlePlayerController.h"
#include "Blueprint/UserWidget.h"

ALSBattlePlayerController::ALSBattlePlayerController()
{
}

void ALSBattlePlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    FInputModeGameOnly InputMode;
    SetInputMode(InputMode);
};

void ALSBattlePlayerController::ClientShowResultUI_Implementation()
{
    if (ResultWidgetClass)
    {
        UUserWidget* ResultWidget = CreateWidget<UUserWidget>(this, ResultWidgetClass);
        if (ResultWidget)
        {
            ResultWidget->AddToViewport();

            FInputModeUIOnly InputMode;
            SetInputMode(InputMode);
            bShowMouseCursor = true;
        }
    }
}