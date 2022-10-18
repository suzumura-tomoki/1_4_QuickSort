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

			data.score += readCharacter;
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


	//=========メインループ=========
	
	//ソートするキーを指定する関数オブジェクト
	auto fpGetName = [](ResultData& data) {return data.name; };
	auto fpGetScore = [](ResultData& data) {
		int score = 0;
		int length = data.score.length();
		for (size_t i = 0; i < length; i++)
		{
			score *= 10;
			score += data.score[i] - 48;
		}
		return score;
	};
	while (true)
	{
		system("cls");

		//オーダーの選択
		printf("ソート順を選択してください\n 昇順:0 降順:1 終了:2\n");
		int inputOrder;
		scanf_s("%d", &inputOrder);
		if (inputOrder == 2) {
			break;
		}
		if (inputOrder != 0 && inputOrder != 1) {
			continue;
		}

		//キーの選択
		printf("キーを選択してください\n 名前:0 スコア:1\n");
		int inputKey;
		scanf_s("%d", &inputKey);
		if (inputKey != 0 && inputKey != 1) {
			continue;
		}

		if (inputOrder == 0) {
			if (inputKey == 0) {
				list.Sort<std::string>(DoublyLinkedList<ResultData>::SortOrder::ASCENDING_ORDER, fpGetName);
			}
			else
			{
				list.Sort<int>(DoublyLinkedList<ResultData>::SortOrder::ASCENDING_ORDER, fpGetScore);
			}
		}
		else {
			if (inputKey == 0) {
				list.Sort<std::string>(DoublyLinkedList<ResultData>::SortOrder::DESCENDING_ORDER, fpGetName);
			}
			else
			{
				list.Sort<int>(DoublyLinkedList<ResultData>::SortOrder::DESCENDING_ORDER, fpGetScore);
			}
		}

		//ソートしたデータを出力
		const DoublyLinkedList<ResultData>::Iterator end = list.GetEnd();
		for (it = list.GetBegin(); it != end; it++) {
			printf(it->score.c_str());
			printf("  ");
			printf(it->name.c_str());
			printf("\n");
		}

		printf("\n続行:ENTER\n");
		rewind(stdin);
		getchar();
	}
	
	return 0;
}