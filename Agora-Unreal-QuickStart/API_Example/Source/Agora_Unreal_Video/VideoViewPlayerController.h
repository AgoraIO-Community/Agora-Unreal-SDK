// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Templates/UniquePtr.h"
#include "VideoViewUserWidget.h"
#include "VideoViewPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class AGORA_UNREAL_VIDEO_API AVideoViewPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
        TSubclassOf<UUserWidget> WvideoViewWidget;
    
    UVideoViewUserWidget* VideoViewWidget = nullptr;

    void BeginPlay() override;

    void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
