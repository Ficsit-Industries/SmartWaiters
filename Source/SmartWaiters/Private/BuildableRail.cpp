

#include "BuildableRail.h"

ABuildableRail::ABuildableRail()
{

}

void ABuildableRail::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABuildableRail, mSplineData);
}