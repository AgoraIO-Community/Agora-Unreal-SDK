// Fill out your copyright notice in the Description page of Project Settings.


#include "VoiceViewPlayerController.h"


void AVoiceViewPlayerController::BeginPlay() {
    Super::BeginPlay();
    VoiceViewWidget = CreateWidget<UVoiceViewUserWidget>(this, WvoiceViewWidget);
    VoiceViewWidget->AddToViewport();
}

void AVoiceViewPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason) {
    Super::EndPlay(EndPlayReason);
}