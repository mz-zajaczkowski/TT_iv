#include <cstdlib>
#include <iostream>
using namespace std;

struct angle
{
    uint16_t value;
    bool half;
    angle()
    {
        angle(0);
    }

    angle(int intVal)
    {
        value = std::abs(intVal) > 359 ? std::abs(intVal - 359) : std::abs(intVal);
        half = value/180;
    }
};

// X, Y - angle (0-360)
// return - one of (+/-30; +/- 90; +/- 135; 180)
int intersection_solution(int X, int Y)
{
    angle aAngle {X};
    angle lAngle {Y};

    int returnAngle = -1;
    int diff = aAngle.value - lAngle.value;
    bool turnLeft = false;
    if ((aAngle.value > lAngle.value && diff > 180)
            || (aAngle.value < lAngle.value && diff > -180))
        turnLeft = true;

    int localDiff = 0;
    if (aAngle.half != lAngle.half)
    {
        if(aAngle.value < lAngle.value)
        {
            localDiff = lAngle.value - 180 - aAngle.value;
        }
        else if(aAngle.value > lAngle.value)
        {
            localDiff = aAngle.value - 180 - lAngle.value;
        }

        if(localDiff < 0)
        {
            localDiff = -localDiff;
        }
        if (localDiff <= 15)
            returnAngle = 0;
        else if (localDiff > 15 && localDiff <= 60)
            returnAngle = -30;
        else if (localDiff > 60 && localDiff <= 113)
            returnAngle = -90;
        else if (localDiff > 113 && localDiff <= 157)
            returnAngle = -135;
        else
            returnAngle = 180;
    }
    else
    {
        if(aAngle.value < lAngle.value)
            localDiff = lAngle.value - aAngle.value;
        else
            localDiff = diff;

        if (localDiff < 23)
            returnAngle = 180;
        else if (localDiff >= 23 && localDiff < 67)
            returnAngle = -135;
        else if (localDiff >= 67 && localDiff < 120)
            returnAngle = -90;
        else if (localDiff >= 120 && localDiff < 157)
            returnAngle = -30;
        else
            returnAngle = 0;

    }

    if(!turnLeft && returnAngle != 0 && returnAngle != 180)
        returnAngle = -returnAngle;

    return returnAngle;
}
