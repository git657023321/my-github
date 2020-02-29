#include"WTransfer.h"
#include"WCommon.h"
#include"WScreen.h"
#include"WQueryDlg.h"
#include"WTip.h"

void WTransfer::OnReturnClick(void *pThis)
{
	
	WTransfer* pObj=(WTransfer*) pThis;
	if(pObj)
	{
		pObj->OnReturnClick();
	}
}

void WTransfer::OnReturnClick()
{	
	WScreen::getSingletonScreen()->DeleteDialog();
}


void WTransfer::OnTransferClick(void *pThis)
{
	
	WTransfer* pObj=(WTransfer*) pThis;
	if(pObj)
	{
		pObj->OnTransferClick();
	}
}

void WTransfer::OnTransferClick()
{	
	//////////////////////////����ת�˲�������
    string strID=m_pIDBox->GetText();
	string strmoney=m_pMoneyBox->GetText();


	char sendbuf[50];
	sendbuf[0]='4';
	int i;
	for(i=1;i<11;i++)
	{
		sendbuf[i]=CardId[i-1];
	}
	for(i=11;i<strID.length()+11;i++)
	{
		sendbuf[i]=strID.at(i-11);
	}
	for(i=21;i<strmoney.length()+21;i++)
	{
		sendbuf[i]=strmoney.at(i-21);
	}
	sendbuf[i]='\0';

	if(send0(sockCli,sendbuf))
	{
		WTip* tip = WTip::CreatWWindow(200,100,400,250);
		WbmpRes bmp;
		bmp.strPath="res/tip.bmp";
		bmp.isTransParent = false;
		tip->SetBackGround(bmp);
		tip->SetText("ת�˳ɹ�!");
		WScreen::getSingletonScreen()->AddDialog(tip);
	}


}

WTransfer::WTransfer(int posx,int posy,int width,int height)
:WDialog(posx,posy,width,height)
{
}

void WTransfer::OnInit()
{
	//���Է��˻�ID��label
	m_pIDLabel=WLabel::CreateWWindow(230,100,260, 60);
	m_pIDLabel->SetCaption("�Է��˺�:");
	this->AddControl(m_pIDLabel);


	//�������lable
	m_pMoneyLabel=WLabel::CreateWWindow(230,180,260, 60);
	m_pMoneyLabel->SetCaption("ת�˽��:");
	this->AddControl(m_pMoneyLabel);


	//ID�����
	m_pIDBox=WTextBox::CreateWWindow(510, 100, 200, 60);
	WColor clr={255,255,255};
	m_pIDBox->SetBackGroundColor(clr);
	this->AddControl(m_pIDBox);

	//��������
	m_pMoneyBox=WTextBox::CreateWWindow(510, 180, 200, 60);
	m_pMoneyBox->SetBackGroundColor(clr);
	this->AddControl(m_pMoneyBox);

	//ȷ��ת�˴洢btn
	m_pTransBtn=WButton::CreateWWindow(220,300,227,75);
	WbmpRes bmp;
	bmp.strPath="res/btn_N.bmp";
    bmp.isTransParent = true;
	m_pTransBtn->SetBackGroundNormal(bmp);
	

	bmp.strPath="res/btn_F.bmp";
    bmp.isTransParent = true;
	m_pTransBtn->SetBackGroundFocus(bmp);

	bmp.strPath="res/btn_P.bmp";
    bmp.isTransParent = true;
	m_pTransBtn->SetBackGroundPush(bmp);
	m_pTransBtn->SetCaption("ȷ��");

	m_pTransBtn->SetClickCallBack(OnTransferClick,this);
	this->AddControl(m_pTransBtn);


	//�������˵�btn
	m_pReturnBtn=WButton::CreateWWindow(470,300,227,75);
	bmp.strPath="res/btn_N.bmp";
    bmp.isTransParent = true;
	m_pReturnBtn->SetBackGroundNormal(bmp);
	

	bmp.strPath="res/btn_F.bmp";
    bmp.isTransParent = true;
	m_pReturnBtn->SetBackGroundFocus(bmp);

	bmp.strPath="res/btn_P.bmp";
    bmp.isTransParent = true;
	m_pReturnBtn->SetBackGroundPush(bmp);
	m_pReturnBtn->SetCaption("����");
	
	m_pReturnBtn->SetClickCallBack(OnReturnClick,this);

	
	this->AddControl(m_pReturnBtn);

	

}