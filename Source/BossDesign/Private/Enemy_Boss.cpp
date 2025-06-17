
#include "Enemy_Boss.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

AEnemy_Boss::AEnemy_Boss()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AEnemy_Boss::BeginPlay()
{
	Super::BeginPlay();

}

void AEnemy_Boss::WeaknessDestroy()
{
	AAIController* AICon = Cast<AAIController>(GetController());
	if(AICon)
	{
		AICon->GetBlackboardComponent()->SetValueAsBool("bIsStunned", true);

		GetWorldTimerManager().SetTimer(stunnedTimer, this, &AEnemy_Boss::EndStun, 7.f, false);
	}
}

void AEnemy_Boss::EndStun()
{
	AAIController* AICon = Cast<AAIController>(GetController());
	if(AICon)
	{
		AICon->GetBlackboardComponent()->SetValueAsBool("bIsStunned", false);
	}
}

void AEnemy_Boss::BossDead(bool isDeath)
{
	bIsDeath = isDeath;
	AAIController* AICon = Cast<AAIController>(GetController());
	if(AICon)
	{
		AICon->GetBlackboardComponent()->SetValueAsBool("bIsDeath", bIsDeath);
	}
	
}

void AEnemy_Boss::BreakLeftArm()
{
	FName boneName = TEXT("upperarm_l");

	USkeletalMeshComponent* brokenMesh = GetMesh();

	if(brokenMesh)
	{
		brokenMesh->HideBoneByName(boneName, EPhysBodyOp::PBO_None);

		FVector SpawnLocation = brokenMesh->GetBoneLocation(TEXT("hand_l"));
		FRotator SpawnRotation = FRotator::ZeroRotator;

		if(!dropLeftArmClass) return;

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		AActor* Spawned = GetWorld()->SpawnActor<AActor>(dropLeftArmClass, SpawnLocation, FRotator::ZeroRotator);
		if(!Spawned) return;
		
		if(UStaticMeshComponent* spawnedMesh = Spawned->FindComponentByClass<UStaticMeshComponent>()) spawnedMesh->SetSimulatePhysics(true);

		AAIController* AICon = Cast<AAIController>(GetController());
		if(AICon && AICon->GetBlackboardComponent())
		{
			AICon->GetBlackboardComponent()->SetValueAsBool(FName("bIsBrokenArm"), true);
		}
	}
}

UBehaviorTree *AEnemy_Boss::GetBehaviorTree() const
{
	return bossTree;
}