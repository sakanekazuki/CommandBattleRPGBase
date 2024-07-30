// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BattleState.h"
#include "TurnState.h"
#include "CPP_BattleSubSystem.generated.h"

class ACPP_BattleCharacter;

/**
 * �퓬�̃V�X�e��
 */
UCLASS()
class COMMANDBATTLERPGBASE_API UCPP_BattleSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float StatusCalculation();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float DamageCalculation();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<FVector> PositionCalculation(int actorValue, float yPosition);

	UFUNCTION(BlueprintCallable)
	int GetTurnValue();

	UFUNCTION(BlueprintCallable)
	void BattleStart();

	UFUNCTION(BlueprintCallable)
	void TurnStart();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void PlayerCharacterActionSelect();
	void PlayerCharacterActionSelect_Implementation();

	void CharacterSkillExecution();
	void CharacterDead(ACPP_BattleCharacter* character);

	UFUNCTION(BlueprintCallable)
	void NextTurn();

	UFUNCTION(BlueprintCallable)
	void BattleFinish();

	UFUNCTION(BlueprintCallable)
	TArray<ACPP_BattleCharacter*> ActionOrderCheck();

	UFUNCTION(BlueprintCallable)
	void SetBattleCharacters(TArray<ACPP_BattleCharacter*> characters);

private:
	// ����
	float distance = 100;
	// �^�[����
	int turnValue = 0;

	// �퓬�L�����N�^�[
	TArray<ACPP_BattleCharacter*> battleCharacters;

	// �L�����N�^�[�̏���
	TArray<int> characterOrder;
	// �U���L�����N�^�[�̔ԍ�
	int attackCharacterNumber;

	// �퓬�̏��
	EBattleState battleState = EBattleState::Start;
	// �^�[���̏��
	ETurnState turnState = ETurnState::TurnStart;

	// �v���C���[�̏��s
	bool isPlayerWin = false;
	bool isPlayerLose = false;

};
