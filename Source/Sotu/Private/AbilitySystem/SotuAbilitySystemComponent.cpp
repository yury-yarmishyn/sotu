#include "AbilitySystem/SotuAbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "GameplayEffectTypes.h"

USotuAbilitySystemComponent::USotuAbilitySystemComponent()
{
	AttributeSet = CreateDefaultSubobject<USotuAttributeSet>(TEXT("AttributeSet"));
	AddAttributeSetSubobject(AttributeSet.Get());
}

void USotuAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeAbilitySystem(GetOwner(), GetOwner());
	InitializeAttributes(AttributeSet.Get(), AttributeData.Get());
	InitializeGameplayAbilities(DefaultAbilities);
}

void USotuAbilitySystemComponent::InitializeAbilitySystem(AActor* InOwnerActor, AActor* InAvatarActor)
{
	if (!InOwnerActor || !InAvatarActor) return;
	InitAbilityActorInfo(InOwnerActor, InAvatarActor);
}

void USotuAbilitySystemComponent::InitializeAttributes(USotuAttributeSet* InAttributeSet, USotuAttributeData* InAttributeData)
{
	if (!InAttributeSet || !InAttributeData) return;

	for (const TPair<FGameplayAttribute, float>& Pair : InAttributeData->Attributes)
	{
		if (Pair.Key.IsValid())
		{
			GetGameplayAttributeValueChangeDelegate(Pair.Key).AddUObject(this, &USotuAbilitySystemComponent::HandleAttributeChanged);
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