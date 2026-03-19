// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/UW_Cutscene.h"

void UUW_Cutscene::SkipCutscene(bool SkipAll)
{
	if (!bCanBeSkip) 
	{
		return;
	}

	if (SkipAll)
	{
		OnEndCutsceneEvent.Broadcast(this);
		return;
	}
	SkipCutsceneFrame();
}
void UUW_Cutscene::EndCutscene()
{
	OnEndCutsceneEvent.Broadcast(this);

}