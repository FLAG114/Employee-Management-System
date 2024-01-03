#pragma once
#include<iostream>
#include"worker.h"
#include"boss.h"
#include"employee.h"
#include"manager.h"
#include<fstream>
#define FILENAME "empFile.txt" 
using namespace std;
class WorkerManager
{
public:
	//��¼ְ������
	int _emp_num;

	//ְ������ָ��
	worker** _emp_arr;

	//�ļ��Ƿ�Ϊ��
	bool is_file_empty;

	//��Ա��
	//������

	//����&����
	WorkerManager();
	~WorkerManager();

	//չʾ�˵�
	void show_menu();

	//���
	void add_emp();

	//�����ļ� 
	void save();

	//��ʾְ��
	void show_emp();

	//�ж�ĳ��ְ���Ƿ����
	int is_exist(int id);

	//ɾ��ְ��
	void del_emp();

	//�޸�ְ��
	void mod_emp();

	//ͳ���ļ�������
	int get_emp_num();

	//����ְ��
	void find_emp();

	//����ְ��
	void sort_emp();
	
	//��ʼ��Ա��
	void init_emp();

	//���
	void clear_emp();

	//�˳�
	void exit_system();

};