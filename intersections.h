#include <cstdlib>
#include <iostream>
using namespace std;

struct angle
{
    uint16_t value;
    uint8_t quarter;
    bool half;
    angle()
    {
        angle(0);
    }

    angle(int intVal)
    {
        value = std::abs(intVal) > 360 ? std::abs(intVal)/360 : std::abs(intVal);
        half = value/180;
        quarter = value/90;
//        cout << "quarter: " << static_cast<unsigned int>(quarter) << endl;
    }

    bool toLeft(const angle& other)
    {
        cout << "this.half: " << boolalpha << half << endl;
        cout << "other.half: " << boolalpha << other.half << endl;
        if (half == other.half)
            return (value - other.value) > 0;
        else
          if (half && !other.half)
              return (value - 180 - other.value) > 0;
          else
              return (value + 180 - other.value) > 0;
    }
};


int turnAngle(const angle& approachingAngle, const angle& leavingAngle)
{
    int returnAngle = 0;
    int diff = 0;

    // 90 to 180
    if (approachingAngle.half == leavingAngle.half)
    {
        if (approachingAngle.value == leavingAngle.value)
            return 180;
        else
            diff = approachingAngle.value - leavingAngle.value;
            bool turnLeft = diff > 0;
            if (diff == 90 || diff == -90)
                return diff;
            else
                returnAngle = turnLeft ? 135 : -135;
    }
    else
    {
      if (approachingAngle.half && !leavingAngle.half)
      {
          diff = (approachingAngle.value - 180 - leavingAngle.value);
      }
      else
      {
          diff = (approachingAngle.value + 180 - leavingAngle.value);
          returnAngle = 0;
      }
    }
    return returnAngle;
}

// X, Y - angle (0-360)
// return - one of (+/-30; +/- 90; +/- 135; 180)
int intersection_solution(int X, int Y)
{
    angle approachingAngle {X};
    angle leavingAngle {Y};

    int diff = approachingAngle.value - leavingAngle.value;
    bool turnLeft = false;
    if ((X > Y && diff > 180) || (X < Y && diff > -180))
        turnLeft = true;

    if ((X > Y) && (approachingAngle.half != leavingAngle.half) && turnLeft)
    {
        int localDiff = X - 180 - Y;
        if (localDiff <= 15)
            return 0;
        else if (localDiff > 15 && localDiff <= 60)
            return -30;
        else if (localDiff > 60 && localDiff <= 113)
            return -90;
        else if (localDiff > 113 && localDiff <= 157)
            return -135;
        else
            return 180;
    }
    else if ((X > Y) && (approachingAngle.half != leavingAngle.half) && !turnLeft)
    {
        int localDiff = X - 180 - Y;
        if (localDiff >= -15 && localDiff <= 0)
            return 0;
        else if (localDiff < -15 && localDiff >= -60)
            return 30;
        else if (localDiff < -60 && localDiff >= -113)
            return 90;
        else if (localDiff < -113 && localDiff >= -157)
            return 135;
        else
            return 180;

    }
    else if ((X > Y) && (approachingAngle.half == leavingAngle.half))
    {// turning right
        int localDiff = diff;
        if (localDiff < 23)
            return 180;
        else if (localDiff >= 23 && localDiff < 67)
            return 135;
        else if (localDiff >= 67 && localDiff < 120)
            return 90;
        else if (localDiff >= 120 && localDiff < 157)
            return 30;
        else
            return 0;
    }
    else if ((X < Y) && (approachingAngle.half == leavingAngle.half))
    {// turning left
        int localDiff = Y - X;
        if (localDiff < 23)
            return 180;
        else if (localDiff >= 23 && localDiff < 67)
            return -135;
        else if (localDiff >= 67 && localDiff < 120)
            return -90;
        else if (localDiff >= 120 && localDiff < 157)
            return -30;
        else
            return 0;
    }
    else if ((X<Y) && (approachingAngle.half != leavingAngle.half) && turnLeft)
    {
        int localDiff = Y - 180 - X;
        if (localDiff <= 15)
            return 0;
        else if (localDiff > 15 && localDiff <= 60)
            return -30;
        else if (localDiff > 60 && localDiff <= 113)
            return -90;
        else if (localDiff > 113 && localDiff <= 157)
            return -135;
        else
            return 180;
    }
    else if ((X<Y) && (approachingAngle.half != leavingAngle.half) && !turnLeft)
    {
        int localDiff = Y - 180 - X;
        if (localDiff <= 15)
            return 0;
        else if (localDiff > 15 && localDiff <= 60)
            return 30;
        else if (localDiff > 60 && localDiff <= 113)
            return 90;
        else if (localDiff > 113 && localDiff <= 157)
            return 135;
        else
            return 180;
    }
    return -1;
}
