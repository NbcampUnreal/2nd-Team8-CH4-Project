// Fill out your copyright notice in the Description page of Project Settings.


#include "LSSessionSubsystem.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystemTypes.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "Kismet/GameplayStatics.h"

void ULSSessionSubsystem::FindMatchmakingSession()
{
    IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    IOnlineSessionPtr Session = Subsystem->GetSessionInterface();
    TSharedRef<FOnlineSessionSearch> Search = MakeShared<FOnlineSessionSearch>();

    Search->QuerySettings.SearchParams.Empty();
    Search->QuerySettings.Set(FName("Matchmaking"), FString("MatchmakingSession"), EOnlineComparisonOp::Equals);
#if P2PMODE
    Search->QuerySettings.Set(SEARCH_LOBBIES, true, EOnlineComparisonOp::Equals);
#endif
    FindMatchmakingSessionsDelegateHandle =
        Session->AddOnFindSessionsCompleteDelegate_Handle(FOnFindSessionsCompleteDelegate::CreateUObject(
            this,
            &ThisClass::HandleFindMatchmakingSessionsComplete,
            Search));
    

    UE_LOG(LogTemp, Log, TEXT("Finding matchmaking session."));
    
    if (!Session->FindSessions(0, Search))
    {
        UE_LOG(LogTemp, Warning, TEXT("Finding session failed."));
        Session->ClearOnFindSessionsCompleteDelegate_Handle(FindMatchmakingSessionsDelegateHandle);
        FindMatchmakingSessionsDelegateHandle.Reset();
    }
}

void ULSSessionSubsystem::HandleFindMatchmakingSessionsComplete(bool bWasSuccessful, TSharedRef<FOnlineSessionSearch> Search)
{
    IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    if (bWasSuccessful)
    {
        if (IOnlineSessionPtr SessionPtr = Online::GetSessionInterface(GetWorld()))
        {
            if (Search->SearchResults.Num() > 0)
            {
                for (auto SessionInSearchResult : Search->SearchResults)
                {
                    FString ConnectString;
                    if (SessionPtr->GetResolvedConnectString(SessionInSearchResult, NAME_GamePort, ConnectString))
                    {
                        SessionToJoin = &SessionInSearchResult;
                        FString OwnerIP = SessionInSearchResult.Session.OwningUserId->ToString();
                        UE_LOG(LogTemp, Log, TEXT("Session Owner IP: %s"), *OwnerIP);
                    }
                    break;
                }
                JoinSession("MatchmakingSession");
            }else
            {
                UGameplayStatics::OpenLevel(GetWorld(), FName("EOSMatchmakingTestMap"), true, L"Listen");
            }
        }
    }else
    {
        UGameplayStatics::OpenLevel(GetWorld(), FName("EOSMatchmakingTestMap"), true, L"Listen");
    }
}

void ULSSessionSubsystem::FindCustomSession(const FString SessionName)
{
    IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    IOnlineSessionPtr Session = Subsystem->GetSessionInterface();
    TSharedRef<FOnlineSessionSearch> Search = MakeShared<FOnlineSessionSearch>();

    Search->QuerySettings.SearchParams.Empty();

    Search->QuerySettings.Set(FName("Custom"), SessionName, EOnlineComparisonOp::In);

    FindCustomSessionsDelegateHandle =
        Session->AddOnFindSessionsCompleteDelegate_Handle(FOnFindSessionsCompleteDelegate::CreateUObject(
            this,
            &ThisClass::HandleFindCustomSessionsComplete,
            Search));
    
    UE_LOG(LogTemp, Log, TEXT("Finding custom session."));
    
    if (!Session->FindSessions(0, Search))
    {
        UE_LOG(LogTemp, Warning, TEXT("Finding custom failed."));
        Session->ClearOnFindSessionsCompleteDelegate_Handle(FindCustomSessionsDelegateHandle);
        FindCustomSessionsDelegateHandle.Reset();
    }
}

void ULSSessionSubsystem::HandleFindCustomSessionsComplete(bool bWasSuccessful, TSharedRef<FOnlineSessionSearch> Search)
{
    if (bWasSuccessful)
    {
        if (IOnlineSessionPtr SessionPtr = Online::GetSessionInterface(GetWorld()))
        {
            if (Search->SearchResults.Num() > 0)
            {
                UE_LOG(LogTemp, Log, TEXT("세션을 찾았습니다."));
                OnEOSSessionSearchComplete.Broadcast(Search);
                JoinSession("CustomSession");
            }
        }
    }

    IOnlineSessionPtr Session = Online::GetSessionInterface(GetWorld());
    if (Session.IsValid())
    {
        Session->ClearOnFindSessionsCompleteDelegate_Handle(FindMatchmakingSessionsDelegateHandle);
        FindMatchmakingSessionsDelegateHandle.Reset();
    }
}

void ULSSessionSubsystem::JoinSession(const FName SessionName)
{
    IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

    JoinSessionDelegateHandle = 
        Session->AddOnJoinSessionCompleteDelegate_Handle(FOnJoinSessionCompleteDelegate::CreateUObject(
            this,
            &ThisClass::HandleJoinSessionComplete));

    UE_LOG(LogTemp, Log, TEXT("Joining session."));
    if (!Session->JoinSession(0, SessionName, *SessionToJoin))
    {
        UE_LOG(LogTemp, Log, TEXT("Join session failed."));
        Session->ClearOnJoinSessionCompleteDelegate_Handle(JoinSessionDelegateHandle);
        JoinSessionDelegateHandle.Reset();
    }
}

void ULSSessionSubsystem::HandleJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
    IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

    if (Result == EOnJoinSessionCompleteResult::Success)
    {
        FString ConnectString;
        if (Session->GetResolvedConnectString(SessionName, ConnectString))
        {
            if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
            {
                PlayerController->ClientTravel(ConnectString, ETravelType::TRAVEL_Absolute);
            }
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to join session."));
    }

    Session->ClearOnJoinSessionCompleteDelegate_Handle(JoinSessionDelegateHandle);
    JoinSessionDelegateHandle.Reset();
}

void ULSSessionSubsystem::SetupNotifications()
{
    // IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    // IOnlineSessionPtr Session = Subsystem->GetSessionInterface();
    //
    // Session->AddOnSessionParticipantJoinedDelegate_Handle(FOnSessionParticipantsChangeDelegate::CreateUObject(
    //     this,
    //     &ThisClass::HandleParticipantChanged)); 
}

void ULSSessionSubsystem::HandleParticipantChanged(FName EOSLobbyName, const FUniqueNetId& NetId, bool bJoined)
{
//     if (bJoined)
//     {
//         UE_LOG(LogTemp, Log, TEXT("A player has joined Lobby: %s"), *EOSLobbyName.ToString()); 
//     }
//     else
//     {
//         UE_LOG(LogTemp, Log, TEXT("A player has left Lobby: %s"), *EOSLobbyName.ToString());
//     }
}
