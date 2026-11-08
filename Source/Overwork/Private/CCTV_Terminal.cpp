// Fill out your copyright notice in the Description page of Project Settings.


#include "CCTV_Terminal.h"

#include "Components/WidgetComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

#include "Engine/Engine.h"

#include "CameraWidget.h"

// Sets default values
ACCTV_Terminal::ACCTV_Terminal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraTerminal = CreateDefaultSubobject<UWidgetComponent>(TEXT("CameraTerminal"));
	
	CameraTerminalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CameraTerminalMesh"));

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;

	CameraTerminal->SetWidgetSpace(EWidgetSpace::World);
	// attach to
	CameraTerminal->SetupAttachment(Scene);
	CameraTerminalMesh->SetupAttachment(Scene);

	// set replicated
	bReplicates = true;
}

// Called when the game starts or when spawned
void ACCTV_Terminal::BeginPlay()
{
	Super::BeginPlay();

	// initialize the widget
	if (IsValid(CameraTerminal)) {
		CameraTerminal->InitWidget();
	}

	CameraTerminalWidget = Cast<UCameraWidget>(CameraTerminal->GetUserWidgetObject());

	// set's the widget's owning player to the first local player
	// use for requesting update
	CameraTerminalWidget->SetOwningPlayer(UGameplayStatics::GetPlayerController(this, 0));

	if (IsValid(CameraTerminalWidget)) {
		CameraTerminalWidget->InitializeCameraWidget(this);
	}

	CurrentCameraIndex = 0;

	// Calls the update CameraWidget and set the first Render target to current scene
	UpdateCameraWidget();
}

// Called every frame
void ACCTV_Terminal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACCTV_Terminal::NextCamera()
{
	if (CameraFeeds.IsEmpty()) // Feeds should not be empty
		return;

	CurrentCameraIndex = (CurrentCameraIndex + 1) % CameraFeeds.Num();
	UpdateCameraWidget();
}

void ACCTV_Terminal::PreviousCamera()
{
	if (CameraFeeds.IsEmpty())
		return;

	CurrentCameraIndex = (CurrentCameraIndex + CameraFeeds.Num() - 1) % CameraFeeds.Num();
	UpdateCameraWidget();
}

void ACCTV_Terminal::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACCTV_Terminal, CurrentCameraIndex);
}

void ACCTV_Terminal::OnRep_UpdateCurrentCameraIndex()
{
	UpdateCameraWidget();
}

void ACCTV_Terminal::UpdateCameraWidget()
{
	if (!IsValid(CameraTerminal) || !IsValid(CameraTerminalWidget))
		return;

	// Set the current camera seleted to selected camera
	CameraTerminalWidget->SetFeedMaterial(CameraFeeds[CurrentCameraIndex]);
	CameraTerminal->RequestRedraw();

}

