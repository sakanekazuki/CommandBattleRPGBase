// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleState.generated.h"

UENUM(BlueprintType)
enum class EBattleState : uint8
{
	Start = 0 UMETA(DisplayName = "Start"),
	Battle = 1 UMETA(DisplayName = "Battle"),
	Finish = 2 UMETA(DisplayName = "Finish"),
};