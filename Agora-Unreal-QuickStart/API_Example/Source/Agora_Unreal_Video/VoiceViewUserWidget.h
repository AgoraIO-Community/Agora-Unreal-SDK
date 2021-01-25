// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "AgoraController.h"
#include <string.h>
#include "Async/Async.h"
#include "VoiceViewUserWidget.generated.h"
/**
 * 
 */
UCLASS()
class AGORA_UNREAL_VIDEO_API UVoiceViewUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
        UButton* JoinBtn = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
        UButton* LeaveBtn = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
        UTextBlock* LogText = nullptr;
		   
    void NativeConstruct() override;

    void NativeDestruct() override;

    void onUserJoined(unsigned int uid);
    
    void onUserOffline(unsigned int uid);
    
    void onJoinChannelSuccess(const char* channel, uid_t uid, int elapsed);
    
    void onLeaveChannel(const agora::rtc::RtcStats& stats);

    void PrintLog(const char *logStr);

	void SetButtonClickAble(bool enable);

    std::string format(const char *fmt,...);

    UFUNCTION(BlueprintCallable)
        void OnJoinButtonClick();
    
    UFUNCTION(BlueprintCallable)
        void OnLeaveButtonClick();

private:
    AgoraController* _agoraControllerPtr;
	const char* CHANNEL_NAME = "Hello_Agora";
    std::string logTextStr;
};
