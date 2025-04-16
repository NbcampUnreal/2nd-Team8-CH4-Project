#include "LS_Button.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "LS_ObjectSpawnBox.h"

ALS_Button::ALS_Button()
{
    PrimaryActorTick.bCanEverTick = false;

    Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
    RootComponent = Cube;

    Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
    Box->SetupAttachment(RootComponent);
    Box->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);  // 충돌 설정 변경
    Box->SetCollisionResponseToAllChannels(ECR_Overlap);
}

void ALS_Button::BeginPlay()
{
    Super::BeginPlay();

    Box->OnComponentBeginOverlap.AddDynamic(this, &ALS_Button::OnBeginOverlap);

    if (UnpressedMesh)
    {
        Cube->SetStaticMesh(UnpressedMesh);
    }
}

void ALS_Button::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (!bActivated && OtherActor && OtherActor != this)
    {
        UE_LOG(LogTemp, Log, TEXT("OnBeginOverlap Triggered!"));
        ActivateButton();
    }
}

void ALS_Button::ActivateButton()
{
    bActivated = true;

    // 버튼이 눌렸을 때 로그 출력
    UE_LOG(LogTemp, Log, TEXT("Button Pressed!"));

    if (ActivateSound)
    {
        float RandomPitch = FMath::FRandRange(0.95f, 1.05f); // 피치 랜덤화로 중복 재생 방지
        UGameplayStatics::PlaySoundAtLocation(this, ActivateSound, GetActorLocation(), 1.0f, RandomPitch);
    }

    if (PressedMesh)
    {
        Cube->SetStaticMesh(PressedMesh);
    }

    Box->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    SnowballSpawnCount = 0;

    // SnowballClass와 SpawnBoxRef가 유효한지 체크
    if (!SnowballClass || !SpawnBoxRef)
    {
        UE_LOG(LogTemp, Warning, TEXT("SnowballClass or SpawnBoxRef is NULL"));
        return;
    }

    // 타이머가 정상적으로 설정되는지 확인
    UE_LOG(LogTemp, Log, TEXT("Timer started for spawning snowballs"));
    GetWorld()->GetTimerManager().SetTimer(
        SpawnTimerHandle,
        this,
        &ALS_Button::SpawnSnowballStep,
        SpawnInterval,
        true
    );
}

void ALS_Button::SpawnSnowballStep()
{
    // 타이머가 호출되었는지 확인
    UE_LOG(LogTemp, Log, TEXT("SpawnSnowballStep triggered"));

    if (!SnowballClass || !SpawnBoxRef) return;

    UBoxComponent* BoxComp = SpawnBoxRef->SpawnBox;
    if (!BoxComp) return;

    FVector Origin = BoxComp->GetComponentLocation();
    FVector Extent = BoxComp->GetScaledBoxExtent();

    FVector RandomOffset = FVector(
        FMath::FRandRange(-Extent.X, Extent.X),
        FMath::FRandRange(-Extent.Y, Extent.Y),
        FMath::FRandRange(-Extent.Z, Extent.Z)
    );

    FVector SpawnLocation = Origin + RandomOffset;
    FRotator SpawnRotation = FRotator::ZeroRotator;

    GetWorld()->SpawnActor<AActor>(SnowballClass, SpawnLocation, SpawnRotation);

    SnowballSpawnCount++;

    if (SnowballSpawnCount >= TotalSnowballsToSpawn)
    {
        GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
    }
}
