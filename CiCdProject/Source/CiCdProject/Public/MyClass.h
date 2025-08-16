

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MyClass.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CICDPROJECT_API AMyClass : public AActor
{
	GENERATED_BODY()

public:

	AMyClass();
	virtual ~AMyClass();
};
