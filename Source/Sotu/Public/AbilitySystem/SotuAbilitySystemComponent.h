// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "SotuAttributeData.h"
#include "SotuAttributeSet.h"
#include "SotuAbilitySystemComponent.generated.h"
/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChangedSignature, FGameplayAttribute, Attribute, float, OldValue, float, NewValue);

UCLASS(Blueprintable, BlueprintType)
class SOTU_API USotuAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	USotuAbilitySystemComponent();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	TObjectPtr<USotuAttributeData> AttributeData;

	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnAttributeChangedSignature OnAttributeChanged;

protected:
	virtual void BeginPlay() override;
	void InitializeAttributes();
	void InitializeAbilitySystemComponent();
};
