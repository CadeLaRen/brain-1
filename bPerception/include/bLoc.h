/********* blob robotics 2014 *********
 *  title: bLoc.h
 *  brief: interface for localization
 * author: adrian jimenez-gonzalez
 * e-mail: blob.robotics@gmail.com
 **************************************/
#ifndef B_LOCALIZATION_H
#define B_LOCALIZATION_H

#include "bImu.h"
#include "bBaro.h"
#include "bTask.h"

namespace blob {

class Loc : public Task
{
  public:
    Loc ();

    void couple (Imu *imu);
    void couple (Baro *baro);
    
    void init   ();
    void update ();        // update acc, gyro and mag if coupled
    
    Vector3d<float> getVelFlu ();
    Vector3d<float> getVelEnu ();
    Vector3d<float> getPos ();
    
    void print (bool ln = true);
    
  protected:

    Imu  *_imu;
    Baro *_baro;
    
    Vector3d<float> _velFlu; /* body */
    Vector3d<float> _velEnu; /* nav  */
    Vector3d<float> _pos;
};

}

#endif /* B_Localization_H */
