#include"employee.h"
void employee::show_info()
{
	cout << "ְ����ţ�" << this->_id
		<< "\tְ��������" << this->_name
		<< "\t��λ��" << this->get_dep_id()
		<< "\t��λְ����ɾ��������" << endl;
}

string employee::get_dep_id()
{
	return string("Ա��");
}

employee::employee(int id, string name, int did)
{
	this->_id = id;
	this->_name = name;
	this->_dep_id = did;
}
