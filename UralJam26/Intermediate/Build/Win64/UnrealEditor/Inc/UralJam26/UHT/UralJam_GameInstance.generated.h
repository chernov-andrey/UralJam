// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "UralJam_GameInstance.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef URALJAM26_UralJam_GameInstance_generated_h
#error "UralJam_GameInstance.generated.h already included, missing '#pragma once' in UralJam_GameInstance.h"
#endif
#define URALJAM26_UralJam_GameInstance_generated_h

#define FID_UralGameJam_UralJam26_Source_UralJam26_Public_UralJam_GameInstance_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execStartGame);


#define FID_UralGameJam_UralJam26_Source_UralJam26_Public_UralJam_GameInstance_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUUralJam_GameInstance(); \
	friend struct Z_Construct_UClass_UUralJam_GameInstance_Statics; \
public: \
	DECLARE_CLASS(UUralJam_GameInstance, UGameInstance, COMPILED_IN_FLAGS(0 | CLASS_Transient), CASTCLASS_None, TEXT("/Script/UralJam26"), NO_API) \
	DECLARE_SERIALIZER(UUralJam_GameInstance)


#define FID_UralGameJam_UralJam26_Source_UralJam26_Public_UralJam_GameInstance_h_16_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UUralJam_GameInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UUralJam_GameInstance(UUralJam_GameInstance&&); \
	UUralJam_GameInstance(const UUralJam_GameInstance&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UUralJam_GameInstance); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UUralJam_GameInstance); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UUralJam_GameInstance) \
	NO_API virtual ~UUralJam_GameInstance();


#define FID_UralGameJam_UralJam26_Source_UralJam26_Public_UralJam_GameInstance_h_13_PROLOG
#define FID_UralGameJam_UralJam26_Source_UralJam26_Public_UralJam_GameInstance_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_UralGameJam_UralJam26_Source_UralJam26_Public_UralJam_GameInstance_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_UralGameJam_UralJam26_Source_UralJam26_Public_UralJam_GameInstance_h_16_INCLASS_NO_PURE_DECLS \
	FID_UralGameJam_UralJam26_Source_UralJam26_Public_UralJam_GameInstance_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> URALJAM26_API UClass* StaticClass<class UUralJam_GameInstance>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_UralGameJam_UralJam26_Source_UralJam26_Public_UralJam_GameInstance_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
