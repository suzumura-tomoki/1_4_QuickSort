/**********************************************************************************//**
	@file           ManualTestForList.cpp
	@brief          GoogleTest手動テストコード
	@par            手動テストとは、チェックリスト内の「自動テスト化しなくてよい」項目を指します。
					defineマクロの条件分岐により、必要なものだけコンパイル対象になるようにしてください。
*//***********************************************************************************/


//--------------------------------------------------------------------------------
// ファイル依存関係
//--------------------------------------------------------------------------------
#include "pch.h"
#include"ManualTestForList.h"

// テスト対象のヘッダファイル
#include "../メインプロジェクト/main.h"

namespace ex01_DataStructure
{
	namespace chapter2
	{
		//--------------------------------------------------------------------------------
		// コンパイル関連手動テスト
		//--------------------------------------------------------------------------------
		/**********************************************************************************//**
			@brief		データ数の取得機能について、constのメソッドであるかのテスト
			@details	ID:リスト-8(手動)\n
						データ数の取得機能のテストです。\n
						constのメソッドであるかを確認しています。\n
						コンパイルが通れば成功です。\n
						TT_TEST_GET_DATA_NUM_IS_CONSTマクロを定義すると有効になります。\n
		*//***********************************************************************************/
		TEST(ListManualTest, TestGetDataNumWhenConst)
		{
#if defined TT_TEST_GET_DATA_NUM_WHEN_CONST
			const DoublyLinkedList<ResultData> list;
			EXPECT_EQ(0, list.GetSize());
#endif //TT_TEST_GET_DATA_NUM_WHEN_CONST
			SUCCEED();
		}

		/**********************************************************************************//**
			@brief		リスト末尾のデータ追加について、非constが保障されているかのテスト
			@details	ID:リスト-15(手動)\n
						リスト末尾のデータ追加テストです。\n
						非constが保障されているかを確認しています。\n
						コンパイルエラーになれば成功です。\n
		*//***********************************************************************************/
		TEST(ListManualTest, TestInsertWhenConst)
		{
#if defined TT_TEST_INSERT_WHEN_CONST
			const DoublyLinkedList<ResultData> list;
			DoublyLinkedList<ResultData>::ConstIterator it = list.GetConstBegin();
			list.Insert(it, ResultData());//ここでエラー
#endif //TT_TEST_INSERT_WHEN_CONST
			SUCCEED();
		}

		/**********************************************************************************//**
			@brief		データの削除機能について非constのメソッドであるかのテスト
			@details	ID:リスト-22 (手動)\n
						リストの要素削除テストです。\n
						constのリストから呼び出して、コンパイルエラーとなるかを確認しています。\n
						コンパイルエラーになれば成功です。\n
		*//***********************************************************************************/
		TEST(ListManualTest, TestDeleteWhenConst)
		{
#if defined TT_TEST_DELETE_WHEN_CONST
			const DoublyLinkedList<ResultData> list;
			DoublyLinkedList<ResultData>::ConstIterator it = list.GetConstBegin();
			list.Delete(it);//ここでエラー
#endif //TT_TEST_DELETE_WHEN_CONST
			SUCCEED();
		}

		/**********************************************************************************//**
			@brief		先頭イテレータの取得機能について非constのメソッドであるかのテスト
			@details	ID:リスト-28 (手動)\n
						先頭イテレータの取得機能のテストです。\n
						constのリストから呼び出した際の挙動を確認しています。\n
						コンパイルエラーになれば成功です。\n
		*//***********************************************************************************/
		TEST(ListManualTest, TestGetBeginWhenConst)
		{
#if defined TT_TEST_GET_BEGIN_WHEN_CONST
			const DoublyLinkedList<ResultData> list;
			list.GetBegin();//ここでエラー
#endif //TT_TEST_GET_BEGIN_WHEN_CONST
			SUCCEED();
		}

		/**********************************************************************************//**
			@brief		先頭コンストイテレータの取得機能機能についてconstのメソッドであるかのテスト
			@details	ID:リスト-34 (手動)\n
						先頭コンストイテレータの取得機能のテストです。\n
						constのリストから呼び出した際の挙動を確認しています。\n
						コンパイルが通れば成功です。\n
		*//***********************************************************************************/
		TEST(ListManualTest, TestGetConstBeginWhenConst)
		{
#if defined TT_TEST_GET_CONST_BEGIN_WHEN_CONST
			const DoublyLinkedList<ResultData> list;
			list.GetConstBegin();
#endif //TT_TEST_GET_CONST_BEGIN_WHEN_CONST
			SUCCEED();
		}

		/**********************************************************************************//**
			@brief		末尾イテレータの取得機能について非constのメソッドであるかのテスト
			@details	ID:リスト-40 (手動)\n
						末尾イテレータの取得機能のテストです。\n
						constのリストから呼び出した際の挙動を確認しています。\n
						コンパイルエラーになれば成功です。\n
		*//***********************************************************************************/
		TEST(ListManualTest, TestGetEndWhenConst)
		{
#if defined TT_TEST_GET_END_WHEN_CONST
			const DoublyLinkedList<ResultData> list;
			list.GetEnd();
#endif //TT_TEST_GET_END_WHEN_CONST
			SUCCEED();
		}

		/**********************************************************************************//**
			@brief		末尾コンストイテレータの取得機能について非constのメソッドであるかのテスト
			@details	ID:リスト-46 (手動)\n
						末尾コンストイテレータの取得機能のテストです。\n
						constのリストから呼び出した際の挙動を確認しています。\n
						コンパイルが通れば成功です。\n
		*//***********************************************************************************/
		TEST(ListManualTest, TestGetConstEndWhenConst)
		{
#if defined TT_TEST_GET_CONST_END_WHEN_CONST
			const DoublyLinkedList<ResultData> list;
			list.GetConstEnd();
#endif //TT_TEST_GET_END_WHEN_CONST
			SUCCEED();
		}

		/**********************************************************************************//**
			@brief		コンストイテレータから取得した要素に対して、値を代入した際の挙動テスト
			@details	ID:イテレータ-2 (手動)\n
						コンストイテレータの要素取得機能のテストです。\n
						コンストイテレータから取得した要素に対して、値を代入した際の挙動を確認しています。\n
						コンパイルエラーになれば成功です。\n
		*//***********************************************************************************/
		TEST(ListManualTest, ConstIteratorGetDataAndAssignment)
		{
#if defined TT_TEST_CONST_ITERATOR_DATA_ASSIGNMENT
			DoublyLinkedList<ResultData> list;
			DoublyLinkedList<ResultData>::ConstIterator cit = list.GetConstBegin();
			list.Insert(cit, ResultData());
			cit->name = "name";
#endif //TT_TEST_CONST_ITERATOR_DATA_ASSIGNMENT
			SUCCEED();
		}

		/**********************************************************************************//**
			@brief		ConstIterator<ResultData>から、Iterator<ResultData>へコピーを行った際の挙動テスト
			@details	ID:イテレータ-17 (手動)\n
						イテレータのコピー機能のテストです。\n
						ConstIterator<ResultData>から、Iterator<ResultData>へコピーを行った際の挙動を確認しています。\n
						コンパイルエラーになると成功です。\n
		*//***********************************************************************************/
		TEST(ListManualTest, CopyConstIteratorToIterator)
		{
#if defined TT_TEST_CONST_ITERATOR_COPY_TO_ITERATOR
			DoublyLinkedList<ResultData>::ConstIterator cit;
			DoublyLinkedList<ResultData>::Iterator it = cit;
#endif //TT_TEST_CONST_ITERATOR_COPY_TO_ITERATOR
			SUCCEED();
		}

		/**********************************************************************************//**
			@brief		Iterator<ResultData>にConstIterator<ResultData>を代入した際の挙動テスト
			@details	ID:イテレータ-19 (手動)\n
						イテレータの代入のテストです。\n
						Iterator<ResultData>にConstIterator<ResultData>を代入した際の挙動を確認しています。\n
						コンパイルエラーとなれば成功です。\n
		*//***********************************************************************************/
		TEST(ListManualTest, AssignmentConstIteratorToIterator)
		{
#if defined TT_TEST_ASSIGNMENT_CONST_ITERATOR_TO_ITERATOR
			DoublyLinkedList<ResultData>::ConstIterator cit;
			DoublyLinkedList<ResultData>::Iterator it;
			it = cit;
#endif //TT_TEST_ASSIGNMENT_CONST_ITERATOR_TO_ITERATOR
			SUCCEED();
		}

	}	// chapter2
}	//	ex01_DataStructure
