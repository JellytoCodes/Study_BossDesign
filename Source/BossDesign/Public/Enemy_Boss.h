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

protected:
	virtual void BeginPlay() override;

private :
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* bossTree;

};
