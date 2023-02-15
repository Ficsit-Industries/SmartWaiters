
#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGConnectionComponent.h"
#include "FGInventoryComponent.h"
#include "RailConnectionComponent.generated.h"

/**
 * Connection base used to link smart waiters rails together
 */
UCLASS( ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class SMARTWAITERS_API URailConnectionComponent : public UFGConnectionComponent
{
	GENERATED_BODY()
public:
	URailConnectionComponent();

	// Begin ActorComponent interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	//virtual void OnComponentDestroyed( bool isDestroyingHierarchy ) override;
	//virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// End ActorComponent interface

		/** Set the conveyor clearance for this connection. */
	FORCEINLINE void SetConnectorClearance( float clearance ){ mConnectorClearance = clearance; }

	/** Return the clearance needed when routing a pipe from this connection. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Rails|Connection" )
	FORCEINLINE float GetConnectorClearance() const { return mConnectorClearance; }

	/**
	 * Set which connection this is connected to.
	 * @note Sets both ends of the connection.
	 * If there already a connection made we assert.
	 */
	void SetConnection( class URailConnectionComponent* toComponent );

	/**
	 * Get which connection this is connected to.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Rails|Connection" )
	FORCEINLINE class URailConnectionComponent* GetConnection() const 
	{
		if( IsValid( mConnectedComponent ) ) 			
		{
			return mConnectedComponent;
		}
		else 	
		{
			return nullptr;
		}
	}

	/**
	 * Clear the connection on this component
	 * @note Clears both ends of the connection.
	 * If nothing is connected this does nothing.
	 */
	void ClearConnection();

	/**
	 * Is this connection connected to anything.
	 * @return - true if connected; otherwise false. Always false if attached to hologram, snap only or bad index configuration.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Rails|Connection" )
	bool IsConnected() const;
	
	/** Check if the given connection can snap to this. */
	bool CanSnapTo( URailConnectionComponent* otherConnection ) const;
	
	/** Check if the given connection can connect to this. */
	bool CanConnectTo( URailConnectionComponent* otherConnection ) const;


	/** Return the connectors world location with or without considering the clearance. */
	FVector GetConnectorLocation( bool withClearance = false ) const;

	/** Return the connectors world normal. */
	FVector GetConnectorNormal() const { return GetComponentRotation().Vector(); }

	/**
	 * Find overlapping connections that are compatible with this one.
	 */
	static URailConnectionComponent* FindCompatibleOverlappingConnection( class URailConnectionComponent* component, const FVector& location, float radius, URailConnectionComponent* lowPriorityConnection = nullptr);

	/**
	 * Returns an overlapped pipe connection. Does not take into account if it is a valid connection only if the connection is in the radius of the one passed in
	 */
	static URailConnectionComponent* FindOverlappingConnection( class URailConnectionComponent* component, const FVector& location, float radius, URailConnectionComponent* lowPriorityConnection = nullptr );

protected:
	UPROPERTY( SaveGame, VisibleAnywhere, Replicated, Category = "Connection" )
	int32 mNetworkID;

	/** How long the connector is extending, indicates where the connected pipe may start turning. */
	UPROPERTY( EditDefaultsOnly, Category = "Connection" )
	float mConnectorClearance;

	/** Connection to another component. If this is set we're connected. */
	UPROPERTY( SaveGame, Replicated )
	class URailConnectionComponent* mConnectedComponent;
};