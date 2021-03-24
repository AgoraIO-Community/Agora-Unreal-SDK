#pragma once
#include "CoreMinimal.h"
#include "AgoraGMEngine.h"

using namespace agora::rtc;

class AgoraGMEngineEventHandler : public IGMEngineEventHandler {

public:
    virtual void onRequestToken() override;

    virtual void onEnterRoomSuccess() override;

    virtual void onEnterRoomFail() override;

    virtual void onConnectionStateChange(GME_CONNECTION_STATE_TYPE state, GME_CONNECTION_CHANGED_REASON_TYPE reason) override;

    virtual void onLostSync(int64_t lostSyncTimeMs) override;

    virtual void onGetSync(int64_t lostSyncTimeMs) override;

    virtual void onTeamMatesChange(const unsigned int *uids, int userCount) override;
};