
#include "Enemy_Boss.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Components/WidgetComponent.h"

/** -------------------------------------------------------------------------- */

AEnemy_Boss::AEnemy_Boss()
{
	PrimaryActorTick.bCanEverTick = false;

	lootWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("LootWidget"));
	lootWidgetComponent->SetupAttachment(RootComponent);
	lootWidgetComponent->SetWidgetSpace(EWidgetSpace::World);
	lootWidgetComponent->SetDrawAtDesiredSize(true);
	lootWidgetComponent->SetRelativeLocation(FVector(0.f, 0.f, 100.f));

	static ConstructorHelpers::FClassFinder<UUserWidget> 
	lootWidgetAssset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Enemy/WBP_LootWidget.WBP_LootWidget_C'"));

	if(lootWidgetAssset.Succeeded()) lootWidgetComponent->SetWidgetClass(lootWidgetAssset.Class);
}

void AEnemy_Boss::BeginPlay()
{
	Super::BeginPlay();

	if(lootWidgetComponent) lootWidgetComponent->SetVisibility(false);
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
	if(!AICon) return;
	
	AICon->GetBlackboardComponent()->SetValueAsBool("bIsDeath", bIsDeath);
	
	if(!lootWidgetComponent) return;
	lootWidgetComponent->SetVisibility(true);
}

void AEnemy_Boss::BreakLeftArm()
{
	USkeletalMeshComponent* brokenMesh = GetMesh();

	if(brokenMesh)
	{
		brokenMesh->HideBoneByName(boneName, EPhysBodyOp::PBO_None);

		FVector SpawnLocation = brokenMesh->GetBoneLocation(boneName);
		FRotator SpawnRotation = FRotator::ZeroRotator;

		if(!dropBoneActorClass) return;

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		AActor* Spawned = GetWorld()->SpawnActor<AActor>(dropBoneActorClass, SpawnLocation, FRotator::ZeroRotator);
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