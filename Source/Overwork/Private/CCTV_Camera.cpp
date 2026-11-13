// Fill out your copyright notice in the Description page of Project Settings.


#include "CCTV_Camera.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Net/UnrealNetwork.h"

#include "Engine/Engine.h"

// Sets default values
ACCTV_Camera::ACCTV_Camera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = SceneRoot;

	Pivot = CreateDefaultSubobject<USceneComponent>(TEXT("Pivot"));
	Pivot->SetupAttachment(SceneRoot);

	CameraMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CameraMesh"));
	CameraMesh->SetupAttachment(Pivot);

	CameraCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("CaptureComponent2D"));
	CameraCaptureComponent->SetupAttachment(CameraMesh);

	// set capturing every frame
	CameraCaptureComponent->bCaptureEveryFrame = true;
	CameraCaptureComponent->bCaptureOnMovement = true;
	
	// Use normal Color for rendering
	CameraCaptureComponent->CaptureSource = ESceneCaptureSource::SCS_FinalColorLDR;

	CameraCaptureComponent->FOVAngle = 90.0f;
	
	bReplicates = true;
	SetReplicateMovement(true);
}

// Called when the game starts or when spawned
void ACCTV_Camera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACCTV_Camera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// capture scene every frame
	CameraCaptureComponent->CaptureScene();
	
}

