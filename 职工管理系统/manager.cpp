#include"manager.h"
//���캯��
manager::manager(int id, string name, int idi)
{
	this->_id = id;
	this->_name = name;
	this->_dep_id = idi;
}

//��ʾ��Ϣ
void manager::show_info()
{
	cout << "ְ����ţ�" << this->_id
		<< "\tְ��������" << this->_name
		<< "\t��λ��" << this->get_dep_id()
		<< "\t��λְ������ϰ�����񣬲����·�����" << endl;
}

//��ȡ��λ���� 
string manager::get_dep_id()
{
	return string("����");
}