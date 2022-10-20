#pragma once
//#pragma inline_depth(16)//既定が１６

#include<string>

/**
 * @brief 双方向リストのクラス\n
 *		  別名bi-directional list
 * @tparam Type リストに格納するデータの型
 */
template<typename Type>
class DoublyLinkedList
{
private:

	/** @brief 双方向リストのノード */
	struct Node {
		DoublyLinkedList<Type>::Node* pPrevious = nullptr;
		DoublyLinkedList<Type>::Node* pNext = nullptr;
		Type data;
	};

public:

	/** @brief ソート順の列挙 */
	enum class SortOrder
	{
		ASCENDING_ORDER,
		DESCENDING_ORDER,
	};

	/**
	 * @brief 双方向リストのコンストイテレータ\n
	 *		  ＊演算子または->演算子でデータにアクセスできます
	 */
	class ConstIterator {

		friend DoublyLinkedList<Type>;

	public:
		/** @brief コンストラクタ*/
		ConstIterator();
		/**
		 * @brief コンストラクタ
		 * @param[in] _pList 参照するリストへのポインタ\n
		 *					 nullptrの場合、挿入や削除に失敗し、イテレータを移動する際にエラーになります\n
		 *					 _pListと_pNodeに関連が無い場合、参照するリストにイテレータを渡すことで挿入や削除が行えますが、実際にはノードの所属するリストが更新されます
		 * @param[in] _pNode コンストイテレータが示すノードへのポインタ\n
		 *					 nullptrの場合は挿入や削除が行われず、イテレータを移動する際にエラーになります。
		 */
		ConstIterator(const DoublyLinkedList<Type>* _pList, Node* _pNode);

		/**
		 * @brief コピーコンストラクタ
		 * @param[in] obj コピー元のオブジェクト
		 */
		ConstIterator(const ConstIterator& obj);

		/** @brief デストラクタ */
		virtual ~ConstIterator();

		/**
		 * @brief 次の要素に移動します
		 * @return 移動したコンストイテレータ
		 */
		ConstIterator& operator++();
		/**
		 * @brief 次の要素に移動します
		 * @return 移動していないコンストイテレータ
		 */
		ConstIterator operator++(int);
		/**
		 * @brief 前の要素に移動します
		 * @return 移動したコンストイテレータ
		 */
		ConstIterator& operator--();
		/**
		 * @brief 前の要素に移動します
		 * @return 移動していないコンストイテレータ
		 */
		ConstIterator operator--(int);

		/**
		 * @brief 末尾方向に指定した数だけ移動したコンストイテレータを返します
		 * @param[in] n 移動回数\n
		 *				リストの範囲を越えて指定した場合、先頭または末尾のコンストイテレータを返します
		 * @return 移動したコンストイテレータ
		 */
		ConstIterator operator+(int n)const;
		/**
		 * @brief 先頭方向に指定した数だけ移動したコンストイテレータを返します
		 * @param[in] n 移動回数\n
		 *				リストの範囲を越えて指定した場合、先頭または末尾のコンストイテレータを返します
		 * @return 移動したコンストイテレータ
		 */
		ConstIterator operator-(int n)const;

		/**
		 * @brief イテレータの示すノードが同じものか比較します
		 * @param[in] it 比較対象
		 * @return true:同じノードを指している\n
		 *		   false:異なるノードを指している
		 */
		bool operator==(const ConstIterator& it)const;
		/**
		 * @brief イテレータの示すノードが異なるものか比較します
		 * @param[in] it 比較対象
		 * @return true:異なるノードを指している\n
		 *		   false:同じノードを指している
		 */
		bool operator!=(const ConstIterator& it)const;

		/**
		 * @brief コンストイテレータが示す要素のコンスト参照を取得します
		 * @return イテレータが示す要素のコンスト参照
		 */
		const Type& operator*()const;
		/**
		 * @brief コンストイテレータが示すコンスト要素を取得します\n
		 *		  暗黙的に戻り値の持つ->が呼ばれます
		 * @return コンストイテレータが示すコンスト要素へのポインタ
		 */
		const Type* operator->()const;

	protected:
		/** @brief このイテレータが示すノードへのポインタ */
		Node* pNode = nullptr;
		/** @brief このイテレータが参照しているリストへのポインタ */
		const DoublyLinkedList<Type>* pList = nullptr;
	private:

	};

	/**
	 * @brief 双方向リストのイテレータ\n
	 *		 継承：コンストイテレータ\n
	 *		 ＊演算子または->演算子でデータにアクセスできます
	 */
	class Iterator :public ConstIterator {
	public:
		/** @brief コンストラクタ */
		Iterator();
		/**
		 * @brief コンストラクタ
		 * @param[in] _pList 参照するリストへのポインタ\n
		 *					 nullptrの場合、挿入や削除に失敗し、イテレータを移動する際にエラーになります\n
		 *					 _pListと_pNodeに関連が無い場合、参照するリストにイテレータを渡すことで挿入や削除が行えますが、実際にはノードの所属するリストが更新されます
		 * @param[in] _pNode イテレータが示すノードへのポインタ\n
		 *					 nullptrの場合は挿入や削除が行われず、イテレータを移動する際にエラーになります。
		 */
		Iterator(DoublyLinkedList<Type>* _pList, Node* _pNode);

		/**
		 * @brief デフォルトコピーコンストラクタ
		 * @param[in] obj コピー元のオブジェクト
		 */
		Iterator(const Iterator& obj) = default;

		/** @brief デストラクタ */
		virtual ~Iterator();

		/**
		 * @brief 次の要素に移動します
		 * @return 移動したイテレータ
		 */
		Iterator& operator++();
		/**
		 * @brief 次の要素に移動します
		 * @return 移動していないイテレータ
		 */
		Iterator operator++(int);
		/**
		 * @brief 前の要素に移動します
		 * @return 移動したイテレータ
		 */
		Iterator& operator--();
		/**
		 * @brief 前の要素に移動します
		 * @return 移動していないイテレータ
		 */
		Iterator operator--(int);

		/**
		 * @brief 末尾方向に指定した数だけ移動したイテレータを返します
		 * @param[in] n 移動回数\n
		 *				リストの範囲を越えて指定した場合、先頭または末尾のイテレータを返します
		 * @return 移動したイテレータ
		 */
		Iterator operator+(int n)const;
		/**
		 * @brief 先頭方向に指定した数だけ移動したイテレータを返します
		 * @param[in] n 移動回数\n
		 *				リストの範囲を越えて指定した場合、先頭または末尾のイテレータを返します
		 * @return 移動したイテレータ
		 */
		Iterator operator-(int n)const;

		/**
		 * @brief イテレータが示す要素の参照を取得します
		 * @return イテレータが示す要素の参照
		 */
		Type& operator*();
		/**
		 * @brief イテレータが示す要素を取得します\n
		 *		  暗黙的に戻り値の持つ->が呼ばれます
		 * @return イテレータが示す要素へのポインタ
		 */
		Type* operator->();

	private:

	};

	/** @brief コンストラクタ */
	DoublyLinkedList();

	/** @brief デフォルトコピーコンストラクタ */
	DoublyLinkedList(const DoublyLinkedList<Type>& obj) = default;

	/**
	 * @brief デストラクタ\n
	 * 確保したノードを全て解放する
	 */
	virtual ~DoublyLinkedList();

	/**
	 * @brief 要素数を取得します
	 * @return 要素数
	 */
	unsigned int GetSize()const;

	/**
	 * @brief イテレータが示す要素の前に要素を挿入します\n
	 *		  追加した要素にイテレータを移動させます
	 * @param[in,out] iterator 挿入位置のイテレータ、挿入した要素に移動します
	 * @param[in]	  data     格納するデータ
	 * @return true:挿入に成功\n
	 *		   false:挿入に失敗\n
	 * 別のリストのイテレータを渡した場合や、リストやノードへの参照がないイテレータを渡した場合に挿入に失敗します
	 */
	bool Insert(ConstIterator& iterator, const Type& data);

	/**
	 * @brief イテレータが示す要素を削除します\n
	 *		  削除した要素の次の要素にイテレータを移動させます
	 * @param[in,out] iterator 削除する要素のイテレータ
	 * @return true:削除に成功\n
	 *		   false:削除に失敗\n
	 * 別のリストのイテレータを渡した場合や、リストやノードへの参照がないイテレータを渡した場合に削除に失敗します\n
	 * 末尾のイテレータを渡した場合も失敗します
	 */
	bool Delete(ConstIterator& iterator);

	/**
	 * @brief 先頭のイテレータを取得
	 * @return 先頭のイテレータ
	 */
	Iterator GetBegin();

	/**
	 * @brief 先頭のコンストイテレータを取得
	 * @return 先頭のコンストイテレータ
	 */
	ConstIterator GetConstBegin()const;

	/**
	 * @brief 末尾のイテレータを取得
	 * @return 末尾のイテレータ
	 */
	Iterator GetEnd();

	/**
	 * @brief 末尾のコンストイテレータを取得
	 * @return 末尾のコンストイテレータ
	 */
	ConstIterator GetConstEnd()const;

	/**
	 * @brief データからソートに使用するキーを取得する関数オブジェクトのポインタ型
	 * @tparam KeyType キーの型
	 * @param[in] リストに格納しているデータ
	 * @return データから取り出したソートに使用するキー
	 */
	template<typename KeyType>
	using FuncGetKey = const KeyType&(*)(const Type&);

	/**
	 * @brief リストをKeyType型のキーについてソートします
	 * @tparam KeyType キーの型
	 * @param[in] order 昇順または降順の指定
	 * @param[in] GetKey 格納されているデータからKeyType型のキーを取得する関数オブジェクトのポインタ
	 */
	template<typename KeyType>
	void Sort(SortOrder order, FuncGetKey<KeyType> GetKey);

private:
	friend Iterator;
	friend ConstIterator;

	/**
	 * @brief 再帰しながらリストをKeyType型のキーについてソートします
	 * @tparam KeyType キーの型
	 * @param[in] order 昇順または降順の指定
	 * @param[in] GetKey 格納されているデータからKeyType型のキーを取得する関数オブジェクトのポインタ
	 * @param[in] head 先頭のイテレータ
	 * @param[in] tail 末尾のイテレータ
	 * @param[in] _size 要素の数
	 */
	template<typename KeyType>
	void QuickSort(SortOrder order, FuncGetKey<KeyType> GetKey, Iterator head, Iterator tail, uint32_t _size);

	/**
	 * @brief ３つのキーからピボットを取得します
	 * @tparam KeyType キーの型
	 * @param[in] head 先頭要素のキー
	 * @param[in] middle 中央要素のキー
	 * @param[in] tail 末尾要素のキー
	 * @return ３つの引数の中央値へのポインタ
	 */
	template<typename KeyType>
	const KeyType* GetPivot(const KeyType& head, const KeyType& middle, const KeyType& tail);

	/**
	 * @brief イテレータの示すデータを入れ替えます
	 * @param[in] it1 入れ替えるデータのイテレータ
	 * @param[in] it2 入れ替えるデータのイテレータ
	 */
	void Swap(Iterator& it1, Iterator& it2);

	/** @brief 末尾を示すダミー要素　データは格納されない */
	Node dummy;
	/** @brief 先頭要素へのポインタ */
	Node* pTop;
	/** @brief 要素の数 */
	unsigned int size;
};

#include"DoublyLinkedList.inl"