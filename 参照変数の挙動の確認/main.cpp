#include<iostream>

int main() {

	//�Q�ƂɎQ�Ƃɂ������������̋����̊m�F
	//���ʁA�Q�Ɛ�͕ς�炸�l�̑���̂ݍs����

	int a = 0;
	int& refA = a;

	int b = 2;
	int& refB = b;

	refB = refA;//���̋���

	a = 1;

	std::cout << "a " << a << "\nrefA " << refA << "\nb " << b << "\nrefB " << refB << std::endl;

	getchar();
	return 0;
}