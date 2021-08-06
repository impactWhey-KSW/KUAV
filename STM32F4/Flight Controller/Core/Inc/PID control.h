/**
 * PID control.c
 * @author ChrisP @ M-HIVE

 * This library source code is for cascade double loop pid control for STM32 Drone Development online course.
 *
 * Created by ChrisP(Wonyeob Park) @ M-HIVE Embedded Academy, July, 2020
 * Rev. 1.0
 *
 * Where to take the online course.
 * https://www.inflearn.com/course/STM32CubelDE-STM32F4%EB%93%9C%EB%A1%A0-%EA%B0%9C%EB%B0%9C (Korean language supported only)
 *
 * Where to buy MH-FC V2.2 STM32F4 Drone Flight Controller.
 * https://smartstore.naver.com/mhivestore/products/4961922335
 *
 * https://github.com/ChrisWonyeobPark
 * https://blog.naver.com/lbiith
 * https://cafe.naver.com/mhiveacademy
 * https://www.udemy.com/course/stm32-drone-programming/?referralCode=E24CB7B1CD9993855D45
 * https://www.inflearn.com/course/stm32cubelde-stm32f4%EB%93%9C%EB%A1%A0-%EA%B0%9C%EB%B0%9C
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PID_CONTROL_H
#define __PID_CONTROL_H
#ifdef __cplusplus
 extern "C" {
#endif


typedef struct _PIDSingle
{
	float kp;
	float ki;
	float kd;
	
	float reference;
	float meas_value;
	float meas_value_prev;
	float meas_rate;
	float meas_rate_prev;

	float error;
	float error_prev;
	float error_sum;
	float error_deriv;
	float error_deriv_filt;
	
	float p_result;
	float i_result;
	float d_result;
	
	float pid_result;
}PIDSingle;

typedef struct _PIDDouble
{
	PIDSingle in;
	PIDSingle out;
}PIDDouble;

typedef struct PDSingle_GPS
{
	float kp;
	float kd;

	float reference;
	float meas_value;
	float meas_value_prev;

	float total_average;
	float rotating_mem[40];
	unsigned char rotating_mem_location;

	float error;
	float error_prev;
	float error_sum;
	float error_deriv;
	float error_deriv_filt;

	float p_result;
	float d_result;

	float pd_result;
}PDSingle_GPS;


extern PIDDouble roll;
extern PIDDouble pitch;

extern PIDSingle altitude;
extern PDSingle_GPS lat;
extern PDSingle_GPS lon;

extern PIDSingle yaw_heading;
extern PIDSingle yaw_rate;


void Double_Roll_Pitch_PID_Calculation(PIDDouble* axis, float set_point_angle, float angle, float rate);
void Single_Yaw_Rate_PID_Calculation(PIDSingle* axis, float set_point, float value);
void Single_Yaw_Heading_PID_Calculation(PIDSingle* axis, float set_point, float angle, float rate);
void Reset_PID_Integrator(PIDSingle* axis);
void Reset_All_PID_Integrator(void);
void Single_Alt_PID_Calculation(PIDSingle* axis, float set_point_alt, float baro);

void Single_Altitude_PID_Calculation(PIDSingle* axis, float set_point_altitude, float current_altitude);
void Double_Altitude_PID_Calculation(PIDDouble* axis, float set_point_antitude, float anltitude);
void Single_GPS_PD_Calculation(PDSingle_GPS* axis, float set_point_gps, float gps);
void Double_GPS_PID_Calculation(PIDDouble* axis, float set_point_gps, float gps);

#ifdef __cplusplus
}
#endif
#endif /*__PID_CONTROL_H */
