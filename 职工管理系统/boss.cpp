#include"boss.h"
//���캯��
boss::boss(int id, string name, int did)
{
	this->_id = id;
	this->_name = name;
	this->_dep_id = did;
}

//��ʾ��Ϣ
void boss::show_info()
{
	cout << "ְ����ţ�" << this->_id
		<< "\tְ��������" << this->_name
		<< "\t��λ��" << this->get_dep_id()
		<< "\t��λְ�𣺹���˾��������" << endl;
}

//��ȡ��λ���� 
string boss::get_dep_id()
{
	return string("�ϰ�");
}