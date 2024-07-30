// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "StatusBase.h"
#include "CPP_BattleCharacter.generated.h"

UCLASS()
class COMMANDBATTLERPGBASE_API ACPP_BattleCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACPP_BattleCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void MoveSelect();
	virtual void MoveSelect_Implementation();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SkillSelect();
	virtual void SkillSelect_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetAttackTargetActors(const TArray<AActor*>& targetActors);
	virtual void SetAttackTargetActors_Implementation(const TArray<AActor*>& targetActors);

	UFUNCTION(BlueprintCallable)
	void SkillExecution();

	FStatusBase GetStatus();
	TArray<AActor*> GetTargetActors();
	bool GetIsPlayerCharacter();

protected:
	// ステータス
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FStatusBase status;
	// スキル
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int> skills;
	// 攻撃対象
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> attackTargetActors;
	// true = プレイヤーキャラクター
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool isPlayerCharacter = false;

};