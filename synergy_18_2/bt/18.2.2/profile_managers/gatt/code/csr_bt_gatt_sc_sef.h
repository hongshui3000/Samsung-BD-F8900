#ifndef CSR_BT_GATT_SC_SEF_H__
#define CSR_BT_GATT_SC_SEF_H__

#include "csr_synergy.h"
/****************************************************************************

               (c) Cambridge Silicon Radio Limited 2010

               All rights reserved and confidential information of CSR

REVISION:      $Revision: #1 $
****************************************************************************/

#include "csr_bt_gatt_main.h"

#ifdef __cplusplus
extern "C" {
#endif

CsrBool CsrBtGattCheckSecurity(GattMainInst *inst,
                               att_result_t result,
                               CsrBtGattQueueElement *qelm);

void CsrBtGattDispatchSc(GattMainInst *inst);

#ifdef __cplusplus
}
#endif

#endif /* CSR_BT_GATT_SC_SEF_H__ */

