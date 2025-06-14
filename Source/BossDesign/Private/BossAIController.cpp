
#include "BossAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

/** -------------------------------------------------------------------------- */

#include "Enemy_Boss.h"
#include "BossDesignCharacter.h"
#include "Boss_HealthWidget.h"

/** -------------------------------------------------------------------------- */

ABossAIController::ABossAIController(FObjectInitializer const &ObjectInitializer)
{
	SetupPerceptionSystem();
}

void ABossAIController::OnPossess(APawn* inPawn)
{
	Super::OnPossess(inPawn);

	boss = Cast<AEnemy_Boss>(inPawn);

	if(boss)
	{
		if(UBehaviorTree* const bossTree = boss->GetBehaviorTree())
		{
			UBlackboardComponent* bossBlackBoard;
			UseBlackboard(bossTree->BlackboardAsset, bossBlackBoard);
			Blackboard = bossBlackBoard;
			RunBehaviorTree(bossTree);
		}
	}
}

void ABossAIController::SetupPerceptionSystem()
{
	sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	if(!sightConfig) return;

	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

	sightConfig->SightRadius = 1000.f;
	sightConfig->LoseSightRadius = sightConfig->SightRadius + 10;
	sightConfig->PeripheralVisionAngleDegrees = 90.f;
	sightConfig->SetMaxAge(2.f);
	sightConfig->AutoSuccessRangeFromLastSeenLocation = 520.f;
	sightConfig->DetectionByAffiliation.bDetectEnemies = true;
	sightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	sightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*sightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ABossAIController::OnTargetDetected);
	GetPerceptionComponent()->ConfigureSense(*sightConfig);
}

void ABossAIController::OnTargetDetected(AActor *Actor, FAIStimulus const Stimulus)
{
	if(auto* const player = Cast<ABossDesignCharacter>(Actor))
	{
		GetBlackboardComponent()->SetValueAsBool("canSeePlayer", Stimulus.WasSuccessfullySensed());
		
		if(!bIsCheckWakeUp)
		{
			player->SetBossWidget(boss);
			player->GetBossInstance(boss);

			bIsCheckWakeUp = true;
		}
	}
}
