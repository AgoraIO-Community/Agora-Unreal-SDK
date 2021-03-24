#include "AgoraGMEngineEventHandler.h"


void AgoraGMEngineEventHandler::onRequestToken() 
{
    UE_LOG(LogTemp, Warning, TEXT("onRequestToken"));
}

void AgoraGMEngineEventHandler::onEnterRoomSuccess()
{
    UE_LOG(LogTemp, Warning, TEXT("onEnterRoomSuccess"));
}

void AgoraGMEngineEventHandler::onEnterRoomFail()
{
    UE_LOG(LogTemp, Warning, TEXT("onEnterRoomFail"));
}

void AgoraGMEngineEventHandler::onConnectionStateChange(GME_CONNECTION_STATE_TYPE state, GME_CONNECTION_CHANGED_REASON_TYPE reason)
{
    UE_LOG(LogTemp, Warning, TEXT("onConnectionStateChange state: %d, reason: %d"), state, reason);
}

void AgoraGMEngineEventHandler::onLostSync(int64_t lostSyncTimeMs)
{
    UE_LOG(LogTemp, Warning, TEXT("onLostSync lostSyncTimeMs: %d"), lostSyncTimeMs );
}

void AgoraGMEngineEventHandler::onGetSync(int64_t lostSyncTimeMs)
{
    UE_LOG(LogTemp, Warning, TEXT("onGetSync lostSyncTimeMs: %d"), lostSyncTimeMs );
}

void AgoraGMEngineEventHandler::onTeamMatesChange(const unsigned int *uids, int userCount)
{
    UE_LOG(LogTemp, Warning, TEXT("onTeamMatesChange"));
}