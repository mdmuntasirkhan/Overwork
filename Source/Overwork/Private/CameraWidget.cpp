// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/TextureRenderTarget2D.h"
#include "OverworkPlayerController.h"
#include "CCTV_Terminal.h"
#include "Engine/Engine.h"

void UCameraWidget::NextClick()
{
	AOverworkPlayerController* PC = Cast<AOverworkPlayerController>(GetOwningPlayer());

	if (IsValid(PC) && IsValid(CameraTerminal))
		PC->ServerChangeCCTVCamera(CameraTerminal.Get(), true);
}

void UCameraWidget::PreviousClick()
{
	AOverworkPlayerController* PC = Cast<AOverworkPlayerController>(GetOwningPlayer());

	if (IsValid(PC) && IsValid(CameraTerminal))
		PC->ServerChangeCCTVCamera(CameraTerminal.Get(), false);
}

// Initialization of CameraWidget
void UCameraWidget::InitializeCameraWidget(ACCTV_Terminal* terminal)
{
	CameraTerminal = terminal;

	// sets up the Dynamic calling for buttons
	Next->OnClicked.AddUniqueDynamic(this, &UCameraWidget::NextClick);
	Previous->OnClicked.AddUniqueDynamic(this, &UCameraWidget::PreviousClick);

	// For some reason Unreal is not regonize the default click method (Up and Down) in multiplayer
	// (Works perfectlly on single player mode)
	// So I switch it to MouseDown
	Next->SetClickMethod(EButtonClickMethod::MouseDown);
	Previous->SetClickMethod(EButtonClickMethod::MouseDown);
}

// set the material used on CameralFeedImage to a dynamicMaterial and change it accordingly
void UCameraWidget::SetFeedMaterial(UTextureRenderTarget2D* image)
{
	if (IsValid(CameraFeedImage) && IsValid(image)) {
		FeedMaterial = CameraFeedImage->GetDynamicMaterial();
	}

	if (IsValid(FeedMaterial)) {
		FeedMaterial->SetTextureParameterValue("CameraTexture", image);
	}
}
