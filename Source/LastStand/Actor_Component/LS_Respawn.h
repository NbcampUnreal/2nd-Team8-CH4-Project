// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LS_Respawn.generated.h"

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
    Normal    UMETA(DisplayName = "Normal"),
    Intangible UMETA(DisplayName = "Intangible"),
    Idle      UMETA(DisplayName = "Idle"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LASTSTAND_API ULS_Respawn : public UActorComponent
{
	GENERATED_BODY()

public:
    ULS_Respawn();

    // 서버 리스폰 구현
    UFUNCTION(Server, Reliable, WithValidation)
    void Server_Respawn();
    void Server_Respawn_Implementation();
    bool Server_Respawn_Validate();

protected:
    // 현재 상태
    ECharacterState CurrentState;

    // 무적 상태 시작
    void StartIntangible();

    // 무적 상태 종료
    void EndIntangible();

    // 캐릭터 컨트롤 활성화
    void EnableCharacterControl(ACharacter* Character);

private:
    FTimerHandle IntangibleTimerHandle;
};