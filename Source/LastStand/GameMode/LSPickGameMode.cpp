// Fill out your copyright notice in the Description page of Project Settings.


#include "LSPickGameMode.h"

#include "Player/LSPickPlayerController.h"
#include "Kismet/GameplayStatics.h"

ALSPickGameMode::ALSPickGameMode()
{
    PlayerControllerClass = ALSPickPlayerController::StaticClass();
}

void ALSPickGameMode::GameStart()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("게임 시작"));

    ALSPickPlayerController* PickPlayerController = GetWorld()->GetFirstPlayerController<ALSPickPlayerController>();
    //asasd
    
    FString MapName = PickPlayerController->GetPickMapName();
    GetWorld()->ServerTravel(MapName);
}

void ALSPickGameMode::CheckAllLoaded()
{
    bool bAllLoad = true;
    for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
    {
        if (ALSPickPlayerController* PlayerController = Cast<ALSPickPlayerController>(Iter->Get()))
        {
            bAllLoad &= PlayerController->IsLoaded();
        }
    }

    //PlayerController가 천천히 생기기 때문에 호스트가 처음 들어왔을 땐 PlayerController가 1개임
    //그 후 들어오는 플레이어마다 1씩 늘어남
    int PlayerCount = GetWorld()->GetNumPlayerControllers();
    int TempMaxPlayerCount = 2; //임시. EOS에서 정원의 인원수 뚫어주면 바꿀거임
    
    if (PlayerCount == TempMaxPlayerCount && bAllLoad)
    {
        for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
        {
            if (ALSPickPlayerController* PlayerController = Cast<ALSPickPlayerController>(Iter->Get()))
            {
                PlayerController->ClientStartPickCharacter(PlayerCount);
            }
        }
    }
}

void ALSPickGameMode::CheckAllPlayerPick()
{
    bool bAllPlayerPick = true;
    for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
    {
        if (ALSPickPlayerController* PlayerController = Cast<ALSPickPlayerController>(Iter->Get()))
        {
            FName CharacterName = PlayerController->GetPickCharacterName();
            if (CharacterName == "" || CharacterName == "None")
            {
                bAllPlayerPick = false;
                break;
            }
        }
    }
    
    if(!bAllPlayerPick)
    {
        return;
    }
    
    //모두 캐릭터를 픽함
    
    for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
    {
        if (ALSPickPlayerController* PlayerController = Cast<ALSPickPlayerController>(Iter->Get()))
        {
            PlayerController->ClientActiveGameStartButton();
        }
    }
}
