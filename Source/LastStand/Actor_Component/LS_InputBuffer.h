#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LS_InputBuffer.generated.h"


UENUM(BlueprintType)
enum class EBufferedDirection : uint8
{
    None UMETA(DisplayName = "None"),
    Up UMETA(DisplayName = "Up"),
    Down UMETA(DisplayName = "Down"),
    Left UMETA(DisplayName = "Left"),
    Right UMETA(DisplayName = "Right")
};


UENUM(BlueprintType)
enum class EBufferedMove : uint8
{
    None UMETA(DisplayName = "None"),
    Attack UMETA(DisplayName = "Attack"),
    Special UMETA(DisplayName = "Special"),
    Shield UMETA(DisplayName = "Shield"),
    Jump UMETA(DisplayName = "Jump"),
    Taunt1 UMETA(DisplayName = "Taunt1"),
    Taunt2 UMETA(DisplayName = "Taunt2"),
    Taunt3 UMETA(DisplayName = "Taunt3"),
    Taunt4 UMETA(DisplayName = "Taunt4")
};
DECLARE_DELEGATE(FOnMoveConsumed);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LASTSTAND_API ULS_InputBuffer : public UActorComponent
{
    GENERATED_BODY()


public:
    // Constructor
    ULS_InputBuffer();

public:
    // Buffer Direction
    void BufferDirection(EBufferedDirection NewDirection);

    // Buffer Move
    void BufferMove(EBufferedMove NewMove);

    // Consume a Move
    bool ConsumeMove(EBufferedMove MoveToConsume);

    // Consume a Direction
    bool ConsumeDirection(EBufferedDirection DirectionToConsume);

    // Clear the buffer
    void ClearBuffer();

    // Reset the buffer after a certain time
    void ResetBuffer();

    // Enhanced Input action handling
    void HandleInputAction(FName ActionName, FVector2D Direction);

    // Timer for resetting buffer
    FTimerHandle BufferTimerHandle;

    // Buffered direction and move
    EBufferedDirection BufferedDirection;
    EBufferedMove BufferedMove;

    // Buffer time duration in seconds
    UPROPERTY(EditAnywhere, Category = "InputBuffer")
    float BufferTime = 0.5f;
};