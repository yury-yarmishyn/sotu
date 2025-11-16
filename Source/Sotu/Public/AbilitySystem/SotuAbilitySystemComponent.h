#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "SotuAbilitySystemComponent.generated.h"

struct FOnAttributeChangeData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChangedSignature, FGameplayAttribute, Attribute, float, OldValue, float, NewValue);

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Abilities), meta=(BlueprintSpawnableComponent))
class SOTU_API USotuAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	USotuAbilitySystemComponent();

	UPROPERTY(BlueprintAssignable, Category="Attributes")
	FOnAttributeChangedSignature OnAttributeChanged;

	UFUNCTION(BlueprintCallable, Category="Sotu|GAS|Tags")
	FGameplayTagContainer GetChildrenGameplayTags(const FGameplayTag ParentTag, bool bIncludeAllDescendants) const;

protected:
	virtual void BeginPlay() override;

	void HandleAttributeChanged(const FOnAttributeChangeData& Data) const;

	UFUNCTION(BlueprintCallable, Category="Abilities")
	void InitializeAbilitySystem();

	UFUNCTION(BlueprintCallable, Category="Attributes")
	void InitializeAttributeSet();
};