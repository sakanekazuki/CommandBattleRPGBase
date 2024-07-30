// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_BattleSubSystem.h"

#include "Kismet/GameplayStatics.h"
#include "CPP_BattleCharacter.h"
#include "StatusBase.h"

/**
* ステータス計算
*
* @return 結果
*/
float UCPP_BattleSubSystem::StatusCalculation()
{
	float result = 0;

	return result;
}

/**
* ダメージ計算
*
* @return 結果
*/
float UCPP_BattleSubSystem::DamageCalculation()
{
	float result = 0;

	return result;
}

/**
* 位置計算
*
* @param actorValue キャラクター数
* @param yPosition  X座標
*
* @return 結果
*/
TArray<FVector> UCPP_BattleSubSystem::PositionCalculation(int actorValue, float yPosition)
{
	// 結果
	TArray<FVector> results;

	// 奇数だった場合、最初のアクターが真ん中になる
	bool isFirstActorCenter = actorValue % 2 == 1;

	// 位置の計算
	for (int i = 0; i < actorValue; ++i)
	{
		// 位置
		FVector position = FVector(0, yPosition, 192.0f);
		// 最初のキャラクターが真ん中だった場合
		if (isFirstActorCenter)
		{
			if (i == 0)
			{
			}
			else
			{
				// 偶数（右側）
				if (i % 2 == 0)
				{
					position.X = (i - 1) * distance;
				}
				// 奇数
				else
				{
					position.X = i * -distance;
				}
			}
		}
		// 最初のキャラクターが真ん中ではない場合
		else
		{
			int number = (i - 2);
			if (number < 0)
			{
				number = 0;
			}
			// 右側
			if (i % 2 == 0)
			{
				position.X = number * distance + distance * 0.5f;
			}
			// 左側
			else
			{
				position.X = -(number * distance + distance * 0.5f);
			}
		}
		// 位置追加
		results.Add(position);
	}

	return results;
}

/**
* ターン数取得
*/
int UCPP_BattleSubSystem::GetTurnValue()
{
	return turnValue;
}

/**
* 戦闘開始
*/
void UCPP_BattleSubSystem::BattleStart()
{
	// プレイヤーコントローラー取得
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	// 戦闘開始時にターンを0にする
	turnValue = 0;

	// 戦闘状態を戦闘中に変更
	battleState = EBattleState::Battle;

	// マウスカーソル表示
	playerController->SetShowMouseCursor(true);
}

/**
* ターン開始
*/
void UCPP_BattleSubSystem::TurnStart()
{
	// ターン数を進める
	++turnValue;
	// 攻撃キャラクターの番号を初期化
	attackCharacterNumber = 0;

	// ターン開始状態に変更
	turnState = ETurnState::TurnStart;
}

/**
* プレイヤーキャラクターのアクション選択
*/
void UCPP_BattleSubSystem::PlayerCharacterActionSelect_Implementation()
{
	// スキル選択状態に変更
	turnState = ETurnState::SkillSelect;
}

/**
* キャラクターのスキル実行
*/
void UCPP_BattleSubSystem::CharacterSkillExecution()
{
	// 攻撃中状態に変更
	turnState = ETurnState::Attack;

	// スキル実行
	battleCharacters[characterOrder[attackCharacterNumber]]->SkillExecution();

	// 最後に攻撃するキャラクターの番号を進める
	++attackCharacterNumber;

	// 敵か味方のどちらかが全滅しているか調べる
	isPlayerLose = !battleCharacters.ContainsByPredicate([](ACPP_BattleCharacter* character)
		{
			return character->GetIsPlayerCharacter();
		});
	isPlayerWin = !battleCharacters.ContainsByPredicate([](ACPP_BattleCharacter* character)
		{
			return !character->GetIsPlayerCharacter();
		});
	if (isPlayerWin || isPlayerLose)
	{
		// 戦闘終了
		BattleFinish();
	}

	// 全てのキャラクターがスキルを使用し終わった場合
	if (battleCharacters.Num() <= attackCharacterNumber)
	{
		NextTurn();
	}
}

/**
* キャラクターの死亡
* 
* @param character 死亡したキャラクター
*/
void UCPP_BattleSubSystem::CharacterDead(ACPP_BattleCharacter* character)
{
	// 配列から削除
	battleCharacters.Remove(character);
}

/**
* 次のターンに進む
*/
void UCPP_BattleSubSystem::NextTurn()
{
	// ターン終了状態に変更
	turnState = ETurnState::TurnFinish;
}

/**
* 戦闘終了
*/
void UCPP_BattleSubSystem::BattleFinish()
{
	// 戦闘状態を終了に変更
	//battleState = EBattleState::Finish;
	// プレイヤー勝利
	if (isPlayerWin)
	{

	}
	// プレイヤー敗北
	else if (isPlayerLose)
	{

	}
}

/**
* 行動順を調べる
*
* @return 結果
*/
TArray<ACPP_BattleCharacter*> UCPP_BattleSubSystem::ActionOrderCheck()
{
	// 番号
	TArray<ACPP_BattleCharacter*> result = battleCharacters;

	// 並べ替える
	result.Sort([](ACPP_BattleCharacter& a, ACPP_BattleCharacter& b)
		{
			FStatusBase status1 = a.GetStatus();
			FStatusBase status2 = b.GetStatus();
			
			return status1.Agility < status2.Agility;
		});

	return result;
}

/**
* 攻撃するキャラクター設定
* 
* @param characters 攻撃するキャラクター
*/
void UCPP_BattleSubSystem::SetBattleCharacters(TArray<ACPP_BattleCharacter*> characters)
{
	battleCharacters = characters;
}