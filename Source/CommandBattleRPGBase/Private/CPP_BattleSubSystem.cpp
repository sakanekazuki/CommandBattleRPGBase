// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_BattleSubSystem.h"

#include "Kismet/GameplayStatics.h"
#include "CPP_BattleCharacter.h"
#include "StatusBase.h"

/**
* �X�e�[�^�X�v�Z
*
* @return ����
*/
float UCPP_BattleSubSystem::StatusCalculation()
{
	float result = 0;

	return result;
}

/**
* �_���[�W�v�Z
*
* @return ����
*/
float UCPP_BattleSubSystem::DamageCalculation()
{
	float result = 0;

	return result;
}

/**
* �ʒu�v�Z
*
* @param actorValue �L�����N�^�[��
* @param yPosition  X���W
*
* @return ����
*/
TArray<FVector> UCPP_BattleSubSystem::PositionCalculation(int actorValue, float yPosition)
{
	// ����
	TArray<FVector> results;

	// ��������ꍇ�A�ŏ��̃A�N�^�[���^�񒆂ɂȂ�
	bool isFirstActorCenter = actorValue % 2 == 1;

	// �ʒu�̌v�Z
	for (int i = 0; i < actorValue; ++i)
	{
		// �ʒu
		FVector position = FVector(0, yPosition, 192.0f);
		// �ŏ��̃L�����N�^�[���^�񒆂������ꍇ
		if (isFirstActorCenter)
		{
			if (i == 0)
			{
			}
			else
			{
				// �����i�E���j
				if (i % 2 == 0)
				{
					position.X = (i - 1) * distance;
				}
				// �
				else
				{
					position.X = i * -distance;
				}
			}
		}
		// �ŏ��̃L�����N�^�[���^�񒆂ł͂Ȃ��ꍇ
		else
		{
			int number = (i - 2);
			if (number < 0)
			{
				number = 0;
			}
			// �E��
			if (i % 2 == 0)
			{
				position.X = number * distance + distance * 0.5f;
			}
			// ����
			else
			{
				position.X = -(number * distance + distance * 0.5f);
			}
		}
		// �ʒu�ǉ�
		results.Add(position);
	}

	return results;
}

/**
* �^�[�����擾
*/
int UCPP_BattleSubSystem::GetTurnValue()
{
	return turnValue;
}

/**
* �퓬�J�n
*/
void UCPP_BattleSubSystem::BattleStart()
{
	// �v���C���[�R���g���[���[�擾
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	// �퓬�J�n���Ƀ^�[����0�ɂ���
	turnValue = 0;

	// �퓬��Ԃ�퓬���ɕύX
	battleState = EBattleState::Battle;

	// �}�E�X�J�[�\���\��
	playerController->SetShowMouseCursor(true);
}

/**
* �^�[���J�n
*/
void UCPP_BattleSubSystem::TurnStart()
{
	// �^�[������i�߂�
	++turnValue;
	// �U���L�����N�^�[�̔ԍ���������
	attackCharacterNumber = 0;

	// �^�[���J�n��ԂɕύX
	turnState = ETurnState::TurnStart;
}

/**
* �v���C���[�L�����N�^�[�̃A�N�V�����I��
*/
void UCPP_BattleSubSystem::PlayerCharacterActionSelect_Implementation()
{
	// �X�L���I����ԂɕύX
	turnState = ETurnState::SkillSelect;
}

/**
* �L�����N�^�[�̃X�L�����s
*/
void UCPP_BattleSubSystem::CharacterSkillExecution()
{
	// �U������ԂɕύX
	turnState = ETurnState::Attack;

	// �X�L�����s
	battleCharacters[characterOrder[attackCharacterNumber]]->SkillExecution();

	// �Ō�ɍU������L�����N�^�[�̔ԍ���i�߂�
	++attackCharacterNumber;

	// �G�������̂ǂ��炩���S�ł��Ă��邩���ׂ�
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
		// �퓬�I��
		BattleFinish();
	}

	// �S�ẴL�����N�^�[���X�L�����g�p���I������ꍇ
	if (battleCharacters.Num() <= attackCharacterNumber)
	{
		NextTurn();
	}
}

/**
* �L�����N�^�[�̎��S
* 
* @param character ���S�����L�����N�^�[
*/
void UCPP_BattleSubSystem::CharacterDead(ACPP_BattleCharacter* character)
{
	// �z�񂩂�폜
	battleCharacters.Remove(character);
}

/**
* ���̃^�[���ɐi��
*/
void UCPP_BattleSubSystem::NextTurn()
{
	// �^�[���I����ԂɕύX
	turnState = ETurnState::TurnFinish;
}

/**
* �퓬�I��
*/
void UCPP_BattleSubSystem::BattleFinish()
{
	// �퓬��Ԃ��I���ɕύX
	//battleState = EBattleState::Finish;
	// �v���C���[����
	if (isPlayerWin)
	{

	}
	// �v���C���[�s�k
	else if (isPlayerLose)
	{

	}
}

/**
* �s�����𒲂ׂ�
*
* @return ����
*/
TArray<ACPP_BattleCharacter*> UCPP_BattleSubSystem::ActionOrderCheck()
{
	// �ԍ�
	TArray<ACPP_BattleCharacter*> result = battleCharacters;

	// ���בւ���
	result.Sort([](ACPP_BattleCharacter& a, ACPP_BattleCharacter& b)
		{
			FStatusBase status1 = a.GetStatus();
			FStatusBase status2 = b.GetStatus();
			
			return status1.Agility < status2.Agility;
		});

	return result;
}

/**
* �U������L�����N�^�[�ݒ�
* 
* @param characters �U������L�����N�^�[
*/
void UCPP_BattleSubSystem::SetBattleCharacters(TArray<ACPP_BattleCharacter*> characters)
{
	battleCharacters = characters;
}