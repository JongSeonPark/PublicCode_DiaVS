#include "Actor/SummonedCreature/DiaSummonedBird.h"

ADiaSummonedBird::ADiaSummonedBird()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADiaSummonedBird::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(RandomLocationTimerHandle, this, &ADiaSummonedBird::UpdateRandomLocation, StopDelay, false);
}

void ADiaSummonedBird::BeginDestroy()
{
	Super::BeginDestroy();
}

void ADiaSummonedBird::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


	// 랜덤 딜레이가 돌고 있음.
	if (!RandomLocationTimerHandle.IsValid())
	{
		if (FVector::DistSquared(MovedLocation, RandomPickLocation) > 100.f)
		{
			// const FVector Direction = (RandomPickLocation - ActorLocation).GetSafeNormal();
			const FVector Direction = MoveDirectionVector;
			MovedLocation += Direction * FloatingSpeed * DeltaSeconds;
		}
		else
		{
			// 거리가 10 내부일 때
			GetWorld()->GetTimerManager().SetTimer(RandomLocationTimerHandle, this, &ADiaSummonedBird::UpdateRandomLocation, StopDelay, false);
		}
	}
	
	SetActorLocation(GetInstigator() ? GetInstigator()->GetActorLocation() + MovedLocation : MovedLocation);
}

FVector ADiaSummonedBird::GetFireLocation() const
{
	return SkeltalMesh->GetSocketLocation(FName("FireLocation"));
}

void ADiaSummonedBird::UpdateRandomLocation()
{
	const float Length = FMath::FRand() * FloatingRange;
	const float Rad = FMath::FRand() * 2 * UE_PI;
	RandomPickLocation = FVector(FMath::Cos(Rad), FMath::Sin(Rad), 0) * Length;
	MoveDirectionVector = (RandomPickLocation- MovedLocation).GetSafeNormal();

	SetActorRotation((MoveDirectionVector).Rotation());

	RandomLocationTimerHandle.Invalidate();
}
