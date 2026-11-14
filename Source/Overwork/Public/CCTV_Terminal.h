// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CCTV_Terminal.generated.h"

class UWidgetComponent;
class UStaticMeshComponent;
class USceneComponent;
class UTextureRenderTarget2D;

class UImage;
class UMaterialInstanceDynamic;
class UCameraWidget;

UCLASS()
class OVERWORK_API ACCTV_Terminal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACCTV_Terminal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> CameraTerminalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> CameraTerminal;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCameraWidget> CameraTerminalWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> Scene;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "CCTV_VALUE")
	TArray<UTextureRenderTarget2D*> CameraFeeds;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, ReplicatedUsing = OnRep_UpdateCurrentCameraIndex)
	int32 CurrentCameraIndex = 0;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "CCTV_Control")
	void NextCamera();

	UFUNCTION(BlueprintCallable, Category = "CCTV_Control")
	void PreviousCamera();

	// Function for calling all the Replacted variables / functions when there is a change
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps) const override;
private:
	UFUNCTION()
	void OnRep_UpdateCurrentCameraIndex();

	UFUNCTION()
	void UpdateCameraWidget();

	UFUNCTION(BlueprintPure)
	int32 GetCurrentCamera() const { return CurrentCameraIndex; }
};
