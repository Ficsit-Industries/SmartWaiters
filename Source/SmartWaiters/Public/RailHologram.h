
#pragma once

#include "FactoryGame.h"
#include "Hologram/FGSplineHologram.h"
#include "Components/SplineComponent.h"
#include "RailHologram.generated.h"

/**
 * Hologram for the rails, contains --all the-- NO curve bending magic.
 */
UCLASS()
class SMARTWAITERS_API ARailHologram : public AFGSplineHologram
{
	GENERATED_BODY()
public:

	ARailHologram();

	// Begin AActor Interface
	//virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	// End AActor Interface

	// Begin AFGHologram Interface
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;

	// mehrere Phasen beim Plazieren. Höhe/Neigung der Stützen.
	virtual bool DoMultiStepPlacement(bool isInputFromARelease) override;

	virtual int32 GetBaseCostMultiplier() const override;
	// virtual AActor* GetUpgradedActor() const override;
	// virtual void OnInvalidHitResult() override;
	// virtual void SpawnChildren( AActor* hologramOwner, FVector spawnLocation, APawn* hologramInstigator ) override;
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const override;
	// virtual void AdjustForGround( FVector& out_adjustedLocation, FRotator& out_adjustedRotation ) override;
	// virtual void PreHologramPlacement() override;
	// virtual void PostHologramPlacement() override;
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	// virtual void Scroll( int32 delta ) override;
	//virtual void GetSupportedScrollModes( TArray<EHologramScrollMode>* out_modes ) const override;
	virtual float GetHologramHoverHeight() const override;
	// virtual void GetIgnoredClearanceActors( TArray< AActor* >& ignoredActors ) const override;
	// virtual void CheckBlueprintCommingling() override;
	// End AFGHologram Interface

protected:
	// Begin AFGBuildableHologram Interface
	//virtual void CheckValidFloor() override;
	//virtual void CheckValidPlacement() override;
	//virtual void ConfigureActor( class AFGBuildable* inBuildable ) const override;
	
	
	//virtual void ConfigureComponents( class AFGBuildable* inBuildable ) const override;*/
	
	// End AFGBuildableHologram Interface

	UFUNCTION(BlueprintPure)
	FORCEINLINE class USplineComponent* GetSplineComponent() const { return this->mSplineComponent; }

private:
	// Begin FGSplineHologram
	//virtual void UpdateSplineComponent() override;
	// End FGSplineHologram

	/** Create connection arrow component on the client. */
	//UFUNCTION()
	//void OnRep_ConnectionArrowComponentDirection();

	/**
	 * This routes the spline to the new location. Inserting bends and straights.
	 */
	void AutoRouteSpline(
		const FVector& startConnectionPos,
		const FVector& startConnectionNormal,
		const FVector& endConnectionPos,
		const FVector& endConnectionNormal );

	bool ValidateIncline();
	bool ValidateMinLength();

private:
	bool mUsingCutstomPoleRotation = false;

	/** The two connection components for this rail. */
	UPROPERTY()
	class URailConnectionComponent* mConnectionComponents[ 2 ];

	/** The connections we've made. */
	UPROPERTY( CustomSerialization )
	class URailConnectionComponent* mSnappedConnectionComponents[ 2 ];

	/** Class of Rail pole to place at the end. */
	UPROPERTY( EditDefaultsOnly, Category = "Rail Track" )
	TSubclassOf< class UFGRecipe > mDefaultRailPoleRecipe;

	/** Class of Rail pole to place at the end. */
	UPROPERTY( EditDefaultsOnly, Category = "Rail Track" )
	TSubclassOf< class UFGRecipe > mDefaultRailWallPoleRecipe;

	/** Class of Rail pole to place at the end. */
	UPROPERTY( EditDefaultsOnly, Category = "Rail Track" )
	TSubclassOf< class UFGRecipe > mDefaultRailCeilingPoleRecipe;

	/** What radius will the bends have. */
	UPROPERTY( EditDefaultsOnly, Category = "Rail Track" )
	float mBendRadius;

	/** Maximum length that can be built. [cm] */
	UPROPERTY( EditDefaultsOnly, Category = "Rail Track" )
	float mMaxSplineLength = 5600.1f;

	/** What is the maximum incline of the conveyor belt (degrees). */
	UPROPERTY( EditDefaultsOnly, Category = "Rail Track" )
	float mMaxIncline;

	UPROPERTY( CustomSerialization )
	FVector mConstructionPoleLocations[ 2 ];

	UPROPERTY(CustomSerialization)
	FRotator mConstructionPoleRotations[ 2 ];

	/** All the generated spline meshes. */
	UPROPERTY()
	TArray< class USplineMeshComponent* > mSplineMeshes;

	/** All the generated collision meshes. */
	UPROPERTY()
	TArray< class UShapeComponent* > mCollisionMeshes;

	/** Cached from the default buildable. */
	UPROPERTY()
	class UStaticMesh* mMesh;
	float mMeshLength;
};