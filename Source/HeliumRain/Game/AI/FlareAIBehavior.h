#pragma once

#include "Object.h"
#include "../FlareGameTypes.h"
#include "FlareAIBehavior.generated.h"


class UFlareCompany;
class UFlareScenarioTools;
struct FFlareCelestialBody;

UCLASS()
class HELIUMRAIN_API UFlareAIBehavior : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/*----------------------------------------------------
		Public API
	----------------------------------------------------*/

	/** Load the company behavior */
	virtual void Load(UFlareCompany* ParentCompany);

protected:

	/*----------------------------------------------------
		Internal subsystems
	----------------------------------------------------*/


	void GenerateAffilities();

	/*----------------------------------------------------
		Helpers
	----------------------------------------------------*/


	void SetResourceAffilities(float Value);

	void SetResourceAffility(FFlareResourceDescription* Resource, float Value);

	void SetSectorAffilities(float Value);

	void SetSectorAffility(UFlareSimulatedSector* Sector, float Value);

	void SetSectorAffilitiesByMoon(FFlareCelestialBody *CelestialBody, float Value);

protected:

	/*----------------------------------------------------
		Data
	----------------------------------------------------*/

	// Gameplay data
	UFlareCompany*			               Company;
	AFlareGame*                            Game;
	UFlareScenarioTools*                    ST;


	TMap<FFlareResourceDescription*, float> ResourceAffilities;
	TMap<UFlareSimulatedSector*, float> SectorAffilities;
public:

	/*----------------------------------------------------
		Public Data
	----------------------------------------------------*/

	float StationCapture;
	float TradingBuy;
	float TradingSell;
	float TradingBoth;
	float ShipyardAffility;
	float ConsumerAffility;
	float MaintenanceAffility;
	float BudgetTechnology;
	float BudgetMilitary;
	float BudgetStation;
	float BudgetTrade;
	float ArmySize;
	float Agressivity;
	float Bold;
	float Peaceful;


	/*----------------------------------------------------
		Getters
	----------------------------------------------------*/

	AFlareGame* GetGame() const
	{
		return Game;
	}

	float GetSectorAffility(UFlareSimulatedSector* Sector);
	float GetResourceAffility(FFlareResourceDescription* Resource);

};
