
; void dzx0_agile_rcs_callee(void *src, void *dst)

SECTION code_clib
SECTION code_compress_zx0

PUBLIC dzx0_agile_rcs_callee

EXTERN asm_dzx0_agile_rcs

dzx0_agile_rcs_callee:

   pop hl
   pop de
   ex (sp),hl
   
   jp asm_dzx0_agile_rcs
