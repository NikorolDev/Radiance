// Fill out your copyright notice in the Description page of Project Settings.


#include "FadeViewportClient.h"
#include "Engine/Canvas.h"

void UFadeViewportClient::PostRender(UCanvas* Canvas)
{
    UGameViewportClient::PostRender(Canvas);

    // Fade if requested, you could use the same DrawScreenFade method from any canvas such as the HUD
    if (bFading)
    {
        DrawScreenFade(Canvas);
    }
}

void UFadeViewportClient::ClearFade()
{
    bFading = false;
}

void UFadeViewportClient::Fade(const float Duration, const bool bToBlack)
{
    const UWorld* world = GetWorld();
    if (world)
    {
        bFading = true;
        this->bIfBlack = bToBlack;
        FadeDuration = Duration;
        FadeStartTime = world->GetTimeSeconds();
    }
}

void UFadeViewportClient::DrawScreenFade ( UCanvas* Canvas )
{
    if ( bFading )
    {
        const UWorld* world = GetWorld ( );
        if ( world )
        {
            const float Time = world->GetTimeSeconds ( );
            const float Alpha = FMath::Clamp ( ( Time - FadeStartTime ) / FadeDuration, 0.f, 1.f );

            // Make sure that we stay black in a fade to black
            if ( Alpha == 1.f && !bIfBlack )
            {
                bFading = false;
            }
            else
            {
                FColor OldColor = Canvas->DrawColor;
                FLinearColor FadeColor = FLinearColor::Black;
                FadeColor.A = bIfBlack ? Alpha : 1 - Alpha;
                Canvas->DrawColor = FadeColor.ToFColor ( true ); 
                Canvas->DrawTile ( Canvas->DefaultTexture, 0, 0, Canvas->ClipX, Canvas->ClipY, 0, 0, Canvas->DefaultTexture->GetSizeX ( ), Canvas->DefaultTexture->GetSizeY ( ) );
                Canvas->DrawColor = OldColor;
            }
        }
    }
}
