// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "VoiceViewUserWidget.h"
#include "VoiceViewPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class AGORA_UNREAL_VIDEO_API AVoiceViewPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
        TSubclassOf<UUserWidget> WvoiceViewWidget;
    
    UVoiceViewUserWidget* VoiceViewWidget = nullptr;

    void BeginPlay() override;

    void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
};
