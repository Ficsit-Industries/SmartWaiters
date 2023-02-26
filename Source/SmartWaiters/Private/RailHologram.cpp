
#include "RailHologram.h"
#include "RailConnectionComponent.h"
#include "BuildableRail.h"
#include "SmartWaiters.h"

ARailHologram::ARailHologram()
{

}

void ARailHologram::BeginPlay()
{
	Super::BeginPlay();

	ABuildableRail* rail = mBuildClass->GetDefaultObject< ABuildableRail >();
	//ABuildableRail* rail = this->GetDefaultBuildable<ABuildableRail>();
	this->mMesh = rail->mMesh;
	this->mMeshLength = rail->mMeshLength;
}

static URailConnectionComponent* GetValidConnection( const FHitResult& hitResult)
{
	const AActor* actor = hitResult.GetActor();
	if (actor == NULL) return NULL;
	
	TArray<URailConnectionComponent*> connections;
	actor->GetComponents<URailConnectionComponent>(connections);
	if (connections.Num() == 0) return NULL;
	
	for (URailConnectionComponent* con : connections)
	{
		if (!con->IsConnected())
		{
			return con;
		}
	}
	return NULL;
}

// 3 (wenn 2 fehl schlägt)
void ARailHologram::SetHologramLocationAndRotation( const FHitResult& hitResult )
{
	UE_LOG(LogSmartWaiters, Warning, TEXT("SetHologramLocationAndRotation"));
	
	if (this->mBuildStep == ESplineHologramBuildStep::SHBS_FindStart)
	{
		this->SetActorLocation(hitResult.Location);
		this->AutoRouteSpline(
			hitResult.Location,
			FVector::ForwardVector,
			hitResult.Location + FVector::ForwardVector * 100,
			FVector::ForwardVector);
	}
	else if (this->mBuildStep == ESplineHologramBuildStep::SHBS_PlacePoleOrSnapEnding)
	{
		this->AutoRouteSpline(
			this->mSnappedConnectionComponents[0]->GetConnectorLocation(),
			this->mSnappedConnectionComponents[0]->GetConnectorNormal(),
			hitResult.Location,
			this->mSnappedConnectionComponents[0]->GetConnectorNormal());
	}
	this->UpdateSplineComponent();

	/*const AActor* actor = hitResult.GetActor();
	if (actor == NULL) return false;

	TArray<URailConnectionComponent>* connections;
	actor->GetComponents(URailConnectionComponent::StaticClass(), connections);
	if (connections.Num() == 0) return false;
	
	for (URailConnectionComponent* con : connections)
	{

		for (URailConnectionComponent* con : connections)
		{
			if (!con->IsConnected())
			{
				return true;
			}
		}
	}*/
}

/*void ConfigureComponents( class AFGBuildable* inBuildable ) const
{
	
}*/

bool ARailHologram::DoMultiStepPlacement(bool isInputFromARelease)
{
	UE_LOG(LogSmartWaiters, Warning, TEXT("DoMultiStepPlacement"));

	if (this->mSnappedConnectionComponents[0] == NULL) return false;
	this->mActivePointIdx++;
	this->mBuildStep = ESplineHologramBuildStep::SHBS_PlacePoleOrSnapEnding;
	return mActivePointIdx == 2;
}

int32 ARailHologram::GetBaseCostMultiplier() const
{
	return 1;
}

// 1
bool ARailHologram::IsValidHitResult( const FHitResult& hitResult ) const
{
	//UE_LOG(LogSmartWaiters, Warning, TEXT("IsValidHitResult"));

	return (hitResult.GetActor() != NULL);
}

// 2
bool ARailHologram::TrySnapToActor( const FHitResult& hitResult )
{
	UE_LOG(LogSmartWaiters, Warning, TEXT("TrySnapToActor"));

	URailConnectionComponent* connection = GetValidConnection(hitResult);
	if (connection == NULL) return false;

	this->mSnappedConnectionComponents[this->mActivePointIdx] = connection;
	if (this->mBuildStep == ESplineHologramBuildStep::SHBS_FindStart)
	{
		this->SetActorLocation(connection->GetConnectorLocation());
		this->AutoRouteSpline(
			connection->GetConnectorLocation(),
			connection->GetConnectorNormal(),
			connection->GetConnectorLocation() + connection->GetConnectorNormal() * 200,
			connection->GetConnectorNormal());
	}
	else if (this->mBuildStep == ESplineHologramBuildStep::SHBS_PlacePoleOrSnapEnding)
	{
		this->AutoRouteSpline(
			this->mSnappedConnectionComponents[0]->GetConnectorLocation(),
			this->mSnappedConnectionComponents[0]->GetConnectorNormal(),
			connection->GetConnectorLocation() + connection->GetConnectorNormal() * 200,
			connection->GetConnectorNormal());
	}
	this->UpdateSplineComponent();
	return true;
}

/*const TArray<EHologramScrollMode>* SCROLL_MODES = {EHologramScrollMode::HSM_SPLINE_PATH_MODE};

void ARailHologram::GetSupportedScrollModes( TArray<EHologramScrollMode>* out_modes ) const
{
	return SCROLL_MODES;
}*/

float ARailHologram::GetHologramHoverHeight() const
{
	return 3.5f;
}

/*void ARailHologram::ConfigureActor( class AFGBuildable* inBuildable ) const
{

}*/

bool ARailHologram::ValidateIncline() { return true; }
bool ARailHologram::ValidateMinLength() { return true; }

/*void ARailHologram::UpdateSplineComponent()
{
	this->AutoRouteSpline();
}*/

void ARailHologram::AutoRouteSpline( const FVector& startConnectionPos, const FVector& startConnectionNormal, const FVector& endConnectionPos, const FVector& endConnectionNormal )
{
	UE_LOG(LogSmartWaiters, Warning, TEXT("AutoRouteSpline"));

	//FOccluderVertexArray points = {startConnectionPos, endConnectionPos};
	//this->mSplineComponent->SetSplinePoints(points, ESplineCoordinateSpace::World);
	
	TArray<FSplinePointData> data = this->GetSplineData();
	data.Reset();

	data.Add(FSplinePointData(startConnectionPos - this->GetActorLocation(), startConnectionNormal));
	data.Add(FSplinePointData(endConnectionPos - this->GetActorLocation(), endConnectionNormal));
	this->mSplineData = data;
}
