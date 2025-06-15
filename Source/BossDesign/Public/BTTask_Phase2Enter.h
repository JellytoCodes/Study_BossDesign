// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Phase2Enter.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class BOSSDESIGN_API UBTTask_Phase2Enter : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public : 
	explicit UBTTask_Phase2Enter(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;	

private :
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* phaseTransitionAnim;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	float animPlayRate = 1.f;
};
