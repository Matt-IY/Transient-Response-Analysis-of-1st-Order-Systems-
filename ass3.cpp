#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

double findDifference(double, double);
void eulers(double);
void rungeKutta(double);

/***********************************************************
Function name:	main
Purpose:		main function
In parameters:	none
Out parameters:	0 for succesful execution
Version:		1.0
Author:			Matt Idone-York
************************************************************/

int main() {
	system("cls");
	int choice = 0;
	double stepSize = 0;
	while (choice != 3) {
		printf("\n");
		printf("Choose the method for solving the ODE:\n");
		do {
			printf("1. Euler's Method\n2. Runge - Kutta 4th Order Method\n3. Quit\n");
			fflush(stdin);
			scanf(" %d", &choice);
			if (choice == 3) {
				return 0;
			}
		} while (choice != 1 && choice != 2);
		do {
			printf("Choose step size \"h\" (0.8, 0.2, 0.05)\n");
			fflush(stdin);
			scanf(" %lf", &stepSize);
		} while (stepSize != 0.8 && stepSize != 0.2 && stepSize != 0.05);
		if (choice == 1) {
			eulers(stepSize);
		}
		else {
			rungeKutta(stepSize);
		}
		return 0;
	}
	return 0;
}
/***********************************************************
Function name:	eulers
Purpose:		calculates the eulers method
In parameters:	double h
Out parameters:	none
Version:		1.0
Author:			Matt Idone-York
************************************************************/

void eulers(double h) {
	double y = 3, x = 0, exact, error = 100;
	int loops = (int)(2.0 / h), i;
	printf("Time(s)\tExact Temp(C)\tEstimated Temp(C)\tPercentage Error(%%)\n");
	for (i = 0; i < loops; i++) {
		y += (h * (cos(4 * x) - 2 * y));
		x += h;
		exact = 0.1 * cos(4.0 * x) + 0.2 * sin(4.0 * x) + 2.9 * exp(-2.0 * x);
		error *= fabs((y - exact) / exact);
		printf("%0.1lf\t%0.3lf\t\t%0.3lf\t\t\t%0.2lf\n", x, exact, y, error);
		error = 100;
	}
}

/***********************************************************
Function name:	rungeKutta
Purpose:		Calculates the Runge-Kutta 4th method
In parameters:	double h
Out parameters:	none
Version:		1.0
Author:			Matt Idone-York
************************************************************/

void rungeKutta(double h) {
	double runge1 = h, runge2 = h, runge3 = h, runge4 = h, error = 100, y = 3, t = 0, exact;
	int loops = (int)(2.0 / h);
	printf("Time(s)\tExact Temp(C)\tEstimated Temp(C)\tPercentage Error(%%)\n");
	for (int i = 0; i < loops; i++) {
		runge1 *= findDifference(t, y);
		runge2 *= findDifference(t + 0.5 * h, y + 0.5 * runge1);
		runge3 *= findDifference(t + 0.5 * h, y + 0.5 * runge2);
		runge4 *= findDifference(t + h, y + runge3);
		y = y + (1.0 / 6.0) * (runge1 + 2 * runge2 + 2 * runge3 + runge4);
		t += h;
		exact = 0.1 * cos(4 * t) + 0.2 * sin(4 * t) + 2.9 * exp(-2 * t);
		error *= fabs((y - exact) / exact);
		printf("%0.1lf\t%0.3lf\t\t%0.3lf\t\t\t%0.2lf\n", t, exact, y, error);
		error = 100;
		runge1 = h;
		runge2 = h;
		runge3 = h;
		runge4 = h;
	}
}

/***********************************************************
Function name:	findDifference
Purpose:		Calculates the difference
In parameters:	double cm double y
Out parameters:	double difference
Version:		1.0
Author:			Matt Idone-York
************************************************************/

double findDifference(double x, double y) {
	double difference = cos(4 * x) - 2 * y;
	return difference;
}