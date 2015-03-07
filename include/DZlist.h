/**************************************************************************
 *   Copyright (C) 2015 by Carlo Carrano                                  *
 *   crc@dazzlingsolutions.com                                            *
 *                                                                        *
 *   This program is free software; you can redistribute it and/or modify *
 *   it under the terms of the GNU General Public License as published by *
 *   the Free Software Foundation; version 2 of the License.              *
 *   This program is distributed in the hope that it will be useful, but  *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU     *
 *   General Public License for more details.                             *
 *   You should have received a copy of the GNU General Public License    *
 *   along with this program; if not, write to the Free Software          *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  *
 *   USA.  																  *
 **************************************************************************/

/**************************************************************************
 * Change Log                                                             *
 *------------------------------------------------------------------------*
 * 03-04-2015	file created                                              *
 **************************************************************************/

#ifndef DZLIST_H
#define DZLIST_H

#include "DZlogger.h"


template <class T> class DZnode;
template <class T> class DZiterator;
template <class T> class DZlist;


/*****************************************************************
 *
 * Class:			DZnode
 *
 * Description:		General node of the single linked list.
 *					It holds the pointer to the next node and
 *					the data itself.
 *
 * Interface:		n/a
 *					DZnode is used internally in DZlist
 *
 ****************************************************************/
template <class T> class DZnode
{
	public:
		T Data;
		DZnode<T>* nextPtr;

		DZnode()
		{
			DZ_LOG(DZ_LOG_TRACE, "Creating node");
			nextPtr = 0;
		}

		~DZnode()
		{
			DZ_LOG(DZ_LOG_TRACE, "Destroying node");
		}
};



/*****************************************************************
 *
 * Class:			DZlist
 *
 * Description:		Single linked list
 *
 * Interface:		DZlist()	- constructor
 *					~DZlist()	- destructor
 *					Append(data)	- append node to the end
 *									  of the list
 *					Prepend(data)	- add node to the beginning
 *									  of the list
 *					Insert(iterator,data)
 *									- insert node at the specified
 *									  position; node previously
 *									  at that position is moved
 *									  forward
 *					Remove(iterator)- remove node at specified
 *									  position
 *					headRemove()	- remove node at the head
 *									  of the list
 *					tailRemove()	- remove node at the tail
 *									  of the list
 *					getIterator()	- gets an iterator for the
 *									  list, positioned at the
 *									  head
 *					getCount()		- gets the number of nodes
 *									  in the list
 *					store(filename) - store list in to given file
 *					retrieve(filename)
 *									- retrieves list from
 *									  given file
 *
 ****************************************************************/
template <class T> class DZlist
{
	public:
		//--------------------------------------------------------
		// Name:		DZlist::DZlist
		// Description:	constructor for an empty list
		// Arguments:	n/a
		//--------------------------------------------------------
		DZlist()
		{
			DZ_LOG(DZ_LOG_TRACE, "Creating list");
			headPtr = 0;
			tailPtr = 0;
			Count = 0;
		}

		//--------------------------------------------------------
		// Name:		DZlist::~DZlist
		// Description:	destructor; removes every node
		// Arguments:	n/a
		//--------------------------------------------------------
		~DZlist()
		{
			DZnode<T>* iter = headPtr;
			DZnode<T>* nextNodePtr;

			DZ_LOG(DZ_LOG_TRACE, "Destroying list");

			while (iter != 0)
			{
				nextNodePtr = iter->nextPtr;
				delete iter;
				iter = nextNodePtr;
			}
		}

		//--------------------------------------------------------
		// Name:		DZlist::Append
		// Description:	append a new node to the end of the list
		// Arguments:	data	- data to be stored in the node
		//--------------------------------------------------------
		void Append(T data)
		{
			DZ_LOG(DZ_LOG_TRACE, "Appending new node");

			DZnode<T>* node_ptr = new DZnode<T>;
			node_ptr->Data = data;

			if (headPtr == 0)
			{
				headPtr = node_ptr;
				tailPtr = node_ptr;
			}
			else
			{
				tailPtr->nextPtr = node_ptr;
				tailPtr = node_ptr;
			}

			Count++;
		}

		//--------------------------------------------------------
		// Name:		DZlist::Prepend
		// Description:	prepend a new node to the beginning of the
		//				list
		// Arguments:	data	- data to be stored in the node
		//--------------------------------------------------------
		void Prepend(T data)
		{
			DZ_LOG(DZ_LOG_TRACE, "prepending new node");

			DZnode<T>* node_ptr = new DZnode<T>;
			node_ptr->Data = data;

			if (headPtr == 0)
			{
				tailPtr = node_ptr;
			}
			else
			{
				node_ptr->nextPtr = headPtr;
			}

			headPtr = node_ptr;

			Count++;
		}

		//--------------------------------------------------------
		// Name:		DZlist::Insert
		// Description:	Insert a new node after the iterator. If the
		//				iterator is invalid it will do an append.
		// Arguments:	iter	- iterator at the location of the
		//						  insert
		//				data	- the data to be assigned to the new
		//						  node
		//--------------------------------------------------------
		void Insert(DZiterator<T> iter, T data)
		{
			if (iter.listPtr != this)
			{
				DZ_LOG(DZ_LOG_WARN, "iterator is not for this list");
				return;
			}

			DZ_LOG(DZ_LOG_TRACE, "Inserting new node");

			if ((iter.isValid() == false) || (iter.nodePtr == tailPtr))
			{
				Append(data);
			}
			else
			{
				// create new node
				DZnode<T>* node_ptr = new DZnode<T>;
				node_ptr->Data = data;

				// insert the node
				node_ptr->nextPtr = iter.nodePtr->nextPtr;
				iter.nodePtr->nextPtr = node_ptr;

				Count++;
			}
		}

		//--------------------------------------------------------
		// Name:		DZlist::Remove
		// Description:	Removes node at the iterator position;
		//				the iterator remains set to the previous
		//				node (the node before the removed one)
		// Arguments:	iter	- list iterator
		//--------------------------------------------------------
		void Remove(DZiterator<T> iter)
		{
			DZnode<T>* t_ptr;
			unsigned int t_cnt;

			if (iter.listPtr != this)
			{
				DZ_LOG(DZ_LOG_WARN, "iterator is not for this list");
				return;
			}

			DZ_LOG(DZ_LOG_TRACE, "Removing existing node");

			if (iter.isValid() == false)
			{
				// nothing to do
				return;
			}

			if (Count == 1)
			{
				// remove the one node in the list
				if (headPtr == tailPtr)
				{
					delete headPtr;
					headPtr = 0;
					tailPtr = 0;
					Count = 0;
					iter.nodePtr = 0;
					return;
				}

				DZ_LOG(DZ_LOG_WARN, "List is corrupted");
				return;
			}
			else if (iter.nodePtr == headPtr)
			{
				// remove head node
				t_ptr = headPtr;
				headPtr = t_ptr->nextPtr;
				delete t_ptr;
				Count--;

				// set iterator to new head node
				iter.nodePtr = headPtr;
				return;
			}

			// find the node before the one to be removed
			t_ptr = headPtr;
			t_cnt = 1;
			while (t_ptr->nextPtr != iter.nodePtr)
			{
				t_ptr = t_ptr->nextPtr;
				t_cnt++;
				if (t_cnt >= Count)
				{
					DZ_LOG(DZ_LOG_WARN, "List is corrupted");
					return;
				}
			}

			// t_ptr is pointing to the node before the iterator

			if (iter.nodePtr == tailPtr)
			{
				// remove tail node
				tailPtr = t_ptr;
				delete t_ptr->nextPtr;
				t_ptr->nextPtr = 0;

				// set iterator to tail node
				iter.nodePtr = t_ptr;
			}
			else
			{
				// remove intermediate node
				t_ptr->nextPtr = iter.nodePtr->nextPtr;
				delete iter.nodePtr;

				// set iterator to previous node
				iter.nodePtr = t_ptr;
			}

			Count--;
		}

		//--------------------------------------------------------
		// Name:		DZlist::headRemove
		// Description:	remove the node at the head of the list
		// Arguments:	n/a
		//--------------------------------------------------------
		void headRemove()
		{
			DZ_LOG(DZ_LOG_TRACE, "Removing head node");

			DZnode<T>* t_ptr = 0;

			if (Count == 0)
			{
				// nothing to remove
				return;
			}

			t_ptr = headPtr->nextPtr;
			delete headPtr;
			headPtr = t_ptr;

			if (headPtr == 0)
			{
				// that was the last node in the list
				tailPtr = 0;
			}

			Count--;
		}

		//--------------------------------------------------------
		// Name:		DZlist::tailRemove
		// Description:	remove the node at the tail of the list
		// Arguments:	n/a
		//--------------------------------------------------------
		void tailRemove()
		{
			DZ_LOG(DZ_LOG_TRACE, "Removing tail node");

			unsigned int t_cnt;
			DZnode<T>* t_ptr = headPtr;

			if (Count == 0)
			{
				// nothing to remove
				return;
			}

			if (Count == 1)
			{
				// there is only one node on the list
				delete headPtr;
				headPtr = 0;
				tailPtr = 0;
				Count = 0;
				return;
			}

			// find the node before the one on the tail
			t_cnt = 1;
			while (t_ptr->nextPtr != tailPtr)
			{
				t_ptr = t_ptr->nextPtr;
				t_cnt++;

				if (t_cnt >= Count)
				{
					DZ_LOG(DZ_LOG_WARN, "List is corrupted");
					return;
				}
			}

			tailPtr = t_ptr;
			delete t_ptr->nextPtr;
			t_ptr->nextPtr = 0;
			Count--;
		}

		//--------------------------------------------------------
		// Name:		DZlist::getIterator
		// Description:	returns an iterator to the list
		// Arguments:	n/a
		//--------------------------------------------------------
		DZiterator<T> getIterator()
		{
			DZ_LOG(DZ_LOG_TRACE, "Returning iterator");
			return DZiterator<T>(this, headPtr);
		}

		//--------------------------------------------------------
		// Name:		DZlist::getCount
		// Description:	returns the number of nodes in the list
		// Arguments:	n/a
		//--------------------------------------------------------
		unsigned int getCount()
		{
			DZ_LOG(DZ_LOG_TRACE, "Returning number of nodes");
			return Count;
		}

		//--------------------------------------------------------
		// Name:		DZlist::store
		// Description:	stores the whole list on file
		// Arguments:	filename - the storage file
		//--------------------------------------------------------
		bool store(const char* fileName)
		{
			DZ_LOG(DZ_LOG_TRACE, "... entering...");

			DZnode<T>* t_ptr;

			ofstream outFile(fileName, ios::out);
			if (outFile == 0)
			{
				DZ_LOG(DZ_LOG_WARN, "Cannot open file for writing");
				return false;
			}

			outFile << Count << '\n';

			t_ptr = headPtr;
			for (unsigned int i=0 ; i < Count ; i++)
			{
				outFile << t_ptr->Data << '\n';
				t_ptr = t_ptr->nextPtr;
			}

			outFile.close();

			return true;
		}


		//--------------------------------------------------------
		// Name:		DZlist::retrieve
		// Description:	rebuilds a list from file contents
		// Arguments:	filename - the file where the list is stored
		//--------------------------------------------------------
		bool retrieve(const char* fileName)
		{
			DZ_LOG(DZ_LOG_TRACE, "...entering...");

			unsigned int t_cnt;
			T t_data;

			std::ifstream inFile(fileName, ios::in);
			if (inFile == 0)
			{
				DZ_LOG(DZ_LOG_WARN, "Cannot open file for reading");
				return false;
			}

			inFile >> t_cnt;

			for (unsigned int i=0 ; i < t_cnt ; i++)
			{
				inFile >> t_data;
				Append(t_data);
			}

			inFile.close();

			return true;
		}

		DZnode<T>* get_headPtr()
		{
			return headPtr;
		}

	protected:
	private:
		DZnode<T>*	headPtr;
		DZnode<T>*	tailPtr;
		unsigned int	Count;

	friend class DZiterator<T>;
};


/*****************************************************************
 *
 * Class:			DZiterator
 *
 * Description:		Iterator for single linked list
 *
 * Interface:		DZiterator	- constructor
 *					First()		- moves to the begining of
 *								  the list
 *					Next()		- moves to the next node
 *								  in the list
 *					getData()	- return reference to
 *								  current data
 *					isValid()	- determines if the iterator
 *								  points to a valid node
 *
 ****************************************************************/
template <class T> class DZiterator
{
	public:
		//--------------------------------------------------------
		// Name:		DZiterator::DZiterator
		// Description:	list iterator
		// Arguments:	list_ptr - pointer to the list object
		//				node_ptr - initializes the iterator to that
		//						   node position
		//--------------------------------------------------------
		DZiterator(DZlist<T>* list_ptr, DZnode<T>* node_ptr = 0)
		{
			DZ_LOG(DZ_LOG_TRACE, "Creating iterator");
			listPtr = list_ptr;
			nodePtr = node_ptr;
		}

		~DZiterator()
		{
			DZ_LOG(DZ_LOG_TRACE, "Destroying iterator");
		}

		//--------------------------------------------------------
		// Name:		DZiterator::First
		// Description:	move the iterator to the beginning of the list
		// Arguments:
		//--------------------------------------------------------
		void First()
		{
			DZ_LOG(DZ_LOG_TRACE, "setting iterator to head of list");
			if (listPtr != 0)
			{
				nodePtr = listPtr->get_headPtr();
			}
		}

		//--------------------------------------------------------
		// Name:		DZiterator::Next
		// Description:	advances the iterator to the next node
		// Arguments:	n/a
		//--------------------------------------------------------
		void Next()
		{
			DZ_LOG(DZ_LOG_TRACE, "Moving iterator forward");
			if (nodePtr != 0)
			{
				nodePtr = nodePtr->nextPtr;
			}
		}

		//--------------------------------------------------------
		// Name:		DZiterator::getData
		// Description:	returning reference to node data
		// Arguments:	n/a
		//--------------------------------------------------------
		T& getData()
		{
			DZ_LOG(DZ_LOG_TRACE, "Referencing node data");
			return nodePtr->Data;
		}

		//--------------------------------------------------------
		// Name:		DZiterator::isValid
		// Description:	check if the iterator is valid
		// Arguments:	n/a
		//--------------------------------------------------------
		bool isValid()
		{
			DZ_LOG(DZ_LOG_TRACE, "checking iterator validity");
			return (nodePtr != 0);
		}

		DZnode<T>* nodePtr;
		DZlist<T>* listPtr;
};

#endif // DZLIST_H
