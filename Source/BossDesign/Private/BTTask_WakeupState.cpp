// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_WakeupState.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

/** -------------------------------------------------------------------------- */

#include "BossDesignCharacter.h"
#include "BossAIController.h"
#include "BTTask_ChasePlayer.h"

/** -------------------------------------------------------------------------- */

UBTTask_WakeupState::UBTTask_WakeupState(FObjectInitializer const &ObjectInitializer)
: UBTTask_BlackboardBase(ObjectInitializer)
{
	NodeName = "Wakeup State";
}

EBTNodeResult::Type UBTTask_WakeupState::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8* NodeMemory)
{
    auto* const bossCon = Cast<ABossAIController>(OwnerComp.GetAIOwner());
    if(!bossCon) return EBTNodeResult::Failed;

    APawn* boss = bossCon->GetPawn();
    if(!boss) return EBTNodeResult::Failed;

    AActor* player = UGameplayStatics::GetPlayerCharacter(boss->GetWorld(), 0);
    if(!player) return EBTNodeResult::Failed;

    float distance = FVector::Dist(boss->GetActorLocation(), player->GetActorLocation());

    // SearchRadius �̳���� ���� ��� ��ȯ
    if (distance <= SearchRadius)
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsBool("bIsCombat", true);
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        return EBTNodeResult::Succeeded;
    }
    else
    {
        // ���� �Ÿ� �̴��̸� ���з� ��ȯ�ؼ� Ʈ�� ��õ�(Loop)�ǵ���
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return EBTNodeResult::Failed;
    }
}
