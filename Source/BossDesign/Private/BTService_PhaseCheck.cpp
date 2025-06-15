// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PhaseCheck.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

/** -------------------------------------------------------------------------- */

#include "BossDesignCharacter.h"
#include "BossAIController.h"
#include "Enemy_Boss.h"
#include "BTTask_ChasePlayer.h"

/** -------------------------------------------------------------------------- */

UBTService_PhaseCheck::UBTService_PhaseCheck()
{
	NodeName = "Check Boss Phase";
}

void UBTService_PhaseCheck::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//Get Boss AIController
    auto* const bossCon = Cast<ABossAIController>(OwnerComp.GetAIOwner());
    if(!bossCon) return;

    //Get Boss Pawn
    AEnemy_Boss* boss = Cast<AEnemy_Boss>(bossCon->GetPawn());
    if(!boss) return;

    auto* bossBlackBoard = OwnerComp.GetBlackboardComponent();
    if(!bossBlackBoard) return;

    float curPercent = boss->GetHealthPercent(); //(100 ~ 0.f Percent)

    //Start Phase1 Fixed
    EPhaseType curPhase = EPhaseType::Phase1;

    if(curPercent > 0.6f)         curPhase = EPhaseType::Phase1;
    else if (curPercent > 0.3f)   curPhase = EPhaseType::Phase2;
    else if (curPercent <= 0.3f)  curPhase = EPhaseType::Phase3;

    EPhaseType setPhase = curPhase;
    
    bossBlackBoard->SetValueAsInt("PhaseKey", static_cast<uint8>(setPhase));
}
