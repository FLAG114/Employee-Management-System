#include"workerManager.h"
#include<cassert>

//���캯��
WorkerManager::WorkerManager()
{

	//1.�ļ�������
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		//ȫ����ʼ��Ϊ0
		this->_emp_num = 0;
		this->_emp_arr = NULL;
		//Ϊ��
		this->is_file_empty = true;
		ifs.close();
		return;
	}

	//2.�ļ����ڣ�������Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//�ļ�Ϊ��
		cout << "�ļ�Ϊ��" << endl;
		//ȫ����ʼ��Ϊ0
		this->_emp_num = 0;
		this->_emp_arr = NULL;
		//Ϊ��
		this->is_file_empty = true;
		ifs.close();
		return;
	}

	//3.�ļ�������������
	int num = this->get_emp_num();
	cout << "ְ������Ϊ��" << num << endl;
	this->_emp_num = num;

	//���ٿռ�
	this->_emp_arr = new worker * [this->_emp_num];
	//���ļ��е����ݴ浽������
	this->init_emp();

}

//��������
WorkerManager::~WorkerManager()
{
	if (this->_emp_arr != NULL)
	{
		delete[] this->_emp_arr;
		this->_emp_arr = NULL;
	}
}

//չʾ�˵�
void WorkerManager::show_menu()
{
	cout << "*��ӭʹ��ְ������ϵͳ*" << endl;
	cout << "***0.�˳�����ϵͳ***" << endl;
	cout << "***1.����ְ����Ϣ***" << endl;
	cout << "***2.��ʾԱ����Ϣ***" << endl;
	cout << "***3.ɾ����ְԱ��***" << endl;
	cout << "***4.�޸�Ա����Ϣ***" << endl;
	cout << "***5.����Ա����Ϣ***" << endl;
	cout << "***6.���ձ������***" << endl;
	cout << "***7.���������Ϣ***" << endl;
	cout << endl;
}

//���
void WorkerManager::add_emp()
{
	cout << "���������ְ��������" << endl;
	int add_num = 0;
	cin >> add_num;//�����û���������
	assert(add_num > 0);

	//��������¿ռ�Ĵ�С
	//ԭ��+����
	int new_size = this->_emp_num + add_num;

	//�����¿ռ�
	worker** new_space = new worker * [new_size];

	//��ԭ��ԭ���ռ�����ݷ����¿ռ���
	if (this->_emp_arr != NULL)
	{
		for (int i = 0; i < this->_emp_num; i++)
		{
			new_space[i] = this->_emp_arr[i];
		}
	}

	//�������������
	for (int i = 0; i < add_num; ++i)
	{
		int id;
		string name;
		int dep_select;
		cout << "�������" << i + 1 << "����ְ�����" << endl;
		cin >> id;
		cout << "�������" << i + 1 << "����ְ������" << endl;
		cin >> name;
		cout << "�������" << i + 1 << "����ְ�������" << endl;
		cout << "1.Ա��"
			<< "\t2.����"
			<< "\t3.�ϰ�" << endl;
		cin >> dep_select;
		assert(dep_select == 1 || dep_select == 2 || dep_select == 3);
		worker* worker = NULL;
		switch (dep_select)
		{
		case 1:
			worker = new employee(id, name, 1);
			break;
		case 2:
			worker = new manager(id, name, 2);
			break;
		case 3:
			worker = new boss(id, name, 3);
			break;
		default:
			break;
		}

		new_space[this->_emp_num + i] = worker;
	}

	//�ͷ�ԭ�пռ�
	delete[]this->_emp_arr;

	//�����¿ռ��ָ��
	this->_emp_arr = new_space;

	//��������
	this->_emp_num = new_size;

	//����ְ����Ϊ�յ�״̬
	this->is_file_empty = false;

	cout << "�ɹ����" << add_num << "����ְ��" << endl;

	//�������ݵ��ļ���
	this->save();

	system("pause");
	system("cls");
}

//ͳ���ļ�������
int WorkerManager::get_emp_num()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int did;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> did)
	{
		//ͳ������
		++num;
	}
	return num;
}

//��ʼ��Ա��
void WorkerManager::init_emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int did;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> did)
	{
		worker* worker = NULL;

		if (did == 1)     //��ְͨ��
			worker = new employee(id, name, did);
		else if (did == 2)//����
			worker = new manager(id, name, did);
		else             //boss
			worker = new boss(id, name, did);

		this->_emp_arr[index] = worker;
		++index;
	}
	ifs.close();
	//ifstream�����Զ����еĹ���
}

//�����ļ� 
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);//д

	//��ÿ���˵�����д���ļ���
	for (int i = 0; i < this->_emp_num; i++)
	{
		ofs << this->_emp_arr[i]->_id << " "
			<< this->_emp_arr[i]->_name << " "
			<< this->_emp_arr[i]->_dep_id << endl;
	}
	ofs.close();
	//std::ofstream��������д�Ǵ�ͷ��ʼд��Ҳ���ǰ�ԭ�������ݸ����ˡ�
}

//��ʾְ��
void WorkerManager::show_emp()
{
	//�ж��ļ��Ƿ�Ϊ��
	if (this->is_file_empty)
	{
		cout << "�ļ����ܴ��ڻ��߼�¼Ϊ��" << endl;
	}
	else 
	{
		for (int i = 0; i < this->_emp_num; ++i)
		{
			this->_emp_arr[i]->show_info();
		}
	}

	system("pause");
	system("cls");
}

//�ж�ĳ��ְ���Ƿ����
int WorkerManager::is_exist(int id)
{
	int index = -1;//Ĭ��û�ҵ�����-1
	for (int i = 0; i < this->_emp_num;++i)
	{
		if (this->_emp_arr[i]->_id == id)
		{
			index = i;//�ҵ���
			break;
		}
	}
	return index;
}

//ɾ��ְ��
void WorkerManager::del_emp()
{
	if (this->is_file_empty)
	{
		cout << "�ļ�������or��¼Ϊ��" << endl;
	}
	else
	{
		cout << "������Ҫɾ����ְ���ı��:";
		int id = 0;
		cin >> id;
		int index = this->is_exist(id);
		if (index != -1)//�ҵ���
		{
			for (int i = index; i < this->_emp_num - 1; ++i)
			{
				//����ǰ��
				this->_emp_arr[i] = this->_emp_arr[i + 1];
			}
			--this->_emp_num;//����num
			//���µ��ļ���
			this->save();

			cout << "ɾ���ɹ�" << endl;
		}
		else
		{
			cout << "û�ҵ���ְ���ı��" << endl;
		}
	}

	system("pause");
	system("cls");
}

//�޸�ְ��
void WorkerManager::mod_emp()
{
	if (this->is_file_empty)
	{
		cout << "�ļ������ڻ�Ϊ��" << endl;
	}
	else
	{
		cout << "������ְ�����" << endl;
		int id = 0;
		cin >> id;

		int ret = this->is_exist(id);
		if (ret != -1)//���ҵ�
		{
			delete this->_emp_arr[ret];

			int new_id = 0;
			string new_name = "\0";
			int new_did = 0;
			cout << "���ҵ����Ϊ��" << id << "��ְ��" << endl;
			cout << "�������µı�ţ�" << endl;
			cin >> new_id;
			cout << "�������µ�������" << endl;
			cin >> new_name;
			cout << "�������µĸ�λ��" << endl;
			cout << "1.Ա��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
			cin >> new_id;

			worker* wk = NULL;
			switch (new_id)
			{
			case 1:
				wk = new employee(new_id, new_name, new_did);
				break;
			case 2:
				wk = new manager(new_id, new_name, new_did);
				break;
			case 3:
				wk = new boss(new_id, new_name, new_did);
				break;
			default:
				break;
			}

			//����
			this->_emp_arr[ret] = wk;
			cout << "�޸ĳɹ�" << endl;

			//���浽�ļ���
			this->save();
		}
		else//û�ҵ�
		{
			cout << "�޸�ʧ�ܣ�δ�鵽Ŀ����Ϣ" << endl;
		}
		system("pause");
		system("cls");
	}
}

//����ְ��
void WorkerManager::find_emp()
{
	if (this->is_file_empty)
	{
		cout << "�ļ������ڻ��߼�¼Ϊ��" << endl;
	}
	else
	{
		cout << "��������ҷ�ʽ" << endl;
		cout << "1.����Ų���" << endl;
		cout << "2.����������" << endl;

		int choice = 0;
		cin >> choice;

		if (choice == 1)
		{
			//��Ų���
			int id;
			cout << "����ְ�����" << endl;
			cin >> id;
			int ret = this->is_exist(id);
			if (ret != -1)
			{
				cout << "�ҵ�ְ������Ϣ���£�" << endl;
				this->_emp_arr[ret]->show_info();
			}
			else
			{
				cout << "û�ҵ�" << endl;
			}
		}
		else if (choice == 2)
		{
			//��������
			string name;
			cout << "����ְ������" << endl;
			cin >> name;

			bool flag = false;
			for (int i = 0; i < this->_emp_num; ++i)
			{
				if (this->_emp_arr[i]->_name == name)
				{
					cout << "���ҳɹ�,��Ϣ���£�" << endl;
					this->_emp_arr[i]->show_info();
					flag = true;
					break;
				}
			}
			if (flag == false)
			{
				cout << "����ʧ��" << endl;
			}
		}
		else
		{
			cout << "��������" << endl;
		}
	}
	system("pause");
	system("cls");
}

//����ְ��
void WorkerManager::sort_emp()
{
	if (this->is_file_empty)
	{
		cout << "�ļ������ڻ��߼�¼Ϊ��" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "����������ʽ" << endl;
		cout << "1.��ְ��������" << endl;
		cout << "2.��ְ���Ž���" << endl;

		int choice = 0;
		cin >> choice;
		for (int i = 0; i < this->_emp_num; ++i)
		{
			int min_or_max = i;
			for (int j = i + 1; j < this->_emp_num; ++j)
			{
				if (choice == 1)//����
				{
					if (this->_emp_arr[min_or_max]->_id > this->_emp_arr[j]->_id)
					{
						min_or_max = j;
					}
				}
				else//����
				{
					if (this->_emp_arr[min_or_max]->_id < this->_emp_arr[j]->_id)
					{
						min_or_max = j;
					}
				}

				if (i != min_or_max)
				{
					worker* temp = this->_emp_arr[i];
					this->_emp_arr[i] = this->_emp_arr[min_or_max];
					this->_emp_arr[min_or_max] = temp;
				}
			}

		}

		cout << "����ɹ�" << endl;
		this->save();
		this->show_emp();
	}
}

//���
void WorkerManager::clear_emp()
{
	cout << "ȷ����գ�(y/n)" << endl;
	char a;
	cin >> a;
	if (a == 'y')
	{
		//����ļ�
		ofstream ofs;
		ofs.open(FILENAME, ios::trunc);//ɾ���ļ������´���
		ofs.close();

		if (this->_emp_arr != NULL)
		{
			//ɾ��ÿ��ְ������
			for (int i = 0; i < this->_emp_num; ++i)
			{
				delete this->_emp_arr[i];
				this->_emp_arr[i] == NULL;
			}

			//ɾ����������ָ��
			delete[] this->_emp_arr;
			this->_emp_arr = NULL;
			this->_emp_num = true;
			this->is_file_empty = true;
		}
		cout << "��ճɹ�" << endl;
		system("pause");
		system("cls");
	}
}

//�˳�
void WorkerManager::exit_system()
{
	cout << "�ڴ��´�ʹ��" << endl;
	exit(0);
}