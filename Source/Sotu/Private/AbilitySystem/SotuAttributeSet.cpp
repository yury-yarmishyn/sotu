// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/SotuAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystem/SotuAbilitySystemComponent.h"

USotuAttributeSet::USotuAttributeSet()
{
	
}

void USotuAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void USotuAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	const FGameplayAttribute& Attribute = Data.EvaluatedData.Attribute;
	float OldValue = Data.EvaluatedData.Magnitude;
	float NewValue = Attribute.GetNumericValue(this);

	if (USotuAbilitySystemComponent* SotuASC = Cast<USotuAbilitySystemComponent>(GetOwningAbilitySystemComponent()))
	{
		SotuASC->OnAttributeChanged.Broadcast(Attribute, OldValue, NewValue);
	}
}

