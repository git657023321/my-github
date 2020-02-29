#include"ATMLogInDlg.h"
#include"WCommon.h"
#include "ATMMenuDlg.h"
#include"WScreen.h"
#include"WLoginFailTip.h"
#include <string>
#include <stdlib.h>
#include<stdio.h>


//����ص�
void ATMLogInDlg::OnLoginClick(void *pThis)//static�汾��������ʽ���� 
{
	ATMLogInDlg* pObj=(ATMLogInDlg*) pThis;
	if(pObj)
	{
		pObj->OnLoginClick();//ͨ�����ݻ�ȡ��ǰ��ʵ����ָ�룬��ȥ���÷�static�汾
	}
}

//��static��Ա������Ĭ�϶�һ��������һ��������߶���ָ�룩��static��Ա��������Ҫ���ݶ���ָ�루static��Ա�ͷ�����������������ڣ�
void ATMLogInDlg::OnLoginClick()
{
	//��ȡ������еĿ��š�����
	int i;
	string strCardNo=m_pCardID->GetText();
	string  strPwd=m_pPwd->GetText();
	
/*	int x=0;
	char str1[10];
	sprintf(str1,"%d",x);
	char str2[10];
	sprintf(str2,"%s",strCardNo);
	char str3[10];
	sprintf(str3,"%s",strPwd);

	char *strCat=(char*)malloc(strlen(str1)+strlen(str2)+strlen(str3));
	sprintf(strCat,"%s%s%s",str1,str2,str3);
*/	
	
	string str=strCardNo+strPwd;
	char sendstr[50];
	sendstr[0]='0';
	for(i=1;i<str.length()+1;i++)
	{
		sendstr[i]=str.at(i-1);
	}
	sendstr[i]='\0';
	//������ݿ����Ӳ���������˺������Ƿ�ƥ��
	//char sendbuf[20]={'1','2','3','4'};
	
	
	if(send0(sockCli,sendstr))
	{
	//���ݿ�ƥ��ɹ��������˵�ҳ��
		for(i=0;i<strCardNo.length();i++)
		{
			CardId[i]=strCardNo.at(i);
		}
		CardId[i]='\0';
		ATMMenuDlg* plg = ATMMenuDlg::CreatWWindow(0,0,800,480);
		WbmpRes bmp;
		bmp.strPath="res/menu.bmp";
		bmp.isTransParent = false;
		plg->SetBackGround(bmp);
		WScreen::getSingletonScreen()->AddDialog(plg);
		m_pCardID->SetStrText("");
		m_pPwd->SetStrText("");
		m_pCardID->Domessage(MSG_MOUSE_LBUTTONDOWN,300,200);
		m_pPwd->Domessage(MSG_MOUSE_LBUTTONDOWN,300,280);
		m_pPwd->SetCaret();
		m_pCardID->SetCaret();
		Refresh();
	}
	else
	{
		//��������	
		m_pCardID->SetStrText("");
		m_pPwd->SetStrText("");
		
		m_pPwd->Domessage(MSG_MOUSE_LBUTTONDOWN,300,280);
		m_pCardID->Domessage(MSG_MOUSE_LBUTTONDOWN,300,200);
		
		m_pPwd->SetCaret();
		m_pCardID->SetCaret();
		//������ʾ�������������������

		WLoginFailTip* tip = WLoginFailTip::CreatWWindow(200,100,400,250);
		WbmpRes bmp;
		bmp.strPath="res/tip.bmp";
		bmp.isTransParent = false;
		tip->SetBackGround(bmp);
		tip->SetText("�������");
		WScreen::getSingletonScreen()->AddDialog(tip);
	}
}


void ATMLogInDlg::OnCancelLick(void *pThis)
{
	ATMLogInDlg* pObj=(ATMLogInDlg*) pThis;
	if(pObj)
	{
		pObj->OnCancelLick();
	}
}

void ATMLogInDlg::OnCancelLick()
{
	m_pCardID->SetStrText("");
	m_pPwd->SetStrText("");
	
	m_pPwd->Domessage(MSG_MOUSE_LBUTTONDOWN,300,280);
	m_pCardID->Domessage(MSG_MOUSE_LBUTTONDOWN,300,200);

}

ATMLogInDlg::ATMLogInDlg(int posx,int posy,int width,int height)
:WDialog(posx,posy,width,height)
{
}
void ATMLogInDlg::OnInit()
{
	//���š������ǩ
	m_pIDLab=WLabel::CreateWWindow(90, 150, 120, 60);
	m_pIDLab->SetCaption("�˺�");
	m_pPwdLab=WLabel::CreateWWindow(90, 240, 120, 60);
	m_pPwdLab->SetCaption("����");
	this->AddControl(m_pIDLab);
	this->AddControl(m_pPwdLab);

	//������������������
	m_pCardID=WTextBox::CreateWWindow(220, 150, 500, 60);
	WColor clr={255,255,255};
	m_pCardID->SetBackGroundColor(clr);

	m_pPwd=WTextBox::CreateWWindow(220, 240, 500, 60);
	m_pPwd->SetBackGroundColor(clr);
	m_pPwd->SetIsHide(true);

	this->AddControl(m_pCardID);
	this->AddControl(m_pPwd);


	//��¼��ť
	m_pLoginBtn=WButton::CreateWWindow(230,350,227,75);
	WbmpRes bmp;
	bmp.strPath="res/btn_N.bmp";
    bmp.isTransParent = false;
	m_pLoginBtn->SetBackGroundNormal(bmp);
	
	
	bmp.strPath="res/btn_F.bmp";
    bmp.isTransParent = false;
	m_pLoginBtn->SetBackGroundFocus(bmp);

	bmp.strPath="res/btn_P.bmp";
    bmp.isTransParent = false;
	m_pLoginBtn->SetBackGroundPush(bmp);
	m_pLoginBtn->SetCaption("��¼");
	m_pLoginBtn->SetClickCallBack(OnLoginClick,this);
	this->AddControl(m_pLoginBtn);
	
	//ȡ����ť
	m_pCancelBtn=WButton::CreateWWindow(480,350,227,75);
	bmp.strPath="res/btn_N.bmp";
    bmp.isTransParent = false;
	m_pCancelBtn->SetBackGroundNormal(bmp);
	
	
	bmp.strPath="res/btn_F.bmp";
    bmp.isTransParent = false;
	m_pCancelBtn->SetBackGroundFocus(bmp);

	bmp.strPath="res/btn_P.bmp";
    bmp.isTransParent = false;
	m_pCancelBtn->SetBackGroundPush(bmp);
	m_pCancelBtn->SetCaption("ȡ��");
	m_pCancelBtn->SetClickCallBack(OnCancelLick,this);
	this->AddControl(m_pCancelBtn);

}