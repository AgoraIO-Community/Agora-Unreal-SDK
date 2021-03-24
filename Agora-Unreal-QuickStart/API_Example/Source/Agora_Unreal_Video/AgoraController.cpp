// Copyright (c) 2019 Agora.io. All rights reserved.


#include "AgoraController.h"
#include "VideoViewUserWidget.h"
#include "VoiceViewUserWidget.h"
#include <memory>

using namespace agora::rtc;
using namespace agora::rtc::ue4;

AgoraController::AgoraController():_rtcEnginePtr(nullptr)
{
    
}

AgoraController::~AgoraController()
{
    ReleaseEngine();
}

void AgoraController::OnTick() {
    _rtcEnginePtr->OnTick();
}

void AgoraController::InitEngine() {
    _rtcEnginePtr = AgoraRtcEngine::createAgoraRtcEngine();
    RtcEngineContext _rtcEngineContext;
    _rtcEngineContext.appId = YOUR_APP_ID;
    _rtcEngineContext.eventHandler = this;
    _rtcEnginePtr->initialize(_rtcEngineContext);
}

void AgoraController::ReleaseEngine() {
    _rtcEnginePtr->release();
    _rtcEnginePtr = nullptr;
}

int AgoraController::JoinChannel(bool isAudio, const char *channelName) {
    //choose is audio mode or video mode joinChannel
    if (isAudio) {
        _rtcEnginePtr->setChannelProfile(CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_COMMUNICATION);
        _rtcEnginePtr->enableAudio();
    } else {
        _rtcEnginePtr->setChannelProfile(CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_COMMUNICATION);
        _rtcEnginePtr->enableAudio();
        _rtcEnginePtr->enableVideo();
        _rtcEnginePtr->registerVideoFrameObserver(this);
    }
    auto ret = _rtcEnginePtr->joinChannel("", channelName, "", 0);
    UE_LOG(LogTemp, Warning, TEXT("JoinChannel ret: %d"), ret);

    _agoraGMEnginePtr = agora::rtc::ue4::AgoraGMEngine::createAgoraGameMediaEngine();

    GMEngineContext context;
    context.appId = "5db0d12c40354100abd7a8a0adaa1fb8";
    _gmEngineEventHandler = std::make_shared<AgoraGMEngineEventHandler>();
    
    context.eventHandler = _gmEngineEventHandler.get();
    
    auto initRet = _agoraGMEnginePtr->initialize(_rtcEnginePtr, context);
    UE_LOG(LogTemp, Warning, TEXT("_agoraGMEnginePtr  initialize ret: %d"), initRet);

    auto enableSpatializerRet = _agoraGMEnginePtr->enableSpatializer(true, true);
    UE_LOG(LogTemp, Warning, TEXT("_agoraGMEnginePtr  enableSpatializerRet ret: %d"), enableSpatializerRet);

    auto setRangeAudioTeamIDRet = _agoraGMEnginePtr->setRangeAudioTeamID(324324);
    UE_LOG(LogTemp, Warning, TEXT("_agoraGMEnginePtr  setRangeAudioTeamIDRet ret: %d"), setRangeAudioTeamIDRet);
  
    // auto setRangeAudioTeamIDRet = _agoraGMEnginePtr->setRangeAudioTeamID(324324);
    // UE_LOG(LogTemp, Warning, TEXT("_agoraGMEnginePtr  setRangeAudioTeamIDRet ret: %d"), setRangeAudioTeamIDRet);
  
    auto setMaxHearAudioCountRet = _agoraGMEnginePtr->setMaxHearAudioCount(324324);
    UE_LOG(LogTemp, Warning, TEXT("_agoraGMEnginePtr  setMaxHearAudioCountRet ret: %d"), setMaxHearAudioCountRet);
  
    auto updateAudioRecvRangeRet = _agoraGMEnginePtr->updateAudioRecvRange(324324);
    UE_LOG(LogTemp, Warning, TEXT("_agoraGMEnginePtr  updateAudioRecvRangeRet ret: %d"), updateAudioRecvRangeRet);
  
    auto setParametersRet = _agoraGMEnginePtr->setParameters("");
    UE_LOG(LogTemp, Warning, TEXT("_agoraGMEnginePtr  setParametersRet ret: %d"), setParametersRet);
  
    auto enterRoomRet = _agoraGMEnginePtr->enterRoom("ewr", "rewrew", 32342);
    UE_LOG(LogTemp, Warning, TEXT("_agoraGMEnginePtr  enterRoomRet ret: %d"), enterRoomRet);

    auto renewTokenRet = _agoraGMEnginePtr->renewToken("re32r");
    UE_LOG(LogTemp, Warning, TEXT("_agoraGMEnginePtr  renewTokenRet ret: %d"), renewTokenRet);

    auto exitRoomRet = _agoraGMEnginePtr->exitRoom();
    UE_LOG(LogTemp, Warning, TEXT("_agoraGMEnginePtr  exitRoomRet ret: %d"), exitRoomRet);
  
    auto enableMicRet = _agoraGMEnginePtr->enableMic(false);
    UE_LOG(LogTemp, Warning, TEXT("_agoraGMEnginePtr  enableMicRet ret: %d"), enableMicRet);

    auto enableSpeakerRet = _agoraGMEnginePtr->enableSpeaker(false);
    UE_LOG(LogTemp, Warning, TEXT("_agoraGMEnginePtr  enableSpeakerRet ret: %d"), enableSpeakerRet);

    return ret;
}

int AgoraController::LeaveChannel() {
    auto ret = _rtcEnginePtr->leaveChannel();
    _rtcEnginePtr->registerVideoFrameObserver(nullptr);
    return ret;
}

void AgoraController::onWarning(int warn, const char* msg) {
    UE_LOG(LogTemp, Warning, TEXT("onWarning warn: %d"), warn);
}

void AgoraController::onError(int err, const char* msg) {
    UE_LOG(LogTemp, Warning, TEXT("onError err: %d, msg: %s"), err, msg);
}

void AgoraController::onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed) {
    int build = 0;
    UE_LOG(LogTemp, Warning, TEXT("onJoinChannelSuccess channel: %s, uid: %u, sdk ver: %s"), channel, uid, _rtcEnginePtr->getVersion(&build));
    if(_videoWidget) {
        _videoWidget->onJoinChannelSuccess(channel, uid, elapsed);
    }

    if(_voiceWidget) {
        _voiceWidget->onJoinChannelSuccess(channel, uid, elapsed);
    }
}

void AgoraController::onRejoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed)
{
    UE_LOG(LogTemp, Warning, TEXT("onRejoinChannelSuccess channel"));
}

void AgoraController::onLeaveChannel(const RtcStats& stats) {
    UE_LOG(LogTemp, Warning, TEXT("onLeaveChannel"));
    if(_videoWidget) {
        _videoWidget->onLeaveChannel(stats);
    }

    if(_voiceWidget) {
        _voiceWidget->onLeaveChannel(stats);
    }
}

void AgoraController::onUserJoined(agora::rtc::uid_t uid, int elapsed) {
    UE_LOG(LogTemp, Warning, TEXT("AgoraController::onUserJoined  uid: %u"), uid);
    if(_videoWidget) {
        _videoWidget->onUserJoined(uid);
    }

    if(_voiceWidget) {
        _voiceWidget->onUserJoined(uid);
    }
}

void AgoraController::onUserOffline(agora::rtc::uid_t uid, USER_OFFLINE_REASON_TYPE reason) {
    UE_LOG(LogTemp, Warning, TEXT("onUserOffline  uid: %u"), uid);
    if(_videoWidget) {
        _videoWidget->onUserOffline(uid);
    }

    if(_voiceWidget) {
        _voiceWidget->onUserOffline(uid);
    }
}

void AgoraController::OnLocalVideoTextureUpdate(const VideoTextureFrame& _videoFrame) {
    UE_LOG(LogTemp, Warning, TEXT("OnLocalVideoTextureUpdate uid"));
    if (_videoWidget) {
        _videoWidget->OnLocalVideoTextureUpdate(_videoFrame);
    }
}

void AgoraController::OnRemoteVideoTextureUpdate(unsigned int uid, const VideoTextureFrame& _videoFrame) {
    UE_LOG(LogTemp, Warning, TEXT("OnRemoteVideoTextureUpdate uid: %u"), uid);
    if (_videoWidget) {
        _videoWidget->OnRemoteVideoTextureUpdate(uid, _videoFrame);
    }
}

void AgoraController::SetVideoViewWidget(UVideoViewUserWidget* videoWidget) {
    _videoWidget = videoWidget;
}

void AgoraController::SetVoiceViewWidget(UVoiceViewUserWidget* voiceWidget) {
    _voiceWidget = voiceWidget;
}

void AgoraController::SetupLocalVideo(UImage* Brush) {
    _rtcEnginePtr->setupLocalVideo(Brush);
}

void AgoraController::SetupRemoteVideo(unsigned int uid, UImage* Brush) {
    UE_LOG(LogTemp, Warning, TEXT("AgoraController::SetupRemoteVideo  uid: %u"), uid);
    _rtcEnginePtr->setupRemoteVideo(uid, Brush);
}

void AgoraController::ReleaseVideoView(unsigned int uid) {
    _rtcEnginePtr->releaseVideoView(uid);
}

const char* AgoraController::getVersion() {
    int build = 0;
    return _rtcEnginePtr->getVersion(&build);
}