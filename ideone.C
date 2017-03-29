#include<stdio.h>
 
main()
{
        int hash[1000] = {0};
        int li = -1, mi = -1;  /* li is left of median, mi is right of median */
        int sum = 0, n = 0; /* n is number of integers */
        float  med = 0;
        int i, idx;
        int ar[] = {4, 15, 1, 3, 6, 20, 25, 5};
        int d = 0;
 
        while (d < 8)
        {
                //printf("Enter > ");
                //scanf("%d", &i);
                i = ar[d];
                d++;
                printf("Enter > %d\n", i);
                hash[i] = 1;
 
                sum += i;
                n++;
                printf("av %d, ", sum/n);
 
                if (li == -1 && mi == -1) {
                        med = li = mi = i;
                        printf("med %f\n", med);
                        continue;
                }
 
                if (med < i && mi < i) {
                        if (mi == med)
                                mi = i;
                        if (n%2 == 0) {
                                med = (med + mi)/2;
                                printf("med %f\n", med);
                                continue;
                        }
                        if ((int)med == med && hash[(int)med] == 1) {
                                li = med;
                        }
                        med = mi;
                        idx = mi+1;
                        while (idx <= 1000 && hash[idx] != 1) {
                                idx++;
                        }
                        if (idx == 1001) mi = med;
                        else mi = idx;
                        printf("med %f\n", med);
                        continue;
                }
 
                if (med < i && i < mi) {
                        if (n%2 == 0) {
                                li = med;
                                med = (med + i)/2;
                                mi = i;
                                printf("med %f\n", med);
                                continue;
                        }
                        li = med;
                        med = i;
                        printf("med %f\n", med);
                        continue;
                }
 
                if (med > i && i > li) {
                        if (n%2 == 0) {
                                mi = med;
                                med = (med + i)/2;
                                li = i;
                                printf("med %f\n", med);
                                continue;
                        }
                        mi = med;
                        med = i;
                        printf("med %f\n", med);
                        continue;
                }
                if (med > i && li > i) {
                        if (li == med)
                                li = i;
                        if (n%2 == 0) {
                                med = (li + med)/2;
                                printf("med %f\n", med);
                                continue;
                        }
                        if ((int)med == med && hash[(int)med] == 1) {
                                mi = med;
                        }
                        med = li;
                        idx = li-1;
                        while (idx >= 0 && hash[idx] != 1) {
                                idx--;
                        }
                        if (idx == -1) li = med;
                        else li = idx;
                        printf("med %f\n", med);
                        continue;
                }
                if (med == i) {
                        printf("med %f\n", med);
                        continue;
                }
        }
}
