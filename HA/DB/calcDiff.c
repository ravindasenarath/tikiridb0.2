// Calculates the number of calendar days between any two dates.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calcDiff.h"


int is_leap_year(int year) 
{
        if (year % 400 == 0) {
                return 1;
        } else if (year % 100 == 0) {
                return 0;
        } else if (year % 4 == 0) {
                return 1;
        } else {
                return 0;
        }
}

int days_in_month(int month, int year) 
{
        int leap = is_leap_year(year);
        /*                  J   F   M   A   M   J   J   A   S   O   N   D   */
        int days[2][13] = {{0,31,28,31,30,31,30,31,31,30,31,30,31},
                           {0,31,29,31,30,31,30,31,31,30,31,30,31}};
                                                      
        if (month < 0 || month > 12 || year < 1753)
                return -1;

	int count = days[leap][month];
        return count;
}

int date(int month1, int day1, int year1, int month2, int day2, int year2, int leap1, int leap2)
{
	int value = 1;
        for(;;)                     // Infinite loop (exited upon valid input)
        {
                int fail = 0;                
                if(month1 < 1 || month1 > 12)
                {
                        printf("Invalid entry for month.\n");
                        fail += 1;
                }
                if(day1 < 1 || day1 > 31)
                {
                        printf("Invalid entry for day.\n");
                        fail += 1;
                }
                if(year1 < 1)
                {
                        printf("Invalid entry for year.\n");
                        fail += 1;
                }
                if(days_in_month(month1, year1) == 30 && day1 > 30)
                {
                        printf("Invalid month and day combination.\n");
                        fail += 1;
                }
                if(month1 == 2)
                {
                        if(leap1 == 1 && day1 > 29)
                        {
                            printf("Invalid month and day combination.\n");
                            fail += 1;
                        }
                        else if(day1 > 28)
                        {
                            printf("Invalid month and day combination.\n");
                            fail += 1;
                        }
                }
                if(fail > 0)
                        continue;
                else
                        break;
        }

        for(;;)
        {
                int fail = 0;
                if(year1 == year2)
                {
                        if(month1 > month2)
                        {
                                //printf("Invalid entry.\n");
                                value = 0;
                                break;
                                fail += 1;
                        }
                        if(month1 == month2 && day1 > day2)
                        {
                                //printf("Invalid entry.\n");
                                value = 0;
                                break;
                                fail += 1;
                        }
                }
                if(month2 < 1 || month2 > 12)
                {
                        printf("Invalid entry for month.\n");
                        fail += 1;
                }
                if(day2 < 1 || day2 > 31)
                {
                        printf("Invalid entry for day.\n");
                        fail += 1;
                }
                if(year2 < 1)
                {
                        printf("Invalid entry for year.\n");
                        fail += 1;
                }
                if(days_in_month(month2, year2) == 30 && day2 > 30)
                {
                        printf("Invalid month and day combination.\n");
                        fail += 1;
                }
                if(month2 == 2)
                {
                        if(leap2 == 1 && day2 > 29)
                        {
                            printf("Invalid month and day combination.\n");
                            fail += 1;
                        }
                        else if(day2 > 28)
                        {
                            printf("Invalid month and day combination.\n");
                            fail += 1;
                        }
                }
                if(fail > 0)
                        continue;
                else
                        break;
        }
        return value;
}


int getDuration(char *first, char *second)
{
        int month1, day1, year1, month2, day2, year2, leap1, leap2;
        int duration = 0;
        char buff[10]; char var[4];   
        char buff1[10]; char var1[4];      
        char *p, *q; 
        
        strcpy(buff, first);
	p = strtok (buff,"-"); int i = 0;
	  
	while (p != NULL)
	{	
	    strcpy(var, p);  
	    if (i == 0){ year1 = atoi(var); i = 1;} 
	    else if (i == 1){ month1 = atoi(var); i = 2;} 
	    else if (i == 2){ day1 = atoi(var); i = 0;}
	    p = strtok (NULL, "-");
	}
        
        strcpy(buff1, second);
        q = strtok (buff1,"-"); 
        
        while (q != NULL)
	{	
	    strcpy(var1, q);  
	    if (i == 0){ year2 = atoi(var1); i = 1;} 
	    else if (i == 1){ month2 = atoi(var1); i = 2;} 
	    else if (i == 2){ day2 = atoi(var1); i = 0;}
	    q = strtok (NULL, "-");
	}
        
	int returnVal = date(month1, day1, year1, month2, day2, year2, leap1, leap2);

	if (returnVal == 1)
	{
		leap1 = is_leap_year(year1);
        	leap2 = is_leap_year(year2);
        	
		if(year1 == year2)
		{
		        int i, total;
		        if(month1 == month2)                            // Total days if month1 == month2
		        {
		                total = day2 - day1;
		                //printf("There are %d days between the two dates.\n", total);
		        }
		        else
		        {
		            total = days_in_month(month1, year1) - day1;
		            for(i = month1 + 1; i < month2; i++)        // Days remaining between dates (excluding last month)
		            {
		                total += days_in_month(i, year1);
		            }
		            total += day2;                              // Final sum of days between dates (including last month)
		            //printf("There are %d days between the two dates.\n", total);
		        }
		        duration = total;
		}
		else                                                    // If year1 != year2 ...
		{
		        int i, total, century1 = ((year1 / 100) + 1) * 100, falseleap = 0;
		        total = days_in_month(month1, year1) - day1;
		        for(i = month1 + 1; i <= 12; i++)               // Day remaining in first year
		        {
		            total += days_in_month(i, year1);
		        }
		        
		        for(i = 1; i < month2; i++)                     // Days remaining in final year (excluding last month)
		        {
		            total += days_in_month(i,year2);
		        }
		        int leapcount1 = year1 / 4;                     // Leap years prior to and including first year
		        int leapcount2 = year2 / 4;                     // Leap years prior to and NOT including final year
		        if(year2 % 4 == 0)
		                leapcount2 -= 1;
		                
		        int leaptotal = leapcount2 - leapcount1;        // Leap years between dates

		        for(i = century1; i < year2; i += 100)          // "False" leap years (divisible by 100 but not 400)
		        {
		                if((i % 400) != 0)
		                        falseleap += 1;
		        }

		        total += 365 * (year2 - year1 - 1) + day2 + leaptotal - falseleap;      // Final calculation
		        //printf("There are %d days between the two dates.\n", total);
		        duration = total;
		}
	}
        return duration;
}


/*

int main(int argc, char **argv)
{
	int a;
	char *first;
	char *second;
	first = "2012-03-12";
	second = "2014-01-08";
	a = getDuration(first, second);
	
	return 0;
}

*/
