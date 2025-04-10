#include "LS_InputBuffer.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"

ULS_InputBuffer::ULS_InputBuffer()
{
    PrimaryComponentTick.bCanEverTick = false;
    BufferedMove = EBufferedMove::None;
    BufferedDirection = EBufferedDirection::None;
}


void ULS_InputBuffer::BufferDirection(EBufferedDirection NewDirection)
{
    BufferedDirection = NewDirection;
    GetWorld()->GetTimerManager().ClearTimer(BufferTimerHandle);
    GetWorld()->GetTimerManager().SetTimer(BufferTimerHandle, this, &ULS_InputBuffer::ResetBuffer, BufferTime, false);
}

void ULS_InputBuffer::BufferMove(EBufferedMove NewMove)
{
    BufferedMove = NewMove;
    GetWorld()->GetTimerManager().ClearTimer(BufferTimerHandle);
    GetWorld()->GetTimerManager().SetTimer(BufferTimerHandle, this, &ULS_InputBuffer::ResetBuffer, BufferTime, false);
}

bool ULS_InputBuffer::ConsumeMove(EBufferedMove MoveToConsume)
{
    if (BufferedMove == MoveToConsume)
    {
        BufferedMove = EBufferedMove::None;
        return true;
    }
    return false;
}

bool ULS_InputBuffer::ConsumeDirection(EBufferedDirection DirectionToConsume)
{
    if (BufferedDirection == DirectionToConsume)
    {
        BufferedDirection = EBufferedDirection::None;
        return true;
    }
    return false;
}

void ULS_InputBuffer::ClearBuffer()
{
    BufferedMove = EBufferedMove::None;
    BufferedDirection = EBufferedDirection::None;
    GetWorld()->GetTimerManager().ClearTimer(BufferTimerHandle);
}

void ULS_InputBuffer::ResetBuffer()
{
    BufferedMove = EBufferedMove::None;
    BufferedDirection = EBufferedDirection::None;
}

void ULS_InputBuffer::HandleInputAction(FName ActionName, FVector2D Direction)
{
    // 방향 처리
    if (Direction != FVector2D::ZeroVector)
    {
        if (FMath::Abs(Direction.Y) > FMath::Abs(Direction.X))
        {
            BufferDirection(Direction.Y > 0 ? EBufferedDirection::Up : EBufferedDirection::Down);
        }
        else
        {
            BufferDirection(Direction.X > 0 ? EBufferedDirection::Right : EBufferedDirection::Left);
        }
    }

    // 액션 이름에 따라 Move 버퍼링
    if (ActionName == "IA_Jump") BufferMove(EBufferedMove::Jump);
    else if (ActionName == "IA_Attack") BufferMove(EBufferedMove::Attack);
    else if (ActionName == "IA_Special") BufferMove(EBufferedMove::Special);
    else if (ActionName == "IA_Shield") BufferMove(EBufferedMove::Shield);
    else if (ActionName == "IA_Taunt1") BufferMove(EBufferedMove::Taunt1);
    else if (ActionName == "IA_Taunt2") BufferMove(EBufferedMove::Taunt2);
    else if (ActionName == "IA_Taunt3") BufferMove(EBufferedMove::Taunt3);
    else if (ActionName == "IA_Taunt4") BufferMove(EBufferedMove::Taunt4);
}