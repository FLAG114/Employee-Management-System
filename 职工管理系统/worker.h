#pragma once
#include<iostream>
using namespace std;

//����ְ����
class worker
{
public:
	//��ʾ��Ϣ
	virtual void show_info() = 0;

	//��ȡ��λ���� 
	virtual string get_dep_id() = 0;

	//���
	int _id;
	//����
	string _name;
	//���ű��
	int _dep_id;
};