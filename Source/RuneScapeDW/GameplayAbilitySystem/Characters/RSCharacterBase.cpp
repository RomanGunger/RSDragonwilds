// Fill out your copyright notice in the Description page of Project Settings.


#include "RSCharacterBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RuneScapeDW/GameplayAbilitySystem/RSAbilitySystemComponent.h"
#include "RuneScapeDW/GameplayAbilitySystem/Attributes/USkillsAttributeSet.h"
#include "RuneScapeDW/GameplayAbilitySystem/Attributes/BasicAttributeSet.h"

// Sets default values
ARSCharacterBase::ARSCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Add AbilitySystemComponent
	AbilitySystemComponent = CreateDefaultSubobject<URSAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(ASCReplicationMode);
	
	GetCapsuleComponent()->InitCapsuleSize(35.0f, 90.0f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	
	GetCharacterMovement()->JumpZVelocity = 400.0f;
	GetCharacterMovement()->AirControl =0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	
	//Add basic attribute set
	BasicAttributeSet = CreateDefaultSubobject<UBasicAttributeSet>(TEXT("BasicAttributeSet"));
	SkillsAttributeSet = CreateDefaultSubobject<USkillsAttributeSet>(TEXT("SkillsAttributeSet"));
	
	if (SkillsAttributeSet)
	{
		UE_LOG(LogTemp, Warning, TEXT("WoodcuttingLevel initialized to: %f"), 
			SkillsAttributeSet->GetWoodcuttingLevel());
	}
}

// Called when the game starts or when spawned
void ARSCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void ARSCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARSCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ARSCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		GrantAbilities(StartingAbilities);
		
		BindSkillDelegates();
	}
}

void ARSCharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		
		BindSkillDelegates();
	}
}

void ARSCharacterBase::BindSkillDelegates()
{
	if (!AbilitySystemComponent || !SkillsAttributeSet) return;

	TArray<ESkillType> Skills = USkillsAttributeSet::GetAllSkillTypes();

	for (ESkillType Skill : Skills)
	{
		// ===== LEVEL =====
		FGameplayAttribute LevelAttribute = SkillsAttributeSet->GetLevelAttributeBySkill(Skill);

		if (LevelAttribute.IsValid())
		{
			AbilitySystemComponent
				->GetGameplayAttributeValueChangeDelegate(LevelAttribute)
				.AddUObject(this, &ARSCharacterBase::OnSkillLevelChanged);

			SkillAttributeMap.Add(LevelAttribute, Skill);
		}

		// ===== XP =====
		FGameplayAttribute XPAttribute;

		switch (Skill)
		{
		case ESkillType::Woodcutting:
			XPAttribute = SkillsAttributeSet->GetWoodcuttingXPAttribute();
			break;

		case ESkillType::Mining:
			XPAttribute = SkillsAttributeSet->GetMiningXPAttribute();
			break;

		default:
			continue;
		}

		if (XPAttribute.IsValid())
		{
			AbilitySystemComponent
				->GetGameplayAttributeValueChangeDelegate(XPAttribute)
				.AddUObject(this, &ARSCharacterBase::OnSkillXPChanged);

			SkillAttributeMap.Add(XPAttribute, Skill);
		}
	}
}

UAbilitySystemComponent* ARSCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

TArray<FGameplayAbilitySpecHandle> ARSCharacterBase::GrantAbilities(
	TArray<TSubclassOf<UGameplayAbility>> AbilitiesToGrant)
{
	if (!AbilitySystemComponent || !HasAuthority())
	{
		return TArray<FGameplayAbilitySpecHandle>();
	}
	
	TArray<FGameplayAbilitySpecHandle> AbilityHandles;
	
	for (TSubclassOf<UGameplayAbility> Ability : AbilitiesToGrant)
	{
		FGameplayAbilitySpecHandle SpecHandle = AbilitySystemComponent->
		GiveAbility(FGameplayAbilitySpec(Ability, 1, -1, this));
		AbilityHandles.Add(SpecHandle);
	}
	
	SendAbilitiesChangedEvent();
	return AbilityHandles;
}

void ARSCharacterBase::RemoveAbilities(TArray<FGameplayAbilitySpecHandle> AbilityHandlesToRemove)
{
	if (!AbilitySystemComponent || !HasAuthority())
	{
		return;
	}
	
	for (FGameplayAbilitySpecHandle AbilityHandle : AbilityHandlesToRemove)
	{
		AbilitySystemComponent->ClearAbility(AbilityHandle);
	}
	
	SendAbilitiesChangedEvent();
}

void ARSCharacterBase::SendAbilitiesChangedEvent()
{
	FGameplayEventData EventData;
	EventData.EventTag = FGameplayTag::RequestGameplayTag(FName("Event.Abilities.Changed"));
	EventData.Instigator = this;
	EventData.Target = this;
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, EventData.EventTag, EventData);
}

void ARSCharacterBase::OnSkillLevelChanged(const FOnAttributeChangeData& Data)
{
	ESkillType* SkillPtr = SkillAttributeMap.Find(Data.Attribute);

	if (!SkillPtr) return;

	ESkillType Skill = *SkillPtr;

	float OldValue = Data.OldValue;
	float NewValue = Data.NewValue;

	if (NewValue > OldValue)
	{
		UE_LOG(LogTemp, Warning, TEXT("LEVEL UP: %s"),
			*USkillsAttributeSet::GetSkillName(Skill).ToString());
		
		OnSkillLevelChangedBP.Broadcast(Skill, OldValue, NewValue);
	}
}

void ARSCharacterBase::OnSkillXPChanged(const FOnAttributeChangeData& Data)
{
	if (!SkillAttributeMap.Contains(Data.Attribute)) return;

	const ESkillType Skill = SkillAttributeMap[Data.Attribute];
	
	UE_LOG(LogTemp, Warning, TEXT("XP: %s"),
	*USkillsAttributeSet::GetSkillName(Skill).ToString());

	OnSkillXPChangedBP.Broadcast(Skill, Data.OldValue, Data.NewValue);
}


void ARSCharacterBase::ServerSendGameplayEventToSelf_Implementation(FGameplayEventData EventData)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, EventData.EventTag, EventData);
}

