


#include "Actor/Projectile/DiaAxe.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "PhysicsEngine/PhysicsSettings.h"

ADiaAxe::ADiaAxe()
{
	PrimaryActorTick.bCanEverTick = true;
	LookRoot = CreateDefaultSubobject<USceneComponent>("LookRoot"); 
	LookRoot->SetupAttachment(SphereComponent);

	// 위치를 ProjectileMovement로 업데이트하지 않겠음. 
	ProjectileMovement->InitialSpeed = 0;
	ProjectileMovement->MaxSpeed = 0;
	ProjectileMovement->Velocity = FVector::Zero();
}

void ADiaAxe::BeginPlay()
{
	Super::BeginPlay();
	// 도끼 회전
	AxeRotatorVelocity.Yaw =  AxeVelocity.Length() * FMath::FRandRange(0.5f, 1.5f); 
}

void ADiaAxe::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// XY 기준으로만 중력 업데이트
	const FVector OldVelocity = AxeVelocity;
	const FVector MoveDelta = ComputeMoveDelta(OldVelocity, DeltaSeconds);
	AxeVelocity = ComputeVelocity(AxeVelocity, DeltaSeconds);
	
	AddActorLocalOffset(MoveDelta);
	LookRoot->AddLocalRotation(AxeRotatorVelocity * DeltaSeconds);
}

void ADiaAxe::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(ADiaAxe, AxeVelocity, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ADiaAxe, AxeRotatorVelocity, COND_None, REPNOTIFY_Always);
}

FVector ADiaAxe::ComputeAcceleration(float DeltaTime) const
{
	FVector Acceleration(FVector::ZeroVector);
	const float Gravity = UPhysicsSettings::Get()->DefaultGravityZ;
	Acceleration.X += Gravity;
	return Acceleration;
}

FVector ADiaAxe::ComputeVelocity(const FVector& InVelocity, float DeltaTime) const
{
	// V = V0 + a * t
	const FVector Velocity_Internal = InVelocity + (ComputeAcceleration(DeltaTime) * DeltaTime);
	return Velocity_Internal;
}

FVector ADiaAxe::ComputeMoveDelta(const FVector& InVelocity, float DeltaTime) const
{
	const FVector Velocity_Internal = ComputeVelocity(InVelocity, DeltaTime);
	const FVector MoveDelta = Velocity_Internal * DeltaTime;
	return MoveDelta;
}
