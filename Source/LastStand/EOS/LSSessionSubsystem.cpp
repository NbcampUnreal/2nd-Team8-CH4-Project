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
    Search->QuerySettings.Set(FName("Matchmaking"), 0, EOnlineComparisonOp::GreaterThanEquals);
    Search->QuerySettings.Set(TEXT("LOBBYSEARCH"), true, EOnlineComparisonOp::Equals);
    
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
            int32 MaxPlayers = 0;
            FOnlineSessionSearchResult* BestSession = nullptr;

            for (auto& SessionInSearchResult : Search->SearchResults)
            {
                int32 CurrentPlayers = SessionInSearchResult.Session.NumOpenPublicConnections;
                UE_LOG(LogTemp, Log, TEXT("Session PlayerNums : %d"), CurrentPlayers);
                if (CurrentPlayers > MaxPlayers)
                {
                    MaxPlayers = CurrentPlayers;
                    BestSession = &SessionInSearchResult;
                }
            }

            if (BestSession)
            {
                FString ConnectString;
                if (SessionPtr->GetResolvedConnectString(*BestSession, NAME_GamePort, ConnectString))
                {
                    SessionToJoin = BestSession;
                    FString OwnerIP = BestSession->Session.OwningUserId->ToString();
                    UE_LOG(LogTemp, Log, TEXT("Session Owner IP: %s"), *OwnerIP);
                }
                JoinSession("MatchmakingSession");
            }
            else
            {
                CreateSession("Matchmaking", "MatchmakingSession");
            }
        }
    }
    else
    {
        CreateSession("Matchmaking", "MatchmakingSession");
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

int32 ULSSessionSubsystem::GetNumOfPlayersInSession()
{
    int32 NumPlayers = 0;
    if (IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld()))
    {
        if (IOnlineSessionPtr Session = Subsystem->GetSessionInterface())
        {
            if (FNamedOnlineSession* NamedSession = Session->GetNamedSession(NAME_GameSession))
            {
                NumPlayers = NamedSession->RegisteredPlayers.Num();
            }
        }
    }
    return NumPlayers;
}

int32 ULSSessionSubsystem::GetIndexOfPlayerInSession()
{
    if (IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld()))
    {
        if (IOnlineSessionPtr Session = Subsystem->GetSessionInterface())
        {
            if (FNamedOnlineSession* NamedSession = Session->GetNamedSession(NAME_GameSession))
            {
                const TArray<TSharedRef<const FUniqueNetId>>& RegisteredPlayers = NamedSession->RegisteredPlayers;
                const FUniqueNetIdRepl LocalPlayerId = GetWorld()->GetFirstLocalPlayerFromController()->GetPreferredUniqueNetId();

                for (int32 Index = 0; Index < RegisteredPlayers.Num(); ++Index)
                {
                    if (*RegisteredPlayers[Index] == *LocalPlayerId)
                    {
                        return Index;
                    }
                }
            }
        }
    }

    checkNoEntry();
    return -1;
}

int32 ULSSessionSubsystem::GetIndexOfPlayerInSession(const APlayerController* Controller)
{
    if (IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld()))
    {
        if (IOnlineSessionPtr Session = Subsystem->GetSessionInterface())
        {
            if (FNamedOnlineSession* NamedSession = Session->GetNamedSession(NAME_GameSession))
            {
                const TArray<TSharedRef<const FUniqueNetId>>& RegisteredPlayers = NamedSession->RegisteredPlayers;
                const FUniqueNetIdRepl LocalPlayerId = Controller->GetLocalPlayer()->GetPreferredUniqueNetId();

                for (int32 Index = 0; Index < RegisteredPlayers.Num(); ++Index)
                {
                    if (*RegisteredPlayers[Index] == *LocalPlayerId)
                    {
                        return Index;
                    }
                }
            }
        }
    }
    
    checkNoEntry();
    return -1;
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


void ULSSessionSubsystem::CreateSession(const FName KeyName, const FString KeyValue)
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
    SessionSettings->Settings.Add(KeyName, FOnlineSessionSetting(0, EOnlineDataAdvertisementType::ViaOnlineService));

    UE_LOG(LogTemp, Log, TEXT("Creating Lobby..."));

    if (!Session->CreateSession(0, FName(KeyValue), *SessionSettings))
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to create Lobby!"));
    }
}

void ULSSessionSubsystem::HandleCreateSessionCompleted(FName SessionName, bool bWasSuccessful)
{
    // Tutorial 7: Callback function: This is called once our lobby is created

    IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    IOnlineSessionPtr Session = Subsystem->GetSessionInterface();
    if (bWasSuccessful)
    {
        UE_LOG(LogTemp, Log, TEXT("Lobby: %s Created!"), *SessionName.ToString());
        const FString Map = "/Game/Local/EOSMatchmakingTestMap?listen";
        GetWorld()->ServerTravel(Map, false);
        
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to create lobby!"));
    }

    // Clear our handle and reset the delegate. 
    Session->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionDelegateHandle);
    CreateSessionDelegateHandle.Reset();
}