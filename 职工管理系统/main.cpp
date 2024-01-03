#include"workerManager.h"//管理

#include"worker.h"//worker是下面三个的抽象

#include"employee.h"
#include"boss.h"
#include"manager.h"
int main()
{
	//实例化管理者对象
	WorkerManager wm;
	
	while (1)
	{
		wm.show_menu();
		cout << "Make your choice" << endl;
		int choice;
		cin >> choice;
		switch (choice)
		{
		case 0://退出
			wm.exit_system();
			break;
		case 1://添加职工
			wm.add_emp();
			break;
		case 2://显示
			wm.show_emp();
			break;
		case 3://删除
			wm.del_emp();
			break;
		case 4://修改
			wm.mod_emp();
			break;
		case 5://查找
			wm.find_emp();
			break;
		case 6://排序
			wm.sort_emp();
			break;
		case 7://清空
			wm.clear_emp();
			break;
		default://无效数字清屏
			system("cls");
			break;
		}

	}

	return 0;
}