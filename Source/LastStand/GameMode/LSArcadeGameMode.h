#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "LSArcadeGameMode.generated.h"

UCLASS()
class LASTSTAND_API ALSArcadeGameMode : public AGameMode
{
    GENERATED_BODY()

public:
    ALSArcadeGameMode();

    //int32 GetPlayerCount(); - MultiPlay

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere)
    int32 KillScore = 0;

    void EndGameConditions();

    FTimerHandle GameTimerHandle;
    float GameDuration = 180.f;

    void OnTimeExpired();
    
     
    //int32 PlayerNum; - MultiPlay
    // 
    //UFUNCTION(NetMulticast, Reliable)
    //void MulticastShowResult();
};
