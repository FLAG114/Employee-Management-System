#include"boss.h"
//构造函数
boss::boss(int id, string name, int did)
{
	this->_id = id;
	this->_name = name;
	this->_dep_id = did;
}

//显示信息
void boss::show_info()
{
	cout << "职工编号：" << this->_id
		<< "\t职工姓名：" << this->_name
		<< "\t岗位：" << this->get_dep_id()
		<< "\t岗位职责：管理公司所有任务" << endl;
}

//获取岗位名称 
string boss::get_dep_id()
{
	return string("老板");
}