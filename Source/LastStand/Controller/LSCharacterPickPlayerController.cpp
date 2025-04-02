// Fill out your copyright notice in the Description page of Project Settings.


#include "LSCharacterPickPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "GameFramework/PlayerState.h"
#include "GameMode/LSCharacterPickGameMode.h"
#include "Kismet/GameplayStatics.h"

void ALSCharacterPickPlayerController::ClientStartPick_Implementation()
{
    //위젯들 활성화
    TArray<UWidget*> Widgets;
    PickWidget->WidgetTree->GetAllWidgets(Widgets);

    for (UWidget* Widget : Widgets)
        Widget->SetIsEnabled(true);
}

void ALSCharacterPickPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (IsLocalController() == false)
        return;

    SetShowMouseCursor(true);

    //픽 화면 추가
    PickWidget = CreateWidget(this, PickWidgetClass);
    PickWidget->AddToViewport();

    //위젯들 비활성화
    TArray<UWidget*> Widgets;
    PickWidget->WidgetTree->GetAllWidgets(Widgets);

    for (UWidget* Widget : Widgets)
        Widget->SetIsEnabled(false);

    ServerCompleteLoad();
}

void ALSCharacterPickPlayerController::ClientPickCharacter_Implementation(int PlayerNumber, FName CharacterName)
{
    // if (UWidget* Widget = PickWidget->GetWidgetFromName("CharacterPickTile"))
        
}

void ALSCharacterPickPlayerController::ServerPickCharacter_Implementation(FName CharacterName)
{
}

void ALSCharacterPickPlayerController::ServerCompleteLoad_Implementation()
{
    //서버에서만 실행되므로 서버에 있는 Controller만 true가 되어있음
    bLoaded = true;
    GetWorld()->GetAuthGameMode<ALSCharacterPickGameMode>()->CheckAllLoaded();
}
