#include "workerManager.h"
//构造函数
WorkerManager::WorkerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//文件不存在
	if (!ifs.is_open()) {
        //cout << "文件不存在" << endl;
	    //初始化记录人数
		this->m_EmpNum = 0;

	    //初始化数组指针
		this->m_EmpArray = NULL;

	    //初始化文件是否为空
		this->m_FileIsEmpty = true;

		ifs.close();
		return;
	}

	//文件中无数据
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "文件为空" << endl;
		//初始化记录人数
		this->m_EmpNum = 0;

		//初始化数组指针
		this->m_EmpArray = NULL;

		//初始化文件是否为空
		this->m_FileIsEmpty = true;

		ifs.close();
		return;
	}

	//3、文件存在且记录数据
	int num = this->get_EmpNum();
	//cout << "职工人数为 ： " << num << endl;
	this->m_EmpNum = num;
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	this->init_Emp();
	//for (int i = 0; i < this->m_EmpNum; i++) {
	//	cout << "编号： " << this->m_EmpArray[i]->m_ID<<" "
	//		<< "姓名： " << this->m_EmpArray[i]->m_Name<<" "
	//		<< "岗位： " << this->m_EmpArray[i]->getDeptName() << endl;
	//}

}

//析构函数
WorkerManager::~WorkerManager() 
{
	if (this->m_EmpArray != NULL) {
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}

//展示菜单
void WorkerManager::Show_Menu()
{
	cout << "******************************" << endl;
	cout << "*****欢迎使用职工管理系统*****" << endl;
	cout << "*******0-退出管理程序*********" << endl;
	cout << "*******1-增加职工信息*********" << endl;
	cout << "*******2-显示职工信息*********" << endl;
	cout << "*******3-删除离职职工*********" << endl;
	cout << "*******4-修改职工信息*********" << endl;
	cout << "*******5-查找职工信息*********" << endl;
	cout << "*******6-按照编号排序*********" << endl;
	cout << "*******7-清空所有文档*********" << endl;
	cout << "******************************" << endl;
}

//退出系统功能
void WorkerManager::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

//增加职工
void WorkerManager::Add_Emp()
{
	cout << "请输入添加职员人数： " << endl;
	int AddNum = 0;
	cin >> AddNum;
	if (AddNum > 0) {
        int NewSize = this->m_EmpNum + AddNum;
	    Worker** NewSpace = new Worker * [NewSize];
		//将原数据拷贝
		if(this->m_EmpArray != NULL){
			for (int i = 0; i < this->m_EmpNum; i++) {
				NewSpace[i] = this->m_EmpArray[i];
		    }
        }
		//批量添加新数据
		for (int i = 0; i < AddNum; i++) 
		{
			int id;
			string name;
			int did;

			cout << "请输入第 " << i + 1 << "个职工的编号" << endl;
			cin >> id;
			cout << "请输入第 " << i + 1 << "个职工的姓名" << endl;
			cin >> name;
			cout << "请选择第 " << i + 1 << "个职工的岗位" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> did;
			Worker* worker = NULL;
			switch (did)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			NewSpace[this->m_EmpNum + i ] = worker;
		}
		
		
	    this->m_EmpNum = NewSize;
		delete[] this->m_EmpArray;
		this->m_EmpArray = NewSpace;	
		
		//保存数据到文件中
		this->save();
	
		cout << "成功添加" << AddNum << "名新职工" << endl;

		//更新职工不为空标志
		this->m_FileIsEmpty = false;
		
	}
	else {
		cout << "输入数据有误" << endl;
	}
	system("pause");
	system("cls");
}

//保存文件
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	for (int i = 0; i < this->m_EmpNum; i++) {
		ofs << this->m_EmpArray[i]->m_ID << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptID << endl;
	}
	ofs.close();
}

//统计文件中人数
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int did;
	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> did) {
		num++;
	}
	return num;
}

//初始化员工
void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int did;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> did) {
		Worker* worker = NULL;
		if (did == 1) {
			worker = new Employee(id, name, did);
		}
		else if (did == 2) {
			worker = new Manager(id, name, did);
		}
		else if (did == 3) {
			worker = new Boss(id, name, did);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();
}

//显示职工
void WorkerManager::Show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或为空" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

//删除员工
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或数据为空" << endl;
	}
	else{
	    int id = 0;
	    cout << "请输入删除员工的编号:" << endl;
	    cin >> id;
	    int index = this->IsExist(id);
	    if (index == -1) {
		   cout << "员工不存在" << endl;
	    }
	    else {
		   for (int i = index; i < this->m_EmpNum - 1; i++) {
			  this->m_EmpArray[i] = this->m_EmpArray[i + 1];
		}
		this->m_EmpNum--;
		this->save();
		cout << "删除成功" << endl;
	}
	system("pause");
	system("cls");
	}
}

//判断职工是否存在  如果存在返回职工所在数组中的位置，不存在返回-1
int WorkerManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++) {
		if (id == this->m_EmpArray[i]->m_ID) {
			index = i;
			break;
		}
	}
	return index;
}

//修改职工
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或数据为空" << endl;
	}
	else {
		int id = 0;
		cout << "请输入修改员工编号：" << endl;
		cin >> id;
		int ret = this->IsExist(id);
		if ( ret != -1) {
			delete this->m_EmpArray[ret];
			int id;
			string name;
			int did;
			cout << "请输入修改的编号： " << endl;
			cin >> id;
			cout << "请输入修改的姓名： " << endl;
			cin >> name;
			cout << "请选择修改的岗位： " << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> did;
			Worker* worker = NULL;
			switch (did)
			{
			case 1:
				worker =new Employee(id, name, 1);
				break;
			case 2:
				worker =new Manager(id, name, 2);
				break;
			case 3:
				worker =new Boss(id, name, 3);
				break;
			default:
				break;
			}
			this->m_EmpArray[ret] = worker;
			cout << "修改成功！" << endl;
			this->save();
			system("pause");
			system("cls");

		}
		else {
			cout << "员工不存在" << endl;
		}
	}
}

//查找职工
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或数据为空" << endl;
	}
	else {
		cout << "请输入查找职工的方式：" << endl;
		cout << "1、按编号查找" << endl;
		cout << "2、按姓名查找" << endl;

		int select = 0;
		cin >> select;
		
		if (select == 1) {
			cout << "请输入查找员工的编号：" << endl;
			int id = 0;
			cin >> id;
			int ret = this->IsExist(id);
			if (ret != -1) {
				cout << "查找成功，该员工信息如下：" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else {
				cout << "查找失败，查无此人" << endl;
			}
		}
		else if (select == 2) {
			cout << "请输入查找员工的姓名：" << endl;
			string name = " ";
			cin >> name;
			bool flag = false;
			for (int i = 0; i < this->m_EmpNum; i++) {
				if (this->m_EmpArray[i]->m_Name == name) {
					cout << "查找成功，该员工信息如下：" << endl;
					this->m_EmpArray[i]->showInfo();
					flag = true;
				}
			}
			if (!flag) {
				cout << "查找失败，查无此人" << endl;
			}
		}
		else {
			cout << "选择有误" << endl;
		}
		system("pause");
		system("cls");
	}
}

//按编号排序
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请输入排序方式：" << endl;
		cout << "1、按照工号进行升序" << endl;
		cout << "2、按照工号进行降序" << endl;
		int select = 0;
		cin >> select;


		for (int i = 0; i < m_EmpNum; i++)
		{
			int minOrMax = i;//声明最小值或最大值下标
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)//升序
				{
					if (this->m_EmpArray[minOrMax]->m_ID > this->m_EmpArray[j]->m_ID)
					{
						minOrMax = j;
					}
				}

				else//降序
				{
					if (this->m_EmpArray[minOrMax]->m_ID < this->m_EmpArray[j]->m_ID)
					{
						minOrMax = j;
					}
				}
			}
			//判断一开始认定 最小值或最大值 是不是计算的最大值或最小值 ，如果不是 交换数据
			if (i != minOrMax)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}
		}
		cout << "排序成功！排序后的结果为：" << endl;
		this->save();//排序后结果保存到文件中
		this->Show_Emp();//展示所有职工
	}
}

//清空文件操作
void WorkerManager::Clean_File()
{
	cout << "确定清空？" << endl;
	cout << "1、确定" << endl;
	cout << "2、返回" << endl;

	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//清空文件
		ofstream ofs(FILENAME, ios::trunc);//删除文件后重新创建
		ofs.close();
		if (this->m_EmpArray != NULL)
		{
			//删除堆区的每个职工对象
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
			//删除堆区数组指针
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");
}




