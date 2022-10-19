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

	//スコア読み込み
	while (ifsScoreFile.eof() == false)
	{
		ResultData data{};

		//ファイルの読み取り
		char readCharacter;
		while (true)
		{
			ifsScoreFile.get(readCharacter);

			//ファイル終端の改行を無視
			if (ifsScoreFile.eof())
			{
				break;
			}

			if (readCharacter == ' ')
			{
				break;
			}
			if (readCharacter == '　')
			{
				break;
			}
			if (readCharacter == '\t')
			{
				break;
			}

			data.score *= 10;
			data.score += readCharacter - '0';
		}

		while (true)
		{
			ifsScoreFile.get(readCharacter);

			//ファイル終端の改行を無視
			if (ifsScoreFile.eof())
			{
				break;
			}

			if (readCharacter == '\n')
			{
				break;
			}
			data.name += readCharacter;

		}

		//ファイル終端を無視
		if (ifsScoreFile.eof()) {
			break;
		}

		//読み取ったデータの挿入
		it = list.GetEnd();
		list.Insert(it, data);
	}

	ifsScoreFile.close();

	//ソートして出力

	//ソートするキーを指定する関数オブジェクト
	auto fpGetName = [](ResultData& data) {return data.name; };
	auto fpGetScore = [](ResultData& data) {return data.score; };

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