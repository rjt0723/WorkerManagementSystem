#include "boss.h"
//���캯��
Boss::Boss(int id, string name, int did)
{
	this->m_ID = id;
	this->m_Name = name;
	this->m_DeptID = did;
}

//��ʾ������Ϣ
void Boss::showInfo()
{
	cout << "ְ����ţ� " << this->m_ID
		<< "\tְ�������� " << this->m_Name
		<< "\t��λ�� " << this->getDeptName()
		<< "\t��λְ��:����˾���е�����" << endl;
}

//��ȡ��λ����
string Boss::getDeptName()
{
	return "�ϰ�";
}
