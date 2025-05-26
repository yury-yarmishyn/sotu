// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/SotuAbilitySystemComponent.h"


USotuAbilitySystemComponent::USotuAbilitySystemComponent()
{
	
}

void USotuAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeAbilitySystemComponent();
	InitializeAttributes();
}

void USotuAbilitySystemComponent::InitializeAttributes()
{
	if (!AttributeData) return;
	
	USotuAttributeSet* AttributeSet = NewObject<USotuAttributeSet>(GetOwner());
	AddAttributeSetSubobject(AttributeSet);

	for (const TPair<FGameplayAttribute, float>& Attribute : AttributeData->Attributes)
	{
		if (Attribute.Key.IsValid())
		{
			SetNumericAttributeBase(Attribute.Key, Attribute.Value);
		}
	}
}

void USotuAbilitySystemComponent::InitializeAbilitySystemComponent()
{
	if (!GetOwner()) return;
	
	InitAbilityActorInfo(GetOwner(), GetOwner());
}
