  # labwork.S
  # Written 2015 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1 2015-2016.
  # The macros PUSH and POP are in the public domain.
  # Code added and edited by E Mickols

.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm

  # You can add your own code here
.globl delay, time2string, enable_interrupt	# l�ter kompilatorn veta att dessa labels har fri �tkomst fr�n �vriga filer

enable_interrupt:
	ei
	jr	$ra
	nop

hexasc:
        andi    $a1,$a1,0xf     # spara bara 4 minst signifikanta bits

	move	$v0,$a1		# copy from a1 to v0

	li      $t1, 1          # skapa loop-kriterium

	slti    $t0, $v0, 10    # test f�r loop. 0-9 blir true

	bne     $t0, $t1, bok   # loop. �r argumentet mindre �n 10? is�fall forts�tt, annars branch till 'bok'stav
	nop
        addi    $v0, $a1, 0x30  # l�gg till f�r ASCII-kod

        jr      $ra             # tillbaks med reutrv�rde i $v0
        nop

bok:
        addi    $v0, $a1, 0x37  # addera v�rde f�r stora bokst�ver ASCII

        jr       $ra
        nop


delay:
        add     $t0, $0, $0     # villkorsvariabel till while-loopen
        addi    $t2, $0, 13500	# justerar for-loopens villkor efter inkommande argument

while:
        addi    $t1, $0, 0	# villkorsvariabel till for-loopen
        ble     $a0, $t0, slut	# avsluta loop om $a0 <= 0
        nop
        addi    $a0, $a0, -1	# minska $a0 inkrementellt

for:
        beq     $t1, $t2, while	# hoppa tillbaks till while-loopen om for-loopens villkor �r uppfyllt
        nop
        addi    $t1, $t1, 1	# �ka inkrementellt vid varje instans av 'for'
        j	for
        nop

slut:
	jr	$ra
	nop

time2string:
       PUSH     $ra            	# pusha register
       PUSH     $a0            	# pusha registeradress d�r bytes skall sparas
       move     $t0, $a1       	# l�gg hexv�rde i tempor�r
       addi     $t3, $0, 0x3a  	# ASCII ':'
       addi     $t6, $0, 0x00  	# ASCII 'NUL'
       addi	$t4, $0, 0
       # FIXME
       addi	$t5, $0, 0x05	# NUL pos.

       PUSH     $a1            	# pusha hexv�rde/argument inf�r jal
       PUSH     $t0            	# pusha tempor�rsparat v�rde
       jal      hexasc
       nop
       POP      $t0            	# �terst�ll temp
       POP      $a1         	# �terst�ll hexargument
       beq	$v0, 0x32, two
       nop
       sb       $v0, 0x04($a0)	# spara i l�mplig byte

return_two:

       PUSH     $a1  		# upprepa proceduren
       PUSH     $t0
       srl      $a1, $a1, 4	# shiftar hexv�rdets bits f�r att komma �t n�sta byte att skicka till hexasc
       jal      hexasc
       nop
       POP      $t0
       POP      $a1
       sb       $v0, 0x03($a0)

       sb       $t3, 0x02($a0)
       PUSH     $a1
       PUSH     $t0
       srl      $a1, $a1, 8
       jal      hexasc
       nop
       POP      $t0
       POP      $a1
       sb       $v0, 0x01($a0)

       PUSH     $a1
       PUSH     $t0
       srl      $a1, $a1, 12
       jal      hexasc
       nop
       POP      $t0
       POP      $a1
       sb       $v0, 0x00($a0)
       beq	$t4, 1, twonull
       nop
       sb       $t6, 0x05($a0)
       j	sam
       nop
twonull:
	sb	$t6, 0x07($a0)

sam:
       POP      $a0        	# �terst�ll registeradress
       POP      $ra        	# �terst�ll returadress
       jr       $ra          	# hoppa tillbaks
       nop

two:
	addi 	$v0, $0, 0
	addi 	$v0, $v0, 0x54
	sb	$v0, 0x04($a0)
	addi	$v0, $0, 0x57
	sb	$v0, 0x05($a0)
	addi	$v0, $0, 0x4f
	sb	$v0, 0x06($a0)
	addi	$t4, $0, 1
	j	return_two
	nop
