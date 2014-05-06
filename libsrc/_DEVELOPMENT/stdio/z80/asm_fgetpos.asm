
; ===============================================================
; Jan 2014
; ===============================================================
; 
; int fgetpos(FILE *stream, fpos_t *pos)
;
; Write current file position to pos.
;
; This implementation does not support multibyte character sets
; so the value written to pos is the same as returned by ftell().
;
; ===============================================================

INCLUDE "clib_cfg.asm"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
IF __CLIB_OPT_MULTITHREAD & $02
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

XLIB asm_fgetpos

LIB asm0_fgetpos_unlocked, __stdio_lock_release

asm_fgetpos:

   ; enter :   ix = FILE *
   ;           hl = fpos_t *pos
   ;
   ; exit  :   ix = FILE *
   ;
   ;         success
   ;
   ;           hl = 0
   ;           carry reset
   ;
   ;         fail
   ;
   ;           hl = -1
   ;           carry set
   ;
   ; uses  : all except ix

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
IF __CLIB_OPT_STDIO & $01

   LIB __stdio_verify_valid_lock

   call __stdio_verify_valid_lock
   ret c

ELSE

   LIB __stdio_lock_acquire, error_enolck_mc
   
   call __stdio_lock_acquire
   jp c, error_enolck_mc

ENDIF
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
   
   call asm0_fgetpos_unlocked
   jp __stdio_lock_release

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
ELSE
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

XLIB asm_fgetpos

LIB asm_fgetpos_unlocked

asm_fgetpos:

   jp asm_fgetpos_unlocked

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
ENDIF
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
