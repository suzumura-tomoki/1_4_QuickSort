#include "pch.h"

#include "../メインプロジェクト/main.h"

namespace ex01_DataStructure
{
	namespace chapter2
	{
		//=================================== グローバル変数 ===================================

		/**
		 * @brief データからスコアを取り出してint型に変換する関数オブジェクト
		 * @param[in] data リストに格納しているデータ
		 * @return int型に変換したスコア
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


		//=================================== リストのソート ===================================

		//手動テスト　コンパイルエラーとなれば成功
		//#define SORT_TEST_KEY_IS_IRREGULAR //テスト７
		//#define SORT_CONST_LIST //テスト８


		/**********************************************************************************//**
			@brief		リストが空である場合のソート機能のテスト
			@details	ID:リスト-クイックソート-0\n
						何も起こらなければ成功です\n
		*//***********************************************************************************/
		TEST(SortTest, TestWhenEmpty) {
			DoublyLinkedList<ResultData> list;
			auto fpGetName = [](ResultData& data) {return data.name; };
			list.Sort<std::string>(DoublyLinkedList<ResultData>::SortOrder::ASCENDING_ORDER, fpGetName);
			EXPECT_EQ(0, list.GetSize());
		}

		/**********************************************************************************//**
			@brief		リストに要素が1つある場合のソート機能のテスト
			@details	ID:リスト-クイックソート-1\n
						何も起こらなければ成功です\n
		*//***********************************************************************************/
		TEST(SortTest, TestWhenOneData) {
			DoublyLinkedList<ResultData> list;

			//要素を1つ用意する
			ResultData data;
			data.name = "test";
			list.Insert(list.GetBegin(), data);

			auto fpGetName = [](ResultData& data) {return data.name; };
			list.Sort<std::string>(DoublyLinkedList<ResultData>::SortOrder::ASCENDING_ORDER, fpGetName);

			EXPECT_EQ(1, list.GetSize());
			EXPECT_EQ(data.name, list.GetBegin()->name);
		}

		/**********************************************************************************//**
			@brief		リストに要素が複数ある場合のソート機能のテスト
			@details	ID:リスト-クイックソート-2\n
						指定通りにソートされていれば成功です\n
		*//***********************************************************************************/
		TEST(SortTest, TestWhenMultipleData) {
			DoublyLinkedList<ResultData> list;

			//要素を2つ用意する
			ResultData data1 = { "10", "a" };
			ResultData data2 = { "20", "b" };

			DoublyLinkedList<ResultData>::Iterator it = list.GetBegin();
			list.Insert(it, data1);
			list.Insert(it, data2);

			//昇順　スコア
			list.Sort<int>(DoublyLinkedList<ResultData>::SortOrder::ASCENDING_ORDER, fpGetScore);
			EXPECT_EQ(data1.score, it->score);

			//昇順　名前
			auto fpGetName = [](ResultData& data) {return data.name; };
			list.Sort<std::string>(DoublyLinkedList<ResultData>::SortOrder::ASCENDING_ORDER, fpGetName);
			EXPECT_EQ(data1.name, it->name);

			//降順　スコア
			list.Sort<int>(DoublyLinkedList<ResultData>::SortOrder::DESCENDING_ORDER, fpGetScore);
			EXPECT_EQ(data2.score, it->score);

			//降順　名前
			list.Sort<std::string>(DoublyLinkedList<ResultData>::SortOrder::DESCENDING_ORDER, fpGetName);
			EXPECT_EQ(data2.name, it->name);
		}

		/**********************************************************************************//**
			@brief		リストに同じキーを持つ要素がある場合のソート機能のテスト
			@details	ID:リスト-クイックソート-3\n
						同じキーを持つ要素を除いて指定通りにソートされていれば成功です\n
		*//***********************************************************************************/
		TEST(SortTest, TestWhenSameData) {
			DoublyLinkedList<ResultData> list;

			//要素を3つ用意する
			ResultData data1 = { "10", "a" };
			ResultData data2 = { "20", "b" };

			DoublyLinkedList<ResultData>::Iterator it = list.GetBegin();
			list.Insert(it, data1);//同じ
			list.Insert(it, data1);//同じ
			list.Insert(it, data2);

			//昇順　スコア
			list.Sort<int>(DoublyLinkedList<ResultData>::SortOrder::ASCENDING_ORDER, fpGetScore);
			EXPECT_EQ(data2.score, (list.GetEnd() - 1)->score);

			//昇順　名前
			auto fpGetName = [](ResultData& data) {return data.name; };
			list.Sort<std::string>(DoublyLinkedList<ResultData>::SortOrder::ASCENDING_ORDER, fpGetName);
			EXPECT_EQ(data2.name, (list.GetEnd() - 1)->name);

			//降順　スコア
			list.Sort<int>(DoublyLinkedList<ResultData>::SortOrder::DESCENDING_ORDER, fpGetScore);
			EXPECT_EQ(data2.score, list.GetBegin()->score);

			//降順　名前
			list.Sort<std::string>(DoublyLinkedList<ResultData>::SortOrder::DESCENDING_ORDER, fpGetName);
			EXPECT_EQ(data2.name, list.GetBegin()->name);
		}

		/**********************************************************************************//**
			@brief		リストがソート済みの場合のソート機能のテスト
			@details	ID:リスト-クイックソート-4\n
						同じキーを持つ要素を除いて、変動していなければ成功です\n
		*//***********************************************************************************/
		TEST(SortTest, TestWhenSorted) {
			DoublyLinkedList<ResultData> list;
		
			auto fpGetName = [](ResultData& data) {return data.name; };

			//要素を3つ用意する
			ResultData data1 = { "10", "a" };
			ResultData data2 = { "20", "b" };

			DoublyLinkedList<ResultData>::Iterator it = list.GetBegin();
			list.Insert(it, data1);//同じ
			list.Insert(it, data1);//同じ
			list.Insert(it, data2);

			//昇順　スコア
			list.Sort<int>(DoublyLinkedList<ResultData>::SortOrder::ASCENDING_ORDER, fpGetScore);
			EXPECT_EQ(data2.score, (list.GetEnd() - 1)->score);
			//昇順　スコア　2回目
			list.Sort<int>(DoublyLinkedList<ResultData>::SortOrder::ASCENDING_ORDER, fpGetScore);
			EXPECT_EQ(data2.score, (list.GetEnd() - 1)->score);

			//昇順　名前
			list.Sort<std::string>(DoublyLinkedList<ResultData>::SortOrder::ASCENDING_ORDER, fpGetName);
			EXPECT_EQ(data2.name, (list.GetEnd() - 1)->name);
			//昇順　名前　2回目
			list.Sort<std::string>(DoublyLinkedList<ResultData>::SortOrder::ASCENDING_ORDER, fpGetName);
			EXPECT_EQ(data2.name, (list.GetEnd() - 1)->name);

			//降順　スコア
			list.Sort<int>(DoublyLinkedList<ResultData>::SortOrder::DESCENDING_ORDER, fpGetScore);
			EXPECT_EQ(data2.score, list.GetBegin()->score);
			//降順　スコア　2回目
			list.Sort<int>(DoublyLinkedList<ResultData>::SortOrder::DESCENDING_ORDER, fpGetScore);
			EXPECT_EQ(data2.score, list.GetBegin()->score);

			//降順　名前
			list.Sort<std::string>(DoublyLinkedList<ResultData>::SortOrder::DESCENDING_ORDER, fpGetName);
			EXPECT_EQ(data2.name, list.GetBegin()->name);
			//降順　名前　2回目
			list.Sort<std::string>(DoublyLinkedList<ResultData>::SortOrder::DESCENDING_ORDER, fpGetName);
			EXPECT_EQ(data2.name, list.GetBegin()->name);

		}

		/**********************************************************************************//**
			@brief		整列したリストの各所に挿入し、再度ソートした場合のソート機能のテスト
			@details	ID:リスト-クイックソート-5\n
						指定通りにソートされていれば成功です\n
		*//***********************************************************************************/
		TEST(SortTest, TestWhenAfterSortAndInsert) {
			DoublyLinkedList<ResultData> list;
			
			auto fpGetName = [](ResultData& data) {return data.name; };

			//要素を2つ用意する
			ResultData data10 = { "10", "d" };
			ResultData data20 = { "20", "e" };

			DoublyLinkedList<ResultData>::Iterator it = list.GetBegin();
			list.Insert(it, data10);
			list.Insert(it, data20);

			//挿入用の要素
			ResultData data1 = { "1", "a" };
			ResultData data2 = { "2", "b" };
			ResultData data3 = { "3", "c" };

			//4パターン
			//昇順　スコア
			list.Sort<int>(DoublyLinkedList<ResultData>::SortOrder::ASCENDING_ORDER, fpGetScore);
			EXPECT_EQ(data20.score, (list.GetEnd() - 1)->score);

			//先頭、中央、末尾に挿入
			list.Insert(it, data1);
			list.Insert(it + 2, data2);
			list.Insert(list.GetEnd(), data3);

			//昇順　スコア　2回目
			list.Sort<int>(DoublyLinkedList<ResultData>::SortOrder::ASCENDING_ORDER, fpGetScore);
			EXPECT_EQ(data1.score, it->score);
			EXPECT_EQ(data2.score, (++it)->score);
			EXPECT_EQ(data3.score, (++it)->score);
			EXPECT_EQ(data10.score, (++it)->score);
			EXPECT_EQ(data20.score, (++it)->score);

			//挿入したデータの削除
			for (int i = 0; i < 3; i++) {
				list.Delete(list.GetBegin());
			}

			//2/4
			//昇順　名前
			list.Sort<std::string>(DoublyLinkedList<ResultData>::SortOrder::ASCENDING_ORDER, fpGetName);
			EXPECT_EQ(data20.name, (list.GetEnd() - 1)->name);

			//先頭、中央、末尾に挿入
			list.Insert(list.GetBegin(), data1);
			list.Insert(list.GetBegin() + 2, data2);
			list.Insert(list.GetEnd(), data3);

			//昇順　名前　2回目
			list.Sort<std::string>(DoublyLinkedList<ResultData>::SortOrder::ASCENDING_ORDER, fpGetName);
			it = list.GetBegin();
			EXPECT_EQ(data1.score, it->score);
			EXPECT_EQ(data2.score, (++it)->score);
			EXPECT_EQ(data3.score, (++it)->score);
			EXPECT_EQ(data10.score, (++it)->score);
			EXPECT_EQ(data20.score, (++it)->score);

			//挿入したデータの削除
			for (int i = 0; i < 3; i++) {
				list.Delete(list.GetBegin());
			}

			//3/4
			//降順　スコア
			list.Sort<int>(DoublyLinkedList<ResultData>::SortOrder::DESCENDING_ORDER, fpGetScore);
			EXPECT_EQ(data20.score, list.GetBegin()->score);

			//先頭、中央、末尾に挿入
			list.Insert(list.GetBegin(), data1);
			list.Insert(list.GetBegin() + 2, data2);
			list.Insert(list.GetEnd(), data3);

			//降順　スコア　2回目
			list.Sort<int>(DoublyLinkedList<ResultData>::SortOrder::DESCENDING_ORDER, fpGetScore);
			it = list.GetEnd() - 1;
			EXPECT_EQ(data1.score, it->score);
			EXPECT_EQ(data2.score, (--it)->score);
			EXPECT_EQ(data3.score, (--it)->score);
			EXPECT_EQ(data10.score, (--it)->score);
			EXPECT_EQ(data20.score, (--it)->score);

			//挿入したデータの削除
			for (int i = 0; i < 3; i++) {
				list.Delete(list.GetEnd() - 1);
			}

			//4/4
			//降順　名前
			list.Sort<std::string>(DoublyLinkedList<ResultData>::SortOrder::DESCENDING_ORDER, fpGetName);
			EXPECT_EQ(data20.name, list.GetBegin()->name);

			//先頭、中央、末尾に挿入
			list.Insert(list.GetBegin(), data1);
			list.Insert(list.GetBegin() + 2, data2);
			list.Insert(list.GetEnd(), data3);

			//降順　名前　2回目
			list.Sort<std::string>(DoublyLinkedList<ResultData>::SortOrder::DESCENDING_ORDER, fpGetName);
			it = list.GetEnd() - 1;
			EXPECT_EQ(data1.score, it->score);
			EXPECT_EQ(data2.score, (--it)->score);
			EXPECT_EQ(data3.score, (--it)->score);
			EXPECT_EQ(data10.score, (--it)->score);
			EXPECT_EQ(data20.score, (--it)->score);

		}

		/**********************************************************************************//**
			@brief		キー指定をしなかった(nullptrを渡した)場合のソート機能のテスト
			@details	ID:リスト-クイックソート-6\n
						何も起こらなければ成功です\n
		*//***********************************************************************************/
		TEST(SortTest, TestKeyIsNull) {
			DoublyLinkedList<ResultData> list;

			list.Sort<std::string>(DoublyLinkedList<ResultData>::SortOrder::ASCENDING_ORDER, nullptr);
		}

		/**********************************************************************************//**
			@brief		キーが不適切な場合のソート機能のテスト
			@details	ID:リスト-クイックソート-7\n
						キーの型がテンプレート引数と引数で異なる場合のテスト
						コンパイルエラーとなれば成功です\n
		*//***********************************************************************************/
		TEST(SortTest, TestKeyIsIrregular) {
//#define SORT_TEST_KEY_IS_IRREGULAR
#ifdef SORT_TEST_KEY_IS_IRREGULAR
			DoublyLinkedList<ResultData> list;

			//キーの型がテンプレート引数と引数で異なる
			list.Sort<int>(DoublyLinkedList<ResultData>::SortOrder::ASCENDING_ORDER, [](ResultData& data) {return data.name; });
#else
			SUCCEED();
#endif // SORT_TEST_KEY_IS_IRREGULAR
	}

		/**********************************************************************************//**
			@brief		リストがconstの場合のソート機能のテスト
			@details	ID:リスト-クイックソート-8\n
						コンパイルエラーとなれば成功です\n
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