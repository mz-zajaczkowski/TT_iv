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
        cout << "quarter: " << static_cast<unsigned int>(quarter) << endl;
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
    if (approachingAngle.toLeft(leavingAngle))
        cout << "turn left" << endl;
    else
        cout << "turn right\n";
    return -1;
}
