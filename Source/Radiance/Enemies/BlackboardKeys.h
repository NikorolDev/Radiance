#pragma once

#include "Runtime/Core/Public/UObject/NameTypes.h"
#include "Runtime/Core/Public/Containers/UnrealString.h"

//-----------------------------------------------------------------------------------------------------------------------------
// Namespcae Name		: BlackboardKeys
// Author				: Saurya Saurav
// Editors				: 
// Purpose				: Stores all the Blackboard keys for Enemy AI Behaviour Tree
//-----------------------------------------------------------------------------------------------------------------------------
namespace BlackboardKeys
{
    TCHAR const* const chTargetLocation             = TEXT ( "TargetLocation" );
    TCHAR const* const chCanSeePlayer               = TEXT ( "CanSeePlayer" );
    TCHAR const* const chPlayerIsInAttackRange      = TEXT ( "PlayerIsInAttackRange" );
    TCHAR const* const chPlayerAnimationAttack      = TEXT ( "PlayerAnimationAttack" );
    TCHAR const* const chTargetActor                = TEXT ( "TargetActor" );
    TCHAR const* const chAttackTarget               = TEXT ( "AttackTarget" );
    TCHAR const* const chExplode                    = TEXT ( "Explode" );
    TCHAR const* const chTargetAttackLocation       = TEXT ( "TargetAttackLocation" );
    TCHAR const* const chIsAtAttackLocation         = TEXT ( "IsAtAttackLocation" );
    TCHAR const* const chIsAttacking                = TEXT ( "IsAttacking" );
    TCHAR const* const chCanChangeLocation          = TEXT ( "CanChangeLocation" );
    TCHAR const* const chEnemyLocationAtStart       = TEXT ( "EnemyLocationAtStart" );
}