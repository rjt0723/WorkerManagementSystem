#include "workerManager.h"
//���캯��
WorkerManager::WorkerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//�ļ�������
	if (!ifs.is_open()) {
        //cout << "�ļ�������" << endl;
	    //��ʼ����¼����
		this->m_EmpNum = 0;

	    //��ʼ������ָ��
		this->m_EmpArray = NULL;

	    //��ʼ���ļ��Ƿ�Ϊ��
		this->m_FileIsEmpty = true;

		ifs.close();
		return;
	}

	//�ļ���������
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "�ļ�Ϊ��" << endl;
		//��ʼ����¼����
		this->m_EmpNum = 0;

		//��ʼ������ָ��
		this->m_EmpArray = NULL;

		//��ʼ���ļ��Ƿ�Ϊ��
		this->m_FileIsEmpty = true;

		ifs.close();
		return;
	}

	//3���ļ������Ҽ�¼����
	int num = this->get_EmpNum();
	//cout << "ְ������Ϊ �� " << num << endl;
	this->m_EmpNum = num;
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	this->init_Emp();
	//for (int i = 0; i < this->m_EmpNum; i++) {
	//	cout << "��ţ� " << this->m_EmpArray[i]->m_ID<<" "
	//		<< "������ " << this->m_EmpArray[i]->m_Name<<" "
	//		<< "��λ�� " << this->m_EmpArray[i]->getDeptName() << endl;
	//}

}

//��������
WorkerManager::~WorkerManager() 
{
	if (this->m_EmpArray != NULL) {
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}

//չʾ�˵�
void WorkerManager::Show_Menu()
{
	cout << "******************************" << endl;
	cout << "*****��ӭʹ��ְ������ϵͳ*****" << endl;
	cout << "*******0-�˳��������*********" << endl;
	cout << "*******1-����ְ����Ϣ*********" << endl;
	cout << "*******2-��ʾְ����Ϣ*********" << endl;
	cout << "*******3-ɾ����ְְ��*********" << endl;
	cout << "*******4-�޸�ְ����Ϣ*********" << endl;
	cout << "*******5-����ְ����Ϣ*********" << endl;
	cout << "*******6-���ձ������*********" << endl;
	cout << "*******7-��������ĵ�*********" << endl;
	cout << "******************************" << endl;
}

//�˳�ϵͳ����
void WorkerManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

//����ְ��
void WorkerManager::Add_Emp()
{
	cout << "���������ְԱ������ " << endl;
	int AddNum = 0;
	cin >> AddNum;
	if (AddNum > 0) {
        int NewSize = this->m_EmpNum + AddNum;
	    Worker** NewSpace = new Worker * [NewSize];
		//��ԭ���ݿ���
		if(this->m_EmpArray != NULL){
			for (int i = 0; i < this->m_EmpNum; i++) {
				NewSpace[i] = this->m_EmpArray[i];
		    }
        }
		//�������������
		for (int i = 0; i < AddNum; i++) 
		{
			int id;
			string name;
			int did;

			cout << "������� " << i + 1 << "��ְ���ı��" << endl;
			cin >> id;
			cout << "������� " << i + 1 << "��ְ��������" << endl;
			cin >> name;
			cout << "��ѡ��� " << i + 1 << "��ְ���ĸ�λ" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
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
		
		//�������ݵ��ļ���
		this->save();
	
		cout << "�ɹ����" << AddNum << "����ְ��" << endl;

		//����ְ����Ϊ�ձ�־
		this->m_FileIsEmpty = false;
		
	}
	else {
		cout << "������������" << endl;
	}
	system("pause");
	system("cls");
}

//�����ļ�
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

//ͳ���ļ�������
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

//��ʼ��Ա��
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

//��ʾְ��
void WorkerManager::Show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ�Ϊ��" << endl;
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

//ɾ��Ա��
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ�����Ϊ��" << endl;
	}
	else{
	    int id = 0;
	    cout << "������ɾ��Ա���ı��:" << endl;
	    cin >> id;
	    int index = this->IsExist(id);
	    if (index == -1) {
		   cout << "Ա��������" << endl;
	    }
	    else {
		   for (int i = index; i < this->m_EmpNum - 1; i++) {
			  this->m_EmpArray[i] = this->m_EmpArray[i + 1];
		}
		this->m_EmpNum--;
		this->save();
		cout << "ɾ���ɹ�" << endl;
	}
	system("pause");
	system("cls");
	}
}

//�ж�ְ���Ƿ����  ������ڷ���ְ�����������е�λ�ã������ڷ���-1
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

//�޸�ְ��
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ�����Ϊ��" << endl;
	}
	else {
		int id = 0;
		cout << "�������޸�Ա����ţ�" << endl;
		cin >> id;
		int ret = this->IsExist(id);
		if ( ret != -1) {
			delete this->m_EmpArray[ret];
			int id;
			string name;
			int did;
			cout << "�������޸ĵı�ţ� " << endl;
			cin >> id;
			cout << "�������޸ĵ������� " << endl;
			cin >> name;
			cout << "��ѡ���޸ĵĸ�λ�� " << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
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
			cout << "�޸ĳɹ���" << endl;
			this->save();
			system("pause");
			system("cls");

		}
		else {
			cout << "Ա��������" << endl;
		}
	}
}

//����ְ��
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ�����Ϊ��" << endl;
	}
	else {
		cout << "���������ְ���ķ�ʽ��" << endl;
		cout << "1������Ų���" << endl;
		cout << "2������������" << endl;

		int select = 0;
		cin >> select;
		
		if (select == 1) {
			cout << "���������Ա���ı�ţ�" << endl;
			int id = 0;
			cin >> id;
			int ret = this->IsExist(id);
			if (ret != -1) {
				cout << "���ҳɹ�����Ա����Ϣ���£�" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else {
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else if (select == 2) {
			cout << "���������Ա����������" << endl;
			string name = " ";
			cin >> name;
			bool flag = false;
			for (int i = 0; i < this->m_EmpNum; i++) {
				if (this->m_EmpArray[i]->m_Name == name) {
					cout << "���ҳɹ�����Ա����Ϣ���£�" << endl;
					this->m_EmpArray[i]->showInfo();
					flag = true;
				}
			}
			if (!flag) {
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else {
			cout << "ѡ������" << endl;
		}
		system("pause");
		system("cls");
	}
}

//���������
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "����������ʽ��" << endl;
		cout << "1�����չ��Ž�������" << endl;
		cout << "2�����չ��Ž��н���" << endl;
		int select = 0;
		cin >> select;


		for (int i = 0; i < m_EmpNum; i++)
		{
			int minOrMax = i;//������Сֵ�����ֵ�±�
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)//����
				{
					if (this->m_EmpArray[minOrMax]->m_ID > this->m_EmpArray[j]->m_ID)
					{
						minOrMax = j;
					}
				}

				else//����
				{
					if (this->m_EmpArray[minOrMax]->m_ID < this->m_EmpArray[j]->m_ID)
					{
						minOrMax = j;
					}
				}
			}
			//�ж�һ��ʼ�϶� ��Сֵ�����ֵ �ǲ��Ǽ�������ֵ����Сֵ ��������� ��������
			if (i != minOrMax)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}
		}
		cout << "����ɹ��������Ľ��Ϊ��" << endl;
		this->save();//����������浽�ļ���
		this->Show_Emp();//չʾ����ְ��
	}
}

//����ļ�����
void WorkerManager::Clean_File()
{
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;

	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//����ļ�
		ofstream ofs(FILENAME, ios::trunc);//ɾ���ļ������´���
		ofs.close();
		if (this->m_EmpArray != NULL)
		{
			//ɾ��������ÿ��ְ������
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
			//ɾ����������ָ��
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "��ճɹ���" << endl;
	}
	system("pause");
	system("cls");
}




