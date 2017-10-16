
SECTION data_align_256

PUBLIC asci0TxBuffer

EXTERN __ASCI0_TX_SIZE

; asci0TxBuffer:   defs __ASCI0_TX_SIZE  ; Space for the Tx Buffer
asci0TxBuffer:   defm __ASCI0_TX_SIZE  ; Space for the Tx Buffer

; pad to next 256 byte boundary

IF (ASMPC & 0xff)
   defs 256 - (ASMPC & 0xff)
ENDIF

SECTION data_driver

PUBLIC asci0TxCount, asci0TxIn, asci0TxOut, asci0TxLock

asci0TxCount:    defb 0                 ; Space for Tx Buffer Management
asci0TxIn:       defw asci0TxBuffer     ; non-zero item in bss since it's initialized anyway
asci0TxOut:      defw asci0TxBuffer     ; non-zero item in bss since it's initialized anyway
asci0TxLock:     defb 0                 ; lock flag for Tx exclusion

