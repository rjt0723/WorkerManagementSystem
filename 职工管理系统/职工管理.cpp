#include <iostream>
#include"workerManager.h"
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
using namespace std;
int main()
{
	//实例化对象
	WorkerManager wm;
	
	int choice = 0;

	while (true) {
		//显示菜单
		wm.Show_Menu();
		cout << "请输入你的选择: " << endl;
        cin >> choice;
		switch (choice) 
		{
		case 0://退出系统
			wm.ExitSystem();
			break;
		case 1://增加职工
			wm.Add_Emp();
			break;
		case 2://显示职工
			wm.Show_Emp();
			break;
		case 3://删除职工
			wm.Del_Emp();
			break;
		case 4://修改职工
			wm.Mod_Emp();
			break;
		case 5://查找职工
			wm.Find_Emp();
			break;
		case 6://编号排序
			wm.Sort_Emp();
			break;
		case 7://清空所有
			wm.Clean_File();
			break;
		default:
			system("cls");
			break;
		}
	}
	return 0;
}