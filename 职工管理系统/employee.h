//普通员工文件
#pragma once
#include<iostream> 
#include"worker.h"
using namespace std;

class employee :public worker
{
public:
	//构造函数
	employee(int id,string name,int did);
	

	//显示信息
	void show_info();

	//获取岗位名称 
	string get_dep_id();
};