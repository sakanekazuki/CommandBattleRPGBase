// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurnState.generated.h"

UENUM(BlueprintType)
enum class ETurnState : uint8
{
	TurnStart   = 0 UMETA(DisplayName = "Start"),
	SkillSelect = 1 UMETA(DisplayName = "SkillSelect"),
	Attack      = 2 UMETA(DisplayName = "Attack"),
	TurnFinish  = 3 UMETA(DisplayName = "Finish"),
};