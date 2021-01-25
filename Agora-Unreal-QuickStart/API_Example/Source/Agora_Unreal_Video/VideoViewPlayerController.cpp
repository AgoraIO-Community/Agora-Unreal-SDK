// Fill out your copyright notice in the Description page of Project Settings.


#include "VideoViewPlayerController.h"


void AVideoViewPlayerController::BeginPlay() {
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("AVideoViewPlayerController::BeginPlay ======"));
    VideoViewWidget = CreateWidget<UVideoViewUserWidget>(this, WvideoViewWidget);
    VideoViewWidget->AddToViewport();
}

void AVideoViewPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason) {
    Super::EndPlay(EndPlayReason);
    UE_LOG(LogTemp, Warning, TEXT("AVideoViewPlayerController::EndPlay ======"));
}