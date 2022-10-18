#include<iostream>

int main() {

	//参照に参照にを代入したさいの挙動の確認
	//結果、参照先は変わらず値の代入のみ行われる

	int a = 0;
	int& refA = a;

	int b = 2;
	int& refB = b;

	refB = refA;//この挙動

	a = 1;

	std::cout << "a " << a << "\nrefA " << refA << "\nb " << b << "\nrefB " << refB << std::endl;

	getchar();
	return 0;
}