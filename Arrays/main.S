	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 15, 0	sdk_version 15, 2
	.globl	__Z13trapped_waterPii           ; -- Begin function _Z13trapped_waterPii
	.p2align	2
__Z13trapped_waterPii:                  ; @_Z13trapped_waterPii
	.cfi_startproc
; %bb.0:
	stp	x29, x30, [sp, #-16]!           ; 16-byte Folded Spill
	mov	x29, sp
	sub	sp, sp, #112
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	adrp	x8, ___stack_chk_guard@GOTPAGE
	ldr	x8, [x8, ___stack_chk_guard@GOTPAGEOFF]
	ldr	x8, [x8]
	stur	x8, [x29, #-8]
	stur	x0, [x29, #-16]
	stur	w1, [x29, #-20]
	stur	wzr, [x29, #-24]
	ldur	w8, [x29, #-20]
                                        ; kill: def $x8 killed $w8
	mov	x9, sp
	stur	x9, [x29, #-32]
	lsl	x9, x8, #2
	add	x9, x9, #15
	and	x9, x9, #0xfffffffffffffff0
	stur	x9, [x29, #-96]                 ; 8-byte Folded Spill
	adrp	x16, ___chkstk_darwin@GOTPAGE
	ldr	x16, [x16, ___chkstk_darwin@GOTPAGEOFF]
	blr	x16
	ldur	x10, [x29, #-96]                ; 8-byte Folded Reload
	mov	x9, sp
	subs	x9, x9, x10
	mov	sp, x9
	stur	x9, [x29, #-80]                 ; 8-byte Folded Spill
	stur	x8, [x29, #-40]
	ldur	w8, [x29, #-20]
                                        ; kill: def $x8 killed $w8
	lsl	x9, x8, #2
	add	x9, x9, #15
	and	x9, x9, #0xfffffffffffffff0
	stur	x9, [x29, #-88]                 ; 8-byte Folded Spill
	adrp	x16, ___chkstk_darwin@GOTPAGE
	ldr	x16, [x16, ___chkstk_darwin@GOTPAGEOFF]
	blr	x16
	ldur	x11, [x29, #-88]                ; 8-byte Folded Reload
	ldur	x9, [x29, #-80]                 ; 8-byte Folded Reload
	mov	x10, sp
	subs	x10, x10, x11
	mov	sp, x10
	stur	x10, [x29, #-72]                ; 8-byte Folded Spill
	stur	x8, [x29, #-48]
	ldur	x8, [x29, #-16]
	ldr	w8, [x8]
	str	w8, [x9]
	ldur	x9, [x29, #-16]
	ldur	w11, [x29, #-20]
	mov	w8, #1                          ; =0x1
	subs	w11, w11, #1
	ldr	w9, [x9, w11, sxtw #2]
	ldur	w11, [x29, #-20]
	subs	w11, w11, #1
	str	w9, [x10, w11, sxtw #2]
	stur	w8, [x29, #-52]
	b	LBB0_1
LBB0_1:                                 ; =>This Inner Loop Header: Depth=1
	ldur	w8, [x29, #-52]
	ldur	w9, [x29, #-20]
	subs	w8, w8, w9
	cset	w8, ge
	tbnz	w8, #0, LBB0_4
	b	LBB0_2
LBB0_2:                                 ;   in Loop: Header=BB0_1 Depth=1
	ldur	x8, [x29, #-80]                 ; 8-byte Folded Reload
	ldur	w9, [x29, #-52]
	subs	w9, w9, #1
	add	x0, x8, w9, sxtw #2
	ldur	x8, [x29, #-16]
	ldursw	x9, [x29, #-52]
	add	x1, x8, x9, lsl #2
	bl	__ZNSt3__13maxB8ne180100IiEERKT_S3_S3_
	ldur	x9, [x29, #-80]                 ; 8-byte Folded Reload
	ldr	w8, [x0]
	ldursw	x10, [x29, #-52]
	str	w8, [x9, x10, lsl #2]
	b	LBB0_3
LBB0_3:                                 ;   in Loop: Header=BB0_1 Depth=1
	ldur	w8, [x29, #-52]
	add	w8, w8, #1
	stur	w8, [x29, #-52]
	b	LBB0_1
LBB0_4:
	ldur	w8, [x29, #-20]
	subs	w8, w8, #2
	stur	w8, [x29, #-56]
	b	LBB0_5
LBB0_5:                                 ; =>This Inner Loop Header: Depth=1
	ldur	w8, [x29, #-56]
	subs	w8, w8, #0
	cset	w8, lt
	tbnz	w8, #0, LBB0_8
	b	LBB0_6
LBB0_6:                                 ;   in Loop: Header=BB0_5 Depth=1
	ldur	x8, [x29, #-72]                 ; 8-byte Folded Reload
	ldur	w9, [x29, #-56]
	add	w9, w9, #1
	add	x0, x8, w9, sxtw #2
	ldur	x8, [x29, #-16]
	ldursw	x9, [x29, #-56]
	add	x1, x8, x9, lsl #2
	bl	__ZNSt3__13maxB8ne180100IiEERKT_S3_S3_
	ldur	x9, [x29, #-72]                 ; 8-byte Folded Reload
	ldr	w8, [x0]
	ldursw	x10, [x29, #-56]
	str	w8, [x9, x10, lsl #2]
	b	LBB0_7
LBB0_7:                                 ;   in Loop: Header=BB0_5 Depth=1
	ldur	w8, [x29, #-56]
	subs	w8, w8, #1
	stur	w8, [x29, #-56]
	b	LBB0_5
LBB0_8:
	stur	wzr, [x29, #-60]
	b	LBB0_9
LBB0_9:                                 ; =>This Inner Loop Header: Depth=1
	ldur	w8, [x29, #-60]
	ldur	w9, [x29, #-20]
	subs	w8, w8, w9
	cset	w8, ge
	tbnz	w8, #0, LBB0_12
	b	LBB0_10
LBB0_10:                                ;   in Loop: Header=BB0_9 Depth=1
	ldur	x8, [x29, #-72]                 ; 8-byte Folded Reload
	ldur	x9, [x29, #-80]                 ; 8-byte Folded Reload
	ldursw	x10, [x29, #-60]
	add	x0, x9, x10, lsl #2
	ldursw	x9, [x29, #-60]
	add	x1, x8, x9, lsl #2
	bl	__ZNSt3__13minB8ne180100IiEERKT_S3_S3_
	ldr	w8, [x0]
	ldur	x9, [x29, #-16]
	ldursw	x10, [x29, #-60]
	ldr	w9, [x9, x10, lsl #2]
	subs	w9, w8, w9
	ldur	w8, [x29, #-24]
	add	w8, w8, w9
	stur	w8, [x29, #-24]
	b	LBB0_11
LBB0_11:                                ;   in Loop: Header=BB0_9 Depth=1
	ldur	w8, [x29, #-60]
	add	w8, w8, #1
	stur	w8, [x29, #-60]
	b	LBB0_9
LBB0_12:
	ldur	w8, [x29, #-24]
	stur	w8, [x29, #-108]                ; 4-byte Folded Spill
	ldur	x8, [x29, #-32]
	stur	x8, [x29, #-104]                ; 8-byte Folded Spill
	ldur	x9, [x29, #-8]
	adrp	x8, ___stack_chk_guard@GOTPAGE
	ldr	x8, [x8, ___stack_chk_guard@GOTPAGEOFF]
	ldr	x8, [x8]
	subs	x8, x8, x9
	cset	w8, eq
	tbnz	w8, #0, LBB0_14
	b	LBB0_13
LBB0_13:
	bl	___stack_chk_fail
LBB0_14:
	ldur	w0, [x29, #-108]                ; 4-byte Folded Reload
	ldur	x8, [x29, #-104]                ; 8-byte Folded Reload
	mov	sp, x8
	mov	sp, x29
	ldp	x29, x30, [sp], #16             ; 16-byte Folded Reload
	ret
	.cfi_endproc
                                        ; -- End function
	.private_extern	__ZNSt3__13maxB8ne180100IiEERKT_S3_S3_ ; -- Begin function _ZNSt3__13maxB8ne180100IiEERKT_S3_S3_
	.globl	__ZNSt3__13maxB8ne180100IiEERKT_S3_S3_
	.weak_definition	__ZNSt3__13maxB8ne180100IiEERKT_S3_S3_
	.p2align	2
__ZNSt3__13maxB8ne180100IiEERKT_S3_S3_: ; @_ZNSt3__13maxB8ne180100IiEERKT_S3_S3_
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #48
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	x0, [x29, #-8]
	str	x1, [sp, #16]
	ldur	x0, [x29, #-8]
	ldr	x1, [sp, #16]
	bl	__ZNSt3__13maxB8ne180100IiNS_6__lessIvvEEEERKT_S5_S5_T0_
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
	.cfi_endproc
                                        ; -- End function
	.private_extern	__ZNSt3__13minB8ne180100IiEERKT_S3_S3_ ; -- Begin function _ZNSt3__13minB8ne180100IiEERKT_S3_S3_
	.globl	__ZNSt3__13minB8ne180100IiEERKT_S3_S3_
	.weak_definition	__ZNSt3__13minB8ne180100IiEERKT_S3_S3_
	.p2align	2
__ZNSt3__13minB8ne180100IiEERKT_S3_S3_: ; @_ZNSt3__13minB8ne180100IiEERKT_S3_S3_
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #48
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	x0, [x29, #-8]
	str	x1, [sp, #16]
	ldur	x0, [x29, #-8]
	ldr	x1, [sp, #16]
	bl	__ZNSt3__13minB8ne180100IiNS_6__lessIvvEEEERKT_S5_S5_T0_
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #96
	stp	x29, x30, [sp, #80]             ; 16-byte Folded Spill
	add	x29, sp, #80
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	adrp	x8, ___stack_chk_guard@GOTPAGE
	ldr	x8, [x8, ___stack_chk_guard@GOTPAGEOFF]
	ldr	x8, [x8]
	stur	x8, [x29, #-8]
	str	wzr, [sp, #20]
	add	x0, sp, #24
	str	x0, [sp, #8]                    ; 8-byte Folded Spill
	mov	x2, #48                         ; =0x30
	adrp	x1, l___const.main.array@PAGE
	add	x1, x1, l___const.main.array@PAGEOFF
	bl	_memcpy
	ldr	x0, [sp, #8]                    ; 8-byte Folded Reload
	mov	w8, #12                         ; =0xc
	str	w8, [sp, #16]
	ldr	w1, [sp, #16]
	bl	__Z13trapped_waterPii
	mov	x1, x0
	adrp	x0, __ZNSt3__14coutE@GOTPAGE
	ldr	x0, [x0, __ZNSt3__14coutE@GOTPAGEOFF]
	bl	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEi
	ldur	x9, [x29, #-8]
	adrp	x8, ___stack_chk_guard@GOTPAGE
	ldr	x8, [x8, ___stack_chk_guard@GOTPAGEOFF]
	ldr	x8, [x8]
	subs	x8, x8, x9
	cset	w8, eq
	tbnz	w8, #0, LBB3_2
	b	LBB3_1
LBB3_1:
	bl	___stack_chk_fail
LBB3_2:
	mov	w0, #0                          ; =0x0
	ldp	x29, x30, [sp, #80]             ; 16-byte Folded Reload
	add	sp, sp, #96
	ret
	.cfi_endproc
                                        ; -- End function
	.private_extern	__ZNSt3__13maxB8ne180100IiNS_6__lessIvvEEEERKT_S5_S5_T0_ ; -- Begin function _ZNSt3__13maxB8ne180100IiNS_6__lessIvvEEEERKT_S5_S5_T0_
	.globl	__ZNSt3__13maxB8ne180100IiNS_6__lessIvvEEEERKT_S5_S5_T0_
	.weak_definition	__ZNSt3__13maxB8ne180100IiNS_6__lessIvvEEEERKT_S5_S5_T0_
	.p2align	2
__ZNSt3__13maxB8ne180100IiNS_6__lessIvvEEEERKT_S5_S5_T0_: ; @_ZNSt3__13maxB8ne180100IiNS_6__lessIvvEEEERKT_S5_S5_T0_
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #48
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	str	x0, [sp, #16]
	str	x1, [sp, #8]
	ldr	x1, [sp, #16]
	ldr	x2, [sp, #8]
	sub	x0, x29, #1
	bl	__ZNKSt3__16__lessIvvEclB8ne180100IiiEEbRKT_RKT0_
	tbz	w0, #0, LBB4_2
	b	LBB4_1
LBB4_1:
	ldr	x8, [sp, #8]
	str	x8, [sp]                        ; 8-byte Folded Spill
	b	LBB4_3
LBB4_2:
	ldr	x8, [sp, #16]
	str	x8, [sp]                        ; 8-byte Folded Spill
	b	LBB4_3
LBB4_3:
	ldr	x0, [sp]                        ; 8-byte Folded Reload
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
	.cfi_endproc
                                        ; -- End function
	.private_extern	__ZNKSt3__16__lessIvvEclB8ne180100IiiEEbRKT_RKT0_ ; -- Begin function _ZNKSt3__16__lessIvvEclB8ne180100IiiEEbRKT_RKT0_
	.globl	__ZNKSt3__16__lessIvvEclB8ne180100IiiEEbRKT_RKT0_
	.weak_definition	__ZNKSt3__16__lessIvvEclB8ne180100IiiEEbRKT_RKT0_
	.p2align	2
__ZNKSt3__16__lessIvvEclB8ne180100IiiEEbRKT_RKT0_: ; @_ZNKSt3__16__lessIvvEclB8ne180100IiiEEbRKT_RKT0_
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #32
	.cfi_def_cfa_offset 32
	str	x0, [sp, #24]
	str	x1, [sp, #16]
	str	x2, [sp, #8]
	ldr	x8, [sp, #16]
	ldr	w8, [x8]
	ldr	x9, [sp, #8]
	ldr	w9, [x9]
	subs	w8, w8, w9
	cset	w8, lt
	and	w0, w8, #0x1
	add	sp, sp, #32
	ret
	.cfi_endproc
                                        ; -- End function
	.private_extern	__ZNSt3__13minB8ne180100IiNS_6__lessIvvEEEERKT_S5_S5_T0_ ; -- Begin function _ZNSt3__13minB8ne180100IiNS_6__lessIvvEEEERKT_S5_S5_T0_
	.globl	__ZNSt3__13minB8ne180100IiNS_6__lessIvvEEEERKT_S5_S5_T0_
	.weak_definition	__ZNSt3__13minB8ne180100IiNS_6__lessIvvEEEERKT_S5_S5_T0_
	.p2align	2
__ZNSt3__13minB8ne180100IiNS_6__lessIvvEEEERKT_S5_S5_T0_: ; @_ZNSt3__13minB8ne180100IiNS_6__lessIvvEEEERKT_S5_S5_T0_
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #48
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	str	x0, [sp, #16]
	str	x1, [sp, #8]
	ldr	x1, [sp, #8]
	ldr	x2, [sp, #16]
	sub	x0, x29, #1
	bl	__ZNKSt3__16__lessIvvEclB8ne180100IiiEEbRKT_RKT0_
	tbz	w0, #0, LBB6_2
	b	LBB6_1
LBB6_1:
	ldr	x8, [sp, #8]
	str	x8, [sp]                        ; 8-byte Folded Spill
	b	LBB6_3
LBB6_2:
	ldr	x8, [sp, #16]
	str	x8, [sp]                        ; 8-byte Folded Spill
	b	LBB6_3
LBB6_3:
	ldr	x0, [sp]                        ; 8-byte Folded Reload
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__const
	.p2align	2, 0x0                          ; @__const.main.array
l___const.main.array:
	.long	1                               ; 0x1
	.long	0                               ; 0x0
	.long	3                               ; 0x3
	.long	4                               ; 0x4
	.long	5                               ; 0x5
	.long	0                               ; 0x0
	.long	5                               ; 0x5
	.long	7                               ; 0x7
	.long	7                               ; 0x7
	.long	8                               ; 0x8
	.long	9                               ; 0x9
	.long	0                               ; 0x0

.subsections_via_symbols
