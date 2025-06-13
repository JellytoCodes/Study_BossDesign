// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ChasePlayer.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

/** -------------------------------------------------------------------------- */

#include "BossDesignCharacter.h"
#include "BossAIController.h"
#include "BTTask_ChasePlayer.h"

/** -------------------------------------------------------------------------- */

UBTTask_ChasePlayer::UBTTask_ChasePlayer(FObjectInitializer const &ObjectInitializer)
{
	NodeName = "Chase Player";
}

EBTNodeResult::Type UBTTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    //Get Boss AIController
    auto* const bossCon = Cast<ABossAIController>(OwnerComp.GetAIOwner());
    if(!bossCon) return EBTNodeResult::Failed;

    //Get Boss Pawn
    APawn* boss = bossCon->GetPawn();
    if(!boss) return EBTNodeResult::Failed;

    //Get Boss BlackboardComponent
    auto* bossBlackBoard = OwnerComp.GetBlackboardComponent();
    if(!bossBlackBoard) return EBTNodeResult::Failed;
    
    //Get Player Actor
    AActor* player = UGameplayStatics::GetPlayerCharacter(boss->GetWorld(), 0);
    if(!player) return EBTNodeResult::Failed;
    
    //Get Player Location
    FVector playerLocation = player->GetActorLocation();
    FVector bossLocation = boss->GetActorLocation();
    
    float curDist = FVector::Dist(bossLocation, playerLocation);

    float distance = 100.f;

    if(curDist > distance)
    {  
        FVector dirToPlayer = (playerLocation - bossLocation).GetSafeNormal();
        FVector targetLocation = playerLocation - dirToPlayer * distance;

        UAIBlueprintHelperLibrary::SimpleMoveToLocation(bossCon, targetLocation);
    }

    FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    return EBTNodeResult::Succeeded;
}