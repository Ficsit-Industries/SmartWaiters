
#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Buildables/FGBuildable.h"
#include "Components/SplineComponent.h"
#include "RailHologram.h"
#include "FGSignificanceInterface.h"
#include "FGSplineBuildableInterface.h"
#include "RailConnectionComponent.h"
#include "BuildableRail.generated.h"

/**
 * Rail for transferring items in gondolas between stations.
 */
UCLASS()
class SMARTWAITERS_API ABuildableRail : public AFGBuildable, public IFGSignificanceInterface, public IFGSplineBuildableInterface
{
	GENERATED_BODY()
public:
	ABuildableRail();

	// Begin Actor Interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	//virtual void BeginPlay() override;
	//virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	// End Actor Interface 

	// Begin IFGSignificance Interface
	UFUNCTION( BlueprintPure, Category = "SmartWaiters|Rails" )
	FORCEINLINE bool GetIsSignificant() { return mIsSignificant; }
	// End IFGSignificance Interface

	/** @return The connections, safe to assume its always valid. */
	FORCEINLINE URailConnectionComponent* GetConnection0() const { return mConnection0; }
	FORCEINLINE URailConnectionComponent* GetConnection1() const { return mConnection1; }

	/** Get the mesh used for this conveyor. */
	UFUNCTION( BlueprintPure, Category = "SmartWaiters|Rails" )
	FORCEINLINE UStaticMesh* GetSplineMesh() const { return mMesh; }

	/** Returns the spline component */
	UFUNCTION( BlueprintPure, Category = "SmartWaiters|Rails" )
	FORCEINLINE class USplineComponent* GetSplineComponent() { return mSplineComponent; }
	FORCEINLINE const class USplineComponent* GetSplineComponent() const { return mSplineComponent; }

	/* Get the length of the spline in world space */
	FORCEINLINE float GetLength() const { return mLength; }

	// Begin IFGSplineBuildableInterface
	TArray< FSplinePointData > GetSplinePointData() { return mSplineData; };
	float GetMeshLength() { return mMeshLength; }
	FVector GetCollisionExtent() override { return COLLISION_EXTENT; }
	float GetCollisionSpacing() override { return COLLISION_SPACING; }
	FVector GetCollisionOffset() override { return COLLISION_OFFSET; }
	UStaticMesh* GetUsedSplineMesh() override { return mMesh; }
	// End IFGSplineBuildableInterface

protected:
	friend class ARailHologram;

	/** Mesh to use for his rail. */
	UPROPERTY( EditDefaultsOnly, Category = "Rails" )
	class UStaticMesh* mMesh;

	/** Length of the mesh to use for this pipe. */
	UPROPERTY( EditDefaultsOnly, Category = "Rails" )
	float mMeshLength;

	/** Length of the pipe in centimeters. */
	float mLength;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Rails" )
	URailConnectionComponent* mConnection0;

	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Rails" )
	URailConnectionComponent* mConnection1;

	/** Compact representation of mSplineComponent, used for replication and save game */
	UPROPERTY( SaveGame, Replicated, Meta = ( NoAutoJson ) )
	TArray< FSplinePointData > mSplineData;

	/** The spline component for this splined factory. */
	UPROPERTY( VisibleAnywhere, Category = "Spline" )
	class USplineComponent* mSplineComponent;

	/** The spline meshes for this train track. */
	// Kompiliert hiermit nicht. TODO: Import prüfen
	//UPROPERTY( VisibleAnywhere, Category = "Spline" )
	//class UFGInstancedSplineMeshComponent* mInstancedSplineComponent;

private:
	bool mIsSignificant;

	// Collision Constants. These used to be magic numbers in the .cpp but were moved here so they could be accessed via the SplineBuildableInterface
	static inline const FVector COLLISION_EXTENT = FVector( 40.0f, 80.f , 80.f );
	static inline const float COLLISION_SPACING =  80.f;
	static inline const FVector COLLISION_OFFSET = FVector( 0.f, 0.f, 0.f );
};