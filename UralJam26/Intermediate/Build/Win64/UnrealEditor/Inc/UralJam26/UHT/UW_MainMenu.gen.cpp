// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UralJam26/Public/UW_MainMenu.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeUW_MainMenu() {}

// Begin Cross Module References
UMG_API UClass* Z_Construct_UClass_UButton_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UPackage* Z_Construct_UPackage__Script_UralJam26();
URALJAM26_API UClass* Z_Construct_UClass_UUW_MainMenu();
URALJAM26_API UClass* Z_Construct_UClass_UUW_MainMenu_NoRegister();
// End Cross Module References

// Begin Class UUW_MainMenu Function OnExitGameButtonClicked
struct Z_Construct_UFunction_UUW_MainMenu_OnExitGameButtonClicked_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/UW_MainMenu.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UUW_MainMenu_OnExitGameButtonClicked_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UUW_MainMenu, nullptr, "OnExitGameButtonClicked", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UUW_MainMenu_OnExitGameButtonClicked_Statics::Function_MetaDataParams), Z_Construct_UFunction_UUW_MainMenu_OnExitGameButtonClicked_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UUW_MainMenu_OnExitGameButtonClicked()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UUW_MainMenu_OnExitGameButtonClicked_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UUW_MainMenu::execOnExitGameButtonClicked)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnExitGameButtonClicked();
	P_NATIVE_END;
}
// End Class UUW_MainMenu Function OnExitGameButtonClicked

// Begin Class UUW_MainMenu Function OnStartGameButtonClicked
struct Z_Construct_UFunction_UUW_MainMenu_OnStartGameButtonClicked_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/UW_MainMenu.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UUW_MainMenu_OnStartGameButtonClicked_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UUW_MainMenu, nullptr, "OnStartGameButtonClicked", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UUW_MainMenu_OnStartGameButtonClicked_Statics::Function_MetaDataParams), Z_Construct_UFunction_UUW_MainMenu_OnStartGameButtonClicked_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UUW_MainMenu_OnStartGameButtonClicked()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UUW_MainMenu_OnStartGameButtonClicked_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UUW_MainMenu::execOnStartGameButtonClicked)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnStartGameButtonClicked();
	P_NATIVE_END;
}
// End Class UUW_MainMenu Function OnStartGameButtonClicked

// Begin Class UUW_MainMenu
void UUW_MainMenu::StaticRegisterNativesUUW_MainMenu()
{
	UClass* Class = UUW_MainMenu::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "OnExitGameButtonClicked", &UUW_MainMenu::execOnExitGameButtonClicked },
		{ "OnStartGameButtonClicked", &UUW_MainMenu::execOnStartGameButtonClicked },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UUW_MainMenu);
UClass* Z_Construct_UClass_UUW_MainMenu_NoRegister()
{
	return UUW_MainMenu::StaticClass();
}
struct Z_Construct_UClass_UUW_MainMenu_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "UW_MainMenu.h" },
		{ "ModuleRelativePath", "Public/UW_MainMenu.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StartGameButton_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UW_MainMenu.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ExitGameButton_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UW_MainMenu.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_StartGameButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ExitGameButton;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UUW_MainMenu_OnExitGameButtonClicked, "OnExitGameButtonClicked" }, // 2977926070
		{ &Z_Construct_UFunction_UUW_MainMenu_OnStartGameButtonClicked, "OnStartGameButtonClicked" }, // 3071150239
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UUW_MainMenu>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UUW_MainMenu_Statics::NewProp_StartGameButton = { "StartGameButton", nullptr, (EPropertyFlags)0x0020080000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UUW_MainMenu, StartGameButton), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StartGameButton_MetaData), NewProp_StartGameButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UUW_MainMenu_Statics::NewProp_ExitGameButton = { "ExitGameButton", nullptr, (EPropertyFlags)0x0020080000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UUW_MainMenu, ExitGameButton), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ExitGameButton_MetaData), NewProp_ExitGameButton_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UUW_MainMenu_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UUW_MainMenu_Statics::NewProp_StartGameButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UUW_MainMenu_Statics::NewProp_ExitGameButton,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UUW_MainMenu_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UUW_MainMenu_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UUserWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_UralJam26,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UUW_MainMenu_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UUW_MainMenu_Statics::ClassParams = {
	&UUW_MainMenu::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UUW_MainMenu_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UUW_MainMenu_Statics::PropPointers),
	0,
	0x00B010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UUW_MainMenu_Statics::Class_MetaDataParams), Z_Construct_UClass_UUW_MainMenu_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UUW_MainMenu()
{
	if (!Z_Registration_Info_UClass_UUW_MainMenu.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UUW_MainMenu.OuterSingleton, Z_Construct_UClass_UUW_MainMenu_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UUW_MainMenu.OuterSingleton;
}
template<> URALJAM26_API UClass* StaticClass<UUW_MainMenu>()
{
	return UUW_MainMenu::StaticClass();
}
UUW_MainMenu::UUW_MainMenu(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UUW_MainMenu);
UUW_MainMenu::~UUW_MainMenu() {}
// End Class UUW_MainMenu

// Begin Registration
struct Z_CompiledInDeferFile_FID_Create_Jame_UralJam_UralJam26_Source_UralJam26_Public_UW_MainMenu_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UUW_MainMenu, UUW_MainMenu::StaticClass, TEXT("UUW_MainMenu"), &Z_Registration_Info_UClass_UUW_MainMenu, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UUW_MainMenu), 351161852U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Create_Jame_UralJam_UralJam26_Source_UralJam26_Public_UW_MainMenu_h_2309284521(TEXT("/Script/UralJam26"),
	Z_CompiledInDeferFile_FID_Create_Jame_UralJam_UralJam26_Source_UralJam26_Public_UW_MainMenu_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Create_Jame_UralJam_UralJam26_Source_UralJam26_Public_UW_MainMenu_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
