#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "SotuAttributeData.h"
#include "SotuAttributeSet.h"
#include "SotuAbilitySystemComponent.generated.h"

struct FOnAttributeChangeData;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Attributes")
	TObjectPtr<USotuAttributeSet> AttributeSet = nullptr;

protected:
	virtual void BeginPlay() override;

	void HandleAttributeChanged(const FOnAttributeChangeData& Data);
	void InitializeAttributes(USotuAttributeSet* InAttributeSet, USotuAttributeData* InAttributeData);
	void InitializeGameplayAbilities(const TArray<TSubclassOf<UGameplayAbility>>& InDefaultAbilities);

private:
	void InitializeAbilitySystem(AActor* InOwnerActor, AActor* InAvatarActor);
};