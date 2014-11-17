/********* blob robotics 2014 *********
 *  title: bLoc.cpp
 *  brief: implementation of localization
 * author: adrian jimenez-gonzalez
 * e-mail: blob.robotics@gmail.com
 **************************************/
#include "bLoc.h" 

#if defined(__linux__)
  #include <iostream>
#endif // defined(__linux__)

blob::Loc::Loc ()
{
   _imu = 0;
   _baro = 0;

} // Loc::Loc

void blob::Loc::init()
{
  return;   
} // Loc::init

/* Add imu data */
void blob::Loc::couple (Imu *imu)
{
  if(imu)
    _imu = imu;

} // Loc::couple

/* Add baro data */
void blob::Loc::couple (Baro *baro)
{
  if(baro)
    _baro = baro;

} // Loc::couple

/* Refresh data from acc, gyro and mag */
void blob::Loc::update()
{
  static uint16_t _imuIndex = 0, _baroIndex = 0;
  
  blob::Vector3d<float> euler;
  
  _ready = _imu->isReady() & _baro->isReady();
  
  /* update imu */
  if (_imuIndex != _imu->getIndex()) {
    _imuIndex = _imu->getIndex();
    euler = _imu->getEuler();
  }
  
  /* update baro */
  if (_baroIndex != _baro->getIndex()) {
    _baroIndex = _baro->getIndex();
    _velEnu.z = (_baro->getHeight() - _pos.z)/_baro->getTimeLapse();
    _velFlu.z = _velEnu.z; 
    _pos.z = _baro->getHeight();
  }
  _index++;

#ifdef __DEBUG__
  print();
#endif

} // Loc::update


blob::Vector3d<float> blob::Loc::getVelFlu () {return _velFlu;}
blob::Vector3d<float> blob::Loc::getVelEnu () {return _velEnu;}
blob::Vector3d<float> blob::Loc::getPos () {return _pos;}
    
void blob::Loc::print(bool ln) {
#if defined(__AVR_ATmega32U4__)
  if (Serial) {
    Serial.print("blob::Loc - ");
    Serial.print(_velFlu.x); Serial.print(" ");
    Serial.print(_velFlu.y); Serial.print(" ");
    Serial.print(_velFlu.z); Serial.print(" ");
    Serial.print(_velEnu.x); Serial.print(" ");
    Serial.print(_velEnu.y); Serial.print(" ");
    Serial.print(_velEnu.z); Serial.print(" ");
    Serial.print(_pos.x); Serial.print(" ");
    Serial.print(_pos.y); Serial.print(" ");
    Serial.print(_pos.z); Serial.print(" ");
    Serial.print(_dt);    
    if (ln)
      Serial.println(" - ");
    else
      Serial.print(" - ");
  }
#endif
#if defined(__linux__)
  std::cout << "blob::Loc - " 
            << _velFlu.x << " " 
            << _velFlu.y << " " 
            << _velFlu.z << " " 
            << _velEnu.x << " " 
            << _velEnu.y << " " 
            << _velEnu.z << " "
            << _pos.x << " " 
            << _pos.y << " " 
            << _pos.z << " "
            << _dt << " - ";
  if (ln) std::cout << std::endl;       
#endif // defined(__linux__)
} // Loc::print
