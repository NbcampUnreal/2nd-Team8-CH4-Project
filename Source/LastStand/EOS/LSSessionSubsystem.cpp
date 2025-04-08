// Fill out your copyright notice in the Description page of Project Settings.


#include "LSSessionSubsystem.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystemTypes.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"

/** 세션 생성 */
void ULSSessionSubsystem::CreateSession(FName KeyName, FString KeyValue)
{
    IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    IOnlineSessionPtr Session = Subsystem->GetSessionInterface(); // Retrieve the generic session interface. 

    // Bind delegate to callback function
    CreateSessionDelegateHandle =
        Session->AddOnCreateSessionCompleteDelegate_Handle(FOnCreateSessionCompleteDelegate::CreateUObject(
            this,
            &ThisClass::OnCreateSessionComplete));
    
    // Set session settings 
    TSharedRef<FOnlineSessionSettings> SessionSettings = MakeShared<FOnlineSessionSettings>();
    SessionSettings->NumPublicConnections = 8; //We will test our sessions with 2 players to keep things simple
    SessionSettings->bShouldAdvertise = true; //This creates a public match and will be searchable. This will set the session as joinable via presence. 
    SessionSettings->bUsesPresence = false;   //No presence on dedicated server. This requires a local user.
    SessionSettings->bAllowJoinViaPresence = false; // superset by bShouldAdvertise and will be true on the backend
    SessionSettings->bAllowJoinViaPresenceFriendsOnly = false; // superset by bShouldAdvertise and will be true on the backend
    SessionSettings->bAllowInvites = false;    //Allow inviting players into session. This requires presence and a local user. 
    SessionSettings->bAllowJoinInProgress = false; //Once the session is started, no one can join.
    SessionSettings->bIsDedicated = false; //Session created on dedicated server.
    SessionSettings->bUseLobbiesIfAvailable = false; //This is an EOS Session not an EOS Lobby as they aren't supported on Dedicated Servers.
    SessionSettings->bUseLobbiesVoiceChatIfAvailable = false;
    SessionSettings->bUsesStats = true; //Needed to keep track of player stats.

    // This custom attribute will be used in searches on GameClients. 
    SessionSettings->Settings.Add(KeyName, FOnlineSessionSetting((KeyValue), EOnlineDataAdvertisementType::ViaOnlineService));

    // Create session.
    UE_LOG(LogTemp, Log, TEXT("Creating session..."));
    
    if (!Session->CreateSession(0, "SessionName", *SessionSettings))
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to create session!"));
        Session->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionDelegateHandle);
        CreateSessionDelegateHandle.Reset();
    }
}

void ULSSessionSubsystem::JoinSession(const FName SessionName)
{
    IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

    JoinSessionDelegateHandle = 
        Session->AddOnJoinSessionCompleteDelegate_Handle(FOnJoinSessionCompleteDelegate::CreateUObject(
            this,
            &ThisClass::OnJoinSessionComplete));

    UE_LOG(LogTemp, Log, TEXT("Joining session."));
    if (!Session->JoinSession(0, SessionName, *SessionToJoin))
    {
        UE_LOG(LogTemp, Log, TEXT("Join session failed."));
        Session->ClearOnJoinSessionCompleteDelegate_Handle(JoinSessionDelegateHandle);
        JoinSessionDelegateHandle.Reset();
    }
}

void ULSSessionSubsystem::FindMatchmakingSession()
{
    IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    IOnlineSessionPtr Session = Subsystem->GetSessionInterface();
    TSharedRef<FOnlineSessionSearch> Search = MakeShared<FOnlineSessionSearch>();

    Search->QuerySettings.SearchParams.Empty();

    Search->QuerySettings.Set(FName("Matchmaking"), FString("MatchmakingSession"), EOnlineComparisonOp::Equals); // Seach using our Key/Value pair

    FindMatchmakingSessionsDelegateHandle =
        Session->AddOnFindSessionsCompleteDelegate_Handle(FOnFindSessionsCompleteDelegate::CreateUObject(
            this,
            &ThisClass::OnFindMatchmakingSessionsComplete,
            Search));
    

    UE_LOG(LogTemp, Log, TEXT("Finding matchmaking session."));
    
    if (!Session->FindSessions(0, Search))
    {
        UE_LOG(LogTemp, Warning, TEXT("Finding session failed."));
        // Clear our handle and reset the delegate. 
        Session->ClearOnFindSessionsCompleteDelegate_Handle(FindMatchmakingSessionsDelegateHandle);
        FindMatchmakingSessionsDelegateHandle.Reset();
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
            &ThisClass::OnFindCustomSessionsComplete,
            Search));
    
    UE_LOG(LogTemp, Log, TEXT("Finding custom session."));
    
    if (!Session->FindSessions(0, Search))
    {
        UE_LOG(LogTemp, Warning, TEXT("Finding custom failed."));
        Session->ClearOnFindSessionsCompleteDelegate_Handle(FindCustomSessionsDelegateHandle);
        FindCustomSessionsDelegateHandle.Reset();
    }
}

void ULSSessionSubsystem::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
    
}

void ULSSessionSubsystem::OnFindMatchmakingSessionsComplete(bool bWasSuccessful,
    TSharedRef<FOnlineSessionSearch> Search)
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
                    // Local 테스트 용
                    FString ConnectString = "127.0.0.1:8081";
                    if (SessionPtr->GetResolvedConnectString(SessionInSearchResult, NAME_GamePort, ConnectString))
                    {
                        SessionToJoin = &SessionInSearchResult; 
                    }
                    break; 
                }
                JoinSession("MatchmakingSession");  
            }else
            {
                CreateSession("Matchmaking", "MatchmakingSession");
            }
        }
    }else
    {
        CreateSession("Matchmaking", "MatchmakingSession");
    }
}


void ULSSessionSubsystem::OnFindCustomSessionsComplete(bool bWasSuccessful, TSharedRef<FOnlineSessionSearch> Search)
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

void ULSSessionSubsystem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
}