#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RSAnimInstance.generated.h"

UCLASS()
class RUNESCAPEDW_API URSAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "MotionMatching")
	bool bShouldSearch = true;

protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
