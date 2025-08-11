// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AntlerTail/AntlerTailGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAntlerTailGameMode() {}

// Begin Cross Module References
ANTLERTAIL_API UClass* Z_Construct_UClass_AAntlerTailGameMode();
ANTLERTAIL_API UClass* Z_Construct_UClass_AAntlerTailGameMode_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
UPackage* Z_Construct_UPackage__Script_AntlerTail();
// End Cross Module References

// Begin Class AAntlerTailGameMode
void AAntlerTailGameMode::StaticRegisterNativesAAntlerTailGameMode()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AAntlerTailGameMode);
UClass* Z_Construct_UClass_AAntlerTailGameMode_NoRegister()
{
	return AAntlerTailGameMode::StaticClass();
}
struct Z_Construct_UClass_AAntlerTailGameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "AntlerTailGameMode.h" },
		{ "ModuleRelativePath", "AntlerTailGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AAntlerTailGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AAntlerTailGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_AntlerTail,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AAntlerTailGameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AAntlerTailGameMode_Statics::ClassParams = {
	&AAntlerTailGameMode::StaticClass,
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
	0x008802ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AAntlerTailGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_AAntlerTailGameMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AAntlerTailGameMode()
{
	if (!Z_Registration_Info_UClass_AAntlerTailGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AAntlerTailGameMode.OuterSingleton, Z_Construct_UClass_AAntlerTailGameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AAntlerTailGameMode.OuterSingleton;
}
template<> ANTLERTAIL_API UClass* StaticClass<AAntlerTailGameMode>()
{
	return AAntlerTailGameMode::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AAntlerTailGameMode);
AAntlerTailGameMode::~AAntlerTailGameMode() {}
// End Class AAntlerTailGameMode

// Begin Registration
struct Z_CompiledInDeferFile_FID_Work_Unreal_Projects_AntlerTail_AntlerTail_Source_AntlerTail_AntlerTailGameMode_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AAntlerTailGameMode, AAntlerTailGameMode::StaticClass, TEXT("AAntlerTailGameMode"), &Z_Registration_Info_UClass_AAntlerTailGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AAntlerTailGameMode), 3968057050U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Work_Unreal_Projects_AntlerTail_AntlerTail_Source_AntlerTail_AntlerTailGameMode_h_1554761698(TEXT("/Script/AntlerTail"),
	Z_CompiledInDeferFile_FID_Work_Unreal_Projects_AntlerTail_AntlerTail_Source_AntlerTail_AntlerTailGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Work_Unreal_Projects_AntlerTail_AntlerTail_Source_AntlerTail_AntlerTailGameMode_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
