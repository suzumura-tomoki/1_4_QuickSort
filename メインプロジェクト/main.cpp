#include<fstream>
#include"main.h"

int main() {

	std::ifstream ifsScoreFile;
	ifsScoreFile.open("Scores.txt");

	if (!ifsScoreFile) {
		printf("ファイルを開けませんでした");
		getchar();
		return 1;
	}

	DoublyLinkedList<ResultData> list;
	DoublyLinkedList<ResultData>::Iterator it;

	while (ifsScoreFile.eof() == false)
	{
		//ファイルの読み取り

		ResultData data{};
		std::string readString{};

		//スコアの読み込み
		std::getline(ifsScoreFile, readString, '\t');

		//ファイル終端の改行を無視
		if (ifsScoreFile.eof())
		{
			break;
		}

		//数字の文字列を整数値に変換
		data.score = std::stoi(readString);


		//名前の読み込み
		//ResultDataに直接読み込む
		std::getline(ifsScoreFile, data.name, '\n');

		//ファイル終端の改行を無視
		if (ifsScoreFile.eof())
		{
			break;
		}

		//読み取ったデータの挿入
		it = list.GetEnd();
		list.Insert(it, data);
	}

	ifsScoreFile.close();

	//ソートして出力

	//ソートするキーを指定する関数オブジェクト
	auto fpGetName = [](const ResultData& data) ->const std::string& {return data.name; };
	auto fpGetScore = [](const ResultData& data) ->const int& {return data.score; };

	//末尾のイテレータ
	const DoublyLinkedList<ResultData>::Iterator END = list.GetEnd();

	list.Sort<int>(DoublyLinkedList<ResultData>::SortOrder::ASCENDING_ORDER, fpGetScore);
	printf("\nスコア昇順\n\n");
	//ソートしたデータを出力
	for (it = list.GetBegin(); it != END; it++) {
		printf(std::to_string(it->score).c_str());
		printf("  ");
		printf(it->name.c_str());
		printf("\n");
	}

	list.Sort<int>(DoublyLinkedList<ResultData>::SortOrder::DESCENDING_ORDER, fpGetScore);
	printf("\n\nスコア降順\n\n");
	//ソートしたデータを出力
	for (it = list.GetBegin(); it != END; it++) {
		printf(std::to_string(it->score).c_str());
		printf("  ");
		printf(it->name.c_str());
		printf("\n");
	}

	list.Sort<std::string>(DoublyLinkedList<ResultData>::SortOrder::ASCENDING_ORDER, fpGetName);
	//ソートしたデータを出力
	printf("\n\n名前昇順\n\n");
	for (it = list.GetBegin(); it != END; it++) {
		printf(std::to_string(it->score).c_str());
		printf("  ");
		printf(it->name.c_str());
		printf("\n");
	}

	list.Sort<std::string>(DoublyLinkedList<ResultData>::SortOrder::DESCENDING_ORDER, fpGetName);
	printf("\n\n名前降順\n\n");
	//ソートしたデータを出力
	for (it = list.GetBegin(); it != END; it++) {
		printf(std::to_string(it->score).c_str());
		printf("  ");
		printf(it->name.c_str());
		printf("\n");
	}

	printf("\n続行:ENTER\n");
	rewind(stdin);
	getchar();


	return 0;
}