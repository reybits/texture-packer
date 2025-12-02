/**********************************************\
*
*  Andrey A. Ugolnik
*  http://www.ugolnik.info
*  andrey@ugolnik.info
*
\**********************************************/

#include "Config.h"
#include "Log.h"
#include "Utils.h"

void sConfig::dump() const
{
    // General
    cLog::Info("Method:             {}", slowMethod ? "Classic" : "KD-Tree");
    cLog::Info("Border:             {} px", border);
    cLog::Info("Padding:            {} px", padding);
    cLog::Info("Max atlas size:     {} px", maxTextureSize);

    // Features
    cLog::Info("Keep hotspot float: {}", isEnabled(keepFloat) ? "Enabled" : "Disabled");
    cLog::Info("Power of Two:       {}", isEnabled(pot) ? "Enabled" : "Disabled");
    // cLog::Info("Multi-atlas:        {}", isEnabled(multi) ? "Enabled" : "Disabled");
    cLog::Info("Trim sprites:       {}", isEnabled(trim) ? "Enabled" : "Disabled");
    cLog::Info("Drop extension:     {}", isEnabled(dropExt) ? "Enabled" : "Disabled");
    cLog::Info("Allow duplicates:   {}", isEnabled(alowDupes) ? "Enabled" : "Disabled");
    cLog::Info("Overlay:            {}", isEnabled(overlay) ? "Enabled" : "Disabled");
}
