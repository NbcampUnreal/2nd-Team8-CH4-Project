// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LSPickPlayerController.generated.h"

class ULSCharacterPickWidget;
/**
 * 
 */
UCLASS()
class LASTSTAND_API ALSPickPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    UFUNCTION(Client, Reliable)
    void ClientStartPick(int32 PlayerCount);

    UFUNCTION(Client, Reliable)
    void ClientActiveGameStartButton();
    
    bool IsLoaded() const { return bLoaded; }
    FName GetPickCharacterName() const { return PickCharacterName; }

protected:
    virtual void BeginPlay() override;

private:
    UFUNCTION(Client, Reliable)
    void ClientPickCharacter(int PlayerNumber, FName CharacterName);

    UFUNCTION(Server, Reliable)
    void ServerCompleteLoad();

    UFUNCTION(Server, Reliable, BlueprintCallable)
    void ServerPickCharacter(FName CharacterName);

private:
    const int32 MaxPlayerCount = 6;
    
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<ULSCharacterPickWidget> CharacterPickWidgetClass;

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UUserWidget> MapPickWidgetClass;
    
    TObjectPtr<ULSCharacterPickWidget> CharacterPickWidget;
    TObjectPtr<UUserWidget> MapPickWidget;
    bool bLoaded;
    FName PickCharacterName;
};
