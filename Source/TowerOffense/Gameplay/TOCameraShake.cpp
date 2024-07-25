#include "TOCameraShake.h"

UTOCameraShake::UTOCameraShake(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	OscillationDuration = 0.25f;
	OscillationBlendInTime = 0.05f;
	OscillationBlendOutTime = 0.05f;

	RotOscillation.Pitch.Amplitude = FMath::RandRange(1.0f, 5.0f);
	RotOscillation.Pitch.Frequency = FMath::RandRange(25.0f, 35.0f);

	RotOscillation.Yaw.Amplitude = FMath::RandRange(1.0f, 5.0f);
	RotOscillation.Yaw.Frequency = FMath::RandRange(25.0f, 35.0f);
}
