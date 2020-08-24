// FILE: node.cpp
//
//
//  COEN 79
//  --- Farokh Eskafi, COEN, SCU ---
//
//
// IMPLEMENTS: The functions of the node class and the
// linked list toolkit (see node1.h for documentation).
//
// INVARIANT for the node class:
//   The data of a node is stored in data_field
//   and the link to the next node is stored in link_field.

#include "node.h"
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t
#include <iostream>

//using namespace std;

namespace coen79_lab6
{
    size_t list_length(const node* head_ptr)
    // Library facilities used: cstdlib
    {
	const node *cursor;
	size_t answer;

	answer = 0;
	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
	    ++answer;

	return answer;
    }

    void list_head_insert(node*& head_ptr, const node::value_type& entry)
    {
    	head_ptr = new node(entry, head_ptr);
    }

    void list_insert(node* previous_ptr, const node::value_type& entry)
    {
    	node *insert_ptr;

    	insert_ptr = new node(entry, previous_ptr->link( ));
    	previous_ptr->set_link(insert_ptr);
    }

    node* list_search(node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    const node* list_search(const node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	const node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    node* list_locate(node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    const node* list_locate(const node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	const node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    void list_head_remove(node*& head_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = head_ptr;
    	head_ptr = head_ptr->link( );
    	delete remove_ptr;
    }

    void list_remove(node* previous_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = previous_ptr->link( );
    	previous_ptr->set_link( remove_ptr->link( ) );
    	delete remove_ptr;
    }

    void list_clear(node*& head_ptr)
    // Library facilities used: cstdlib
    {
    	while (head_ptr != NULL)
    	    list_head_remove(head_ptr);
    }

    void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
    // Library facilities used: cstdlib
    {
    	head_ptr = NULL;
    	tail_ptr = NULL;

    	// Handle the case of the empty list.
    	if (source_ptr == NULL)
    	    return;

    	// Make the head node for the newly created list, and put data in it.
    	list_head_insert(head_ptr, source_ptr->data( ));
    	tail_ptr = head_ptr;

    	// Copy the rest of the nodes one at a time, adding at the tail of new list.
    	source_ptr = source_ptr->link( );
    	while (source_ptr != NULL)
    	{
    	    list_insert(tail_ptr, source_ptr->data( ));
    	    tail_ptr = tail_ptr->link( );
    	    source_ptr = source_ptr->link( );
    	}
    }

    


//FUNCTIONS
//WRITTEN
//BY
//SILAS KIDD MYERS

    void list_piece(node* start_ptr, node* end_ptr, node*& head_ptr, node*& tail_ptr)
	{
    	head_ptr = NULL;
    	tail_ptr = NULL;

    	// Handle the case of the empty list.
    	if (start_ptr == NULL)
    	    return;

    	// Make the head node for the newly created list, and put data in it.
    	list_head_insert(head_ptr, start_ptr->data( ));
    	tail_ptr = head_ptr;

    	// Copy the rest of the nodes one at a time, adding at the tail of new list.
    	while(start_ptr != end_ptr)
    	{
    	    list_insert(tail_ptr, start_ptr->data( ));
    	    tail_ptr = tail_ptr->link( );
    	    start_ptr = start_ptr->link( );
    	}
	}

    size_t list_occurrences(node* head_ptr, const node::value_type& target)
	{
		size_t cnt = 0;
		node* p = head_ptr;
		if(head_ptr == NULL)
			return cnt;
		while(p != NULL)
		{
			if(p->data() == target)//increment count when found data
				cnt++;
			p = p->link();
		}
		return cnt;
	}

    void list_insert_at(node*& head_ptr, const node::value_type& entry, size_t position)
	{
		assert(position > 0);
		assert(position <= list_length(head_ptr) + 1);

		if(position == 1)//head insert
		{
			list_head_insert(head_ptr, entry);
		}
		else
		{
			list_insert(list_locate(head_ptr, position - 1), entry);
		}
	}

    node::value_type list_remove_at(node*& head_ptr, size_t position)
	{
		assert(head_ptr != NULL);
		assert(position > 0);
		assert(position <= list_length(head_ptr));

		node::value_type pop_value = list_locate(head_ptr, position)->data();

		if(position == 1)//head delete
		{
			list_head_remove(head_ptr);
		}
		else
		{
			list_remove(list_locate(head_ptr, position - 1));
		}
		return pop_value;
	}

    node* list_copy_segment(node* head_ptr, size_t start, size_t finish)
	{	
		assert((1 <= start) && (start <= finish) && (finish <= list_length(head_ptr)));
    	if (head_ptr == NULL)// Handle the case of the empty list.
    	    return NULL;
		node* new_head = NULL;
		node* new_tail = NULL;

		node* begin = list_locate(head_ptr, start);//get node* from start and end
		node* end = list_locate(head_ptr, finish);

		list_piece(begin, end, new_head, new_tail);//reuse list pice but in altered format
		return new_head;
	}

    void list_print(const node* head_ptr)
	{
		if(head_ptr == NULL)
		{
      		std::cout << std::endl;
      		return;
    	}
		while(head_ptr != NULL)
		{
			std::cout << head_ptr->data() << ", ";
			head_ptr = head_ptr->link();
		}

	}

    void list_remove_dups(node* head_ptr)
	{
		if(head_ptr == NULL)
		{
     		return;
    	}
		node* head_ptr_cursor = head_ptr;//increments every loop in order to test every combo
		node* p = head_ptr->link();
		node::value_type test_value;
		int pos_head_cursor = 1, pos = 2;

		while(head_ptr_cursor->link() != NULL)//nested loop to systematically go through every combination of items
		{	
			test_value = head_ptr_cursor->data();//value that is being tested in each loop
			while(p != NULL)
			{
				if(p->data() == test_value)//if p is a duplicate
				{
					list_remove_at(head_ptr, pos);
				}
				p = p->link();
				pos++;
			}
			head_ptr_cursor = head_ptr_cursor->link();
			p = head_ptr_cursor->link();
			pos_head_cursor++;
			pos = pos_head_cursor + 1;
		}
	}

    node* list_detect_loop (node* head_ptr)
	{
		assert(head_ptr != NULL);
		node* p = head_ptr->link();
		node* head_cursor = head_ptr;//p acts as a head_ptr_cursor
		while(head_cursor->link() != NULL)//nested loop to systematically go through every combination of items
		{	
			while(p != NULL)
			{
				if(p == head_cursor)//if q eventually links back to p
				{
					return head_cursor;//return p as the headptr that loops
				}
				p = p->link();
			}
			head_cursor = head_cursor->link();//increment head
			p = head_cursor->link();//p needs to start with head
		}
		return NULL;			
	}

}
