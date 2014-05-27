// Rahul Palamuttam, rpalamut@ucsc.edu
// Programming Assigment 1 : Lex
// $Id: Lex.java,v 1.3 2014-01-12 03:14:15-08 - - $
import java.io.*;
import java.util.Scanner;
import static java.lang.System.*;
class Lex{
    
    static Scanner open(String filename){
	Scanner scan = null;
	try{
	    scan = new Scanner(new File(filename));
	} catch (IOException except){
	    System.err.println("Invalid filename");
	    exit(1);
	}
	return scan;
    }
    
    // counts the lines in the file
    static int countlines(Scanner file){
	int index = 0;
	for(; file.hasNextLine(); file.nextLine()) index++;
	return index;
    }

    // stores each line in an array
    static String[] read(Scanner file, int lines){
	String[] array = new String[lines];
	for(int i = 0; file.hasNextLine(); i++){
	    array[i] = file.nextLine();
	}
	return array;
    }
    
    // carries out insertion sort
    static List insertsort(String[] file){	
	List list = new List();
	// puts in the first element into the list
	if (file.length > 0) list.append(0);
	// the sorting
	for (int j = 1; j < file.length; j++){
	    String temp = file[j];
	    int index = j - 1;
	    // move cursor to current position
	    list.moveTo(index);
	    while (index > -1 && temp.compareTo(file[list.getElement()]) < 1){	
		index--;
		list.movePrev();
	    }

	    // if cursor is null, then prepend
	    // otherwise insert after it
	    if(list.getIndex() == -1){
		list.prepend(j);
	    } else {
		list.insertAfter(j);
	    }
	}
    
	return list;
    }
    
    public static void main (String[] args){
	// checks for proper number of arguements
	if(args.length != 2) {
	    System.err.println("Invalid inputs");
	    exit(1);
	}

	// stores files in scanner objects
	Scanner input = open(args[0]);
	PrintWriter writer = null;
	try {
	    writer = new PrintWriter(new FileWriter(args[1]));
	} catch (FileNotFoundException excep){
	    System.err.println("Could not create the file");
	    exit(1);
	} catch (IOException excep){
	    System.err.println("Could not create the file");
	    exit(1);
	}

	// prints out the line numbers
	int linecount = countlines(input);	
	// resets line Scanner line pointer
	input = open(args[0]);
	String[] array = read (input, linecount);
	// stores indices in list without affecting array elements
	List list = insertsort(array);
	// writes the lines to the files
	for(list.moveTo(0); list.getIndex()>=0; list.moveNext()){
	    writer.println(array[list.getElement()]);
	}

	writer.close();
	
    }

}