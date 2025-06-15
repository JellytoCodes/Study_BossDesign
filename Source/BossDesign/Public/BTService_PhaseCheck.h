// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_PhaseCheck.generated.h"

UENUM(BlueprintType)
enum class EPhaseType : uint8
{
	Phase1,
	Phase2,
	Phase3,
};

UCLASS()
class BOSSDESIGN_API UBTService_PhaseCheck : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public :
	UBTService_PhaseCheck();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
private :
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PhaseCheck", meta = (AllowPrivateAccess = "true"))
	float checkPhasePercent = 0.5f;

	bool bIsPhaseSwap = false;
};
