
; float frexp(float value, int *exp)

SECTION code_clib
SECTION code_fp_math48

PUBLIC cm48_sdccix_frexp

EXTERN l0_cm48_sdccix_frexp_callee

cm48_sdccix_frexp:

   pop af
   
   pop de
   pop hl                      ; hlde' = float value
   
   exx
   
   pop hl                      ; hl = exp
   
   push hl
   
   push hl
   push de
   
   push af

   jp l0_cm48_sdccix_frexp_callee
