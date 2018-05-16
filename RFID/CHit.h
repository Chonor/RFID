#pragma once
#include <string>
using std::string;
class Hits
{
public:
	Hits() {
		error_hit[0] = "IFD_OK 执行成功";
		error_hit[1] = "IFD_ICC_TypeError 卡片类型不对";
		error_hit[2] = "IFD_ICC_NoExist 无卡";
		error_hit[3] = "IFD_ICC_NoPower 有卡未上电";
		error_hit[4] = "IFD_ICC_NoResponse 卡片无应答";
		error_hit[5] = "IFD_ICC_BCCError BCC校验错误";
		error_hit[6] = "IFD_ICC_TimeOut 接收超时";
		error_hit[7] = "IFD_ICC_RunFail 执行失败";
		error_hit[8] = "IFD_ICC_SiteFail 卡片位置错误";
		error_hit[9] = "IFD_ICC_SetFail 设置失败";
		error_hit[10] = "IFD_NoSlot 无卡";
		error_hit[11] = "IFD_ConnectError 读卡器连接错";
		error_hit[12] = "IFD_UnConnected 未建立连接(没有执行打开设备函数)";
		error_hit[13] = "IFD_BadCommand (动态库)不支持该命令";
		error_hit[14] = "IFD_CheckSumError 信息校验和出错";
		error_hit[15] = "IFD_ICC_PowerFail 卡片上电失败";
		error_hit[16] = "IFD_ICC_ResetFail 卡片复位失败";
		error_hit[17] = "IFD_ICC_PowerOffFail 卡片下电失败";
	};
	string error_hit[18];
};
