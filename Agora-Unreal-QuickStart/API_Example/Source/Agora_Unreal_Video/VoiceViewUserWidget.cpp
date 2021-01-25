// Fill out your copyright notice in the Description page of Project Settings.


#include "VoiceViewUserWidget.h"


void UVoiceViewUserWidget::NativeConstruct() {
    Super::NativeConstruct();
    _agoraControllerPtr = new AgoraController();
    _agoraControllerPtr->InitEngine();
    _agoraControllerPtr->SetVoiceViewWidget(this);
    UE_LOG(LogTemp, Warning, TEXT("UVoiceViewUserWidget ====== NativeConstruct ======"));
    JoinBtn->OnClicked.AddDynamic(this, &UVoiceViewUserWidget::OnJoinButtonClick);
    LeaveBtn->OnClicked.AddDynamic(this, &UVoiceViewUserWidget::OnLeaveButtonClick);
}

void UVoiceViewUserWidget::NativeDestruct() {
    Super::NativeDestruct();
    delete _agoraControllerPtr;
    _agoraControllerPtr = nullptr;
}

void UVoiceViewUserWidget::OnJoinButtonClick() {
    UE_LOG(LogTemp, Warning, TEXT("UVoiceViewUserWidget OnJoinButtonClick ======"));
    SetButtonClickAble(false);
    int ret = _agoraControllerPtr->JoinChannel(true, CHANNEL_NAME);

    PrintLog(format("JoinChannel  ret: %d\r\n\r\n", ret).c_str());
}

void UVoiceViewUserWidget::OnLeaveButtonClick() {
    UE_LOG(LogTemp, Warning, TEXT("UVoiceViewUserWidget OnLeaveButtonClick ======"));
    SetButtonClickAble(true);
    int ret = _agoraControllerPtr->LeaveChannel();

    PrintLog(format("LeaveChannel  ret: %d\r\n\r\n", ret).c_str());
}

void UVoiceViewUserWidget::SetButtonClickAble(bool enable) {
    JoinBtn->SetIsEnabled(enable);
    LeaveBtn->SetIsEnabled(!enable);
}

void UVoiceViewUserWidget::onUserJoined(unsigned int uid) {
    UE_LOG(LogTemp, Warning, TEXT("UVoiceViewUserWidget onUserJoined uid: %u"), uid);

    PrintLog(format("onUserJoined  uid: %u\r\n\r\n", uid).c_str());
}

void UVoiceViewUserWidget::onUserOffline(unsigned int uid) {
    UE_LOG(LogTemp, Warning, TEXT("UVoiceViewUserWidget onUserOffline uid: %u"), uid);

    PrintLog(format("onUserOffline  uid: %u\r\n\r\n", uid).c_str());
}

void UVoiceViewUserWidget::onJoinChannelSuccess(const char* channel, uid_t uid, int elapsed) {
    UE_LOG(LogTemp, Warning, TEXT("UVoiceViewUserWidget onJoinChannelSuccess channel: %s, uid: %u"), channel, uid);

    PrintLog(format("onJoinChannelSuccess channel: %s, uid: %u\r\n\r\n", channel, uid).c_str());
}

void UVoiceViewUserWidget::onLeaveChannel(const agora::rtc::RtcStats& stats) {
    UE_LOG(LogTemp, Warning, TEXT("UVoiceViewUserWidget onLeaveChannel"));

    PrintLog(format("onLeaveChannel \r\n\r\n").c_str());
}

void UVoiceViewUserWidget::PrintLog(const char *logStr) {
    std::string stdStrLog(logStr);
    AsyncTask(ENamedThreads::GameThread, [=]()
    {
        if (strlen(logTextStr.c_str()) > 400) {
            logTextStr = "";
        }
        logTextStr += stdStrLog;

        FString log = logTextStr.c_str();
        LogText->SetText(FText::FromString(log));
    });
}

std::string UVoiceViewUserWidget::format(const char *fmt,...)
{
#define FORMAT_MSG_BUFFER_SIZE (204800)
    char szBuffer[FORMAT_MSG_BUFFER_SIZE + 1] = { 0 };
    va_list args;
    va_start(args, fmt);
    vsnprintf(szBuffer, FORMAT_MSG_BUFFER_SIZE, fmt, args);
    va_end(args);
    auto strRet  = szBuffer;
    return strRet;
}
