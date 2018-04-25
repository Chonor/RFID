#pragma once
#include <string>
using std::string;

string error_hit[19] = { "IFD_OK 执行成功",
	"IFD_ICC_TypeError 卡片类型不对",
	"IFD_ICC_NoExist 无卡",
	"IFD_ICC_NoPower 有卡未上电",
	"IFD_ICC_NoResponse 卡片无应答",
	"IFD_ICC_BCCError BCC校验错误",
	"IFD_ICC_TimeOut 接收超时",
	"IFD_ICC_RunFail 执行失败",
	"IFD_ICC_SiteFail 卡片位置错误",
	"IFD_ICC_SetFail 设置失败",
	"IFD_NoSlot 无卡",
	"IFD_ConnectError 读卡器连接错",
	"IFD_UnConnected 未建立连接(没有执行打开设备函数)",
	"IFD_BadCommand (动态库)不支持该命令",
	"IFD_CheckSumError 信息校验和出错",
	"IFD_ICC_PowerFail 卡片上电失败",
	"IFD_ICC_ResetFail 卡片复位失败",
	"IFD_ICC_PowerOffFail 卡片下电失败"
};
