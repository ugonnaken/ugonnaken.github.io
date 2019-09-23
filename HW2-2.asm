#     Color Matcher
#
# Your Name: Ugonna Nwankwo
#
# Date: 1/30/19
#
# This program finds the two closest colors in a eight color palette.
#
#  required output register usage:
#  $10: minimum total component difference
#  $11 and $12: memory addresses of the two closest colors

.data
Array:  .alloc  8               # allocate static space for packed color data

.text
ColorMatch:     addi  $1, $0, Array     # set memory base
                swi     500             # create color palette and update memory
                addi $2,$0, Array       # z = 0
                addi $27,$0,Array
                addi $3,$0,0            # bdiff = 0
                addi $4,$0,0            # gdiff = 0
                addi $5,$0,0            # rdiff = 0
                addi $23,$0,0           # diff = 0
                addi $24,$0,-1          # x = -1
                addi $25,$1,32          # i + 32
               ######################################################
                # Temporary: the following 3 instructions demo use of swi 581.
                # Be sure to replace them.
                addi  $10, $0, 600      # guess min component difference
                addi  $11, $1, 12       # guess an address
                addi  $12, $1, 4        # guess an address
                ######################################################

            L1: slt $9,$1,$25           # while(i < 7)
                beq  $9,$0,end 
                lbu $6, 0($1)           # blue
                lbu $7, 1($1)           # green
                lbu $8, 2($1)           # red
                
            L2: slt $13,$2,$25         # while(z < 7)
                beq  $13,$0,last 
                lbu $14, 0($2)          # next blue
                lbu $15, 1($2)          # next green
                lbu $16, 2($2)          # next red

                beq $1,$2,next
                sub $17,$6,$14          # blue - next blue
                sub $18,$7,$15          # green - next green
                sub $19,$8,$16          # red - next red

            Tot:  slti $20,$17,0          # if bdiff < 0
                  bne  $20,$0,posb        
                  slti $21,$18,0          # if gdiff < 0
                  bne  $21,$0,posg
                  slti $22,$19,0          # if rdiff < 0
                  bne  $22,$0,posr

                 addu $23,$17,$18
                 addu $23,$23,$19        # diff = rdiff + bdiff + gdiff

                 slt $26,$10,$23
                 bne $26,$0,next
                 addi $10,$23,0          # MinDelta = diff
                 addi  $11, $2, 0       # first color 
                 addi  $12, $1, 0       # second color

            next: addi $2,$2,4          # z++

                j L2

            last: addi $2,$0, Array     # z = 0
            
                  addi $1,$1,4          # i++

                j L1
            
            posb: mult $17,$24
                  mflo $17
                  j Tot

            posg: mult $18,$24
                  mflo $18
                  j Tot

            posr: mult $19,$24
                  mflo $19
                  j Tot


                                
             end: addi $1,$0,Array          # i=0      

                

                swi     581             # report answer (in $10, $11, $12)
                jr      $31             # return to caller

