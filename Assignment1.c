/* Program to compute floor areas and categories for apartments.

   Skeleton written by Alistair Moffat, ammoffat@unimelb.edu.au,
   April 2025, with the intention that it be modified by students
   to add functionality, as required by the assignment specification.

   Student Authorship Declaration:

   (1) I certify that except for the code provided in the initial skeleton
   file, the  program contained in this submission is completely my own
   individual work, except where explicitly noted by further comments that
   provide details otherwise.  I understand that work that has been developed
   by another student, or by me in collaboration with other students, or by
   non-students as a result of request, solicitation, or payment, may not be
   submitted for assessment in this subject.  I understand that submitting for
   assessment work developed by AI tools such as CharGPT, or that was
   developed in collaboration with other students or non-students, constitutes
   Academic Misconduct, and may be penalized by mark deductions, or by other
   penalties determined via the University of Melbourne Academic Honesty
   Policy, as described at https://academicintegrity.unimelb.edu.au.

   (2) I also certify that I have not provided a copy of this work in either
   softcopy or hardcopy or any other form to any other student, and nor will I
   do so until after the marks are released. I understand that providing my
   work to other students, regardless of my intention or any undertakings made
   to me by that other student, is also Academic Misconduct.

   (3) I further understand that providing a copy of the assignment
   specification to any form of code authoring or assignment tutoring service,
   or drawing the attention of others to such services and code that may have
   been made available via such a service, may be regarded as Student General
   Misconduct (interfering with the teaching activities of the University
   and/or inciting others to commit Academic Misconduct).  I understand that
   an allegation of Student General Misconduct may arise regardless of whether
   or not I personally make use of such solutions or sought benefit from such
   actions.

   Signed by: Tristan Leo Grichting (1616946)
   Dated:     20/04/2025

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/**********************************************************************/

/* some helpful constants, as a hint to get you started */

/* the number of different room types, plus one for simplicity */

#define NUMROOMTYPES 10

/* the numbers associated with the nine room types, these are not
   actually explicitly used in the program, but just for completeness */

#define UNUSED   0
#define HALLWAY  1
#define BEDROOM  2
#define LIVING   3
#define BATHROOM 4
#define KITCHEN  5
#define LAUNDRY  6
#define STORAGE  7
#define GARAGE   8
#define BALCONY  9

   /* overall room categories, and mapping from room types to categories */

#define NUMCATEGORIES 3
#define DRY     1
#define WET     2
#define UTILITY 3

/* fixed global arrays with initializers are permitted as a form of
   contants, can you see how you are intended to use this array?
*/

int roomcategories[NUMROOMTYPES] =
{ UNUSED, DRY, DRY, DRY, WET, WET, WET, UTILITY, UTILITY, UTILITY };

char* ROOM_TYPE_INT_TO_STRING[NUMROOMTYPES] =
{ "Unused", "Hallway", "Bedroom", "Living", "Bathroom",
    "Kitchen", "Laundry", "Storage", "Garage", "Balcony" };
/* and now add your own constants here */

#define MAX_ROOMS 99
#define MAX_APARTMENTS 999
#define MAX_SEGMENTS 9
#define ROOM_NO_ROW 0

// Structures
typedef struct {
    int type;
    int num;
    double xsize;
    double ysize;
} room_t;
/**********************************************************************/

/* put your function prototypes here */

/* plus two free gifts if you want them, to help with the sorting
*/

void	int_swap(int* p1, int* p2);
void	dbl_swap(double* p1, double* p2);
void    room_t_swap(room_t* p1, room_t* p2);
void    sort_room_t_array_by_room_num(room_t apartment[], int n);
void    sort_room_t_array_by_room_type(room_t apartment[], int n);
void    print_building_percentage_table(double area_percentages[][4],
    int num_of_apartments);
int     read_room_t_array(room_t apartment[], int maxvals);
int    read_write_apartment_area();

/**********************************************************************/

int
main(int argc, char* argv[]) {
    //define variables
    room_t apartment[MAX_ROOMS * MAX_SEGMENTS];
    int num_of_apartments = 0;
    double area_percentages[MAX_APARTMENTS][4]; //Change the 

    //find the apartment number
    num_of_apartments = read_write_apartment_area(apartment, area_percentages);

    // print summary
    printf("+-------+----------------+----------------+----------------+\n");
    printf("| Apart |    Dry areas   |    Wet areas   |  Utility areas |\n");
    printf("+-------+----------------+----------------+----------------+\n");
    print_building_percentage_table(area_percentages, num_of_apartments);

    /* you have to write the body of the main function, but don't
       make it too long, it should control the traffic flow and use
       functions to do the actual work
    */

    /* all done, time for a nap */
    printf("\n");
    printf("tadaa!\n");
    return EXIT_SUCCESS;
}

/**********************************************************************/

/* add all your functions here, one function per major (or minor!)
   task
*/

int read_write_apartment_area(room_t apartment[],
    double area_percentages[][4]) {
    int apartmentno = 0, num_of_apartments = 0, num_of_rooms = 0;
    double room_area = 0, total_area = 0;
    while (scanf("%d", &apartmentno) == 1) {

        //read apartment data
        num_of_rooms = read_room_t_array(apartment, MAX_ROOMS * MAX_SEGMENTS);

        //sorts apartment data into correct format
        sort_room_t_array_by_room_num(apartment, num_of_rooms);
        sort_room_t_array_by_room_type(apartment, num_of_rooms);

        //write output header
        printf("Apartment %d\n-------------\n", apartmentno);

        //for each of the rooms
        for (int i = 0; i < num_of_rooms; i++) {

            // if the cell has data
            if (apartment[i].type != 0) {

                //if the section has another section referencing the same room
                if ((apartment[i].type == apartment[i + 1].type) &&
                    (apartment[i].num == apartment[i + 1].num)) {

                    //calculate room area
                    room_area += apartment[i].xsize * apartment[i].ysize;

                    //print results -room area as that will be displayed 
                    //in final area
                    printf("%-8s %-2d %6.2lf  x  %-5.2lf   ---\n",
                        ROOM_TYPE_INT_TO_STRING[apartment[i].type],
                        apartment[i].num, apartment[i].xsize,
                        apartment[i].ysize);
                }
                else {
                    //calculate room area
                    room_area += apartment[i].xsize * apartment[i].ysize;

                    //add room area to the total area of the apartment
                    total_area += room_area;

                    //add the room area to the table of areas in the correct position
                    area_percentages[num_of_apartments]
                        [roomcategories[apartment[i].type]] += room_area;

                    //print results
                    printf("%-8s %-2d %6.2lf  x  %-5.2lf %6.2lf\n",
                        ROOM_TYPE_INT_TO_STRING[apartment[i].type],
                        apartment[i].num, apartment[i].xsize,
                        apartment[i].ysize, room_area);

                    room_area = 0;
                }
            }
        }
        printf("Total area %24.2lf meters^2\n", total_area);
        printf("\n");

        //format area_percentages
        area_percentages[num_of_apartments][ROOM_NO_ROW] = apartmentno;

        //reset variable
        total_area = 0;
        num_of_apartments += 1;
    }
    return num_of_apartments;
}

//This is a variation of the array reading program provided in class modified for my structure
int
read_room_t_array(room_t apartment[], int maxvals) {
    int n = 0;
    room_t nextroom;

    scanf("%d", &nextroom.type);
    while (nextroom.type != -1) {
        scanf("%d %lf %lf",
            &nextroom.num, &nextroom.xsize, &nextroom.ysize);
        if (n != maxvals) {
            apartment[n++] = nextroom;
        }
        scanf("%d", &nextroom.type);
    }
    return n;
}

//This is a variation of the insert sort algorithim shown in class for my structure
void
sort_room_t_array_by_room_num(room_t apartment[], int n) {
    int i, j;
    for (i = 1; i < n; i++) {
        for (j = i - 1; j >= 0 && apartment[j + 1].num < apartment[j].num; j--) {
            room_t_swap(&apartment[j], &apartment[j + 1]);
        }
    }
}

//This is a variation of the insert sort algorithim shown in class for my structure
void
sort_room_t_array_by_room_type(room_t apartment[], int n) {
    int i, j;
    for (i = 1; i < n; i++) {
        for (j = i - 1; j >= 0 && apartment[j + 1].type < apartment[j].type; j--) {
            room_t_swap(&apartment[j], &apartment[j + 1]);
        }
    }
}

void
print_building_percentage_table(double area_percentages[][4], int num_of_apartments) {
    //define variables
    double total_area = 0, wet_percent = 0, dry_percent = 0, utility_percent = 0;
    //for each entry in area_percentages
    for (int i = 0; i < num_of_apartments; i++) {
        //find the total area
        total_area = area_percentages[i][1] +
            area_percentages[i][2] + area_percentages[i][3];

        //find the percent of each area type to total area
        wet_percent = 100 * (area_percentages[i][WET] / total_area);
        dry_percent = 100 * (area_percentages[i][DRY] / total_area);
        utility_percent = 100 * (area_percentages[i][UTILITY] / total_area);

        //print lines
        printf("|  %03.0f  | %6.2lf  %4.1lf%%  | %6.2lf  %4.1lf%%  | %6.2lf  %4.1lf%%  |\n",
            area_percentages[i][ROOM_NO_ROW],
            area_percentages[i][WET], wet_percent,
            area_percentages[i][DRY], dry_percent,
            area_percentages[i][UTILITY], utility_percent);
    }
    printf("+-------+----------------+----------------+----------------+\n");
}

void
room_t_swap(room_t* p1, room_t* p2) {
    room_t tmp;
    tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}
/**********************************************************************/

/* this one taken directly from the textbook, and is here if you want it
*/

void
int_swap(int* p1, int* p2) {
    int tmp;
    tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

/**********************************************************************/

/* and this one is also provided as a "free gift", use it if you want
*/

void
dbl_swap(double* p1, double* p2) {
    double tmp;
    tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

/**********************************************************************/
//programming is fun