// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "UVideoTextureObserver.h"
#include "AgoraRtcEngine.h"
#include "Async/Async.h"
#include "VideoViewUserWidget.generated.h"

class AgoraController;
/**
 * 
 */
UCLASS()
class AGORA_UNREAL_VIDEO_API UVideoViewUserWidget : public UUserWidget
{
	GENERATED_BODY()
    
public:
    void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;
    
    void NativeConstruct() override;

    void NativeDestruct() override;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
        UImage* remoteVideo = nullptr;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
        UImage* localVideo = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
        UButton* JoinBtn = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
        UButton* LeaveBtn = nullptr;
    
    void OnLocalVideoTextureUpdate(const agora::rtc::ue4::VideoTextureFrame& _videoFrame);

    void OnRemoteVideoTextureUpdate(unsigned int uid, const agora::rtc::ue4::VideoTextureFrame& _videoFrame);
    
    void SetButtonClickAble(bool enable);
    
    void onUserJoined(unsigned int uid);
    
    void onUserOffline(unsigned int uid);
    
    void onJoinChannelSuccess(const char* channel, uid_t uid, int elapsed);
    
    void onLeaveChannel(const agora::rtc::RtcStats& stats);
    
    
    UFUNCTION(BlueprintCallable)
        void OnJoinButtonClick();
    
    UFUNCTION(BlueprintCallable)
        void OnLeaveButtonClick();
    
private:
    FSlateBrush LocalBrush;
    FSlateBrush RemoteBrush;
    FSlateBrush EmptyBrush;
    AgoraController* _agoraControllerPtr;
    const char* CHANNEL_NAME = "Hello_Agora";
};
