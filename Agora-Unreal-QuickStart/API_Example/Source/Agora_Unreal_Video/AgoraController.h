// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AgoraRtcEngine.h"
#include "UVideoTextureObserver.h"

class UVideoViewUserWidget;
class UVoiceViewUserWidget;
/**
 * 
 */
class AGORA_UNREAL_VIDEO_API AgoraController : public agora::rtc::IRtcEngineEventHandler, public agora::rtc::ue4::UVideoTextureObserver
{
public:
	AgoraController();
	~AgoraController();
    
    void OnTick();

    void InitEngine();
    
    void ReleaseEngine();
    
    int JoinChannel(bool isAudio, const char *channelName);

    int LeaveChannel();
    
    void SetupLocalVideo(UImage* Brush);
    
    void SetupRemoteVideo(unsigned int uid, UImage* Brush);
    
    void ReleaseVideoView(unsigned int uid);
    
    void onWarning(int warn, const char* msg) override;
    
    void onError(int err, const char* msg) override;
    
    void onJoinChannelSuccess(const char* channel, uid_t uid, int elapsed) override;

    void onRejoinChannelSuccess(const char* channel, uid_t uid, int elapsed) override;
    
    void onLeaveChannel(const agora::rtc::RtcStats& stats) override;
    
    void onUserJoined(agora::rtc::uid_t uid, int elapsed) override;

    void onUserOffline(agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason) override;
    
    void OnLocalVideoTextureUpdate(const agora::rtc::ue4::VideoTextureFrame& _videoFrame) override;

    void OnRemoteVideoTextureUpdate(unsigned int uid, const agora::rtc::ue4::VideoTextureFrame& _videoFrame) override;
    
    void SetVideoViewWidget(UVideoViewUserWidget* videoWidget);
    
    void SetVoiceViewWidget(UVoiceViewUserWidget* voiceWidget);
private:
    agora::rtc::ue4::AgoraRtcEngine* _rtcEnginePtr = nullptr;
    UVideoViewUserWidget* _videoWidget = nullptr;
    UVoiceViewUserWidget* _voiceWidget = nullptr;
    const char* YOUR_APP_ID = "5db0d12c40354100abd7a8a0adaa1fb8";
};
