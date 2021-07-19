#ifndef DRAILFRAGMENT_H
#define DRAILFRAGMENT_H


/*
#include <dnetworknode.h>


enum RailFragmentTypes
{
    straightVert = 0,
    straightHoriz,
    diagULDR,
    diagDRUL = RailFragmentTypes::diagULDR,
    diagDLUR,
    diagURDL = RailFragmentTypes::diagDLUR,

    tight_U_UL,
    tight_DR_D = RailFragmentTypes::tight_U_UL,

    tight_U_UR,
    tight_DL_D = RailFragmentTypes::tight_U_UR,

    tight_D_DL,
    tight_UR_U = RailFragmentTypes::tight_D_DL,

    tight_D_DR,
    tight_UL_U = RailFragmentTypes::tight_D_DR,

    tight_UL_L,
    tight_R_DR = RailFragmentTypes::tight_UL_L,

    tight_DL_L,
    tight_R_UR = RailFragmentTypes::tight_DL_L,

    tight_UR_R,
    tight_L_DL = RailFragmentTypes::tight_UR_R,

    tight_DR_R,
    tight_L_UL = RailFragmentTypes::tight_DR_R,




    loose_U_UL,
    loose_DR_D = RailFragmentTypes::loose_U_UL,

    loose_U_UR,
    loose_DL_D = RailFragmentTypes::loose_U_UR,

    loose_D_DL,
    loose_UR_U = RailFragmentTypes::loose_D_DL,

    loose_D_DR,
    loose_UL_U = RailFragmentTypes::loose_D_DR,


    junction_U_UL,
    junction_U_UR,

    junction_UR_U,
    junction_UR_R,

    junction_R_UR,
    junction_R_DR,

    junction_DR_R,
    junction_DR_D,

    junction_D_DR,
    junction_D_DL,

    junction_DL_D,
    junction_DL_L,

    junction_L_DL,
    junction_L_UL,

    junction_UL_L,
    junction_UL_U

    // PLACEHOLDERS for crossings, X-junctions et al.

};

enum texture_rotation
{
    d0 = 0,
    d90,
    d180,
    d270,

    m0,
    m90,
    m180,
    m270
};



struct DRailFragment
{
   //    DRailFragment(RailFragmentTypes type=straightVert);
   int i,j;//top left corner on map
   int ax,ay;//top left corner on atlas
   int bx,by;//bottom right corner on atlas
   texture_rotation rotation = d0;
};
*/

#endif // DRAILFRAGMENT_H
