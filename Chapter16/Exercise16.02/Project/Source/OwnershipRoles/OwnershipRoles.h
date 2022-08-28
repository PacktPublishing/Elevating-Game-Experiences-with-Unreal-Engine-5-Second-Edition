// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#define ROLE_TO_STRING(Value) FindObject<UEnum>(ANY_PACKAGE, TEXT("ENetRole"), true)->GetNameStringByIndex(static_cast<int32>(Value))