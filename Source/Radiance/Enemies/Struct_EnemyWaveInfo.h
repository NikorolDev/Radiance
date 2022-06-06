#pragma once

#include "Struct_EnemyWaveInfo.generated.h"

//-----------------------------------------------------------------------------------------------------------------------------
// Struct Name			: FStructEnemyWaveInfo
// Author				: Saurya Saurav
// Purpose				: Stores the Wave information 
//-----------------------------------------------------------------------------------------------------------------------------
USTRUCT ( BlueprintType )
struct FStructEnemyWaveInfo
{
    GENERATED_BODY ( )

    UPROPERTY ( EditInstanceOnly , BlueprintReadOnly , Category = "Wave Properties" ,
                meta = ( DisplayName = "Wave ID" , ToolTip = "Wave ID" ) )
        int iWaveID;

    UPROPERTY ( EditInstanceOnly , BlueprintReadOnly , Category = "Wave Properties" ,
                meta = ( DisplayName = "Total Number of Enemies" , ToolTip = "Total Number of Enemies in this combat" ) )
        int iTotalNumberOfEnemies;

    UPROPERTY ( EditInstanceOnly , BlueprintReadOnly , Category = "Enemy Spawner Properties" ,
                meta = ( DisplayName = "Number of Corrupter" , ToolTip = "Total Number of Corrupter Enemy in this combat" ) )
        int iTotalNumberOfCorrupter;

    UPROPERTY ( EditInstanceOnly , BlueprintReadOnly , Category = "Enemy Spawner Properties" ,
                meta = ( DisplayName = "Number of Fallen" , ToolTip = "Total Number of Corrupter Enemy in this Fallen" ) )
        int iTotalNumberOfFallen;

    UPROPERTY ( EditInstanceOnly , BlueprintReadOnly , Category = "Enemy Spawner Properties" ,
                meta = ( DisplayName = "Max Number of Enemies Visible" , ToolTip = "Max number of enemies that can be present in the Combat Zone at a time" ) )
        int iMaxNumberOfEnemiesAtATime;

    UPROPERTY ( EditInstanceOnly , BlueprintReadOnly , Category = "Enemy Spawner Properties" ,
                meta = ( DisplayName = "List of Spawn Locations" , ToolTip = "List of Spawn Locations in the Combat Zone" ) )
        TArray<AActor*> SpawnLocations;

};