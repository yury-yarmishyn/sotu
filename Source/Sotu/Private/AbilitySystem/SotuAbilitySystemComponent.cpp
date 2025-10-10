#include "AbilitySystem/SotuAbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbilitySpec.h"
#include "GameplayEffectTypes.h"
#include "AttributeSet.h"

USotuAbilitySystemComponent::USotuAbilitySystemComponent()
{
}

void USotuAbilitySystemComponent::CancelAbilitiesWithTags(const FGameplayTagContainer& WithTags, const FGameplayTagContainer& WithoutTags)
{
	FGameplayTagContainer WithTagsCopy = WithTags;
	FGameplayTagContainer WithoutTagsCopy = WithoutTags;

	if (WithTagsCopy.IsEmpty() && WithoutTagsCopy.IsEmpty())
	{
		return;
	}

	CancelAbilities(
		WithTagsCopy.IsEmpty() ? nullptr : &WithTagsCopy,
		WithoutTagsCopy.IsEmpty() ? nullptr : &WithoutTagsCopy,
		nullptr
	);
}

void USotuAbilitySystemComponent::ClearAbilityWithClass(TSubclassOf<UGameplayAbility> AbilityClass)
{
	for (int32 Index = 0; Index < DefaultAbilities.Num(); ++Index)
	{
		if (!AbilityClass) continue;
		if (FindAbilitySpecFromClass(AbilityClass) != nullptr) continue;

		FGameplayAbilitySpec Spec(AbilityClass);
		ClearAbility(Spec.Handle);
	}
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
	for (int32 Index = 0; Index < InDefaultAbilities.Num(); ++Index)
	{
		TSubclassOf<UGameplayAbility> AbilityClass = InDefaultAbilities[Index];
		if (!AbilityClass) continue;
		if (FindAbilitySpecFromClass(AbilityClass) != nullptr) continue;

		FGameplayAbilitySpec Spec(AbilityClass, 1, Index, this);
		GiveAbility(Spec);
	}
}

void USotuAbilitySystemComponent::HandleAttributeChanged(const FOnAttributeChangeData& Data)
{
	OnAttributeChanged.Broadcast(Data.Attribute, Data.OldValue, Data.NewValue);
}
