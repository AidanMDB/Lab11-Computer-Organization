#! /bin/bash

# Instructions go below, make sure to follow the format!
# make sure to include the semicolon at the end of the line.
# Do not add semicolon at the very end (creates an empty .bin file).
INSNS="lw x4, 4(x11);
sw x5, 0(x12);
beq x10, x0, _done;
add x10, x10, x11;
sub x11, x10, x11;
addi x4, x5, 5;
addi x4, x5, -6;
or x12, x11, x10;
ori x4, x5, 7;
and x6, x7, x11;
andi x12, x13, 7"   

# separate by semicolon and process each line
echo $INSNS | tr ";" "\n" | while read line
do
    echo
    echo ${line}
    # save instruction into file with harness code
    cat > start.S << EOF
.align 4
.globl _start
_start:
    ${line}
_done:
EOF
    # assemble and extract binary
    make raw.bin 1>/dev/null
    make extract.bin 1>/dev/null
    # move binary to a file with the instruction name
    # if it exists, add a number to the end or increment the number
    # cp extract.bin ${line%% *}.bin
    if [ -f ${line%% *}.bin ]
    then
        i=1
        while [ -f ${line%% *}${i}.bin ]
        do
            i=$((i+1))
        done
        mv extract.bin ${line%% *}${i}.bin
    else
        mv extract.bin ${line%% *}.bin
    fi
    rm -f raw.bin
    xxd ${line%% *}.bin
done
