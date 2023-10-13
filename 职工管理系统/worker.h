#pragma once
#include <iostream>
#include <string>
using namespace std;
//职工抽象类
class Worker
{
public:
	//显示个人信息
	virtual void showInfo() = 0;

	//获取岗位名称
	virtual string getDeptName() = 0;

	int m_ID;

	string m_Name;
	
	int m_DeptID;
};

