// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UralJam26/Public/UralJam_GameInstance.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeUralJam_GameInstance() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_UGameInstance();
UPackage* Z_Construct_UPackage__Script_UralJam26();
URALJAM26_API UClass* Z_Construct_UClass_UUralJam_GameInstance();
URALJAM26_API UClass* Z_Construct_UClass_UUralJam_GameInstance_NoRegister();
// End Cross Module References

// Begin Class UUralJam_GameInstance Function StartGame
struct Z_Construct_UFunction_UUralJam_GameInstance_StartGame_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Game" },
		{ "ModuleRelativePath", "Public/UralJam_GameInstance.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UUralJam_GameInstance_StartGame_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UUralJam_GameInstance, nullptr, "StartGame", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UUralJam_GameInstance_StartGame_Statics::Function_MetaDataParams), Z_Construct_UFunction_UUralJam_GameInstance_StartGame_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UUralJam_GameInstance_StartGame()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UUralJam_GameInstance_StartGame_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UUralJam_GameInstance::execStartGame)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->StartGame();
	P_NATIVE_END;
}
// End Class UUralJam_GameInstance Function StartGame

// Begin Class UUralJam_GameInstance
void UUralJam_GameInstance::StaticRegisterNativesUUralJam_GameInstance()
{
	UClass* Class = UUralJam_GameInstance::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "StartGame", &UUralJam_GameInstance::execStartGame },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UUralJam_GameInstance);
UClass* Z_Construct_UClass_UUralJam_GameInstance_NoRegister()
{
	return UUralJam_GameInstance::StaticClass();
}
struct Z_Construct_UClass_UUralJam_GameInstance_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "UralJam_GameInstance.h" },
		{ "ModuleRelativePath", "Public/UralJam_GameInstance.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LevelName_MetaData[] = {
		{ "Category", "Game" },
		{ "ModuleRelativePath", "Public/UralJam_GameInstance.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FNamePropertyParams NewProp_LevelName;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UUralJam_GameInstance_StartGame, "StartGame" }, // 754510430
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UUralJam_GameInstance>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FNamePropertyParams Z_Construct_UClass_UUralJam_GameInstance_Statics::NewProp_LevelName = { "LevelName", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UUralJam_GameInstance, LevelName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LevelName_MetaData), NewProp_LevelName_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UUralJam_GameInstance_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UUralJam_GameInstance_Statics::NewProp_LevelName,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UUralJam_GameInstance_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UUralJam_GameInstance_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UGameInstance,
	(UObject* (*)())Z_Construct_UPackage__Script_UralJam26,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UUralJam_GameInstance_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UUralJam_GameInstance_Statics::ClassParams = {
	&UUralJam_GameInstance::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UUralJam_GameInstance_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UUralJam_GameInstance_Statics::PropPointers),
	0,
	0x009000A8u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UUralJam_GameInstance_Statics::Class_MetaDataParams), Z_Construct_UClass_UUralJam_GameInstance_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UUralJam_GameInstance()
{
	if (!Z_Registration_Info_UClass_UUralJam_GameInstance.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UUralJam_GameInstance.OuterSingleton, Z_Construct_UClass_UUralJam_GameInstance_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UUralJam_GameInstance.OuterSingleton;
}
template<> URALJAM26_API UClass* StaticClass<UUralJam_GameInstance>()
{
	return UUralJam_GameInstance::StaticClass();
}
UUralJam_GameInstance::UUralJam_GameInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UUralJam_GameInstance);
UUralJam_GameInstance::~UUralJam_GameInstance() {}
// End Class UUralJam_GameInstance

// Begin Registration
struct Z_CompiledInDeferFile_FID_Create_Jame_UralJam_UralJam26_Source_UralJam26_Public_UralJam_GameInstance_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UUralJam_GameInstance, UUralJam_GameInstance::StaticClass, TEXT("UUralJam_GameInstance"), &Z_Registration_Info_UClass_UUralJam_GameInstance, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UUralJam_GameInstance), 3526864775U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Create_Jame_UralJam_UralJam26_Source_UralJam26_Public_UralJam_GameInstance_h_232103932(TEXT("/Script/UralJam26"),
	Z_CompiledInDeferFile_FID_Create_Jame_UralJam_UralJam26_Source_UralJam26_Public_UralJam_GameInstance_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Create_Jame_UralJam_UralJam26_Source_UralJam26_Public_UralJam_GameInstance_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
