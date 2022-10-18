#pragma once
#include"DoublyLinkedList.h"
#include<assert.h>

template<typename Type>
DoublyLinkedList<Type>::DoublyLinkedList()
	:dummy({ nullptr,nullptr,Type() })
	, pTop(&dummy)
	, size(0)
{
	//初期化子リストで初期化
}


template<typename Type>
DoublyLinkedList<Type>::~DoublyLinkedList()
{
	DoublyLinkedList<Type>::Iterator it = GetBegin();

	while (size > 0)
	{
		Delete(it);
	}
}


template<typename Type>
unsigned int DoublyLinkedList<Type>::GetSize()const
{
	return size;
}


template<typename Type>
bool DoublyLinkedList<Type>::Insert(ConstIterator& iterator, const Type& data)
{
	if (this != iterator.pList)
	{
		return false;
	}

	if (iterator.pNode == nullptr)
	{
		return false;
	}

	//新しい要素を生成
	Node* pNewNode = new Node;
	pNewNode->data = data;
	pNewNode->pNext = iterator.pNode;//追加する位置にあった要素を次の要素にする
	pNewNode->pPrevious = pNewNode->pNext->pPrevious;//追加位置の前の要素を前の要素にする

	//前後の要素が新しい要素を参照するようにする
	pNewNode->pNext->pPrevious = pNewNode;

	if (pNewNode->pPrevious != nullptr)
	{
		//前の要素がある場合
		pNewNode->pPrevious->pNext = pNewNode;
	}

	//先頭に追加した場合に先頭ポインタを更新
	if (iterator.pNode == pTop)
	{
		pTop = pNewNode;
	}

	iterator--;//追加した要素へ移動
	this->size++;

	return true;
}

template<typename Type>
bool DoublyLinkedList<Type>::Delete(ConstIterator& iterator)
{
	// イテレータが自分のリストのイテレータか判断する
	if (this != iterator.pList)
	{
		return false;
	}

	//不正なイテレータか判断する
	if (iterator.pNode == nullptr)
	{
		return false;
	}

	//ダミーノードか判断する
	if (iterator.pNode == &iterator.pList->dummy)
	{
		return false;
	}

	//前に要素があれば削除対象の次の要素を指すように変更
	if (iterator.pNode->pPrevious != nullptr)
	{
		iterator.pNode->pPrevious->pNext = iterator.pNode->pNext;
	}

	//次の要素が削除対象の前の要素を指すように変更
	iterator.pNode->pNext->pPrevious = iterator.pNode->pPrevious;

	Node* pDeleteNode = iterator.pNode;

	iterator++;//次のノードへ移動

	//削除対象が先頭だったら先頭ポインタを更新
	if (pDeleteNode == pTop)
	{
		pTop = iterator.pNode;
	}

	delete pDeleteNode;

	size--;

	return true;
}

template<typename Type>
typename DoublyLinkedList<Type>::Iterator DoublyLinkedList<Type>::GetBegin()
{
	return Iterator(this, pTop);
}

template<typename Type>
typename DoublyLinkedList<Type>::ConstIterator DoublyLinkedList<Type>::GetConstBegin()const
{
	return ConstIterator(this, pTop);
}

template<typename Type>
typename DoublyLinkedList<Type>::Iterator DoublyLinkedList<Type>::GetEnd()
{
	return Iterator(this, &dummy);
}

template<typename Type>
typename DoublyLinkedList<Type>::ConstIterator DoublyLinkedList<Type>::GetConstEnd()const
{
	//コンストメンバ関数の中ではメンバ変数がコンストとして扱われますが、引数に渡せないためコンストを消します
	return ConstIterator(this, const_cast<Node*>(&dummy));
}

template<typename Type>
template<typename KeyType>
void DoublyLinkedList<Type>::Sort(SortOrder order, KeyType(*fpGetKey)(Type&))
{
	if (size <= 1)
	{
		//要素が１つ以下の場合終了
		return;
	}

	if (fpGetKey == nullptr)
	{
		//キーの指定がない場合終了
		return;
	}

	QuickSort<KeyType>(order, fpGetKey, GetBegin(), GetEnd() - 1, size);

}

template<typename Type>
template<typename KeyType>
inline void DoublyLinkedList<Type>::QuickSort(SortOrder order, KeyType(*fpGetKey)(Type&), Iterator head, Iterator tail, uint32_t _size) {

	//参考にした資料
	// ウィキペディア
	//https://ja.wikipedia.org/wiki/%E3%82%AF%E3%82%A4%E3%83%83%E3%82%AF%E3%82%BD%E3%83%BC%E3%83%88#cite_ref-4
	//過去の自作のクイックソート

	//再帰したときに要素が1つだったら終了
	if (_size <= 1)
		return;

	//基準値を決める
	// 先頭・中央・末尾から中間の値を選び基準値とする　最悪計算量の回避、完全な回避ではない
	KeyType keyHead = fpGetKey(*head);
	KeyType keyMiddle = fpGetKey(*(head + (_size / 2)));
	KeyType keyTail = fpGetKey(*tail);

	KeyType pivot = GetPivot(keyHead, keyMiddle, keyTail);

	//入れ替える要素を探索
	Iterator workHead = head;
	Iterator workTail = tail;
	int cntHeadMoved = 0;
	int cntTailMoved = 0;
	while (true) {
		switch (order)
		{
		case SortOrder::ASCENDING_ORDER:
			//先頭から順に基準値以上の値を持つ要素を探索
			while (workHead != workTail && fpGetKey(*workHead) < pivot) {
				workHead++;
				cntHeadMoved++;
			}
			//末尾から順に基準値未満の値を持つ要素を探索
			while (workHead != workTail && fpGetKey(*workTail) >= pivot) {
				workTail--;
				cntTailMoved++;
			}
			break;
		case SortOrder::DESCENDING_ORDER:
			//先頭から順に基準値以下の値を持つ要素を探索
			while (workHead != workTail && fpGetKey(*workHead) > pivot) {
				workHead++;
				cntHeadMoved++;
			}
			//末尾から順に基準値より大きい値を持つ要素を探索
			while (workHead != workTail && fpGetKey(*workTail) <= pivot) {
				workTail--;
				cntTailMoved++;
			}
			break;
		}

		//入れ替える要素がなくなると探索終了
		if (workHead == workTail) {
			break;
		}

		//探索した要素を入れ替える
		Swap(workHead, workTail);
	}

	//入れ替える要素がなくなるまで再帰

	if (cntHeadMoved == 0) {//ヘッドの移動が0の場合
		//※昇順についての記述（かっこの中は降順についての記述）
		//すべてのデータがピボット以上（以下）の値
		//PPP.. AP APP.. AAPP.. APPAP PPPA	P:ピボットと同じ値	A:ピボットより大きい値(ピボット未満の値)
		//ヘッドがPなら何もしない
		//ヘッドがAならPと入れ替え、Pは要素から選んでいるため必ず存在する
		if (fpGetKey(*head) == pivot) {
			//ヘッドがPなら何もしない
		}
		else
		{
			//ヘッドがAならPと入れ替え

			//末尾から順にPを探索
			workTail = tail;
			while (workHead != workTail && fpGetKey(*workTail) != pivot) {//workHead != workTailはいらないが念のため付けておく
				workTail--;
			}
			
			Swap(head, workTail);
		}
		//ヘッドをソート範囲から外して再帰
		QuickSort(order, fpGetKey, head + 1, tail, _size - 1);
		return;
	}

	QuickSort(order, fpGetKey, head, workHead - 1, cntHeadMoved);
	QuickSort(order, fpGetKey, workTail, tail, cntTailMoved + 1);
}

template<typename Type>
template<typename KeyType>
inline KeyType DoublyLinkedList<Type>::GetPivot(KeyType head, KeyType middle, KeyType tail)
{
	if (head < middle) {
		if (tail < head) {
			return head;
		}
		else if (middle < tail) {
			return middle;
		}
		else {
			return tail;
		}
	}
	else {
		if (tail > head) {
			return head;
		}
		else if (middle > tail) {
			return middle;
		}
		else {
			return tail;
		}
	}
}

template<typename Type>
inline void DoublyLinkedList<Type>::Swap(Iterator& it1, Iterator& it2)
{
	Type work = *it1;
	*it1 = *it2;//参照先は変わらず値のみコピーされる
	*it2 = work;
}

template<typename Type>
DoublyLinkedList<Type>::ConstIterator::ConstIterator()
	:pList(nullptr)
	, pNode(nullptr)
{
	//初期化子リストで初期化
}

template<typename Type>
DoublyLinkedList<Type>::ConstIterator::ConstIterator(const DoublyLinkedList<Type>* _pList, Node* _pNode)
	:pList(_pList)
	, pNode(_pNode)
{
	//初期化子リストで初期化
}

template<typename Type>
DoublyLinkedList<Type>::ConstIterator::ConstIterator(const ConstIterator& obj)
{
	this->pList = obj.pList;
	this->pNode = obj.pNode;
}

template<typename Type>
DoublyLinkedList<Type>::ConstIterator::~ConstIterator()
{
	//何もしない
}

template<typename Type>
typename DoublyLinkedList<Type>::ConstIterator& DoublyLinkedList<Type>::ConstIterator::operator++()
{
	assert(this->pList != nullptr);//リストの参照がない場合
	assert(this->pNode != nullptr);//ノードの参照がない場合
	assert(this->pNode != &this->pList->dummy);//末尾ノードである場合

	pNode = pNode->pNext;
	return *this;
}

template<typename Type>
typename DoublyLinkedList<Type>::ConstIterator DoublyLinkedList<Type>::ConstIterator::operator++(int)
{
	assert(this->pList != nullptr);//リストの参照がない
	assert(this->pNode != nullptr);//ノードの参照がない場合
	assert(this->pNode != &this->pList->dummy);//末尾ノードである

	ConstIterator cit = *this;
	operator++();
	return cit;
}

template<typename Type>
typename DoublyLinkedList<Type>::ConstIterator& DoublyLinkedList<Type>::ConstIterator::operator--()
{
	assert(this->pList != nullptr);//リストの参照がない
	assert(this->pNode != nullptr);//ノードの参照がない場合
	assert(this->pNode->pPrevious != nullptr);//先頭ノードである　またはリストが空の時の末尾ノード
	pNode = pNode->pPrevious;
	return *this;
}

template<typename Type>
typename DoublyLinkedList<Type>::ConstIterator DoublyLinkedList<Type>::ConstIterator::operator--(int)
{
	assert(this->pList != nullptr);//リストの参照がない
	assert(this->pNode != nullptr);//ノードの参照がない場合
	assert(this->pNode->pPrevious != nullptr);//先頭ノードである　またはリストが空の時の末尾ノード
	ConstIterator cit = *this;
	operator--();
	return cit;
}

template<typename Type>
typename DoublyLinkedList<Type>::ConstIterator DoublyLinkedList<Type>::ConstIterator::operator+(int n)const
{
	//エラーチェック　他の項目は++演算子の呼び出し時に行われる
	//先にノードにアクセスするのでノードの参照のみチェックしておく
	assert(this->pNode != nullptr);//ノードの参照がない場合

	if (n >= 0)
	{//末尾に進む

		ConstIterator cit = *this;

		for (int i = 0; i < n; i++) {

			//末尾を越えるとアサーションがでるよう変更
			// 意図しない挙動で動いてしまうより、エラーになるほうが良いと判断
			// コード量も若干軽減
			//末尾を越えないように停止する
			//if (cit.pNode->pNext == nullptr)
			//{
			//	return cit;
			//}

			cit++;
		}

		return cit;
	}
	else
	{//先頭に進む

		//絶対値を取得
		n = static_cast<int>(labs(n));

		//先頭に進めたイテレータを返す
		return (*this) - n;
	}
}

template<typename Type>
typename DoublyLinkedList<Type>::ConstIterator DoublyLinkedList<Type>::ConstIterator::operator-(int n)const
{
	//エラーチェック　他の項目は++演算子の呼び出し時に行われる
	//先にノードにアクセスするのでノードの参照のみチェックしておく
	assert(this->pNode != nullptr);//ノードの参照がない場合

	if (n >= 0)
	{//先頭に進む

		ConstIterator cit = *this;

		for (int i = 0; i < n; i++) {

			//先頭を越えるとアサーションがでるよう変更
			// 意図しない挙動で動いてしまうより、エラーになるほうが良いと判断
			// コード量も若干軽減
			//先頭を越えないように停止する
			//if (cit.pNode->pPrevious == nullptr)
			//{
			//	return cit;
			//}

			cit--;
		}

		return cit;
	}
	else
	{//末尾に進む

		//絶対値を取得
		n = static_cast<int>(labs(n));

		//末尾に進めたイテレータを返す
		return (*this) + n;
	}
}

template<typename Type>
bool DoublyLinkedList<Type>::ConstIterator::operator==(const ConstIterator& it)const
{
	return this->pNode == it.pNode;
}

template<typename Type>
bool DoublyLinkedList<Type>::ConstIterator::operator!=(const ConstIterator& it)const
{
	return !(*this == it);
}

template<typename Type>
const Type& DoublyLinkedList<Type>::ConstIterator::operator*()const
{
	assert(pList != nullptr);//pListがnullptrでないこと
	assert(pNode != &pList->dummy);//pNodeがダミーでないこと

	return pNode->data;
}

template<typename Type>

const Type* DoublyLinkedList<Type>::ConstIterator::operator->()const
{
	assert(pList != nullptr);//pListがnullptrでないこと
	assert(pNode != &pList->dummy);//pNodeがダミーでないこと

	return &pNode->data;
}

template<typename Type>
DoublyLinkedList<Type>::Iterator::Iterator()
{
	//何もしない　メンバがいない
}

template<typename Type>
DoublyLinkedList<Type>::Iterator::Iterator(DoublyLinkedList<Type>* _pList, Node* _pNode) : ConstIterator(_pList, _pNode)
{
	//基底クラスConstIteratorのコンストラクタに引数を渡す
	//ここでは何もしない
}

template<typename Type>
DoublyLinkedList<Type>::Iterator::~Iterator()
{
	//何もしない
}

template<typename Type>
typename DoublyLinkedList<Type>::Iterator& DoublyLinkedList<Type>::Iterator::operator++()
{
	ConstIterator::operator++();

	return *this;
}

template<typename Type>
typename DoublyLinkedList<Type>::Iterator DoublyLinkedList<Type>::Iterator::operator++(int)
{
	Iterator it = *this;

	operator++();

	return it;
}

template<typename Type>
typename DoublyLinkedList<Type>::Iterator& DoublyLinkedList<Type>::Iterator::operator--()
{
	ConstIterator::operator--();

	return *this;
}

template<typename Type>
typename DoublyLinkedList<Type>::Iterator DoublyLinkedList<Type>::Iterator::operator--(int)
{
	Iterator it = *this;

	operator--();

	return it;
}

template<typename Type>
typename DoublyLinkedList<Type>::Iterator DoublyLinkedList<Type>::Iterator::operator+(int n)const
{
	ConstIterator cit = ConstIterator::operator+(n);

	//関数がconstのため、別のインスタンスの親クラスのメンバもconstとして扱われてしまうので、引数として渡すためにconstを外します
	return Iterator(const_cast<DoublyLinkedList<Type>*>(cit.pList), const_cast<Node*>(cit.pNode));
}

template<typename Type>
typename DoublyLinkedList<Type>::Iterator DoublyLinkedList<Type>::Iterator::operator-(int n)const
{
	ConstIterator cit = ConstIterator::operator-(n);

	//関数がconstのため、別のインスタンスの親クラスのメンバもconstとして扱われてしまうので、引数として渡すためにconstを外します
	return Iterator(const_cast<DoublyLinkedList<Type>*>(cit.pList), const_cast<Node*>(cit.pNode));
}

template<typename Type>
Type& DoublyLinkedList<Type>::Iterator::operator*()
{
	//コンストイテレータの機能を流用してコンストを解除
	return const_cast<Type&>(ConstIterator::operator*());
}

template<typename Type>
Type* DoublyLinkedList<Type>::Iterator::operator->()
{
	//コンストイテレータの機能を流用してコンストを解除
	return const_cast<Type*>(ConstIterator::operator->());//ここではポインタの->は呼ばれていない
}
