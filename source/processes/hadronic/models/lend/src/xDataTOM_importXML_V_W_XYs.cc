#include "CommonHeader.h"

/*
# <<BEGIN-copyright>>
# <<END-copyright>>
*/
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

#include "xDataTOM_importXML_private.h"

#if defined __cplusplus
namespace GIDI {
using namespace GIDI;
#endif

static int xDataXML_V_W_XYs_W_XYsToTOM( statusMessageReporting *smr, xDataXML_element *XE, xDataTOM_W_XYs *W_XYs, xDataTOM_axes *axes );
/*
************************************************************
*/
int xDataXML_V_W_XYsToTOM( statusMessageReporting *smr, xDataXML_element *XE, xDataTOM_element *TE ) {

    int index, length;
    xDataTOM_xDataInfo *xDI = &(TE->xDataInfo);
    xDataXML_element *XMLChild;
    char const *wLabel;
    xDataTOM_V_W_XYs *V_W_XYs;

/* Need to release V_W_XYs if an error occurs later. */
    if( ( xDI->data = xDataXML_initializeData( smr, XE, TE, xDataTOM_V_W_XYs_ID, sizeof( xDataTOM_V_W_XYs ) ) ) == NULL ) return( 1 );
    V_W_XYs = (xDataTOM_V_W_XYs *) xDI->data;
    if( ( wLabel = xDataTOM_axes_getLabel( smr, &(xDI->axes), 0 ) ) == NULL ) goto err;
    length = xDataXML_numberOfElementsByTagName( smr, XE, wLabel );
    if( xDataTOM_V_W_XYs_initialize( smr, V_W_XYs, length, &(xDI->axes) ) != 0 ) return( 1 );

    for( XMLChild = xDataXML_getFirstElement( XE ), index = 0; XMLChild != NULL; XMLChild = xDataXML_getNextElement( XMLChild ) ) {
        if( strcmp( "axes", XMLChild->name ) == 0 ) {
            continue; }
        else if( strcmp( wLabel, XMLChild->name ) == 0 ) {
            if( xDataXML_V_W_XYs_W_XYsToTOM( smr, XMLChild, &(V_W_XYs->W_XYs[index]), &(xDI->axes) ) != 0 ) goto err;
            index++; }
        else {
            smr_setReportError3( smr, xDataXML_get_smrUserInterfaceFromElement( XE ), xDataTOM_smrLibraryID, -1,
                "invalid element '%s' in xData = 'V_W_XYs'", XMLChild->name );
            goto err;
        }
    }

    return( 0 );

err:
    smr_freeMemory( (void **) &(xDI->data) );
    return( 1 );
}
/*
************************************************************
*/
static int xDataXML_V_W_XYs_W_XYsToTOM( statusMessageReporting *smr, xDataXML_element *XE, xDataTOM_W_XYs *W_XYs, xDataTOM_axes *axes ) {

    int index;
    G4double value;

    if( xDataXML_convertAttributeTo_xDataTOM_Int( smr, XE, "index", &index, 1 ) != 0 ) return( 1 );
    if( xDataXML_convertAttributeToDouble( smr, XE, "value", &value, 1 ) != 0 ) return( 1 );
    return( xDataXML_W_XYsDataToTOM( smr, XE, W_XYs, index, value, axes, 1 ) );
}

#if defined __cplusplus
}
#endif
