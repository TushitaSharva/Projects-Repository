#include<iostream>
#include<fstream>
#include<cctype>
#include<string>

using namespace std;


void displaySelectActions(int);

class CourseDetails;
class FacultyDetails;
class StudentDetails;
class Admin;
class Faculty;
class Student;

class CourseDetails
{
    public:
        string courseID;
        string courseName;
};

class FacultyDetails
{
    public:
        string facultyID;
        string facultyName;
        string facultyEmail;
        
};

class StudentDetails
{
    public:
        string studentID;
        string studentName;
        string studentEmail;
};

class Grades
{
    public: 
        string grade;
};

class Admin : public CourseDetails, public FacultyDetails, public StudentDetails, public Grades
{
    public:
        void setCourse();
        void setStudent();
        void setFaculty();
    /*
        STILL YOU HAVE TO WORRY ABOUT DELETING DATA... :)
    */
};

void Admin :: setFaculty()
{

    int num;

    cout<<"How many FACULTY MEMBERS do you want to set now?\t";
    cin>>num;
    ofstream facultyList("FacultyList.csv");
    facultyList<<"faculty ID"<<","<<"facultyName"<<","<<"faculty Email"<<endl;

    for (int i = 0; i < num; i++)
    {
        cout<<"Enter the FacultyID:\t";
        cin>>facultyID;
        cout<<"Enter the name of the Faculty:\t";
        cin.ignore();
        getline(cin, facultyName);
        cout<<"Enter the email ID of the Faculty:\t";
        cin>>facultyEmail;

        //FILE WRITING FOR THE FILE FACULTYLIST.CSV
        facultyList<<facultyID<<","<<facultyName<<","<<facultyEmail<<endl;
    }
}

void Admin :: setCourse()
{
    int num;

    cout<<"How many courses do you want to set now?\t";
    cin>>num;

    ofstream CoursesList("CoursesList.csv");
    CoursesList<<"course ID"<<","<<"course Name"<<","<<"faculty Name"<<","<<"faculty Email"<<endl;
    ofstream CourseStudentList("Course_Student.csv");
    
    for (int i = 0; i < num; i++)
    {
        cout<<"Entry number"<<i+1<<":\n";  
        cout<<"Enter the CourseID:\t";
        cin>>courseID;

        cout<<"Enter the name of the course:   \t";
        cin.ignore();
        getline(std::cin, courseName);

        cout<<"Enter the name of the Faculty dealing:\t";
        getline(std::cin, facultyName);
        
        cout<<"Enter the email ID of the Faculty:\t";
        cin>>facultyEmail;
        cout<<"\n";
        //FILE WRITING FOR THE FILE COURSELIST.CSV
        
        CoursesList<<courseID<<","<<courseName<<","<<facultyName<<","<<facultyEmail<<endl;
        CourseStudentList<<courseID<<endl<<"Grade"<<endl;
    }    
}

void Admin :: setStudent()
{
    int num;

    cout<<"How many students do you want to set now?\t";
    cin>>num;
    ofstream StudentListOut("ListofStudentsSheet.csv");
    StudentListOut<<"Student ID"<<","<<"Student Name"<<","<<"Student Email"<<","<<"Courses Registered"<<","<<"Course Grade"<<endl;
    
    for (int i = 0; i < num; i++)
    {
        cout<<"Entry Number"<<i+1<<":\n";
        cout<<"Enter the StudentID:\t";
        cin>>studentID;
        cout<<"Enter the name of the Student:\t";
        cin.ignore();
        getline(cin, studentName);
        cout<<"Enter the email ID of the Student:\t";
        cin>>studentEmail;

        //FILE WRITING FOR THE FILE LISTOFSTUDENTSHEET.CSV

        StudentListOut<<studentID<<","<<studentName<<","<<studentEmail<<endl;
        break;
    }  
}

class Faculty : public CourseDetails, public FacultyDetails, public StudentDetails, public Grades
{
    public:
        void getEnrolledList();
        void uploadGrades();   
};

void Faculty :: getEnrolledList()
{
    string line;
    cout<<"Enter the course ID\t";
    cin>>courseID;
    ifstream courseStudentlistIn("Course_Student.csv");
    getline(courseStudentlistIn, line);


    if(line.find(courseID) != std::string::npos)
    {
        getline(courseStudentlistIn, line);
    }    
}

void Faculty :: uploadGrades()
{
    string line;
    string name;

    cout<<"Enter the course ID for grading\n";
    cin>>courseID;
    // cout<<"Enter the grades of the student in the order of their roll number.";

    ifstream courseStudentlistIn("Course_Student.csv");
    ofstream courseStudentlistOut("Course_Student.csv");
    getline(courseStudentlistIn, line);

    if(line.find(courseID) != std::string::npos)
    {
        while(line.find("\n") == std::string::npos)
        {
            cout<<"Enter the grade for the student ";
            cout<<line;    
            cin>>grade;
        }
    }
}

class Student : public CourseDetails, public FacultyDetails, public StudentDetails, public Grades
{
    public:
        void resisterCourse();
        void deregisterCourse(); //Still sould be implemented
        void veiwGrades(); //Still Should be implemented
};

void Student :: resisterCourse()
{
    int num;

    cout<<"The list of courses available are:\n";
    ifstream displayingCourses;
    string course;
    string line;
    displayingCourses.open("CoursesList.csv");
    
    while (displayingCourses.eof()==0) 
    {
        // using getline to fill the whole line in st
        getline(displayingCourses,course);
        cout<<course<<endl;
    }

    cout<<"How many courses do you want to register??\t";
    cin>>num;

    ofstream courseStudentlistOut("Course_Student.csv");
    ifstream courseStudentlistIn("Course_Student.csv");
    getline(courseStudentlistIn, line);

    for(int i = 0; i < num; i++)
    {
        cout<<"Please enter your ID\n";//***************************************
        cout<<"Enter the course ID of the course you want to register\n";
        cin>>courseID;

        if (line.find(courseID) != std::string::npos)
        courseStudentlistOut<<","<<studentID<<endl;
    }
}

void displaySelectActions(int userType)
{
    int actionType;

    if (userType == 1)
    {
        Admin admin;

        cout<<"You can perform the following actions:\n";
        cout<<"(1) Add Courses\n";
        cout<<"(2) Add students to IITH\n";
        cout<<"(3) Add Faculty to IITH\n";

    /*  
        TO BE IMPLEMENTED
        cout<<"(4) Delete courses\n";
        cout<<"(5) Remove students from IITH\n";
        cout<<"(6) Add students to courses\n";@
        cout<<"(7) Delete students from the course\n";
    */  
        cout<<"Please enter the number to the corresponding action\n";
        cin>>actionType;

        if(actionType == 1)
        {
            admin.setCourse();
        }
        else if(actionType == 2)
        {
            admin.setStudent();
        }

        else if(actionType == 3)
        {
            admin.setFaculty();
        }

        // else if(actionType == 4)
        // {

        // }

        // else if(actionType == 5)
        // {

        // }
        // else if(actionType == 6)
        // {

        // }

        else
        {
            cout<<"Error... Please enter a valid number.\n";
            int displaySelectActions(1);
        }
    }

    else if (userType == 2)
    {
        Faculty faculty;

        cout<<"You can perform the following actions:\n";
        cout<<"(1) Get the list of students who registered for your course\n";
        cout<<"(2) Submit grades of the students\n";

        cout<<"Please enter the number to the corresponding action\n";
        cin>>actionType;

        if(actionType == 1)
        {
            faculty.getEnrolledList();
        }

        else if(actionType == 2)
        {
            faculty.uploadGrades();
        }

        else 
        {
            cout<<"Error... Please Enter a valid number.\n";
            int displaySelectActions(2);
        }
    }
    
    else if (userType == 3)
    {
        Student student;

        cout<<"You can perform the following actions:\n";
        cout<<"(1) Register for a course\n";
        cout<<"(2) Deregister for a course\n";
        cout<<"(3) View grades available\n";

        cout<<"Please enter the number to the corresponding action\n";
        cin>>actionType;

        if(actionType == 1)
        {
            student.resisterCourse();
        }

        else if(actionType == 2)
        {
            cout<<"Not yet implemented, sorry\n";
        }

        else if(actionType == 3)
        {
            cout<<"Not yet implemented, sorry\n";
        }

        else 
        {
            cout<<"Error... Please Enter a valid number.\n";
            int displaySelectActions(3);
        }
    }        
}

int main()
{
    int userType;

    cout<<"Hello!\n";
    cout<<"Please enter (1) if you are an Admin\n";
    cout<<"Please enter (2) if you are a Faculty member\n";
    cout<<"Please enter (3) if you are a Student\n";
    cin>>userType;

    displaySelectActions(userType);

    cout<<"Thank you\n";
    return 0;
}
