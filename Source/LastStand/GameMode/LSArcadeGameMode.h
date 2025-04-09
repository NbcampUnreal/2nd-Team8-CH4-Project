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

    UPROPERTY(BlueprintReadWrite, Category = "Game Rules")
    bool bIsGameRunning = false;

    UPROPERTY(BlueprintReadWrite, Category = "Game Rules")
    float ElapsedTime = 0.0f;

    UPROPERTY(BlueprintReadWrite, Category = "Game Rules")
    int32 KillScore = 0;

    UFUNCTION(BlueprintPure, Category = "Game Rules")
   float GetElapsedTime() const { return ElapsedTime; }

protected:
    virtual void BeginPlay() override;

    virtual void Tick(float DeltaSeconds) override;
private:


};
