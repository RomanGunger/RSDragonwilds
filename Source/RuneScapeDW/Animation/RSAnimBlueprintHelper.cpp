#include "RSAnimBlueprintHelper.h"

#include "Animation/AnimMontage.h"

bool URSAnimBlueprintHelper::SetMontageSlotName(UAnimMontage* Montage, FName SlotName)
{
	if (!Montage || Montage->SlotAnimTracks.IsEmpty())
	{
		return false;
	}

	for (FSlotAnimationTrack& Track : Montage->SlotAnimTracks)
	{
		Track.SlotName = SlotName;
	}

	Montage->Modify();
	Montage->MarkPackageDirty();
	return true;
}

#if WITH_EDITOR
#include "Animation/AnimBlueprint.h"
#include "Animation/AnimInstance.h"
#include "Engine/Blueprint.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/KismetEditorUtilities.h"

bool URSAnimBlueprintHelper::ReparentAnimBlueprint(UAnimBlueprint* AnimBlueprint, TSubclassOf<UAnimInstance> NewParentClass)
{
	if (!AnimBlueprint || !NewParentClass)
	{
		return false;
	}

	if (AnimBlueprint->ParentClass == NewParentClass)
	{
		return CompileAnimBlueprint(AnimBlueprint);
	}

	AnimBlueprint->ParentClass = NewParentClass;

	if (FBlueprintEditorUtils::FindMemberVariableGuidByName(AnimBlueprint, TEXT("bShouldSearch")).IsValid())
	{
		FBlueprintEditorUtils::RemoveMemberVariable(AnimBlueprint, TEXT("bShouldSearch"));
	}

	return CompileAnimBlueprint(AnimBlueprint);
}

bool URSAnimBlueprintHelper::CompileAnimBlueprint(UAnimBlueprint* AnimBlueprint)
{
	if (!AnimBlueprint)
	{
		return false;
	}

	FKismetEditorUtilities::CompileBlueprint(AnimBlueprint);
	AnimBlueprint->Modify();
	AnimBlueprint->MarkPackageDirty();
	return true;
}

bool URSAnimBlueprintHelper::RemoveBlueprintBoolVariable(UAnimBlueprint* AnimBlueprint, FName VariableName)
{
	if (!AnimBlueprint || VariableName.IsNone())
	{
		return false;
	}

	if (!FBlueprintEditorUtils::FindMemberVariableGuidByName(AnimBlueprint, VariableName).IsValid())
	{
		return true;
	}

	FBlueprintEditorUtils::RemoveMemberVariable(AnimBlueprint, VariableName);
	return CompileAnimBlueprint(AnimBlueprint);
}
#else
bool URSAnimBlueprintHelper::ReparentAnimBlueprint(UAnimBlueprint* AnimBlueprint, TSubclassOf<UAnimInstance> NewParentClass)
{
	return false;
}

bool URSAnimBlueprintHelper::CompileAnimBlueprint(UAnimBlueprint* AnimBlueprint)
{
	return false;
}

bool URSAnimBlueprintHelper::RemoveBlueprintBoolVariable(UAnimBlueprint* AnimBlueprint, FName VariableName)
{
	return false;
}
#endif
