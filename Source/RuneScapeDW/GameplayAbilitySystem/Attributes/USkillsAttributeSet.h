// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "USkillsAttributeSet.generated.h"

UENUM(BlueprintType)
enum class ESkillType : uint8
{
	Woodcutting,
	Mining,
	Cooking,
	Smithing,
	Crafting,
	Attack
};

USTRUCT(BlueprintType)
struct FSkillUIData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	ESkillType SkillType;

	UPROPERTY(BlueprintReadOnly)
	float Level;

	UPROPERTY(BlueprintReadOnly)
	float XP;

	UPROPERTY(BlueprintReadOnly)
	float MaxLevel;
};

USTRUCT(BlueprintType)
struct RUNESCAPEDW_API FSkillLevelData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Levels")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Levels")
	float RequiredXP = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Levels")
	float TotalXP = 0.0f;
};

/**
 * 
 */
UCLASS()
class RUNESCAPEDW_API USkillsAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	
	USkillsAttributeSet();
	
	UPROPERTY(BlueprintReadOnly, Category="Woodcutting", ReplicatedUsing=OnRep_WoodcuttingLevel)
	FGameplayAttributeData WoodcuttingLevel;
	ATTRIBUTE_ACCESSORS_BASIC(USkillsAttributeSet, WoodcuttingLevel);
	
	UPROPERTY(BlueprintReadOnly, Category="Woodcutting", ReplicatedUsing=OnRep_WoodcuttingXP)
	FGameplayAttributeData WoodcuttingXP;
	ATTRIBUTE_ACCESSORS_BASIC(USkillsAttributeSet, WoodcuttingXP);
	
	UPROPERTY(BlueprintReadOnly, Category="Woodcutting", ReplicatedUsing=OnRep_WoodcuttingMaxLevel)
	FGameplayAttributeData WoodcuttingMaxLevel;
	ATTRIBUTE_ACCESSORS_BASIC(USkillsAttributeSet, WoodcuttingMaxLevel);
	
	
	UPROPERTY(BlueprintReadOnly, Category="Mining", ReplicatedUsing=OnRep_MiningLevel)
	FGameplayAttributeData MiningLevel;
	ATTRIBUTE_ACCESSORS_BASIC(USkillsAttributeSet, MiningLevel);
	
	UPROPERTY(BlueprintReadOnly, Category="Mining", ReplicatedUsing=OnRep_MiningXP)
	FGameplayAttributeData MiningXP;
	ATTRIBUTE_ACCESSORS_BASIC(USkillsAttributeSet, MiningXP);
	
	UPROPERTY(BlueprintReadOnly, Category="Mining", ReplicatedUsing=OnRep_MiningMaxLevel)
	FGameplayAttributeData MiningMaxLevel;
	ATTRIBUTE_ACCESSORS_BASIC(USkillsAttributeSet, MiningMaxLevel);

	
public:
	
	UFUNCTION()
	void OnRep_WoodcuttingLevel(FGameplayAttributeData& OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(USkillsAttributeSet, WoodcuttingLevel, OldValue);
	}
	
	UFUNCTION()
	void OnRep_WoodcuttingXP(FGameplayAttributeData& OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(USkillsAttributeSet, WoodcuttingXP, OldValue);
	}
	
	UFUNCTION()
	void OnRep_WoodcuttingMaxLevel(FGameplayAttributeData& OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(USkillsAttributeSet, WoodcuttingMaxLevel, OldValue);
	}
	
	UFUNCTION()
	void OnRep_MiningLevel(FGameplayAttributeData& OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(USkillsAttributeSet, MiningLevel, OldValue);
	}
	
	UFUNCTION()
	void OnRep_MiningXP(FGameplayAttributeData& OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(USkillsAttributeSet, MiningXP, OldValue);
	}
	
	UFUNCTION()
	void OnRep_MiningMaxLevel(FGameplayAttributeData& OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(USkillsAttributeSet,MiningMaxLevel, OldValue);
	}
	
	UFUNCTION(BlueprintCallable)
	FSkillUIData GetSkillData(ESkillType SkillType, UAbilitySystemComponent* ASC) const;
	
	UFUNCTION(BlueprintCallable)
	TArray<FSkillUIData> GetAllSkills(UAbilitySystemComponent* ASC) const;
	
	UFUNCTION(BlueprintPure)
	static FName GetSkillName(ESkillType SkillType);
	
	UFUNCTION(BlueprintPure)
	FGameplayAttribute GetLevelAttributeBySkill(ESkillType SkillType) const;
	
	UFUNCTION(BlueprintPure)
	static TArray<ESkillType> GetAllSkillTypes();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
