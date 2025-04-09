#include "LS_Respawn.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"

ULS_Respawn::ULS_Respawn()
{
   
    PrimaryComponentTick.bCanEverTick = false;
    CurrentState = ECharacterState::Normal;
}

void ULS_Respawn::Server_Respawn_Implementation()
{
    // 리스폰 시 캐릭터의 위치 및 회전 초기화
    if (ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner()))
    {
        OwnerCharacter->SetActorLocation(FVector(0.f, 0.f, 300.f));
        OwnerCharacter->SetActorRotation(FRotator::ZeroRotator);

       
        StartIntangible();

        
        FTimerHandle RespawnDelayHandle;
        OwnerCharacter->GetWorldTimerManager().SetTimer(RespawnDelayHandle, [this, OwnerCharacter]() {
            CurrentState = ECharacterState::Idle;
            EnableCharacterControl(OwnerCharacter);
            }, 1.0f, false);
    }
}

bool ULS_Respawn::Server_Respawn_Validate()
{
    return true;
}

void ULS_Respawn::StartIntangible()
{
 
    CurrentState = ECharacterState::Intangible;

   
    GetWorld()->GetTimerManager().SetTimer(IntangibleTimerHandle, this, &ULS_Respawn::EndIntangible, 7.0f, false);
}

void ULS_Respawn::EndIntangible()
{
    CurrentState = ECharacterState::Normal;
}

void ULS_Respawn::EnableCharacterControl(ACharacter* Character)
{
    if (!Character) return;
    Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}