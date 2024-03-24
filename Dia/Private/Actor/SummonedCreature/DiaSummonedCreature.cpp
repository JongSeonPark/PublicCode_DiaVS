


#include "Actor/SummonedCreature/DiaSummonedCreature.h"

// Sets default values
ADiaSummonedCreature::ADiaSummonedCreature()
{
	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root")));
	SkeltalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeltalMesh->SetupAttachment(RootComponent);
}

