#
#  Copyright (c) 2011 - 2022, ARM Limited. All rights reserved.
#  Copyright (c) 2014, Linaro Limited. All rights reserved.
#  Copyright (c) 2015 - 2020, Intel Corporation. All rights reserved.
#  Copyright (c) 2018, Bingxing Wang. All rights reserved.
#  Copyright (c) Microsoft Corporation.
#
#  SPDX-License-Identifier: BSD-2-Clause-Patent
#
#

################################################################################
#
# Defines Section - statements that will be processed to create a Makefile.
#
################################################################################
[Defines]
  PLATFORM_NAME                  = SurfaceDuo2
  PLATFORM_GUID                  = b6325ac2-9f3f-4b1d-b129-ac7b35ddde60
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  OUTPUT_DIRECTORY               = Build/SurfaceDuo2Pkg
  SUPPORTED_ARCHITECTURES        = AARCH64
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT
  FLASH_DEFINITION               = SurfaceDuo2Pkg/SurfaceDuo2.fdf
  SECURE_BOOT                    = 0
  USE_PHYSICAL_TIMER             = 0
  USE_SCREEN_FOR_SERIAL_OUTPUT   = 0
  USE_MEMORY_FOR_SERIAL_OUTPUT   = 0

  DEFAULT_KEYS                   = FALSE
  PK_DEFAULT_FILE                = SurfaceDuoFamilyPkg/Include/Resources/SecureBoot/keystore/OEMA0-PK.der
  KEK_DEFAULT_FILE1              = SurfaceDuoFamilyPkg/Include/Resources/SecureBoot/keystore/KEK/Certificates/MicCorKEKCA2011_2011-06-24.der
  KEK_DEFAULT_FILE2              = SurfaceDuoFamilyPkg/Include/Resources/SecureBoot/keystore/KEK/Certificates/microsoft corporation kek 2k ca 2023.der
  KEK_DEFAULT_FILE3              = SurfaceDuoFamilyPkg/Include/Resources/SecureBoot/keystore/OEMA0-KEK.der
  DB_DEFAULT_FILE1               = SurfaceDuoFamilyPkg/Include/Resources/SecureBoot/keystore/DB/Certificates/MicWinProPCA2011_2011-10-19.der
  DB_DEFAULT_FILE2               = SurfaceDuoFamilyPkg/Include/Resources/SecureBoot/keystore/DB/Certificates/windows uefi ca 2023.der
  DB_DEFAULT_FILE3               = SurfaceDuoFamilyPkg/Include/Resources/SecureBoot/keystore/DB/Certificates/MicCorUEFCA2011_2011-06-27.der
  DB_DEFAULT_FILE4               = SurfaceDuoFamilyPkg/Include/Resources/SecureBoot/keystore/DB/Certificates/microsoft uefi ca 2023.der
  DB_DEFAULT_FILE5               = SurfaceDuoFamilyPkg/Include/Resources/SecureBoot/keystore/DB/Certificates/microsoft option rom uefi ca 2023.der
  DBX_DEFAULT_FILE1              = SurfaceDuoFamilyPkg/Include/Resources/SecureBoot/Artifacts/Aarch64/DefaultDbx.bin

  PEI_CRYPTO_SERVICES            = NONE
  DXE_CRYPTO_SERVICES            = STANDARD
  RUNTIMEDXE_CRYPTO_SERVICES     = STANDARD
  SMM_CRYPTO_SERVICES            = NONE
  STANDALONEMM_CRYPTO_SERVICES   = NONE
  PEI_CRYPTO_ARCH                = NONE
  DXE_CRYPTO_ARCH                = AARCH64
  RUNTIMEDXE_CRYPTO_ARCH         = AARCH64
  SMM_CRYPTO_ARCH                = NONE
  STANDALONEMM_CRYPTO_ARCH       = NONE

  PLATFORM_HAS_ACTLR_EL1_UNIMPLEMENTED_ERRATA         = 1
  PLATFORM_HAS_AMCNTENSET0_EL0_UNIMPLEMENTED_ERRATA   = 0
  PLATFORM_HAS_GIC_V3_WITHOUT_IRM_FLAG_SUPPORT_ERRATA = 1
  PLATFORM_HAS_PSCI_MEMPROTECT_FAILING_ERRATA         = 0

[PcdsFixedAtBuild.common]
  # Platform-specific
  gArmTokenSpaceGuid.PcdSystemMemorySize|0x200000000        # 8GB Size

  # SMBIOS
  gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdSmbiosSystemModel|"Surface Duo 2"
  gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdSmbiosSystemRetailModel|"1995"
  gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdSmbiosSystemRetailSku|"Surface_Duo_2_1995"
  gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdSmbiosBoardModel|"Surface Duo 2"

  # Simple FrameBuffer
  gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdMipiFrameBufferWidth|1344
  gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdMipiFrameBufferHeight|1892
  gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdMipiFrameBufferPixelBpp|32

  gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdABLProduct|"surfaceduo2"

[PcdsDynamicDefault.common]
  gEfiMdeModulePkgTokenSpaceGuid.PcdVideoHorizontalResolution|1344
  gEfiMdeModulePkgTokenSpaceGuid.PcdVideoVerticalResolution|1892
  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoHorizontalResolution|1344
  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoVerticalResolution|1892
  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutColumn|168 # 168 = 1344 / EFI_GLYPH_WIDTH(8)
  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutRow|99 # 99.57 = 1892 / EFI_GLYPH_HEIGHT(19)
  gEfiMdeModulePkgTokenSpaceGuid.PcdConOutColumn|168 # 168 = 1344 / EFI_GLYPH_WIDTH(8)
  gEfiMdeModulePkgTokenSpaceGuid.PcdConOutRow|99 # 99.57 = 1892 / EFI_GLYPH_HEIGHT(19)

!include QcomPkg/QcomPkg.dsc.inc
!include SurfaceDuoFamilyPkg/SurfaceDuoFamily.dsc.inc
!include SurfaceDuoFamilyPkg/Frontpage.dsc.inc

[Components.common]
  SurfaceDuo2Pkg/AcpiTables/AcpiTables.inf
