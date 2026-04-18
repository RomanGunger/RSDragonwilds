// Fill out your copyright notice in the Description page of Project Settings.


#include "USkillsAttributeSet.h"
#include "Net/UnrealNetwork.h"

USkillsAttributeSet::USkillsAttributeSet()
{
	WoodcuttingLevel = 1.0f;
	WoodcuttingXP = 0.0f;
	WoodcuttingMaxLevel = 99.0f;
	
	MiningLevel = 1.0f;
	MiningXP = 0.0f;
	MiningMaxLevel = 99.0f;
}

FSkillUIData USkillsAttributeSet::GetSkillData(ESkillType SkillType, UAbilitySystemComponent* ASC) const
{
	FSkillUIData Data;

	if (!ASC) return Data;

	switch (SkillType)
	{
	case ESkillType::Woodcutting:
		{
			Data.SkillType = SkillType;
			Data.Level = ASC->GetNumericAttribute(GetWoodcuttingLevelAttribute());
			Data.XP = ASC->GetNumericAttribute(GetWoodcuttingXPAttribute());
			Data.MaxLevel = ASC->GetNumericAttribute(GetWoodcuttingMaxLevelAttribute());
			break;
		}
	case ESkillType::Mining:
		{
			Data.SkillType = SkillType;
			Data.Level = ASC->GetNumericAttribute(GetMiningLevelAttribute());
			Data.XP = ASC->GetNumericAttribute(GetMiningXPAttribute());
			Data.MaxLevel = ASC->GetNumericAttribute(GetMiningMaxLevelAttribute());
			break;
		}

	default:
		break;
	}

	return Data;
}

TArray<FSkillUIData> USkillsAttributeSet::GetAllSkills(UAbilitySystemComponent* ASC) const
{
	TArray<FSkillUIData> Result;

	Result.Add(GetSkillData(ESkillType::Woodcutting, ASC));
	Result.Add(GetSkillData(ESkillType::Mining, ASC));

	return Result;
}

FName USkillsAttributeSet::GetSkillName(ESkillType SkillType)
{
	switch (SkillType)
	{
	case ESkillType::Woodcutting:
		return FName("Woodcutting");
		
	case ESkillType::Mining:
		return FName("Mining");

	default:
		return FName("Unknown");
	}
}

FGameplayAttribute USkillsAttributeSet::GetLevelAttributeBySkill(ESkillType SkillType) const
{
	switch (SkillType)
	{
	case ESkillType::Woodcutting:
		return GetWoodcuttingLevelAttribute();

	case ESkillType::Mining:
		return GetMiningLevelAttribute();

	default:
		return FGameplayAttribute();
	}
}

TArray<ESkillType> USkillsAttributeSet::GetAllSkillTypes()
{
	return {
		ESkillType::Woodcutting,
		ESkillType::Mining
	};
}

void USkillsAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(USkillsAttributeSet, WoodcuttingLevel, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USkillsAttributeSet, WoodcuttingXP, COND_None, REPNOTIFY_Always);    
	DOREPLIFETIME_CONDITION_NOTIFY(USkillsAttributeSet, WoodcuttingMaxLevel, COND_None, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(USkillsAttributeSet, MiningLevel, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USkillsAttributeSet, MiningXP, COND_None, REPNOTIFY_Always);    
	DOREPLIFETIME_CONDITION_NOTIFY(USkillsAttributeSet, MiningMaxLevel, COND_None, REPNOTIFY_Always);
}


