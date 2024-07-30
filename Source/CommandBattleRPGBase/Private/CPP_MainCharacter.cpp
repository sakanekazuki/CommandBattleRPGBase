// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_MainCharacter.h"

#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ACPP_MainCharacter::ACPP_MainCharacter()
{
	// あたり判定のサイズ設定
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 700.0f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	cameraBoom->SetupAttachment(RootComponent);
	cameraBoom->TargetArmLength = 400.0f;
	cameraBoom->bUsePawnControlRotation = true;

	followCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	followCamera->SetupAttachment(cameraBoom, USpringArmComponent::SocketName);
	followCamera->bUsePawnControlRotation = false;

	defaultSpeed = GetCharacterMovement()->MaxWalkSpeed;
}

// Called when the game starts or when spawned
void ACPP_MainCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 入力マッピングコンテキスト追加
	if (APlayerController* playerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer()))
		{
			subsystem->AddMappingContext(mainInputContext, 0);
		}
	}
}

/**
* 移動入力
* 
* @param value 移動量
*/
void ACPP_MainCharacter::Move(const FInputActionValue& value)
{
	// 入力量取得
	FVector2D movementVector = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, movementVector.Y);
		AddMovementInput(RightDirection, movementVector.X);
	}
}

/**
* カメラ入力
* 
* @param value 入力値
*/
void ACPP_MainCharacter::Look(const FInputActionValue& value)
{
	// 入力量取得
	FVector2D lookAxisVector = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(-lookAxisVector.X);
		AddControllerPitchInput(lookAxisVector.Y);
	}
}

/**
* メニュー
*/
void ACPP_MainCharacter::Menu_Implementation()
{
	UKismetSystemLibrary::PrintString(this, "hello", true, true, FColor::Cyan, 2.0f, TEXT("None"));
}

/**
* ダッシュ
*/
void ACPP_MainCharacter::Dash()
{
	GetCharacterMovement()->MaxWalkSpeed = dashSpeed;
}

/**
* ダッシュキャンセル
*/
void ACPP_MainCharacter::DashCancel()
{
	GetCharacterMovement()->MaxWalkSpeed = defaultSpeed;
}

// Called every frame
void ACPP_MainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPP_MainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// 入力
	if (UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// ジャンプ割り当て
		enhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		enhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		enhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACPP_MainCharacter::Move);

		enhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACPP_MainCharacter::Look);

		// メニュー割り当て
		enhancedInputComponent->BindAction(MenuAction, ETriggerEvent::Started, this, &ACPP_MainCharacter::Menu);
		// ダッシュ割り当て
		enhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &ACPP_MainCharacter::Dash);
		enhancedInputComponent->BindAction(DashAction, ETriggerEvent::Completed, this, &ACPP_MainCharacter::DashCancel);
	}
}