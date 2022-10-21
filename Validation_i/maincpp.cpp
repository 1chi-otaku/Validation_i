#include <iostream>
#include <fstream>
#include <stack>

using namespace std;
int main() {
    const int size = 128;
    string buffer;

    fstream read("Test.html", ios::in);
    stack <string> stack; //Creating stack to еo check if the tag sequence is correct.
    if (read) // If the file opens successfully
    {
        while (!read.eof()) //While it's not end of file.
        {
            //Checking basic syntax 
            read >> buffer;                                     //reading string.
            cout << buffer << endl;                             //printing string.
            if (buffer[0] == '>') {                             //If the tag is something like that: >head>, gives an error message immediately.
                cout << "<- Invalid syntax" << endl;
                read.close();
            }
            if (buffer[0] == '<') {                             //If the string starts with < checks if it ends with >, otherwise, gives an error message immediately.
                if (buffer[buffer.size() - 1] != '>') {
                    cout << "<- Invalid syntax" << endl;
                    read.close();
                }
            }

            //Checking tag sequence for head, title and body tags.
            if (buffer == "<head>") stack.push("</head>");      //If the current string is <head>, pushes </head> to the stack.
            if (buffer == "<title>") stack.push("</title>");    //If the current string is <title>, pushes </title> to the stack.
            if (buffer == "<body>")   stack.push("</body>");    //If the current string is <body>, pushes </body> to the stack.

            if (buffer == "</head>" ||    //If the current string is </head>, </title> or </body>
                buffer == "</title>" ||
                buffer == "</body>")
            {
                if (stack.empty() || stack.top() != buffer) {  //1. Checks if the stack is empty. 2. If the sequence is correct on the top of the stack has to be the same tag we have in buffer now.
                    cout << "<- Tag sequence error" << endl;   //If any condition is true, gives an error message immediately.
                    read.close();
                }
                stack.pop();                                   //Otherwise, pops top value from the stack. If the sequence is correct, stack has to be EMPTY.
            }


        }
        read.close();
    }
    else
    {
        cout << "Could not open the file" << endl;          //If file cannot be opened, gives an error message immediately.
    }


    if (stack.empty()) {    //If the stack is empty, the sequence of tags is correct. 
        cout << "Success!" << endl;
    }
    else //Otherwise, there has to be a problem in sequence...
        cout << "Sequence error." << endl;



    return 0;
}