// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_BattleCharacter.h"

// Sets default values
ACPP_BattleCharacter::ACPP_BattleCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_BattleCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// �z��폜
	attackTargetActors.Empty();
}

// Called every frame
void ACPP_BattleCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPP_BattleCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

/**
* �s���I��
*/
void ACPP_BattleCharacter::MoveSelect_Implementation()
{
	// �z��폜
	attackTargetActors.Empty();
}

/**
* �X�L���I��
*/
void ACPP_BattleCharacter::SkillSelect_Implementation()
{

}

/**
* �^�[�Q�b�g�ݒ�
* 
* @param targetActors �^�[�Q�b�g
*/
void ACPP_BattleCharacter::SetAttackTargetActors_Implementation(const TArray<AActor*>& targetActors)
{
	attackTargetActors = targetActors;
}

/**
* �X�L�����g��
*/
void ACPP_BattleCharacter::SkillExecution_Implementation()
{

}

/**
* �X�e�[�^�X�擾
* 
* @return �X�e�[�^�X
*/
FStatusBase ACPP_BattleCharacter::GetStatus()
{
	return status;
}

/**
* �^�[�Q�b�g�擾
*/
TArray<AActor*> ACPP_BattleCharacter::GetTargetActors()
{
	return attackTargetActors;
}

/**
* �L�����N�^�[���v���C���[�̃L�����N�^�[���擾
*/
bool ACPP_BattleCharacter::GetIsPlayerCharacter()
{
	return isPlayerCharacter;
}