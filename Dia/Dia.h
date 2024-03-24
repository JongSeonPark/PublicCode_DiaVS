// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogDia, Log, All);

#define ECC_Projectile ECollisionChannel::ECC_GameTraceChannel1
#define ECC_Item ECollisionChannel::ECC_GameTraceChannel2
#define ECC_Magnet ECollisionChannel::ECC_GameTraceChannel3