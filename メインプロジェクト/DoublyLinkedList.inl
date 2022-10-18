#pragma once
#include"DoublyLinkedList.h"
#include<assert.h>

template<typename Type>
DoublyLinkedList<Type>::DoublyLinkedList()
	:dummy({ nullptr,nullptr,Type() })
	, pTop(&dummy)
	, size(0)
{
	//�������q���X�g�ŏ�����
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

	//�V�����v�f�𐶐�
	Node* pNewNode = new Node;
	pNewNode->data = data;
	pNewNode->pNext = iterator.pNode;//�ǉ�����ʒu�ɂ������v�f�����̗v�f�ɂ���
	pNewNode->pPrevious = pNewNode->pNext->pPrevious;//�ǉ��ʒu�̑O�̗v�f��O�̗v�f�ɂ���

	//�O��̗v�f���V�����v�f���Q�Ƃ���悤�ɂ���
	pNewNode->pNext->pPrevious = pNewNode;

	if (pNewNode->pPrevious != nullptr)
	{
		//�O�̗v�f������ꍇ
		pNewNode->pPrevious->pNext = pNewNode;
	}

	//�擪�ɒǉ������ꍇ�ɐ擪�|�C���^���X�V
	if (iterator.pNode == pTop)
	{
		pTop = pNewNode;
	}

	iterator--;//�ǉ������v�f�ֈړ�
	this->size++;

	return true;
}

template<typename Type>
bool DoublyLinkedList<Type>::Delete(ConstIterator& iterator)
{
	// �C�e���[�^�������̃��X�g�̃C�e���[�^�����f����
	if (this != iterator.pList)
	{
		return false;
	}

	//�s���ȃC�e���[�^�����f����
	if (iterator.pNode == nullptr)
	{
		return false;
	}

	//�_�~�[�m�[�h�����f����
	if (iterator.pNode == &iterator.pList->dummy)
	{
		return false;
	}

	//�O�ɗv�f������΍폜�Ώۂ̎��̗v�f���w���悤�ɕύX
	if (iterator.pNode->pPrevious != nullptr)
	{
		iterator.pNode->pPrevious->pNext = iterator.pNode->pNext;
	}

	//���̗v�f���폜�Ώۂ̑O�̗v�f���w���悤�ɕύX
	iterator.pNode->pNext->pPrevious = iterator.pNode->pPrevious;

	Node* pDeleteNode = iterator.pNode;

	iterator++;//���̃m�[�h�ֈړ�

	//�폜�Ώۂ��擪��������擪�|�C���^���X�V
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
	//�R���X�g�����o�֐��̒��ł̓����o�ϐ����R���X�g�Ƃ��Ĉ����܂����A�����ɓn���Ȃ����߃R���X�g�������܂�
	return ConstIterator(this, const_cast<Node*>(&dummy));
}

template<typename Type>
template<typename KeyType>
void DoublyLinkedList<Type>::Sort(SortOrder order, KeyType(*fpGetKey)(Type&))
{
	if (size <= 1)
	{
		//�v�f���P�ȉ��̏ꍇ�I��
		return;
	}

	if (fpGetKey == nullptr)
	{
		//�L�[�̎w�肪�Ȃ��ꍇ�I��
		return;
	}

	QuickSort<KeyType>(order, fpGetKey, GetBegin(), GetEnd() - 1, size);

}

template<typename Type>
template<typename KeyType>
inline void DoublyLinkedList<Type>::QuickSort(SortOrder order, KeyType(*fpGetKey)(Type&), Iterator head, Iterator tail, uint32_t _size) {

	//�Q�l�ɂ�������
	// �E�B�L�y�f�B�A
	//https://ja.wikipedia.org/wiki/%E3%82%AF%E3%82%A4%E3%83%83%E3%82%AF%E3%82%BD%E3%83%BC%E3%83%88#cite_ref-4
	//�ߋ��̎���̃N�C�b�N�\�[�g

	//�ċA�����Ƃ��ɗv�f��1��������I��
	if (_size <= 1)
		return;

	//��l�����߂�
	// �擪�E�����E�������璆�Ԃ̒l��I�ъ�l�Ƃ���@�ň��v�Z�ʂ̉���A���S�ȉ���ł͂Ȃ�
	KeyType keyHead = fpGetKey(*head);
	KeyType keyMiddle = fpGetKey(*(head + (_size / 2)));
	KeyType keyTail = fpGetKey(*tail);

	KeyType pivot = GetPivot(keyHead, keyMiddle, keyTail);

	//����ւ���v�f��T��
	Iterator workHead = head;
	Iterator workTail = tail;
	int cntHeadMoved = 0;
	int cntTailMoved = 0;
	while (true) {
		switch (order)
		{
		case SortOrder::ASCENDING_ORDER:
			//�擪���珇�Ɋ�l�ȏ�̒l�����v�f��T��
			while (workHead != workTail && fpGetKey(*workHead) < pivot) {
				workHead++;
				cntHeadMoved++;
			}
			//�������珇�Ɋ�l�����̒l�����v�f��T��
			while (workHead != workTail && fpGetKey(*workTail) >= pivot) {
				workTail--;
				cntTailMoved++;
			}
			break;
		case SortOrder::DESCENDING_ORDER:
			//�擪���珇�Ɋ�l�ȉ��̒l�����v�f��T��
			while (workHead != workTail && fpGetKey(*workHead) > pivot) {
				workHead++;
				cntHeadMoved++;
			}
			//�������珇�Ɋ�l���傫���l�����v�f��T��
			while (workHead != workTail && fpGetKey(*workTail) <= pivot) {
				workTail--;
				cntTailMoved++;
			}
			break;
		}

		//����ւ���v�f���Ȃ��Ȃ�ƒT���I��
		if (workHead == workTail) {
			break;
		}

		//�T�������v�f�����ւ���
		Swap(workHead, workTail);
	}

	//����ւ���v�f���Ȃ��Ȃ�܂ōċA

	if (cntHeadMoved == 0) {//�w�b�h�̈ړ���0�̏ꍇ
		//�������ɂ��Ă̋L�q�i�������̒��͍~���ɂ��Ă̋L�q�j
		//���ׂẴf�[�^���s�{�b�g�ȏ�i�ȉ��j�̒l
		//PPP.. AP APP.. AAPP.. APPAP PPPA	P:�s�{�b�g�Ɠ����l	A:�s�{�b�g���傫���l(�s�{�b�g�����̒l)
		//�w�b�h��P�Ȃ牽�����Ȃ�
		//�w�b�h��A�Ȃ�P�Ɠ���ւ��AP�͗v�f����I��ł��邽�ߕK�����݂���
		if (fpGetKey(*head) == pivot) {
			//�w�b�h��P�Ȃ牽�����Ȃ�
		}
		else
		{
			//�w�b�h��A�Ȃ�P�Ɠ���ւ�

			//�������珇��P��T��
			workTail = tail;
			while (workHead != workTail && fpGetKey(*workTail) != pivot) {//workHead != workTail�͂���Ȃ����O�̂��ߕt���Ă���
				workTail--;
			}
			
			Swap(head, workTail);
		}
		//�w�b�h���\�[�g�͈͂���O���čċA
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
	*it1 = *it2;//�Q�Ɛ�͕ς�炸�l�̂݃R�s�[�����
	*it2 = work;
}

template<typename Type>
DoublyLinkedList<Type>::ConstIterator::ConstIterator()
	:pList(nullptr)
	, pNode(nullptr)
{
	//�������q���X�g�ŏ�����
}

template<typename Type>
DoublyLinkedList<Type>::ConstIterator::ConstIterator(const DoublyLinkedList<Type>* _pList, Node* _pNode)
	:pList(_pList)
	, pNode(_pNode)
{
	//�������q���X�g�ŏ�����
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
	//�������Ȃ�
}

template<typename Type>
typename DoublyLinkedList<Type>::ConstIterator& DoublyLinkedList<Type>::ConstIterator::operator++()
{
	assert(this->pList != nullptr);//���X�g�̎Q�Ƃ��Ȃ��ꍇ
	assert(this->pNode != nullptr);//�m�[�h�̎Q�Ƃ��Ȃ��ꍇ
	assert(this->pNode != &this->pList->dummy);//�����m�[�h�ł���ꍇ

	pNode = pNode->pNext;
	return *this;
}

template<typename Type>
typename DoublyLinkedList<Type>::ConstIterator DoublyLinkedList<Type>::ConstIterator::operator++(int)
{
	assert(this->pList != nullptr);//���X�g�̎Q�Ƃ��Ȃ�
	assert(this->pNode != nullptr);//�m�[�h�̎Q�Ƃ��Ȃ��ꍇ
	assert(this->pNode != &this->pList->dummy);//�����m�[�h�ł���

	ConstIterator cit = *this;
	operator++();
	return cit;
}

template<typename Type>
typename DoublyLinkedList<Type>::ConstIterator& DoublyLinkedList<Type>::ConstIterator::operator--()
{
	assert(this->pList != nullptr);//���X�g�̎Q�Ƃ��Ȃ�
	assert(this->pNode != nullptr);//�m�[�h�̎Q�Ƃ��Ȃ��ꍇ
	assert(this->pNode->pPrevious != nullptr);//�擪�m�[�h�ł���@�܂��̓��X�g����̎��̖����m�[�h
	pNode = pNode->pPrevious;
	return *this;
}

template<typename Type>
typename DoublyLinkedList<Type>::ConstIterator DoublyLinkedList<Type>::ConstIterator::operator--(int)
{
	assert(this->pList != nullptr);//���X�g�̎Q�Ƃ��Ȃ�
	assert(this->pNode != nullptr);//�m�[�h�̎Q�Ƃ��Ȃ��ꍇ
	assert(this->pNode->pPrevious != nullptr);//�擪�m�[�h�ł���@�܂��̓��X�g����̎��̖����m�[�h
	ConstIterator cit = *this;
	operator--();
	return cit;
}

template<typename Type>
typename DoublyLinkedList<Type>::ConstIterator DoublyLinkedList<Type>::ConstIterator::operator+(int n)const
{
	//�G���[�`�F�b�N�@���̍��ڂ�++���Z�q�̌Ăяo�����ɍs����
	//��Ƀm�[�h�ɃA�N�Z�X����̂Ńm�[�h�̎Q�Ƃ̂݃`�F�b�N���Ă���
	assert(this->pNode != nullptr);//�m�[�h�̎Q�Ƃ��Ȃ��ꍇ

	if (n >= 0)
	{//�����ɐi��

		ConstIterator cit = *this;

		for (int i = 0; i < n; i++) {

			//�������z����ƃA�T�[�V�������ł�悤�ύX
			// �Ӑ}���Ȃ������œ����Ă��܂����A�G���[�ɂȂ�ق����ǂ��Ɣ��f
			// �R�[�h�ʂ��኱�y��
			//�������z���Ȃ��悤�ɒ�~����
			//if (cit.pNode->pNext == nullptr)
			//{
			//	return cit;
			//}

			cit++;
		}

		return cit;
	}
	else
	{//�擪�ɐi��

		//��Βl���擾
		n = static_cast<int>(labs(n));

		//�擪�ɐi�߂��C�e���[�^��Ԃ�
		return (*this) - n;
	}
}

template<typename Type>
typename DoublyLinkedList<Type>::ConstIterator DoublyLinkedList<Type>::ConstIterator::operator-(int n)const
{
	//�G���[�`�F�b�N�@���̍��ڂ�++���Z�q�̌Ăяo�����ɍs����
	//��Ƀm�[�h�ɃA�N�Z�X����̂Ńm�[�h�̎Q�Ƃ̂݃`�F�b�N���Ă���
	assert(this->pNode != nullptr);//�m�[�h�̎Q�Ƃ��Ȃ��ꍇ

	if (n >= 0)
	{//�擪�ɐi��

		ConstIterator cit = *this;

		for (int i = 0; i < n; i++) {

			//�擪���z����ƃA�T�[�V�������ł�悤�ύX
			// �Ӑ}���Ȃ������œ����Ă��܂����A�G���[�ɂȂ�ق����ǂ��Ɣ��f
			// �R�[�h�ʂ��኱�y��
			//�擪���z���Ȃ��悤�ɒ�~����
			//if (cit.pNode->pPrevious == nullptr)
			//{
			//	return cit;
			//}

			cit--;
		}

		return cit;
	}
	else
	{//�����ɐi��

		//��Βl���擾
		n = static_cast<int>(labs(n));

		//�����ɐi�߂��C�e���[�^��Ԃ�
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
	assert(pList != nullptr);//pList��nullptr�łȂ�����
	assert(pNode != &pList->dummy);//pNode���_�~�[�łȂ�����

	return pNode->data;
}

template<typename Type>

const Type* DoublyLinkedList<Type>::ConstIterator::operator->()const
{
	assert(pList != nullptr);//pList��nullptr�łȂ�����
	assert(pNode != &pList->dummy);//pNode���_�~�[�łȂ�����

	return &pNode->data;
}

template<typename Type>
DoublyLinkedList<Type>::Iterator::Iterator()
{
	//�������Ȃ��@�����o�����Ȃ�
}

template<typename Type>
DoublyLinkedList<Type>::Iterator::Iterator(DoublyLinkedList<Type>* _pList, Node* _pNode) : ConstIterator(_pList, _pNode)
{
	//���N���XConstIterator�̃R���X�g���N�^�Ɉ�����n��
	//�����ł͉������Ȃ�
}

template<typename Type>
DoublyLinkedList<Type>::Iterator::~Iterator()
{
	//�������Ȃ�
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

	//�֐���const�̂��߁A�ʂ̃C���X�^���X�̐e�N���X�̃����o��const�Ƃ��Ĉ����Ă��܂��̂ŁA�����Ƃ��ēn�����߂�const���O���܂�
	return Iterator(const_cast<DoublyLinkedList<Type>*>(cit.pList), const_cast<Node*>(cit.pNode));
}

template<typename Type>
typename DoublyLinkedList<Type>::Iterator DoublyLinkedList<Type>::Iterator::operator-(int n)const
{
	ConstIterator cit = ConstIterator::operator-(n);

	//�֐���const�̂��߁A�ʂ̃C���X�^���X�̐e�N���X�̃����o��const�Ƃ��Ĉ����Ă��܂��̂ŁA�����Ƃ��ēn�����߂�const���O���܂�
	return Iterator(const_cast<DoublyLinkedList<Type>*>(cit.pList), const_cast<Node*>(cit.pNode));
}

template<typename Type>
Type& DoublyLinkedList<Type>::Iterator::operator*()
{
	//�R���X�g�C�e���[�^�̋@�\�𗬗p���ăR���X�g������
	return const_cast<Type&>(ConstIterator::operator*());
}

template<typename Type>
Type* DoublyLinkedList<Type>::Iterator::operator->()
{
	//�R���X�g�C�e���[�^�̋@�\�𗬗p���ăR���X�g������
	return const_cast<Type*>(ConstIterator::operator->());//�����ł̓|�C���^��->�͌Ă΂�Ă��Ȃ�
}
