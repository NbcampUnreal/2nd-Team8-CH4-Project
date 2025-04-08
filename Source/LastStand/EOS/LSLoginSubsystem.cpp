// Fill out your copyright notice in the Description page of Project Settings.


#include "LSLoginSubsystem.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystemTypes.h"
#include "Interfaces/OnlineIdentityInterface.h"


void ULSLoginSubsystem::LoginWithEOS(const FString& UserId, const FString& Token, const FString& LoginType)
{
    if(IOnlineSubsystem* SubsystemRef = Online::GetSubsystem(GetWorld()))
    {
        const IOnlineIdentityPtr Identity = SubsystemRef->GetIdentityInterface();
        if (Identity.IsValid())
        {
            FOnlineAccountCredentials Credentials;
            Credentials.Id = UserId;
            Credentials.Token = Token;
            Credentials.Type = LoginType;
            Identity->OnLoginCompleteDelegates->AddUObject(this, &ThisClass::LoginWithEOSComplete);
            Identity->Login(0, Credentials);
        }
    }
}

void ULSLoginSubsystem::GetPlayerUse(const FString& UserId, const FString& Token, const FString& LoginType)
{
    
}

bool ULSLoginSubsystem::GetIsPlayerLogin()
{
    if (IOnlineSubsystem* SubsystemRef = Online::GetSubsystem(GetWorld()))
    {
        const IOnlineIdentityPtr Identity = SubsystemRef->GetIdentityInterface();
        if (Identity.IsValid())
        {
            bool bIsLoggedIn = Identity->GetLoginStatus(0) == ELoginStatus::LoggedIn;
            UE_LOG(LogTemp, Log, TEXT("Is player logged in: %s"), bIsLoggedIn ? TEXT("true") : TEXT("false"));
            return bIsLoggedIn;
        }
    }
    return false;
}

void ULSLoginSubsystem::LoginWithEOSComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId,
                                             const FString& ErrorString)
{
    if (bWasSuccessful)
    {
        UE_LOG(LogTemp, Log, TEXT("Login successful for user: %s"), *UserId.ToString());
        OnEOSLoginComplete.Broadcast();
    }else
    {
        UE_LOG(LogTemp, Log, TEXT("Login failed: %s"), *ErrorString);
    }
}
