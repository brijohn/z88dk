
; void dzx1_mega_callee(void *src, void *dst)

SECTION code_clib
SECTION code_compress_zx1

PUBLIC dzx1_mega_callee

EXTERN asm_dzx1_mega

dzx1_mega_callee:

   pop hl
   pop de
   ex (sp),hl
   
   jp asm_dzx1_mega
