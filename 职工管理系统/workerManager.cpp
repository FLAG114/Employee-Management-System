#include"workerManager.h"
#include<cassert>

//构造函数
WorkerManager::WorkerManager()
{

	//1.文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		//全部初始化为0
		this->_emp_num = 0;
		this->_emp_arr = NULL;
		//为空
		this->is_file_empty = true;
		ifs.close();
		return;
	}

	//2.文件存在，当数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//文件为空
		cout << "文件为空" << endl;
		//全部初始化为0
		this->_emp_num = 0;
		this->_emp_arr = NULL;
		//为空
		this->is_file_empty = true;
		ifs.close();
		return;
	}

	//3.文件存在且有数据
	int num = this->get_emp_num();
	cout << "职工人数为：" << num << endl;
	this->_emp_num = num;

	//开辟空间
	this->_emp_arr = new worker * [this->_emp_num];
	//将文件中的数据存到数组中
	this->init_emp();

}

//析构函数
WorkerManager::~WorkerManager()
{
	if (this->_emp_arr != NULL)
	{
		delete[] this->_emp_arr;
		this->_emp_arr = NULL;
	}
}

//展示菜单
void WorkerManager::show_menu()
{
	cout << "*欢迎使用职工管理系统*" << endl;
	cout << "***0.退出管理系统***" << endl;
	cout << "***1.增加职工信息***" << endl;
	cout << "***2.显示员工信息***" << endl;
	cout << "***3.删除离职员工***" << endl;
	cout << "***4.修改员工信息***" << endl;
	cout << "***5.查找员工信息***" << endl;
	cout << "***6.按照编号排序***" << endl;
	cout << "***7.清空所有信息***" << endl;
	cout << endl;
}

//添加
void WorkerManager::add_emp()
{
	cout << "请输入添加职工的数量" << endl;
	int add_num = 0;
	cin >> add_num;//保存用户输入数量
	assert(add_num > 0);

	//计算添加新空间的大小
	//原来+新增
	int new_size = this->_emp_num + add_num;

	//开辟新空间
	worker** new_space = new worker * [new_size];

	//将原来原来空间的数据放在新空间里
	if (this->_emp_arr != NULL)
	{
		for (int i = 0; i < this->_emp_num; i++)
		{
			new_space[i] = this->_emp_arr[i];
		}
	}

	//批量添加新数据
	for (int i = 0; i < add_num; ++i)
	{
		int id;
		string name;
		int dep_select;
		cout << "请输入第" << i + 1 << "个新职工编号" << endl;
		cin >> id;
		cout << "请输入第" << i + 1 << "个新职工姓名" << endl;
		cin >> name;
		cout << "请输入第" << i + 1 << "个新职工的身份" << endl;
		cout << "1.员工"
			<< "\t2.经理"
			<< "\t3.老板" << endl;
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

	//释放原有空间
	delete[]this->_emp_arr;

	//更改新空间的指向
	this->_emp_arr = new_space;

	//更新人数
	this->_emp_num = new_size;

	//更新职工不为空的状态
	this->is_file_empty = false;

	cout << "成功添加" << add_num << "名新职工" << endl;

	//保存数据到文件中
	this->save();

	system("pause");
	system("cls");
}

//统计文件中人数
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
		//统计人数
		++num;
	}
	return num;
}

//初始化员工
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

		if (did == 1)     //普通职工
			worker = new employee(id, name, did);
		else if (did == 2)//经理
			worker = new manager(id, name, did);
		else             //boss
			worker = new boss(id, name, did);

		this->_emp_arr[index] = worker;
		++index;
	}
	ifs.close();
	//ifstream流有自动换行的功能
}

//保存文件 
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);//写

	//将每个人的数据写入文件中
	for (int i = 0; i < this->_emp_num; i++)
	{
		ofs << this->_emp_arr[i]->_id << " "
			<< this->_emp_arr[i]->_name << " "
			<< this->_emp_arr[i]->_dep_id << endl;
	}
	ofs.close();
	//std::ofstream这样设置写是从头开始写，也就是把原来的内容覆盖了。
}

//显示职工
void WorkerManager::show_emp()
{
	//判断文件是否为空
	if (this->is_file_empty)
	{
		cout << "文件不能存在或者记录为空" << endl;
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

//判断某个职工是否存在
int WorkerManager::is_exist(int id)
{
	int index = -1;//默认没找到返回-1
	for (int i = 0; i < this->_emp_num;++i)
	{
		if (this->_emp_arr[i]->_id == id)
		{
			index = i;//找到了
			break;
		}
	}
	return index;
}

//删除职工
void WorkerManager::del_emp()
{
	if (this->is_file_empty)
	{
		cout << "文件不存在or记录为空" << endl;
	}
	else
	{
		cout << "请输入要删除的职工的编号:";
		int id = 0;
		cin >> id;
		int index = this->is_exist(id);
		if (index != -1)//找到了
		{
			for (int i = index; i < this->_emp_num - 1; ++i)
			{
				//数据前移
				this->_emp_arr[i] = this->_emp_arr[i + 1];
			}
			--this->_emp_num;//更新num
			//更新到文件中
			this->save();

			cout << "删除成功" << endl;
		}
		else
		{
			cout << "没找到此职工的编号" << endl;
		}
	}

	system("pause");
	system("cls");
}

//修改职工
void WorkerManager::mod_emp()
{
	if (this->is_file_empty)
	{
		cout << "文件不存在或为空" << endl;
	}
	else
	{
		cout << "请输入职工编号" << endl;
		int id = 0;
		cin >> id;

		int ret = this->is_exist(id);
		if (ret != -1)//已找到
		{
			delete this->_emp_arr[ret];

			int new_id = 0;
			string new_name = "\0";
			int new_did = 0;
			cout << "查找到编号为：" << id << "的职工" << endl;
			cout << "请输入新的编号：" << endl;
			cin >> new_id;
			cout << "请输入新的姓名：" << endl;
			cin >> new_name;
			cout << "请输入新的岗位：" << endl;
			cout << "1.员工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
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

			//更新
			this->_emp_arr[ret] = wk;
			cout << "修改成功" << endl;

			//保存到文件中
			this->save();
		}
		else//没找到
		{
			cout << "修改失败，未查到目标信息" << endl;
		}
		system("pause");
		system("cls");
	}
}

//查找职工
void WorkerManager::find_emp()
{
	if (this->is_file_empty)
	{
		cout << "文件不存在或者记录为空" << endl;
	}
	else
	{
		cout << "请输入查找方式" << endl;
		cout << "1.按编号查找" << endl;
		cout << "2.按姓名查找" << endl;

		int choice = 0;
		cin >> choice;

		if (choice == 1)
		{
			//编号查找
			int id;
			cout << "输入职工编号" << endl;
			cin >> id;
			int ret = this->is_exist(id);
			if (ret != -1)
			{
				cout << "找到职工，信息如下：" << endl;
				this->_emp_arr[ret]->show_info();
			}
			else
			{
				cout << "没找到" << endl;
			}
		}
		else if (choice == 2)
		{
			//按姓名查
			string name;
			cout << "输入职工姓名" << endl;
			cin >> name;

			bool flag = false;
			for (int i = 0; i < this->_emp_num; ++i)
			{
				if (this->_emp_arr[i]->_name == name)
				{
					cout << "查找成功,信息如下：" << endl;
					this->_emp_arr[i]->show_info();
					flag = true;
					break;
				}
			}
			if (flag == false)
			{
				cout << "查找失败" << endl;
			}
		}
		else
		{
			cout << "输入有误" << endl;
		}
	}
	system("pause");
	system("cls");
}

//排序职工
void WorkerManager::sort_emp()
{
	if (this->is_file_empty)
	{
		cout << "文件不存在或者记录为空" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请输入排序方式" << endl;
		cout << "1.按职工号升序" << endl;
		cout << "2.按职工号降序" << endl;

		int choice = 0;
		cin >> choice;
		for (int i = 0; i < this->_emp_num; ++i)
		{
			int min_or_max = i;
			for (int j = i + 1; j < this->_emp_num; ++j)
			{
				if (choice == 1)//升序
				{
					if (this->_emp_arr[min_or_max]->_id > this->_emp_arr[j]->_id)
					{
						min_or_max = j;
					}
				}
				else//降序
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

		cout << "排序成功" << endl;
		this->save();
		this->show_emp();
	}
}

//清空
void WorkerManager::clear_emp()
{
	cout << "确定清空？(y/n)" << endl;
	char a;
	cin >> a;
	if (a == 'y')
	{
		//清空文件
		ofstream ofs;
		ofs.open(FILENAME, ios::trunc);//删除文件后重新创建
		ofs.close();

		if (this->_emp_arr != NULL)
		{
			//删除每个职工对象
			for (int i = 0; i < this->_emp_num; ++i)
			{
				delete this->_emp_arr[i];
				this->_emp_arr[i] == NULL;
			}

			//删除堆区数组指针
			delete[] this->_emp_arr;
			this->_emp_arr = NULL;
			this->_emp_num = true;
			this->is_file_empty = true;
		}
		cout << "清空成功" << endl;
		system("pause");
		system("cls");
	}
}

//退出
void WorkerManager::exit_system()
{
	cout << "期待下次使用" << endl;
	exit(0);
}