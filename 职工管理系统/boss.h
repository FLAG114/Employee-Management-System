#pragma once
#include<iostream>
#include"worker.h"
using namespace std;
class boss :public worker
{
public:
	//���캯��
	boss(int id, string name, int did);

	//��ʾ��Ϣ
	void show_info();

	//��ȡ��λ���� 
	string get_dep_id();
};