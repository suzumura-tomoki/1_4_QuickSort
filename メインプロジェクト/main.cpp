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

	while (ifsScoreFile.eof() == false)
	{
		//�t�@�C���̓ǂݎ��

		ResultData data{};
		std::string readString{};

		//�X�R�A�̓ǂݍ���
		std::getline(ifsScoreFile, readString, '\t');

		//�t�@�C���I�[�̉��s�𖳎�
		if (ifsScoreFile.eof())
		{
			break;
		}

		//�����̕�����𐮐��l�ɕϊ�
		data.score = std::stoi(readString);


		//���O�̓ǂݍ���
		//ResultData�ɒ��ړǂݍ���
		std::getline(ifsScoreFile, data.name, '\n');

		//�t�@�C���I�[�̉��s�𖳎�
		if (ifsScoreFile.eof())
		{
			break;
		}

		//�ǂݎ�����f�[�^�̑}��
		it = list.GetEnd();
		list.Insert(it, data);
	}

	ifsScoreFile.close();

	//�\�[�g���ďo��

	//�\�[�g����L�[���w�肷��֐��I�u�W�F�N�g
	auto fpGetName = [](const ResultData& data) ->const std::string& {return data.name; };
	auto fpGetScore = [](const ResultData& data) ->const int& {return data.score; };

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