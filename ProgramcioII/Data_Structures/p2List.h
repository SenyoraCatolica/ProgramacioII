#ifndef __p2List_H__
#define __p2List_H__

#include "p2Defs.h"
#include "p2DynArray.h"

/**
* Manages a double linked list
*/
template<class TYPE>
class p2List
{
public:

	/**
	* Node implementation
	*/
	struct node
	{
		friend class p2List<TYPE>;
	public:
		mutable TYPE	data;

		inline const node* next() const
		{
			return nxt;
		}
		inline const node* prev() const
		{
			return prv;
		}

	private:
		node*   nxt = nullptr;
		node*   prv = nullptr;

		node(const TYPE& data) : data(data)
		{}

		/* mmm .... something to think about :)
		~node()
		{
		if(prv)
		prv->nxt = nullptr;
		if(nxt)
		nxt->prv = nullptr;
		}
		*/
	};

private:

	node*   start = nullptr;

public:

	// Constructors ------------------------------------------------------

	// Destructor ---------------------------------------------------------
	~p2List()
	{
		clear();
	}

	// Operators ----------------------------------------------------------
	const p2List<TYPE>& operator +=(const p2List<TYPE>& list)
	{
		node* item = list.start;
		node* last = back_node();

		while (item != nullptr)
		{
			node* new_item = new node(item->data);

			if (last != nullptr)
			{
				new_item->prv = last;
				last->nxt = new_item;
			}
			else
				start = new_item;

			item = item->nxt;
			last = new_item;
		}
		return(*this);
	}

	const p2List<TYPE> operator +=(p2List<TYPE> second)
	{
		if (second.start != NULL)
		{
			for (unsigned int i = 0; i < second.size; i++)
			{
				add(second[i]);
			}
			return *(this);
		}
		else
			return *(this);
	}

	int find(const TYPE& data)
	{
		p2List_item<TYPE>* tmp = start;
		int index = 0;

		while (tmp != NULL)
		{
			if (tmp->data == data)
				return(index);

			++index;
			tmp = tmp->next;
		}
		return (-1);
	}

	// Data Management -----------------------------------------------------
	node* push_back(const TYPE& data)
	{
		node* item = new node(data);
		node* last = back_node();

		if (last != nullptr)
		{
			item->prv = last;
			last->nxt = item;
		}
		else
			start = item;

		return item;
	}

	node* push_front(const TYPE& data)
	{
		node* item = new node(data);

		if (start != nullptr)
		{
			item->nxt = start;
			start->prv = item;
		}

		start = item;

		return item;
	}

	bool pop_back(TYPE& data)
	{
		node* last = back_node();

		if (last != nullptr)
		{
			data = last->data;
			if (last->prv != nullptr)
				last->prv->nxt = nullptr;
			else
				start = nullptr;

			RELEASE(last);
			return true;
		}

		return false;
	}

	bool pop_front(TYPE& data)
	{
		if (start != nullptr)
		{
			data = start->data;
			node* second_node = start->nxt;
			RELEASE(start); // start is reset to nullptr inside RELEASE

			if (second_node != nullptr)
			{
				start = second_node;
				start->prv = nullptr;
			}
			return true;
		}
		return false;
	}

	void clear()
	{
		node*   item;
		node*   item_next;
		item = start;

		while (item != nullptr)
		{
			item_next = item->nxt;
			RELEASE(item);
			item = item_next;
		}

		start = nullptr;
	}

	bool erase(uint index)
	{
		node* item = at(index);

		if (item != nullptr)
		{
			if (item->nxt != nullptr)
				item->nxt->prv = item->prv;

			if (item->prv != nullptr)
				item->prv->nxt = item->nxt;

			RELEASE(item);
			return true;
		}
		return false;
	}

	bool erase(node* item)
	{
		if (item != nullptr)
		{
			if (item->nxt != nullptr)
				item->nxt->prv = item->prv;

			if (item->prv != nullptr)
				item->prv->nxt = item->nxt;

			RELEASE(item);
			return true;
		}
		return false;
	}

	bool insert(const TYPE& data, uint position)
	{
		node* item = at_node(position);

		if (position <= size())
		{
			if (position == 0)
				push_front(data);

			else if (position == size())
				push_back(data);

			else
			{
				node* new_item = new node(data);
				new_item->nxt = item;
				new_item->prv = item->prv;
				item->prv->nxt = new_item;
				item->prv = new_item;
			}

			return true;
		}
		else
			return false;
	}

	bool insert(const p2List<TYPE>& list, uint position)
	{
		node* item = at_node(position);
		node* other_list = list.start;

		if (item != nullptr && other_list != nullptr)
		{
			// copy the whole list
			node* start_new_list = nullptr;
			node* end_new_list = nullptr;

			while (other_list != nullptr)
			{
				node* new_item = new node(other_list->data);

				if (start_new_list != nullptr)
				{
					new_item->prv = end_new_list;
					end_new_list->nxt = new_item;
				}
				else
					start_new_list = new_item;

				end_new_list = new_item;
				other_list = other_list->nxt;
			}

			// now exchange pointers
			end_new_list->nxt = item;
			start_new_list->prv = item->prv;

			if (start_new_list->prv != nullptr)
				start_new_list->prv->nxt = start_new_list;

			item->prv = end_new_list;

			return true;
		}
		return false;
	}

	TYPE* at(uint index)
	{
		uint counter = 0;
		node* item = start;

		while (item != nullptr)
		{
			if (counter++ == index)
				return &(item->data);
			item = item->nxt;
		}

		return nullptr;
	}

	const TYPE* at(uint index) const
	{
		uint counter = 0;
		node* item = start;

		while (item != nullptr)
		{
			if (counter++ == index)
				return &(item->data);
			item = item->nxt;
		}

		return nullptr;
	}

	node* at_node(uint index)
	{
		uint counter = 0;
		node* item = start;

		while (item != nullptr)
		{
			if (counter++ == index)
				return item;
			item = item->nxt;
		}
		return nullptr;
	}

	const node* at_node(uint index) const
	{
		uint counter = 0;
		node* item = start;

		while (item != nullptr)
		{
			if (counter++ == index)
				return item;
			item = item->nxt;
		}
		return nullptr;
	}

	/*void AddArray(uint pos, const p2DynArray<TYPE> array_to_add)
	{
		for (uint i = 0; i < array_to_add.size(); i++)
			insert(array_to_add[i], pos++);
	}*/

	uint delNodes(unsigned int position, unsigned int NodesToDelete)
	{
		uint ret = 0;
		if (position > size || NodesToDelete == 0)
		{
			return 0;
		}
		p2List_item<TYPE>* first_item = start;

		for (uint i = 0; i < position; i++)
			first_item = first_item->next;

		p2List_item<TYPE>* last_item = first_item;

		for (uint i = 1; i < NodesToDelete && last_item->next != NULL; i++)
			last_item = last_item->next;

		if (first_item->prev != NULL)
		{
			first_item->prev->next = last_item->next;

			if (last_item->next != NULL)
				last_item->next->prev = first_item->prev;

			else
				end = first_item->prev;
		}
		else
		{
			if (last_item->next != NULL)
				start = last_item->next;
			else
				start = end = NULL;
		}
		p2List_item<TYPE>* tmp = first_item;
		ret = 1;
		while (tmp != last_item)
		{
			tmp = tmp->next;
			delete first_item;
			first_item = tmp;
			ret++;
		}
		delete last_item;
		size -= ret;
		return ret;
	}

	// Utils ------------------------------------------------------------
	uint size() const
	{
		uint ret = 0;

		for (node* item = start; item != nullptr; item = item->nxt)
			++ret;

		return ret;
	}

	bool empty() const
	{
		return start == nullptr;
	}

	node* front_node()
	{
		return start;
	}

	const node* front_node() const
	{
		return start;
	}

	node* back_node()
	{
		node* item = start;
		node* last_item = nullptr;
		while (item != nullptr)
		{
			last_item = item;
			item = item->nxt;
		}

		return last_item;
	}

	const node* back_node() const
	{
		node* item = start;
		node* last_item = nullptr;
		while (item != nullptr)
		{
			last_item = item;
			item = item->nxt;
		}

		return last_item;
	}

	TYPE* front()
	{
		if (start != nullptr)
			return &(start->data);
		return nullptr;
	}

	const node* front() const
	{
		if (start != nullptr)
			return &(start->data);
		return nullptr;
	}

	TYPE* back()
	{
		node* item = start;
		node* last_item = nullptr;
		while (item != nullptr)
		{
			last_item = item;
			item = item->nxt;
		}

		return (last_item != nullptr) ? &(last_item->data) : nullptr;
	}

	const TYPE* back() const
	{
		node* item = start;
		node* last_item = nullptr;
		while (item != nullptr)
		{
			last_item = item;
			item = item->nxt;
		}

		return (last_item != nullptr) ? &(last_item->data) : nullptr;
	}

	// Sort -------------------------------------------------------------
	int BubbleSort()
	{
		int ret = 0;
		bool swapped = true;

		while (swapped)
		{
			swapped = false;
			node* tmp = start;

			while (tmp != nullptr && tmp->nxt != nullptr)
			{
				++ret;
				if (tmp->data > tmp->nxt->data)
				{
					SWAP(tmp->data, tmp->nxt->data);
					swapped = true;
				}

				tmp = tmp->nxt;
			}
		}

		return ret;
	}


	void Flip()
	{
		node* tmp1 = back_node();
		for (uint i = size(); i > 0; i--)
		{
			node* tmp2 = tmp1;

			if (tmp1->nxt != nullptr)
			{
				tmp1 = tmp1->prv;
				tmp2->prv = tmp2->nxt;
				tmp2->nxt = tmp1;

			}

			else if (tmp1->nxt == NULL)
			{
				tmp1->nxt = tmp1->prv;
				tmp1->prv = nullptr;
				start = tmp1;
				tmp1 = tmp1->nxt;
			}

			else 
			{
				tmp1->prv = tmp1->nxt;
				tmp1->nxt = nullptr;			
			}


		}

	}


		
	TYPE& operator[](const TYPE index)
		{
			node* item = start;
			if (index == 0)
			{
				return item->data;
			}
			for (uint i = 0; i < index; i++)
			{
				item = item->nxt;
			}

			return item->data;
		}
};

#endif /*__p2List_H__*/


	


