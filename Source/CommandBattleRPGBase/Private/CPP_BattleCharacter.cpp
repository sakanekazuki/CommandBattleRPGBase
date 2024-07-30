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
	
	// 配列削除
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
* 行動選択
*/
void ACPP_BattleCharacter::MoveSelect_Implementation()
{
	// 配列削除
	attackTargetActors.Empty();
}

/**
* スキル選択
*/
void ACPP_BattleCharacter::SkillSelect_Implementation()
{

}

/**
* ターゲット設定
* 
* @param targetActors ターゲット
*/
void ACPP_BattleCharacter::SetAttackTargetActors_Implementation(const TArray<AActor*>& targetActors)
{
	attackTargetActors = targetActors;
}

/**
* スキルを使う
*/
void ACPP_BattleCharacter::SkillExecution_Implementation()
{

}

/**
* ステータス取得
* 
* @return ステータス
*/
FStatusBase ACPP_BattleCharacter::GetStatus()
{
	return status;
}

/**
* ターゲット取得
*/
TArray<AActor*> ACPP_BattleCharacter::GetTargetActors()
{
	return attackTargetActors;
}

/**
* キャラクターがプレイヤーのキャラクターか取得
*/
bool ACPP_BattleCharacter::GetIsPlayerCharacter()
{
	return isPlayerCharacter;
}