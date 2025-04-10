// Fill out your copyright notice in the Description page of Project Settings.
#include "LS_InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "LS_InputBuffer.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"

ULS_InputMappingContext::ULS_InputMappingContext()
{
    PrimaryComponentTick.bCanEverTick = false;
    InputBuffer = nullptr;
}

void ULS_InputMappingContext::BeginPlay()
{
    Super::BeginPlay();

    // 타이머를 사용해서 초기화 지연 실행
    GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ULS_InputMappingContext::InitializeInput);
}

void ULS_InputMappingContext::InitializeInput()
{
    ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
    if (!OwnerCharacter)
    {
        UE_LOG(LogTemp, Error, TEXT("[ULS_InputMappingContext] OwnerCharacter is null (InitializeInput)"));
        return;
    }

    APlayerController* PC = Cast<APlayerController>(OwnerCharacter->GetController());
    if (!PC)
    {
        UE_LOG(LogTemp, Error, TEXT("[ULS_InputMappingContext] PlayerController is null (InitializeInput)"));
        return;
    }

    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
    {
        if (MappingContext)
        {
            UE_LOG(LogTemp, Warning, TEXT("[ULS_InputMappingContext] AddMappingContext: %s"), *MappingContext->GetName());
            Subsystem->AddMappingContext(MappingContext, 0);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("[ULS_InputMappingContext] MappingContext is null"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("[ULS_InputMappingContext] Subsystem is null"));
    }

    InputBuffer = OwnerCharacter->FindComponentByClass<ULS_InputBuffer>();
    if (!InputBuffer)
    {
        UE_LOG(LogTemp, Error, TEXT("[ULS_InputMappingContext] InputBuffer is null (InitializeInput)"));
    }

    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(OwnerCharacter->InputComponent))
    {
        UE_LOG(LogTemp, Warning, TEXT("[ULS_InputMappingContext] EnhancedInputComponent is valid (InitializeInput)"));
        BindInput(EnhancedInput);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("[ULS_InputMappingContext] EnhancedInputComponent is null"));
    }
}

void ULS_InputMappingContext::BindInput(UEnhancedInputComponent* EnhancedInput)
{
    if (!EnhancedInput) return;

    if (IA_UpDown)
        EnhancedInput->BindAction(IA_UpDown, ETriggerEvent::Triggered, this, &ULS_InputMappingContext::OnUpDown);

    if (IA_LeftRight)
        EnhancedInput->BindAction(IA_LeftRight, ETriggerEvent::Triggered, this, &ULS_InputMappingContext::OnLeftRight);

    if (IA_Attack)
        EnhancedInput->BindAction(IA_Attack, ETriggerEvent::Started, this, &ULS_InputMappingContext::OnAttack);

    if (IA_SpecialAttack)
        EnhancedInput->BindAction(IA_SpecialAttack, ETriggerEvent::Started, this, &ULS_InputMappingContext::OnSpecialAttack);

    if (IA_Shield)
        EnhancedInput->BindAction(IA_Shield, ETriggerEvent::Started, this, &ULS_InputMappingContext::OnShield);

    if (IA_Jump)
        EnhancedInput->BindAction(IA_Jump, ETriggerEvent::Started, this, &ULS_InputMappingContext::OnJump);

    if (IA_Taunt1)
        EnhancedInput->BindAction(IA_Taunt1, ETriggerEvent::Started, this, &ULS_InputMappingContext::OnTaunt1);

    if (IA_Taunt2)
        EnhancedInput->BindAction(IA_Taunt2, ETriggerEvent::Started, this, &ULS_InputMappingContext::OnTaunt2);

    if (IA_Taunt3)
        EnhancedInput->BindAction(IA_Taunt3, ETriggerEvent::Started, this, &ULS_InputMappingContext::OnTaunt3);

    if (IA_Taunt4)
        EnhancedInput->BindAction(IA_Taunt4, ETriggerEvent::Started, this, &ULS_InputMappingContext::OnTaunt4);

    // 메뉴 입력 처리
    if (IA_MenuBack)
        EnhancedInput->BindAction(IA_MenuBack, ETriggerEvent::Started, this, &ULS_InputMappingContext::OnMenuBack);

    if (IA_MenuSelect)
        EnhancedInput->BindAction(IA_MenuSelect, ETriggerEvent::Started, this, &ULS_InputMappingContext::OnMenuSelect);

    if (IA_MenuLT)
        EnhancedInput->BindAction(IA_MenuLT, ETriggerEvent::Started, this, &ULS_InputMappingContext::OnMenuLT);

    if (IA_MenuRT)
        EnhancedInput->BindAction(IA_MenuRT, ETriggerEvent::Started, this, &ULS_InputMappingContext::OnMenuRT);

    if (IA_MenuLS)
        EnhancedInput->BindAction(IA_MenuLS, ETriggerEvent::Triggered, this, &ULS_InputMappingContext::OnMenuLS);

    if (IA_MenuRS)
        EnhancedInput->BindAction(IA_MenuRS, ETriggerEvent::Triggered, this, &ULS_InputMappingContext::OnMenuRS);

    if (IA_Start)
        EnhancedInput->BindAction(IA_Start, ETriggerEvent::Started, this, &ULS_InputMappingContext::OnStart);
}

// --- 방향 입력 처리 ---

void ULS_InputMappingContext::OnUpDown(const FInputActionValue& Value)
{
    if (!InputBuffer) return;

    const float Y = Value.Get<float>();
    if (Y > 0.5f)
        InputBuffer->BufferDirection(EBufferedDirection::Up);
    else if (Y < -0.5f)
        InputBuffer->BufferDirection(EBufferedDirection::Down);
}

void ULS_InputMappingContext::OnLeftRight(const FInputActionValue& Value)
{
    UE_LOG(LogTemp, Warning, TEXT(">>> OnLeftRight Triggered"));

    if (!InputBuffer)
    {
        UE_LOG(LogTemp, Error, TEXT("InputBuffer is null in OnLeftRight"));
        return;
    }

    const float X = Value.Get<float>();
    UE_LOG(LogTemp, Warning, TEXT("LeftRight Axis Value: %f"), X);

    if (X > 0.5f)
        InputBuffer->BufferDirection(EBufferedDirection::Right);
    else if (X < -0.5f)
        InputBuffer->BufferDirection(EBufferedDirection::Left);
}

// --- 버튼 입력 처리 ---

void ULS_InputMappingContext::OnAttack(const FInputActionValue& Value)
{
    if (InputBuffer)
        InputBuffer->BufferMove(EBufferedMove::Attack);
}

void ULS_InputMappingContext::OnSpecialAttack(const FInputActionValue& Value)
{
    if (InputBuffer)
        InputBuffer->BufferMove(EBufferedMove::Special);
}

void ULS_InputMappingContext::OnShield(const FInputActionValue& Value)
{
    if (InputBuffer)
        InputBuffer->BufferMove(EBufferedMove::Shield);
}

void ULS_InputMappingContext::OnJump(const FInputActionValue& Value)
{
    if (InputBuffer)
        InputBuffer->BufferMove(EBufferedMove::Jump);
}

// --- 도발 입력 처리 ---

void ULS_InputMappingContext::OnTaunt1(const FInputActionValue& Value)
{
    UE_LOG(LogTemp, Log, TEXT("Taunt 1"));
}

void ULS_InputMappingContext::OnTaunt2(const FInputActionValue& Value)
{
    UE_LOG(LogTemp, Log, TEXT("Taunt 2"));
}

void ULS_InputMappingContext::OnTaunt3(const FInputActionValue& Value)
{
    UE_LOG(LogTemp, Log, TEXT("Taunt 3"));
}

void ULS_InputMappingContext::OnTaunt4(const FInputActionValue& Value)
{
    UE_LOG(LogTemp, Log, TEXT("Taunt 4"));
}

// --- 메뉴 입력 처리 ---

void ULS_InputMappingContext::OnMenuBack(const FInputActionValue& Value)
{
    UE_LOG(LogTemp, Log, TEXT("MenuBack Pressed"));
}

void ULS_InputMappingContext::OnMenuSelect(const FInputActionValue& Value)
{
    UE_LOG(LogTemp, Log, TEXT("MenuSelect Pressed"));
}

void ULS_InputMappingContext::OnMenuLT(const FInputActionValue& Value)
{
    UE_LOG(LogTemp, Log, TEXT("MenuLT Pressed"));
}

void ULS_InputMappingContext::OnMenuRT(const FInputActionValue& Value)
{
    UE_LOG(LogTemp, Log, TEXT("MenuRT Pressed"));
}

void ULS_InputMappingContext::OnMenuLS(const FInputActionValue& Value)
{
    UE_LOG(LogTemp, Log, TEXT("MenuLS Axis: %f"), Value.Get<float>());
}

void ULS_InputMappingContext::OnMenuRS(const FInputActionValue& Value)
{
    UE_LOG(LogTemp, Log, TEXT("MenuRS Axis: %f"), Value.Get<float>());
}

void ULS_InputMappingContext::OnStart(const FInputActionValue& Value)
{
    UE_LOG(LogTemp, Log, TEXT("Start Pressed"));
}
