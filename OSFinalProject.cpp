//Jerrod Koenigseder
//001187225 -- Student ID #

#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

/*
*               Method to print queue
* while the queue is not empty print the first value then remove it
* this sets the next value to now be the front. Continues until queue is emtpy. 
* Nothing needs to be returned since the function will print the values, and the
* only parameter needed is the queue with values
*/
void print_queue(queue<int> q)
{
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << '\n';
}


/*
             FIFO Algorithim
   The purpose of this function is to calculate the page faults
   that would result from the reference string based on the number
   of frames allowed. 
   Parameters = # of frames allowed, the reference string to test with, and count is the size of the reference string
   Output = Returns the number of page faults calculated
*/
int FIFOalg(char frame, int refString[], int count)                     
{
    int pageFaults = 0;   //to track the number of pagefaults                             
    int i = 0;            //general incrementer, will be used to ensure the algo only goes until the end of the reference string
    bool test = false;    //
    int framesFull = 0;   //to keep track of the frames and once capacity is reached
    queue<int> q;         //
    queue<int> q2;        //


                       
    while (i < count)                                                       //while i is less than the size of the reference string
    { 
        
        if (q.empty()) {                                                    //if the queue is empty we can add the first value, increment the number of page faults, number of frames used, and i 
            q.push(refString[i]);
            i++;
            framesFull++;
            pageFaults++;
        }
        else if (framesFull == frame)                                      //if the number of frames has been reached
        {
            q2 = q;                                                        //set q2 (the second queue) equal to the first queue (q)
            while (!q2.empty())                                            //now we get confusing
            {                                                              //while q2 is not empty, check current reference string value against the first value in the queue
                if (q2.front() != refString[i])                            //if they are not equal, pop the first value in the queue and check again. Keep going until either
                    q2.pop();                                              //the reference string values equals a value in the queue or the queue becomes empty
                else
                {
                    i++;                                                   //if the reference string values does equal a value in the queue, skip it by incrementing i and breaking from the loop
                    test = true;
                }
                if (test)
                    break;
            }
            test = false;

            if (q2.empty())                                                 //if q2 is now empty, that means the reference string value did not equal a current value in the frames
            {                                                               //Because queues are FIFO data structures we can pop the first value and add the new value
                q.pop();                                                    //incrememnt page faults as a new value has been added
                q.push(refString[i]);
                pageFaults++;
                  
            }
        }      
        else if (q.front() != refString[i])                                 //check if the current reference string value equals in the front of the queue
        {
            q2 = q;                                                         //if it does not, set the second queue equal to the first
            if (q2.size() == 1)                                             //if there is only one value in the queue we can add the reference string value because we know they are not equal
            {
                q.push(refString[i]);
                pageFaults++;
                framesFull++;
                i++;
            }
            else {                                                          //if the second queue has more than one value
                while (q2.size() >= 1)                                      //while the size of the queue remains greater than or equal to one
                { 
                    q2.pop();                                               //remove the first value as we know it doesn't equal the reference string value
                    if (q2.front() != refString[i] && q2.size() == 1)       //if the front value does not equal the reference string vlaue and the size of the queue is one
                    {
                        test = true;                                        //set test to true in order to add it to the original queue
                        break;
                    }
                    else
                    {
                        test = false;                                       //if the values are equal or the string is not one we keep checking
                    }
                }
            }
            if (test)                                                     //if test is true then a value needs to be added
            {
                q.push(refString[i]);                                     //add said value to the queue and incrememnt page faults, i, and number of frames occupied
                i++;
                pageFaults++;
                framesFull++;
            }
        }


        else if (q.front() == refString[i] || q.back() == refString[i])              //if the value does equal then we do not need to add it
        {
            i++;
            continue;
        }
        
       
    }
    cout << endl;
    print_queue(q);
    return pageFaults;
}


//creates the node structure that will be used in the linked list
//data is the value the node holds
//next is a pointer
struct node
{
    int data;
    node* next;
};


//linkedList class
//holds all functions needed for the linked list

class linkedList
{

    //a pointer to the head and tail of the list
    //count which is used in later functions
public:
    node* head, * tail;
 


    //constructor 
    //initially sets the head and tail null
    linkedList()
    {
        head = NULL;
        tail = NULL;
    }


    //since the head is the beginning of the list, if it is null then the list must be empty
    bool empty()
    {
        if (head == NULL)
            return true;
        else
            return false;
    }


    //method to add a new node into the list
    //does not return anything but requires the data that will be associated with the node
    void insertNewNode(int data)
    {
        node* temp = new node; //creates a pointer called temp to a new node
        temp->data = data;     //assigns the data that was passed to the temp pointer
        temp->next = NULL;     //sets the default value of next (the next node in the list) to null

        if (head == NULL) //if the list is empty
        {
            head = temp; //then temp points to both the front and back as there is only one mode in the list at this time
            tail = temp;
        }
        else
        {
            tail->next = temp; //if there are more than one nodes in the list then the last value in the list now points to temp, the new node
            tail = tail->next; //sets temp to be the last value in the list
        }

    }


    /*find distance method
     this method returns an int that represents the distance to the target
     target is the value to find in the list, start represents the node to start at
     the function will iterate through the list until the target value is found. Once found the count will be returned
    */

    int findDistance(int target,int start)
    {
        node* temp = new node;                                         //temp pointer and startnode
        node* startNode = new node;
        temp = head;                                                   //have both pointers point to head of list
        startNode = head;
        int count = 0;
        int i = 0;

        while (i != start)                                             //iterate through the list until the starting node is found
        {
            startNode = startNode->next;
            i++;
        }
        
        temp = startNode;                                              //set temp equal to the start node
         
        while (temp->data != target && temp->next != NULL)    //while the data of N node is not equal to the target and the next node is not null
        {
            temp = temp->next;                                //set temp equal to the next node in the list and increment the count
            count++;
        }

        if (temp->data == target)                             //if the target value was found return the count
        { 
            return count;
        }
        else                                                  //if target value does not reoccur in the list set to abritrary amount (50 in this case)
        {
            count = 50;
            return count;
        }
    }
};




//                     OPT Algorithim
/*
    This algorithim returns an int - this represents the number of page faults calculated
    It is passed the number of frames allowed, an int array representing the reference string, an int count representing the length of the reference string
    and a linked list containing the values of the reference string. 
*/
    int OPTalgo(int frames, int reference[], int count, linkedList ll)
    {
        int pageFaults = 0;
        int i = 0;
        int test[10] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };
        int remove = 0;
        int distance = 0;
        int stepCount = 0;
        bool check = false;

        //algorithim start 
        while (i < count)
        {
            if (i == 0)                                                        //if i is 0 then there is no data in the frames so we can add the first value and increment pages counts and i
            {
                pageFaults++;
                test[i] = reference[i];
                i++;
            }
            else if (i >= frames)                                              //if i is greater than the number of frames this means the frames are full and we now need to determine what value to remove
            {
                int j = 0;
                distance = 0;

                while (j < frames)                                           //where the magic happens. this code is gross
                {
                    if (reference[i] == test[j])                             //now we are looping through test, an int array, which holds the values that would be in the frames
                    {                                                        //if the current value of the reference string equals any value in the test array this means it does not need to be added
                        i++;                                                 //check is used to determine if a value should be added or not
                        j++;
                        check = false;                                       
                        break;
                    }
                    else                                                     //stepCount holds the distance from the current node to the next iteration of the target value 
                    {                       
                        stepCount = ll.findDistance(test[j], i);                 //initially it is set to distance, then if the next value is further away distance is updated with the step count
                        if (stepCount >= distance)                               //remove is used to the hold the index of the value to be removed
                        {
                            distance = stepCount;                                        
                            remove = j;
                        }
                        j++;
                        check = true;                                            
                    }
                    
                    
                }
                if (check)                                                  // a value needs to be added to the frames
                {                                                           // the value in frames that had the greatest distance now equals the current value in the reference string
                    test[remove] = reference[i];                                 //increment i to move to the next value and increment number of pages faults
                    i++;
                    pageFaults++;
                }


            }
            else                                                            //if the frame limit has NOT been reached
            {
                int j = 0;
                check = false;

                while (j < frames)                                          //while incrementer j is less than number of frames allowed
                {
                    if (reference[i] != test[j] || test[j] == -1)           //if the current value in the reference string does not equal any values in the test array (representing the values in frames) or the value is -1 
                    {                                                       //if the value is -1 and the current reference string value does not match any values in the test array we can add, increment page faults and move to
                        if (test[j] == -1)                                  //the next value in the reference string
                        {
                            test[j] = reference[i];
                            check = false;
                            i++;
                            pageFaults++;
                            break;
                        }
                        check = true;                                        //check again represents whether a value should be added or not
                        j++;
                  
                    }
                    else if (reference[i] == test[j])                        //if the reference string value equals a value already in a frame then we ignore it     
                    {
                        check = false;
                        i++;
                        break;
                    }


                }

                if (check)                                                    //if it was determined a value needs to be added to the frame
                {                                                             //add value to the frame (test array) and increment page faults
                    test[i] = reference[i];
                    i++;
                    pageFaults++;
                }

            }
        }


        for (i = 0; i < frames; i++)                                          //simple for loop used to print the final values in the test array/frames 
        {
            cout << test[i] << " ";
        }
        cout << endl;


        return pageFaults;                                                    //return total number of page faults
    }



    int main()                                                                                       //program start
    {                                                                                                //runs twice to hit both OPT and FIFO algorithims
        int runs = 0;
        while (runs < 2)
        {
            ifstream myfile;                                                                         
            

            if (runs == 1)
            {
                myfile.open("FIFO.txt");
            }
            else
                myfile.open("OPT.txt");


            string mystring;

            char algo = 'a';
            int frames = 0;
            int reference[20] = {};
            linkedList ll;

            if (myfile.is_open()) //ensures text file is open
            {
                myfile >> mystring; //puts text from myfile into variable called mystring

                /*
                //for loop used to remove commas from file
                */
                for (int i = 0; i < mystring.size(); i++)
                {
                    if (mystring[i] == ',')
                    {
                        mystring.erase(i, 1);
                    }
                }


                /*
                This For loop is used to get the reference string from the mystring variable
                If the algo variable equals O then we will also add each value to the linked list
                */
                int j = 0;
                for (int i = 0; i < mystring.size(); i++)
                {
                    if (i == 0)
                        algo = mystring[i];
                    else if (i == 1)
                        frames = mystring[i] - '0';                 //when reading the values in they are stored as Chars, using - '0' we get the intended int value instead of the ascii value
                    else
                    {
                        reference[j] = mystring[i] - '0';
                        if (algo == 'O')
                            ll.insertNewNode(reference[j]);
                        j++;
                    }
                }

                //runs both algos and prints the number of page faults
                if (algo == 'O')
                {
                    cout << "Page Faults on OPT algorithm: " << OPTalgo(frames, reference, j, ll);
                    runs++;
                }
                else if (algo == 'F')
                {
                    cout << "Page Faults on FIFO algorithm: " << FIFOalg(frames, reference, j);
                    runs++;
                }


            }
            else //if file is not open, print error
                cout << "file not open";
        }
    }

