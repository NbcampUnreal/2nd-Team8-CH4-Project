// Fill out your copyright notice in the Description page of Project Settings.


#include "LSPickGameMode.h"

#include "Data/LSGameDataSubSystem.h"
#include "Data/LSMapDataAsset.h"
#include "EOS/LSSessionSubsystem.h"
#include "Player/LSPickPlayerController.h"
#include "Kismet/GameplayStatics.h"

ALSPickGameMode::ALSPickGameMode()
{
    PlayerControllerClass = ALSPickPlayerController::StaticClass();
}

void ALSPickGameMode::GameStart(FMapData MapData)
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("게임 시작"));
    
    //데이터를 붙여서 보냄 (원래 이렇게해서 맵에 전달 후 생성하려고 했는데 있는거 이용하기로 결정)
    FString OpenURL = MapData.Level.GetAssetName();
    OpenURL += "?";
    int a = 0;
    TArray<FName> PickCharacters;
    
    for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
    {
        if (ALSPickPlayerController* Cont = Cast<ALSPickPlayerController>(*Iter))
        {
            int32 PlayerNumber = a;
            // int32 PlayerNumber = GetGameInstance()->GetSubsystem<ULSSessionSubsystem>()->GetIndexOfPlayerInSession(Cont);
            OpenURL.Append("&");
            OpenURL.AppendInt(PlayerNumber);
            OpenURL.Append("=" + Cont->GetPickCharacterName().ToString());
            a++;

            PickCharacters.Add(Cont->GetPickCharacterName());
        }
    }

    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, OpenURL);

    //GameInstance 설정 (블프에서 해야함)
    SetGameSettings(PickCharacters, MapData);
    
    GetWorld()->ServerTravel(OpenURL);
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
    int TempMaxPlayerCount = TempPlayerSize;
    // int TempMaxPlayerCount = GetGameInstance()->GetSubsystem<ULSSessionSubsystem>()->GetNumOfPlayersInSession();

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

    if (!bAllPlayerPick)
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
