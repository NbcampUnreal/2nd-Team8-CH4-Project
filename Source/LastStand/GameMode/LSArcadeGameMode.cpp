#include "GameMode/LSArcadeGameMode.h"
#include "Player/LSBattlePlayerController.h"
#include "Kismet/GameplayStatics.h"

ALSArcadeGameMode::ALSArcadeGameMode()
{
    // PlayerControllerClass = ALSBattlePlayerController::StaticClass();

    PrimaryActorTick.bCanEverTick = true;
}

void ALSArcadeGameMode::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void ALSArcadeGameMode::BeginPlay()
{
    Super::BeginPlay();
}