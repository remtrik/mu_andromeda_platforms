#ifndef _PLATFORM_UTILS_H_
#define _PLATFORM_UTILS_H_

#include <Library/PcdLib.h>

#define TLMM_ADDR 0x0F100000

#define TLMM_ADDR_OFFSET_FOR_PIN(x) (0x1000 * x)

#define TLMM_PIN_CONTROL_REGISTER 0
#define TLMM_PIN_IO_REGISTER 4
#define TLMM_PIN_INTERRUPT_CONFIG_REGISTER 8
#define TLMM_PIN_INTERRUPT_STATUS_REGISTER 0xC
#define TLMM_PIN_INTERRUPT_TARGET_REGISTER TLMM_PIN_INTERRUPT_CONFIG_REGISTER

#define LID0_GPIO38_STATUS_ADDR                                                \
  (TLMM_ADDR + TLMM_ADDR_OFFSET_FOR_PIN(38) + TLMM_PIN_IO_REGISTER)

#define GICD_BASE (UINT32)PcdGet64(PcdGicDistributorBase)
#define GICR_BASE (UINT32)PcdGet64(PcdGicRedistributorsBase)
#define GICR_WAKER 0x0014
#define GICR_SIZE 0x20000
#define GICR_SGI 0x10000
#define GICR_ICENABLER0 0x0180
#define GICR_ICPENDR0 0x0280

VOID PlatformInitialize();
BOOLEAN IsLinuxBootRequested(VOID);

#endif /* _PLATFORM_UTILS_H_ */