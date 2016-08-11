// ArisUDPClient.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "ArisUDPClient.h"



#define MOT_NUM 19
#define FOR_NUM 6


aris::control::data_emitter::Data origin_data;
std::mutex data_lock;
WSASession Session;
UDPSocket Socket;



extern "C" __declspec(dllexport) void __stdcall GetExchangeData(struct ArisExchangeData *data)
{
	data_lock.lock();

	for (int i = 0;i < MOT_NUM;i++)
	{
		data->target_pos[i] = origin_data.motor_data.at(i).target_pos;
		data->target_vel[i] = origin_data.motor_data.at(i).target_vel;
		data->target_cur[i] = origin_data.motor_data.at(i).target_cur;

		data->feedback_pos[i] = origin_data.motor_data.at(i).feedback_pos;
		data->feedback_vel[i] = origin_data.motor_data.at(i).feedback_vel;
		data->feedback_cur[i] = origin_data.motor_data.at(i).feedback_cur;

		data->cmd[i] = origin_data.motor_data.at(i).cmd;
		data->mode[i] = origin_data.motor_data.at(i).mode;
		data->statusword[i] = origin_data.motor_data.at(i).statusword;
		data->ret[i] = origin_data.motor_data.at(i).ret;
	}

	for (int i = 0;i < FOR_NUM;i++)
	{
		data->Fx[i] = origin_data.force_data.at(i).Fx;
		data->Fy[i] = origin_data.force_data.at(i).Fy;
		data->Fz[i] = origin_data.force_data.at(i).Fz;

		data->Mx[i] = origin_data.force_data.at(i).Mx;
		data->My[i] = origin_data.force_data.at(i).My;
		data->Mz[i] = origin_data.force_data.at(i).Mz;
	}

	data->yaw = origin_data.imu_data.yaw;
	data->pitch = origin_data.imu_data.pitch;
	data->roll = origin_data.imu_data.roll;

	data_lock.unlock();
}



extern "C" __declspec(dllexport) void __stdcall StartUDPListener()
{
	aris::control::data_emitter::Data data_report;
	std::cout << "Start test UDP" << std::endl;
	

	char buffer[8192];
	Socket.Bind(6661);

	while (1)
	{
		int ret = Socket.RecvFrom(buffer, 8192);
		std::cout << "Get data size: " << ret << std::endl;
		if (data_lock.try_lock())
		{
			memcpy(&origin_data, buffer, sizeof(origin_data));
			data_lock.unlock();
		}




		//for debug
		std::cout << (int)origin_data.motor_data.at(0).cmd << std::endl;

		if (ret == 0 || ret == SOCKET_ERROR || ret<0)
		{
			std::cout << "UDP socket closed." << std::endl;
			break;
		}
	}
}

extern "C" __declspec(dllexport) void __stdcall CloseUDPListener()
{
	closesocket(Socket.sock);
}


