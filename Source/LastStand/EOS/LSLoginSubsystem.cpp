// Fill out your copyright notice in the Description page of Project Settings.


#include "LSLoginSubsystem.h"
#include  "OnlineSubsystemUtils.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineUserInterface.h"

void ULSLoginSubsystem::LoginWithEOS(const FString& UserId, const FString& Token, const FString& LoginType)
{
    IOnlineSubsystem* SubsystemRef = Online::GetSubsystem(GetWorld());

    if(SubsystemRef)
    {
        IOnlineIdentityPtr Identity = SubsystemRef->GetIdentityInterface();
        if (Identity.IsValid())
        {
            FOnlineAccountCredentials Credentials;
            Credentials.Id = UserId;
            Credentials.Token = Token;
            Credentials.Type = LoginType;
            Identity->OnLoginCompleteDelegates->AddUObject(this, &ULSLoginSubsystem::LoginWithEOSComplete);
            Identity->Login(0, Credentials);
        }
    }
}

void ULSLoginSubsystem::GetPlayerUse(const FString& UserId, const FString& Token, const FString& LoginType)
{
    
}

void ULSLoginSubsystem::LoginWithEOSComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId,
                                             const FString& ErrorString)
{
    if (bWasSuccessful)
    {
        UE_LOG(LogTemp, Log, TEXT("Login successful for user: %s"), *UserId.ToString());
    }else
    {
        UE_LOG(LogTemp, Log, TEXT("Login failed: %s"), *ErrorString);
    }
}
