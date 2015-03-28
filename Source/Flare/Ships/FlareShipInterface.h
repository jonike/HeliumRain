#pragma once

#include "../Game/FlareCompany.h"
#include "FlareShipInterface.generated.h"

class IFlareStationInterface;
struct FFlareShipComponentSave;


/** Possible subsystems targets */
UENUM()
namespace EFlareSubsystem
{
	enum Type
	{
		SYS_Temperature,
		SYS_Propulsion,
		SYS_RCS,
		SYS_LifeSupport,
		SYS_Power,
		SYS_Weapon,
	};
}


/** Ship save data */
USTRUCT()
struct FFlareShipSave
{
	GENERATED_USTRUCT_BODY()

	/** Ship location */
	UPROPERTY(EditAnywhere, Category = Save)
	FVector Location;

	/** Ship rotation */
	UPROPERTY(EditAnywhere, Category = Save)
	FRotator Rotation;
	
	/** Ship linear velocity */
	UPROPERTY(EditAnywhere, Category = Save)
	FVector LinearVelocity;

	/** Ship angular velocity */
	UPROPERTY(EditAnywhere, Category = Save)
	FVector AngularVelocity;

	/** Ship name. Readable for the player */
	UPROPERTY(EditAnywhere, Category = Save)
	FName Name;

	/** Ship catalog identifier */
	UPROPERTY(EditAnywhere, Category = Save)
	FName Identifier;

	/** Ship company identifier */
	UPROPERTY(EditAnywhere, Category = Save)
	FName CompanyIdentifier;

	/** Components list */
	UPROPERTY(EditAnywhere, Category = Save)
	TArray<FFlareShipComponentSave> Components;

	/** We are docked at this station */
	UPROPERTY(EditAnywhere, Category = Save)
	FName DockedTo;

	/** We are docked at this specific dock */
	UPROPERTY(EditAnywhere, Category = Save)
	int32 DockedAt;

	/** Accululated heat in KJ */
	UPROPERTY(EditAnywhere, Category = Save)
	float Heat;

	// Duration until the end of th power outage, in seconds
	UPROPERTY(EditAnywhere, Category = Save)
	float PowerOutageDelay;

};


/** Catalog binding between FFlareShipDescription and FFlareShipComponentDescription structure */
USTRUCT()
struct FFlareShipSlotDescription
{
	GENERATED_USTRUCT_BODY()
	
	/** Slot internal name */
	UPROPERTY(EditAnywhere, Category = Content) FName SlotIdentifier;
	
	/** Component description can be empty if configurable slot */
	UPROPERTY(EditAnywhere, Category = Content) FName ComponentIdentifier;
};


/** Catalog data structure for a ship */
USTRUCT()
struct FFlareShipDescription
{
	GENERATED_USTRUCT_BODY()

	/** Ship internal name */
	UPROPERTY(EditAnywhere, Category = Content) FName Identifier;

	/** Ship name */
	UPROPERTY(EditAnywhere, Category = Content) FText Name;

	/** Ship description */
	UPROPERTY(EditAnywhere, Category = Content) FText Description;

	/** Ship cost */
	UPROPERTY(EditAnywhere, Category = Content) int32 Cost;

	/** Size of the ship components */
	UPROPERTY(EditAnywhere, Category = Save)
	TEnumAsByte<EFlarePartSize::Type> Size;

	/** Ship status */
	UPROPERTY(EditAnywhere, Category = Content) bool Military;

	/** Number of RCS */
	UPROPERTY(EditAnywhere, Category = Save) int32 RCSCount;

	/** Number of orbital engine */
	UPROPERTY(EditAnywhere, Category = Save) int32 OrbitalEngineCount;

	/** Gun slots */
	UPROPERTY(EditAnywhere, Category = Content)
	TArray<FFlareShipSlotDescription> GunSlots;

	/** Turret slots */
	UPROPERTY(EditAnywhere, Category = Content)
	TArray<FFlareShipSlotDescription> TurretSlots;

	/** Internal component slots */
	UPROPERTY(EditAnywhere, Category = Content)
	TArray<FFlareShipSlotDescription> InternalComponentSlots;

	/** Max angular velocity in degree/s */
	UPROPERTY(EditAnywhere, Category = Content)	float AngularMaxVelocity;

	/** Max linear velocity in m/s */
	UPROPERTY(EditAnywhere, Category = Content)	float LinearMaxVelocity;

	/** Heat capacity un KJ/K */
	UPROPERTY(EditAnywhere, Category = Content) float HeatCapacity;

	/** Ship mesh name */
	UPROPERTY(EditAnywhere, Category = Content) UBlueprint* Template;

	/** Ship mesh preview image */
	UPROPERTY(EditAnywhere, Category = Content) FSlateBrush MeshPreviewBrush;

};


/** Interface wrapper */
UINTERFACE(MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))
class UFlareShipInterface  : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};


/** Actual interface */
class IFlareShipInterface
{
	GENERATED_IINTERFACE_BODY()

public:

	/*----------------------------------------------------
		Save
	----------------------------------------------------*/

	/** Load the ship from a save file */
	virtual void Load(const FFlareShipSave& Data) = 0;

	/** Save the ship to a save file */
	virtual FFlareShipSave* Save() = 0;

	/** Set the parent company */
	virtual void SetOwnerCompany(UFlareCompany* Company) = 0;

	/** Get the parent company */
	virtual UFlareCompany* GetCompany() = 0;


	/*----------------------------------------------------
		Damage control
	----------------------------------------------------*/

	/** Get the health factor associated to a ship's subsystem */
	virtual float GetSubsystemHealth(EFlareSubsystem::Type Type) = 0;

	/** Get the ship's temperature in Kelvin */
	virtual float GetTemperature() = 0;

	/** Get the ship's maximum acceptable temperature in Kelvin */
	virtual float GetMaxTemperature() = 0;

	/** Apply damage to this ship.
	 * Location is the center of sphere where damages are applied.
	 */
	virtual void ApplyDamage(float Energy, float Radius, FVector Location) = 0;

	/** Return true if any lifesupport system is alive */
	virtual bool IsAlive() = 0;

	/** Return true if the ship cockpit is powered */
	virtual bool IsPowered() = 0;

	/** Return true if the ship is currently on power outage */
	virtual bool HasPowerOutage() = 0;

	/** If on power outage, time until the end of the power outage. Else 0. */
	virtual float GetPowerOutageDuration() = 0;


	/*----------------------------------------------------
		Navigation API
	----------------------------------------------------*/

	/** Navigate there (scene coordinates) */
	virtual bool NavigateTo(FVector TargetLocation) = 0;

	/** Check if the ship is manually flown */
	virtual bool IsManualPilot() = 0;

	/** Check if the gliding mode is activated */
	virtual bool IsGliding() = 0;

	/** Check if the autopilot is enabled */
	virtual bool IsAutoPilot() = 0;

	/** Check if the ship is currently docked */
	virtual bool IsDocked() = 0;

	/** Navigate to and dock at this station */
	virtual bool DockAt(IFlareStationInterface* TargetStation) = 0;

	/** Undock from the current station */
	virtual bool Undock() = 0;

	/** Get the station where we are docked to */
	virtual IFlareStationInterface* GetDockStation() = 0;


	/*----------------------------------------------------
		Content
	----------------------------------------------------*/

	/** Get a Slate brush */
	static const FSlateBrush* GetIcon(FFlareShipDescription* Characteristic);

};
