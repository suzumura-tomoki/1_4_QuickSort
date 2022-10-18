#include<fstream>
#include"main.h"

int main() {

	std::ifstream ifsScoreFile;
	ifsScoreFile.open("Scores.txt");

	if (!ifsScoreFile) {
		printf("�t�@�C�����J���܂���ł���");
		getchar();
		return 1;
	}

	DoublyLinkedList<ResultData> list;
	DoublyLinkedList<ResultData>::Iterator it;

	//�X�R�A�ǂݍ���
	while (ifsScoreFile.eof() == false)
	{
		ResultData data{};

		//�t�@�C���̓ǂݎ��
		char readCharacter;
		while (true)
		{
			ifsScoreFile.get(readCharacter);

			//�t�@�C���I�[�̉��s�𖳎�
			if (ifsScoreFile.eof())
			{
				break;
			}

			if (readCharacter == ' ')
			{
				break;
			}
			if (readCharacter == '�@')
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

			//�t�@�C���I�[�̉��s�𖳎�
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

		//�t�@�C���I�[�𖳎�
		if (ifsScoreFile.eof()) {
			break;
		}

		//�ǂݎ�����f�[�^�̑}��
		it = list.GetEnd();
		list.Insert(it, data);
	}

	ifsScoreFile.close();


	//=========���C�����[�v=========
	
	//�\�[�g����L�[���w�肷��֐��I�u�W�F�N�g
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

		//�I�[�_�[�̑I��
		printf("�\�[�g����I�����Ă�������\n ����:0 �~��:1 �I��:2\n");
		int inputOrder;
		scanf_s("%d", &inputOrder);
		if (inputOrder == 2) {
			break;
		}
		if (inputOrder != 0 && inputOrder != 1) {
			continue;
		}

		//�L�[�̑I��
		printf("�L�[��I�����Ă�������\n ���O:0 �X�R�A:1\n");
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

		//�\�[�g�����f�[�^���o��
		const DoublyLinkedList<ResultData>::Iterator end = list.GetEnd();
		for (it = list.GetBegin(); it != end; it++) {
			printf(it->score.c_str());
			printf("  ");
			printf(it->name.c_str());
			printf("\n");
		}

		printf("\n���s:ENTER\n");
		rewind(stdin);
		getchar();
	}
	
	return 0;
}