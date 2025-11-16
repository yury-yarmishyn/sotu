// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/SotuGameplayAbility.h"

TSubclassOf<UGameplayEffect> USotuGameplayAbility::GetCooldownClass()
{
	return GetCooldownGameplayEffect()->GetClass();
}

const FGameplayTagContainer* USotuGameplayAbility::GetCooldownTags() const
{
	const FGameplayTagContainer* SuperTags = Super::GetCooldownTags();
	FGameplayEffectSpec* Spec = CooldownSpecHandle.IsValid() ? CooldownSpecHandle.Data.Get() : nullptr;

	if (Spec)
	{
		if (SuperTags)
		{
			Spec->DynamicGrantedTags.AppendTags(*SuperTags);
		}
		return &Spec->DynamicGrantedTags;
	}

	return SuperTags;
}

void USotuGameplayAbility::ApplyCooldown(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	if (CooldownSpecHandle.IsValid())
	{
		ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, CooldownSpecHandle);
	}
	else
	{
		return Super::ApplyCooldown(Handle, ActorInfo, ActivationInfo);
	}
}
