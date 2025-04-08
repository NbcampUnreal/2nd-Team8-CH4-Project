#include "GameMode/LSArcadeGameMode.h"
//#include "Gamestate/LSGamestate.h"
#include "Player/LSBattlePlayerController.h"
#include "Kismet/GameplayStatics.h"

ALSArcadeGameMode::ALSArcadeGameMode()
{
    PlayerControllerClass = ALSBattlePlayerController::StaticClass();
    //GameStateClass = AGameState::StaticClass();

}

//int32 ALSArcadeGameMode::GetPlayerCount()
//{
//    AGameState* GameState = Cast<ALSGameState>(GetWorld()->GetGameState());
//    if (LSGameState)
//    {
//        int32 PlayerCount = LSGameState->PlayerArray.Num();
//
//        return PlayerCount;
//    }
//
//    return 0;
//}

void ALSArcadeGameMode::BeginPlay()
{
    Super::BeginPlay();

    //GetWorld()->GetTimerManager().SetTimer(
    //    GameTimerHandle,
    //    this,
    //    &ALSArcadeGameMode::OnTimeExpired,
    //    GameDuration,
    //    false
    //);
}

void ALSArcadeGameMode::EndGameConditions()
{

}

void ALSArcadeGameMode::OnTimeExpired()
{
    // if (ALSArcadePlayerController* PC = Cast<ALSArcadePlayerController>(*It))
    // {
    //     PC->ShowResultUI();
    // }
}
  
//void ALSArcadeGameMode::MulticastShowResult_Implementation() - MultiPlay
//{
//    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
//    {
//        if (ALSBattlePlayerController* PC = Cast<ALSBattlePlayerController>(*It))
//        {
//            PC->ClientShowResultUI();
//        }
//    }
//}