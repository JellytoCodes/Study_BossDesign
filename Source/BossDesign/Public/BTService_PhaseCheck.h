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

USTRUCT(BlueprintType)
struct FPhaseCheck
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhaseCheck")
	float checkMinPercent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhaseCheck")
	float checkMaxPercent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhaseCheck")
	EPhaseType PhaseType;
};

UCLASS()
class BOSSDESIGN_API UBTService_PhaseCheck : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public :
	UBTService_PhaseCheck();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
private :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhaseCheck", meta = (AllowPrivateAccess = "true"))
	TArray<FPhaseCheck> PhaseCheck;

	bool bIsPhaseSwap = false;
};
