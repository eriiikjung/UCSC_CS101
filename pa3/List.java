// Rahul Palamuttam, rpalamut@ucsc.edu
// Programming Assigment 3 : Matrix Math
// $Id: List.java,v 1.4 2014-02-06 01:06:14-08 - - $
class List {
    private class node {
	Object data;
	node prev;
	node next;
	
	//first constructor for first node
	node(Object num){
	    data = num;
	    prev = null;
	    next = null;
	}

	// useful for inserting a new node
	node(Object num, node previous, node after){
	    data = num;
	    prev = previous;
	    next = after;
	}
	// to string method
	public String toString(){
	    return "" + data;
	}
    }
    
    // More of a state variable for cursor
    private static final node OFF = null;
    private node cursor;
    private node front;
    private node back;
    private int length;
    
    // Creates a new empty list
    public List (){
	cursor = OFF;
	front = null;
	back = null;
	length = 0;
    }

    // Returns number of elements in list
    public int length() {
	return length;
    }
    
    // Returns the index of the cursor element
    // or -1 if undefined
    public int getIndex(){
	int index = -1;
	if (cursor == OFF) return index;
	for (node tmp = front; tmp != null; tmp = tmp.next){
	    index++;
	    if (tmp == cursor) break;
	}
	return index;   
    }
    
    // Returns front element if length > 0
    public Object front() {
	if (length() > 0) {
	    return front.data;
	} 
	  
	return null;
    }

    // Returns back element if length > 0
    public Object back() {
	if (length() > 0){
	    return back.data;
	}

	return null;
    }
    
    // Returns cursor element in this list
    public Object getElement(){
	if (length() > 0 && getIndex() >= 0) return cursor.data;
	return null;
    }

    //Returns true if this List and L are same integer sequence
    public boolean equals(Object L){
	if (L == null || !(L instanceof List)) {
	    System.out.println("List:equals: incorrect parameter type");
	    return false;
	}
	node right = front;
	node left = ((List)L).front;
	// checks if corresponding indices are incorrect
	while (right != null && left != null){
	    if (!(right.data.equals(left.data))){
		return false;
	    }
	    right = right.next;
	    left = left.next;
	}
	// if either list had more elements than the other
	if (right != null || left != null) return false;
	return true;
    }

    // Re-sets this List to the empty state
    public void clear(){
	cursor = OFF;
	front = null;
	back = null;
	length = 0;
    }
    
    // moves the cursor to index i
    public void moveTo(int i){
	if (i >= 0 && i <= length() - 1){
	    cursor = front;
	    for(; i > 0; i--) cursor = cursor.next;
	} else {
	    cursor = OFF;
	}
    }
    
    // this operation is equivalent to moveTo(getIndex() -1)
    // it is much more efficient, since it doesn't traverse
    // the list twice
    public void movePrev(){
	int index = getIndex();
	if (index > 0 && index <= length() - 1){
	    cursor = cursor.prev;
	} else {
	    cursor = OFF;
	}
    }

    // like movePrev() but moves the cursor one step forward
    public void moveNext(){
	int index = getIndex();
	if(index >= 0 && index < length() - 1){
	    cursor = cursor.next;
	} else {
	    cursor = OFF;
	}
    }
    
    // prepends to the list
    public void prepend(Object data){
	length++;
	node node = new node(data,null, front);
	if (front != null) {
	    front.prev = node;
	} else {
	    back = node;
	}
	front = node;
    }

    // appends to the list
    public void append(Object data){
	length++;
	node temp = new node(data, back, null);
	if (back != null) {
	    back.next = temp;
	} else {
	    front = temp;
	}
	back = temp;
    }
    
    // inserts an element before the cursor
    public void insertBefore(Object data){
	if (!(length() >0 && getIndex() >=0)) return;
	length++;
	node temp = new node(data, cursor.prev, cursor);
	// make sure node exists before cursor
	// if the cursor is the front node
	// front must be changed accordingly
	if (cursor.prev != null) {
	    cursor.prev.next = temp;
	} else {
	    front = temp;
	}

	cursor.prev = temp;
    }
    
    public void insertAfter(Object data){
	if(!(length() >0 && getIndex() >=0)) return;
	length++;
	node temp = new node(data, cursor, cursor.next);
	// make sure node exists after cursor
	// if the cursor is the back node
	// back must be changed to the new node
	if (cursor.next != null){
	    cursor.next.prev = temp;
	} else {
	    back = temp;
	}

	cursor.next = temp;
    }

    // deletes the front node
    public void deleteFront(){
	if (length() > 0) {
	    length--;
	    // if the cursor happens to be the front node
	    // then it must be set to OFF
	    if(cursor == front) cursor = OFF;
	    front = front.next;
	    front.prev = null;
	}
    }

    // deletes the backnode
    public void deleteBack(){
	if (length() > 0){
	    length--;
	    // if the cursor happens to be the backnode
	    // then it must be set to OFF
	    if(cursor == back) cursor = OFF;
	    back = back.prev;
	    back.next = null;
	}
    }

    // deletes the cursor node
    public void delete(){	
	if (cursor == front){
	    deleteFront();
	} else if (cursor == back){
	    deleteBack();
	}
	
	if (length() > 0 && getIndex() > 0){
	    length--;
	    cursor.next.prev = cursor.prev;
	    cursor.prev.next = cursor.next;
	    cursor = OFF;
	}
	
    }

    public String toString() {
	String result = "";
	node temp = front;
	while (temp.next != null){
	    result += temp + " ";
	    temp = temp.next;
	}
	result += temp;
	return result;
    }

}