// PrePi.c: Entry point for SEC(Security).

#include <PiPei.h>
#include <Pi/PiBootMode.h>

#include <Library/PrePiLib.h>
#include <Library/PrintLib.h>
#include <Library/PrePiHobListPointerLib.h>
#include <Library/CacheMaintenanceLib.h>
#include <Library/MemoryMapHelperLib.h>

#include <Ppi/GuidedSectionExtraction.h>

#include "PrePi.h"
#include "InitializationUtils.h"

UINT64  mSystemMemoryEnd = FixedPcdGet64 (PcdSystemMemoryBase) +
                           FixedPcdGet64 (PcdSystemMemorySize) - 1;

VOID EFIAPI ProcessLibraryConstructorList(VOID);

VOID PrePiMain()
{

  EFI_HOB_HANDOFF_INFO_TABLE *HobList;
  EFI_STATUS                  Status;

  UINTN MemoryBase     = 0;
  UINTN MemorySize     = 0;
  UINTN UefiMemoryBase = 0;
  UINTN UefiMemorySize = 0;
  UINTN StackBase      = 0;
  UINTN StackSize      = 0;

  ARM_MEMORY_REGION_DESCRIPTOR_EX DxeHeap;
  ARM_MEMORY_REGION_DESCRIPTOR_EX UefiStack;
  ARM_MEMORY_REGION_DESCRIPTOR_EX UefiFd;

  // Architecture-specific initialization
  // Enable Floating Point
  ArmEnableVFP();

  if (ArmReadCurrentEL() == AARCH64_EL2) {
    // Trap General Exceptions. All exceptions that would be routed to EL1 are routed to EL2
    ArmWriteHcr(ARM_HCR_TGE);

    /* Enable Timer access for non-secure EL1 and EL0
       The cnthctl_el2 register bits are architecturally
       UNKNOWN on reset.
       Disable event stream as it is not in use at this stage
    */
    ArmWriteCntHctl(CNTHCTL_EL2_EL1PCTEN | CNTHCTL_EL2_EL1PCEN);
  }

  /* Enable program flow prediction, if supported */
  ArmEnableBranchPrediction();

  Status = LocateMemoryMapAreaByName("DXE Heap", &DxeHeap);
  ASSERT_EFI_ERROR (Status);

  Status = LocateMemoryMapAreaByName("UEFI Stack", &UefiStack);
  ASSERT_EFI_ERROR (Status);

  Status = LocateMemoryMapAreaByName("UEFI FD", &UefiFd);
  ASSERT_EFI_ERROR (Status);

  // Declare UEFI region
  MemoryBase     = FixedPcdGet32(PcdSystemMemoryBase);
  MemorySize     = FixedPcdGet32(PcdSystemMemorySize);
  UefiMemoryBase = DxeHeap.Address;
  UefiMemorySize = DxeHeap.Length;
  StackBase      = UefiStack.Address;
  StackSize      = UefiStack.Length;
  StackBase      = UefiMemoryBase + UefiMemorySize - StackSize;

  DEBUG(
      (EFI_D_INFO | EFI_D_LOAD,
       "UEFI Memory Base = 0x%llx, Size = 0x%llx, Stack Base = 0x%llx, Stack "
       "Size = 0x%llx\n",
       UefiMemoryBase, UefiMemorySize, StackBase, StackSize));

  // Set up HOB
  HobList = HobConstructor(
      (VOID *)UefiMemoryBase, UefiMemorySize, (VOID *)UefiMemoryBase,
      (VOID *)StackBase);

  PrePeiSetHobList (HobList);

  // Invalidate cache
  InvalidateDataCacheRange(
      (VOID *)(UINTN)UefiFd.Address, UefiFd.Length);

  // Initialize MMU
  Status = MemoryPeim(UefiMemoryBase, UefiMemorySize);
  ASSERT_EFI_ERROR (Status);

  // Add HOBs
  BuildStackHob (StackBase, StackSize);

  // TODO: Call CpuPei as a library
  BuildCpuHob (ArmGetPhysicalAddressBits (), PcdGet8 (PcdPrePiCpuIoSize));

  // Set the Boot Mode
  SetBootMode (BOOT_WITH_DEFAULT_SETTINGS);

  // Initialize Platform HOBs (CpuHob and FvHob)
  Status = PlatformPeim();
  ASSERT_EFI_ERROR (Status);

  // Now, the HOB List has been initialized, we can register performance information
  // PERF_START (NULL, "PEI", NULL, StartTimeStamp);

  // SEC phase needs to run library constructors by hand.
  ProcessLibraryConstructorList();

  // Assume the FV that contains the SEC (our code) also contains a compressed FV.
  Status = DecompressFirstFv();
  ASSERT_EFI_ERROR (Status);

  // Load the DXE Core and transfer control to it
  Status = LoadDxeCoreFromFv(NULL, 0);
  ASSERT_EFI_ERROR (Status);
}

VOID CEntryPoint()
{
  EarlyInitialization();

  // Goto primary Main.
  PrePiMain();

  // DXE Core should always load and never return
  ASSERT(FALSE);
}

VOID
SecondaryCEntryPoint(
  IN  UINTN  MpId
  )
{
  // We must never get into this function on UniCore system
  ASSERT(FALSE);
}