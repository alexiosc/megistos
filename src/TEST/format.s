	.file	"format.c"
gcc2_compiled.:
___gnu_compiled_c:
.text
	.align 4
___gnu_calloc:
	pushl %ebp
	movl %esp,%ebp
	pushl %esi
	pushl %ebx
	movl 8(%ebp),%ebx
	movl 12(%ebp),%esi
	movl %esi,%eax
	testl %esi,%esi
	jne L2
	movl $1,%eax
L2:
	pushl %eax
	movl %ebx,%eax
	testl %ebx,%ebx
	jne L3
	movl $1,%eax
L3:
	pushl %eax
	call _calloc
	addl $8,%esp
	movl %eax,%edx
	movl %edx,%eax
	jmp L1
	.align 4,0x90
L1:
	leal -8(%ebp),%esp
	popl %ebx
	popl %esi
	movl %ebp,%esp
	popl %ebp
	ret
	.align 4
___gnu_malloc:
	pushl %ebp
	movl %esp,%ebp
	pushl %ebx
	movl 8(%ebp),%ebx
	movl %ebx,%eax
	testl %ebx,%ebx
	jne L5
	movl $1,%eax
L5:
	pushl %eax
	call _malloc
	addl $4,%esp
	movl %eax,%edx
	movl %edx,%eax
	jmp L4
	.align 4,0x90
L4:
	movl -4(%ebp),%ebx
	movl %ebp,%esp
	popl %ebp
	ret
.globl _RMARGIN
.data
	.align 2
_RMARGIN:
	.long 1
.globl _LMARGIN
	.align 2
_LMARGIN:
	.long 0
.globl _flags
	.align 2
_flags:
	.long 0
.globl _xpos
	.align 2
_xpos:
	.long 0
.globl _plidx
	.align 2
_plidx:
	.long 0
.globl _comidx
	.align 2
_comidx:
	.long 0
.globl _comstate
	.align 2
_comstate:
	.long 0
.globl _lastc
_lastc:
	.byte 32
.globl _lastpos
	.align 2
_lastpos:
	.long 0
.globl _lastp
	.align 2
_lastp:
	.long 0
.globl _savepos
	.align 2
_savepos:
	.long 0
.text
LC0:
	.byte 0
	.space 1023
LC1:
	.ascii "%s%s%s\0"
	.align 4
.globl _strins
_strins:
	pushl %ebp
	movl %esp,%ebp
	subl $9220,%esp
	pushl %edi
	pushl %esi
	leal -1024(%ebp),%edi
	movl $LC0,%esi
	cld
	movl $256,%ecx
	rep
	movsl
	movl 8(%ebp),%ecx
	addl 12(%ebp),%ecx
	movl %ecx,-1028(%ebp)
	cmpl $0,12(%ebp)
	je L13
	movl 12(%ebp),%ecx
	pushl %ecx
	movl 8(%ebp),%ecx
	pushl %ecx
	leal -1024(%ebp),%eax
	pushl %eax
	call _memcpy
	addl $12,%esp
L13:
	movl -1028(%ebp),%ecx
	pushl %ecx
	movl 16(%ebp),%ecx
	pushl %ecx
	leal -1024(%ebp),%eax
	pushl %eax
	pushl $LC1
	leal -9220(%ebp),%eax
	pushl %eax
	call _sprintf
	addl $20,%esp
	leal -9220(%ebp),%edx
	movl %edx,%eax
	jmp L12
	.align 4,0x90
L12:
	leal -9228(%ebp),%esp
	popl %esi
	popl %edi
	movl %ebp,%esp
	popl %ebp
	ret
LC2:
	.ascii " \0"
	.align 4
.globl _justify
_justify:
	pushl %ebp
	movl %esp,%ebp
	subl $36,%esp
	pushl %esi
	pushl %ebx
	movl $132,%eax
	subl _LMARGIN,%eax
	movl %eax,%edx
	subl _RMARGIN,%edx
	movl %edx,%esi
	subl _lastpos,%esi
	movl %esi,-4(%ebp)
	cmpl $0,-4(%ebp)
	jg L15
	jmp L14
	.align 4,0x90
L15:
	movl 8(%ebp),%ebx
	pushl %ebx
	call _strlen
	addl $4,%esp
	movl %eax,%ecx
	movl %ecx,%eax
	xorl %edx,%edx
	divl -4(%ebp)
	movl %eax,%ebx
	xorl %esi,%esi
	movl %ebx,-36(%ebp)
	movl %esi,-32(%ebp)
	fildq -36(%ebp)
	fstps -8(%ebp)
	movl $0,-12(%ebp)
L16:
	movl -12(%ebp),%eax
	cmpl %eax,-4(%ebp)
	jle L17
	movl -12(%ebp),%eax
	incl %eax
	pushl %eax
	fildl (%esp)
	addl $4,%esp
	fmuls -8(%ebp)
	fnstcw -24(%ebp)
	movl -24(%ebp),%ebx
	movb $12,%bh
	movl %ebx,-28(%ebp)
	fldcw -28(%ebp)
	subl $4,%esp
	fistpl (%esp)
	popl %eax
	fldcw -24(%ebp)
	movl 8(%ebp),%esi
	addl %eax,%esi
	movl %esi,-16(%ebp)
	movl -16(%ebp),%ebx
	movl %ebx,-20(%ebp)
L19:
	movl -20(%ebp),%eax
	cmpb $0,(%eax)
	je L20
	movl -20(%ebp),%eax
	cmpb $32,(%eax)
	je L20
L21:
	incl -20(%ebp)
	jmp L19
	.align 4,0x90
L20:
	movl -20(%ebp),%eax
	cmpb $0,(%eax)
	je L22
	pushl $LC2
	movl -20(%ebp),%eax
	subl 8(%ebp),%eax
	pushl %eax
	movl 8(%ebp),%esi
	pushl %esi
	call _strins
	addl $12,%esp
	movl %eax,%eax
	pushl %eax
	movl 8(%ebp),%ebx
	pushl %ebx
	call _strcpy
	addl $8,%esp
	jmp L23
	.align 4,0x90
L22:
	movl -16(%ebp),%esi
	movl %esi,-20(%ebp)
L24:
	movl -20(%ebp),%eax
	cmpl %eax,8(%ebp)
	ja L25
	movl -20(%ebp),%eax
	cmpb $32,(%eax)
	je L25
L26:
	decl -20(%ebp)
	jmp L24
	.align 4,0x90
L25:
	movl -20(%ebp),%eax
	cmpl %eax,8(%ebp)
	ja L27
	pushl $LC2
	movl -20(%ebp),%eax
	subl 8(%ebp),%eax
	pushl %eax
	movl 8(%ebp),%ebx
	pushl %ebx
	call _strins
	addl $12,%esp
	movl %eax,%eax
	pushl %eax
	movl 8(%ebp),%esi
	pushl %esi
	call _strcpy
	addl $8,%esp
	jmp L28
	.align 4,0x90
L27:
	jmp L17
	.align 4,0x90
L28:
L23:
L18:
	incl -12(%ebp)
	jmp L16
	.align 4,0x90
L17:
L14:
	leal -44(%ebp),%esp
	popl %ebx
	popl %esi
	movl %ebp,%esp
	popl %ebp
	ret
LC3:
	.ascii "%d;%d\0"
LC4:
	.byte 0
	.space 255
LC5:
	.ascii "%s%s\0"
LC6:
	.ascii "%s%s\12\0"
	.align 4
.globl _format
_format:
	pushl %ebp
	movl %esp,%ebp
	subl $1296,%esp
	pushl %edi
	pushl %esi
	movl 8(%ebp),%ecx
	movl %ecx,-4(%ebp)
	movl $0,_lastp
L30:
	movl -4(%ebp),%eax
	movb (%eax),%dl
	movb %dl,-5(%ebp)
	testb %dl,%dl
	je L31
	movb _flags,%al
	andb $16,%al
	testb %al,%al
	je L32
	movb _flags,%al
	andb $12,%al
	testb %al,%al
	je L32
	cmpb $10,-5(%ebp)
	je L34
	cmpb $13,-5(%ebp)
	je L34
	jmp L33
	.align 4,0x90
L34:
	movb $32,-5(%ebp)
L33:
	cmpb $32,_lastc
	je L35
	cmpb $32,-5(%ebp)
	jne L35
	movl _xpos,%ecx
	movl %ecx,_lastpos
L35:
	movb -5(%ebp),%cl
	movb %cl,_lastc
L32:
	movl _comstate,%eax
	cmpl $1,%eax
	je L40
	cmpl $1,%eax
	jg L105
	testl %eax,%eax
	je L37
	jmp L104
	.align 4,0x90
L105:
	cmpl $2,%eax
	je L45
	cmpl $3,%eax
	je L47
	jmp L104
	.align 4,0x90
L37:
	cmpb $27,-5(%ebp)
	jne L38
	movb $0,_command
	movl $0,_comidx
	movl $1,_comstate
	movl $0,_comidx
	jmp L39
	.align 4,0x90
L38:
	movl _plidx,%eax
	addl $_prevline,%eax
	movb -5(%ebp),%cl
	movb %cl,(%eax)
	incl _plidx
	movl _plidx,%eax
	addl $_prevline,%eax
	movb $0,(%eax)
	incl _xpos
L39:
	jmp L36
	.align 4,0x90
L40:
	cmpb $91,-5(%ebp)
	jne L41
	movl $2,_comstate
	jmp L42
	.align 4,0x90
L41:
	cmpb $33,-5(%ebp)
	jne L43
	movl $3,_comstate
	jmp L44
	.align 4,0x90
L43:
	movl $0,_comstate
	movl _plidx,%eax
	addl $_prevline,%eax
	movb -5(%ebp),%cl
	movb %cl,(%eax)
	incl _plidx
	movl _plidx,%eax
	addl $_prevline,%eax
	movb $0,(%eax)
L44:
L42:
	jmp L36
	.align 4,0x90
L45:
	cmpl $0,_comidx
	jne L46
	movl _plidx,%eax
	addl $_prevline,%eax
	movb $27,(%eax)
	incl _plidx
	movl _plidx,%eax
	addl $_prevline,%eax
	movb $91,(%eax)
	incl _plidx
	movl _plidx,%eax
	addl $_prevline,%eax
	movb $0,(%eax)
L46:
L47:
	cmpl $3,_comstate
	je L48
	movl _plidx,%eax
	addl $_prevline,%eax
	movb -5(%ebp),%cl
	movb %cl,(%eax)
	incl _plidx
	movl _plidx,%eax
	addl $_prevline,%eax
	movb $0,(%eax)
L48:
	movsbl -5(%ebp),%eax
	movl %eax,%edx
	movl %edx,%eax
	addl %edx,%eax
	movl ___ctype_b,%edx
	movb (%edx,%eax),%al
	andb $8,%al
	testb %al,%al
	jne L50
	cmpb $59,-5(%ebp)
	je L50
	jmp L49
	.align 4,0x90
L50:
	movl _comidx,%eax
	addl $_command,%eax
	movb -5(%ebp),%cl
	movb %cl,(%eax)
	incl _comidx
	jmp L51
	.align 4,0x90
L49:
	movl _comidx,%eax
	addl $_command,%eax
	movb $0,(%eax)
	cmpl $2,_comstate
	jne L52
	movb -5(%ebp),%dl
	addb $-67,%dl
	movsbl %dl,%eax
	movl $50,%edx
	cmpl %eax,%edx
	jb L76
	movl L75(,%eax,4),%eax
	jmp *%eax
	.align 4,0x90
L75:
	.long L54
	.long L60
	.long L76
	.long L76
	.long L76
	.long L67
	.long L76
	.long L66
	.long L76
	.long L76
	.long L76
	.long L76
	.long L76
	.long L76
	.long L76
	.long L76
	.long L76
	.long L76
	.long L76
	.long L76
	.long L76
	.long L76
	.long L76
	.long L76
	.long L76
	.long L76
	.long L76
	.long L76
	.long L76
	.long L76
	.long L76
	.long L76
	.long L76
	.long L76
	.long L76
	.long L76
	.long L76
	.long L76
	.long L76
	.long L76
	.long L76
	.long L76
	.long L76
	.long L76
	.long L76
	.long L76
	.long L76
	.long L76
	.long L73
	.long L76
	.long L74
	.align 4,0x90
L54:
	cmpb $0,_command
	je L55
	pushl $_command
	call _atoi
	addl $4,%esp
	movl %eax,%eax
	movl %eax,%edx
	addl _xpos,%edx
	cmpl $131,%edx
	jg L56
	pushl $_command
	call _atoi
	addl $4,%esp
	movl %eax,%edx
	movl %edx,%eax
	addl _xpos,%eax
	jmp L57
	.align 4,0x90
L56:
	movl $131,%eax
L57:
	movl %eax,_xpos
	jmp L58
	.align 4,0x90
L55:
	incl _xpos
	cmpl $131,_xpos
	jle L59
	movl $131,_xpos
L59:
L58:
	jmp L53
	.align 4,0x90
L60:
	cmpb $0,_command
	je L61
	pushl $_command
	call _atoi
	addl $4,%esp
	movl %eax,%eax
	movl _xpos,%edx
	subl %eax,%edx
	testl %edx,%edx
	jl L62
	pushl $_command
	call _atoi
	addl $4,%esp
	movl %eax,%edx
	movl _xpos,%eax
	subl %edx,%eax
	jmp L63
	.align 4,0x90
L62:
	xorl %eax,%eax
L63:
	movl %eax,_xpos
	jmp L64
	.align 4,0x90
L61:
	decl _xpos
	cmpl $0,_xpos
	jge L65
	movl $0,_xpos
L65:
L64:
	jmp L53
	.align 4,0x90
L66:
	movl $0,_xpos
	jmp L53
	.align 4,0x90
L67:
	leal -16(%ebp),%eax
	pushl %eax
	leal -12(%ebp),%eax
	pushl %eax
	pushl $LC3
	pushl $_command
	call _sscanf
	addl $16,%esp
	movl %eax,%eax
	cmpl $2,%eax
	jne L68
	movl -16(%ebp),%ecx
	decl %ecx
	movl %ecx,_xpos
	jmp L69
	.align 4,0x90
L68:
	movl $0,_xpos
L69:
	cmpl $0,_xpos
	jge L70
	movl $0,-16(%ebp)
	jmp L71
	.align 4,0x90
L70:
	cmpl $131,_xpos
	jle L72
	movl $131,_xpos
L72:
L71:
	jmp L53
	.align 4,0x90
L73:
	movl _xpos,%ecx
	movl %ecx,_savepos
	jmp L53
	.align 4,0x90
L74:
	movl _savepos,%ecx
	movl %ecx,_xpos
	jmp L53
	.align 4,0x90
L76:
L53:
	jmp L77
	.align 4,0x90
L52:
	cmpl $3,_comstate
	jne L78
	movb -5(%ebp),%dl
	addb $-40,%dl
	movsbl %dl,%eax
	movl $74,%edx
	cmpl %eax,%edx
	jb L102
	movl L101(,%eax,4),%eax
	jmp *%eax
	.align 4,0x90
L101:
	.long L85
	.long L86
	.long L102
	.long L102
	.long L102
	.long L102
	.long L102
	.long L102
	.long L102
	.long L102
	.long L102
	.long L102
	.long L102
	.long L102
	.long L102
	.long L102
	.long L102
	.long L102
	.long L102
	.long L102
	.long L102
	.long L102
	.long L102
	.long L102
	.long L102
	.long L102
	.long L102
	.long L82
	.long L102
	.long L102
	.long L99
	.long L102
	.long L102
	.long L102
	.long L84
	.long L102
	.long L80
	.long L102
	.long L102
	.long L102
	.long L102
	.long L102
	.long L81
	.long L102
	.long L102
	.long L102
	.long L102
	.long L83
	.long L102
	.long L102
	.long L102
	.long L102
	.long L102
	.long L102
	.long L102
	.long L102
	.long L102
	.long L102
	.long L102
	.long L102
	.long L102
	.long L102
	.long L102
	.long L102
	.long L102
	.long L102
	.long L102
	.long L102
	.long L93
	.long L102
	.long L102
	.long L102
	.long L102
	.long L102
	.long L87
	.align 4,0x90
L80:
	movl _flags,%eax
	andb $240,%al
	movl %eax,%ecx
	orb $16,%cl
	movl %ecx,_flags
	jmp L79
	.align 4,0x90
L81:
	movl _flags,%eax
	andb $240,%al
	movl %eax,%ecx
	orb $17,%cl
	movl %ecx,_flags
	jmp L79
	.align 4,0x90
L82:
	movl _flags,%eax
	andb $240,%al
	movl %eax,%ecx
	orb $18,%cl
	movl %ecx,_flags
	jmp L79
	.align 4,0x90
L83:
	movl _flags,%eax
	andb $240,%al
	movl %eax,%ecx
	orb $20,%cl
	movl %ecx,_flags
	jmp L79
	.align 4,0x90
L84:
	movl _flags,%eax
	andb $240,%al
	movl %eax,%ecx
	orb $24,%cl
	movl %ecx,_flags
	jmp L79
	.align 4,0x90
L85:
	orb $16,_flags
	jmp L79
	.align 4,0x90
L86:
	orb $32,_flags
	jmp L79
	.align 4,0x90
L87:
	pushl $_command
	call _strlen
	addl $4,%esp
	movl %eax,%eax
	testl %eax,%eax
	je L88
	pushl $_command
	call _atoi
	addl $4,%esp
	movl %eax,%eax
	cmpl $122,%eax
	jg L89
	pushl $_command
	call _atoi
	addl $4,%esp
	movl %eax,%eax
	jmp L90
	.align 4,0x90
L89:
	movl $122,%eax
L90:
	movl %eax,_RMARGIN
	jmp L91
	.align 4,0x90
L88:
	movl $132,%ecx
	subl _xpos,%ecx
	movl %ecx,_RMARGIN
	cmpl $122,_RMARGIN
	jle L92
	movl $122,_RMARGIN
L92:
L91:
	jmp L79
	.align 4,0x90
L93:
	pushl $_command
	call _strlen
	addl $4,%esp
	movl %eax,%eax
	testl %eax,%eax
	je L94
	pushl $_command
	call _atoi
	addl $4,%esp
	movl %eax,%eax
	cmpl $122,%eax
	jg L95
	pushl $_command
	call _atoi
	addl $4,%esp
	movl %eax,%eax
	jmp L96
	.align 4,0x90
L95:
	movl $122,%eax
L96:
	movl %eax,_LMARGIN
	jmp L97
	.align 4,0x90
L94:
	movl _xpos,%ecx
	movl %ecx,_LMARGIN
	cmpl $122,_LMARGIN
	jle L98
	movl $122,_LMARGIN
L98:
L97:
	jmp L79
	.align 4,0x90
L99:
	movl -4(%ebp),%eax
	incl %eax
	cmpb $0,(%eax)
	je L100
	leal -272(%ebp),%edi
	movl $LC4,%esi
	cld
	movl $64,%ecx
	rep
	movsl
	movl $132,%eax
	subl _RMARGIN,%eax
	movl %eax,%edx
	subl _LMARGIN,%edx
	movl %edx,%eax
	subl _xpos,%eax
	pushl %eax
	movl -4(%ebp),%eax
	incl %eax
	movsbl (%eax),%edx
	pushl %edx
	leal -272(%ebp),%eax
	pushl %eax
	call _memset
	addl $12,%esp
	movl -4(%ebp),%eax
	addl $2,%eax
	pushl %eax
	leal -272(%ebp),%eax
	pushl %eax
	pushl $LC5
	leal -1296(%ebp),%eax
	pushl %eax
	call _sprintf
	addl $16,%esp
	leal -1296(%ebp),%eax
	pushl %eax
	movl -4(%ebp),%eax
	incl %eax
	pushl %eax
	call _strcpy
	addl $8,%esp
L100:
	jmp L79
	.align 4,0x90
L102:
L79:
L78:
L77:
	movl $0,_comstate
L51:
	jmp L36
	.align 4,0x90
L104:
L36:
	movb _flags,%al
	andb $12,%al
	testb %al,%al
	je L106
	movb _flags,%al
	andb $16,%al
	testb %al,%al
	je L106
	pushl $32
	pushl $_prevline
	call _strrchr
	addl $8,%esp
	movl %eax,%eax
	movl %eax,-16(%ebp)
	movl $132,%eax
	subl _LMARGIN,%eax
	movl %eax,%edx
	subl _RMARGIN,%edx
	cmpl %edx,_xpos
	jl L107
	leal -1296(%ebp),%edi
	movl $LC4,%esi
	cld
	movl $64,%ecx
	rep
	movsl
	cmpl $0,-16(%ebp)
	je L108
	movl -16(%ebp),%eax
	movb $0,(%eax)
	movb _flags,%al
	andb $8,%al
	testb %al,%al
	je L109
	pushl $_prevline
	call _justify
	addl $4,%esp
L109:
	cmpl $0,_LMARGIN
	je L110
	movl _LMARGIN,%ecx
	pushl %ecx
	pushl $32
	leal -1296(%ebp),%eax
	pushl %eax
	call _memset
	addl $12,%esp
L110:
	pushl $_prevline
	leal -1296(%ebp),%eax
	pushl %eax
	pushl $LC6
	call _printf
	addl $12,%esp
	movl -4(%ebp),%ecx
	movl %ecx,-16(%ebp)
L111:
	movl -16(%ebp),%eax
	cmpl %eax,8(%ebp)
	ja L112
	movl -16(%ebp),%eax
	cmpb $32,(%eax)
	je L112
L113:
	decl -16(%ebp)
	jmp L111
	.align 4,0x90
L112:
	movl -16(%ebp),%eax
	cmpl %eax,_lastp
	je L114
	movl -16(%ebp),%ecx
	movl %ecx,-4(%ebp)
	movl -16(%ebp),%ecx
	movl %ecx,-4(%ebp)
L115:
	movl -4(%ebp),%eax
	cmpb $0,(%eax)
	je L116
	movl -4(%ebp),%eax
	cmpb $32,(%eax)
	jne L116
L117:
	incl -4(%ebp)
	jmp L115
	.align 4,0x90
L116:
	movl -4(%ebp),%eax
	cmpl %eax,8(%ebp)
	jae L118
	decl -4(%ebp)
L118:
	movl -4(%ebp),%ecx
	movl %ecx,_lastp
L114:
	jmp L119
	.align 4,0x90
L108:
	cmpl $0,_LMARGIN
	je L120
	movl _LMARGIN,%ecx
	pushl %ecx
	pushl $32
	leal -1296(%ebp),%eax
	pushl %eax
	call _memset
	addl $12,%esp
L120:
	pushl $_prevline
	leal -1296(%ebp),%eax
	pushl %eax
	pushl $LC6
	call _printf
	addl $12,%esp
L119:
	movl $0,_xpos
	movl $0,_plidx
L107:
	movb _flags,%al
	andb $32,%al
	testb %al,%al
	je L121
	andl $-17,_flags
L121:
L106:
	movb _flags,%al
	andb $16,%al
	testb %al,%al
	je L122
	movl _flags,%eax
	andb $239,%al
	testl %eax,%eax
	je L122
	cmpb $10,-5(%ebp)
	je L123
	cmpb $13,-5(%ebp)
	je L123
	jmp L122
	.align 4,0x90
L123:
	leal -1296(%ebp),%edi
	movl $LC4,%esi
	cld
	movl $64,%ecx
	rep
	movsl
	leal -1040(%ebp),%edi
	movl $LC4,%esi
	cld
	movl $64,%ecx
	rep
	movsl
	movl $132,%eax
	subl _LMARGIN,%eax
	movl %eax,%edx
	subl _RMARGIN,%edx
	movl %edx,%eax
	subl _xpos,%eax
	leal 1(%eax),%ecx
	movl %ecx,-12(%ebp)
	movb _flags,%al
	andb $2,%al
	testb %al,%al
	je L124
	movl -12(%ebp),%eax
	movl %eax,%edx
	shrl $31,%edx
	addl %edx,%eax
	movl %eax,%ecx
	sarl $1,%ecx
	movl %ecx,-12(%ebp)
L124:
	cmpl $0,-12(%ebp)
	jl L126
	cmpl $255,-12(%ebp)
	jg L126
	jmp L125
	.align 4,0x90
L126:
	movb $0,-1296(%ebp)
	jmp L127
	.align 4,0x90
L125:
	movl -12(%ebp),%ecx
	pushl %ecx
	pushl $32
	leal -1296(%ebp),%eax
	pushl %eax
	call _memset
	addl $12,%esp
L127:
	movl _plidx,%eax
	addl $_prevline,%eax
	movb $0,(%eax)
	cmpl $0,_LMARGIN
	je L128
	movl _LMARGIN,%ecx
	pushl %ecx
	pushl $32
	leal -1040(%ebp),%eax
	pushl %eax
	call _memset
	addl $12,%esp
L128:
	pushl $_prevline
	leal -1296(%ebp),%eax
	pushl %eax
	leal -1040(%ebp),%eax
	pushl %eax
	pushl $LC1
	call _printf
	addl $16,%esp
	movb _flags,%al
	andb $32,%al
	testb %al,%al
	je L129
	andl $-17,_flags
L129:
	movl $0,_xpos
	movl $0,_plidx
	jmp L130
	.align 4,0x90
L122:
	movb _flags,%al
	andb $16,%al
	testb %al,%al
	je L131
	movb _flags,%al
	andb $15,%al
	testb %al,%al
	jne L131
	cmpb $10,-5(%ebp)
	je L132
	cmpb $13,-5(%ebp)
	je L132
	jmp L131
	.align 4,0x90
L132:
	leal -1296(%ebp),%edi
	movl $LC4,%esi
	cld
	movl $64,%ecx
	rep
	movsl
	cmpl $0,_LMARGIN
	je L133
	movl _LMARGIN,%ecx
	pushl %ecx
	pushl $32
	leal -1296(%ebp),%eax
	pushl %eax
	call _memset
	addl $12,%esp
L133:
	pushl $_prevline
	leal -1296(%ebp),%eax
	pushl %eax
	pushl $LC5
	call _printf
	addl $12,%esp
	movb _flags,%al
	andb $32,%al
	testb %al,%al
	je L134
	andl $-17,_flags
L134:
	movl $0,_lastpos
	movb $-1,_lastc
	movl $0,_xpos
	movl $0,_plidx
	jmp L135
	.align 4,0x90
L131:
	movb _flags,%al
	andb $16,%al
	testb %al,%al
	jne L136
	cmpb $10,-5(%ebp)
	je L137
	cmpb $13,-5(%ebp)
	je L137
	jmp L136
	.align 4,0x90
L137:
	leal -1296(%ebp),%edi
	movl $LC4,%esi
	cld
	movl $64,%ecx
	rep
	movsl
	movb _flags,%al
	andb $32,%al
	testb %al,%al
	je L138
	cmpl $0,_LMARGIN
	je L139
	movl _LMARGIN,%ecx
	pushl %ecx
	pushl $32
	leal -1296(%ebp),%eax
	pushl %eax
	call _memset
	addl $12,%esp
L139:
L138:
	pushl $_prevline
	leal -1296(%ebp),%eax
	pushl %eax
	pushl $LC5
	call _printf
	addl $12,%esp
	movb _flags,%al
	andb $32,%al
	testb %al,%al
	je L140
	andl $-49,_flags
L140:
	movl $0,_lastpos
	movb $-1,_lastc
	movl $0,_xpos
	movl $0,_plidx
L136:
L135:
L130:
	incl -4(%ebp)
	jmp L30
	.align 4,0x90
L31:
L29:
	leal -1304(%ebp),%esp
	popl %esi
	popl %edi
	movl %ebp,%esp
	popl %ebp
	ret
LC7:
	.ascii "%s%s\12\12\12\0"
	.align 4
.globl _main
_main:
	pushl %ebp
	movl %esp,%ebp
	subl $1024,%esp
	pushl %edi
	pushl %esi
	call ___main
L142:
	pushl $__IO_stdin_
	call _feof
	addl $4,%esp
	movl %eax,%eax
	testl %eax,%eax
	jne L143
	pushl $__IO_stdin_
	pushl $1024
	leal -1024(%ebp),%eax
	pushl %eax
	call _fgets
	addl $12,%esp
	movl %eax,%eax
	testl %eax,%eax
	jne L144
	jmp L142
	.align 4,0x90
L144:
	leal -1024(%ebp),%eax
	pushl %eax
	call _format
	addl $4,%esp
	jmp L142
	.align 4,0x90
L143:
	leal -1024(%ebp),%edi
	movl $LC4,%esi
	cld
	movl $64,%ecx
	rep
	movsl
	movl _LMARGIN,%ecx
	pushl %ecx
	pushl $32
	leal -1024(%ebp),%eax
	pushl %eax
	call _memset
	addl $12,%esp
	movl _plidx,%eax
	addl $_prevline,%eax
	movb $0,(%eax)
	movb _flags,%al
	andb $12,%al
	testb %al,%al
	je L145
	pushl $_prevline
	leal -1024(%ebp),%eax
	pushl %eax
	pushl $LC7
	call _printf
	addl $12,%esp
L145:
L141:
	leal -1032(%ebp),%esp
	popl %esi
	popl %edi
	movl %ebp,%esp
	popl %ebp
	ret
.comm _prevline,1024
.comm _command,64
