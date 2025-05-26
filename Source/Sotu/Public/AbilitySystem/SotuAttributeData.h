// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Engine/DataAsset.h"
#include "SotuAttributeData.generated.h"
/**
 * 
 */
UCLASS()
class SOTU_API USotuAttributeData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	TMap<FGameplayAttribute, float> Attributes;
};