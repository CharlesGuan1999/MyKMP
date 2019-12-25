/* 
 KMP算法 C++实现
 
 主要算法：
 1.求next数组算法： 找到前方最大匹配前缀、后缀（递归寻找）
 2.使用next数组，快速匹配子串 ---> 不匹配，但有匹配前缀i不动，j回溯至next[j];无匹配前缀，i后移，j置0
*/

#include <iostream>
using namespace std;

//Next数组
int* Next(string target) {
	//Next数组
	int* next = new int[target.length()];

	//首元素赋值为-1
	next[0] = -1;
	
	//循环变量
	int i = 0;
	int k,tag;
	
	//循坏求求next[i+1]
	while (i+1 < (int)target.length()) {
		//情况1:：i+1位置的字符和next[i]位置的字符匹配，则next[i+1] = next[i] + 1
		//情况2：如果以上字符不匹配，则递归向前寻找是否有更小的匹配前缀
		k = next[i];
		tag = 0;
		while (k != -1) {
			if (target[k] == target[i]) {
				next[i + 1] = k + 1;
				tag = 1;
				break;
			}
			k = next[k];
		}
		if (tag == 0) next[i+1] = 0;
		i++;
	}
	return next;
}

//KMP算法
int KMP(string Base, string target){
	//空串直接返回
	if (target.length() == 0||Base.length() == 0) {
		return -1;
	}

	int* next = Next(target);
	//可视化next数组
	cout << "Next: ";
	for (int i = 0; i < target.length(); i++) {
		cout << next[i] << " ";
	}
	std::cout << "OK";

	//Base数组索引
	int i = 0;

	//target数组索引
	int j = 0;

	//主串未结束时继续匹配
	while (i < (int)Base.length()) {
		//匹配成功返回target在base的开始位置
		if (j == (int)target.length() - 1) {
			return (i - target.length() + 1);
		}
		//匹配未结束
		//相等时匹配成功, 指针下移
		if (Base[i] == target[j]) {
			i++;
			j++;
		}
		//匹配失败
		else {
			//没有前缀匹配，从target的第一个位置匹配
			if (next[j] == -1) {
				i++;
			}
			else {
				//如果有前缀匹配
				//则i指针不移动，j指针向前移动j-next[j]
				j = next[j];
			}
		}
	}
	return -1;
}


int main()
{
	//测试用例
	int test = KMP("adsdsasacasdvafbasxaabacasabasdsadaabca", "abacasabasdsada");
	cout << endl;
	cout <<"Test: "<< test;
	return 0;
}