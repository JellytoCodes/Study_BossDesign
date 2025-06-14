// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BossAIController.generated.h"

UCLASS()
class BOSSDESIGN_API ABossAIController : public AAIController
{
	GENERATED_BODY()

public :
	explicit ABossAIController(FObjectInitializer const& ObjectInitializer);

protected :
	virtual void OnPossess(APawn* inPawn) override;

private :
	class UAISenseConfig_Sight* sightConfig;

	void SetupPerceptionSystem();

	UFUNCTION()
	void OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus);

	bool bIsCheckWakeUp = false;

	class AEnemy_Boss* boss;
};
