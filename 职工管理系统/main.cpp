#include"workerManager.h"//����

#include"worker.h"//worker�����������ĳ���

#include"employee.h"
#include"boss.h"
#include"manager.h"
int main()
{
	//ʵ���������߶���
	WorkerManager wm;
	
	while (1)
	{
		wm.show_menu();
		cout << "Make your choice" << endl;
		int choice;
		cin >> choice;
		switch (choice)
		{
		case 0://�˳�
			wm.exit_system();
			break;
		case 1://���ְ��
			wm.add_emp();
			break;
		case 2://��ʾ
			wm.show_emp();
			break;
		case 3://ɾ��
			wm.del_emp();
			break;
		case 4://�޸�
			wm.mod_emp();
			break;
		case 5://����
			wm.find_emp();
			break;
		case 6://����
			wm.sort_emp();
			break;
		case 7://���
			wm.clear_emp();
			break;
		default://��Ч��������
			system("cls");
			break;
		}

	}

	return 0;
}