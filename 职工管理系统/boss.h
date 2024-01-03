#pragma once
#include<iostream>
#include"worker.h"
using namespace std;
class boss :public worker
{
public:
	//构造函数
	boss(int id, string name, int did);

	//显示信息
	void show_info();

	//获取岗位名称 
	string get_dep_id();
};