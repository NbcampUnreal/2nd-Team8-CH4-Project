// Fill out your copyright notice in the Description page of Project Settings.


#include "LSPickPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "GameFramework/GameStateBase.h"
#include "GameMode/LSPickGameMode.h"
#include "UI/Pick/LSCharacterPickWidget.h"
#include "UI/Pick/LSSelectCharacterWidget.h"

void ALSPickPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (IsLocalController() == false)
    {
        return;
    }

    SetShowMouseCursor(true);

    //픽 화면 추가
    CharacterPickWidget = CreateWidget<ULSCharacterPickWidget>(this, CharacterPickWidgetClass);
    CharacterPickWidget->AddToViewport();

    //위젯들 비활성화
    TArray<UWidget*> Widgets;
    CharacterPickWidget->WidgetTree->GetAllWidgets(Widgets);

    for (UWidget* Widget : Widgets)
    {
        Widget->SetIsEnabled(false);
    }

    ServerCompleteLoad();
}

void ALSPickPlayerController::ClientStartPick_Implementation(int32 PlayerCount)
{
    //위젯들 활성화
    TArray<UWidget*> Widgets;
    CharacterPickWidget->WidgetTree->GetAllWidgets(Widgets);

    for (UWidget* Widget : Widgets)
    {
        Widget->SetIsEnabled(true);
    }

    //정원만큼 픽창 줄임
    UWidget* SelectedCharacterWidget = CharacterPickWidget->GetWidgetFromName("SelectedCharacterPanel");
    check(SelectedCharacterWidget);
    
    UPanelWidget* SelectedPanel = Cast<UPanelWidget>(SelectedCharacterWidget);
    for (int i = 0; i < MaxPlayerCount - PlayerCount; i++)
        SelectedPanel->RemoveChildAt(SelectedPanel->GetChildrenCount() - 1);
}

void ALSPickPlayerController::ClientPickCharacter_Implementation(int PlayerNumber, FName CharacterName)
{
    UWidget* TileWidget = CharacterPickWidget->GetWidgetFromName("SelectCharacterTile");
    check(TileWidget);
    
    UPanelWidget* TilePanel = Cast<UPanelWidget>(TileWidget);
    for (int i = 0; i < TilePanel->GetChildrenCount(); i++)
    {
        if (ULSSelectCharacterWidget* SelectCharacter = Cast<ULSSelectCharacterWidget>(TilePanel->GetChildAt(i)))
        {
            SelectCharacter->HiddenBorder(PlayerNumber);
            
            if (SelectCharacter->GetKeyName() != "" && SelectCharacter->GetKeyName() != "None" &&
                SelectCharacter->GetKeyName() == CharacterName)
            {
                SelectCharacter->VisibleBorder(PlayerNumber);
            }
        }
    }
    
    UWidget* SelectedCharacterWidget = CharacterPickWidget->GetWidgetFromName("SelectedCharacterPanel");
    check(SelectedCharacterWidget);
    
    UPanelWidget* SelectedPanel = Cast<UPanelWidget>(SelectedCharacterWidget);
    
    check(PlayerNumber < SelectedPanel->GetChildrenCount())
    ULSSelectCharacterWidget* SCWidget = Cast<ULSSelectCharacterWidget>(SelectedPanel->GetChildAt(PlayerNumber));
    
    SCWidget->SetCharacter(CharacterName);
}

void ALSPickPlayerController::ClientActiveGameStartButton_Implementation()
{
    CharacterPickWidget->PlayStartButtonAnimation();
}

void ALSPickPlayerController::ServerPickCharacter_Implementation(FName CharacterName)
{
    PickCharacterName = CharacterName;
    
    //서버 기준 몇번째 PlayerState인지를 PlayerNumber로 설정
    int PickPlayerNumber = GetWorld()->GetGameState()->PlayerArray.Find(PlayerState);
    for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
    {
        if (ALSPickPlayerController* Cont = Cast<ALSPickPlayerController>(*Iter))
        {            
            Cont->ClientPickCharacter(PickPlayerNumber, CharacterName);
        }
    }

    GetWorld()->GetAuthGameMode<ALSPickGameMode>()->CheckAllPlayerPick();
}

void ALSPickPlayerController::ServerCompleteLoad_Implementation()
{
    //서버에서만 실행되므로 서버에 있는 Controller만 true가 되어있음
    bLoaded = true;
    GetWorld()->GetAuthGameMode<ALSPickGameMode>()->CheckAllLoaded();
}
