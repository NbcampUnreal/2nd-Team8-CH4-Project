// Fill out your copyright notice in the Description page of Project Settings.


#include "LSBaseGameSession.h"
#include "LSSessionSubsystem.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystemTypes.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlineStatsInterface.h"


ALSBaseGameSession::ALSBaseGameSession()
{
    PrimaryActorTick.bCanEverTick = false;

    NumberOfPlayersInSession = 0;
    MaxNumberOfPlayersInSession = 6;
}

bool ALSBaseGameSession::ProcessAutoLogin()
{
    return true;
}

FString ALSBaseGameSession::ApproveLogin(const FString& Options)
{
    if (IsRunningDedicatedServer())
    {
        Super::ApproveLogin(Options);
        return NumberOfPlayersInSession == MaxNumberOfPlayersInSession ? "FULL" : "";
    }
    else
    {
        return "";
    }
}

void ALSBaseGameSession::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
    DestroySession(); 
}

void ALSBaseGameSession::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);
    NumberOfPlayersInSession++;
}

void ALSBaseGameSession::NotifyLogout(const APlayerController* ExitingPlayer)
{
    Super::NotifyLogout(ExitingPlayer);
    
    NumberOfPlayersInSession--; 
    
    if (NumberOfPlayersInSession==0)
    {
        IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
        IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

        if (Session->GetSessionState(SessionName) == EOnlineSessionState::InProgress)
        {
            EndSession();
        }        
    }
    
}

void ALSBaseGameSession::CreateSession(FName KeyName, FString KeyValue)
{
    IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    IOnlineSessionPtr Session = Subsystem->GetSessionInterface();
    
    CreateSessionDelegateHandle =
        Session->AddOnCreateSessionCompleteDelegate_Handle(FOnCreateSessionCompleteDelegate::CreateUObject(
            this,
            &ThisClass::HandleCreateSessionCompleted));
    
    TSharedRef<FOnlineSessionSettings> SessionSettings = MakeShared<FOnlineSessionSettings>();
    SessionSettings->NumPublicConnections = 2; //We will test our sessions with 2 players to keep things simple
    SessionSettings->bShouldAdvertise = true; //This creates a public match and will be searchable.
    SessionSettings->bUsesPresence = false;   //No presence on dedicated server. This requires a local user.
    SessionSettings->bAllowJoinViaPresence = false;
    SessionSettings->bAllowJoinViaPresenceFriendsOnly = false;
    SessionSettings->bAllowInvites = false;    //Allow inviting players into session. This requires presence and a local user. 
    SessionSettings->bAllowJoinInProgress = false; //Once the session is started, no one can join.
    SessionSettings->bIsDedicated = false; //Session created on dedicated server.
    SessionSettings->bUseLobbiesIfAvailable = true; //For P2P we will use a lobby instead of a session
    SessionSettings->bUseLobbiesVoiceChatIfAvailable = true; //We will also enable voice
    SessionSettings->bUsesStats = true; //Needed to keep track of player stats.
    
    SessionSettings->Settings.Add(KeyName, FOnlineSessionSetting((KeyValue), EOnlineDataAdvertisementType::ViaOnlineService));

    UE_LOG(LogTemp, Log, TEXT("Creating session..."));
    
    if (!Session->CreateSession(0, SessionName, *SessionSettings))
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to create session!"));
    }
}

void ALSBaseGameSession::HandleCreateSessionCompleted(FName EOSSessionName, bool bWasSuccessful)
{
    IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

    if (bWasSuccessful)
    {
        bIsSessionExists = true; 
        UE_LOG(LogTemp, Log, TEXT("Session: %s Created!"), *EOSSessionName.ToString());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to create session!"));
    }

    Session->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionDelegateHandle);
    CreateSessionDelegateHandle.Reset();
}

void ALSBaseGameSession::RegisterPlayer(APlayerController* NewPlayer, const FUniqueNetIdRepl& UniqueId, bool bWasFromInvite)
{
    Super::RegisterPlayer(NewPlayer, UniqueId, bWasFromInvite);

    IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

    RegisterPlayerDelegateHandle =
        Session->AddOnRegisterPlayersCompleteDelegate_Handle(FOnRegisterPlayersCompleteDelegate::CreateUObject(
            this,
            &ThisClass::HandleRegisterPlayerCompleted));

    if (!Session->RegisterPlayer(SessionName, *UniqueId, false))
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to Register Player!"));
        Session->ClearOnRegisterPlayersCompleteDelegate_Handle(RegisterPlayerDelegateHandle);
        RegisterPlayerDelegateHandle.Reset();
    }
    
}

void ALSBaseGameSession::HandleRegisterPlayerCompleted(FName EOSSessionName, const TArray<FUniqueNetIdRef>& PlayerIds, bool bWasSuccesful)
{
    IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

    if (bWasSuccesful)
    {
        UE_LOG(LogTemp, Log, TEXT("Player registered in EOS Session!"));
        if (NumberOfPlayersInSession == MaxNumberOfPlayersInSession)
        {
            StartSession();
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to register player! (From Callback)"));
    }
    
    Session->ClearOnRegisterPlayersCompleteDelegate_Handle(RegisterPlayerDelegateHandle);
    RegisterPlayerDelegateHandle.Reset();
}

void ALSBaseGameSession::UnregisterPlayer(const APlayerController* ExitingPlayer)
{
    Super::UnregisterPlayer(ExitingPlayer);
    
    IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface(); 
    IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

    if (ExitingPlayer->PlayerState) 
    {
        UnregisterPlayerDelegateHandle =
            Session->AddOnUnregisterPlayersCompleteDelegate_Handle(FOnUnregisterPlayersCompleteDelegate::CreateUObject(
                this,
                &ThisClass::HandleUnregisterPlayerCompleted));

        if (!Session->UnregisterPlayer(SessionName, *ExitingPlayer->PlayerState->GetUniqueId()))
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to Unregister Player!"));
            Session->ClearOnUnregisterPlayersCompleteDelegate_Handle(UnregisterPlayerDelegateHandle);
            UnregisterPlayerDelegateHandle.Reset();
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to Unregister Player!"));
    }

    
}

void ALSBaseGameSession::HandleUnregisterPlayerCompleted(FName EOSSessionName, const TArray<FUniqueNetIdRef>& PlayerIds, bool bWasSuccesful)
{

    IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

    if (bWasSuccesful)
    {
        UE_LOG(LogTemp, Log, TEXT("Player unregistered in EOS Session!"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to unregister player! (From Callback)"));
    }
    Session->ClearOnUnregisterPlayersCompleteDelegate_Handle(UnregisterPlayerDelegateHandle);
    UnregisterPlayerDelegateHandle.Reset();
}

void ALSBaseGameSession::StartSession()
{
    IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

    StartSessionDelegateHandle =
        Session->AddOnStartSessionCompleteDelegate_Handle(FOnStartSessionCompleteDelegate::CreateUObject(
            this,
            &ThisClass::HandleStartSessionCompleted)); 
    
    if (!Session->StartSession(SessionName))
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to start session!"));
        Session->ClearOnStartSessionCompleteDelegate_Handle(StartSessionDelegateHandle);
        StartSessionDelegateHandle.Reset();
    }
}

void ALSBaseGameSession::HandleStartSessionCompleted(FName EOSSessionName, bool bWasSuccessful)
{
    IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

    if (bWasSuccessful)
    {
        UE_LOG(LogTemp, Log, TEXT("Session Started!"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to start session! (From Callback)"));
    }

    Session->ClearOnStartSessionCompleteDelegate_Handle(StartSessionDelegateHandle);
    StartSessionDelegateHandle.Reset();
}

void ALSBaseGameSession::EndSession()
{
    IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

    EndSessionDelegateHandle =
        Session->AddOnEndSessionCompleteDelegate_Handle(FOnEndSessionCompleteDelegate::CreateUObject(
            this,
            &ThisClass::HandleEndSessionCompleted));

    if (!Session->EndSession(SessionName))
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to end session!"));
        Session->ClearOnEndSessionCompleteDelegate_Handle(EndSessionDelegateHandle);
        EndSessionDelegateHandle.Reset();
    }
}

void ALSBaseGameSession::HandleEndSessionCompleted(FName EOSSessionName, bool bWasSuccessful)
{
    IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

    if (bWasSuccessful)
    {
        UE_LOG(LogTemp, Log, TEXT("Session ended!"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to end session! (From Callback)"));
    }

    Session->ClearOnEndSessionCompleteDelegate_Handle(EndSessionDelegateHandle);
    EndSessionDelegateHandle.Reset();
}



void ALSBaseGameSession::DestroySession()
{
    IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

    DestroySessionDelegateHandle =
        Session->AddOnDestroySessionCompleteDelegate_Handle(FOnDestroySessionCompleteDelegate::CreateUObject(
            this,
            &ThisClass::HandleDestroySessionCompleted));

    if (!Session->DestroySession(SessionName))
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to destroy session.")); 
        Session->ClearOnDestroySessionCompleteDelegate_Handle(DestroySessionDelegateHandle);
        DestroySessionDelegateHandle.Reset();
    }
}

void ALSBaseGameSession::HandleDestroySessionCompleted(FName EOSSessionName, bool bWasSuccesful)
{

    IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

    if (bWasSuccesful)
    {
        bIsSessionExists = false;
        UE_LOG(LogTemp, Log, TEXT("Destroyed session succesfully.")); 
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to destroy session.")); 
    }

    Session->ClearOnDestroySessionCompleteDelegate_Handle(DestroySessionDelegateHandle);
    DestroySessionDelegateHandle.Reset();
}

