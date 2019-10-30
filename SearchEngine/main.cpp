#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<windows.h>
#include<mysql.h>
#include<sstream>

using namespace std;

bool dbconn();
void addPost();
void editrec();
void delPost();
void view();
void viewAll();
void viewWithID();
void viewWithTitle();
void viewWithCategory();

string dummy;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;

int main()
{
    int runforever = 1;
    int ans;
    while(runforever){
    system("cls");
        cout << endl << endl << "---------------" << endl << endl << "1. Add new post" << endl << "2. Edit post" << endl << "3. Delete Posts" << endl << "4. View Posts" << endl << "5. End" << endl << endl << "---------------" << endl;

        cout << endl << "Your Answer : ";

        cin >> ans;

        switch(ans){
        case 1:
            addPost();
            break;
        case 2:
            editrec();
            break;
        case 3:
            delPost();
            break;
        case 4:
            view();
            break;
        case 5:
            runforever=1;
            exit(0);
            break;
        default:
            cout<<endl<<"Wrong choice entered!"<<endl;
            system("pause");
            break;
        }
    }

    return 0;
}

void addPost(){
    system("cls");
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "192.168.0.110", "admin", "admin", "search_engine", 0, NULL, 0);
    if(conn){
        int qstate = 0;
        //char content[100], cAspect[30];
        string title, content, contentSpace, cAspect;

        cout << "Enter title of the post : ";
        cin.get();
        getline(cin, title);

        cout << "Enter content : ";
        getline(cin, content);

        cout << "Enter topic's area : ";
        getline(cin, cAspect);

        stringstream ss;

        ss << "INSERT INTO se__dbms(title, content, cAspect) VALUES('" << title << "','" << content << "','" << cAspect <<"')";

        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0){
            cout << "Record Inserted..." << endl;
            cout << "Press B to go back";
            cin >> dummy;
        }else{
            cout << "Insert Error" << mysql_error(conn) << endl;
            cout << "Press B to go back";
            cin >> dummy;
        }
    }else{
        cout << "Connection Error" << endl;
        cout << "Press B to go back";
        cin >> dummy;
    }

    system("pause");
    system("cls");

}

void editrec(){
    system("cls");
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "192.168.0.110", "admin", "admin", "search_engine", 0, NULL, 0);
    if(conn){
        int qstate = 0;
        string name;
        int quantity;
        cout << "Enter Name : ";
        cin >> name;
        cout << "Enter Quantity : ";
        cin >> quantity;

        stringstream ss;
        ss << "UPDATE se__dbms SET quantity = quantity + " << quantity << " WHERE name = '" << name << "'";

        string query = ss.str();

        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0){
            cout << "Record Updated..." << endl;
            cout << "Press B to go back";
            cin >> dummy;
        }else{
            cout << "Insert Error" << mysql_error(conn) << endl;
            cout << "Press B to go back";
            cin >> dummy;
        }
    }else{
        cout << "Connection Error" << endl;
        cout << "Press B to go back";
        cin >> dummy;
    }

    system("pause");
    system("cls");

}

void delPost(){
    MYSQL* conn2;
    system("cls");
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "192.168.0.110", "admin", "admin", "search_engine", 0, NULL, 0);

    conn2 = mysql_init(0);
    conn2 = mysql_real_connect(conn, "192.168.0.110", "admin", "admin", "search_engine", 0, NULL, 0);

    if(conn){

        int id;
        cout << "Enter id : ";
        cin >> id;

        int qstate1 = 0;

        stringstream ss1;
        //ss1 << "UPDATE se__dbms SET quantity = quantity - " << quantity << " WHERE name = '" << name << "'";
        ss1 << "DELETE from se__dbms WHERE id = '" << id <<"'";

        string query1 = ss1.str();

        const char* q1 = query1.c_str();
        qstate1 = mysql_query(conn2, q1);
        if(qstate1 == 0){
            cout << "Record Deleted..." << endl;
        }else{
            cout << "Insert Error" << mysql_error(conn) << endl;
        }

    }

    cout << "Press B to go back";
    cin >> dummy;

    system("pause");
    system("cls");
}

void view(){

int runforever = 1;
int ans;
system("cls");
while(runforever == 1){

        cout << endl << endl << "---------------" << endl << endl << "1. View all post" << endl << "2. View posts by title" << endl << "3. View posts by Category" << endl << "4. Return to main menu" << endl << endl << "---------------" << endl;
        cout << endl << "Your Answer : ";
        cin >> ans;

        switch(ans){
        case 1:
            viewAll();
            break;
        case 2:
            viewWithTitle();
            break;
        case 3:
            viewWithCategory();
            break;
        case 4:
            main();
            break;
        default:
            cout<< "Wrong choice entered!";
        }
    }
}

void viewAll(){
    system("cls");
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "192.168.0.110", "admin", "admin", "search_engine", 0, NULL, 0);
    if(conn){
        int qstate = mysql_query(conn, "SELECT id, title, content, cAspect, date, time FROM se__dbms");

        if(!qstate){
            res = mysql_store_result(conn);
            //cout<< endl << "----------------------------------------------------------------" << endl << endl;
            //cout << "ID" <<"\t | \t" << "NAME" <<"\t | \t" << "LOCATION" <<"\t | \t" << "QUANTITY" << endl << endl;
            //cout<< "----------------------------------------------------------------" << endl << endl;

            while(row = mysql_fetch_row(res))
                cout << "\n\nPost Code :\t" << row[0] <<"\nTITLE :\t" << row[1] <<"\nCONTENT :\t" << row[2] <<"\nTOPIC SUBJECT :\t" << row[3] << "\nCREATED ON :\t" << row[4] <<" " << row[5] << endl << endl;
        }
    }

    cout << "Press B to go back";
    cin >> dummy;

    system("pause");
    system("cls");
}


void viewWithID(){
    system("cls");
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "192.168.0.110", "admin", "admin", "search_engine", 0, NULL, 0);
    int id;
    cout<< "enter id";
    cin>>id;
    stringstream ss;
    ss<<"SELECT id, title, content, cAspect, date, time FROM se__dbms where id = '" << id <<"'";
    string query = ss.str();
    const char* q = query.c_str();
    if(conn){
        int qstate = mysql_query(conn, q);

        if(!qstate){
            res = mysql_store_result(conn);
            while(row = mysql_fetch_row(res)){
                    cout << "\n\nPost Code :\t" << row[0] <<"\nTITLE :\t" << row[1] <<"\nCONTENT :\t" << row[2] <<"\nTOPIC SUBJECT :\t" << row[3] << "\nCREATED ON :\t" << row[4] <<" " << row[5] << endl << endl;
            }
        }
    }
    system("pause");
    system("cls");
}

//void viewWithID(){
//    system("cls");
//    string dummy;
//    MYSQL* conn;
//    MYSQL_ROW row;
//    MYSQL_RES* res;
//    conn = mysql_init(0);
//    conn = mysql_real_connect(conn, "192.168.0.110", "admin", "admin", "search_engine", 0, NULL, 0);
//    int id;
//    cout<< "enter id: ";
//    cin>>id;
//    stringstream ss;
//    ss<<"SELECT id, title, content, cAspect, date, time FROM se__dbms where id = '" << id <<"'";
//    string query = ss.str();
//    const char* q = query.c_str();
//    if(conn){
//        int qstate = mysql_query(conn, q);
//
//        if(!qstate){
//            res = mysql_store_result(conn);
//            while(row = mysql_fetch_row(res))
//                cout << "\n\nPost Code :\t" << row[0] <<"\nTITLE :\t" << row[1] <<"\nCONTENT :\t" << row[2] <<"\nTOPIC SUBJECT :\t" << row[3] << "\nCREATED ON :\t" << row[4] <<" " << row[5] << endl << endl;
//        }
//    }
//    system("pause");
//    system("cls");
//}

void viewWithTitle(){
    system("cls");
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "192.168.0.110", "admin", "admin", "search_engine", 0, NULL, 0);
    string title;
    cout<< "enter title: ";
    cin.get();
    getline(cin, title);
    stringstream ss;
    ss<<"SELECT id, title, content, cAspect, date, time FROM se__dbms where title = '" << title <<"'";
    string query = ss.str();
    const char* q = query.c_str();
    if(conn){
        int qstate = mysql_query(conn, q);

        if(!qstate){
            res = mysql_store_result(conn);
            while(row = mysql_fetch_row(res))
                cout << "\n\nPost Code :\t" << row[0] <<"\nTITLE :\t" << row[1] <<"\nCONTENT :\t" << row[2] <<"\nTOPIC SUBJECT :\t" << row[3] << "\nCREATED ON :\t" << row[4] <<" " << row[5] << endl << endl;
        }
    }
    system("pause");
    system("cls");
}


void viewWithCategory(){
    system("cls");
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "192.168.0.110", "admin", "admin", "search_engine", 0, NULL, 0);
    string cAspect;
    cout<< "enter topic category: ";
    cin.get();
    getline(cin, cAspect);
    stringstream ss;
    ss<<"SELECT id, title, content, cAspect, date, time FROM se__dbms where cAspect = '" << cAspect <<"'";
    string query = ss.str();
    const char* q = query.c_str();
    if(conn){
        int qstate = mysql_query(conn, q);

        if(!qstate){
            res = mysql_store_result(conn);
            while(row = mysql_fetch_row(res))
                cout << "\n\nPost Code :\t" << row[0] <<"\nTITLE :\t" << row[1] <<"\nCONTENT :\t" << row[2] <<"\nTOPIC SUBJECT :\t" << row[3] << "\nCREATED ON :\t" << row[4] <<" " << row[5] << endl << endl;
        }
    }
    system("pause");
    system("cls");
}
