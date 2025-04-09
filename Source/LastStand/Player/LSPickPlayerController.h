// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LSPickPlayerController.generated.h"

class ULSMapPickWidget;
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
    void ClientStartPickCharacter(int32 PlayerCount);

    UFUNCTION(Client, Reliable)
    void ClientActiveGameStartButton();

    bool IsLoaded() const { return bLoaded; }
    FName GetPickCharacterName() const { return PickCharacterName; }
    FString GetPickMapName() const { return PickMapName; }
    
protected:
    virtual void BeginPlay() override;

private:
    UFUNCTION(BlueprintCallable)
    void StartPickMap();
    
    UFUNCTION(BlueprintCallable)
    void PickMap(FString MapName);
    
    UFUNCTION(Client, Reliable)
    void ClientPickCharacter(int PlayerNumber, FName CharacterName);

    UFUNCTION(Client, Reliable)
    void ClientStartPickMap();    
    
    UFUNCTION(Client, Reliable)
    void ClientPickMap(const FString& MapName);
    
    UFUNCTION(Server, Reliable)
    void ServerCompleteLoad();
    
    UFUNCTION(Server, Reliable, BlueprintCallable)
    void ServerPickCharacter(FName CharacterName);

private:
    const int32 MaxPlayerCount = 6;
    
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<ULSCharacterPickWidget> CharacterPickWidgetClass;

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<ULSMapPickWidget> MapPickWidgetClass;
    
    TObjectPtr<ULSCharacterPickWidget> CharacterPickWidget;
    TObjectPtr<ULSMapPickWidget> MapPickWidget;
    bool bLoaded;
    FName PickCharacterName;
    FString PickMapName;
};
