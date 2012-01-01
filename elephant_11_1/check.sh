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
#       CREATED: 12/31/2011 12:54:59 AM EST
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

insize="$1"
tmp=`mktemp`

for ((j = 0; j < 10; ++j)); do 
    cat /dev/null > 'tin'
    for ((i = 0; i < $insize; ++i)); do
        echo $RANDOM $RANDOM >> 'tin';
    done

    cat 'tin' | ./elephant > 'tout'
    awk 'BEGIN {
            for(i=1; getline < "tin"; ++i) {
                wt[i] = $1;
                iq[i] = $2;
            }

        } (NR > 1) {
            if (NR > 2 && (wt[$1] <= cur_wt || iq[$1] >= cur_iq)) {
                exit 1;
            }
            cur_wt = wt[$1];
            cur_iq = iq[$1];
            print $1, cur_wt, cur_iq;
        }' "tout" > "tres"
done
