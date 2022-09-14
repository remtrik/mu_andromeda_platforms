#ifndef _PLATFORM_UTILS_H_
#define _PLATFORM_UTILS_H_

#include <Library/PcdLib.h>

#define TLMM_WEST 0x03100000
#define TLMM_EAST 0x03500000
#define TLMM_NORTH 0x03900000
#define TLMM_SOUTH 0x03D00000

#define TLMM_ADDR_OFFSET_FOR_PIN(x) (0x1000 * x)

#define TLMM_PIN_CONTROL_REGISTER 0
#define TLMM_PIN_IO_REGISTER 4
#define TLMM_PIN_INTERRUPT_CONFIG_REGISTER 8
#define TLMM_PIN_INTERRUPT_STATUS_REGISTER 0xC
#define TLMM_PIN_INTERRUPT_TARGET_REGISTER TLMM_PIN_INTERRUPT_CONFIG_REGISTER

#define LID0_GPIO121_STATUS_ADDR                                               \
  (TLMM_SOUTH + TLMM_ADDR_OFFSET_FOR_PIN(121) + TLMM_PIN_IO_REGISTER)

#define MDSS_DSI0 0xAE94000
#define MDSS_DSI1 0xAE96000
#define DSI_CTRL 4
#define DSI_CTRL_ENABLE 1
#define DSI_CTRL_VIDEO_MODE_ENABLE 2
#define DSI_CTRL_COMMAND_MODE_ENABLE 4

#define SMMU_BASE 0x15000000

#define SMMU_CTX_BANK_SIZE 0x1000

#define SMMU_CTX_BANK_0_OFFSET 0x80000
#define SMMU_CTX_BANK_SCTLR_OFFSET 0x0
#define SMMU_CTX_BANK_TTBR0_0_OFFSET 0x20
#define SMMU_CTX_BANK_TTBR0_1_OFFSET 0x24
#define SMMU_CTX_BANK_TTBR1_0_OFFSET 0x28
#define SMMU_CTX_BANK_TTBR1_1_OFFSET 0x2C
#define SMMU_CTX_BANK_MAIR0_OFFSET 0x38
#define SMMU_CTX_BANK_MAIR1_OFFSET 0x3C
#define SMMU_CTX_BANK_TTBCR_OFFSET 0x30

#define SMMU_NON_CCA_SCTLR 0xE0
#define SMMU_CCA_SCTLR 0x9F00E0

#define UFS_CTX_BANK 1

#define APSS_WDT_BASE 0x17C10000
#define APSS_WDT_ENABLE_OFFSET 0x8

VOID PlatformInitialize();
BOOLEAN IsLinuxBootRequested(VOID);

#endif /* _PLATFORM_UTILS_H_ */