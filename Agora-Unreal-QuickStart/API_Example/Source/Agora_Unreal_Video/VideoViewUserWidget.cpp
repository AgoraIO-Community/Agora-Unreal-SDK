// Fill out your copyright notice in the Description page of Project Settings.


#include "VideoViewUserWidget.h"
#include "AgoraController.h"

void UVideoViewUserWidget::NativeConstruct() {
    Super::NativeConstruct();
    _agoraControllerPtr = new AgoraController();
    _agoraControllerPtr->InitEngine();
    _agoraControllerPtr->SetVideoViewWidget(this);
    UE_LOG(LogTemp, Warning, TEXT("UVideoViewUserWidget ====== NativeConstruct ======"));
    JoinBtn->OnClicked.AddDynamic(this, &UVideoViewUserWidget::OnJoinButtonClick);
    LeaveBtn->OnClicked.AddDynamic(this, &UVideoViewUserWidget::OnLeaveButtonClick);
}

void UVideoViewUserWidget::NativeDestruct() {
    Super::NativeDestruct();
    delete _agoraControllerPtr;
    _agoraControllerPtr = nullptr;
}

void UVideoViewUserWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime) {
    Super::NativeTick(MyGeometry, DeltaTime);
    _agoraControllerPtr->OnTick();
}

void UVideoViewUserWidget::OnLocalVideoTextureUpdate(const agora::rtc::ue4::VideoTextureFrame& _videoFrame) {
}

void UVideoViewUserWidget::OnRemoteVideoTextureUpdate(unsigned int uid, const agora::rtc::ue4::VideoTextureFrame& _videoFrame) {
}

void UVideoViewUserWidget::OnJoinButtonClick() {
    UE_LOG(LogTemp, Warning, TEXT("UVideoViewUserWidget OnJoinButtonClick ======"));
    SetButtonClickAble(false);
    _agoraControllerPtr->JoinChannel(false, CHANNEL_NAME);
}

void UVideoViewUserWidget::OnLeaveButtonClick() {
    UE_LOG(LogTemp, Warning, TEXT("UVideoViewUserWidget OnLeaveButtonClick ======"));
    SetButtonClickAble(true);
    _agoraControllerPtr->LeaveChannel();
}

void UVideoViewUserWidget::SetButtonClickAble(bool enable) {
    JoinBtn->SetIsEnabled(enable);
    LeaveBtn->SetIsEnabled(!enable);
}

void UVideoViewUserWidget::onUserJoined(unsigned int uid) {
    AsyncTask(ENamedThreads::GameThread, [=]()
    {
        UE_LOG(LogTemp, Warning, TEXT("UVideoViewUserWidget::onUserJoined ======%u"), uid);
        _agoraControllerPtr->SetupRemoteVideo(uid, remoteVideo);
    });
}

void UVideoViewUserWidget::onUserOffline(unsigned int uid) {
    AsyncTask(ENamedThreads::GameThread, [=]()
    {
        UE_LOG(LogTemp, Warning, TEXT("UVideoViewUserWidget onUserOffline ======"));
        remoteVideo->SetBrush(EmptyBrush);
        _agoraControllerPtr->ReleaseVideoView(uid);
    });
}

void UVideoViewUserWidget::onJoinChannelSuccess(const char* channel, uid_t uid, int elapsed) {
    AsyncTask(ENamedThreads::GameThread, [=]()
    {
        UE_LOG(LogTemp, Warning, TEXT("UVideoViewUserWidget clean =====onJoinChannelSuccess ======"));
        _agoraControllerPtr->SetupLocalVideo(localVideo);
    });
}

void UVideoViewUserWidget::onLeaveChannel(const agora::rtc::RtcStats& stats) {
    AsyncTask(ENamedThreads::GameThread, [=]()
    {
        UE_LOG(LogTemp, Warning, TEXT("UVideoViewUserWidget onLeaveChannel ======"));
        localVideo->SetBrush(EmptyBrush);
        remoteVideo->SetBrush(EmptyBrush);
    });
}
