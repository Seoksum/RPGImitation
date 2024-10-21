// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController_Enemy.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemies/Enemy.h"

const FName AAIController_Enemy::HomePosKey(TEXT("HomePos"));
const FName AAIController_Enemy::PatrolPosKey(TEXT("PatrolPos"));

AAIController_Enemy::AAIController_Enemy()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("BehaviorTree'/Game/AI/BT_Enemy.BT_Enemy'"));
	if (BT.Succeeded())
	{
		BehaviorTree = BT.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBlackboardData> BD(TEXT("BlackboardData'/Game/AI/BB_Enemy.BB_Enemy'"));
	if (BD.Succeeded())
	{
		BlackboardData = BD.Object;
	}
}

void AAIController_Enemy::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BlackboardData, Blackboard))
	{
		Blackboard->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		Blackboard->SetValueAsObject(FName(TEXT("Enemy")), InPawn);

		if (RunBehaviorTree(BehaviorTree))
		{
			// TODO
		}
	}
}

void AAIController_Enemy::OnUnPossess()
{
	Super::OnUnPossess();


}

bool AAIController_Enemy::IsEnemyAIDead() const
{
	AEnemy* Enemy = Cast<AEnemy>(GetPawn());
	if (Enemy)
	{
		return Enemy->IsDeath;
	}

	return false;
}

