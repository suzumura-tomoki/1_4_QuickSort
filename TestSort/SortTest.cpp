#include "pch.h"

#include "../���C���v���W�F�N�g/main.h"

namespace ex01_DataStructure
{
	namespace chapter2
	{
		//=================================== �O���[�o���ϐ� ===================================

		/**
		 * @brief �f�[�^����X�R�A�����o����int�^�ɕϊ�����֐��I�u�W�F�N�g
		 * @param[in] data ���X�g�Ɋi�[���Ă���f�[�^
		 * @return int�^�ɕϊ������X�R�A
		 */
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


		//=================================== ���X�g�̃\�[�g ===================================

		//�蓮�e�X�g�@�R���p�C���G���[�ƂȂ�ΐ���
		//#define SORT_TEST_KEY_IS_IRREGULAR //�e�X�g�V
		//#define SORT_CONST_LIST //�e�X�g�W


		/**********************************************************************************//**
			@brief		���X�g����ł���ꍇ�̃\�[�g�@�\�̃e�X�g
			@details	ID:���X�g-�N�C�b�N�\�[�g-0\n
						�����N����Ȃ���ΐ����ł�\n
		*//***********************************************************************************/
		TEST(SortTest, TestWhenEmpty) {
			DoublyLinkedList<ResultData> list;
			auto fpGetName = [](ResultData& data) {return data.name; };
			list.Sort<std::string>(DoublyLinkedList<ResultData>::SortOrder::ASCENDING_ORDER, fpGetName);
			EXPECT_EQ(0, list.GetSize());
		}

		/**********************************************************************************//**
			@brief		���X�g�ɗv�f��1����ꍇ�̃\�[�g�@�\�̃e�X�g
			@details	ID:���X�g-�N�C�b�N�\�[�g-1\n
						�����N����Ȃ���ΐ����ł�\n
		*//***********************************************************************************/
		TEST(SortTest, TestWhenOneData) {
			DoublyLinkedList<ResultData> list;

			//�v�f��1�p�ӂ���
			ResultData data;
			data.name = "test";
			list.Insert(list.GetBegin(), data);

			auto fpGetName = [](ResultData& data) {return data.name; };
			list.Sort<std::string>(DoublyLinkedList<ResultData>::SortOrder::ASCENDING_ORDER, fpGetName);

			EXPECT_EQ(1, list.GetSize());
			EXPECT_EQ(data.name, list.GetBegin()->name);
		}

		/**********************************************************************************//**
			@brief		���X�g�ɗv�f����������ꍇ�̃\�[�g�@�\�̃e�X�g
			@details	ID:���X�g-�N�C�b�N�\�[�g-2\n
						�w��ʂ�Ƀ\�[�g����Ă���ΐ����ł�\n
		*//***********************************************************************************/
		TEST(SortTest, TestWhenMultipleData) {
			DoublyLinkedList<ResultData> list;

			//�v�f��2�p�ӂ���
			ResultData data1 = { "10", "a" };
			ResultData data2 = { "20", "b" };

			DoublyLinkedList<ResultData>::Iterator it = list.GetBegin();
			list.Insert(it, data1);
			list.Insert(it, data2);

			//�����@�X�R�A
			list.Sort<int>(DoublyLinkedList<ResultData>::SortOrder::ASCENDING_ORDER, fpGetScore);
			EXPECT_EQ(data1.score, it->score);

			//�����@���O
			auto fpGetName = [](ResultData& data) {return data.name; };
			list.Sort<std::string>(DoublyLinkedList<ResultData>::SortOrder::ASCENDING_ORDER, fpGetName);
			EXPECT_EQ(data1.name, it->name);

			//�~���@�X�R�A
			list.Sort<int>(DoublyLinkedList<ResultData>::SortOrder::DESCENDING_ORDER, fpGetScore);
			EXPECT_EQ(data2.score, it->score);

			//�~���@���O
			list.Sort<std::string>(DoublyLinkedList<ResultData>::SortOrder::DESCENDING_ORDER, fpGetName);
			EXPECT_EQ(data2.name, it->name);
		}

		/**********************************************************************************//**
			@brief		���X�g�ɓ����L�[�����v�f������ꍇ�̃\�[�g�@�\�̃e�X�g
			@details	ID:���X�g-�N�C�b�N�\�[�g-3\n
						�����L�[�����v�f�������Ďw��ʂ�Ƀ\�[�g����Ă���ΐ����ł�\n
		*//***********************************************************************************/
		TEST(SortTest, TestWhenSameData) {
			DoublyLinkedList<ResultData> list;

			//�v�f��3�p�ӂ���
			ResultData data1 = { "10", "a" };
			ResultData data2 = { "20", "b" };

			DoublyLinkedList<ResultData>::Iterator it = list.GetBegin();
			list.Insert(it, data1);//����
			list.Insert(it, data1);//����
			list.Insert(it, data2);

			//�����@�X�R�A
			list.Sort<int>(DoublyLinkedList<ResultData>::SortOrder::ASCENDING_ORDER, fpGetScore);
			EXPECT_EQ(data2.score, (list.GetEnd() - 1)->score);

			//�����@���O
			auto fpGetName = [](ResultData& data) {return data.name; };
			list.Sort<std::string>(DoublyLinkedList<ResultData>::SortOrder::ASCENDING_ORDER, fpGetName);
			EXPECT_EQ(data2.name, (list.GetEnd() - 1)->name);

			//�~���@�X�R�A
			list.Sort<int>(DoublyLinkedList<ResultData>::SortOrder::DESCENDING_ORDER, fpGetScore);
			EXPECT_EQ(data2.score, list.GetBegin()->score);

			//�~���@���O
			list.Sort<std::string>(DoublyLinkedList<ResultData>::SortOrder::DESCENDING_ORDER, fpGetName);
			EXPECT_EQ(data2.name, list.GetBegin()->name);
		}

		/**********************************************************************************//**
			@brief		���X�g���\�[�g�ς݂̏ꍇ�̃\�[�g�@�\�̃e�X�g
			@details	ID:���X�g-�N�C�b�N�\�[�g-4\n
						�����L�[�����v�f�������āA�ϓ����Ă��Ȃ���ΐ����ł�\n
		*//***********************************************************************************/
		TEST(SortTest, TestWhenSorted) {
			DoublyLinkedList<ResultData> list;
		
			auto fpGetName = [](ResultData& data) {return data.name; };

			//�v�f��3�p�ӂ���
			ResultData data1 = { "10", "a" };
			ResultData data2 = { "20", "b" };

			DoublyLinkedList<ResultData>::Iterator it = list.GetBegin();
			list.Insert(it, data1);//����
			list.Insert(it, data1);//����
			list.Insert(it, data2);

			//�����@�X�R�A
			list.Sort<int>(DoublyLinkedList<ResultData>::SortOrder::ASCENDING_ORDER, fpGetScore);
			EXPECT_EQ(data2.score, (list.GetEnd() - 1)->score);
			//�����@�X�R�A�@2���
			list.Sort<int>(DoublyLinkedList<ResultData>::SortOrder::ASCENDING_ORDER, fpGetScore);
			EXPECT_EQ(data2.score, (list.GetEnd() - 1)->score);

			//�����@���O
			list.Sort<std::string>(DoublyLinkedList<ResultData>::SortOrder::ASCENDING_ORDER, fpGetName);
			EXPECT_EQ(data2.name, (list.GetEnd() - 1)->name);
			//�����@���O�@2���
			list.Sort<std::string>(DoublyLinkedList<ResultData>::SortOrder::ASCENDING_ORDER, fpGetName);
			EXPECT_EQ(data2.name, (list.GetEnd() - 1)->name);

			//�~���@�X�R�A
			list.Sort<int>(DoublyLinkedList<ResultData>::SortOrder::DESCENDING_ORDER, fpGetScore);
			EXPECT_EQ(data2.score, list.GetBegin()->score);
			//�~���@�X�R�A�@2���
			list.Sort<int>(DoublyLinkedList<ResultData>::SortOrder::DESCENDING_ORDER, fpGetScore);
			EXPECT_EQ(data2.score, list.GetBegin()->score);

			//�~���@���O
			list.Sort<std::string>(DoublyLinkedList<ResultData>::SortOrder::DESCENDING_ORDER, fpGetName);
			EXPECT_EQ(data2.name, list.GetBegin()->name);
			//�~���@���O�@2���
			list.Sort<std::string>(DoublyLinkedList<ResultData>::SortOrder::DESCENDING_ORDER, fpGetName);
			EXPECT_EQ(data2.name, list.GetBegin()->name);

		}

		/**********************************************************************************//**
			@brief		���񂵂����X�g�̊e���ɑ}�����A�ēx�\�[�g�����ꍇ�̃\�[�g�@�\�̃e�X�g
			@details	ID:���X�g-�N�C�b�N�\�[�g-5\n
						�w��ʂ�Ƀ\�[�g����Ă���ΐ����ł�\n
		*//***********************************************************************************/
		TEST(SortTest, TestWhenAfterSortAndInsert) {
			DoublyLinkedList<ResultData> list;
			
			auto fpGetName = [](ResultData& data) {return data.name; };

			//�v�f��2�p�ӂ���
			ResultData data10 = { "10", "d" };
			ResultData data20 = { "20", "e" };

			DoublyLinkedList<ResultData>::Iterator it = list.GetBegin();
			list.Insert(it, data10);
			list.Insert(it, data20);

			//�}���p�̗v�f
			ResultData data1 = { "1", "a" };
			ResultData data2 = { "2", "b" };
			ResultData data3 = { "3", "c" };

			//4�p�^�[��
			//�����@�X�R�A
			list.Sort<int>(DoublyLinkedList<ResultData>::SortOrder::ASCENDING_ORDER, fpGetScore);
			EXPECT_EQ(data20.score, (list.GetEnd() - 1)->score);

			//�擪�A�����A�����ɑ}��
			list.Insert(it, data1);
			list.Insert(it + 2, data2);
			list.Insert(list.GetEnd(), data3);

			//�����@�X�R�A�@2���
			list.Sort<int>(DoublyLinkedList<ResultData>::SortOrder::ASCENDING_ORDER, fpGetScore);
			EXPECT_EQ(data1.score, it->score);
			EXPECT_EQ(data2.score, (++it)->score);
			EXPECT_EQ(data3.score, (++it)->score);
			EXPECT_EQ(data10.score, (++it)->score);
			EXPECT_EQ(data20.score, (++it)->score);

			//�}�������f�[�^�̍폜
			for (int i = 0; i < 3; i++) {
				list.Delete(list.GetBegin());
			}

			//2/4
			//�����@���O
			list.Sort<std::string>(DoublyLinkedList<ResultData>::SortOrder::ASCENDING_ORDER, fpGetName);
			EXPECT_EQ(data20.name, (list.GetEnd() - 1)->name);

			//�擪�A�����A�����ɑ}��
			list.Insert(list.GetBegin(), data1);
			list.Insert(list.GetBegin() + 2, data2);
			list.Insert(list.GetEnd(), data3);

			//�����@���O�@2���
			list.Sort<std::string>(DoublyLinkedList<ResultData>::SortOrder::ASCENDING_ORDER, fpGetName);
			it = list.GetBegin();
			EXPECT_EQ(data1.score, it->score);
			EXPECT_EQ(data2.score, (++it)->score);
			EXPECT_EQ(data3.score, (++it)->score);
			EXPECT_EQ(data10.score, (++it)->score);
			EXPECT_EQ(data20.score, (++it)->score);

			//�}�������f�[�^�̍폜
			for (int i = 0; i < 3; i++) {
				list.Delete(list.GetBegin());
			}

			//3/4
			//�~���@�X�R�A
			list.Sort<int>(DoublyLinkedList<ResultData>::SortOrder::DESCENDING_ORDER, fpGetScore);
			EXPECT_EQ(data20.score, list.GetBegin()->score);

			//�擪�A�����A�����ɑ}��
			list.Insert(list.GetBegin(), data1);
			list.Insert(list.GetBegin() + 2, data2);
			list.Insert(list.GetEnd(), data3);

			//�~���@�X�R�A�@2���
			list.Sort<int>(DoublyLinkedList<ResultData>::SortOrder::DESCENDING_ORDER, fpGetScore);
			it = list.GetEnd() - 1;
			EXPECT_EQ(data1.score, it->score);
			EXPECT_EQ(data2.score, (--it)->score);
			EXPECT_EQ(data3.score, (--it)->score);
			EXPECT_EQ(data10.score, (--it)->score);
			EXPECT_EQ(data20.score, (--it)->score);

			//�}�������f�[�^�̍폜
			for (int i = 0; i < 3; i++) {
				list.Delete(list.GetEnd() - 1);
			}

			//4/4
			//�~���@���O
			list.Sort<std::string>(DoublyLinkedList<ResultData>::SortOrder::DESCENDING_ORDER, fpGetName);
			EXPECT_EQ(data20.name, list.GetBegin()->name);

			//�擪�A�����A�����ɑ}��
			list.Insert(list.GetBegin(), data1);
			list.Insert(list.GetBegin() + 2, data2);
			list.Insert(list.GetEnd(), data3);

			//�~���@���O�@2���
			list.Sort<std::string>(DoublyLinkedList<ResultData>::SortOrder::DESCENDING_ORDER, fpGetName);
			it = list.GetEnd() - 1;
			EXPECT_EQ(data1.score, it->score);
			EXPECT_EQ(data2.score, (--it)->score);
			EXPECT_EQ(data3.score, (--it)->score);
			EXPECT_EQ(data10.score, (--it)->score);
			EXPECT_EQ(data20.score, (--it)->score);

		}

		/**********************************************************************************//**
			@brief		�L�[�w������Ȃ�����(nullptr��n����)�ꍇ�̃\�[�g�@�\�̃e�X�g
			@details	ID:���X�g-�N�C�b�N�\�[�g-6\n
						�����N����Ȃ���ΐ����ł�\n
		*//***********************************************************************************/
		TEST(SortTest, TestKeyIsNull) {
			DoublyLinkedList<ResultData> list;

			list.Sort<std::string>(DoublyLinkedList<ResultData>::SortOrder::ASCENDING_ORDER, nullptr);
		}

		/**********************************************************************************//**
			@brief		�L�[���s�K�؂ȏꍇ�̃\�[�g�@�\�̃e�X�g
			@details	ID:���X�g-�N�C�b�N�\�[�g-7\n
						�L�[�̌^���e���v���[�g�����ƈ����ňقȂ�ꍇ�̃e�X�g
						�R���p�C���G���[�ƂȂ�ΐ����ł�\n
		*//***********************************************************************************/
		TEST(SortTest, TestKeyIsIrregular) {
//#define SORT_TEST_KEY_IS_IRREGULAR
#ifdef SORT_TEST_KEY_IS_IRREGULAR
			DoublyLinkedList<ResultData> list;

			//�L�[�̌^���e���v���[�g�����ƈ����ňقȂ�
			list.Sort<int>(DoublyLinkedList<ResultData>::SortOrder::ASCENDING_ORDER, [](ResultData& data) {return data.name; });
#else
			SUCCEED();
#endif // SORT_TEST_KEY_IS_IRREGULAR
	}

		/**********************************************************************************//**
			@brief		���X�g��const�̏ꍇ�̃\�[�g�@�\�̃e�X�g
			@details	ID:���X�g-�N�C�b�N�\�[�g-8\n
						�R���p�C���G���[�ƂȂ�ΐ����ł�\n
		*//***********************************************************************************/
		TEST(SortTest, TestWhenConstList) {
//#define SORT_CONST_LIST
#ifdef SORT_CONST_LIST
			const DoublyLinkedList<ResultData> list;

			list.Sort<int>(DoublyLinkedList<ResultData>::SortOrder::ASCENDING_ORDER, fpGetScore);
#else
			SUCCEED();
#endif // SORT_CONST_LIST
}

	}//namespace chapter2
}//namespace ex01_DataStructure