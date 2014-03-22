#!/bin/bash - 
#===============================================================================
#
#          FILE:  check.sh
# 
#         USAGE:  ./check.sh 
# 
#   DESCRIPTION:  
# 
#       OPTIONS:  ---
#  REQUIREMENTS:  ---
#         NOTES:  ---
#        AUTHOR: Ming Chen (chenming), brianchenming@gmail.com
#       COMPANY: imeresearch@sogou
#       CREATED: 01/08/2012 11:23:46 PM EST
#      REVISION:  ---
#===============================================================================

set -o nounset                          # Treat unset variables as an error
set -o errexit                          # Stop script if command fail
export PATH="/bin:/usr/bin:$HOME/bin"             
IFS=$' \t\n'                            # Reset IFS
unset -f unalias                        # Make sure unalias is not a function
\unalias -a                             # Unset all aliases
ulimit -H -c 0 --                       # disable core dump
hash -r                                 # Clear the command path hash

tmp=`mktemp`
for i in 2 3 4 5 6 7 8 9 A B C; do
    cat "C.$i.dat" | ./ferry > $i.out
    read out < $i.out
    read dif < C.$i.dif
    if [ "$out" != "$dif" ]; then
        echo "wrong for testcase $i (number mismatch)"
    fi
    awk -v outfile="$i.out" '
        BEGIN {
            for (n=1; getline < outfile; ++n) {
                onport[n] = $1;
            }
            port = 0;
            starboard = 0;
        } (NR < n) {
            if (NR == 1) {
                limit = 100*$1;
            } else {
                if (onport[NR] == "port") {
                    port += $1;
                } else if (onport[NR] == "starboard") {
                    starboard += $1;
                } else {
                    print outfile, "wrong line: ", $0, NR;
                    print port, starboard, limit;
                    exit 1;
                }
                if (port > limit || starboard > limit) {
                    print outfile, "out limit";
                    print port, starboard, limit;
                    exit 1;
                }
            }
        } END {
            print port, starboard, limit;
        }' "C.$i.dat"
done
