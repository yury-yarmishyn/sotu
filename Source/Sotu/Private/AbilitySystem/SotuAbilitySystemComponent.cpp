#include "AbilitySystem/SotuAbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbilitySpec.h"
#include "GameplayEffectTypes.h"
#include "AttributeSet.h"

USotuAbilitySystemComponent::USotuAbilitySystemComponent()
{
}

void USotuAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeAbilitySystem(GetOwner(), GetOwner());
	InitializeAttributeSets(AttributeSetClasses);
	InitializeAttributes(AttributeData.Get());
	InitializeGameplayAbilities(DefaultAbilities);
}

void USotuAbilitySystemComponent::InitializeAbilitySystem(AActor* InOwnerActor, AActor* InAvatarActor)
{
	if (!InOwnerActor || !InAvatarActor) return;
	InitAbilityActorInfo(InOwnerActor, InAvatarActor);
}

void USotuAbilitySystemComponent::InitializeAttributeSets(const TArray<TSubclassOf<UAttributeSet>>& InAttributeSetClasses)
{
	for (TSubclassOf<UAttributeSet> SetClass : InAttributeSetClasses)
	{
		if (!SetClass) continue;
		UAttributeSet* SetInstance = NewObject<UAttributeSet>(GetOwner(), SetClass);
		if (!SetInstance) continue;
		AddAttributeSetSubobject(SetInstance);
	}
}

void USotuAbilitySystemComponent::InitializeAttributes(USotuAttributeData* InAttributeData)
{
	if (!InAttributeData) return;

	for (const TPair<FGameplayAttribute, float>& Pair : InAttributeData->Attributes)
	{
		if (Pair.Key.IsValid())
		{
			GetGameplayAttributeValueChangeDelegate(Pair.Key)
				.AddUObject(this, &USotuAbilitySystemComponent::HandleAttributeChanged);
		}
	}

	for (const TPair<FGameplayAttribute, float>& Pair : InAttributeData->Attributes)
	{
		if (Pair.Key.IsValid())
		{
			SetNumericAttributeBase(Pair.Key, Pair.Value);
		}
	}
}

void USotuAbilitySystemComponent::InitializeGameplayAbilities(const TArray<TSubclassOf<UGameplayAbility>>& InDefaultAbilities)
{
	for (TSubclassOf<UGameplayAbility> AbilityClass : InDefaultAbilities)
	{
		if (!AbilityClass) continue;
		if (FindAbilitySpecFromClass(AbilityClass) != nullptr) continue;

		FGameplayAbilitySpec Spec(AbilityClass, 1, INDEX_NONE, this);
		GiveAbility(Spec);
	}
}

void USotuAbilitySystemComponent::HandleAttributeChanged(const FOnAttributeChangeData& Data)
{
	OnAttributeChanged.Broadcast(Data.Attribute, Data.OldValue, Data.NewValue);
}
