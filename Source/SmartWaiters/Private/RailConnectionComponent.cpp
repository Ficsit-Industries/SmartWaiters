

#include "RailConnectionComponent.h"
#include "Kismet/KismetMathLibrary.h"

URailConnectionComponent::URailConnectionComponent()
{

}

void URailConnectionComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(URailConnectionComponent, mConnectedComponent);
}

void URailConnectionComponent::ClearConnection()
{
	if (this->mConnectedComponent != NULL)
	{
		this->mConnectedComponent->mConnectedComponent = NULL;
		this->mConnectedComponent = NULL;
	}
}

void URailConnectionComponent::SetConnection( class URailConnectionComponent* toComponent )
{
	this->mConnectedComponent = toComponent;
}

bool URailConnectionComponent::IsConnected() const
{
	return this->mConnectedComponent != NULL;
}
	
bool URailConnectionComponent::CanSnapTo( URailConnectionComponent* otherConnection ) const
{
	if (!this->IsConnected() && !otherConnection->IsConnected())
	{
		return true;
	}
	else
	{
		return false;
	}
}
	
bool URailConnectionComponent::CanConnectTo( URailConnectionComponent* otherConnection ) const
{
	if (!this->IsConnected() && !otherConnection->IsConnected())
	{
		return true;
	}
	else
	{
		return false;
	}
}


FVector URailConnectionComponent::GetConnectorLocation( bool withClearance ) const
{
	return this->GetComponentLocation();
}

static URailConnectionComponent* FindCompatibleOverlappingConnection( class URailConnectionComponent* component, const FVector& location, float radius, URailConnectionComponent* lowPriorityConnection)
{
	return NULL;
}

static URailConnectionComponent* FindOverlappingConnection( class URailConnectionComponent* component, const FVector& location, float radius, URailConnectionComponent* lowPriorityConnection )
{
	return NULL;
}