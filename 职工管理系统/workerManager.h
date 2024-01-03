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
	//记录职工人数
	int _emp_num;

	//职工数组指针
	worker** _emp_arr;

	//文件是否为空
	bool is_file_empty;

	//成员↑
	//函数↓

	//构造&析构
	WorkerManager();
	~WorkerManager();

	//展示菜单
	void show_menu();

	//添加
	void add_emp();

	//保存文件 
	void save();

	//显示职工
	void show_emp();

	//判断某个职工是否存在
	int is_exist(int id);

	//删除职工
	void del_emp();

	//修改职工
	void mod_emp();

	//统计文件中人数
	int get_emp_num();

	//查找职工
	void find_emp();

	//排序职工
	void sort_emp();
	
	//初始化员工
	void init_emp();

	//清空
	void clear_emp();

	//退出
	void exit_system();

};