// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatusBase.generated.h"

/**
 * ÉXÉeÅ[É^ÉX
 */
USTRUCT(BlueprintType)
struct FStatusBase
{
	GENERATED_BODY()

	// HP
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HP = 0;
	// MP
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MP = 0;
	// óÕ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Strength = 0;
	// çUåÇóÕ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Attack = 0;
	// ëœãvóÕ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Vitality = 0;
	// ñhå‰óÕ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Defence = 0;
	// ímóÕ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Inteligence = 0;
	// äÌópÇ≥
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Dextrity = 0;
	// ïqè∑ê´
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Agility = 0;
	// â^
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Lucky = 0;
};