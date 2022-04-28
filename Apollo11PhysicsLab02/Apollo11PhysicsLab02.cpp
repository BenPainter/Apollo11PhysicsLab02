/*************************************************************
 * 1. Name:
 *      Star Balls, Ben Painter
 * 2. Assignment Name:
 *      Practice 02: Physics simulator
 * 3. Assignment Description:
 *      Compute how the Apollo lander will move across the screen
 * 4. What was the hardest part? Be as specific as possible.
 *      The hardest part was understanding what formulas to use for the
 *      different calculations. It was great to have the formulas provided
 *      but with our limited knowledge of the differences between acceleration,
 *      velocity, and thrust, we were trying to figure out which formulas to
 *      to use and what exactly we were doing with each of the calculations.
 *      If there was a miscalculation we weren't exactly sure if the bug
 *      was in the formula, the way we putting the formula into C++, or if
 *      we just didn't understand what we were trying to accomplish exactly.
 * 5. How long did it take for you to complete the assignment?
 *      -total time in hours: 4 hours
 **************************************************************/


#define _USE_MATH_DEFINES //Pi and Sqrt

#include <cmath> // Pi and Sqrt
#include <math.h> // Sin and Cos
#include <iostream>  // for CIN and COUT
#include <string> // for strings
using namespace std;

#define WEIGHT 15103.00   // Weight in KG
#define GRAVITY -1.625    // Vertical acceleration due to gravity, in m/s^2
#define THRUST 45000.00   // Thrust of main engine, in Newtons (kg m/s^2)

/***************************************************
 * COMPUTE DISTANCE
 * Apply inertia to compute a new position using the distance equation.
 * The equation is:
 *     s = s + v t + 1/2 a t^2
 * INPUT
 *     s : original position, in meters
 *     v : velocity, in meters/second
 *     a : acceleration, in meters/second^2
 *     t : time, in seconds
 * OUTPUT
 *     s : new position, in meters
 **************************************************/
double computeDistance(double s, double v, double a, double t)
{
    // returns the new position
    return s + (v * t) + (.5 * a * (t * t));
}

/**************************************************
* COMPUTE ACCELERATION
* Find the acceleration given a thrust and mass.
* This will be done using Newton's second law of motion:
*     f = m * a
* INPUT
*     f : force, in Newtons (kg * m / s^2)
*     m : mass, in kilograms
* OUTPUT
*     a : acceleration, in meters/second^2
***************************************************/
double computeAcceleration(double force, double mass)
{
    // Force is THRUST 
    // Mass is WEIGHT
    // returns the acceleration
    return force / mass;
}

/***********************************************
 * COMPUTE VELOCITY
 * Starting with a given velocity, find the new
 * velocity once acceleration is applied. This is
 * called the Kinematics equation. The
 * equation is:
 *     v = v + a t
 * INPUT
 *     v : velocity, in meters/second
 *     a : acceleration, in meters/second^2
 *     t : time, in seconds
 * OUTPUT
 *     v : new velocity, in meters/second
 ***********************************************/
double computeVelocity(double v, double a, double t)
{
    // Calcaute x component of veolcity
    return v + (a * t);
}


/***********************************************
 * COMPUTE VERTICAL COMPONENT
 * Find the vertical component of a velocity or acceleration.
 * The equation is:
 *     cos(a) = y / total
 * This can be expressed graphically:
 *      x
 *    +-----
 *    |   /
 *  y |  / total
 *    |a/
 *    |/
 * INPUT
 *     a : angle, in radians
 *     total : total velocity or acceleration
 * OUTPUT
 *     y : the vertical component of the total
 ***********************************************/
double computeVerticalComp(double a, double total)
{
    // Compute y componenent of acceleration
    return (cos(a) * total);
}

/***********************************************
* COMPUTE HORIZONTAL COMPONENT
* Find the horizontal component of a velocity or acceleration.
* The equation is:
*     sin(a) = x / total
* This can be expressed graphically:
*      x
*    +-----
*    |   /
*  y |  / total
*    |a/
*    |/
* INPUT
*     a : angle, in radians
*     total : total velocity or acceleration
* OUTPUT
*     x : the vertical component of the total
***********************************************/
double computeHorizontalComp(double a, double total)
{
    // Compute x componenent of acceleration
    // a is the radians from the degreesToRadians
    // total is the output of computeAcceleration
    return sin(a) * total;
}

/************************************************
* COMPUTE TOTAL COMPONENT
* Given the horizontal and vertical components of
* something (velocity or acceleration), determine
* the total component. To do this, use the Pythagorean Theorem:
*    x^2 + y^2 = t^2
* where:
*      x
*    +-----
*    |   /
*  y |  / total
*    | /
*    |/
* INPUT
*    x : horizontal component
*    y : vertical component
* OUTPUT
*    total : total component
***********************************************/
double computeTotalComp(double x, double y)
{
    // returns the total component 
    return sqrt((x * x) + (y * y));
}


/*************************************************
* RADIANS FROM DEGREES
* Convert degrees to radians:
*     radians / 2pi = degrees / 360
* INPUT
*     d : degrees from 0 to 360
* OUTPUT
*     r : radians from 0 to 2pi
**************************************************/
double radiansToDegrees(double d)
{
    // returns the convertion of degrees to radians
    return (d / 360.00) * (2.00 * M_PI);
}

/**************************************************
* PROMPT
* A generic function to prompt the user for a double
* INPUT
*      message : the message to display to the user
* OUTPUT
*      response : the user's response
***************************************************/
double prompt(const char* message)
{
    double response;
    cout << message;
    cin >> response;

    // returns the response from the user
    return response;
}

/****************************************************************
* MAIN
* Prompt for input, compute new position, and display output
****************************************************************/
int main()
{
    // Prompt for input and variables to be computed
    double dx = prompt("What is your horizontal velocity (m/s)? ");
    double dy = prompt("What is your vertical velocity (m/s)? ");
    double y = prompt("What is your altitude (m)? ");
    double x = prompt("What is your position (m)? ");
    double aDegrees = prompt("What is the angle of the LM where 0 is up (degrees)? ");
    double t = prompt("What is the time interval (s)? ");

    // Loop through to display the New Position, New Velocity, and the Total Velocity five times.
    for (int i = 0; i < 5; i++)
    {
        double aRadians = radiansToDegrees(aDegrees); // Angle in radians
        double totalThrust = computeAcceleration(THRUST, WEIGHT);  // Calculate the acceleration.
        double ddxThrust = computeHorizontalComp(radiansToDegrees(aDegrees), totalThrust); // Horizontal acceleration due to thrust
        double ddyThrust = computeVerticalComp(radiansToDegrees(aDegrees), totalThrust); // Vertical acceleration due to thrust
        double ddx = ddxThrust; // Total horizontal acceleration
        double ddy = ddyThrust + GRAVITY; // Total vertical acceleration
        dx = computeVelocity(dx, ddx, t); // 
        dy = computeVelocity(dy, ddy, t);
        double v = computeTotalComp(dx, dy); // Total velocity
        x = computeDistance(x, dx, ddx, t);
        y = computeDistance(y, dy, ddy, t);

        // Output
        cout.setf(ios::fixed | ios::showpoint);
        cout.precision(2);
        cout << "\tNew position:   (" << x << ", " << y << ")m\n";
        cout << "\tNew velocity:   (" << dx << ", " << dy << ")m/s\n";
        cout << "\tTotal velocity:  " << v << "m/s\n\n";
    }

    return 0;
}