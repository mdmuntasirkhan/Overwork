// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CameraWidget.generated.h"

/**
 * 
 */

class UButton;
class UImage;
class UMaterialInstanceDynamic;
class UTextureRenderTarget2D;
class ACCTV_Terminal;

UCLASS()
class OVERWORK_API UCameraWidget : public UUserWidget
{
	GENERATED_BODY()

private:
    UFUNCTION()
    void NextClick();

    UFUNCTION()
    void PreviousClick();

    UPROPERTY()
    TObjectPtr<ACCTV_Terminal> CameraTerminal;

protected:
    UPROPERTY(VisibleAnywhere, meta = (BindWidget))
    TObjectPtr<UImage> CameraFeedImage;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    TObjectPtr<UMaterialInstanceDynamic> FeedMaterial;

    UPROPERTY(VisibleAnywhere, meta = (BindWidget))
    TObjectPtr<UButton> Next;

    UPROPERTY(VisibleAnywhere, meta = (BindWidget))
    TObjectPtr<UButton> Previous;

public:
    UFUNCTION()
    void InitializeCameraWidget(ACCTV_Terminal* terminal);

    UFUNCTION()
    void SetFeedMaterial(UTextureRenderTarget2D* cameraImage);
};
