// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy_Boss.generated.h"

class UBehaviorTree;

UCLASS()
class BOSSDESIGN_API AEnemy_Boss : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemy_Boss();
	UBehaviorTree* GetBehaviorTree() const;

private :
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* bossTree;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	float maxHealth = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	float curHealth = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BrokenPoint", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> dropLeftArmClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LootWidget", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWidgetComponent> lootWidgetComponent;

public :
	float GetMaxHealth() const { return maxHealth; }
	float GetCurHealth() const { return curHealth; }
	void SetCurHealth(float setHealth) { curHealth = setHealth; }

	float GetHealthPercent() const { return curHealth / maxHealth; }

	void WeaknessDestroy();
	void EndStun();

	void BossDead(bool isDeath);

	bool bIsDeath = false;

	FTimerHandle stunnedTimer;

	void BreakLeftArm();
};
