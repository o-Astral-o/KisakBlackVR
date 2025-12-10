#pragma once
#include "r_dpvs.h"
#include <DynEntity/DynEntity_client.h>

void __cdecl R_AddCellDynModelSurfacesInFrustumCmd(const DpvsPlane **data);
void __cdecl R_CullDynModelInCell(
                const unsigned int *dynEntCellBits,
                unsigned int dynEntClientWordCount,
                DynEntityPose *dynModelList,
                const DpvsPlane *planes,
                int planeCount,
                unsigned __int8 *dynEntVisData);
