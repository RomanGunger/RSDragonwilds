#include "RSAnimInstance.h"

void URSAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	bShouldSearch = !IsAnyMontagePlaying();
}
