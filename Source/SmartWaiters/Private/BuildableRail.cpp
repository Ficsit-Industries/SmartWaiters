

#include "BuildableRail.h"

ABuildableRail::ABuildableRail()
{
	this->mConnection0 = CreateDefaultSubobject<URailConnectionComponent>(TEXT("mConnection0"));
	this->mConnection1 = CreateDefaultSubobject<URailConnectionComponent>(TEXT("mConnection1"));
	this->mSplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("mSplineComponent"));
}

void ABuildableRail::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABuildableRail, mSplineData);
}