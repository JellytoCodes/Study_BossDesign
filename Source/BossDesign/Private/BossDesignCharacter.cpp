// Copyright Epic Games, Inc. All Rights Reserved.

#include "BossDesignCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "Enemy_Boss.h"
#include "Boss_HealthWidget.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ABossDesignCharacter

ABossDesignCharacter::ABossDesignCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	static ConstructorHelpers::FClassFinder<UBoss_HealthWidget> 
	bossWidgetBP(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Enemy/WBP_BossWidget.WBP_BossWidget_C'"));

	if(bossWidgetBP.Succeeded()) bossWidgetClass = bossWidgetBP.Class;
}

void ABossDesignCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void ABossDesignCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) 
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABossDesignCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABossDesignCharacter::Look);

		EnhancedInputComponent->BindAction(checkBossPhase1, ETriggerEvent::Started, this, &ABossDesignCharacter::curBossPhase1);
		EnhancedInputComponent->BindAction(checkBossPhase2, ETriggerEvent::Started, this, &ABossDesignCharacter::curBossPhase2);
		EnhancedInputComponent->BindAction(checkBossPhase3, ETriggerEvent::Started, this, &ABossDesignCharacter::curBossPhase3);
	}
}

void ABossDesignCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ABossDesignCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ABossDesignCharacter::curBossPhase1()
{
	if(!bossInstance && bossWidgetInstance) return;

	float curHealth = FMath::RandRange(61, 100);

	bossInstance->SetCurHealth(curHealth);
	bossWidgetInstance->UpdatedBossHealth();
}

void ABossDesignCharacter::curBossPhase2()
{
	if(!bossInstance && !bossWidgetInstance) return;

	float curHealth = FMath::RandRange(31, 60);

	bossInstance->SetCurHealth(curHealth);
	bossWidgetInstance->UpdatedBossHealth();
}

void ABossDesignCharacter::curBossPhase3()
{
	if(!bossInstance && bossWidgetInstance) return;

	float curHealth = FMath::RandRange(1, 30);

	bossInstance->SetCurHealth(curHealth);
	bossWidgetInstance->UpdatedBossHealth();
}

void ABossDesignCharacter::SetBossWidget(AEnemy_Boss *inBoss)
{
	if(!inBoss) return;

	UE_LOG(LogTemp, Warning, TEXT("SetBossWidget called with boss: %s"), *inBoss->GetName());

	auto *playerCon = Cast<APlayerController>(GetController());
	if(!playerCon) return;
	
	bossWidgetInstance = CreateWidget<UBoss_HealthWidget>(playerCon, bossWidgetClass);
	if(!bossWidgetInstance) return;

	bossWidgetInstance->SetBossInstance(inBoss);
	bossWidgetInstance->AddToViewport();
}
