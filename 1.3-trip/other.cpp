/*
 * ===========================================================================
 *
 *       Filename:  other.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/09/2011 08:56:57 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ming Chen (chenming), chenming@sohu-rd.com
 *        Company:  imeresearch@sogou
 *
 * ===========================================================================
 */

#include<stdio.h>

#define size 1003

int main(void)
{
    long n,i;
    double avg,sum,sumup,sumdown,out,data[size];

    while(scanf("%ld",&n)==1)
    {
        if(!n)
            break;
        sum = 0.0;
        for(i=0;i<n;i++)
        {
            scanf("%lf",&data[i]);
            sum += data[i];
        }

        avg = sum/n;
        avg = (long)(avg * 100 + 0.5);
        avg /= 100;

        sumup = sumdown = 0.0;

        for(i=0;i<n;i++)
        {
            if(data[i] < avg)
                sumdown += (avg - data[i]);
            else
                sumup += (data[i] - avg);

        }

        if(sumup<sumdown)
            out = sumup;
        else
            out = sumdown;
        printf("$%.2lf\n",out);
    }//end case while

    return 0;
}

