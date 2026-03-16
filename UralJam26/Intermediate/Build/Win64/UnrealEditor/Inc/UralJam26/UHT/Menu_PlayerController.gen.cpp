// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UralJam26/Public/Menu_PlayerController.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMenu_PlayerController() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_APlayerController();
UPackage* Z_Construct_UPackage__Script_UralJam26();
URALJAM26_API UClass* Z_Construct_UClass_AMenu_PlayerController();
URALJAM26_API UClass* Z_Construct_UClass_AMenu_PlayerController_NoRegister();
// End Cross Module References

// Begin Class AMenu_PlayerController
void AMenu_PlayerController::StaticRegisterNativesAMenu_PlayerController()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AMenu_PlayerController);
UClass* Z_Construct_UClass_AMenu_PlayerController_NoRegister()
{
	return AMenu_PlayerController::StaticClass();
}
struct Z_Construct_UClass_AMenu_PlayerController_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "Menu_PlayerController.h" },
		{ "ModuleRelativePath", "Public/Menu_PlayerController.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMenu_PlayerController>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AMenu_PlayerController_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_APlayerController,
	(UObject* (*)())Z_Construct_UPackage__Script_UralJam26,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMenu_PlayerController_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AMenu_PlayerController_Statics::ClassParams = {
	&AMenu_PlayerController::StaticClass,
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
	0x009002A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AMenu_PlayerController_Statics::Class_MetaDataParams), Z_Construct_UClass_AMenu_PlayerController_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AMenu_PlayerController()
{
	if (!Z_Registration_Info_UClass_AMenu_PlayerController.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AMenu_PlayerController.OuterSingleton, Z_Construct_UClass_AMenu_PlayerController_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AMenu_PlayerController.OuterSingleton;
}
template<> URALJAM26_API UClass* StaticClass<AMenu_PlayerController>()
{
	return AMenu_PlayerController::StaticClass();
}
AMenu_PlayerController::AMenu_PlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(AMenu_PlayerController);
AMenu_PlayerController::~AMenu_PlayerController() {}
// End Class AMenu_PlayerController

// Begin Registration
struct Z_CompiledInDeferFile_FID_Create_Jame_UralJam_UralJam26_Source_UralJam26_Public_Menu_PlayerController_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AMenu_PlayerController, AMenu_PlayerController::StaticClass, TEXT("AMenu_PlayerController"), &Z_Registration_Info_UClass_AMenu_PlayerController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMenu_PlayerController), 1880287467U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Create_Jame_UralJam_UralJam26_Source_UralJam26_Public_Menu_PlayerController_h_4010740574(TEXT("/Script/UralJam26"),
	Z_CompiledInDeferFile_FID_Create_Jame_UralJam_UralJam26_Source_UralJam26_Public_Menu_PlayerController_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Create_Jame_UralJam_UralJam26_Source_UralJam26_Public_Menu_PlayerController_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
