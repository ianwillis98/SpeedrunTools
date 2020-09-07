#include "LocalControllerInputFix.h"

void LocalControllerInputFix::fix(ControllerInput &input)
{
    bool jump = input.Handbrake;
    bool holdingBoost = input.ActivateBoost;
    bool activateBoost = input.Jump;
    input.Jump = jump;
    input.HoldingBoost = holdingBoost;
    input.ActivateBoost = activateBoost;
}
