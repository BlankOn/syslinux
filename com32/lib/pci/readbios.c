#include <com32.h>
#include <string.h>
#include "pci/pci.h"

uint32_t __pci_read_bios(uint32_t call, pciaddr_t a)
{
    com32sys_t rs;
    memset(&rs, 0, sizeof rs);
    rs.eax.w[0] = call;
    rs.ebx.w[0] = a >> 8;	/* bus:device:function */
    rs.edi.b[0] = a;		/* address:reg */
    __intcall(0x1a, &rs, &rs);

    return (rs.eflags.l & EFLAGS_CF) ? ~(uint32_t) 0 : rs.ecx.l;
}
