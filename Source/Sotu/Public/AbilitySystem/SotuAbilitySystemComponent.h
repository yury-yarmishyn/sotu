#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "SotuAttributeData.h"
#include "SotuAbilitySystemComponent.generated.h"

struct FOnAttributeChangeData;
class UGameplayAbility;
class UAttributeSet;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChangedSignature, FGameplayAttribute, Attribute, float, OldValue, float, NewValue);

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Abilities), meta=(BlueprintSpawnableComponent))
class SOTU_API USotuAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	USotuAbilitySystemComponent();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	TObjectPtr<USotuAttributeData> AttributeData = nullptr;

	UPROPERTY(BlueprintAssignable, Category="Attributes")
	FOnAttributeChangedSignature OnAttributeChanged;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
	TArray<TSubclassOf<UAttributeSet>> AttributeSetClasses;

	UFUNCTION(BlueprintCallable, Category="GAS|Cancel")
	void CancelAbilitiesWithTags(const FGameplayTagContainer& WithTags, const FGameplayTagContainer& WithoutTags);

	UFUNCTION(BlueprintCallable, Category="GAS|Cancel")
	void ClearAbilityWithClass(TSubclassOf<UGameplayAbility> AbilityClass);

protected:
	virtual void BeginPlay() override;

	void HandleAttributeChanged(const FOnAttributeChangeData& Data);
	void InitializeAbilitySystem(AActor* InOwnerActor, AActor* InAvatarActor);
	void InitializeAttributeSets(const TArray<TSubclassOf<UAttributeSet>>& InAttributeSetClasses);
	void InitializeAttributes(USotuAttributeData* InAttributeData);
	void InitializeGameplayAbilities(const TArray<TSubclassOf<UGameplayAbility>>& InDefaultAbilities);
};