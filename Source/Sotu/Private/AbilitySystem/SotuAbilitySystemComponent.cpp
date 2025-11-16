#include "AbilitySystem/SotuAbilitySystemComponent.h"
#include "GameplayTagsManager.h"
#include "AbilitySystem/SotuAttributeSet.h"

USotuAbilitySystemComponent::USotuAbilitySystemComponent()
{
}

FGameplayTagContainer USotuAbilitySystemComponent::GetChildrenGameplayTags(const FGameplayTag ParentTag,
	bool bIncludeAllDescendants) const
{
	FGameplayTagContainer Result;

	if (!ParentTag.IsValid())
	{
		return Result;
	}

	const UGameplayTagsManager& Manager = UGameplayTagsManager::Get();

	if (bIncludeAllDescendants)
	{
		Result = Manager.RequestGameplayTagChildren(ParentTag);
		return Result;
	}
	
	const TSharedPtr<FGameplayTagNode> Node = Manager.FindTagNode(ParentTag);
	if (!Node.IsValid())
	{
		return Result;
	}

	const TArray<TSharedPtr<FGameplayTagNode>>& Children = Node->GetChildTagNodes();
	for (const TSharedPtr<FGameplayTagNode>& ChildNode : Children)
	{
		if (ChildNode.IsValid())
		{
			Result.AddTag(ChildNode->GetCompleteTag());
		}
	}

	return Result;
}

void USotuAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USotuAbilitySystemComponent::InitializeAbilitySystem()
{
	if (!GetOwner()) return;
	InitAbilityActorInfo(GetOwner(), GetOwner());
}

void USotuAbilitySystemComponent::InitializeAttributeSet()
{
	USotuAttributeSet* AttributeSet = NewObject<USotuAttributeSet>(GetOwner());
	if (!AttributeSet) return;
	AddAttributeSetSubobject(AttributeSet);
}

void USotuAbilitySystemComponent::HandleAttributeChanged(const FOnAttributeChangeData& Data) const
{
	OnAttributeChanged.Broadcast(Data.Attribute, Data.OldValue, Data.NewValue);
}