//��ͨԱ���ļ�
#pragma once
#include<iostream> 
#include"worker.h"
using namespace std;

class employee :public worker
{
public:
	//���캯��
	employee(int id,string name,int did);
	

	//��ʾ��Ϣ
	void show_info();

	//��ȡ��λ���� 
	string get_dep_id();
};