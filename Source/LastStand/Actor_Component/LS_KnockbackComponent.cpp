#include "LS_KnockbackComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

ULS_KnockbackComponent::ULS_KnockbackComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void ULS_KnockbackComponent::ApplyKnockback(FVector SourceLocation, float Strength, float VerticalBoost)
{
    ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
    if (!OwnerCharacter) return;

    FVector Direction = (OwnerCharacter->GetActorLocation() - SourceLocation).GetSafeNormal();


    Direction.Z += VerticalBoost + 1.2f;
    Direction.Normalize();

    UCharacterMovementComponent* MoveComp = OwnerCharacter->GetCharacterMovement();
    if (MoveComp)
    {
      
        MoveComp->GroundFriction = 0.0f;
        MoveComp->BrakingFrictionFactor = 0.0f;
        MoveComp->BrakingDecelerationWalking = 0.0f;

        if (MoveComp->IsFalling())
        {
            MoveComp->Velocity = Direction * Strength;
        }
        else
        {
            MoveComp->SetMovementMode(MOVE_Walking);
            OwnerCharacter->LaunchCharacter(Direction * Strength, true, true);
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("[Knockback] 적용됨! Direction: %s, Strength: %.1f"), *Direction.ToString(), Strength);
}