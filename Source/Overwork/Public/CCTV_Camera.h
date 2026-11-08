// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CCTV_Camera.generated.h"

class UStaticMeshComponent;
class USceneCaptureComponent2D;

UCLASS()
class OVERWORK_API ACCTV_Camera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACCTV_Camera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> CameraMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneCaptureComponent2D> CameraCaptureComponent;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
