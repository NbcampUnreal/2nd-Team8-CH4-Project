#include "LS_Floor.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ULS_Floor::ULS_Floor()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void ULS_Floor::BeginPlay()
{
    Super::BeginPlay();

    OwnerCharacter = Cast<ACharacter>(GetOwner());
    if (OwnerCharacter)
    {
        MoveComp = OwnerCharacter->GetCharacterMovement();
    }
}

void ULS_Floor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (MoveComp && OwnerCharacter && IceMaterial)
    {
        UpdateSurfaceResponse();
    }
}

void ULS_Floor::UpdateSurfaceResponse()
{
    FVector Start = OwnerCharacter->GetActorLocation();
    FVector End = Start - FVector(0, 0, 100);  // 발밑으로 레이캐스트

    FHitResult Hit;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(OwnerCharacter);

    if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
    {
        UMaterialInterface* Mat = Hit.Component.IsValid() ? Hit.Component->GetMaterial(0) : nullptr;
        UPhysicalMaterial* DetectedPhysMat = Mat ? Mat->GetPhysicalMaterial() : nullptr;

        // 각 물리 머티리얼에 대해 처리할 로직
        if (DetectedPhysMat == IceMaterial)
        {
            HandleIceMaterial();
        }
        else if (DetectedPhysMat == FastMaterial)
        {
            HandleFastMaterial();
        }
        else if (DetectedPhysMat == SlowMaterial)
        {
            HandleSlowMaterial();
        }
        else if (DetectedPhysMat == HighJumpMaterial)
        {
            HandleHighJump();
        }
        else if (DetectedPhysMat == LowJumpMaterial)
        {
            HandleLowJump();
        }
        else if (DetectedPhysMat == TickJumpMaterial)
        {
            HandleTickJump();
        }
        else
        {
            RestoreDefaultValues();
        }
    }
}

void ULS_Floor::RestoreDefaultValues()
{
    MoveComp->GroundFriction = NormalGroundFriction;
    MoveComp->BrakingFrictionFactor = NormalBrakingFrictionFactor;
    MoveComp->BrakingDecelerationWalking = NormalBrakingDeceleration;
    MoveComp->MaxWalkSpeed = NormalSpeed;
    MoveComp->JumpZVelocity = NormalJumpZVelocity;

    UE_LOG(LogTemp, Log, TEXT("No specific material detected. Reverting to default settings."));
}

void ULS_Floor::HandleIceMaterial()
{
    MoveComp->GroundFriction = IceGroundFriction;
    MoveComp->BrakingFrictionFactor = IceBrakingFrictionFactor;
    MoveComp->BrakingDecelerationWalking = IceBrakingDeceleration;
    MoveComp->JumpZVelocity = NormalJumpZVelocity;

    UE_LOG(LogTemp, Log, TEXT("Ice material detected. Applying sliding effect."));
}


void ULS_Floor::HandleFastMaterial()
{
    MoveComp->MaxWalkSpeed = FastSpeed; 

    UE_LOG(LogTemp, Log, TEXT("Fast material detected. Increasing movement speed."));
}


void ULS_Floor::HandleSlowMaterial()
{
    MoveComp->MaxWalkSpeed = SlowSpeed;  
  

    UE_LOG(LogTemp, Log, TEXT("Slow material detected. Decreasing movement speed."));
}


void ULS_Floor::HandleHighJump()
{
    MoveComp->JumpZVelocity = HighJumpZVelocity;  


    UE_LOG(LogTemp, Log, TEXT("High Jump material detected. Increasing jump height."));
}


void ULS_Floor::HandleLowJump()
{
    MoveComp->JumpZVelocity = LowJumpZVelocity;  


    UE_LOG(LogTemp, Log, TEXT("Low Jump material detected. Decreasing jump height."));
}

void ULS_Floor::HandleTickJump()
{
    if (!MoveComp->IsFalling()) 
    {
     
        UE_LOG(LogTemp, Log, TEXT("TickJump material detected. Triggering auto-jump."));
        OwnerCharacter->LaunchCharacter(FVector(0, 0, 1) * TickJumpZVelocity, true, true);  

 
        if (JumpSound)
        {
            UGameplayStatics::PlaySoundAtLocation(this, JumpSound, OwnerCharacter->GetActorLocation());
        }
    }
}