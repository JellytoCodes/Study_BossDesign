// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Phase2Enter.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/Character.h"

/** -------------------------------------------------------------------------- */

#include "Enemy_Boss.h"
#include "BossAIController.h"
#include "BossDesignCharacter.h"

/** -------------------------------------------------------------------------- */

UBTTask_Phase2Enter::UBTTask_Phase2Enter(FObjectInitializer const &ObjectInitializer)
: UBTTask_BlackboardBase(ObjectInitializer)
{
    NodeName = "Phase2 Transition";
    bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_Phase2Enter::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
	auto* const bossCon = Cast<ABossAIController>(OwnerComp.GetAIOwner());
    if(!bossCon) return EBTNodeResult::Failed;

    auto* boss = Cast<AEnemy_Boss>(bossCon->GetPawn());
    if(!boss) return EBTNodeResult::Failed;

    if(!OwnerComp.GetBlackboardComponent()->GetValueAsBool("bIsPhase2Transition"))
    {
        UE_LOG(LogTemp, Warning, TEXT("Boss is Phase2 Transition"));
        OwnerComp.GetBlackboardComponent()->SetValueAsBool("bIsPhase2Transition", true);
    }
    
    else if(OwnerComp.GetBlackboardComponent()->GetValueAsBool("bIsPhase2Transition") &&
    !OwnerComp.GetBlackboardComponent()->GetValueAsBool("bIsPhase3Transition"))
    {
        UE_LOG(LogTemp, Warning, TEXT("Boss is Phase3 Transition"));
        OwnerComp.GetBlackboardComponent()->SetValueAsBool("bIsPhase3Transition", true);
    }
    FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    return EBTNodeResult::Succeeded; 
}