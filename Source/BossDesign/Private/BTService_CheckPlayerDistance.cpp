// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckPlayerDistance.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

/** -------------------------------------------------------------------------- */

#include "BossDesignCharacter.h"
#include "BossAIController.h"
#include "BTTask_ChasePlayer.h"

/** -------------------------------------------------------------------------- */

UBTService_CheckPlayerDistance::UBTService_CheckPlayerDistance()
{
	NodeName = "Check Player Distance";
}

void UBTService_CheckPlayerDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//Get Boss AIController
    auto* const bossCon = Cast<ABossAIController>(OwnerComp.GetAIOwner());
    if(!bossCon) return;

    //Get Boss Pawn
    APawn* boss = bossCon->GetPawn();
    if(!boss) return;

    //Get Boss BlackboardComponent
    auto* bossBlackBoard = OwnerComp.GetBlackboardComponent();
    if(!bossBlackBoard) return;

    //Get Player Actor
    AActor* player = UGameplayStatics::GetPlayerCharacter(boss->GetWorld(), 0);
    if(!player) return;

    float distance = FVector::Dist(boss->GetActorLocation(), player->GetActorLocation());

    UE_LOG(LogTemp, Warning, TEXT("Dist : %.2f, check Distance : %.2f"), distance, checkDistance);

    if(distance <= checkDistance) bossBlackBoard->SetValueAsBool("bIsInDistance", true);
    else bossBlackBoard->SetValueAsBool("bIsInDistance", false);
}