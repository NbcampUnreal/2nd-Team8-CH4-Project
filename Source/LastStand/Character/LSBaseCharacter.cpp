#include "LSBaseCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

ALSBaseCharacter::ALSBaseCharacter()
{
    PrimaryActorTick.bCanEverTick = false;

    CollisionCylinder = GetCapsuleComponent();

    CollisionCylinder->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    CollisionCylinder->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
    CollisionCylinder->SetCollisionResponseToChannel(ECC_Visibility, ECR_Overlap);
    CollisionCylinder->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

    LedgeDetector = CreateDefaultSubobject<UBoxComponent>(TEXT("LedgeDetector"));
    LedgeDetector->InitBoxExtent(FVector(32.0f, 32.0f, 32.0f));
    LedgeDetector->SetRelativeLocation(FVector(10.0f, 0.0f, 20.0f));
    LedgeDetector->SetRelativeRotation(FRotator(0.00f, 0.0f, 0.0f));
    LedgeDetector->SetRelativeScale3D(FVector(2.0f, 1.0f, 0.25f));
    LedgeDetector->SetupAttachment(RootComponent);

    Push = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Push"));
    Push->InitCapsuleSize(30.0f, 65.0f);
    Push->SetupAttachment(RootComponent);

    Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
    Widget->SetupAttachment(RootComponent);

    static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(
        TEXT("/Script/Engine.SkeletalMesh'/Game/PlatformFighterKit/Assets/Characters/ue4_Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'")
    );

    USkeletalMeshComponent* MeshComp = GetMesh();
    if (MeshAsset.Succeeded())
    {
        MeshComp->SetSkeletalMesh(MeshAsset.Object);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Character SkeletalMesh load failed"));
    }

    // 손, 팔
    HandL = CreateDefaultSubobject<UCapsuleComponent>(TEXT("HandL"));
    HandL->InitCapsuleSize(10.0f, 10.0f);
    HandL->SetRelativeRotation(FRotator(0.0f, 90.0f, 90.0f));
    HandL->SetupAttachment(GetMesh(), TEXT("hand_l"));

    HandR = CreateDefaultSubobject<UCapsuleComponent>(TEXT("HandR"));
    HandR->InitCapsuleSize(10.0f, 10.0f);
    HandR->SetRelativeRotation(FRotator(0.0f, -90.0f, 90.0f));
    HandR->SetupAttachment(GetMesh(), TEXT("hand_r"));

    UpArm_l = CreateDefaultSubobject<UCapsuleComponent>(TEXT("UpArm_l"));
    UpArm_l->InitCapsuleSize(22.0f, 44.0f);
    UpArm_l->SetRelativeLocation(FVector(15.0f, 0.0f, 0.0f));
    UpArm_l->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
    UpArm_l->SetRelativeScale3D(FVector(1.0f, 0.5f, 0.5f));
    UpArm_l->SetupAttachment(GetMesh(), TEXT("upperarm_l"));

    UpArm_r = CreateDefaultSubobject<UCapsuleComponent>(TEXT("UpArm_r"));
    UpArm_r->InitCapsuleSize(22.0f, 44.0f);
    UpArm_r->SetRelativeLocation(FVector(-15.0f, 0.0f, 0.0f));
    UpArm_r->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
    UpArm_r->SetRelativeScale3D(FVector(1.0f, 0.5f, 0.5f));
    UpArm_r->SetupAttachment(GetMesh(), TEXT("upperarm_r"));

    LowArm_l = CreateDefaultSubobject<UCapsuleComponent>(TEXT("LowArm_l"));
    LowArm_l->InitCapsuleSize(22.0f, 44.0f);
    LowArm_l->SetRelativeLocation(FVector(15.0f, 0.0f, 0.0f));
    LowArm_l->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
    LowArm_l->SetRelativeScale3D(FVector(1.0f, 0.4f, 0.5f));
    LowArm_l->SetupAttachment(GetMesh(), TEXT("lowerarm_l"));

    LowArm_r = CreateDefaultSubobject<UCapsuleComponent>(TEXT("LowArm_r"));
    LowArm_r->InitCapsuleSize(22.0f, 44.0f);
    LowArm_r->SetRelativeLocation(FVector(-15.0f, 0.0f, 0.0f));
    LowArm_r->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
    LowArm_r->SetRelativeScale3D(FVector(1.0f, 0.4f, 0.5f));
    LowArm_r->SetupAttachment(GetMesh(), TEXT("lowerarm_r"));

    // 다리, 발
    FootL = CreateDefaultSubobject<UCapsuleComponent>(TEXT("FootL"));
    FootL->InitCapsuleSize(15.0f, 15.0f);
    FootL->SetRelativeRotation(FRotator(0.0f, 90.0f, -90.0f));
    FootL->SetupAttachment(GetMesh(), TEXT("foot_l"));

    FootR = CreateDefaultSubobject<UCapsuleComponent>(TEXT("FootR"));
    FootR->InitCapsuleSize(15.0f, 15.0f);
    FootR->SetRelativeRotation(FRotator(0.0f, -90.0f, -90.0f));
    FootR->SetupAttachment(GetMesh(), TEXT("foot_r"));

    UpLeg_l = CreateDefaultSubobject<UCapsuleComponent>(TEXT("UpLeg_l"));
    UpLeg_l->InitCapsuleSize(22.0f, 44.0f);
    UpLeg_l->SetRelativeLocation(FVector(-20.0f, 0.0f, 0.0f));
    UpLeg_l->SetRelativeRotation(FRotator(0.0f, 90.0f, -90.0f));
    UpLeg_l->SetRelativeScale3D(FVector(1.0f, 0.5f, 0.5f));
    UpLeg_l->SetupAttachment(GetMesh(), TEXT("thigh_l"));

    UpLeg_r = CreateDefaultSubobject<UCapsuleComponent>(TEXT("UpLeg_r"));
    UpLeg_r->InitCapsuleSize(22.0f, 44.0f);
    UpLeg_r->SetRelativeLocation(FVector(20.0f, 0.0f, 0.0f));
    UpLeg_r->SetRelativeRotation(FRotator(0.0f, -90.0f, -90.0f));
    UpLeg_r->SetRelativeScale3D(FVector(1.0f, 0.5f, 0.5f));
    UpLeg_r->SetupAttachment(GetMesh(), TEXT("thigh_r"));

    LowLeg_l = CreateDefaultSubobject<UCapsuleComponent>(TEXT("LowLeg_l"));
    LowLeg_l->InitCapsuleSize(22.0f, 44.0f);
    LowLeg_l->SetRelativeLocation(FVector(-20.0f, 0.0f, 0.0f));
    LowLeg_l->SetRelativeRotation(FRotator(0.0f, 90.0f, -90.0f));
    LowLeg_l->SetRelativeScale3D(FVector(1.0f, 0.5f, 0.5f));
    LowLeg_l->SetupAttachment(GetMesh(), TEXT("calf_l"));

    LowLeg_r = CreateDefaultSubobject<UCapsuleComponent>(TEXT("LowLeg_r"));
    LowLeg_r->InitCapsuleSize(22.0f, 44.0f);
    LowLeg_r->SetRelativeLocation(FVector(20.0f, 0.0f, 0.0f));
    LowLeg_r->SetRelativeRotation(FRotator(0.0f, -90.0f, -90.0f));
    LowLeg_r->SetRelativeScale3D(FVector(1.0f, 0.5f, 0.5f));
    LowLeg_r->SetupAttachment(GetMesh(), TEXT("calf_r"));

    // 머리 & 몸통
    Head = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Head"));
    Head->InitCapsuleSize(15.0f, 15.0f);
    Head->SetRelativeRotation(FRotator(0.0f, 90.0f, -90.0f));
    Head->SetupAttachment(GetMesh(), TEXT("head"));

    Torso = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Torso"));
    Torso->InitCapsuleSize(20.0f, 40.0f);
    Torso->SetRelativeLocation(FVector(10.0f, 0.0f, 0.0f));
    Torso->SetRelativeRotation(FRotator(0.0f, 90.0f, -90.0f));
    Torso->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
    Torso->SetupAttachment(GetMesh(), TEXT("spine_01"));
}

void ALSBaseCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void ALSBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ALSBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}
