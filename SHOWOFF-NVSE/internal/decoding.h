#pragma once
#include "GameBSExtraData.h"
#include "GameForms.h"
#include "GameObjects.h"
#include "GameTasks.h"
#include "GameTiles.h"
#include "netimmerse.h"
#include "NiPoint.h"
#include "GameUI.h"
#include "havok.h"
#include "GameAPI.h"

// Credits: JIPLN, lStewieAl, JG, and surely others.

//#if 0
class BSGameSound;
class NiBSBoneLODController;
class NiBSplineCompTransformInterpolator;
struct CombatTarget;
struct BGSSaveLoadFileEntry;
class Sky;
class BSTempNodeManager;
class CombatProcedure;
class CombatAction;
class CombatGoal;
class PathingLocation;
class PathingCoverLocation;
struct UnreachableLocation;
struct UnreachableCoverLocation;
class BSAudioManagerThread;
class ImageSpaceModifierInstanceRB;
struct NavMeshClosedDoorInfo;
//#endif

static constexpr UInt32 MergeScriptEventAddr = 0x5AC750;

enum ActorValueCode
{
	kAVCode_Aggression,
	kAVCode_Confidence,
	kAVCode_Energy,
	kAVCode_Responsibility,
	kAVCode_Mood,

	//SPECIAL begin
	kAVCode_Strength,
	kAVCode_Perception,
	kAVCode_Endurance,
	kAVCode_Charisma,
	kAVCode_Intelligence,
	kAVCode_Agility,
	kAVCode_Luck,
	//SPECIAL end

	kAVCode_ActionPoints,
	kAVCode_CarryWeight,
	kAVCode_CritChance,
	kAVCode_HealRate,
	kAVCode_Health,
	kAVCode_MeleeDamage,
	kAVCode_DamageResist,
	kAVCode_PoisonResist,
	kAVCode_RadResist,
	kAVCode_SpeedMult,
	kAVCode_Fatigue,
	kAVCode_Karma,
	kAVCode_XP,
	kAVCode_PerceptionCondition,
	kAVCode_EnduranceCondition,
	kAVCode_LeftAttackCondition,
	kAVCode_RightAttackCondition,
	kAVCode_LeftMobilityCondition,
	kAVCode_RightMobilityCondition,
	kAVCode_BrainCondition,

	//skills begin
	kAVCode_Barter,
	kAVCode_BigGuns,
	kAVCode_EnergyWeapons,
	kAVCode_Explosives,
	kAVCode_Lockpick,
	kAVCode_Medicine,
	kAVCode_MeleeWeapons,
	kAVCode_Repair,
	kAVCode_Science,
	kAVCode_Guns,
	kAVCode_Sneak,
	kAVCode_Speech,
	kAVCode_Survival,
	kAVCode_Unarmed,
	// skills end

	kAVCode_InventoryWeight,
	kAVCode_Paralysis,
	kAVCode_Invisibility,
	kAVCode_Chameleon,
	kAVCode_NightEye,
	kAVCode_Turbo,
	kAVCode_FireResist,
	kAVCode_WaterBreathing,
	kAVCode_RadiationRads,
	kAVCode_BloodyMess,
	kAVCode_UnarmedDamage,
	kAVCode_Assistance,
	kAVCode_ElectricResist,
	kAVCode_FrostResist,
	kAVCode_EnergyResist,
	kAVCode_EmpResist,

	kAVCode_Variable01,
	kAVCode_Variable02,
	kAVCode_Variable03,
	kAVCode_Variable04,
	kAVCode_Variable05,
	kAVCode_Variable06,
	kAVCode_Variable07,
	kAVCode_Variable08,
	kAVCode_Variable09,
	kAVCode_Variable10,

	kAVCode_IgnoreCrippledLimbs,
	kAVCode_Dehydration,
	kAVCode_Hunger,
	kAVCode_SleepDeprivation,
	kAVCode_DamageThreshold,
};

enum MiscStatCode : UInt32
{
	kMiscStat_QuestsCompleted,
	kMiscStat_LocationsDiscovered,
	kMiscStat_PeopleKilled,
	kMiscStat_CreaturesKilled,
	kMiscStat_LocksPicked,
	kMiscStat_ComputersHacked,
	kMiscStat_StimpaksTaken,
	kMiscStat_RadXTaken,
	kMiscStat_RadAwayTaken,
	kMiscStat_ChemsTaken,
	kMiscStat_TimesAddicted,
	kMiscStat_MinesDisarmed,
	kMiscStat_SpeechSuccesses,
	kMiscStat_PocketsPicked,
	kMiscStat_PantsExploded,
	kMiscStat_BooksRead,
	kMiscStat_HealthFromStimpaks,
	kMiscStat_WeaponsCreated,
	kMiscStat_HealthFromFood,
	kMiscStat_WaterConsumed,
	kMiscStat_SandmanKills,
	kMiscStat_ParalyzingPunches,
	kMiscStat_RobotsDisabled,
	kMiscStat_TimesSlept,
	kMiscStat_CorpsesEaten,
	kMiscStat_MysteriousStrangerVisits,
	kMiscStat_DoctorBagsUsed,
	kMiscStat_ChallengesCompleted,
	kMiscStat_MissFortunateOccurrences,
	kMiscStat_Disintegrations,
	kMiscStat_HaveLimbsCrippled,
	kMiscStat_SpeechFailures,
	kMiscStat_ItemsCrafted,
	kMiscStat_WeaponModifications,
	kMiscStat_ItemsRepaired,
	kMiscStat_TotalThingsKilled,
	kMiscStat_DismemberedLimbs,
	kMiscStat_CaravanGamesWon,
	kMiscStat_CaravanGamesLost,
	kMiscStat_BarterAmountTraded,
	kMiscStat_RouletteGamesPlayed,
	kMiscStat_BlackjackGamesPlayed,
	kMiscStat_SlotsGamesPlayed,
};

enum PerkEntryPointID
{
	kPerkEntry_CalculateWeaponDamage,
	kPerkEntry_CalculateMyCriticalHitChance,
	kPerkEntry_CalculateMyCriticalHitDamage,
	kPerkEntry_CalculateWeaponAttackAPCost,
	kPerkEntry_CalculateMineExplodeChance,
	kPerkEntry_AdjustRangePenalty,
	kPerkEntry_AdjustLimbDamage,
	kPerkEntry_CalculateWeaponRange,
	kPerkEntry_CalculateToHitChance,
	kPerkEntry_AdjustExperiencePoints,
	kPerkEntry_AdjustGainedSkillPoints,
	kPerkEntry_AdjustBookSkillPoints,
	kPerkEntry_ModifyRecoveredHealth,
	kPerkEntry_CalculateInventoryAPCost,
	kPerkEntry_GetDisposition,
	kPerkEntry_GetShouldAttack,
	kPerkEntry_GetShouldAssist,
	kPerkEntry_CalculateBuyPrice,
	kPerkEntry_GetBadKarma,
	kPerkEntry_GetGoodKarma,
	kPerkEntry_IgnoreLockedTerminal,
	kPerkEntry_AddLeveledListOnDeath,
	kPerkEntry_GetMaxCarryWeight,
	kPerkEntry_ModifyAddictionChance,
	kPerkEntry_ModifyAddictionDuration,
	kPerkEntry_ModifyPositiveChemDuration,
	kPerkEntry_AdjustDrinkingRadiation,
	kPerkEntry_Activate,
	kPerkEntry_MysteriousStranger,
	kPerkEntry_HasParalyzingPalm,
	kPerkEntry_HackingScienceBonus,
	kPerkEntry_IgnoreRunningDuringDetection,
	kPerkEntry_IgnoreBrokenLock,
	kPerkEntry_HasConcentratedFire,
	kPerkEntry_CalculateGunSpread,
	kPerkEntry_PlayerKillAPReward,
	kPerkEntry_ModifyEnemyCriticalHitChance,
	kPerkEntry_ReloadSpeed,
	kPerkEntry_EquipSpeed,
	kPerkEntry_ActionPointRegen,
	kPerkEntry_ActionPointCost,
	kPerkEntry_MissFortune,
	kPerkEntry_ModifyRunSpeed,
	kPerkEntry_ModifyAttackSpeed,
	kPerkEntry_ModifyRadiationConsumed,
	kPerkEntry_HasPipHacker,
	kPerkEntry_HasMeltdown,
	kPerkEntry_SeeEnemyHealth,
	kPerkEntry_HasJuryRigging,
	kPerkEntry_ModifyThreatRange,
	kPerkEntry_ModifyThread,
	kPerkEntry_HasFastTravelAlways,
	kPerkEntry_KnockdownChance,
	kPerkEntry_ModifyWeaponStrengthReq,
	kPerkEntry_ModifyAimingMoveSpeed,
	kPerkEntry_ModifyLightItems,
	kPerkEntry_ModifyDamageThresholdDefender,
	kPerkEntry_ModifyChanceforAmmoItem,
	kPerkEntry_ModifyDamageThresholdAttacker,
	kPerkEntry_ModifyThrowingVelocity,
	kPerkEntry_ChanceforItemonFire,
	kPerkEntry_HasUnarmedForwardPowerAttack,
	kPerkEntry_HasUnarmedBackPowerAttack,
	kPerkEntry_HasUnarmedCrouchedPowerAttack,
	kPerkEntry_HasUnarmedCounterAttack,
	kPerkEntry_HasUnarmedLeftPowerAttack,
	kPerkEntry_HasUnarmedRightPowerAttack,
	kPerkEntry_VATSHelperChance,
	kPerkEntry_ModifyItemDamage,
	kPerkEntry_HasImprovedDetection,
	kPerkEntry_HasImprovedSpotting,
	kPerkEntry_HasImprovedItemDetection,
	kPerkEntry_AdjustExplosionRadius,
	kPerkEntry_AdjustHeavyWeaponWeight
};

enum SpecialInputCode
{
	kInputCode_Backspace = 0x80000000,
	kInputCode_ArrowLeft = 0x80000001,
	kInputCode_ArrowRight = 0x80000002,
	kInputCode_ArrowUp = 0x80000003,
	kInputCode_ArrowDown = 0x80000004,
	kInputCode_Home = 0x80000005,
	kInputCode_End = 0x80000006,
	kInputCode_Delete = 0x80000007,
	kInputCode_Enter = 0x80000008,
	kInputCode_PageUp = 0x80000009,
	kInputCode_PageDown = 0x8000000A
};

class ExtraDetachTime : public BSExtraData
{
public:
	ExtraDetachTime();
	~ExtraDetachTime();

	UInt32 time;
};
// 34
class BGSPrimitive
{
public:
	BGSPrimitive();
	~BGSPrimitive();

	virtual void	Destructor(bool doFree);
	virtual void	Unk_01(void);
	virtual void	Unk_02(void);
	virtual void	Unk_03(void);
	virtual void	Unk_04(void);
	virtual void	Unk_05(void);

	UInt32			type;		// 04
	float			unk08[4];	// 08
	float			bounds[3];	// 18
	NiRefObject		*unk24;		// 24
	NiRefObject		*unk28;		// 28
	NiRefObject		*unk2C;		// 2C
	UInt32			unk30;		// 30
};

// 34
class BGSPrimitivePlane : public BGSPrimitive
{
public:
	BGSPrimitivePlane();
	~BGSPrimitivePlane();
};

// 4C
class BGSPrimitiveBox : public BGSPrimitive
{
public:
	BGSPrimitiveBox();
	~BGSPrimitiveBox();

	UInt32		unk34[6];	// 34
};

// 34
class BGSPrimitiveSphere : public BGSPrimitive
{
public:
	BGSPrimitiveSphere();
	~BGSPrimitiveSphere();
};

class BSAudioListener
{
public:
	BSAudioListener();
	~BSAudioListener();

	virtual BSAudioListener* Destroy(bool doFree);
	virtual void	Unk_01(void);
	virtual void	Unk_02(void);
	virtual void	Unk_03(void);
	virtual void	Unk_04(void);
	virtual void	Unk_05(void);
	virtual void	Unk_06(void);
	virtual void	Unk_07(void);
	virtual void	Unk_08(void);
	virtual void	Unk_09(void);
	virtual void	Unk_0A(void);
	virtual void	Unk_0B(void);
	virtual void	Unk_0C(void);
};

// 64
class BSWin32AudioListener : public BSAudioListener
{
public:
	BSWin32AudioListener();
	~BSWin32AudioListener();

	UInt32			unk04[14];		// 04
	float			flt3C;			// 3C
	UInt32			unk40[9];		// 40
};

class BSWin32Audio
{
public:
	BSWin32Audio();
	~BSWin32Audio();

	virtual void	Destroy(bool doFree);
	virtual void	Unk_01(void);
	virtual void	Unk_02(void);
	virtual void	Unk_03(void);
	virtual void	Unk_04(void);
	virtual BSGameSound* CreateGameSound(const char* filePath);
	virtual void	Unk_06(void);
	virtual void	Unk_07(void);

	UInt32					unk004[3];		// 004
	BSWin32AudioListener* listener;		// 010
	UInt32					unk014[3];		// 014
	bool(*sub_82D150)(UInt32*, UInt32*, UInt32*, UInt32*);	// 020
	bool(*sub_82D280)(UInt32*, UInt32*, UInt32*, UInt32*);	// 024
	bool(*sub_5E3630)(UInt32*);	// 028
	UInt32(*sub_82D400)(UInt32*, TESSound*, UInt32*);	// 02C
	void(*sub_832C40)(void);	// 030
	void(*sub_832C80)(void);	// 034

	static BSWin32Audio* GetSingleton() { return *(BSWin32Audio**)0x11F6D98; };
};

struct Sound
{
	UInt32 soundID;
	UInt8 byte04;
	UInt8 pad05;
	UInt8 pad06;
	UInt8 pad07;
	UInt32 unk08;

	Sound() : soundID(0xFFFFFFFF), byte04(0), unk08(0) {}


	Sound(const char* soundPath, UInt32 flags)
	{
		ThisStdCall(0xAD7550, BSWin32Audio::GetSingleton(), this, soundPath, flags);
	}
	Sound(UInt32 refId, UInt32 flags)
	{
		ThisStdCall(0xAD73B0, BSWin32Audio::GetSingleton(), this, refId, flags);
	}

	void Play()
	{
		ThisStdCall(0xAD8830, this, 0);
	}
};

// 18
class BSTempEffect : public NiObject
{
public:
	BSTempEffect();
	~BSTempEffect();

	virtual void	Unk_23(void);
	virtual void	Unk_24(void);
	virtual void	Unk_25(void);
	virtual void	Unk_26(void);
	virtual void	Unk_27(void);
	virtual void	Unk_28(void);
	virtual void	Unk_29(void);
	virtual void	Unk_2A(void);
	virtual void	Unk_2B(void);
	virtual void	Unk_2C(void);
	virtual void	Unk_2D(void);
	virtual void	Unk_2E(void);
	virtual void	Unk_2F(void);
	virtual void	Unk_30(void);

	float			duration;	// 08
	TESObjectCELL	*cell;		// 0C
	float			unk10;		// 10
	UInt8			unk14;		// 14
	UInt8			pad15[3];	// 15
};

// 28
class MagicHitEffect : public BSTempEffect
{
public:
	MagicHitEffect();
	~MagicHitEffect();

	virtual void	Unk_31(void);
	virtual void	Unk_32(void);
	virtual void	Unk_33(void);
	virtual void	Unk_34(void);
	virtual void	Unk_35(void);
	virtual void	Unk_36(void);
	virtual void	Unk_37(void);
	virtual void	Unk_38(void);

	ActiveEffect	*activeEffect;	// 18
	TESObjectREFR	*target;		// 1C
	float			unk20;			// 20
	UInt8			flags;			// 24	1 - Stop
	UInt8			pad25[3];		// 25
};

// 6C
class MagicShaderHitEffect : public MagicHitEffect
{
public:
	MagicShaderHitEffect();
	~MagicShaderHitEffect();

	UInt32									unk28[2];		// 28
	TESEffectShader							*effectShader;	// 30
	float									flt34;			// 34
	BSSimpleArray<ParticleShaderProperty>	shaderProps;	// 38
	NiNode									*shaderNode;	// 48
	UInt32									unk4C;			// 4C
	BSSimpleArray<NiAVObject>				objects;		// 50	Seen BSFadeNode
	float									flt60;			// 60
	float									flt64;			// 64
	NiProperty								*prop68;		// 68	Seen 0x10AE0C8
};
STATIC_ASSERT(sizeof(MagicShaderHitEffect) == 0x6C);

// 160
struct ProcessManager
{
	UInt32					unk000;				// 000
	NiTArray<MobileObject*>	objects;			// 004
	UInt32					beginOffsets[4];	// 014	0: High, 1: Mid-High, 2: Mid-Low, 3: Low
	UInt32					endOffsets[4];		// 024
	UInt32					unk034[11];			// 034
	tList<BSTempEffect>		tempEffects;		// 060
	UInt32					unk068[6];			// 068
	tList<Actor>			highActors;			// 080
	UInt32					unk088[54];			// 088

	int GetTotalDetectionValue(Actor *actor, bool arg2 = false);
};

struct DetectionData
{
	Actor		*actor;			// 00
	UInt8		detectionLevel;	// 04
	UInt8		byte05;			// 05
	UInt8		byte06;			// 06
	UInt8		byte07;			// 07
	SInt32		detectionValue;	// 08
	UInt32		unk0C;			// 0C
	UInt32		unk10;			// 10
	UInt32		unk14;			// 14
	UInt32		unk18;			// 18
	UInt8		byte1C;			// 1C
	UInt8		byte1D;			// 1D
	bool		inLOS;			// 1E
	UInt8		byte1F;			// 1F
};

// 150
class Projectile : public MobileObject
{
public:
	Projectile();
	~Projectile();

	enum
	{
		kProjType_Beam =	1,
		kProjType_Flame,
		kProjType_Grenade,
		kProjType_Missile,
		kProjType_ContinuousBeam
	};

	virtual UInt32	GetProjectileType();
	virtual void	Unk_C2(void);
	virtual void	Unk_C3(void);
	virtual void	Unk_C4(void);
	virtual bool	ProcessImpact();
	virtual bool	IsProximityTriggered();
	virtual void	Unk_C7(void);
	virtual bool	DisarmPlacedExplosives(TESObjectREFR *refr, bool unk);
	virtual void	Unk_C9(void);
	virtual void	Unk_CA(void);
	virtual void	Unk_CB(void);

	enum
	{
		kProjFlag_Bit00Unk =			0x1,
		kProjFlag_Bit01Unk =			0x2,
		kProjFlag_Bit02Unk =			0x4,
		kProjFlag_Bit03Unk =			0x8,
		kProjFlag_Bit04Unk =			0x10,
		kProjFlag_Bit05Unk =			0x20,
		kProjFlag_Bit06Unk =			0x40,
		kProjFlag_Bit07Unk =			0x80,
		kProjFlag_Bit08Unk =			0x100,
		kProjFlag_MineDisarmed =		0x200,
		kProjFlag_Bit0AUnk =			0x400,
		kProjFlag_Bit0BUnk =			0x800,
		kProjFlag_Bit0CUnk =			0x1000,
		kProjFlag_Bit0DUnk =			0x2000,
		kProjFlag_Bit0EUnk =			0x4000,
		kProjFlag_Bit0FUnk =			0x8000,		// Don't apply source-weapon's damage upon impact
		kProjFlag_Bit10Unk =			0x10000,
		kProjFlag_Bit11Unk =			0x20000,
		kProjFlag_Bit12Unk =			0x40000,
		kProjFlag_Bit13Unk =			0x80000,
		kProjFlag_Bit14Unk =			0x100000,
	};

	struct ImpactData
	{
		TESObjectREFR	*refr;			// 00
		NiVector3		pos;			// Gotten from JIP
		NiVector3		rot;			// Gotten from JIP
		hkpRigidBody	*rigidBody;		// 1C
		UInt32			materialType;	// 20, gotten from JIP
		SInt32			hitLocation;	// 24
		UInt32			unk28;			// 28
		UInt32			unk2C;			// 2C
	};

	struct Struct128
	{
		UInt32			unk00;
		UInt8			byte04;
		UInt8			pad05[3];
		UInt32			status;		//	0 - Not triggered, 1 - Triggered, 2 - Disarmed
	};

	tList<ImpactData>	impactDataList;	// 088
	UInt8				hasImpacted;	// 090
	UInt8				pad091[3];		// 091
	float				unk094[13];		// 094
	UInt32				projFlags;		// 0C8
	float				speedMult1;		// 0CC
	float				speedMult2;		// 0D0
	float				flt0D4;			// 0D4
	float				elapsedTime;	// 0D8
	float				hitDamage;		// 0DC
	float				flt0E0;			// 0E0
	float				detonationTime;	// 0E4
	float				flt0E8;			// 0E8
	float				flt0EC;			// 0EC
	float				flt0F0;			// 0F0
	float				wpnHealthPerc;	// 0F4
	TESObjectWEAP		*sourceWeap;	// 0F8
	TESObjectREFR		*sourceRef;		// 0FC
	UInt32				unk100;			// 100
	float				flt104;			// 104
	float				flt108;			// 108
	float				flt10C;			// 10C
	float				distTravelled;	// 110
	NiRefObject			*object114;		// 114
	UInt8				byte118;		// 118
	UInt8				pad119[3];		// 119
	NiNode				*node11C;		// 11C
	UInt32				unk120;			// 120
	float				flt124;			// 124
	Struct128			unk128;			// 128
	Struct128			unk134;			// 134
	UInt32				unk140;			// 140
	UInt32				unk144;			// 144
	UInt8				byte148;		// 148
	UInt8				pad149[3];		// 149
	float				range;			// 14C

	// Copied from JIP's Projectile::GetData
	[[nodiscard]] TESObjectREFR* GetImpactRef() const;
};
STATIC_ASSERT(sizeof(Projectile) == 0x150);

// 154
class BeamProjectile : public Projectile
{
public:
	BeamProjectile();
	~BeamProjectile();

	NiRefObject		*object150;		// 150
};

// 158
class ContinuousBeamProjectile : public Projectile
{
public:
	ContinuousBeamProjectile();
	~ContinuousBeamProjectile();

	NiRefObject		*object150;		// 150
	UInt32			unk154;			// 154
};

// 158
class FlameProjectile : public Projectile
{
public:
	FlameProjectile();
	~FlameProjectile();

	virtual void	Unk_CC(void);

	float		flt150;		// 150
	float		flt154;		// 154
};

// 154
class GrenadeProjectile : public Projectile
{
public:
	GrenadeProjectile();
	~GrenadeProjectile();

	virtual void	Unk_CC(void);

	UInt8		byte150;		// 150
	UInt8		pad151[3];		// 151
};

// 160
class MissileProjectile : public Projectile
{
public:
	MissileProjectile();
	~MissileProjectile();

	virtual void	Unk_CC(void);

	UInt32		unk150;			// 150
	UInt8		byte154;		// 154
	UInt8		pad155[3];		// 155
	float		flt158;			// 158
	float		flt15C;			// 15C
};

// 104
class Explosion : public MobileObject
{
public:
	Explosion();
	~Explosion();

	virtual void	Unk_C1(void);

	float			unk088;			// 088
	float			unk08C;			// 08C
	float			fBuildTime;		// 090
	float			radius;			// 094
	float			ISRadius;		// 098
	float			unk09C;			// 09C
	NiRefObject		*object0A0;		// 0A0
	tList<void>		list0A4;		// 0A4
	UInt32			unk0AC[6];		// 0AC
	NiRefObject		*object0C4;		// 0C4
	Actor*			source;			// 0C8
	UInt32			unk0CC;			// 0CC
	NiRefObject		*object0D0;		// 0D0
	UInt32			unk0D4[11];		// 0D4
	float			unk100;			// 100
};
STATIC_ASSERT(sizeof(Explosion) == 0x104);

template <typename Item> struct ListBoxItem
{
	Tile	*tile;
	Item	*object;
};

// 30
template <typename Item> class ListBox : public BSSimpleList<ListBoxItem<Item>>
{
public:
	Tile			*parentTile;	// 0C
	Tile			*selected;		// 10
	Tile			*scrollBar;		// 14
	const char		*templateName;	// 18
	UInt16			itemCount;		// 1C
	UInt16			pad1E;			// 1E
	float			unk20[3];		// 20
	UInt16			unk2C;			// 2C
	UInt16			pad2E;			// 2E

	Item *GetSelected()
	{
		ListNode<ListBoxItem<Item>> *iter = this->list.Head();
		ListBoxItem<Item> *item;
		do
		{
			item = iter->data;
			if (item && (item->tile == selected))
				return item->object;
		}
		while (iter = iter->next);
		return nullptr;
	}

	Tile* GetTileForItem(const Item* item)
	{
		if (!item)
			return nullptr;
		ListNode<ListBoxItem<Item>>* iter = this->list.Head();
		do
		{
			if (auto const i = iter->data;
				i && i->object == item)
			{
				return i->tile;
			}
		} while (iter = iter->next);
		return nullptr;
	}

	void Clear()
	{
		ListNode<ListBoxItem<Item>> *iter = this->list.Head();
		ListBoxItem<Item> *item;
		do
		{
			item = iter->data;
			if (!item) continue;
			if (item->tile)
				item->tile->Destroy(true);
			GameHeapFree(item);
		}
		while (iter = iter->next);
		BSSimpleList<Item>::list.RemoveAll();
		selected = NULL;
		itemCount = 0;
	}

	//taken from Stewie's Tweaks
	void SetParentEnabled(bool isEnabled)
	{
		static UInt32 enabledTrait = TraitNameToID("_enabled");
		parentTile->SetFloat(enabledTrait, isEnabled);
	}
	
	//taken from Stewie's Tweaks
	[[nodiscard]] bool IsEnabled() const
	{
		static UInt32 enabledTrait = TraitNameToID("_enabled");
		return parentTile && parentTile->GetValueFloat(enabledTrait);
	}
};

// 94
class MessageMenu : public Menu			// 1001
{
public:
	MessageMenu();
	~MessageMenu();

	TileRect			*tile28;		// 28
	TileText			*tile2C;		// 2C
	TileImage			*tile30;		// 30
	TileText			*tile34;		// 34
	TileImage			*tile38;		// 38
	TileImage			*tile3C;		// 3C
	ListBox<int>		buttonList;		// 40
	UInt8				unk70;			// 70
	UInt8				pad71[3];		// 71
	float				unk74[3];		// 74
	UInt32				unk80[2];		// 80
	UInt32				tickCount;		// 88
	UInt8				unk8C;			// 8C
	UInt8				unk8D;			// 8D
	UInt8				pad8E[2];		// 8E
	UInt32				unk90;			// 90
};

typedef ListBox<ContChangesEntry> MenuItemEntryList;

// 124
class InventoryMenu : public Menu		// 1002
{
public:
	InventoryMenu();
	~InventoryMenu();

	TileRect			*tile028;		// 028	IM_Headline_PlayerCapsInfo
	TileRect			*tile02C;		// 02C	IM_Headline_PlayerHPInfo
	TileRect			*tile030;		// 030	IM_Headline_PlayerDRInfo
	TileRect			*tile034;		// 034	IM_Headline_PlayerWGInfo
	TileImage			*tile038;		// 038	IM_InventoryList
	TileRect			*tile03C;		// 03C	IM_HotKeyWheel
	TileImage			*tile040;		// 040	IM_EquipButton
	TileImage			*tile044;		// 044	IM_DropButton
	TileImage			*tile048;		// 048	IM_RepairButton
	TileImage			*tile04C;		// 04C	IM_HotkeyButton
	TileImage			*tile050;		// 050	IM_CancelButton
	TileImage			*tile054;		// 054	IM_ItemIcon
	TileRect			*tile058;		// 058	IM_ItemInfoRect
	TileRect			*tile05C;		// 05C	IM_Tabline
	TileRect			*tile060;		// 060	DAMInfo
	TileRect			*tile064;		// 064	DPSInfo
	TileRect			*tile068;		// 068	StrengthReqInfo
	TileRect			*tile06C;		// 06C	DamageResistInfo
	TileRect			*tile070;		// 070	DamageThresholdInfo
	TileImage			*tile074;		// 074	IM_ModButton
	TileImage			*tile078;		// 078	IM_ItemIconBadge
	TileRect			*tile07C;		// 07C	IM_Headline_PlayerDTInfo
	TileText			*tile080;		// 080	IM_StrReq
	UInt32				filter;			// 084
	UInt32				unk088[12];		// 088
	MenuItemEntryList	itemList;		// 0B8
	TileRect			*tile0E8;		// 0E8
	TileRect			*tile0EC;		// 0EC
	TileRect			*tile0F0;		// 0F0
	TileRect			*tile0F4;		// 0F4
	TileRect			*tile0F8;		// 0F8
	TileRect			*tile0FC;		// 0FC
	TileRect			*tile100;		// 100
	TileRect			*tile104;		// 104
	TileRect			*tile108;		// 108
	UInt32				unk10C[6];		// 10C

	//Both copied from JIP
	__forceinline static InventoryMenu* Get() { return *(InventoryMenu**)0x11D9EA4; }
	__forceinline static ContChangesEntry* Selection() { return *(ContChangesEntry**)0x11D9EA8; }
};

// 2A4
class StatsMenu : public Menu			// 1003
{
public:
	StatsMenu();
	~StatsMenu();

	struct AlchItemData
	{
		AlchemyItem		*alchItem;
		TileImage		*tileImg;
		void			*dataPtr;
		bool			(*callback)(void *arg);
	};

	struct StatusEffect;

	AlchItemData					alchItemData[4];	// 028	0: Stimpak, 1: Rad-X, 2: RadAway, 3: Doctor's Bag
	BSSimpleList<EffectSetting>		effectList;			// 068
	UInt32							unk074[4];			// 074
	BSSimpleList<StatusEffect>		statusEffList;		// 084
	TileImage						*tile090;			// 090
	TileImage						*tile094;			// 094
	TileImage						*tile098;			// 098
	TileImage						*tile09C;			// 09C
	TileImage						*tile0A0;			// 0A0
	TileImage						*tile0A4;			// 0A4
	TileImage						*tile0A8;			// 0A8
	TileImage						*tile0AC;			// 0AC
	TileImage						*tile0B0;			// 0B0
	TileImage						*tile0B4;			// 0B4
	TileImage						*tile0B8;			// 0B8
	TileImage						*tile0BC;			// 0BC
	TileImage						*tile0C0;			// 0C0
	TileRect						*tile0C4;			// 0C4
	TileImage						*tile0C8;			// 0C8
	TileRect						*tile0CC;			// 0CC
	TileImage						*tile0D0;			// 0D0
	TileRect						*tile0D4;			// 0D4
	TileImage						*tile0D8;			// 0D8
	TileRect						*tile0DC;			// 0DC
	TileImage						*tile0E0;			// 0E0
	TileRect						*tile0E4;			// 0E4
	TileImage						*tile0E8;			// 0E8
	TileRect						*tile0EC;			// 0EC
	TileImage						*tile0F0;			// 0F0
	TileImage						*tile0F4;			// 0F4
	TileImage						*tile0F8;			// 0F8
	TileText						*tile0FC;			// 0FC
	TileImage						*tile100;			// 100
	TileImage						*tile104;			// 104
	TileImage						*tile108;			// 108
	TileImage						*tile10C;			// 10C
	TileImage						*tile110;			// 110
	TileImage						*tile114;			// 114
	TileImage						*tile118;			// 118
	TileText						*tile11C;			// 11C
	TileImage						*tile120;			// 120
	TileText						*tile124;			// 124
	TileText						*tile128;			// 128
	TileText						*tile12C;			// 12C
	TileRect						*tile130;			// 130
	TileRect						*tile134;			// 134
	TileRect						*tile138;			// 138
	TileRect						*tile13C;			// 13C
	TileText						*tile140;			// 140
	TileText						*tile144;			// 144
	TileImage						*tile148;			// 148
	TileImage						*tile14C;			// 14C
	TileText						*tile150;			// 150
	TileImage						*tile154;			// 154
	TileImage						*tile158;			// 158
	TileText						*tile15C;			// 15C
	TileImage						*tile160;			// 160
	TileImage						*tile164;			// 164
	TileImage						*tile168;			// 168
	TileImage						*tile16C;			// 16C
	TileImage						*tile170;			// 170
	TileImage						*tile174;			// 174
	TileImage						*tile178;			// 178
	TileImage						*tile17C;			// 17C
	ListBox<UInt32>					avIndexList180;		// 180
	ListBox<UInt32>					avIndxeList1B0;		// 1B0
	ListBox<PerkRank>				perkRankList;		// 1E0
	ListBox<UInt32>					miscStatIDList;		// 210
	ListBox<StatusEffect>			statusEffListBox;	// 240
	ListBox<TESReputation>			reputationList;		// 270
	UInt32							unk2A0;				// 2A0
};

// 50
class Tile3D : public Tile
{
public:
	Tile3D();
	~Tile3D();

	UInt32			unk38[6];
};

// 278
class HUDMainMenu : public Menu			// 1004
{
public:
	HUDMainMenu();
	~HUDMainMenu();

	struct QueuedMessage
	{
		char	msgText[0x204];			// 000
		char	iconPath[MAX_PATH];		// 204
		char	soundPath[MAX_PATH];	// 308
		float	displayTime;			// 40C
	};

	struct SubtitleData;

	struct Struct224
	{
		UInt8		byte00;		// 00
		UInt8		pad01[3];	// 01
		float		flt04;		// 04
		float		flt08;		// 08
		float		flt0C;		// 0C
		float		flt10;		// 10
		UInt32		unk14;		// 14
		UInt32		tickCount;	// 18
		UInt8		byte1C;		// 1C
		UInt8		byte1D;		// 1D
		UInt8		pad1E[2];	// 1E
	};
	enum VisibilityFlags
	{
		kActionPoints = 0x1,
		kHitPoints = 0x2,
		kRadiationMeter = 0x4,
		kEnemyHealth = 0x8,
		kQuestReminder = 0x10,
		kRegionLocation = 0x20,
		kReticleCenter = 0x40,
		kSneakMeter = 0x80,
		kMessages = 0x100,
		kInfo = 0x200,
		kSubtitles = 0x400,
		kHotkeys = 0x800,
		kXpMeter = 0x1000,
		kBreathMeter = 0x2000,
		kExplosivePositioning = 0x4000,
		kCrippledLimbIndicator = 0x8000,
		kHardcoreMode = 0x10000,
	};
	enum HUDStates
	{
		kHUDState_RECALCULATE = 0x1,
		kHUDState_Normal = 0x2,
		kHUDState_PipBoy = 0x3,
		kHUDState_Pause = 0x4,
		kHUDState_Loading = 0x5,
		kHUDState_Dialog = 0x6,
		kHUDState_VATSMenu = 0x7,
		kHUDState_VATSPlayback = 0x8,
		kHUDState_Container = 0x9,
		kHUDState_BeginSit = 0xA,
		kHUDState_SleepWait = 0xB,
		kHUDState_PlayerDisabledControls = 0xC,
		kHUDState_D = 0xD,
		kHUDState_LevelUpMenu = 0xE,
		kHUDState_Hacking = 0xF,
		kHUDState_Computers = 0x10,
		kHUDState_Message = 0x11,
		kHUDState_SpecialBook = 0x12,
		kHUDState_LoveTester = 0x13,
		kHUDState_VanityCam = 0x14,
		kHUDState_15 = 0x15,
		kHUDState_Aiming = 0x16,
		kHUDState_AimingScope = 0x17,
		kHUDState_IntroMovie = 0x18,
		kHUDState_Gambling = 0x19,
	};

	UInt32							unk028;			// 028
	TileImage						*tile02C;		// 02C	HitPoints\meter
	TileText						*tile030;		// 030	HitPoints\justify_right_text
	TileRect						*tile034;		// 034	HitPoints\compass_window\compass_icon_group
	TileRect						*tile038;		// 038	HitPoints\compass_window\compass_icon_group
	TileRect						*tile03C;		// 03C	HitPoints\compass_window\compass_icon_group
	TileImage						*tile040;		// 040	HitPoints\compass_window
	TileImage						*tile044;		// 044	ActionPoints\meter
	TileText						*tile048;		// 048	ActionPoints\justify_right_text
	TileText						*tile04C;		// 04C	ActionPoints\justify_right_text
	TileImage						*tile050;		// 050	ActionPoints\meter
	TileImage						*tile054;		// 054	ActionPoints\MeterBackground
	TileText						*tile058;		// 058	ActionPoints\justify_right_text
	TileRect						*tile05C;		// 05C	QuestReminder\QuestStages
	TileRect						*tile060;		// 060	QuestReminder\QuestAdded
	TileText						*tile064;		// 064	Region_Location\justify_left_text
	TileText						*tile068;		// 068	Region_Location\justify_left_text
	TileImage						*tile06C;		// 06C	RadiationMeter\radiation_bracket
	TileImage						*tile070;		// 070	RadiationMeter\radiation_pointer
	TileText						*tile074;		// 074	RadiationMeter\radiation_text_value
	TileText						*tile078;		// 078	RadiationMeter\radiation_text
	TileImage						*tile07C;		// 07C	EnemyHealth\enemy_health_bracket
	TileImage						*tile080;		// 080	EnemyHealth\meter
	TileText						*tile084;		// 084	EnemyHealth\justify_center_text
	TileText						*sneakLabel;	// 088	SneakMeter\sneak_nif
	TileImage						*tile08C;		// 08C	Messages\message_icon
	TileText						*tile090;		// 090	Messages\justify_left_text
	TileImage						*tile094;		// 094	Messages\message_bracket
	TileText						*tile098;		// 098	Subtitles\justify_center_text
	TileRect						*tile09C;		// 09C	Info\justify_center_hotrect
	TileText						*tile0A0;		// 0A0	Info\justify_center_hotrect\PCShortcutLabel
	TileImage						*tile0A4;		// 0A4	Info\justify_center_hotrect\xbox_button
	TileText						*tile0A8;		// 0A8	Info\justify_center_text
	TileText						*tile0AC;		// 0AC	Info\justify_center_text
	TileText						*tile0B0;		// 0B0	Info\justify_center_text
	TileText						*tile0B4;		// 0B4	Info\justify_right_text
	TileText						*tile0B8;		// 0B8	Info\justify_left_text
	TileText						*tile0BC;		// 0BC	Info\justify_right_text
	TileText						*tile0C0;		// 0C0	Info\justify_left_text
	TileImage						*tile0C4;		// 0C4	Info\info_seperator
	TileRect						*tile0C8;		// 0C8	Hokeys\hotkey_selector
	TileText						*tile0CC;		// 0CC	Hokeys\justify_center_text
	TileImage						*tile0D0;		// 0D0	HitPoints\left_bracket
	TileImage						*tile0D4;		// 0D4	ActionPoints\right_bracket
	TileImage						*tile0D8;		// 0D8	XPMeter\XPBracket
	TileText						*tile0DC;		// 0DC	XPMeter\XPAmount
	TileText						*tile0E0;		// 0E0	XPMeter\XPLabel
	TileImage						*tile0E4;		// 0E4	XPMeter\XPPointer
	TileText						*tile0E8;		// 0E8	XPMeter\XPLastLevel
	TileText						*tile0EC;		// 0EC	XPMeter\XPNextLevel
	TileText						*tile0F0;		// 0F0	XPMeter\XPLevelUp
	TileImage						*tile0F4;		// 0F4	ReticleCenter\reticle_center
	TileImage						*tile0F8;		// 0F8	crippled_limb_indicator\Face
	TileImage						*tile0FC;		// 0FC	crippled_limb_indicator\Head
	TileImage						*tile100;		// 100	crippled_limb_indicator\Torso
	TileImage						*tile104;		// 104	crippled_limb_indicator\Left_Arm
	TileImage						*tile108;		// 108	crippled_limb_indicator\Right_Arm
	TileImage						*tile10C;		// 10C	crippled_limb_indicator\Left_Leg
	TileImage						*tile110;		// 110	crippled_limb_indicator\Right_Leg
	TileRect						*tile114;		// 114	ActionPoints
	TileRect						*tile118;		// 118	HitPoints
	TileRect						*tile11C;		// 11C	RadiationMeter
	TileRect						*tile120;		// 120	EnemyHealth
	TileRect						*tile124;		// 124	QuestReminder
	TileRect						*tile128;		// 128	Region_Location
	TileRect						*tile12C;		// 12C	ReticleCenter
	TileRect						*tile130;		// 130	SneakMeter
	TileRect						*tile134;		// 134	Messages
	TileRect						*tile138;		// 138	Info
	TileRect						*tile13C;		// 13C	Subtitles
	TileRect						*tile140;		// 140	Hokeys
	TileRect						*tile144;		// 144	XPMeter
	Tile3D							*tile148;		// 148	BreathMeter
	TileRect						*tile14C;		// 14C	Explosive_positioning_rect
	TileRect						*tile150;		// 150	crippled_limb_indicator
	TileImage						*tile154;		// 154	DDTIcon
	TileImage						*tile158;		// 158	DDTIconEnemy
	TileText						*tile15C;		// 15C	AmmoTypeLabel
	TileRect						*tile160;		// 160	HardcoreMode
	TileText						*tile164;		// 164	HardcoreMode\Dehydration
	TileText						*tile168;		// 168	HardcoreMode\Sleep
	TileText						*tile16C;		// 16C	HardcoreMode\Hunger
	TileImage						*tile170;		// 170	DDTIcon
	TileImage						*tile174;		// 174	DDTIconEnemyAP
	TileText						*tile178;		// 178	HardcoreMode\Rads
	TileText						*tile17C;		// 17C	HardcoreMode\LMBs
	TileImage						*tile180;		// 180	CNDArrows
	UInt32							unk184;			// 184
	float							flt188;			// 188
	tList<QueuedMessage>			queuedMessages;	// 18C
	UInt32							currMsgKey;		// 194
	BSSimpleArray<SubtitleData>		subtitlesArr;	// 198
	UInt32							unk1A8[4];		// 1A8
	TESObjectREFR					*crosshairRef;	// 1B8
	UInt32							unk1BC;			// 1BC
	UInt32							unk1C0;			// 1C0	Crosshair flags?
	UInt32							unk1C4;			// 1C4
	TileRect						*tile1C8;		// 1C8	Hokeys\hotkey_selector
	TileRect						*tile1CC;		// 1CC	Hokeys\hotkey_selector\HK_Item_0
	UInt32							unk1D0;			// 1D0
	TileRect						*tile1D4;		// 1D4	Hokeys\hotkey_selector\HK_Item_2
	TileRect						*tile1D8;		// 1D8	Hokeys\hotkey_selector\HK_Item_3
	TileRect						*tile1DC;		// 1DC	Hokeys\hotkey_selector\HK_Item_4
	TileRect						*tile1E0;		// 1E0	Hokeys\hotkey_selector\HK_Item_5
	TileRect						*tile1E4;		// 1E4	Hokeys\hotkey_selector\HK_Item_6
	TileRect						*tile1E8;		// 1E8	Hokeys\hotkey_selector\HK_Item_7
	UInt32							unk1EC[5];		// 1EC
	NiControllerSequence			*niContSeq;		// 200
	UInt8							byte204;		// 204
	UInt8							byte205;		// 205
	UInt8							pad206[2];		// 206
	UInt32							unk208[5];		// 208
	Actor							*healthTarget;	// 21C
	UInt32							unk220;			// 220
	Struct224						unk224;			// 224
	UInt32							unk244;			// 244
	UInt32							unk248[4];		// 248
	tList<UInt32>					list258;		// 258
	UInt8							byte260;		// 260
	UInt8							byte261;		// 261
	UInt8							pad262[2];		// 262
	tList<UInt32>					list264;		// 264
	tList<UInt32>					list26C;		// 26C
	float							flt274;			// 274
};
STATIC_ASSERT(sizeof(HUDMainMenu) == 0x278);

// 5C0
class LoadingMenu : public Menu			// 1007
{
public:
	LoadingMenu();
	~LoadingMenu();

	Tile3D				*tile028;		// 028
	TileText			*tile02C;		// 02C
	TileText			*tile030;		// 030
	TileText			*tile034;		// 034
	TileText			*tile038;		// 038
	TileText			*tile03C;		// 03C
	TileText			*tile040;		// 040
	TileText			*tile044;		// 044
	TileText			*tile048;		// 048
	TileText			*tile04C;		// 04C
	TileImage			*tile050;		// 050
	Tile3D				*tile054;		// 054
	TileImage			*tile058;		// 058
	TileText			*tile05C;		// 05C
	TileText			*tile060;		// 060
	TileText			*tile064;		// 064
	TileRect			*tile068;		// 068
	TileText			*tile06C;		// 06C
	TileRect			*tile070;		// 070
	TileText			*tile074;		// 074
	TileText			*tile078;		// 078
	TileText			*tile07C;		// 07C
	TileText			*tile080;		// 080
	TileText			*tile084;		// 084
	TileText			*tile088;		// 088
	TileText			*tile08C;		// 08C
	TileText			*tile090;		// 090
	TileRect			*tile094;		// 094
	TileText			*tile098;		// 098
	TileText			*tile09C;		// 09C
	TileText			*tile0A0;		// 0A0
	TileRect			*tile0A4;		// 0A4
	TileImage			*tile0A8;		// 0A8
	TileImage			*tile0AC;		// 0AC
	TileText			*tile0B0;		// 0B0
	TileText			*tile0B4;		// 0B4
	TileImage			*tile0B8;		// 0B8
	TileImage			*tile0BC;		// 0BC
	UInt32				unk0C0;			// 0C0
	UInt32				unk0C4;			// 0C4
	UInt32				unk0C8;			// 0C8
	UInt32				unk0CC;			// 0CC
	DList<Tile>			list0D0;		// 0D0
	DList<Tile>			list0DC;		// 0DC
	DList<Tile>			list0E8;		// 0E8
	DList<Tile>			list0F4;		// 0F4
	DList<Tile>			list100;		// 100
	UInt32				unk10C[49];		// 10C
	TESLoadScreen		*loadScr1D0;	// 1D0
	void				*ptr1D4;		// 1D4
	void				*ptr1D8;		// 1D8
	TESLoadScreen		*loadScr1DC;	// 1DC
	UInt32				unk1E0;			// 1E0
	UInt32				unk1E4;			// 1E4
	TESWorldSpace		*worldspace;	// 1E8
	UInt32				unk1EC[8];		// 1EC
	NiSourceTexture		*srcTexture[4];	// 20C
	UInt32				unk21C;			// 21C
	UInt8				byte220[2];		// 220
	UInt16				flags;			// 222
	UInt32				unk224[231];	// 224
};
STATIC_ASSERT(sizeof(LoadingMenu) == 0x5C0);

// 10C
class ContainerMenu : public Menu		// 1008
{
public:
	ContainerMenu();
	~ContainerMenu();

	enum Mode
	{
		kNormal = 0x1,
		kPickpocket,
		kTeammate,
		kRockItLauncher
	};
	static ContainerMenu* GetSingleton() { return *(ContainerMenu**)(0x11D93F8); }
	static ContChangesEntry* GetSelection() { return *(ContChangesEntry**)(0x11D93FC); }
	void HandleMouseoverAlt(int a2, int a3) { ThisStdCall(0x75CF70, this, a2, a3); }
	static void SetSelection(ContChangesEntry* entry) { *(ContChangesEntry**)(0x11D93FC) = entry; }

	TileImage* tile028;		// 028
	TileText* tile02C;		// 02C
	TileImage* tile030;		// 030
	TileText* tileInventoryWeight;		// 034
	TileImage* tile038;		// 038
	TileImage* tile03C;		// 03C
	TileText* tile040;		// 040
	TileImage* tile044;		// 044
	TileImage* tile048;		// 048
	TileImage* tile04C;		// 04C
	TileImage* takeAllTile;	// 050
	TileImage* tile054;		// 054
	TileImage* tile058;		// 058
	TileRect* tile05C;		// 05C
	TileRect* tile060;		// 060
	TileRect* tile064;		// 064
	TileRect* tile068;		// 068
	TileRect* tile06C;		// 06C
	TileRect* tile070;		// 070
	TESObjectREFR* containerRef;	// 074
	tList<TESForm>			list078;		// 078
	UInt32				mode;			// 080
	UInt32				valueTransfered;// 084
	UInt8				hasPickedPocket;// 088
	UInt8				hasFailedPickpocket;	// 089
	UInt8				pad08A;			// 08A
	UInt8				pad08B;			// 08B
	UInt32				leftFilter;		// 08C
	UInt32				rightFilter;	// 090
	UInt32				menuSoundID;	// 094
	MenuItemEntryList	leftItems;		// 098
	MenuItemEntryList	rightItems;		// 0C8
	MenuItemEntryList* currentItems;	// 0F8
	UInt32				unk0FC;			// 0FC
	Sound				menuSound;		// 100
};
STATIC_ASSERT(sizeof(ContainerMenu) == 0x10C);

// 13C
class DialogMenu : public Menu			// 1009
{
public:
	DialogMenu();
	~DialogMenu();

	UInt32				unk028[2];		// 028
	TileImage			*tile030;		// 030
	TileText			*tile034;		// 034
	TileText			*tile038;		// 038
	TileImage			*tile03C;		// 03C
	ListBox<int>		topicList;		// 040
	void				*unk070;		// 070
	UInt32				unk074;			// 074
	TESTopicInfo		*info078;		// 078
	UInt32				unk07C;			// 07C
	TESObjectREFR		*partnerRef;	// 080
	float				unk084[2];		// 084
	void				*unk08C;		// 08C
	void				*unk090;		// 090
	TESTopicInfo		*infos094[16];	// 094
	void				*unk0D4;		// 0D4
	UInt32				unk0D8[3];		// 0D8
	TESTopicInfo		*infos0E4[8];	// 0E4
	UInt32				unk104[3];		// 104
	TESTopicInfo		*infos110[6];	// 110
	float				unk128;			// 128
	void				*unk12C;		// 12C	ImageSpaceModifierInstanceDOF
	UInt32				unk130[3];		// 130
};

// 4C
class SleepWaitMenu : public Menu		// 1012
{
public:
	SleepWaitMenu();
	~SleepWaitMenu();

	TileText			*tile28;		// 28
	TileImage			*tile2C;		// 2C
	TileText			*tile30;		// 30
	TileText			*tile34;		// 34
	TileImage			*tile38;		// 38
	TileImage			*tile3C;		// 3C
	UInt32				unk40;			// 40
	float				flt44;			// 44
	float				selectedHours;	// 48
};
STATIC_ASSERT(sizeof(SleepWaitMenu) == 0x4C);

// 1D4
class StartMenu : public Menu			// 1013
{
public:
	StartMenu();
	~StartMenu();

	// 10
	class Option
	{
	public:
		Option();
		~Option();

		virtual void	Destructor(bool doFree);

		const char		*optionName;				// 04
		void			(*followupOption_callback)(void);	// 08
		UInt32			flags;						// 0C
	};

	enum CallbackAddresses : UInt32
	{
		kNewAddr = 0x7D0490,
		kContinueAddr = 0x7D0440,
		kCreditsAddr = 0x7D04D0,
		kLoadAddr = 0x7D0680,
		kSaveAddr = 0x7D06C0,
		kSettingsAddr = 0x7D0700,
		kHelpAddr = 0x7D0770,
		kQuitAddr = 0x7D0A10,
		kBackAddr = 0x7D0E40,
	};

	// 30
	class UserOption : public Option
	{
	public:
		UserOption();
		~UserOption();

		const char		*templateName;					// 10
		UInt32			currValue;						// 14
		UInt32			unk18[4];						// 18
		const char		**currValueName;				// 28
		void			(*onSelection)(UserOption*);	// 2C
	};

	static StartMenu* GetSingleton() {
		return 	*(StartMenu**)0x11DAAC0;
	}
	
	static bool Create(bool useMainMenu, bool bWholeMenuIfFalse_OrLoadManu)
	{
		return CdeclCall<bool>(0x7CB7D0, useMainMenu, bWholeMenuIfFalse_OrLoadManu);
	}

	// Taken from Stewie's PDB
	enum StartMenuFlags : UInt32
	{
		 kHasChangedSettings = 0x2,
		 kLoad = 0x4,	//force-load?
		 kIsSaveMenuNotLoad = 0x8,
		 kAreOptionsInitialised = 0x20,
		 kShowDLCPopup = 0x400,
		 kIsActionMapping = 0x1000,
		 kDeleteSave = 0x2000,
		 kIsSaving = 0x4000,
		 kShowCredits = 0x10000,
		 kControllerDisconnected = 0x20000,
		 kShouldInitSavesList = 0x100000,
		 kShowMustRestartToSaveSettings = 0x400000,
		 kSomething_credits = 0x2000000,
		 kControllerInputDebounce = 0x4000000,
		 kSomethingSave = 0x40000000,
	};

	void SetFlag(StartMenuFlags flag, bool setIfTrue_OrRemove)
	{
		if (setIfTrue_OrRemove)
			this->flags |= flag;
		else
			this->flags &= ~flag;
	}
	[[nodiscard]] bool GetFlag(StartMenuFlags flag) const
	{
		return flags & flag;
	}
	// Contains most (if not all?) options and sub-options for the start menu.
	[[nodiscard]] static auto GetStartMenuOptionsArray()
	{
		return (BSSimpleArray<StartMenu::Option*>*)0x11DAB88;
	}


	TileImage						*tile028;		// 028
	TileImage						*tile02C;		// 02C
	TileImage						*tile030;		// 030
	TileImage						*tile034;		// 034
	TileImage						*tile038;		// 038
	TileImage						*tile03C;		// 03C
	TileImage						*tile040;		// 040
	TileImage						*tile044;		// 044
	TileText						*tile048;		// 048
	TileText						*tile04C;		// 04C
	TileText						*tile050;		// 050
	TileImage						*tile054;		// 054
	TileText						*tile058;		// 058
	Tile3D							*tile05C;		// 05C
	TileImage						*tile060;		// 060
	TileImage						*tile064;		// 064
	TileText						*tile068;		// 068
	TileImage						*tile06C;		// 06C
	TileText						*tile070;		// 070
	TileText						*tile074;		// 074
	TileText						*tile078;		// 078
	TileImage						*tile07C;		// 07C
	TileText						*tile080;		// 080
	ListBox<Option>					main_options084;// 084, includes "Continue", "Settings", etc.
	ListBox<Option>					options0B4;		// 0B4
	ListBox<Option>					options0E4;		// 0E4
	ListBox<Option>					options114;		// 114
	ListBox<int>					listBox144;		// 144
	ListBox<BGSSaveLoadFileEntry>	listBox174;		// 174
	UInt32							unk1A4;			// 1A4
	UInt32							flags;			// 1A8
	UInt32							unk1AC;			// 1AC
	UInt32							unk1B0;			// 1B0
	Option							*option1B4;		// 1B4
	NiSourceTexture					*texture1B8;	// 1B8
	UInt32							unk1BC;			// 1BC
	TileImage						*tile1C0;		// 1C0
	TileImage						*tile1C4;		// 1C4
	UInt32							unk1C8;			// 1C8
	UInt32							unk1CC;			// 1CC
	UInt32							unk1D0;			// 1D0
};
STATIC_ASSERT(sizeof(StartMenu) == 0x1D4);

// E4
class LockPickMenu : public Menu		// 1014
{
public:
	LockPickMenu();
	~LockPickMenu();

	UInt32					stage;			// 28, name copied from Tweaks
	TileRect				*tile2C;		// 2C
	TileRect				*tile30;		// 30
	TileRect				*tile34;		// 34
	TileImage				*tile38;		// 38
	TileText				*tile3C;		// 3C
	TileImage				*tile40;		// 40
	TileImage				*tile44;		// 44
	TileText				*tile48;		// 48
	TileImage				*tile4C;		// 4C
	TileImage				*tile50;		// 50
	TileImage				*tile54;		// 54
	TileText				*tile58;		// 58
	TileText				*tile5C;		// 5C
	TileImage				*tile60;		// 60
	TileImage				*tile64;		// 64
	TileImage				*tile68;		// 68
	TESObjectREFR			*targetRef;		// 6C
	UInt32					lockLevel;		// 70
	UInt32					skillLevel;		// 74
	float					fSkillLevel;	// 78
	UInt32					unk7C;			// 7C
	UInt32					unk80;			// 80
	float					flt84;			// 84
	UInt32					sweetSpotLen;	// 88
	float					cylinderAngle;	// 8C
	float					pickAngle;		// 90
	float					pickHealth;		// 94
	bool					isForceRotate;	// 98, credits to Stewie
	UInt8					byte99;			// 99
	UInt8					pad9A[2];		// 99
	NiControllerSequence	*ctrlSeq9C;		// 9C
	NiControllerSequence	*ctrlSeqA0;		// A0
	NiControllerManager		*ctrlManager;	// A4
	NiControllerSequence	*ctrlSeqA8;		// A8
	NiControllerSequence	*ctrlSeqAC;		// AC
	NiControllerSequence	*ctrlSeqB0;		// B0
	NiQuaternion			quaternionB4;	// B4
	NiQuaternion			quaternionC4;	// C4
	NiQuaternion			quaternionD4;	// D4

	static LockPickMenu* GetSingleton() { return *(LockPickMenu**)0x11DA204; }; //copied from Tweaks
};
STATIC_ASSERT(sizeof(LockPickMenu) == 0xE4);

// Code stolen from lStewieAl
class LevelUpMenu : public Menu
{
public:
	LevelUpMenu();
	~LevelUpMenu();

	enum Buttons
	{
		kLevelUp_Reset = 0x6,
		kLevelUp_Done = 0x7,
		kLevelUp_Back = 0x8,
		kLevelUp_Skill = 0xB,
		kLevelUp_Perk = 0xC,
		kLevelUp_Minus = 0xD,
		kLevelUp_Plus = 0xE,
	};
	enum Pages
	{
		kSkillSelection = 0,
		kPerkSelection = 1,
		kCloseMenu = 2,  // (any value >= 2 could work)
	};

	void SetCurrentPage(Pages newPage) { ThisStdCall(0x785830, this, newPage); }
	void SetCurrentPage(int newPage) { ThisStdCall(0x785830, this, newPage); }
	void SetChooseSkillOrPerkNumberText() { ThisStdCall(0x785990, this); }
	
	// Can change numSkillPointsToAssign.
	void SetupSkillAndPerkListBoxes() { ThisStdCall(0x785540, this); }

	// Capped by the max amount of available perks.
	// Call this before calling SetCurrentPage so the initial perk count is accurate (will be 1 otherwise).
	void SetNumPerksToAssign(int newCount)
	{
		auto const numAvailablePerks = perksList.Count();
		numPerksToAssign = std::min<UInt32>(newCount, numAvailablePerks);
	}

	static LevelUpMenu* GetSingleton() { return *(LevelUpMenu**)0x11D9FDC; }

	static LevelUpMenu* Create()
	{
		CdeclCall<void>(0x706270);
		return GetSingleton();
	}
	
	// Has a workaround for the bug that occurs when closing the menu on the same frame it was opened.
	void Close()
	{
		//== Force the closure of this new LevelUpMenu
		// In order to pass the first check for the function called at 0x785265 (Menu::SetFadeOut, check at 0xA1D92A), set title tile visibility to non-null.
		tile->SetFloat(kTileValue_visible, 1);
		SetCurrentPage(kCloseMenu);  // close the menu (will flash in/out nearly instantly). 
	}

	UInt32 currentPage; // 0 for skills, 1 for perks
	TileText* tileTitle;
	TileImage* tileSkills;
	TileImage* tilePerks;
	TileImage* tileSelectionIcon;
	TileText* tileSelectionText;
	TileText* tilePointCounter;
	TileImage* tileBtnReset;
	TileImage* tileBtnContinue;
	TileImage* tileBtnBack;
	TileImage* tileStatsIconBadge;
	UInt32 numAssignedSkillPoints;
	UInt32 numAssignedPerks;
	UInt32 numSkillPointsToAssign;  // Max amount, not the amount left.
	UInt32 numPerksToAssign;  // Max amount, not the amount left.
	ListBox<ActorValueCode> skillListBox;
	ListBox<BGSPerk> perkListBox;
	tList<BGSPerk> perksList; // perks to show in the perk listBox (including non-selectable ones, if gs_bHideUnavailablePerks = 1)
};
STATIC_ASSERT(sizeof(LevelUpMenu) == 0xCC);

// 44
class QuantityMenu : public Menu		// 1016
{
public:
	QuantityMenu();
	~QuantityMenu();

	virtual void		Unk_12(void);

	TileRect			*tile28;		// 28
	TileImage			*tile2C;		// 2C	QM_DecreaseArrow
	TileImage			*tile30;		// 30	QM_IncreaseArrow
	TileText			*tile34;		// 34
	TileImage			*tile38;		// 38
	TileImage			*tile3C;		// 3C
	float				currentQtt;		// 40
};
struct NiPoint3;
// 230
class MapMenu : public Menu				// 1023
{
public:
	MapMenu();
	~MapMenu();

	TileText						*tile028;		// 028	MM_MainRect\MM_HeadlineRect\MM_Headline_LocationInfo
	TileText						*tile02C;		// 02C	MM_MainRect\MM_HeadlineRect\MM_Headline_TimeDateInfo
	TileImage						*tile030;		// 030	MM_MainRect\MM_LocalMap_ClipWindow\MM_LocalMap_ParentImage
	TileImage						*tile034;		// 034	MM_MainRect\MM_LocalMap_ClipWindow\MM_LocalMapCursor
	TileImage						*tile038;		// 038	MM_MainRect\MM_WorldMap_ClipWindow\MM_WorldMap_ParentImage
	TileImage						*tile03C;		// 03C	MM_MainRect\MM_WorldMap_ClipWindow\MM_WorldMapCursor
	TileRect						*tile040;		// 040	MM_MainRect\MM_Highlight_ClipWindow\MM_MapHighlightBox
	TileImage						*tile044;		// 044	MM_MainRect\MM_QuestsList
	TileImage						*tile048;		// 048	MM_MainRect\MM_NotesList
	TileImage						*tile04C;		// 04C	MM_MainRect\MM_NotesList\MM_Notes_SelectedNoteHighlight
	TileImage						*tile050;		// 050	MM_MainRect\MM_RadioStationList
	TileImage						*tile054;		// 054	MM_MainRect\MM_ButtonRect\MM_ButtonA
	TileImage						*tile058;		// 058	MM_MainRect\MM_ButtonRect\MM_ButtonX
	TileRect						*tile05C;		// 05C	MM_MainRect\MM_DataRect
	TileImage						*tile060;		// 060	MM_MainRect\MM_DataRect\MM_DataTextRect
	TileImage						*tile064;		// 064	MM_MainRect\MM_DataRect\MM_QuestObjectivesList
	TileImage						*tile068;		// 068	MM_MainRect\MM_WaveformRect\MM_Waveform
	TileRect						*tile06C;		// 06C	MM_Tabline
	TileImage						*tile070;		// 070	MM_MainRect\MM_ButtonRect\MM_ButtonY
	TileImage						*tile074;		// 074	MM_MainRect\MM_ChallengeList
	TileImage						*tile078;		// 078	MM_MainRect\MM_ChallengeList\MM_Challenge_SelectedHighlight
	TileText						*tile07C;		// 07C	MM_MainRect\MM_Headline_ChallengeType
	UInt8							currentTab;		// 080
	UInt8							pad081[3];		// 081
	TileImage						*tile084;		// 084
	UInt32							unk088[8];		// 088
	BSSimpleArray<String>			arr0A8;			// 0A8
	UInt32							unk0B8[7];		// 0B8
	TileImage						*mapMarker;		// 0D4
	tList<TESObjectREFR>			mapMarkerList;	// 0D8
	tList<TESObjectREFR>			doorList;		// 0E0
	float							flt0E8;			// 0E8
	float							flt0EC;			// 0EC
	float							flt0F0;			// 0F0
	float							flt0F4;			// 0F4
	TESForm*						markerForm;		// 0F8
	NiPoint3						markerPos;		// 0FC
	TESObjectCELL					*cell108;		// 108
	TESWorldSpace					*wspc10C;		// 10C
	UInt32							unk110;			// 110
	TESObjectREFR					*lastExtDoor;	// 114
	TESObjectREFR					*selectedMarker;// 118
	TESObjectCELL					*cell11C;		// 11C
	UInt32							unk120[2];		// 120
	UInt32							unk128;			// 128
	bool							fogOfWar;		// 12C
	UInt8							pad12D[3];		// 12D
	ListBox<TESQuest>				questList;		// 130
	ListBox<BGSNote>				noteList;		// 160
	ListBox<TESObjectREFR>			radioRefList;	// 190
	ListBox<BGSQuestObjective>		objectiveList;	// 1C0
	ListBox<TESChallenge>			challengeList;	// 1F0
	BSSimpleArray<Tile>				arr220;			// 220
};
STATIC_ASSERT(sizeof(MapMenu) == 0x230);
// 8C
class RepairMenu : public Menu			// 1035
{
public:
	RepairMenu();
	~RepairMenu();

	TileRect				*tile28;		// 28
	TileImage				*tile2C;		// 2C
	TileRect				*tile30;		// 30
	TileImage				*tile34;		// 34
	TileRect				*tile38;		// 38
	TileRect				*tile3C;		// 3C
	TileText				*tile40;		// 40
	TileText				*tile44;		// 44
	TileText				*tile48;		// 48
	TileRect				*tile4C;		// 4C
	TileRect				*tile50;		// 50
	TileImage				*tile54;		// 54
	TileImage				*tile58;		// 58
	MenuItemEntryList		repairItems;	// 5C

	//Both copied from JIP
	__forceinline static RepairMenu* Get() { return *(RepairMenu**)0x11DA75C; }
	__forceinline static ContChangesEntry* Target() { return *(ContChangesEntry**)0x11DA760; }
};

// 5C
class TextEditMenu : public Menu		// 1051
{
public:
	TextEditMenu();
	~TextEditMenu();

	virtual void		Unk_12(void);

	TileText			*currTextTile;			// 28
	TileImage			*okButton;				// 2C
	TileText			*messageTitle;			// 30
	String				currentText;			// 34
	String				displayedText;			// 3C	Copy of currentText + cursor
	UInt32				cursorIndex;			// 44
	union
	{
		UInt32			maxPixelLength;			// 48
		struct
		{
			UInt16		minLength;				// 48
			UInt16		maxLength;				// 4A
		};
	};
	union
	{
		UInt32			fontID;					// 4C
		TileRect		*inputRect;				// 4C
	};
	UInt32				cursorBlink;			// 50	Value used for the cursor blink cycles (every 500ms)
	UInt8				cursorVisible;			// 54
	UInt8				isActive;				// 55
	UInt8				byte56;					// 56
	UInt8				miscFlags;				// 57
	union
	{
		bool			(*menuCallback)(char*);	// 58
		Script			*scriptCallback;		// 58
	};
};
STATIC_ASSERT(sizeof(TextEditMenu) == 0x5C);

typedef tList<ContChangesEntry> BarterItemList;

// 120
class BarterMenu : public Menu			// 1053
{
public:
	BarterMenu();
	~BarterMenu();

	TileImage			*tile028;		// 028
	TileImage			*tile02C;		// 02C
	TileImage			*tile030;		// 030
	TileText			*tile034;		// 034
	TileImage			*tile038;		// 038
	TileText			*tile03C;		// 03C
	TileImage			*tile040;		// 040
	TileImage			*tile044;		// 044
	TileText			*tile048;		// 048
	TileImage			*tile04C;		// 04C
	TileText			*tile050;		// 050
	TileImage			*tile054;		// 054
	TileRect			*tile058;		// 058
	TileImage			*tile05C;		// 05C
	TileRect			*tile060;		// 060
	TileRect			*tile064;		// 064
	TileRect			*tile068;		// 068
	TileRect			*tile06C;		// 06C
	TileRect			*tile070;		// 070
	TileImage			*tile074;		// 074
	TileImage			*tile078;		// 078
	TileRect			*tile07C;		// 07C
	TESObjectREFR		*merchantRef;	// 080
	float				barterTotalSum;	// 084
	UInt32				unk088;			// 088
	UInt32				playerGold;		// 08C
	UInt32				merchantGold;	// 090
	float				buyValueMult;	// 094
	float				sellValueMult;	// 098
	UInt32				leftFilter;		// 09C
	UInt32				rightFilter;	// 0A0
	UInt32				unk0A4;			// 0A4
	MenuItemEntryList	leftItems;		// 0A8
	MenuItemEntryList	rightItems;		// 0D8
	MenuItemEntryList	*currentItems;	// 108, points to either left/rightItems
	BarterItemList		leftBarter;		// 10C
	BarterItemList		rightBarter;	// 114
	UInt32				unk11C;			// 11C

	// Taken from JIP
	__forceinline static BarterMenu* Get() { return *reinterpret_cast<BarterMenu**>(0x11D8FA4); }
	__forceinline static ContChangesEntry* Selection() { return *reinterpret_cast<ContChangesEntry**>(0x11D8FA8); }

	Tile* GetTileForItem(ContChangesEntry* itemEntry) const
	{
		if (currentItems)
		{
			return currentItems->GetTileForItem(this->currentItems->GetSelected() /*itemEntry*/);
		}
		return nullptr;
	}

	// Accounts for "CalculateBuyPrice" perk effect, and Buy/Sell mults.
	// Also accounts for item condition and attached weapon mods.
	double CalculateItemPrice(ContChangesEntry* itemEntry) const
	{
		double value = -1.0;
		if (auto const tile = GetTileForItem(itemEntry))
			value = CdeclCall<double>(0x72ED00, tile, itemEntry);
		
		return value;
	}
};

// 1DC
class HackingMenu : public Menu			// 1055
{
public:
	HackingMenu();
	~HackingMenu();

	UInt32				unk028[85];		// 028
	UInt32				attemptsLeft;	// 17C
	UInt32				unk180[6];		// 180
	TESObjectREFR		*targetRef;		// 198
	UInt32				unk19C[16];		// 19C
};
STATIC_ASSERT(sizeof(HackingMenu) == 0x1DC);
/*
struct VATSTargetInfo
{
	UInt32 actionType;
	UInt8 isSuccess;
	UInt8 byte05;
	UInt8 isMysteriousStrangerVisit;
	UInt8 byte07;
	UInt8 remainingShotsToFire_Burst;
	UInt8 count09;
	UInt8 gap0A[2];
	TESObjectREFR* ref;
	UInt32 avCode;
	ActorHitData* hitData;
	float unk18;
	float unk1C;
	float apCost;
	UInt8 isMissFortuneVisit;
	UInt8 gap25[3];
};
STATIC_ASSERT(sizeof(VATSTargetInfo) == 0x28);
*/
// 144
class VATSMenu : public Menu			// 1056
{
public:
	VATSMenu();
	~VATSMenu();

	virtual void		Unk_12(void);

	UInt32				unk028;			// 028
	TileImage			*tile02C;		// 02C
	TileImage			*tile030;		// 030
	TileImage			*tile034;		// 034
	TileImage			*tile038;		// 038
	TileImage			*tile03C;		// 03C
	TileImage			*tile040;		// 040
	TileImage			*tile044;		// 044
	TileImage			*tile048;		// 048
	TileImage			*tile04C;		// 04C
	TileImage			*tile050;		// 050
	TileText			*tile054;		// 054
	TileText			*tile058;		// 058
	TileText			*tile05C;		// 05C
	TileText			*tile060;		// 060
	TileImage			*tile064;		// 064
	TileImage			*tile068;		// 068
	TileImage			*tile06C;		// 06C
	TileImage			*tile070;		// 070
	TileText			*tile074;		// 074
	TileRect			*tile078;		// 078
	TileRect			*tile07C;		// 07C
	TileRect			*tile080;		// 080
	TileImage			*tile084;		// 084
	TileRect			*tile088;		// 088
	TileImage			*tile08C;		// 08C
	TileImage			*tile090;		// 090
	TileImage			*tile094;		// 094
	TileImage			*tile098;		// 098
	TileText			*tile09C;		// 09C
	TileImage			*tile0A0;		// 0A0
	TileImage			*tile0A4;		// 0A4

	UInt32				unk0A8[2];		// 0A8
	ListBox<UInt32>		queuedActions;	// 0B0
	UInt32				unk0E0[18];		// 0E0
	TESObjectREFR		*targetRef;		// 128
	UInt32				unk12C;			// 12C
	void				*ptr130;		// 130
	float				unk134[3];		// 134
	UInt8				unk140;			// 140
	UInt8				pad141[3];		// 141

	// Taken from Tweaks
	static VATSMenu* GetSingleton() { return *(VATSMenu**)0x11DB0D4; };
	// Taken from Tweaks
	static TESObjectREFR* GetTarget() { return *(TESObjectREFR**)0x11F21CC; };
};

// FC
class ComputersMenu : public Menu		// 1057
{
public:
	ComputersMenu();
	~ComputersMenu();

	UInt32				unk28[33];		// 28
	TESObjectREFR		*targetRef;		// AC
	UInt32				unkB0[19];		// B0
};

// A0
class RepairServicesMenu : public Menu	// 1058
{
public:
	RepairServicesMenu();
	~RepairServicesMenu();

	TileText			*tile28;		// 28
	TileText			*tile2C;		// 2C
	TileImage			*tile30;		// 30
	TileImage			*tile34;		// 34
	TileRect			*tile38;		// 38
	TileRect			*tile3C;		// 3C
	TileRect			*tile40;		// 40
	TileText			*tile44;		// 44
	TileText			*tile48;		// 48
	TileText			*tile4C;		// 4C
	TileRect			*tile50;		// 50
	TileRect			*tile54;		// 54
	TileText			*tile58;		// 58
	TileImage			*tile5C;		// 5C
	TileImage			*tile60;		// 60
	TileImage			*tile64;		// 64
	MenuItemEntryList	itemList;		// 68
	UInt32				unk98;			// 98
	UInt8				skill;			// 9C
	UInt8				pad9D[3];		// 9D

	//Both copied from JIP
	__forceinline static RepairServicesMenu* Get() { return *(RepairServicesMenu**)0x11DA7F0; }
};

// 90
class ItemModMenu : public Menu			// 1061
{
public:
	ItemModMenu();
	~ItemModMenu();

	TileRect			*tile28;		// 28
	TileImage			*tile2C;		// 2C
	TileRect			*tile30;		// 30
	TileImage			*tile34;		// 34
	TileRect			*tile38;		// 38
	TileRect			*tile3C;		// 3C
	TileText			*tile40;		// 40
	TileText			*tile44;		// 44
	TileText			*tile48;		// 48
	TileRect			*tile4C;		// 4C
	TileRect			*tile50;		// 50
	TileImage			*tile54;		// 54
	TileImage			*tile58;		// 58
	TileText			*tile5C;		// 5C
	MenuItemEntryList	itemModList;	// 60

	//Both copied from JIP
	__forceinline static ItemModMenu* Get() { return *(ItemModMenu**)0x11D9F54; }
	__forceinline static ContChangesEntry* Target() { return *(ContChangesEntry**)0x11D9F58; }
};

// 88
class CompanionWheelMenu : public Menu	// 1075
{
public:
	CompanionWheelMenu();
	~CompanionWheelMenu();

	virtual void		Unk_12(void);

	UInt32				unk28[16];		// 28
	Actor				*companionRef;	// 68
	UInt32				unk6C[7];		// 6C
};

// 88
class TraitSelectMenu : public Menu		// 1076
{
public:
	TraitSelectMenu();
	~TraitSelectMenu();

	UInt32				unk28[24];		// 28
};

// 104
class RecipeMenu : public Menu			// 1077
{
public:
	RecipeMenu();
	~RecipeMenu();

	TileImage					*tile028;		// 028	RM_Items_LeftFilterArrow
	TileText					*tile02C;		// 02C	RM_ItemsTitle
	TileImage					*tile030;		// 030	RM_Items_RightFilterArrow
	TileImage					*tile034;		// 034	RM_Items_InventoryList
	TileText					*tile038;		// 038	RM_MadeAtVariable
	TileText					*tile03C;		// 03C	RM_SkillRequirement
	TileImage					*tile040;		// 040	RM_Items_IngredientList
	TileImage					*tile044;		// 044	RM_ButtonX
	TileImage					*tile048;		// 048	RM_ButtonB
	TileImage					*tile04C;		// 04C	RM_ItemIcon
	TileRect					*tile050;		// 050	RM_ItemData
	TileText					*tile054;		// 054	RM_Items_IngredientList
	TileText					*tile058;		// 058	RM_ContainerTitle
	TileText					*tile05C;		// 05C	RM_SkillRequirementHeader
	TESObjectREFR				*sourceRef;		// 060
	TESRecipeCategory			*category;		// 064
	UInt32						unk068;			// 068
	ListBox<TESRecipe>			recipeList;		// 06C
	ListBox<TESRecipe>			*unk09C;		// 09C
	ListBox<RecipeComponent>	componentList;	// 0A0
	ListBox<Condition>			conditionList;	// 0D0
	UInt32						unk100;			// 100
};

// E88
class CaravanMenu : public Menu			// 1083
{
public:
	CaravanMenu();
	~CaravanMenu();

	UInt32					unk028[54];		// 028
	TESObjectREFR			*opponentRef;	// 100
	UInt32					unk104[865];	// 104
};

// 8C
class TraitMenu : public Menu			// 1084
{
public:
	TraitMenu();
	~TraitMenu();

	virtual void		Unk_12(void);

	TileText			*tile28;		// 28	LUM_Headline_Title
	TileImage			*tile2C;		// 2C	LUM_PerkList
	TileImage			*tile30;		// 30	LUM_SelectionIcon
	TileText			*tile34;		// 34	TM_DescriptionText
	TileText			*tile38;		// 38	LUM_PointCounter
	TileImage			*tile3C;		// 3C	LUM_ResetButton
	TileImage			*tile40;		// 40	LUM_ContinueButton
	TileImage			*tile44;		// 44	stats_icon_badge
	TileImage			*tile48;		// 48	TM_DescriptionScrollbar
	UInt32				numSelected;	// 4C
	UInt32				maxSelect;		// 50
	ListBox<BGSPerk>	perkListBox;	// 54
	tList<BGSPerk>		perkList;		// 84
};
// ??

// 08
class SkyObject
{
public:
	SkyObject();
	~SkyObject();

	virtual SkyObject	*Destroy(bool doFree);
	virtual void		Fn_01(void);
	virtual void		Fn_02(NiNode *niNode);
	virtual void		Update(Sky *sky, float value);

	NiNode				*node04;	// 04
};

// 1C
class Atmosphere : public SkyObject
{
public:
	Atmosphere();
	~Atmosphere();

	virtual void		Fn_04(NiNode *niNode, NiRefObject *unk);

	NiNode				*node08;	// 08
	BSFogProperty		*fogProp;	// 0C	Same as *0x11DEB00
	NiRefObject			*object10;	// 10
	NiRefObject			*object14;	// 14
	UInt8				byte18;		// 18
	UInt8				pad19[3];	// 19
};

// 10
class Stars : public SkyObject
{
public:
	Stars();
	~Stars();

	NiNode			*node08;	// 08
	float			flt0C;		// 0C
};

// 2C
class Sun : public SkyObject
{
public:
	Sun();
	~Sun();

	NiBillboardNode		*node08;		// 08
	NiBillboardNode		*node0C;		// 0C
	NiTriShape			*shape10;		// 10
	NiTriShape			*shape14;		// 14
	UInt32				unk18;			// 18
	NiDirectionalLight	*sunLight;		// 1C	Same as g_TES->directionalLight
	float				flt20;			// 20
	UInt8				byte24;			// 24
	UInt8				byte25;			// 25
	UInt8				byte26;			// 26
	UInt8				byte27;			// 27
	BSShaderAccumulator	*shaderAccum;	// 28
};

// 5C
class Clouds : public SkyObject
{
public:
	Clouds();
	~Clouds();

	NiAVObject			*layer0;	// 08	(NiTriStrips)
	NiAVObject			*layer1;	// 0C		"
	NiAVObject			*layer2;	// 10		"
	NiAVObject			*layer3;	// 14		"
	UInt32				unk18[4];	// 18
	float				flt28;		// 28
	float				flt2C;		// 2C
	float				flt30;		// 30
	float				flt34;		// 34
	float				flt38;		// 38
	float				flt3C;		// 3C
	float				flt40;		// 40
	float				flt44;		// 44
	float				flt48;		// 48
	float				flt4C;		// 4C
	float				flt50;		// 50
	float				flt54;		// 54
	UInt32				numLayers;	// 58
};

// 7C
class Moon : public SkyObject
{
public:
	Moon();
	~Moon();

	virtual void	Refresh(NiNode *niNode, const char *moonStr);

	NiNode			*node08;			// 08
	NiNode			*node0C;			// 0C
	NiTriShape		*shape10;			// 10
	NiTriShape		*shape14;			// 14
	String			moonTexture[8];		// 18
					//	0	Full Moon
					//	1	Three Wan
					//	2	Half Wan
					//	3	One Wan
					//	4	No Moon
					//	5	One Wax
					//	6	Half Wax
					//	7	Three Wax
	float			flt58;				// 58
	float			flt5C;				// 5C
	float			flt60;				// 60
	float			flt64;				// 64
	float			flt68;				// 68
	UInt32			unk6C;				// 6C
	UInt32			unk70;				// 70
	float			flt74;				// 74
	float			flt78;				// 78
};

// 18
class Precipitation
{
public:
	Precipitation();
	~Precipitation();

	virtual Precipitation	*Destroy(bool doFree);

	NiNode		*node04;	// 04
	NiNode		*node08;	// 08
	UInt32		unk0C;		// 0C
	float		unk10;		// 10
	UInt32		unk14;		// 14
};

// 1C
class ImageSpaceModifierInstance : public NiObject
{
public:
	ImageSpaceModifierInstance();
	~ImageSpaceModifierInstance();

	virtual void	Unk_23(void);
	virtual void	Unk_24(void);
	virtual void	Unk_25(void);
	virtual void	Unk_26(UInt32 arg);

	UInt8					hidden;			// 08
	UInt8					pad09[3];		// 09
	float					percent;		// 0C
	NiObject				*obj10;			// 10
	float					flt14;			// 14
	UInt32					unk18;			// 18
};

// 30
class ImageSpaceModifierInstanceForm : public ImageSpaceModifierInstance
{
public:
	ImageSpaceModifierInstanceForm();
	~ImageSpaceModifierInstanceForm();

	TESImageSpaceModifier	*imageSpace;	// 1C
	void					*ptr20;			// 20
	float					flt24;			// 24
	NiObject				*obj28;			// 28
	float					flt2C;			// 2C
};

// 30
class ImageSpaceModifierInstanceDOF : public ImageSpaceModifierInstance
{
public:
	ImageSpaceModifierInstanceDOF();
	~ImageSpaceModifierInstanceDOF();

	float					flt1C;			// 1C
	float					flt20;			// 20
	float					flt24;			// 24
	float					flt28;			// 28
	UInt32					unk2C;			// 2C
};

// 44
class ImageSpaceModifierInstanceDRB : public ImageSpaceModifierInstance
{
public:
	ImageSpaceModifierInstanceDRB();
	~ImageSpaceModifierInstanceDRB();

	float					flt1C;			// 1C
	float					flt20;			// 20
	float					flt24;			// 24
	float					flt28;			// 28
	float					flt2C;			// 2C
	UInt32					unk30;			// 30
	UInt32					unk34;			// 34
	float					flt38;			// 38
	float					flt3C;			// 3C
	UInt32					unk40;			// 40
};

// 138
class Sky
{
public:
	Sky();
	~Sky();

	virtual Sky						*Destructor(bool doFree);

	NiNode							*niNode004;			// 004
	NiNode							*niNode008;			// 008
	TESClimate						*firstClimate;		// 00C
	TESWeather						*firstWeather;		// 010
	TESWeather						*weather014;		// 014
	TESWeather						*weather018;		// 018
	TESWeather						*weatherOverride;	// 01C
	Atmosphere						*atmosphere;		// 020
	Stars							*stars;				// 024
	Sun								*sun;				// 028
	Clouds							*clouds;			// 02C
	Moon							*masserMoon;		// 030
	Moon							*secundaMoon;		// 034
	Precipitation					*precipitation;		// 038
	NiVector3						vector03C;			// 03C
	NiColor							waterReflection;	// 048
	NiVector3						vector054;			// 054
	NiColor							sunAmbient;			// 060
	NiColor							sunDirectional;		// 06C
	NiVector3						vector078;			// 078
	NiVector3						vector084;			// 084
	NiVector3						vector090;			// 090
	NiVector3						vector09C;			// 09C
	NiVector3						vector0A8;			// 0A8
	NiVector3						vector0B4;			// 0B4
	NiColor							sunFog;				// 0C0
	float							windSpeed;			// 0CC
	float							windDirection;		// 0D0
	UInt32							unk0D4[6];			// 0D4
	float							gameHour;			// 0EC
	float							lastUpdateHour;		// 0F0
	float							weatherPercent;		// 0F4
	UInt32							unk0F8;				// 0F8
	UInt32							unk0FC;				// 0FC
	float							lightningFxPerc;	// 100
	UInt32							unk104;				// 104
	float							flt108;				// 108
	float							flt10C;				// 10C
	float							flt110;				// 110
	UInt32							unk114;				// 114
	UInt32							flags;				// 118
	ImageSpaceModifierInstanceForm	*ismif11C;			// 11C
	ImageSpaceModifierInstanceForm	*ismif120;			// 120
	ImageSpaceModifierInstanceForm	*ismif124;			// 124
	ImageSpaceModifierInstanceForm	*ismif128;			// 128
	float							flt12C;				// 12C
	float							flt130;				// 130
	float							flt134;				// 134

	void RefreshMoon();
	void RefreshClimate(TESClimate *climate, bool immediate = true);
	bool GetIsRaining();
	static Sky* GetSingleton()
	{
		return *reinterpret_cast<Sky**>(0x11CCB78);
	}
};
STATIC_ASSERT(sizeof(Sky) == 0x138);

// 04
class GridArray
{
public:
	GridArray();
	~GridArray();

	virtual void	*Destroy(bool doFree);
	virtual void	Fn_01(void);
	virtual void	Fn_02(void);
	virtual void	Fn_03(void);
	virtual bool	Fn_04(UInt32 arg1, UInt32 arg2);
	virtual void	Fn_05(UInt32 arg1, UInt32 arg2);
};

// 28
class GridCellArray : public GridArray
{
public:
	GridCellArray();
	~GridCellArray();

	virtual void	UnloadCellAtGridXY(UInt32 gridX, UInt32 gridY);
	virtual void	SetGridAtXYToNull(UInt32 gridX, UInt32 gridY);
	virtual void	CopyCellAtGridXYTo(UInt32 gridX1, UInt32 gridY1, UInt32 gridX2, UInt32 gridY2);
	virtual void	SwapCellsAtGridXYs(UInt32 gridX1, UInt32 gridY1, UInt32 gridX2, UInt32 gridY2);

	SInt32			worldX;			// 04	X coord of current cell within worldspace
	SInt32			worldY;			// 08	Y coord "
	UInt32			gridSize;		// 0C	Init'd to uGridsToLoad
	TESObjectCELL	**gridCells;	// 10	Size is gridSize^2
	float			posX;			// 14	worldX * 4096
	float			posY;			// 18	worldY * 4096
	UInt32			unk1C;			// 1C
	UInt8			byte20;			// 20
	UInt8			pad21[3];		// 21
	UInt32			unk24;			// 24
};

// 44
class LoadedAreaBound : public NiRefObject
{
public:
	LoadedAreaBound();
	~LoadedAreaBound();

	bhkPhantom							*phantoms[6];	// 08	Seen bhkAabbPhantom
	TESObjectCELL						*cell;			// 20
	NiTMapBase<bhkRigidBody*, UInt32>	boundsMap;		// 24
	float								flt34;			// 34
	float								flt38;			// 38
	float								flt3C;			// 3C
	float								flt40;			// 40
};
STATIC_ASSERT(sizeof(LoadedAreaBound) == 0x44);

// A0
struct WaterSurfaceManager
{
	// 30
	struct WaterGroup
	{
		TESWaterForm			*waterForm;		// 00
		UInt32					unk04;			// 04
		UInt32					unk08;			// 08
		float					flt0C;			// 0C	Always 1.0 ?
		float					waterHeight;	// 10
		UInt32					unk14;			// 14
		UInt32					unk18;			// 18
		float					flt1C;			// 1C	-flt0C
		float					flt20;			// 20	-waterHeight
		DList<TESObjectREFR>	waterPlanes;	// 24
	};

	struct Struct8C
	{
		UInt32		unk00;
		UInt32		unk04;
		UInt32		unk08;
	};

	UInt32								unk00;			// 00
	UInt32								unk04;			// 04
	NiObject							*object08;		// 08
	NiObject							*object0C;		// 0C
	NiObject							*object10;		// 10
	NiObject							*object14;		// 14
	NiObject							*object18;		// 18
	NiObject							*object1C;		// 1C	Seen NiSourceTexture
	NiObject							*object20;		// 20
	UInt32								unk24;			// 24
	UInt32								unk28;			// 28
	UInt32								unk2C;			// 2C
	UInt32								unk30;			// 30
	UInt32								unk34;			// 34
	UInt32								unk38;			// 38
	DList<WaterGroup>					waterGroups;	// 3C
	WaterGroup							*waterLOD;		// 48	(Assumed)
	NiTPointerMap<TESObjectREFR>		map4C;			// 4C
	NiTPointerMap<TESObjectREFR>		map5C;			// 5C
	NiTPointerMap<TESWaterForm>			map6C;			// 6C
	NiTMapBase<TESObjectREFR*, void*>	map7C;			// 7C
	Struct8C							unk8C;			// 8C
	float								flt98;			// 98
	UInt32								unk9C;			// 9C
};
STATIC_ASSERT(sizeof(WaterSurfaceManager) == 0xA0);

// C4
class TES
{
public:
	TES();
	~TES();

	virtual void		Fn_00(UInt32 arg1, UInt32 arg2, UInt32 arg3, UInt32 arg4, UInt32 arg5);

	UInt32								unk04;				// 04
	GridCellArray						*gridCellArray;		// 08
	NiNode								*niNode0C;			// 0C
	NiNode								*niNode10;			// 10
	NiNode								*niNode14;			// 14
	BSTempNodeManager					*tempNodeMgr;		// 18
	NiDirectionalLight					*directionalLight;	// 1C
	void								*ptr20;				// 20
	SInt32								extGridX;			// 24
	SInt32								extGridY;			// 28
	SInt32								extCoordX;			// 2C
	SInt32								extCoordY;			// 30
	TESObjectCELL						*currentInterior;	// 34
	TESObjectCELL						**interiorsBuffer;	// 38
	TESObjectCELL						**exteriorsBuffer;	// 3C
	UInt32								unk40[9];			// 40
	WaterSurfaceManager					*waterManager;		// 64
	Sky									*sky;				// 68
	tList<ImageSpaceModifierInstance>	activeIMODs;		// 6C
	UInt32								unk74[3];			// 74
	float								flt80;				// 80	Abs X distance from centre of grid.
	float								flt84;				// 84	Abs Y distance from centre of grid.
	TESWorldSpace						*currentWrldspc;	// 88
	tList<UInt32>						list8C;				// 8C
	tList<UInt32>						list94;				// 94
	tList<UInt32>						list9C;				// 9C
	QueuedFile							*unkA4;				// A4
	NiSourceTexture						*unkA8;				// A8
	QueuedFile							*unkAC;				// AC
	void								*ptrB0;				// B0
	UInt32								unkB4[2];			// B4
	NavMeshInfoMap						*navMeshInfoMap;	// BC
	LoadedAreaBound						*areaBound;			// C0

	bool GetTerrainHeight(float *posXY, float *result);
};
STATIC_ASSERT(sizeof(TES) == 0xC4);

// 188
class CombatController : public TESPackage
{
public:
	CombatController();
	~CombatController();

	struct Unk09C
	{
		UInt32									unk000[4];	// 000
		TESObjectWEAP							*weapon1;	// 010
		TESObjectWEAP							*weapon2;	// 014
		TESObjectWEAP							*weapon3;	// 018
		TESObjectWEAP							*weapon4;	// 01C
		UInt32									unk020;		// 020
		BSSimpleArray<TESObjectWEAP>			arr024;		// 024
		UInt32									unk034[36];	// 034
		void									*ptr0C4;	// 0C4
		UInt32									unk0C8[17];	// 0C8
		BSSimpleArray<PathingCoverLocation>		arr10C;		// 10C
		UInt32									unk11C[11];	// 11C
		BSSimpleArray<PathingCoverLocation>		arr148;		// 148
		UInt32									unk158[3];	// 158
		BSSimpleArray<UnreachableCoverLocation>	arr164;		// 164
		BSSimpleArray<UnreachableLocation>		arr174;		// 174
		UInt32									unk184[15];	// 184
		Actor									*actor1C0;	// 1C0
		CombatController						*cmbtCtrl;	// 1C4
		UInt32									unk1C8[22];	// 1C8
	};

	CombatActors					*combatActors;		// 080
	CombatProcedure					*combatProcedure1;	// 084
	CombatProcedure					*combatProcedure2;	// 088
	BSSimpleArray<CombatProcedure>	combatProcedures;	// 08C
	Unk09C							*struct09C;			// 09C
	void							*ptr0A0;			// 0A0
	UInt32							unk0A4;				// 0A4
	CombatAction					*combatAction;		// 0A8
	CombatGoal						*combatGoal;		// 0AC
	UInt32							unk0B0;				// 0B0
	float							flt0B4[2];			// 0B4
	Actor							*packageOwner;		// 0BC
	Actor							*packageTarget;		// 0C0
	UInt32							unk0C4[2];			// 0C4
	float							flt0CC;				// 0CC
	float							flt0D0;				// 0D0
	UInt8							byte0D4;			// 0D4
	UInt8							byte0D5;			// 0D5
	UInt8							pad0D6[2];			// 0D6
	float							flt0D8;				// 0D8
	float							flt0DC;				// 0DC
	float							flt0E0;				// 0E0
	UInt32							unk0E4[3];			// 0E4
	TESObjectWEAP					*weapon;			// 0F0
	TESCombatStyle					*combatStyle;		// 0F4
	UInt32							unk0F8[11];			// 0F8
	UInt8							byte124;			// 124
	bool							stopCombat;			// 125
	UInt8							byte126;			// 126
	UInt8							byte127;			// 127
	UInt32							unk128[8];			// 128
	float							flt148;				// 148
	UInt32							unk14C[15];			// 14C
};
STATIC_ASSERT(sizeof(CombatController) == 0x188);

struct FontHeightData
{
	float		heightBase;
	float		heightwGap;
};
extern FontHeightData s_fontHeightDatas[90];

// 54
struct FontInfo
{
	struct BufferData
	{
		float			lineHeight;		// 0000
		UInt32			unk0004[73];	// 0004
		UInt32			unk0128[458];	// 0128
		float			baseHeight;		// 0850
		float			flt0854;		// 0854
		float			flt0858;		// 0858
	};

	struct ButtonIcon;

	UInt8						isLoaded;	// 00
	UInt8						pad01[3];	// 01
	char						*filePath;	// 04
	UInt8						fontID;		// 08
	UInt8						pad09[3];	// 09
	NiTexturingProperty			*texProp;	// 0C
	UInt32						unk10[7];	// 10
	float						flt2C;		// 2C
	float						flt30;		// 30
	UInt32						unk34;		// 34
	BufferData					*bufferData;// 38
	UInt32						unk3C[2];	// 3C
	BSSimpleArray<ButtonIcon>	arr44;		// 44
};
STATIC_ASSERT(sizeof(FontInfo) == 0x54);

// 164 (24)
class FontManager
{
public:
	FontManager();
	~FontManager();

	FontInfo		*fontInfos[8];		// 00
	UInt8			byte20;				// 20
	UInt8			pad21[3];			// 21
	FontInfo		*extraFonts[80];	// 24

	//	outDims.x := width (pxl); outDims.y := height (pxl); outDims.z := numLines
	NiVector3 *GetStringDimensions(NiVector3 *outDims, const char *srcString, UInt32 fontID, UInt32 maxFlt = 0x7F7FFFFF, UInt32 startIdx = 0);
};

// 24
struct RadioEntry
{
	TESObjectREFR	*radioRef;
	void			*ptr04;
	UInt32			unk08[7];
};

// 18
class LoadedReferenceMap : public NiTPointerMap<TESObjectREFR>
{
public:
	LoadedReferenceMap();
	~LoadedReferenceMap();

	UInt32			unk10;		// 10
	UInt32			unk14;		// 14
};

// 8C
class BackUpPackage : public TESPackage
{
public:
	BackUpPackage();
	~BackUpPackage();

	virtual void	Unk_58(void);

	NiVector3		destPos;	// 80
};

// 229C
class DebugText
{
public:
	DebugText();
	~DebugText();

	virtual void	Unk_00(void);
	virtual void	Unk_01(UInt32 arg1, UInt32 arg2);
	virtual UInt32	Unk_02(UInt32 arg1, UInt32 arg2, UInt32 arg3, UInt32 arg4, UInt32 arg5, UInt32 arg6);
	virtual UInt32	Unk_03(UInt32 arg1, UInt32 arg2, UInt32 arg3, UInt32 arg4);
	virtual void	Unk_04(UInt32 arg1, UInt32 arg2, UInt32 arg3, UInt32 arg4, UInt32 arg5, UInt32 arg6);
	virtual UInt32	Unk_05(UInt32 arg1, UInt32 arg2, UInt32 arg3, UInt32 arg4, UInt32 arg5);
	virtual void	Unk_06(UInt32 arg1, UInt32 arg2, UInt32 arg3, UInt32 arg4, UInt32 arg5);
	virtual UInt32	Unk_07(UInt32 arg1, UInt32 arg2, UInt32 arg3, UInt32 arg4, UInt32 arg5, UInt32 arg6, UInt32 arg7);
	virtual UInt32	Unk_08(UInt32 arg1, UInt32 arg2, UInt32 arg3, UInt32 arg4, UInt32 arg5);
	virtual UInt32	Unk_09(UInt32 arg1, UInt32 arg2, UInt32 arg3, UInt32 arg4, UInt32 arg5, UInt32 arg6);
	virtual UInt32	Unk_0A(UInt32 arg1);
	virtual void	Unk_0B(UInt32 arg1, UInt32 arg2);

	struct DebugLine
	{
		float			offsetX;	// 00
		float			offsetY;	// 04
		UInt32			isVisible;	// 08
		NiNode			*node;		// 0C
		String			text;		// 10
		float			flt18;		// 18	Always -1.0
		NiColorAlpha	color;		// 1C
	};

	DebugLine		lines[200];		// 0004
	UInt32			unk2264[14];	// 2264

	static DebugText *GetSingleton();
	DebugLine *GetDebugInput();
};
STATIC_ASSERT(sizeof(DebugText) == 0x229C);

// 254
class BSSoundInfo
{
public:
	BSSoundInfo();
	~BSSoundInfo();

	UInt32			unk000[72];		// 000
	const char		*filePath;		// 120
	UInt32			unk124[76];		// 124
};

// 230
class BSGameSound
{
public:
	BSGameSound();
	~BSGameSound();

	virtual BSGameSound	*Destroy(bool doFree);
	virtual void	Unk_01(void);
	virtual void	Unk_02(void);
	virtual void	Unk_03(void);
	virtual void	Unk_04(void);
	virtual void	SetPaused(bool doSet);
	virtual void	Unk_06(void);
	virtual void	Unk_07(void);
	virtual void	Unk_08(void);
	virtual void	Unk_09(void);
	virtual void	Unk_0A(void);
	virtual void	Unk_0B(void);
	virtual void	Unk_0C(void);
	virtual bool	Unk_0D(void);
	virtual bool	Unk_0E(void);
	virtual bool	Unk_0F(float arg1);
	virtual void	Unk_10(void);
	virtual bool	Unk_11(void);
	virtual void	Unk_12(void);
	virtual void	Unk_13(float arg1, float arg2, float arg3);
	virtual void	Unk_14(float arg1, float arg2, float arg3);
	virtual void	Unk_15(NiVector3 &arg1);
	virtual void	Unk_16(void);
	virtual void	Unk_17(float arg1, float arg2);
	virtual void	Unk_18(UInt16 arg1, UInt16 arg2, UInt16 arg3, UInt16 arg4, UInt16 arg5);
	virtual bool	Unk_19(float arg1);
	virtual float	Unk_1A(void);
	virtual void	Seek(UInt32 timePoint);

	UInt32			mapKey;					// 004
	UInt32			soundFlags;				// 008
	UInt32			flags00C;				// 00C
	UInt32			stateFlags;				// 010
	UInt32			duration;				// 014
	UInt16			staticAttenuation;		// 018	dB * -1000
	UInt16			unk01A;					// 01A
	UInt16			unk01C;					// 01C
	UInt16			unk01E;					// 01E
	UInt16			unk020;					// 020
	UInt16			unk022;					// 022
	float			volume;					// 024	0.0 to 1.0
	float			flt028;					// 028
	float			flt02C;					// 02C
	UInt32			unk030;					// 030
	UInt16			baseSamplingFreq;		// 034
	char			filePath[254];			// 036	Originally: filePath[260]
	TESSound* sourceSound;			// 134	"Stolen" from filePath
	float			frequencyMod;			// 138	^
	float			maxAttenuationDist;		// 13C
	float			minAttenuationDist;		// 140
	UInt32			pathHashFile;			// 144
	UInt32			pathHashFolder;			// 148
	UInt32			unk14C;					// 14C
	float			flt150;					// 150
	UInt32			unk154;					// 154
	SInt8			randFrequencyShift;		// 158
	UInt8			byte159;				// 159
	UInt16			samplingFreq;			// 15A
	UInt32			unk15C;					// 15C
	UInt32			unk160;					// 160
	UInt32			unk164;					// 164
	UInt32			unk168;					// 168
	UInt32			unk16C;					// 16C
	UInt32			unk170;					// 170
	UInt32			unk174[5];				// 174
	UInt32			priority;				// 188
	UInt32			unk18C[3];				// 18C
};
STATIC_ASSERT(sizeof(BSGameSound) == 0x198);

enum AudioRequestTypes
{
	kRequestType_Stop = 3,
	kRequestType_Stop2 = 4,
	kRequestType_Delay = 5,
	kRequestType_StopSoundFadeOutTime = 9,
	kRequestType_DialogueFadeInOrOut = 0xD,
	kRequestType_RecalculateVolumesForChangesToMasterVolume = 0xE,
	kRequestType_Volume = 0x10,
	kRequestType_FrequencyAdjustment = 0x14,
	kRequestType_FadeAllSFX = 0x18,
	kRequestType_SetState400ForSomeSounds = 0x1A,
	kRequestType_ClearState400ForSomeSounds = 0x1B,
	kRequestType_SetState400ForSomeSounds2 = 0x1C,
	kRequestType_ClearState400ForSomeSounds2 = 0x1D,
	kRequestType_SoundAtPos = 0x1E,
	kRequestType_Attenuation = 0x21,
	kRequestType_ReverbAttenuation = 0x22,
	kRequestType_PlayWithMinMaxDistance = 0x23,
	kRequestType_SetsPlayingSoundClearStateBit200 = 0x26,
	kRequestType_PlayAtNode = 0x27,
	kRequestType_NiNodeSound = 0x29,
	kRequestType_StopAllSoundsWithFlags = 0x2A,
	kRequestType_SetAudioListenerPosition = 0x38,
	kRequestType_HasCompletionCallback = 0x3A,
	kRequestType_HasSomeCallback = 0x3B,
	kRequestType_StartsAtEndsAt = 0x3E,
	kRequestType_MultiThreaded = 0x35,
	kRequestType_ToggleFirstPersonForPlayingSound = 0x40,
	kRequestType_Priority = 0x41,
	kRequestType_Speed = 0x42
};

union FunctionArg
{
	void* pVal;
	float		fVal;
	UInt32		uVal;
	SInt32		iVal;

	FunctionArg& operator=(void* other)
	{
		pVal = other;
		return *this;
	}
	FunctionArg& operator=(float other)
	{
		fVal = other;
		return *this;
	}
	FunctionArg& operator=(UInt32 other)
	{
		uVal = other;
		return *this;
	}
	FunctionArg& operator=(SInt32 other)
	{
		iVal = other;
		return *this;
	}
};


// 20
struct AudioRequestData
{
	UInt32				type;		// 00
	UInt32				soundKey;	// 04
	FunctionArg			value1;		// 08
	FunctionArg			value2;		// 0C
	NiNode* niNode;	// 10
	NiVector3			pos;		// 14
};
// 188
class BSAudioManager
{
public:
	virtual void				Destroy(bool doFree);

	// 10
	struct AudioRequest
	{
		UInt32				count;			// 00
		UInt8				byte04;			// 04
		UInt8				pad05[3];		// 05
		AudioRequestData* requestData;	// 08
		UInt32				tickCount;		// 0C
	};

	UInt32						unk004[8];			// 004
	AudioRequest				request024;			// 024
	AudioRequest				request034;			// 034
	AudioRequest				request044;			// 044
	NiTPointerMap<BSGameSound>	playingSounds;		// 054
	NiTPointerMap<BSSoundInfo>	playingSoundInfos1;	// 064
	NiTPointerMap<BSSoundInfo>	playingSoundInfos2;	// 074
	NiTPointerMap<NiAVObject>	soundPlayingObjects;// 084
	DList<BSGameSound>			cachedSounds;		// 094
	UInt32						unk0A0;				// 0A0
	UInt32						unk0A4;				// 0A4
	float						flt0A8;				// 0A8
	LPCRITICAL_SECTION			cs0AC;				// 0AC
	UInt32						unk0B0[5];			// 0B0
	LPCRITICAL_SECTION			cs0C4;				// 0C4
	UInt32						unk0C8[5];			// 0C8
	LPCRITICAL_SECTION			cs0DC;				// 0DC
	UInt32						unk0E0[5];			// 0E0
	LPCRITICAL_SECTION			cs0F4;				// 0F4
	UInt32						unk0F8[5];			// 0F8
	LPCRITICAL_SECTION			cs10C;				// 10C
	UInt32						unk110[5];			// 110
	DList<void>					list124;			// 124
	UInt32						lastTickCount;		// 130
	UInt8						byte134;			// 134
	UInt8						byte135;			// 135
	UInt8						pad136[2];			// 136
	UInt32						unk138;				// 138
	BSAudioManagerThread* audioMgrThread;	// 13C
	float						volumes[12];		// 140
	//	0	Master
	//	1	Foot
	//	2	Voice
	//	3	Effects
	//	4	Music
	//	5	Radio
	UInt32						unk170;				// 170
	UInt8						byte174;			// 174
	UInt8						byte175;			// 175
	UInt8						pad176[2];			// 176
	UInt32						unk178;				// 178
	UInt32						unk17C;				// 17C
	UInt32						nextMapKey;			// 180
	UInt8						byte184;			// 184
	UInt8						pad185[3];			// 185
};
STATIC_ASSERT(sizeof(BSAudioManager) == 0x188);


// D8
class FORenderedMenu
{
public:
	FORenderedMenu();
	~FORenderedMenu();

	virtual void    Destructor(bool doFree);
	virtual void    Unk_01(void);
	virtual void    Unk_02(void);
	virtual void    Unk_03(void);
	virtual void    Unk_04(void);
	virtual void    Unk_05(void);
	virtual void    Unk_06(void);
	virtual void    Unk_07(void);
	virtual void    Unk_08(void);
	virtual void    Unk_09(void);
	virtual void    Unk_0A(void);
	virtual void    Unk_0B(void);
	virtual void    Unk_0C(void);
	virtual void    Unk_0D(void);
	virtual void    Unk_0E(void);
	virtual void    Unk_0F(void);
	virtual void    Unk_10(void);
	virtual void    Unk_11(void);
	virtual void    Unk_12(void);
	virtual void    Unk_13(void);
	virtual void    Unk_14(void);

	NiAVObject* unk04;
	BSFadeNode* node08;
	UInt32 unk0C;
	NiSourceTexture* srcTexture;
	NiNode* node14;
	TileMenu* tileMenu;
	UInt32 unk1C[2];
	NiCamera* camera;
	UInt8 byte028;
	UInt8 gap028[3];
	UInt32 unk02C[5];
	UInt32 blurRadius;
	UInt32 blurIntensity;
	UInt32 unk048;
	UInt8 byte04C;
	UInt8 byte04D;
	UInt8 gap04E[2];
	float time050;
	float burstDuration;
	float burstIntensity2;
	float burstIntensity;
	UInt32 unk060[30];
};
class FOPipboyManager : public FORenderedMenu
{
public:
	FOPipboyManager();
	~FOPipboyManager();

	NiNode* pipboyScreenNode0D8;
	NiNode* unk0DC;
	NiTriStrips* unk0C0;
	NiRefObject* unk0C4;
	NiTriStrips* pipboyLightButton[3];
	NiNode* pipboyLightGlow[3];
	NiTriStrips* scrollKnobs[3];
	float unk10C[3];
	float pipboyKnobScrollPositions[3];
	float pipboyKnobScrollRates[3];
	float tabKnobMinPosition;
	UInt32 unk134;
	UInt32 unk138;
	UInt32 unk13C;
	float tabKnobMaxPosition;
	UInt8 byte144;
	UInt8 gap145[3];
	UInt32 unk148;
	UInt32 unk14C;
	UInt8 byte150;
	UInt8 gap151[3];
	Sound sound154;
	UInt8 byte160;
	UInt8 byte161;
	UInt8 byte162;
	UInt8 gap163;
	float time164;
	float lightEffectFadeDuration;
	UInt32 unk16C;
};
STATIC_ASSERT(sizeof(FOPipboyManager) == 0x170);

enum
{
	kMusicState_Pause =		1 << 2,
	kMusicState_Stop =		1 << 3,
	kMusicState_Play =		1 << 4,
	kMusicState_Loop =		1 << 5,
};

// 288
struct PlayingMusic
{
	char					track1Path[MAX_PATH];	// 000
	void					*ptr104;				// 104
	char					track2Path[MAX_PATH];	// 108
	UInt32					unk20C;					// 20C
	float					flt210;					// 210
	float					flt214;					// 214
	float					flt218;					// 218
	float					flt21C;					// 21C
	UInt8					track1Flags;			// 220
	UInt8					track2Flags;			// 221
	UInt8					pad222[2];				// 222
	UInt32					unk224;					// 224
	UInt32					unk228[8];				// 228
	float					flt248;					// 248
	float					flt24C;					// 24C
	float					flt250;					// 250
	float					flt254;					// 254
	UInt32					unk258;					// 258
	UInt32					unk25C[8];				// 25C
	UInt32					track1Active;			// 27C
	UInt32					unk280;					// 280
	MediaLocationController	*medLocCtrl;			// 284
};
STATIC_ASSERT(sizeof(PlayingMusic) == 0x288);

// 34
struct GameTimeGlobals
{
	TESGlobal		*year;			// 00
	TESGlobal		*month;			// 04
	TESGlobal		*day;			// 08
	TESGlobal		*hour;			// 0C
	TESGlobal		*daysPassed;	// 10
	TESGlobal		*timeScale;		// 14
	UInt32			unk18;			// 18
	bool			gameLoaded;		// 1C
	UInt8			pad1D[3];		// 1D
	UInt32			unk20;			// 20
	UInt32			unk24;			// 24
	UInt32			unk28;			// 28
	float			lastUpdHour;	// 2C
	UInt32			initialized;	// 30

	float GetDaysPassed(int bgnYear = 2281, int bgnMonth = 9, int bgnDay = 13);
};

// 10
struct EffectArchTypeEntry
{
	const char				*name;
	ActiveEffectCreate		callback;
	UInt32					unk08[2];
};

// 10
struct EntryPointConditionInfo
{
	const char		*entryPoint;
	UInt8			numTabs;
	UInt8			pad01[3];
	const char		**runOn;
	UInt8			byte08;
	UInt8			pad09[3];
};

// 24
struct AnimGroupInfo
{
	const char	*name;			// 00
	UInt32		unk04;			// 04
	UInt32		sequenceType;	// 08
	UInt32		unk0C;			// 0C
	UInt32		unk10;			// 10
	UInt32		unk14[4];		// 14
};

struct PCMiscStat
{
	const char	*name;
	UInt32		level;
};

// 08
struct TypeSignature
{
	char	signature[8];
};

// 14
class ExtraHavok : public BSExtraData
{
public:
	ExtraHavok();
	virtual ~ExtraHavok();

	bhkWorld		*world;			// 0C
	UInt32			unk10;			// 10
};

// 10
class ExtraRegionList : public BSExtraData
{
public:
	ExtraRegionList();
	virtual ~ExtraRegionList();

	TESRegionList	*regionList;	// 0C
};

// 24
class SeenData
{
public:
	SeenData();
	~SeenData();

	virtual void	*Destroy(bool doFree);
	virtual void	Unk_01(void);
	virtual void	Unk_02(void);
	virtual void	Unk_03(void);
	virtual void	Unk_04(void);
	virtual void	Unk_05(void);
	virtual void	Unk_06(void);

	UInt32			alphaLevels[8];		// 04

	bool GetBitSeen(UInt32 row, UInt32 column);
};

// 2C
class IntSeenData : public SeenData
{
public:
	IntSeenData();
	~IntSeenData();

	SInt8			segmentX;		// 24
	SInt8			segmentY;		// 25
	UInt8			pad26[2];		// 26
	IntSeenData		*nextSegment;	// 28

	IntSeenData *GetSectionSeenData(int sectionX, int sectionY);
};

// 10
class ExtraSeenData : public BSExtraData
{
public:
	ExtraSeenData();
	virtual ~ExtraSeenData();

	SeenData		*data;		// 0C
};

// 10
class ExtraCellWaterType : public BSExtraData
{
public:
	ExtraCellWaterType();
	virtual ~ExtraCellWaterType();

	TESWaterForm	*waterForm;		// 0C

	static ExtraCellWaterType* __stdcall Create(TESWaterForm *_waterForm);
};

// 10
class ExtraCellMusicType : public BSExtraData
{
public:
	ExtraCellMusicType();
	virtual ~ExtraCellMusicType();

	BGSMusicType	*musicType;

	static ExtraCellMusicType* __stdcall Create(BGSMusicType *_musicType);
};

// 10
class ExtraCellClimate : public BSExtraData
{
public:
	ExtraCellClimate();
	virtual ~ExtraCellClimate();

	TESClimate		*climate;		// 0C

	static ExtraCellClimate* __stdcall Create(TESClimate *_climate);
};

// 10
class ExtraPersistentCell : public BSExtraData
{
public:
	ExtraPersistentCell();
	virtual ~ExtraPersistentCell();

	TESObjectCELL	*persistentCell;	// 0C
};

// 24
class ExtraStartingPosition : public BSExtraData
{
public:
	ExtraStartingPosition();
	virtual ~ExtraStartingPosition();

	NiVector3	posVector;	// 0C
	NiVector3	rotVector;	// 18
};

// 10
class ExtraAnim : public BSExtraData
{
public:
	ExtraAnim();
	virtual ~ExtraAnim();

	AnimData		*animData;	// 0C
};

// 1C
class ExtraPackage : public BSExtraData
{
public:
	ExtraPackage();
	virtual ~ExtraPackage();

	TESPackage		*package;	// 0C
	UInt32			unk10[3];	// 10
};

// 10
class ExtraFollower : public BSExtraData
{
public:
	ExtraFollower();
	virtual ~ExtraFollower();

	tList<Actor>	*followers;		// 0C
};

// 10
class ExtraOriginalReference : public BSExtraData
{
public:
	ExtraOriginalReference();
	virtual ~ExtraOriginalReference();

	TESObjectREFR	*originalRef;		// 0C

	static ExtraOriginalReference* __stdcall Create(TESObjectREFR *_originalRef);
};

// 10
class ExtraLight : public BSExtraData
{
public:
	ExtraLight();
	virtual ~ExtraLight();

	struct Data
	{
		NiPointLight	*pointLight;
		float			flt04;
	};

	Data		*data;		// 0C
};

// 14
class ExtraEnableStateChildren : public BSExtraData
{
public:
	ExtraEnableStateChildren();
	virtual ~ExtraEnableStateChildren();

	tList<TESObjectREFR>	children;	// 0C

	static ExtraEnableStateChildren* Create();
};

// 10
class ExtraEnableStateParent : public BSExtraData
{
public:
	ExtraEnableStateParent();
	virtual ~ExtraEnableStateParent();

	TESObjectREFR	*parent;	// 0C
	static ExtraEnableStateParent* Create(TESObjectREFR* parent = nullptr);
};

// 10
class ExtraItemDropper : public BSExtraData
{
public:
	ExtraItemDropper();
	virtual ~ExtraItemDropper();

	TESObjectREFR		*dropper;	// 0C
};

// 14
class ExtraDroppedItemList : public BSExtraData
{
public:
	ExtraDroppedItemList();
	virtual ~ExtraDroppedItemList();

	tList<TESObjectREFR>	itemRefs;	// 0C
};

// 10
class ExtraMerchantContainer : public BSExtraData
{
public:
	ExtraMerchantContainer();
	virtual ~ExtraMerchantContainer();

	TESObjectREFR	*containerRef;	// 0C
};

// 10
class ExtraRefractionProperty : public BSExtraData
{
public:
	ExtraRefractionProperty();
	virtual ~ExtraRefractionProperty();

	float			refraction;		// 0C
};

// 10
class ExtraPoison : public BSExtraData
{
public:
	ExtraPoison();
	virtual ~ExtraPoison();

	AlchemyItem		*poisonEffect;	// 0C
};

// 10
class ExtraNorthRotation : public BSExtraData
{
public:
	ExtraNorthRotation();
	virtual ~ExtraNorthRotation();

	float		rotation;		// 0C
};

// 10
class ExtraStartingWorldOrCell : public BSExtraData
{
public:
	ExtraStartingWorldOrCell();
	virtual ~ExtraStartingWorldOrCell();

	TESForm			*worldOrCell;	// 0C
};

// 10
class ExtraTerminalState : public BSExtraData
{
public:
	ExtraTerminalState();
	~ExtraTerminalState();

	UInt8			lockedOut;	// 0C
	UInt8			lockLevel;	// 0D unlocked: 0xFE
	UInt16			pad;

	static ExtraTerminalState *Create();
};

// 10
class ExtraLinkedRef : public BSExtraData
{
public:
	ExtraLinkedRef();
	virtual ~ExtraLinkedRef();

	TESObjectREFR	*linkedRef;		// 0C

	static ExtraLinkedRef* __stdcall Create(TESObjectREFR *_linkedRef = NULL);
};

// 14
class ExtraLinkedRefChildren : public BSExtraData
{
public:
	ExtraLinkedRefChildren();
	virtual ~ExtraLinkedRefChildren();

	tList<TESObjectREFR>	children;	// 0C
};

// 18
class ExtraActivateRef : public BSExtraData
{
public:
	ExtraActivateRef();
	virtual ~ExtraActivateRef();

	struct parentRef
	{
		TESObjectREFR*	ref;
		float			delay;
	};
	tList<parentRef>	parentRefs;
	UInt32				flags;
};

// 10
class ExtraTalkingActor : public BSExtraData
{
public:
	ExtraTalkingActor();
	virtual ~ExtraTalkingActor();

	Actor			*actor;		// 0C
};

// 10
class ExtraObjectHealth : public BSExtraData
{
public:
	ExtraObjectHealth();
	virtual ~ExtraObjectHealth();

	float			health;		// 0C

	static ExtraObjectHealth* __stdcall Create(float _health);
};

// 10
class ExtraCellImageSpace : public BSExtraData
{
public:
	ExtraCellImageSpace();
	virtual ~ExtraCellImageSpace();

	TESImageSpace	*imageSpace;	// 0C

	static ExtraCellImageSpace* __stdcall Create(TESImageSpace *_imgSpace);
};

// 10
class ExtraRadius : public BSExtraData
{
public:
	ExtraRadius();
	virtual ~ExtraRadius();

	float			radius;		// 0C

	static ExtraRadius* __stdcall Create(float _radius);
};

// 10
class ExtraRadiation : public BSExtraData
{
public:
	ExtraRadiation();
	virtual ~ExtraRadiation();

	float			radiation;	// 0C
};

// 30
class ExtraDismemberedLimbs : public BSExtraData
{
public:
	ExtraDismemberedLimbs();
	virtual ~ExtraDismemberedLimbs();

	struct DismemberedLimb
	{
		UInt8				bodyPartID;
		UInt8				explodeChance;
		bool				explodeOnly;
		UInt8				byte03;
		BSSimpleArray<void>	*array04;
	};

	UInt16							dismemberedMask;	// 0C, checked at 0x4303E0
	UInt8							pad0E[2];			// 0E
	int								unk10;				// 10
	TESObjectWEAP					*weapon;			// 14
	int								unk18;				// 18
	bool							wasEaten;			// 1C
	UInt8							pad1D[3];			// 1D
	BSSimpleArray<DismemberedLimb>	dismemberedLimbs;	// 20
};

// 1C
class ExtraRadioData : public BSExtraData
{
public:
	ExtraRadioData();
	virtual ~ExtraRadioData();

	float				radius;			// 0C
	UInt32				rangeType;		// 10
	float				staticPerc;		// 14
	TESObjectREFR		*positionRef;	// 18
};

// 10
class ExtraPrimitive : public BSExtraData
{
public:
	ExtraPrimitive();
	virtual ~ExtraPrimitive();

	BGSPrimitive	*primitive;		// 0C

	static ExtraPrimitive* __stdcall Create(BGSPrimitive *_primitive = NULL);
};

// 10
class ExtraCollisionData : public BSExtraData
{
public:
	ExtraCollisionData();
	virtual ~ExtraCollisionData();

	UInt32			unk0C;			// 0C
};

// 10
class ExtraEncounterZone : public BSExtraData
{
public:
	ExtraEncounterZone();
	virtual ~ExtraEncounterZone();

	BGSEncounterZone	*zone;		// 0C
};

// 1C
class ExtraSayToTopicInfo : public BSExtraData
{
public:
	ExtraSayToTopicInfo();
	virtual ~ExtraSayToTopicInfo();

	TESTopicInfo	*info;		// 0C
	TESTopic		*topic;		// 10
	TESQuest		*quest;		// 14
	Actor			*speaker;	// 18
};

// 10
class ExtraCellAcousticSpace : public BSExtraData
{
public:
	ExtraCellAcousticSpace();
	virtual ~ExtraCellAcousticSpace();

	BGSAcousticSpace	*acousticSpace;		// 0C

	static ExtraCellAcousticSpace* __stdcall Create(BGSAcousticSpace *_acousticSpace = NULL);
};

// 10
class ExtraAshPileRef : public BSExtraData
{
public:
	ExtraAshPileRef();
	virtual ~ExtraAshPileRef();

	Actor		*sourceRef;		// 0C
};

// 28
class ExtraFollowerSwimBreadcrumbs : public BSExtraData
{
public:
	ExtraFollowerSwimBreadcrumbs();
	virtual ~ExtraFollowerSwimBreadcrumbs();

	UInt32			unk0C;
	float			unk10;
	float			unk14;
	float			unk18;
	UInt32			unk1C;
	tList<void>		list20;
};

// 10
class ExtraAudioMarker : public BSExtraData
{
public:
	ExtraAudioMarker();
	virtual ~ExtraAudioMarker();

	// 34
	struct Data
	{
		TESFullName		fullName;
		float			layer2TriggerPerc;
		float			layer3TriggerPerc;
		UInt32			unk14[4];
		UInt32			mediaLocCtrlID;
		UInt32			flags;
		UInt32			unk2C[2];
	};
	
	Data		*data;
};

struct MusicMarker
{
	TESObjectREFR			*markerRef;
	ExtraAudioMarker::Data	*markerData;

	MusicMarker(TESObjectREFR *_markerRef, ExtraAudioMarker::Data *data) : markerRef(_markerRef), markerData(data) {}

	bool operator < (const MusicMarker &rhs) const {return markerData->mediaLocCtrlID < rhs.markerData->mediaLocCtrlID;}
};

// 14
class ExtraSpecialRenderFlags : public BSExtraData
{
public:
	ExtraSpecialRenderFlags();
	virtual ~ExtraSpecialRenderFlags();

	UInt32		flags;		// 0C
	UInt32		unk10;		// 10

	static ExtraSpecialRenderFlags* __stdcall Create(UInt32 _flags = 0);
};

/*
// 48
struct VATSCameraData
{
	tList<VATSTargetInfo>						targetsList;	// 00
	UInt32							mode;			// 08
	UInt32							cameraShots;			// 0C
	BGSCameraShot					*camShot;		// 10
	float							flt14;			// 14
	float							flt18;			// 18
	UInt32							unk1C;			// 1C
	UInt32							unk20;			// 20
	TESIdleForm						*attackAnim;			// 24
	ImageSpaceModifierInstanceForm	*isModInstForm;	// 28
	ImageSpaceModifierInstanceRB	*isModInstRB;	// 2C
	UInt32							unk30;			// 30
	NiPointLight*					niPointLight;		// 34
	UInt8							byte38;			// 38
	UInt8							pad39[3];		// 39
	UInt32							numKills;			// 3C
	UInt32							unk40;			// 40
	UInt32							unk44;			// 44
};
STATIC_ASSERT(sizeof(VATSCameraData) == 0x48);
*/

// 10
struct SystemColorManager
{
	// 0C
	class SystemColor
	{
	public:
		SystemColor();
		~SystemColor();

		virtual void	Destructor(bool doFree);
		virtual UInt32	GetColor();
		virtual void	SetColor(UInt32 newColor);
		virtual bool	IsHard();
		virtual bool	IsSoft();

		String		traitName;

		void SetColorRGB(UInt32 r, UInt32 g, UInt32 b);
	};

	// 10
	class HardSystemColor : public SystemColor
	{
	public:
		HardSystemColor();
		~HardSystemColor();

		UInt32		color;		// 0C
	};

	// 10
	class SoftSystemColor : public SystemColor
	{
	public:
		SoftSystemColor();
		~SoftSystemColor();

		UInt32		*setting;	// 0C
	};

	DList<SystemColor>	sysColors;
	UInt32				unk0C;
};

// 8C
class ObstacleData : public NiRefObject
{
public:
	ObstacleData();
	~ObstacleData();

	UInt32						unk08;			// 08
	NiRefObject					*object0C;		// 0C
	UInt32						unk10[25];		// 10
	UInt8						byte74;			// 74
	UInt8						byte75[3];		// 75
	BSSimpleArray<NavMeshInfo>	navMeshInfos;	// 78
	NiRefObject					*object88;		// 88
};

// 108
class NavMesh : public TESForm
{
public:
	NavMesh();
	~NavMesh();

	virtual void		Unk_4E(void);

	TESChildCell								childCell;			// 018
	NiRefObject									refObject;			// 01C
	TESObjectCELL								*parentCell;		// 024
	BSSimpleArray<NavMeshVertex>				vertexArr;			// 028
	BSSimpleArray<NavMeshTriangle>				triangleArr;		// 038
	BSSimpleArray<EdgeExtraInfo>				edgeInfoArr;		// 048
	BSSimpleArray<NavMeshTriangleDoorPortal>	doorPortalArr;		// 058
	BSSimpleArray<NavMeshClosedDoorInfo>		closedDorrArr;		// 068
	BSSimpleArray<UInt16>						unk078Arr;			// 078
	NiTMapBase<UInt16, NavMeshPOVData*>			povDataMap;			// 088
	BSSimpleArray<UInt16>						unk098Arr;			// 098
	UInt32										unk0A8;				// 0A8
	float										unk0AC[8];			// 0AC
	BSSimpleArray<UInt16>						*arrPtr0CC;			// 0CC
	BSSimpleArray<ObstacleUndoData>				obstacleUndoArr;	// 0D0
	NiTMapBase<UInt16, ObstacleData*>			*obstacleDataMap;	// 0E0
	BSSimpleArray<UInt16>						unk0E4Arr;			// 0E4
	BSSimpleArray<NavMeshStaticAvoidNode>		avoidNodeArr;		// 0F4
	UInt32										*ptr104;			// 104
};
STATIC_ASSERT(sizeof(NavMesh) == 0x108);

class BSArchiveHeader
{
public:
	BSArchiveHeader();
	~BSArchiveHeader();
};

// 70
class BSArchive : public BSArchiveHeader
{
public:
	BSArchive();
	~BSArchive();

	UInt32		unk00;			// 00	160
	UInt32		unk04;			// 04	164
	UInt32		unk08;			// 08	168
	UInt32		unk0C;			// 0C	16C
	UInt32		unk10;			// 10	170
	UInt32		unk14;			// 14	174
	UInt32		unk18;			// 18	178
	UInt32		unk1C;			// 1C	17C
	UInt16		fileTypesMask;	// 20	180
	UInt16		word22;			// 22	182
	UInt32		unk24[19];		// 24	184
};
STATIC_ASSERT(sizeof(BSArchive) == 0x70);

// 1D0
class Archive : public BSFile
{
public:
	Archive();
	~Archive();

	NiRefObject			refObject;		// 158
	BSArchive			archive;		// 160
};
STATIC_ASSERT(sizeof(Archive) == 0x1D0);

// 160
class ArchiveFile : public BSFile
{
public:
	ArchiveFile();
	~ArchiveFile();

	UInt32			unk158;		// 158
	UInt32			unk15C;		// 15C
};
STATIC_ASSERT(sizeof(ArchiveFile) == 0x160);

// 178
class CompressedArchiveFile : public ArchiveFile
{
public:
	CompressedArchiveFile();
	~CompressedArchiveFile();

	void			*ptr160;		// 160
	void			*ptr164;		// 164
	UInt32			streamLength;	// 168
	UInt32			unk16C;			// 16C
	UInt32			streamOffset;	// 170
	UInt32			unk174;			// 174
};
STATIC_ASSERT(sizeof(CompressedArchiveFile) == 0x178);

// 58
class BGSDistantObjectBlockLoadTask : public QueuedFileEntry
{
public:
	BGSDistantObjectBlockLoadTask();
	~BGSDistantObjectBlockLoadTask();

	virtual void	Unk_0C(void);

	UInt8			byte30;			// 30
	UInt8			byte31;			// 31
	UInt8			byte32;			// 32
	UInt8			byte33;			// 33
	int				cellX;			// 34
	int				cellY;			// 38
	UInt32			lodLevel;		// 3C
	void			*lodNode14;		// 40
	TESWorldSpace	*worldSpc;		// 44
	NiRefObject		*object48;		// 48
	NiRefObject		*object4C;		// 4C
	UInt8			byte50;			// 50
	UInt8			byte51;			// 51
	UInt8			byte52;			// 52
	UInt8			byte53;			// 53
	UInt32			unk54;			// 54
};
STATIC_ASSERT(sizeof(BGSDistantObjectBlockLoadTask) == 0x58);

struct AnimGroupClassify
{
	UInt8	category;	// 00
	UInt8	subType;	// 01
	UInt8	flags;		// 02
	UInt8	byte03;		// 03
};
extern AnimGroupClassify s_animGroupClassify[];

// Credits to c6
// Taken from JG's decoding.h
class TESCaravanDeck : public TESForm {
public:
	TESCaravanDeck();
	~TESCaravanDeck();
	TESFullName name;
	tList<TESCaravanCard>* cards;
	UInt32 count;
};
STATIC_ASSERT(sizeof(TESCaravanDeck) == 0x2C);