// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "OverWorkPS.generated.h"

/**
 * 
 */
UCLASS()
class OVERWORK_API AOverWorkPS : public APlayerState
{
	GENERATED_BODY()
	
	enum EPlayerRole {
		CCTVOperator,
		Officer
	};

protected:
	int32 playerRole;

public:
	UFUNCTION(BlueprintPure)
	int32 GetPlayerRole() const { return playerRole; }
};
