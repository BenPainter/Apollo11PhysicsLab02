/*************************************************************
 * 1. Name:
 *      Ben Painter, Star Balls
 * 2. Assignment Name:
 *      Lab 02: Apollo 11
 * 3. Assignment Description:
 *      Simulate the Apollo 11 landing
 * 4. What was the hardest part? Be as specific as possible.
 *      Because of the assignment we did figuring out the computations we 
 *      would need for the lunar module it made this assignment easier. The 
 *      hardest part was figuring out the best way to do the output for ten
 *      seconds with a prompt to the user after the fifth second to ask the
 *      user for another angle.
 * 5. How long did it take for you to complete the assignment?
 *      The assignment took us about an hour to an hour and a half to
 *      complete. 
 *****************************************************************/

#define _USE_MATH_DEFINES //Pi and Sqrt

#include <cmath> // Pi and Sqrt
#include <math.h> // Sin and Cos
#include <iostream>  // for CIN and COUT
#include <string> // for strings
#include <iomanip> // for setw
#include <assert.h> // for asserts
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
   // Mass cannot be zero since you're dividing by it.
   assert(mass != 0.0);
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
   double y =  prompt("What is your altitude (m)? ");
   double x =  0.0;
   double aDegrees = prompt("What is the angle of the LM where 0 is up (degrees)? ");
   double t = 1;
   cout << "\nFor the next 5 seconds with the main engine on, "
        << "the position of the lander is : \n\n";

   // Loop through to display the New Position, New Velocity, and the Total 
   // Velocity ten times.
   for (int i = 0; i < 10; i++)
   {
      // Allows user to change angle after 5 seconds
      if (i == 5)
      {
         cout << endl;
         aDegrees = prompt("What is the angle of the LM where 0 is up (degrees)? ");
         cout << "\nFor the next 5 seconds with the main engine on, "
              << "the position of the lander is : \n\n";
      }
       // Call the functions needed to compute Position, Velocity, Speed, Angle
       // Angle in radians
       double aRadians = radiansToDegrees(aDegrees); 

       // Calculate the acceleration.
       double totalThrust = computeAcceleration(THRUST, WEIGHT); 

       // Horizontal acceleration due to thrust
       double ddxThrust = computeHorizontalComp(radiansToDegrees(aDegrees), totalThrust); 

       // Vertical acceleration due to thrust
       double ddyThrust = computeVerticalComp(radiansToDegrees(aDegrees), totalThrust);

       // Total horizontal acceleration
       double ddx = ddxThrust; 

       // Total vertical acceleration
       double ddy = ddyThrust + GRAVITY; 
       dx = computeVelocity(dx, ddx, t); 
       dy = computeVelocity(dy, ddy, t);

       // Total velocity
       double v = computeTotalComp(dx, dy); 
       x = computeDistance(x, dx, ddx, t);
       y = computeDistance(y, dy, ddy, t);

       // Formatting the output for Position, Velocity, Speed, Angle
       cout.setf(ios::fixed | ios::showpoint);
       cout.precision(2);
       cout << setw(2) << i + 1 << "s - x, y:(" << x << ", " << y 
            << ")m  dx, dy: (" << dx << ", " << dy << ")m/s  speed: " 
            << v << "m/s  angle: " << aDegrees << "deg" << endl;


   }

   return 0;
}