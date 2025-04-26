#include "include/repositories/MovieRepositories.h"

void MovieRepositories::showMovieList(){
    MYSQL* conn = DatabaseManager::getInstance()->getConnection();
    MYSQL_RES* res;
    MYSQL_ROW row;
    
    int qstate = mysql_query(conn, "SELECT * FROM movie_tb");
    
    if (!qstate) {
        res = mysql_store_result(conn);
        cout << "-------------------------------------------------------------------------------------------------------------\n";
        cout << "| " << left << setw(5) << "ID" 
             << "| " << left << setw(15) << "Name" 
             << "| " << left << setw(10) << "Genre"
             << "| " << left << setw(10) << "Format"
             << "| " << left << setw(12) << "Show Date"
             << "| " << left << setw(10) << "Show Time"
             << "| " << left << setw(8) << "Price"
             << "|\n";
        cout << "-------------------------------------------------------------------------------------------------------------\n";
        while ((row = mysql_fetch_row(res))) {
            cout << "| " << left << setw(5) << row[0] 
                 << "| " << left << setw(15) << row[1] 
                 << "| " << left << setw(10) << row[2] 
                 << "| " << left << setw(10) << row[3]
                 << "| " << left << setw(12) << row[4]
                 << "| " << left << setw(10) << row[5]
                 << "| " << left << setw(8) << row[6] 
                 << "|\n";
        }
        cout << ("-------------------------------------------------------------------------------------------------------------\n");
    } else {
        cout << "Query Execution Problem! " << mysql_errno(conn) << endl;
    }
}
void MovieRepositories::editMovie() {
    MYSQL* conn = DatabaseManager::getInstance()->getConnection();
    MYSQL_RES* res;
    MYSQL_ROW row;

    int qstate = mysql_query(conn, "SELECT m_id, m_name FROM movie_tb");
    
    if (!qstate) {
        res = mysql_store_result(conn);
        cout << "--------------------------------\n";
        cout << "| " << left << setw(5) << "ID" 
             << "| " << left << setw(20) << "Name"
             << "|\n";
        cout << "--------------------------------\n";
        while ((row = mysql_fetch_row(res))) {
            cout << "| " << left << setw(5) << row[0] 
                 << "| " << left << setw(20) << row[1] 
                 << "|\n";
        }
        cout << "--------------------------------\n";
    } else {
        cout << "Query Execution Problem! " << mysql_errno(conn) << endl;
        return;
    }

    int id;
    cout << "Enter Movie ID to edit: ";
    std::cin >> id;
    std::cin.ignore(); // clear newline

    std::stringstream ss;
    ss << id;
    string str_id = ss.str();

    // Check if movie exists
    string check_query = "SELECT * FROM movie_tb WHERE m_id = '" + str_id + "'";
    qstate = mysql_query(conn, check_query.c_str());
    
    if (!qstate) {
        res = mysql_store_result(conn);
        if (mysql_num_rows(res) == 0) {
            cout << "Movie not found!\n";
            return;
        }

        row = mysql_fetch_row(res);
        string current_name = row[1];
        string current_genre = row[2];
        string current_format = row[3];
        string current_showdate = row[4];
        string current_showtime = row[5];
        string current_price = row[6];
        string current_seat = row[7];
        string name, genre, format, showDate, showTime, price, seat;
        string defaultString = "xN";

        cout << "Enter new name (" << defaultString << " to keep [" << current_name << "]): ";
        std::getline(std::cin, name);
        if (name == defaultString) name = current_name;

        cout << "Enter new genre (" << defaultString << " to keep [" << current_genre << "]): ";
        std::getline(std::cin, genre);
        if (genre == defaultString) genre = current_genre;

        cout << "Enter new format (" << defaultString << " to keep [" << current_format << "]): ";
        std::getline(std::cin, format);
        if (format == defaultString) format = current_format;

        cout << "Enter new show date (" << defaultString << " to keep [" << current_showdate << "]): ";
        std::getline(std::cin, showDate);
        if (showDate == defaultString) showDate = current_showdate;

        cout << "Enter new show time (" << defaultString << " to keep [" << current_showtime << "]): ";
        std::getline(std::cin, showTime);
        if (showTime == defaultString) showTime = current_showtime;

        cout << "Enter new ticket price (" << defaultString << " to keep [" << current_price << "]): ";
        std::getline(std::cin, price);
        if (price == defaultString) price = current_price;

        cout << "Enter new seat (" << defaultString << " to keep [" << current_seat << "]): ";
        std::getline(std::cin, seat);
        if (seat == defaultString) seat = current_seat;

        string update_query = "UPDATE movie_tb SET "
                              "m_name = '" + name + "', "
                              "m_genre = '" + genre + "', "
                              "m_format = '" + format + "', "
                              "m_showdate = '" + showDate + "', "
                              "m_showtime = '" + showTime + "', "
                              "m_ticketprice = '" + price + "' "
                              "WHERE m_id = '" + str_id + "'";

        qstate = mysql_query(conn, update_query.c_str());

        if (!qstate) {
            cout << "Movie updated successfully!\n";
        } else {
            cout << "Failed to update movie! " << mysql_errno(conn) << endl;
        }
    } else {
        cout << "Query Execution Problem! " << mysql_errno(conn) << endl;
    }
}

void MovieRepositories::deleteMovie() {
    MYSQL* conn = DatabaseManager::getInstance()->getConnection();
    MYSQL_RES* res;
    MYSQL_ROW row;

    int qstate = mysql_query(conn, "SELECT m_id, m_name FROM movie_tb");
    
    if (!qstate) {
        res = mysql_store_result(conn);
        cout << "--------------------------------\n";
        cout << "| " << left << setw(5) << "ID" 
             << "| " << left << setw(20) << "Name"
             << "|\n";
        cout << "--------------------------------\n";
        while ((row = mysql_fetch_row(res))) {
            cout << "| " << left << setw(5) << row[0] 
                 << "| " << left << setw(20) << row[1] 
                 << "|\n";
        }
        cout << "--------------------------------\n";
    } else {
        cout << "Query Execution Problem! " << mysql_errno(conn) << endl;
        return;
    }

    int id;
    cout << "Enter Movie ID to delete: ";
    std::cin >> id;

    std::stringstream ss;
    ss << id;
    string strId = ss.str();

    string delete_query = "DELETE FROM movie_tb WHERE m_id = '" + strId + "'";
    qstate = mysql_query(conn, delete_query.c_str());

    if (!qstate) {
        cout << "Movie deleted successfully!\n";
    } else {
        cout << "Failed to delete movie! " << mysql_errno(conn) << endl;
    }
}