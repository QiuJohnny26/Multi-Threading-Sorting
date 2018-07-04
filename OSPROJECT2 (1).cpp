///////////////////////////////////////////////////////////////////////////////////
//On my honor,
//The following program is a result of personal effort. I have not discussed with
//anyone other than my instructor or any appropriate person in charge of the class.
//I have not used, or slightly modified  code or portion of code from another
//student, or an unauthorized source.
//If any C++ language code or documentation used in my program was obtained from
//another source, such as a textbook or course notes, that has been clearly noted
//with a proper citation in the comments of my program.
//I have not designed this program in such a way as to defeat or interfere with the
//normal operation of the eniac system or cslab machines at Hunter College .
// ****<Johnny Qiu>****
/////////////////////////////////////////////////////////////////////////////////////
//
//Author:***** <Johnny Qiu> ******
//Course: {340}
//Instructor: <Stanley Wine>
//Assignment: <Unix Shell and History>
//Due Date: 5/2/17
#include<iostream>
#include<thread>
#include<vector>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std;

void mergeThread(vector<int>left,vector<int>right); // takes both vector that was sorted from separate threads to merge into one sorted vector from another thread
void leftThread(vector<int>numList); // takes the left side of  the 10 number input and gets quicksorted 
void rightThread(vector<int>numList);// takes the right side of the 10 number input and gets quicksorted
 void quick_sortfirstPiv(vector<int>numList,int left,int right); //uses the first element to use as a pivot for the quick sort and then runs recursively
int main()
{
   
      vector<int> inputs;
      vector<int> left;
      vector<int> right;
      int arraySize=10;
      for(int j=0;j<arraySize;j++){
          cout<< "Please Enter 10 numbers to be sorted by threads"<<endl;
          cout<< j+1<<". ";
          int temp;
          cin>>temp;
          inputs.push_back(temp);
           if(j<=4){
          left.push_back(temp);
           }
           else{
          right.push_back(temp);
           }
          cout<<endl;
}

      thread firstThread(leftThread,left);
      thread::id id1=firstThread.get_id();
      cout<<"Thread Number " << id1<<" will now sort the following array" <<endl;
   //   firstThread.join();
      thread secondThread(rightThread,right);
      thread::id id2=secondThread.get_id();
      cout<<"Thread Number " <<id2<<" will now sort the following array"<<endl;
         firstThread.join();//joins the first thread so it can run
        secondThread.join();//joins so the second thread can run
     thread thirdThread(mergeThread,left,right);
     thread::id id3=thirdThread.get_id();
     cout<<"Thread Number " << id3<<"will now sort the final array"<<endl;
        thirdThread.join();  // joins so the third thread can run 
          
         

      
}
    void quick_sortfirstPiv(vector<int>numList,int left,int right){
          int size=numList.size();
          int i=left,j=right;// the left side of the pivot// the right side of the pivot//for swapping
          int pivot=numList[left];// pivot is first element now
              while(i<=j)
                    {     // it loops through the whole array
                  while (numList[i]<pivot) {  // if the element is less than pivot on the left keep incrementing
                  i++;
                  }
                  while(numList[j]>pivot){ // if the element is more than pivot on the right keep decrementing
                  j--;
                  }
                  if(i<=j){         //if it did not meet the above conditional loops it means that the elements are not in its place and should be swapped
                     int temp=numList[i];
                     numList[i]=numList[j];
                     numList[j]=temp;
                     i++; 
                     j--;
                  }
              }

  
              if (left<j) // sort the left side
               {
                quick_sortfirstPiv(numList,left,j); 
               }
                if (i<right)   //sort the right side;
               {
               quick_sortfirstPiv(numList,i,right);
                }
       if(left==1  && right==2 &&size==5){    //outputs the left and right threads with the sorted array     left would be 0 1 *  and right would be     *234 when it backtracks when it backtracks from the recursion of quicksort
          for(int k=0;k<5;k++){
             cout<<numList[k]<<" ";
          }
          cout<<endl;
          }
    
      
      if(left==4 &&right==5 &&size==10){       //outputs the sorted numbers that the left and right threads merged into a single thread  left would be 0 1 2 3 4* and right would be *5 6 7 8 9 when it backtracks from the recursion of quicksort
           for(int l=0;l<10;l++){
               cout <<numList[l]<<" ";
           }
           cout<<endl;
    }
     
    }
    void leftThread(vector<int>numList){   //left thread takes the left side of the vector which was pushed into the left vector in the main function
        for(int i=0;i<5;i++){
          cout<< numList[i]<<" ";
    }
    cout<<endl;
 
      quick_sortfirstPiv(numList,0,4);
      
      cout << "Thread 1 is sorted " <<endl;
    }
     void rightThread(vector<int>numList){ //right thread takes the right side of the victor which was pushed into the right vector in the main function
        for(int i=0;i<5;i++){

        cout<<numList[i]<<" ";
        }
        cout<<endl;
      quick_sortfirstPiv(numList,0,4);
        cout << "Thread 2 is sorted " <<endl;
     }
        
        void mergeThread(vector<int>left,vector<int>right){ // takes the sorted left vector and right vector to sort alltogether on another thread 
            vector<int> allInputs;
            for(int i=0;i<5;i++){
                allInputs.push_back(left[i]);
           }
           for(int j=0;j<5;j++){
               allInputs.push_back(right[j]);
           }
           quick_sortfirstPiv(allInputs,0,9);
        
        }