// AO_GameplayAbility_Sprint.cpp

#include "Character/GAS/Ability/AO_GameplayAbility_Sprint.h"

#include "AbilitySystemComponent.h"
#include "AO_Log.h"
#include "Character/AO_PlayerCharacter.h"
#include "Character/GAS/AO_PlayerCharacter_AttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"

UAO_GameplayAbility_Sprint::UAO_GameplayAbility_Sprint()
{
	const FGameplayTagContainer SprintTag(FGameplayTag::RequestGameplayTag(FName("Ability.Movement.Sprint")));
	SetAssetTags(SprintTag);

	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;

	ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Status.Action.Sprint")));
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Status.Lockout.Stamina")));
}

bool UAO_GameplayAbility_Sprint::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                    const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
                                                    const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	const UAO_PlayerCharacter_AttributeSet* AttributeSet = ActorInfo->AbilitySystemComponent->GetSet<UAO_PlayerCharacter_AttributeSet>();
	if (!AttributeSet)
	{
		AO_LOG(LogJM, Warning, TEXT("CanActive11111111111"));
		return false;
	}
	
	const float CurrentStamina = AttributeSet->GetStamina();
	const float MaxStamina = AttributeSet->GetMaxStamina();
	if (CurrentStamina < StaminaCost)
	{
		AO_LOG(LogJM, Warning, TEXT("CanActive222222222"));
		if (OptionalRelevantTags)
		{
			OptionalRelevantTags->AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Fail.NotEnoughStamina")));
		}
		return false;
	}

	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		AO_LOG(LogJM, Warning, TEXT("CanActive3333333333333"));
		FGameplayTagContainer OwnedTags;
		ActorInfo->AbilitySystemComponent->GetOwnedGameplayTags(OwnedTags);
		AO_LOG(LogJM, Warning, TEXT("CanActive3333 - 현재 보유 태그: %s"), *OwnedTags.ToStringSimple());
		
		return false;
	}

	if (!ActorInfo || !ActorInfo->AbilitySystemComponent.IsValid() || !ActorInfo->AvatarActor.IsValid())
	{
		AO_LOG(LogJM, Warning, TEXT("CanActive44444444444"));
		return false;
	}

	const AAO_PlayerCharacter* Character = Cast<AAO_PlayerCharacter>(ActorInfo->AvatarActor.Get());
	if (!Character)
	{
		AO_LOG(LogJM, Warning, TEXT("CanActive55555555555555"));
		return false;
	}

	const UCharacterMovementComponent* CharacterMovement = Character->GetCharacterMovement();
	if (!CharacterMovement)
	{
		AO_LOG(LogJM, Warning, TEXT("CanActive666666666666"));
		return false;
	}

	if (CharacterMovement->Velocity.SizeSquared2D() < KINDA_SMALL_NUMBER)
	{
		AO_LOG(LogJM, Warning, TEXT("CanActive7777"));
		return false;
	}

	if (CharacterMovement->IsCrouching())
	{
		AO_LOG(LogJM, Warning, TEXT("CanActive88888"));
		return false;
	}

	if (CurrentStamina < MaxStamina * AttributeSet->StaminaLockoutPercent)
	{
		AO_LOG(LogJM, Warning, TEXT("CanActive999999"));
		return false;
	}

	return true;
}

void UAO_GameplayAbility_Sprint::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                 const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                 const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	AAO_PlayerCharacter* Character = Cast<AAO_PlayerCharacter>(ActorInfo->AvatarActor.Get());
	if (!Character)
	{
		return;
	}
	
	Character->StartSprint_GAS(true);
}

void UAO_GameplayAbility_Sprint::InputPressed(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
	AO_LOG(LogJM,Warning,TEXT("ASC7777777777777"));
	const AAO_PlayerCharacter* Character = Cast<AAO_PlayerCharacter>(ActorInfo->AvatarActor.Get());
	if (!Character)
	{
		AO_LOG(LogJM,Warning,TEXT("ASC88888888888"));
		return;
	}

	const UCharacterMovementComponent* CharacterMovement = Character->GetCharacterMovement();
	if (!CharacterMovement)
	{
		AO_LOG(LogJM,Warning,TEXT("9999999999999"));
		return;
	}
	
	if (CharacterMovement->Velocity.SizeSquared2D() < KINDA_SMALL_NUMBER)
	{
		AO_LOG(LogJM,Warning,TEXT("101010101010"));
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	}
	
}

void UAO_GameplayAbility_Sprint::InputReleased(const FGameplayAbilitySpecHandle Handle,
                                               const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void UAO_GameplayAbility_Sprint::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                            bool bReplicateEndAbility, bool bWasCancelled)
{
	if (!IsActive())
	{
		return;
	}

	AAO_PlayerCharacter* Character = Cast<AAO_PlayerCharacter>(ActorInfo->AvatarActor.Get());
	if (!Character)
	{
		return;
	}

	if (Character)
	{
		Character->StartSprint_GAS(false);
	}

	UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();

	if (ASC)
	{
		const FGameplayTagContainer SprintCostTag(FGameplayTag::RequestGameplayTag(FName("Effect.Cost.Sprint")));
		ASC->RemoveActiveEffectsWithTags(SprintCostTag);

		checkf(PostSprintNoRegenEffectClass, TEXT("PostSprintNoRegenEffectClass is null"));
		if (ActorInfo->IsNetAuthority())
		{
			const FGameplayEffectContextHandle Context = ASC->MakeEffectContext();
			const FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(PostSprintNoRegenEffectClass, 1.f, Context);

			if (SpecHandle.IsValid())
			{
				ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			}
		}
	}
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}