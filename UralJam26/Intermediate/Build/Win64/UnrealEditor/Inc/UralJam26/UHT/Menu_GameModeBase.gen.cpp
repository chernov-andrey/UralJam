// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UralJam26/Public/Menu_GameModeBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMenu_GameModeBase() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
UPackage* Z_Construct_UPackage__Script_UralJam26();
URALJAM26_API UClass* Z_Construct_UClass_AMenu_GameModeBase();
URALJAM26_API UClass* Z_Construct_UClass_AMenu_GameModeBase_NoRegister();
// End Cross Module References

// Begin Class AMenu_GameModeBase
void AMenu_GameModeBase::StaticRegisterNativesAMenu_GameModeBase()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AMenu_GameModeBase);
UClass* Z_Construct_UClass_AMenu_GameModeBase_NoRegister()
{
	return AMenu_GameModeBase::StaticClass();
}
struct Z_Construct_UClass_AMenu_GameModeBase_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "Menu_GameModeBase.h" },
		{ "ModuleRelativePath", "Public/Menu_GameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMenu_GameModeBase>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AMenu_GameModeBase_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_UralJam26,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMenu_GameModeBase_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AMenu_GameModeBase_Statics::ClassParams = {
	&AMenu_GameModeBase::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x009002ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AMenu_GameModeBase_Statics::Class_MetaDataParams), Z_Construct_UClass_AMenu_GameModeBase_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AMenu_GameModeBase()
{
	if (!Z_Registration_Info_UClass_AMenu_GameModeBase.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AMenu_GameModeBase.OuterSingleton, Z_Construct_UClass_AMenu_GameModeBase_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AMenu_GameModeBase.OuterSingleton;
}
template<> URALJAM26_API UClass* StaticClass<AMenu_GameModeBase>()
{
	return AMenu_GameModeBase::StaticClass();
}
AMenu_GameModeBase::AMenu_GameModeBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(AMenu_GameModeBase);
AMenu_GameModeBase::~AMenu_GameModeBase() {}
// End Class AMenu_GameModeBase

// Begin Registration
struct Z_CompiledInDeferFile_FID_UralGameJam_UralJam26_Source_UralJam26_Public_Menu_GameModeBase_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AMenu_GameModeBase, AMenu_GameModeBase::StaticClass, TEXT("AMenu_GameModeBase"), &Z_Registration_Info_UClass_AMenu_GameModeBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMenu_GameModeBase), 4153550313U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UralGameJam_UralJam26_Source_UralJam26_Public_Menu_GameModeBase_h_2932186310(TEXT("/Script/UralJam26"),
	Z_CompiledInDeferFile_FID_UralGameJam_UralJam26_Source_UralJam26_Public_Menu_GameModeBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UralGameJam_UralJam26_Source_UralJam26_Public_Menu_GameModeBase_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
