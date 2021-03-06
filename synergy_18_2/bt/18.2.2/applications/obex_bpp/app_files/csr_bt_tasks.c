/****************************************************************************

               (c) Cambridge Silicon Radio Limited 2009

               All rights reserved and confidential information of CSR

REVISION:      $Revision: #1 $
****************************************************************************/

#include "csr_synergy.h"

#include <string.h>
#include "csr_bt_declare_tasks.h"

/* CSR scheduler task initialisation */
void CsrSchedTaskInit(void *data)
{
    /* Initialise standard tasks (see csr_bt_declare_tasks.c) */
    CsrBtAppTaskInitFw(data);
    CsrBtAppTaskInitBt(data);
    CsrBtAppTaskInitWifi(data);

    /* Synergy BT high-level protocols */
    CsrSchedRegisterTask(&CSR_BT_BPPS_IFACEQUEUE, CSR_BT_BPPS_INIT, CSR_BT_BPPS_DEINIT, CSR_BT_BPPS_HANDLER, "CSR_BT_BPPS", data, ID_STACK);
    CsrSchedRegisterTask(&CSR_BT_BPPC_IFACEQUEUE, CSR_BT_BPPC_INIT, CSR_BT_BPPC_DEINIT, CSR_BT_BPPC_HANDLER, "CSR_BT_BPPC", data, ID_STACK);

#if !defined(EXCLUDE_TEST_MODULE) && (CSR_BT_RUN_TASK_TEST_TASK == 1)
    /* Application task and helpers */
    CsrSchedRegisterTask(&TESTQUEUE, CSR_BT_TEST_INIT, CSR_BT_TEST_DEINIT, CSR_BT_TEST_HANDLER, "CSR_BT_APP", data, ID_APP);
#endif
}
