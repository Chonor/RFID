#pragma once
#include <string>
using std::string;
class Hits
{
public:
	Hits() {
		error_hit[0] = "IFD_OK ִ�гɹ�";
		error_hit[1] = "IFD_ICC_TypeError ��Ƭ���Ͳ���";
		error_hit[2] = "IFD_ICC_NoExist �޿�";
		error_hit[3] = "IFD_ICC_NoPower �п�δ�ϵ�";
		error_hit[4] = "IFD_ICC_NoResponse ��Ƭ��Ӧ��";
		error_hit[5] = "IFD_ICC_BCCError BCCУ�����";
		error_hit[6] = "IFD_ICC_TimeOut ���ճ�ʱ";
		error_hit[7] = "IFD_ICC_RunFail ִ��ʧ��";
		error_hit[8] = "IFD_ICC_SiteFail ��Ƭλ�ô���";
		error_hit[9] = "IFD_ICC_SetFail ����ʧ��";
		error_hit[10] = "IFD_NoSlot �޿�";
		error_hit[11] = "IFD_ConnectError ���������Ӵ�";
		error_hit[12] = "IFD_UnConnected δ��������(û��ִ�д��豸����)";
		error_hit[13] = "IFD_BadCommand (��̬��)��֧�ָ�����";
		error_hit[14] = "IFD_CheckSumError ��ϢУ��ͳ���";
		error_hit[15] = "IFD_ICC_PowerFail ��Ƭ�ϵ�ʧ��";
		error_hit[16] = "IFD_ICC_ResetFail ��Ƭ��λʧ��";
		error_hit[17] = "IFD_ICC_PowerOffFail ��Ƭ�µ�ʧ��";
	};
	string error_hit[18];
};
