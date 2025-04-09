// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnhancedInputComponent.h"
#include "LS_InputBuffer.h"
#include "InputMappingContext.h" 
#include "LS_InputMappingContext.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LASTSTAND_API ULS_InputMappingContext : public UActorComponent
{
	GENERATED_BODY()

public:
    ULS_InputMappingContext();

protected:
    virtual void BeginPlay() override;

public:
    // --- 방향 입력 처리 ---
    UFUNCTION()
    void OnUpDown(const FInputActionValue& Value);

    UFUNCTION()
    void OnLeftRight(const FInputActionValue& Value);

    // --- 버튼 입력 처리 ---
    UFUNCTION()
    void OnAttack(const FInputActionValue& Value);

    UFUNCTION()
    void OnSpecialAttack(const FInputActionValue& Value);

    UFUNCTION()
    void OnShield(const FInputActionValue& Value);

    UFUNCTION()
    void OnJump(const FInputActionValue& Value);

    // --- 도발 입력 처리 ---
    UFUNCTION()
    void OnTaunt1(const FInputActionValue& Value);

    UFUNCTION()
    void OnTaunt2(const FInputActionValue& Value);

    UFUNCTION()
    void OnTaunt3(const FInputActionValue& Value);

    UFUNCTION()
    void OnTaunt4(const FInputActionValue& Value);

    // --- 메뉴 입력 처리 ---
    UFUNCTION()
    void OnMenuBack(const FInputActionValue& Value);

    UFUNCTION()
    void OnMenuSelect(const FInputActionValue& Value);

    UFUNCTION()
    void OnMenuLT(const FInputActionValue& Value);

    UFUNCTION()
    void OnMenuRT(const FInputActionValue& Value);

    UFUNCTION()
    void OnMenuLS(const FInputActionValue& Value);

    UFUNCTION()
    void OnMenuRS(const FInputActionValue& Value);

    UFUNCTION()
    void OnStart(const FInputActionValue& Value);

private:
    ULS_InputBuffer* InputBuffer;

    // --- Input Mapping Context 변수 ---
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
    UInputMappingContext* MappingContext;

    // --- Enhanced Input 액션 바인딩 ---
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Actions", meta = (AllowPrivateAccess = "true"))
    UInputAction* IA_UpDown;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Actions", meta = (AllowPrivateAccess = "true"))
    UInputAction* IA_LeftRight;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Actions", meta = (AllowPrivateAccess = "true"))
    UInputAction* IA_Attack;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Actions", meta = (AllowPrivateAccess = "true"))
    UInputAction* IA_SpecialAttack;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Actions", meta = (AllowPrivateAccess = "true"))
    UInputAction* IA_Shield;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Actions", meta = (AllowPrivateAccess = "true"))
    UInputAction* IA_Jump;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Actions", meta = (AllowPrivateAccess = "true"))
    UInputAction* IA_Taunt1;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Actions", meta = (AllowPrivateAccess = "true"))
    UInputAction* IA_Taunt2;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Actions", meta = (AllowPrivateAccess = "true"))
    UInputAction* IA_Taunt3;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Actions", meta = (AllowPrivateAccess = "true"))
    UInputAction* IA_Taunt4;

    // --- 메뉴 입력 ---
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Actions", meta = (AllowPrivateAccess = "true"))
    UInputAction* IA_MenuBack;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Actions", meta = (AllowPrivateAccess = "true"))
    UInputAction* IA_MenuSelect;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Actions", meta = (AllowPrivateAccess = "true"))
    UInputAction* IA_MenuLT;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Actions", meta = (AllowPrivateAccess = "true"))
    UInputAction* IA_MenuRT;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Actions", meta = (AllowPrivateAccess = "true"))
    UInputAction* IA_MenuLS;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Actions", meta = (AllowPrivateAccess = "true"))
    UInputAction* IA_MenuRS;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Actions", meta = (AllowPrivateAccess = "true"))
    UInputAction* IA_Start;

    // 입력 바인딩 함수
    void BindInput(UEnhancedInputComponent* EnhancedInput);
};