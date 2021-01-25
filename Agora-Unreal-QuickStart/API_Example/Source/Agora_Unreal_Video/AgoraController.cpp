// Copyright (c) 2019 Agora.io. All rights reserved.


#include "AgoraController.h"
#include "VideoViewUserWidget.h"
#include "VoiceViewUserWidget.h"

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

void AgoraController::onJoinChannelSuccess(const char* channel, uid_t uid, int elapsed) {
    UE_LOG(LogTemp, Warning, TEXT("onJoinChannelSuccess channel: %s, uid: %u"), channel, uid);
    if(_videoWidget) {
        _videoWidget->onJoinChannelSuccess(channel, uid, elapsed);
    }

    if(_voiceWidget) {
        _voiceWidget->onJoinChannelSuccess(channel, uid, elapsed);
    }
}

void AgoraController::onRejoinChannelSuccess(const char* channel, uid_t uid, int elapsed)
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

void AgoraController::onUserJoined(uid_t uid, int elapsed) {
    UE_LOG(LogTemp, Warning, TEXT("AgoraController::onUserJoined  uid: %u"), uid);
    if(_videoWidget) {
        _videoWidget->onUserJoined(uid);
    }

    if(_voiceWidget) {
        _voiceWidget->onUserJoined(uid);
    }
}

void AgoraController::onUserOffline(uid_t uid, USER_OFFLINE_REASON_TYPE reason) {
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
