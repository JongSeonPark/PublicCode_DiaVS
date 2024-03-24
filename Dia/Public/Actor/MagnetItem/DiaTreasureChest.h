

#pragma once

#include "CoreMinimal.h"
#include "Actor/MagnetItem/DiaMagnetItem.h"
#include "DiaTreasureChest.generated.h"

/**
 * 뱀파이어 서바이버즈의 전리품 상자를 구현합니다.
 */
UCLASS()
class DIA_API ADiaTreasureChest : public ADiaMagnetItem
{
	GENERATED_BODY()
protected:
	virtual void AcceptedActorUpdate(AActor* CollisionActor) override;

private:
	static const TArray<TPair<int, float>> TreasureCountAndRarity;
	// 본작에서는 시간과 열은 상자 숫자에 따라 일부 정해지는 요소가 있는 듯한데, 1, 3, 6 확률 랜덤으로 적용하겠음.
	int32 ComputeTreasureCount() const;
};
