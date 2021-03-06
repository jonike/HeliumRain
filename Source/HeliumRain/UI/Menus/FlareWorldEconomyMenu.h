#pragma once

#include "../../Flare.h"
#include "../Components/FlareButton.h"
#include "../Components/FlareDropList.h"
#include "../../Game/FlareWorldHelper.h"
#include "../../Data/FlareResourceCatalogEntry.h"
#include "../FlareUITypes.h"


class UFlareSimulatedSector;
class AFlareMenuManager;
struct FFlareResourceDescription;
class UFlareResourceCatalogEntry;

class SFlareWorldEconomyMenu : public SCompoundWidget
{
	/*----------------------------------------------------
		Slate arguments
	----------------------------------------------------*/

	SLATE_BEGIN_ARGS(SFlareWorldEconomyMenu){}

	SLATE_ARGUMENT(TWeakObjectPtr<class AFlareMenuManager>, MenuManager)

	SLATE_END_ARGS()


public:

	/*----------------------------------------------------
		Interaction
	----------------------------------------------------*/

	/** Create the widget */
	void Construct(const FArguments& InArgs);

	/** Setup the widget */
	void Setup();

	/** Enter this menu */
	void Enter(FFlareResourceDescription* Resource, UFlareSimulatedSector* Sector);

	/** Exit this menu */
	void Exit();

	void GenerateSectorList();

protected:

	/*----------------------------------------------------
		Callbacks
	----------------------------------------------------*/

	FSlateColor GetPriceColor(UFlareSimulatedSector* Sector) const;

	/** Get the resource price info */
	FText GetResourceDescription() const;

	/** Get the resource name */
	FText GetResourceName() const;

	/** Get the resource icon */
	const FSlateBrush* GetResourceIcon() const;

	/** Get the resource usage & production info */
	FText GetResourceInfo() const;

	/** Get the sector info */
	FText GetSectorText(UFlareSimulatedSector* Sector) const;

	/** Get the sector info color */
	FSlateColor GetSectorTextColor(UFlareSimulatedSector* Sector) const;

	/** Get the resource production info */
	FText GetResourceProductionInfo(UFlareSimulatedSector* Sector) const;

	/** Get the resource consumption info */
	FText GetResourceConsumptionInfo(UFlareSimulatedSector* Sector) const;

	/** Get the resource stock info */
	FText GetResourceStockInfo(UFlareSimulatedSector* Sector) const;

	/** Get the resource capacity info */
	FText GetResourceCapacityInfo(UFlareSimulatedSector* Sector) const;

	/** Get the resource price info */
	FText GetResourcePriceInfo(UFlareSimulatedSector* Sector) const;

	/** Get the resource price variation info */
	FText GetResourcePriceVariationInfo(UFlareSimulatedSector* Sector, TSharedPtr<int32> MeanDuration) const;

	TSharedRef<SWidget> OnGenerateResourceComboLine(UFlareResourceCatalogEntry* Item);

	void OnResourceComboLineSelectionChanged(UFlareResourceCatalogEntry* Item, ESelectInfo::Type SelectInfo);

	FText OnGetCurrentResourceComboLine() const;

	void OnOpenSector(UFlareSimulatedSector* Sector);

	void OnOpenSectorPrices(UFlareSimulatedSector* Sector);


protected:

	/*----------------------------------------------------
		Protected data
	----------------------------------------------------*/

	// Target data
	TWeakObjectPtr<class AFlareMenuManager>         MenuManager;
	FFlareResourceDescription*                      TargetResource;
	TMap<FFlareResourceDescription*, WorldHelper::FlareResourceStats> WorldStats;

	// Slate data
	TSharedPtr<SVerticalBox>                        SectorList;
	TSharedPtr<SFlareDropList<UFlareResourceCatalogEntry*>> ResourceSelector;

};
