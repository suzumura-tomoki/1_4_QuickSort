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

			data.score *= 10;
			data.score += readCharacter - '0';
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

	//�\�[�g���ďo��

	//�\�[�g����L�[���w�肷��֐��I�u�W�F�N�g
	auto fpGetName = [](ResultData& data) {return data.name; };
	auto fpGetScore = [](ResultData& data) {return data.score; };

	//�����̃C�e���[�^
	const DoublyLinkedList<ResultData>::Iterator END = list.GetEnd();

	list.Sort<int>(DoublyLinkedList<ResultData>::SortOrder::ASCENDING_ORDER, fpGetScore);
	printf("\n�X�R�A����\n\n");
	//�\�[�g�����f�[�^���o��
	for (it = list.GetBegin(); it != END; it++) {
		printf(std::to_string(it->score).c_str());
		printf("  ");
		printf(it->name.c_str());
		printf("\n");
	}

	list.Sort<int>(DoublyLinkedList<ResultData>::SortOrder::DESCENDING_ORDER, fpGetScore);
	printf("\n\n�X�R�A�~��\n\n");
	//�\�[�g�����f�[�^���o��
	for (it = list.GetBegin(); it != END; it++) {
		printf(std::to_string(it->score).c_str());
		printf("  ");
		printf(it->name.c_str());
		printf("\n");
	}

	list.Sort<std::string>(DoublyLinkedList<ResultData>::SortOrder::ASCENDING_ORDER, fpGetName);
	//�\�[�g�����f�[�^���o��
	printf("\n\n���O����\n\n");
	for (it = list.GetBegin(); it != END; it++) {
		printf(std::to_string(it->score).c_str());
		printf("  ");
		printf(it->name.c_str());
		printf("\n");
	}

	list.Sort<std::string>(DoublyLinkedList<ResultData>::SortOrder::DESCENDING_ORDER, fpGetName);
	printf("\n\n���O�~��\n\n");
	//�\�[�g�����f�[�^���o��
	for (it = list.GetBegin(); it != END; it++) {
		printf(std::to_string(it->score).c_str());
		printf("  ");
		printf(it->name.c_str());
		printf("\n");
	}

	printf("\n���s:ENTER\n");
	rewind(stdin);
	getchar();


	return 0;
}