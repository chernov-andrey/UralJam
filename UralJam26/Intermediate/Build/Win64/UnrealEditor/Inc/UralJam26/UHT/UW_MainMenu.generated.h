// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "UW_MainMenu.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef URALJAM26_UW_MainMenu_generated_h
#error "UW_MainMenu.generated.h already included, missing '#pragma once' in UW_MainMenu.h"
#endif
#define URALJAM26_UW_MainMenu_generated_h

#define FID_UralGameJam_UralJam26_Source_UralJam26_Public_UW_MainMenu_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execOnExitGameButtonClicked); \
	DECLARE_FUNCTION(execOnStartGameButtonClicked);


#define FID_UralGameJam_UralJam26_Source_UralJam26_Public_UW_MainMenu_h_17_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUUW_MainMenu(); \
	friend struct Z_Construct_UClass_UUW_MainMenu_Statics; \
public: \
	DECLARE_CLASS(UUW_MainMenu, UUserWidget, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/UralJam26"), NO_API) \
	DECLARE_SERIALIZER(UUW_MainMenu)


#define FID_UralGameJam_UralJam26_Source_UralJam26_Public_UW_MainMenu_h_17_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UUW_MainMenu(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UUW_MainMenu(UUW_MainMenu&&); \
	UUW_MainMenu(const UUW_MainMenu&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UUW_MainMenu); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UUW_MainMenu); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UUW_MainMenu) \
	NO_API virtual ~UUW_MainMenu();


#define FID_UralGameJam_UralJam26_Source_UralJam26_Public_UW_MainMenu_h_14_PROLOG
#define FID_UralGameJam_UralJam26_Source_UralJam26_Public_UW_MainMenu_h_17_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_UralGameJam_UralJam26_Source_UralJam26_Public_UW_MainMenu_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_UralGameJam_UralJam26_Source_UralJam26_Public_UW_MainMenu_h_17_INCLASS_NO_PURE_DECLS \
	FID_UralGameJam_UralJam26_Source_UralJam26_Public_UW_MainMenu_h_17_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> URALJAM26_API UClass* StaticClass<class UUW_MainMenu>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_UralGameJam_UralJam26_Source_UralJam26_Public_UW_MainMenu_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
