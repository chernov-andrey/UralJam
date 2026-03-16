// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UralJam26/Public/Game_PlayerController.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGame_PlayerController() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_APlayerController();
UPackage* Z_Construct_UPackage__Script_UralJam26();
URALJAM26_API UClass* Z_Construct_UClass_AGame_PlayerController();
URALJAM26_API UClass* Z_Construct_UClass_AGame_PlayerController_NoRegister();
// End Cross Module References

// Begin Class AGame_PlayerController
void AGame_PlayerController::StaticRegisterNativesAGame_PlayerController()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AGame_PlayerController);
UClass* Z_Construct_UClass_AGame_PlayerController_NoRegister()
{
	return AGame_PlayerController::StaticClass();
}
struct Z_Construct_UClass_AGame_PlayerController_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "Game_PlayerController.h" },
		{ "ModuleRelativePath", "Public/Game_PlayerController.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AGame_PlayerController>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AGame_PlayerController_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_APlayerController,
	(UObject* (*)())Z_Construct_UPackage__Script_UralJam26,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AGame_PlayerController_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AGame_PlayerController_Statics::ClassParams = {
	&AGame_PlayerController::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AGame_PlayerController_Statics::Class_MetaDataParams), Z_Construct_UClass_AGame_PlayerController_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AGame_PlayerController()
{
	if (!Z_Registration_Info_UClass_AGame_PlayerController.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AGame_PlayerController.OuterSingleton, Z_Construct_UClass_AGame_PlayerController_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AGame_PlayerController.OuterSingleton;
}
template<> URALJAM26_API UClass* StaticClass<AGame_PlayerController>()
{
	return AGame_PlayerController::StaticClass();
}
AGame_PlayerController::AGame_PlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(AGame_PlayerController);
AGame_PlayerController::~AGame_PlayerController() {}
// End Class AGame_PlayerController

// Begin Registration
struct Z_CompiledInDeferFile_FID_Create_Jame_UralJam_UralJam26_Source_UralJam26_Public_Game_PlayerController_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AGame_PlayerController, AGame_PlayerController::StaticClass, TEXT("AGame_PlayerController"), &Z_Registration_Info_UClass_AGame_PlayerController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AGame_PlayerController), 1688826434U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Create_Jame_UralJam_UralJam26_Source_UralJam26_Public_Game_PlayerController_h_349967910(TEXT("/Script/UralJam26"),
	Z_CompiledInDeferFile_FID_Create_Jame_UralJam_UralJam26_Source_UralJam26_Public_Game_PlayerController_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Create_Jame_UralJam_UralJam26_Source_UralJam26_Public_Game_PlayerController_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
