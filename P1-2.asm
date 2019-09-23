# This program solves a match puzzle.
#
# Date:2/21/2019
# Your Name:Ugonna Nwankwo

.data
Reference:   .alloc 1				# allocate space for reference pattern
Candidates:  .alloc 8				# allocate space for puzzle candidates

.text
MPuzzle: addi	$1, $0, Reference	# set memory base
		swi	582			# create and display puzzle
        lw   	$4, Reference($0)
        
restart: addi 	$1, $0, 3
		addi 	$3, $0, 32
newC:   addi 	$3,$3,-4
		lw   	$2, Candidates($3)
		beq  	$4,$2,found           # check the candidates with vertical flip and basic reference
		bne		$3,$0,newC
in:     andi 	$5, $4, 0x000F        # get the last two colors of the reference
        srl  	$4,$4,4               # shift the reference to the right by four bits
        sll  	$5,$5,12              # shift the two colors to the left by twelve bits  
        or   	$4,$4,$5              # the last two colors now become the most significant bits of the reference
		addi 	$3, $0, 32
nextC:  addi 	$3,$3,-4
		lw   	$2, Candidates($3)
        beq  	$4,$2,found           # check the candidates with vertical flip and basic reference
		bne		$3,$0,nextC
        addi 	$1,$1,-1
        bne     $1,$0,in

        andi 	$6,$4,0x3030         # get the colors located at 1,5
        andi 	$5,$4,0xC0C0         # get the colors located at 0,4
        srl  	$5,$5,4              # shift the colors at 0,4 by 4 bits to the right
        or   	$6,$5,$6             # store the colors at 0,4 and 1,5 in $6
        andi 	$5,$4,0x0C0C         # get the colors located at 2,6
        sll  	$5,$5,4              # shift the colors at 2,6 to the left by 4 bits
        or   	$6,$5,$6             # store the colors at 2,6 in $6
        andi 	$5,$4,0x0300         # get the color located at three
        srl  	$5,$5,8              # shift the color at 3 by 8 bits to the right
        or   	$6,$5,$6             # place the color at 3 into $6
        andi 	$5,$4,0x0003         # get the color located at 7 
        sll  	$5,$5,8              # shift the color at 7 to the left 8 bits 
        or   	$4,$6,$5             # $4 is the verticallly flipped reference
        j 		restart
 		
found:   swi	583			# highlight match
		jr      $31			# return to operating system

