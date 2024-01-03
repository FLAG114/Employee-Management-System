#pragma once
#include<iostream>
using namespace std;

//抽象职工类
class worker
{
public:
	//显示信息
	virtual void show_info() = 0;

	//获取岗位名称 
	virtual string get_dep_id() = 0;

	//编号
	int _id;
	//姓名
	string _name;
	//部门编号
	int _dep_id;
};