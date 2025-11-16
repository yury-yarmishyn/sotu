// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "SotuGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class SOTU_API USotuGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ability")
	FGameplayEffectSpecHandle CooldownSpecHandle;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ability")
	TSubclassOf<UGameplayEffect> GetCooldownClass();

protected:
	virtual const FGameplayTagContainer* GetCooldownTags() const override;
	virtual void ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;
};
