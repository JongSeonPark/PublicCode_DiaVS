#include "Actor/DiaChest.h"

#include "Components/WidgetComponent.h"
#include "GameFramework/GameSession.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/DiaPlayerController.h"
#include "UI/Widget/PickableViewWidget.h"

ADiaChest::ADiaChest()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	WorldViewWidget = CreateDefaultSubobject<UWidgetComponent>("Widget");
	WorldViewWidget->SetupAttachment(RootComponent);
	WorldViewWidget->SetWidgetSpace(EWidgetSpace::Screen);
	WorldViewWidget->SetDrawSize(FVector2D::Zero());
}

void ADiaChest::BeginPlay()
{
	Super::BeginPlay();
	if (UPickableViewWidget* PickableViewWidget = Cast<UPickableViewWidget>(WorldViewWidget->GetWidget()))
	{
		PickableViewWidget->PickableItem = this;
	}
}

void ADiaChest::Pick_Implementation()
{
	OpenChest();
}

void ADiaChest::View_Implementation()
{
	IDiaPickable::View_Implementation();
}

void ADiaChest::OpenChest_Implementation()
{
	for (int32 i = 0; i < SpawnCount; i++)
	{
		FTransform SpawnTransform;
		float Rad = FMath::RandRange(0.f, UE_PI * 2);
		FVector RandLocation = GetActorLocation() + FVector(FMath::Cos(Rad), FMath::Sin(Rad), 0) * SpawnRange;
		FHitResult HitResult;
		GetWorld()->LineTraceSingleByChannel(HitResult, RandLocation + FVector(0, 0, 50.f), RandLocation - FVector(0, 0, 1000), ECC_WorldStatic);
		// TODO: 나중에 원점이 아닌 랜덤 반복 등..
		FVector SpawnLocation = HitResult.bBlockingHit ? HitResult.Location : GetActorLocation();
		SpawnTransform.SetLocation(SpawnLocation);
		SpawnTransform.SetRotation(FRotator(0, FMath::RandRange(0.f, 360.f), 0).Quaternion());
		
		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(
			SpawnActor,
			SpawnTransform
		);
	}
}
