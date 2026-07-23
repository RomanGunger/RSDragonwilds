#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RSAnimBlueprintHelper.generated.h"

class UAnimMontage;
class UAnimBlueprint;

UCLASS()
class RUNESCAPEDW_API URSAnimBlueprintHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Animation")
	static bool SetMontageSlotName(UAnimMontage* Montage, FName SlotName);

	UFUNCTION(BlueprintCallable, Category = "Animation")
	static bool ReparentAnimBlueprint(UAnimBlueprint* AnimBlueprint, TSubclassOf<UAnimInstance> NewParentClass);

	UFUNCTION(BlueprintCallable, Category = "Animation")
	static bool CompileAnimBlueprint(UAnimBlueprint* AnimBlueprint);

	UFUNCTION(BlueprintCallable, Category = "Animation")
	static bool RemoveBlueprintBoolVariable(UAnimBlueprint* AnimBlueprint, FName VariableName);
};
