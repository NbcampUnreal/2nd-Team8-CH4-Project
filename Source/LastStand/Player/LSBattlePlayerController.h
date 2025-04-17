#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LSBattlePlayerController.generated.h"

UCLASS()
class LASTSTAND_API ALSBattlePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    ALSBattlePlayerController();

    UFUNCTION(Client, Reliable)
    void ClientShowResultUI();

private:
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidget> ResultWidgetClass;

protected:
    virtual void BeginPlay() override;
};
