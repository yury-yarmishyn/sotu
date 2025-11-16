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

	if (Attribute == GetHealthAttribute() || Attribute == GetRallyAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, MaxHealth.GetCurrentValue());
	}
	else if (Attribute == GetStaminaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, MaxStamina.GetCurrentValue());
	}
}

void USotuAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	const FGameplayAttribute& Attribute = Data.EvaluatedData.Attribute;
	const float OldValue = Data.EvaluatedData.Magnitude;
	const float NewValue = Attribute.GetNumericValue(this);

	if (const USotuAbilitySystemComponent* SotuASC = Cast<USotuAbilitySystemComponent>(GetOwningAbilitySystemComponent()))
	{
		SotuASC->OnAttributeChanged.Broadcast(Attribute, OldValue, NewValue);
	}
}


