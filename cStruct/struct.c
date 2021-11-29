/* CS270 
 *
 * Author: Aayush Lamichhane
 * Date:   2/12/2020
 */

#include "struct.h"
#include <stdio.h>
#include <stdlib.h>

/********** FUNCTION DEFINITIONS **********************************************/

void readStudentAndEnroll(Student **slot) {
    Student* s = malloc(sizeof(Student));

    scanf("%s", s->firstName);
    scanf("%f", &(s->qualityPoints));
    scanf("%i", &(s->numCredits));

    *slot = s;
}

void displayStudent(Student s) {
    float gpa = s.qualityPoints / s.numCredits;
    printf("%s, %.2f\n", s.firstName, gpa);
}