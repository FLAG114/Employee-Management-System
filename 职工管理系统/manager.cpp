#include"manager.h"
//构造函数
manager::manager(int id, string name, int idi)
{
	this->_id = id;
	this->_name = name;
	this->_dep_id = idi;
}

//显示信息
void manager::show_info()
{
	cout << "职工编号：" << this->_id
		<< "\t职工姓名：" << this->_name
		<< "\t岗位：" << this->get_dep_id()
		<< "\t岗位职责：完成老板的任务，并且下发任务" << endl;
}

//获取岗位名称 
string manager::get_dep_id()
{
	return string("经理");
}