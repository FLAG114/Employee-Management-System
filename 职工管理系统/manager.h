#pragma once
#include<iostream>
#include"worker.h"
using namespace std;

class manager :public worker
{
public:
	//���캯��
	manager(int id, string name, int idi);

	//��ʾ��Ϣ
	void show_info();
	 
	//��ȡ��λ���� 
	string get_dep_id();
};