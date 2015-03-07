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
 * 03-05-2015	file created                                              *
 **************************************************************************/


#ifndef DZDLIST_H
#define DZDLIST_H


#include "DZlogger.h"


template <class T> class DZdNode;
template <class T> class DZdIterator;
template <class T> class DZdList;


/*****************************************************************
 *
 * Class:		DZnode
 *
 * Description:	General node of the double linked list.
 *				It holds the pointer to the next and
 *				previous node and the data itself.
 *
 * Interface:	n/a
 *				DZdNode is used internally in DZdList
 *
 ****************************************************************/
template <class T> class DZdNode
{
	public:
		T Data;
		DZdNode<T>* nextPtr;
		DZdNode<T>* prevPtr;

		DZdNode()
		{
			DZ_LOG(DZ_LOG_TRACE, "Creating node");
			nextPtr = 0;
			prevPtr = 0;
		}

		~DZdNode()
		{
			DZ_LOG(DZ_LOG_TRACE, "Destroying node");
		}
};



/*****************************************************************
 *
 * Class:		DZdList
 *
 * Description:	Double linked list
 *
 * Interface:	DZdList()	- constructor
 *				~DZdList()	- destructor
 *				Append(data)	- append node to the end
 *								  of the list
 *				Prepend(data)	- add node to the beginning
 *								  of the list
 *				Insert(iterator,data)
 *								- insert node at the specified
 *								  position; node previously
 *								  at that position is moved
 *								  forward
 *				Remove(iterator)- remove node at specified
 *								  position
 *				headRemove()	- remove node at the head
 *								  of the list
 *				tailRemove()	- remove node at the tail
 *								  of the list
 *				getIterator()	- gets an iterator for the
 *								  list, positioned at the
 *								  head
 *				getCount()		- gets the number of nodes
 *								  in the list
 *				store(filename) - store list in to given file
 *				retrieve(filename)
 *								- retrieves list from
 *								  given file
 *
 ****************************************************************/
template <class T> class DZdList
{
	public:
		//--------------------------------------------------------
		// Name:		DZdList::DZdList
		// Description:	constructor for an empty list
		// Arguments:	n/a
		//--------------------------------------------------------
		DZdList()
		{
			DZ_LOG(DZ_LOG_TRACE, "Creating list");
			headPtr = 0;
			tailPtr = 0;
			Count = 0;
		}

		//--------------------------------------------------------
		// Name:		DZdList::~DZdList
		// Description:	destructor; removes every node
		// Arguments:	n/a
		//--------------------------------------------------------
		~DZdList()
		{
			DZdNode<T>* iter = headPtr;
			DZdNode<T>* nextNodePtr;

			DZ_LOG(DZ_LOG_TRACE, "Destroying list");

			while (iter != 0)
			{
				nextNodePtr = iter->nextPtr;
				delete iter;
				iter = nextNodePtr;
			}
		}

		//--------------------------------------------------------
		// Name:		DZdList::Append
		// Description:	append a new node to the end of the list
		// Arguments:	data	- data to be stored in the node
		//--------------------------------------------------------
		void Append(T data)
		{
			DZ_LOG(DZ_LOG_TRACE, "Appending new node");

			DZdNode<T>* node_ptr = new DZdNode<T>;
			node_ptr->Data = data;

			if (headPtr == 0)
			{
				headPtr = node_ptr;
				tailPtr = node_ptr;
			}
			else
			{
				node_ptr->prevPtr = tailPtr;
				tailPtr->nextPtr = node_ptr;
				tailPtr = node_ptr;
			}

			Count++;
		}

		//--------------------------------------------------------
		// Name:		DZdList::Prepend
		// Description:	prepend a new node to the beginning of the
		//				list
		// Arguments:	data	- data to be stored in the node
		//--------------------------------------------------------
		void Prepend(T data)
		{
			DZ_LOG(DZ_LOG_TRACE, "prepending new node");

			DZdNode<T>* node_ptr = new DZdNode<T>;
			node_ptr->Data = data;

			if (Count == 0)
			{
				headPtr = node_ptr;
				tailPtr = node_ptr;
			}
			else
			{
				node_ptr->nextPtr = headPtr;
				headPtr->prevPtr = node_ptr;
				headPtr = node_ptr;
			}

			Count++;
		}

		//--------------------------------------------------------
		// Name:		DZdList::Insert
		// Description:	Insert a new node after the iterator. If the
		//				iterator is invalid it will do an append.
		// Arguments:	iter	- iterator at the location of the
		//						  insert
		//				data	- the data to be assigned to the new
		//						  node
		//--------------------------------------------------------
		void Insert(DZdIterator<T> iter, T data)
		{
			if (iter.listPtr != this)
			{
				DZ_LOG(DZ_LOG_WARN, "iterator is not for this list");
				return;
			}

			DZ_LOG(DZ_LOG_TRACE, "Inserting new node");

			if ((Count == 0) || iter.isValid() == false)
			{
				Append(data);
				return;
			}

			// create new node
			DZdNode<T>* node_ptr = new DZdNode<T>;
			node_ptr->Data = data;

			if (Count == 1)
			{
				tailPtr = node_ptr;
				headPtr->nextPtr = node_ptr;
				node_ptr->prevPtr = headPtr;
			}
			else
			{
				node_ptr->nextPtr = iter.nodePtr->nextPtr;
				node_ptr->prevPtr = iter.nodePtr;
				iter.nodePtr->nextPtr->prevPtr = node_ptr;
				iter.nodePtr->nextPtr = node_ptr;
			}

			Count++;
		}

		//--------------------------------------------------------
		// Name:		DZdList::Remove
		// Description:	Removes node at the iterator position;
		//				the iterator remains set to the previous
		//				node (the node before the removed one)
		// Arguments:	iter	- list iterator
		//--------------------------------------------------------
		void Remove(DZdIterator<T> iter)
		{
			DZdNode<T>* t_ptr;

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
				iter.nodePtr->nextPtr->prevPtr = 0;
				t_ptr = headPtr;
				headPtr = t_ptr->nextPtr;
				delete t_ptr;

				// set iterator to new head node
				iter.nodePtr = headPtr;
			}
			else if (iter.nodePtr == tailPtr)
			{
				// remove tail node
				t_ptr = tailPtr;
				tailPtr = tailPtr->prevPtr;
				tailPtr->nextPtr = 0;
				delete t_ptr;

				// set iterator to tail node
				iter.nodePtr = tailPtr;
			}
			else
			{
				// remove intermediate node
				iter.nodePtr->nextPtr->prevPtr = iter.nodePtr->prevPtr;
				iter.nodePtr->prevPtr->nextPtr = iter.nodePtr->nextPtr;
				t_ptr = iter.nodePtr->prevPtr;
				delete iter.nodePtr;

				// set iterator to previous node
				iter.nodePtr = t_ptr;
			}

			Count--;
		}

		//--------------------------------------------------------
		// Name:		DZdList::headRemove
		// Description:	remove the node at the head of the list
		// Arguments:	n/a
		//--------------------------------------------------------
		void headRemove()
		{
			DZ_LOG(DZ_LOG_TRACE, "Removing head node");

			DZdNode<T>* t_ptr = 0;

			if (Count == 0)
			{
				// nothing to remove
				return;
			}
			else if (Count == 1)
			{
				delete headPtr;
				headPtr = 0;
				tailPtr = 0;
			}
			else
			{
				headPtr->nextPtr->prevPtr = 0;
				t_ptr = headPtr->nextPtr;
				delete headPtr;
				headPtr = t_ptr;
			}

			Count--;
		}

		//--------------------------------------------------------
		// Name:		DZdList::tailRemove
		// Description:	remove the node at the tail of the list
		// Arguments:	n/a
		//--------------------------------------------------------
		void tailRemove()
		{
			DZ_LOG(DZ_LOG_TRACE, "Removing tail node");

			DZdNode<T>* t_ptr;

			if (Count == 0)
			{
				// nothing to remove
				return;
			}
			else if (Count == 1)
			{
				// there is only one node on the list
				delete headPtr;
				headPtr = 0;
				tailPtr = 0;
				Count = 0;
			}
			else
			{
				t_ptr = tailPtr;
				tailPtr->prevPtr->nextPtr = 0;
				tailPtr = tailPtr->prevPtr;
				delete t_ptr;
			}

			Count--;
		}

		//--------------------------------------------------------
		// Name:		DZdList::getIterator
		// Description:	returns an iterator to the list
		// Arguments:	n/a
		//--------------------------------------------------------
		DZdIterator<T> getIterator()
		{
			DZ_LOG(DZ_LOG_TRACE, "Returning iterator");
			return DZdIterator<T>(this, headPtr);
		}

		//--------------------------------------------------------
		// Name:		DZdList::getCount
		// Description:	returns the number of nodes in the list
		// Arguments:	n/a
		//--------------------------------------------------------
		unsigned int getCount()
		{
			DZ_LOG(DZ_LOG_TRACE, "Returning number of nodes");
			return Count;
		}

		//--------------------------------------------------------
		// Name:		DZdList::store
		// Description:	stores the whole list on file
		// Arguments:	filename - the storage file
		//--------------------------------------------------------
		bool store(const char* fileName)
		{
			DZ_LOG(DZ_LOG_TRACE, "... entering...");

			DZdNode<T>* t_ptr;

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
		// Name:		DZdList::retrieve
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

		DZdNode<T>* get_headPtr()
		{
			return headPtr;
		}

		DZdNode<T>* get_tailPtr()
		{
			return tailPtr;
		}

	protected:
	private:
		DZdNode<T>*	headPtr;
		DZdNode<T>*	tailPtr;
		unsigned int	Count;
};


/*****************************************************************
 *
 * Class:		DZdIterator
 *
 * Description:	Iterator for single linked list
 *
 * Interface:	DZdIterator	- constructor
 *				First()		- moves to the begining of
 *							  the list
 *				Last()		- moves to the end of the
 *							  list
 *				Next()		- moves to the next node
 *							  in the list
 *				Previous()	- moves to the previous
 *							  node in the list
 *				getData()	- return reference to
 *							  current data
 *				isValid()	- determines if the iterator
 *							  points to a valid node
 *
 ****************************************************************/
template <class T> class DZdIterator
{
	public:
		DZdNode<T>* nodePtr;
		DZdList<T>* listPtr;

		//--------------------------------------------------------
		// Name:		DZdIterator::DZdIterator
		// Description:	list iterator
		// Arguments:	list_ptr - pointer to the list object
		//				node_ptr - initializes the iterator to that
		//						   node position
		//--------------------------------------------------------
		DZdIterator(DZdList<T>* list_ptr = 0, DZdNode<T>* node_ptr = 0)
		{
			DZ_LOG(DZ_LOG_TRACE, "Creating iterator");
			nodePtr = node_ptr;
			listPtr = list_ptr;
		}

		~DZdIterator()
		{
			DZ_LOG(DZ_LOG_TRACE, "Destroying iterator");
		}

		//--------------------------------------------------------
		// Name:		DZdIterator::First
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
		// Name:		DZdIterator::Last
		// Description:	move the iterator to the beginning of the list
		// Arguments:
		//--------------------------------------------------------
		void Last()
		{
			DZ_LOG(DZ_LOG_TRACE, "setting iterator to tail of list");
			if (listPtr != 0)
			{
				nodePtr = listPtr->get_tailPtr();
			}
		}

		//--------------------------------------------------------
		// Name:		DZdIterator::Next
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
		// Name:		DZdIterator::Previous
		// Description:	advances the iterator to the next node
		// Arguments:	n/a
		//--------------------------------------------------------
		void Previous()
		{
			DZ_LOG(DZ_LOG_TRACE, "Moving iterator backward");
			if (nodePtr != 0)
			{
				nodePtr = nodePtr->prevPtr;
			}
		}

		//--------------------------------------------------------
		// Name:		DZdIterator::getData
		// Description:	returning reference to node data
		// Arguments:	n/a
		//--------------------------------------------------------
		T& getData()
		{
			DZ_LOG(DZ_LOG_TRACE, "Referencing node data");
			return nodePtr->Data;
		}

		//--------------------------------------------------------
		// Name:		DZdIterator::isValid
		// Description:	check if the iterator is valid
		// Arguments:	n/a
		//--------------------------------------------------------
		bool isValid()
		{
			DZ_LOG(DZ_LOG_TRACE, "checking iterator validity");
			return (nodePtr != 0);
		}
};

#endif // DZDLIST_H
