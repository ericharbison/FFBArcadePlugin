/*This file is part of FFB Arcade Plugin.
FFB Arcade Plugin is free software : you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
FFB Arcade Plugin is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with FFB Arcade Plugin.If not, see < https://www.gnu.org/licenses/>.
*/

#include <string>
#include "SegaRally3.h"

extern int EnableDamper;
extern int DamperStrength;

void SegaRally3::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {
	helpers->log("in SR3 Ffbloop");
	const int ff = GetTeknoParrotFFB();
	std::string ffs = std::to_string(ff);
	helpers->log((char*)ffs.c_str());

	if (EnableDamper)
		triggers->Damper(DamperStrength / 100.0);

	if (ff > 15)
	{
		helpers->log("moving wheel right");
		double percentForce = (31 - ff) / 15.0;
		double percentLength = 100;
		triggers->Rumble(percentForce, 0, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);

	}
	else if (ff > 0)
	{
		helpers->log("moving wheel left");
		double percentForce = (16 - ff) / 15.0;
		double percentLength = 100;
		triggers->Rumble(0, percentForce, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
	}
}