// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatusBase.generated.h"

/**
 * �X�e�[�^�X
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
	// ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Strength = 0;
	// �U����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Attack = 0;
	// �ϋv��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Vitality = 0;
	// �h���
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Defence = 0;
	// �m��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Inteligence = 0;
	// ��p��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Dextrity = 0;
	// �q����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Agility = 0;
	// �^
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Lucky = 0;
};