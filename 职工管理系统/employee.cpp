#include"employee.h"
void employee::show_info()
{
	cout << "职工编号：" << this->_id
		<< "\t职工姓名：" << this->_name
		<< "\t岗位：" << this->get_dep_id()
		<< "\t岗位职责：完成经理的任务" << endl;
}

string employee::get_dep_id()
{
	return string("员工");
}

employee::employee(int id, string name, int did)
{
	this->_id = id;
	this->_name = name;
	this->_dep_id = did;
}
