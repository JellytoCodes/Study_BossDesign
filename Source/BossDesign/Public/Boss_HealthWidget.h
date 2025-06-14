// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Boss_HealthWidget.generated.h"

class UTextBlock;
class UProgressBar;
class AEnemy_Boss;

UCLASS()
class BOSSDESIGN_API UBoss_HealthWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	void NativeConstruct();

private :
	UPROPERTY(meta = (AllowPrivateAccess = "true", BindWidget))
	UProgressBar* bossHealth;

	UPROPERTY(meta = (AllowPrivateAccess = "true", BindWidget))
	UTextBlock* bossName;

	AEnemy_Boss* bossInstance;

public :
	void SetBossInstance(AEnemy_Boss* inBoss) { bossInstance = inBoss; }

	void UpdatedBossName(); 
	void UpdatedBossHealth(); 
};
