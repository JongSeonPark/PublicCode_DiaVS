


#include "Actor/Projectile/DiaCross.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ADiaCross::ADiaCross()
{
	PrimaryActorTick.bCanEverTick = true;
	LookRoot = CreateDefaultSubobject<USceneComponent>("LookRoot"); 
	LookRoot->SetupAttachment(SphereComponent);
}

void ADiaCross::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//
	// FVector Velocity = ProjectileMovement->Velocity;
	// Velocity.X -= DeltaSeconds * 1000.f;
	// ProjectileMovement->SetVelocityInLocalSpace(Velocity);
	ProjectileMovement->Velocity -= GetActorForwardVector() * DeltaSeconds * BackwardSpeed;
	LookRoot->AddLocalRotation(CrossRotatorVelocity * DeltaSeconds);
}