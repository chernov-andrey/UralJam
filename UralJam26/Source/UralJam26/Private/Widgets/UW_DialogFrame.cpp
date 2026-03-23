// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/UW_DialogFrame.h"
#include "Components\Button.h"


void UUW_DialogFrame::NativeConstruct()
{
	check(OkayButton && " UUW_DialogFrame::NativeConstruct  -  OkayButton invalid");
	OkayButton->OnClicked.AddDynamic(this, &ThisClass::OnOkayButtonClicked);
	
	check(CancelButton&&" UUW_DialogFrame::NativeConstruct  -  CancelButton invalid");
	CancelButton->OnClicked.AddDynamic(this,&ThisClass::OnCancelButtonClicked);
	
	
}
void UUW_DialogFrame::OnOkayButtonClicked()
{
	OnReceivedAnswerEvent.Broadcast(true);
}
void UUW_DialogFrame::OnCancelButtonClicked()
{
	OnReceivedAnswerEvent.Broadcast(false);
}