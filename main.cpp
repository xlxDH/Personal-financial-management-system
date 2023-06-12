#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>
#include <time.h>

using namespace std;

string local_time(){
	time_t now = time(NULL);
	tm* tm_t = localtime(&now);
	std::stringstream ss;
	ss << tm_t->tm_year + 1900 << "-" << tm_t->tm_mon + 1 << "-" << tm_t->tm_mday	<< "-" << tm_t->tm_hour << "-" << tm_t->tm_min << "-" << tm_t->tm_sec << endl;
	return ss.str();
}

int get_sum(char buf[]){
	int sum = 0;
	int idx = 0;
	while(buf[idx]){
		sum = sum * 10 + (buf[idx]-'0');
		idx ++;
	}
	return sum;
}

void sum_income_outcome(){
	ifstream ifs;
	ifs.open("income.txt",ios::in);
	char buf[1024] = {0};
	int sum1 = 0;
	int t = 0;
	while(ifs>>buf){
		t++;
		if(t%2==0){
			sum1 += get_sum(buf);
		}
		else continue;
	}
	ifs.close();

	ifs.open("outcome.txt",ios::in);
	int sum2 = 0;
	t = 0;
	while(ifs>>buf){
		t++;
		if(t%2==0){
			sum2 += get_sum(buf);
		}
		else continue;
	}
	ifs.close();
	
	ofstream ofs;

	ofs.open("data.txt",ios::out);
    ofs << "总收入：" << sum1 << endl;
    ofs << "总支出：" << sum2 << endl;
    ofs << "余额：" << sum1 - sum2 << endl;
    ofs.close();
}

void income(int sum){
	ofstream ofs;
	ofs.open("income.txt",ios::app);
		ofs << local_time();
		ofs<< sum << endl << endl;
	ofs.close();
}

void outcome(int sum){
	ofstream ofs;
	ofs.open("outcome.txt",ios::app);
		ofs<< local_time();
		ofs<< sum << endl << endl;
	ofs.close();
}

void show_data(){
	ifstream ifs;
	ifs.open("income.txt",ios::in);
	if(!ifs.is_open()){
		cout << "读取账单失败" << endl;
		return;
	}
	cout << "\t收入" << endl;
	char buf[1024] = {0};
	while(ifs>>buf){
		cout << buf << endl;
	}
	ifs.close();
	
	ifs.open("outcome.txt",ios::in);
	if(!ifs.is_open()){
		cout << "读取账单失败" << endl;
		return;
	}
	cout << "\t支出" << endl;

	while(ifs>>buf){
		cout << buf << endl;
	}
	ifs.close();
	
	sum_income_outcome();
	
	ifs.open("data.txt",ios::in);
	if(!ifs.is_open()){
		cout << "读取账单失败" << endl;
		return;
	}
	cout << "\t总账单" << endl;

	while(ifs>>buf){
		cout << buf << endl;
	}

}

int main()
{
	

    bool exit_flag = false;
    while (!exit_flag)
    {
	cout << "************个人金融管理系统*************\n**************菜单界面*******************" << endl;


    vector<string> menu = {"\t   1. 添加收入", "\t   2. 添加支出", "\t   3. 显示账单", "\t   4. 退出系统"};

        for (string item : menu)
        {
            cout << item << endl;
        }

		cout << "请输入操作：";
        int choice;
        cin >> choice;
		if(choice>10||choice<0){
			cout << "\t   无效的选项，请重新输入！" << endl;
			continue;
		}
		
		
        switch (choice)
        {
            case 1:
            	cout << "请输入收入：";
				int sum;
				cin >> sum;
            	income(sum);
                // 添加收入
                break;
            case 2:
                // 添加支出
                cout << "请输入支出：";
                int s;
                cin >> s;
                outcome(s);
                break;
            case 3:
                // 显示账单
				show_data();
				
                break;
            case 4:
                // 退出
                exit_flag = true;
                break;
            default:
                cout << "\t   无效的选项，请重新输入！" << endl;
                break;
        }
    }

    return 0;
}

