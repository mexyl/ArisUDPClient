#pragma once
#include <aris.h>
//#include "json.hpp"
#include "Network.h"
#include <mutex>

#include <Windows.h>

struct ArisExchangeData
{
	/* Motor Data */
	int32_t target_pos[aris::control::data_emitter::Data::MOT_NUM];
	int32_t feedback_pos[aris::control::data_emitter::Data::MOT_NUM];
	int32_t target_vel[aris::control::data_emitter::Data::MOT_NUM];
	int32_t feedback_vel[aris::control::data_emitter::Data::MOT_NUM];
	int16_t target_cur[aris::control::data_emitter::Data::MOT_NUM];
	int16_t feedback_cur[aris::control::data_emitter::Data::MOT_NUM];
	UINT8 cmd[aris::control::data_emitter::Data::MOT_NUM];
	UINT8 mode[aris::control::data_emitter::Data::MOT_NUM];
	uint16_t statusword[aris::control::data_emitter::Data::MOT_NUM];
	int16_t ret[aris::control::data_emitter::Data::MOT_NUM];
	/* Force Sensor Data */
	float Fx[aris::control::data_emitter::Data::FOR_NUM];
	float Fy[aris::control::data_emitter::Data::FOR_NUM];
	float Fz[aris::control::data_emitter::Data::FOR_NUM];
	float Mx[aris::control::data_emitter::Data::FOR_NUM];
	float My[aris::control::data_emitter::Data::FOR_NUM];
	float Mz[aris::control::data_emitter::Data::FOR_NUM];
	/* IMU Data */
	float yaw;
	float pitch;
	float roll;

	int32_t count;
};

extern "C" __declspec(dllexport) void __stdcall GetExchangeData(struct ArisExchangeData *data);
extern "C" __declspec(dllexport) void __stdcall StartUDPListener();
extern "C" __declspec(dllexport) void __stdcall CloseUDPListener();
