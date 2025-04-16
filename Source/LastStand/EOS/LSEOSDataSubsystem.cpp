#include "LSEOSDataSubsystem.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "Interfaces/OnlineStatsInterface.h"

void ULSEOSDataSubsystem::UpdateStat(FString StatName, int32 StatValue)
{
    IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
    IOnlineStatsPtr Stats = Subsystem->GetStatsInterface();

    FUniqueNetIdPtr NetId = Identity->GetUniquePlayerId(0);

    if (!NetId || Identity->GetLoginStatus(*NetId) != ELoginStatus::LoggedIn)
    {
        return;
    }

    FOnlineStatsUserUpdatedStats StatToUpdate = FOnlineStatsUserUpdatedStats(NetId.ToSharedRef());
    FOnlineStatUpdate IngestAmount = FOnlineStatUpdate(StatValue, FOnlineStatUpdate::EOnlineStatModificationType::Unknown);
    StatToUpdate.Stats.Add(StatName.ToUpper(), IngestAmount);

    TArray<FOnlineStatsUserUpdatedStats> StatsToUpdate;
    StatsToUpdate.Add(StatToUpdate);

    Stats->UpdateStats(NetId.ToSharedRef(), StatsToUpdate,
        FOnlineStatsUpdateStatsComplete::CreateLambda([](const FOnlineError& UpdateResult)
        {
            if (!UpdateResult.bSucceeded)
            {
                UE_LOG(LogTemp, Warning, TEXT("Error updating player statistics: %s"), *UpdateResult.ErrorCode);
                return;
            }
        }));
    
    QueryLeaderboardGlobal();
    // QueryLeaderboardFriends(StatName);
}

void ULSEOSDataSubsystem::QueryLeaderboardGlobal(FName LeaderboardName)
{
    IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
    IOnlineLeaderboardsPtr Leaderboards = Subsystem->GetLeaderboardsInterface();

    FUniqueNetIdPtr NetId = Identity->GetUniquePlayerId(0);

    if (!NetId || Identity->GetLoginStatus(*NetId) != ELoginStatus::LoggedIn)
    {
        return;
    }
    
    FOnlineLeaderboardReadRef GlobalLeaderboardReadRef = MakeShared<FOnlineLeaderboardRead, ESPMode::ThreadSafe>();
    GlobalLeaderboardReadRef->LeaderboardName = LeaderboardName.ToString();

    QueryLeaderboardDelegateHandle =
        Leaderboards->AddOnLeaderboardReadCompleteDelegate_Handle(FOnLeaderboardReadCompleteDelegate::CreateUObject(
            this,
            &ThisClass::HandleQueryLeaderboarComplete,
            GlobalLeaderboardReadRef));

    if (!Leaderboards->ReadLeaderboardsAroundRank(0, 10, GlobalLeaderboardReadRef))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to read global leaderboard."));
        Leaderboards->ClearOnLeaderboardReadCompleteDelegate_Handle(QueryLeaderboardDelegateHandle);
        QueryLeaderboardDelegateHandle.Reset();
    }
}

void ULSEOSDataSubsystem::QueryLeaderboardFriends(FString StatName, FName LeaderboardName)
{
    IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
    IOnlineLeaderboardsPtr Leaderboards = Subsystem->GetLeaderboardsInterface();

    FUniqueNetIdPtr NetId = Identity->GetUniquePlayerId(0);

    if (!NetId || Identity->GetLoginStatus(*NetId) != ELoginStatus::LoggedIn)
    {
        return;
    }

    FOnlineLeaderboardReadRef FriendLeaderboardReadRef = MakeShared<FOnlineLeaderboardRead, ESPMode::ThreadSafe>();
    FriendLeaderboardReadRef->LeaderboardName = FName(LeaderboardName);
    FriendLeaderboardReadRef->ColumnMetadata.Add(FColumnMetaData(FName(StatName), EOnlineKeyValuePairDataType::Int32));
    FriendLeaderboardReadRef->SortedColumn = FName(StatName);

    QueryLeaderboardDelegateHandle =
        Leaderboards->AddOnLeaderboardReadCompleteDelegate_Handle(FOnLeaderboardReadCompleteDelegate::CreateUObject(
            this,
            &ThisClass::HandleQueryLeaderboarComplete,
            FriendLeaderboardReadRef));

    if (!Leaderboards->ReadLeaderboardsForFriends(0, FriendLeaderboardReadRef))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to read friend leaderboard."));
        Leaderboards->ClearOnLeaderboardReadCompleteDelegate_Handle(QueryLeaderboardDelegateHandle);
        QueryLeaderboardDelegateHandle.Reset();
    }
}

void ULSEOSDataSubsystem::HandleQueryLeaderboarComplete(bool bWasSuccessful, FOnlineLeaderboardReadRef GlobalLeaderboardReadRef)
{
    IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    IOnlineLeaderboardsPtr Leaderboards = Subsystem->GetLeaderboardsInterface();

    if (bWasSuccessful)
    {
        for (auto Row : GlobalLeaderboardReadRef->Rows)
        {
            
            OnEOSLeaderboardUpdated.Broadcast(ParseLeaderboardToArray(GlobalLeaderboardReadRef));
            UE_LOG(LogTemp, Log, TEXT("Player Id: %s, Player Rank: %d"), *(*Row.PlayerId).ToString(), Row.Rank);
        }
    }

    Leaderboards->ClearOnLeaderboardReadCompleteDelegate_Handle(QueryLeaderboardDelegateHandle);
    QueryLeaderboardDelegateHandle.Reset();
}

TArray<FLeaderboardEntry> ULSEOSDataSubsystem::ParseLeaderboardToArray(const FOnlineLeaderboardReadRef& LeaderboardReadRef)
{
    TArray<FLeaderboardEntry> LeaderboardEntries;
    for (const FOnlineStatsRow& Row : LeaderboardReadRef->Rows)
    {
        FString ColumnValue = Row.Columns.begin()->Value.ToString();
        LeaderboardEntries.Add(FLeaderboardEntry(Row.NickName, Row.Rank, ColumnValue));
    }
    return LeaderboardEntries;
}