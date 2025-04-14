#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameSession.h"
#include "LSBaseGameSession.generated.h"


//////////////////////////////////////////
// 데디케이트 서버 사용을 위한 GameSession 클래스
// 현재는 사용 X
//////////////////////////////////////////

UCLASS()
class LASTSTAND_API ALSBaseGameSession : public AGameSession
{
    GENERATED_BODY()

public:
    ALSBaseGameSession();

    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual bool ProcessAutoLogin() override;
    virtual FString ApproveLogin(const FString& Options) override;
    virtual void PostLogin(APlayerController* NewPlayer) override;
    virtual void NotifyLogout(const APlayerController* ExitingPlayer) override;
    virtual void RegisterPlayer(APlayerController* NewPlayer, const FUniqueNetIdRepl& UniqueId, bool bWasFromInvite = false) override;
    virtual void UnregisterPlayer(const APlayerController* ExitingPlayer) override;

    void CreateSession(FName KeyName = "KeyName", FString KeyValue = "KeyValue");
    void StartSession();
    void EndSession();
    void DestroySession();

protected:
    void HandleCreateSessionCompleted(FName SessionName, bool bWasSuccessful);
    void HandleRegisterPlayerCompleted(FName SessionName, const TArray<FUniqueNetIdRef>& PlayerIds, bool bWasSuccesful);
    void HandleUnregisterPlayerCompleted(FName SessionName, const TArray<FUniqueNetIdRef>& PlayerIds, bool bWasSuccesful);
    void HandleStartSessionCompleted(FName SessionName, bool bWasSuccessful);
    void HandleEndSessionCompleted(FName SessionName, bool bWasSuccessful);
    void HandleDestroySessionCompleted(FName SessionName, bool bWasSuccessful);

public:
    FName SessionName = "SessionName";
    
private:
    int MaxNumberOfPlayersInSession;
    int NumberOfPlayersInSession;
    bool bIsSessionExists = false;

    FDelegateHandle CreateSessionDelegateHandle;
    FDelegateHandle RegisterPlayerDelegateHandle;
    FDelegateHandle UnregisterPlayerDelegateHandle;
    FDelegateHandle StartSessionDelegateHandle;
    FDelegateHandle EndSessionDelegateHandle;
    FDelegateHandle DestroySessionDelegateHandle;
};