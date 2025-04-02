// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LSCharacterPickPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LASTSTAND_API ALSCharacterPickPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(Client, Reliable)
	void ClientStartPick();
    
    bool IsLoaded() const { return bLoaded; }
    
protected:
	virtual void BeginPlay() override;

private:
    UFUNCTION(Client, Reliable)
    void ClientPickCharacter(int PlayerNumber, FName CharacterName);

    UFUNCTION(Server, Reliable)
    void ServerCompleteLoad();

    UFUNCTION(Server,Reliable)
    void ServerPickCharacter(FName CharacterName);

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> PickWidgetClass;

	TObjectPtr<UUserWidget> PickWidget;
    bool bLoaded;
};
