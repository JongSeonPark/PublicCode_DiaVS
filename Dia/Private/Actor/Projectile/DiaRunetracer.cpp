#include "Actor/Projectile/DiaRunetracer.h"

#include "Components/BoxComponent.h"

ADiaRunetracer::ADiaRunetracer()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADiaRunetracer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (BoxAreaComponent.IsValid())
	{
		FVector BoxLocation = BoxAreaComponent.Pin()->GetComponentLocation();
		FVector BoxExtent = BoxAreaComponent.Pin()->GetScaledBoxExtent();

		// Runetracer가 영역 안에 있는지 확인(X, Y값만 확인)
		FVector Location = GetActorLocation();
		if (!(BoxLocation.X - BoxExtent.X < Location.X && Location.X < BoxLocation.X + BoxExtent.X &&
			BoxLocation.Y - BoxExtent.Y < Location.Y && Location.Y < BoxLocation.Y + BoxExtent.Y))
		{
			// TODO: 알고보니 대칭 변환해야 하는데~
			// Z를 0으로 돌려놓고 외적 값을 통해 상대위치를 통해서 방향을 정함.
			BoxLocation.Z = 0;
			Location.Z = 0;
			FVector Cross = FVector::CrossProduct(BoxLocation, Location);
			AddActorLocalRotation(FRotator(0, Cross.Z > 0 ? 90 : -90, 0));
		}
	}
}
