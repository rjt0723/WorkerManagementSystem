#pragma once
#include <iostream>
#include <fstream>
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#define FILENAME "emFIle.txt"
using namespace std;
class WorkerManager
{
public:
    //���캯��
	WorkerManager();

    //��������
	~WorkerManager();

	//չʾ�˵�
	void Show_Menu();

	//�˳�ϵͳ����
	void ExitSystem();

	//ְ������
	int m_EmpNum;

	//ְ������ָ��
	Worker** m_EmpArray;

	//����ְ��
	void Add_Emp();

	//�����ļ�
	void save();

	//�ж��ļ��Ƿ����
	bool m_FileIsEmpty;

	//ͳ���ļ�������
	int get_EmpNum();

	//��ʼ��Ա��
	void init_Emp();

	//��ʾְ��
	void Show_Emp();

	//ɾ��Ա��
	void Del_Emp();

	//�ж�ְ���Ƿ����  ������ڷ���ְ�����������е�λ�ã������ڷ���-1
	int IsExist(int id);

	//�޸�ְ��
	void Mod_Emp();

	//����ְ��
	void Find_Emp();

	//���������
	void Sort_Emp();

	//����ļ�����
	void Clean_File();

};