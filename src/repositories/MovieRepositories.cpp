#include "../../include/repositories/MovieRepositories.h"

void MovieRepositories::showMovieList() {
    std::string query = "SELECT * FROM movie_tb";
    QueryResult result = DatabaseManager::getInstance()->executeQuery(query);

    if (!result.success) {
        std::cerr << "Query Execution Problem! Error: " << result.error_message << std::endl;
        return;
    }

    MYSQL_RES* res = result.result.get();
    MYSQL_ROW row;

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
        cout << "| " << left << setw(5) << (row[0] ? row[0] : "NULL")
             << "| " << left << setw(15) << (row[1] ? row[1] : "NULL")
             << "| " << left << setw(10) << (row[2] ? row[2] : "NULL")
             << "| " << left << setw(10) << (row[3] ? row[3] : "NULL")
             << "| " << left << setw(12) << (row[4] ? row[4] : "NULL")
             << "| " << left << setw(10) << (row[5] ? row[5] : "NULL")
             << "| " << left << setw(8) << (row[6] ? row[6] : "NULL")
             << "|\n";
    }
    cout << "-------------------------------------------------------------------------------------------------------------\n";
}
void MovieRepositories::editMovie() {
    std::string query = "SELECT m_id, m_name FROM movie_tb";
    QueryResult result = DatabaseManager::getInstance()->executeQuery(query);

    if (!result.success) {
        std::cerr << "Query Execution Problem! Error: " << result.error_message << std::endl;
        return;
    }

    MYSQL_RES* res = result.result.get();
    MYSQL_ROW row;

    cout << "--------------------------------\n";
    cout << "| " << left << setw(5) << "ID"
         << "| " << left << setw(20) << "Name"
         << "|\n";
    cout << "--------------------------------\n";
    while ((row = mysql_fetch_row(res))) {
        cout << "| " << left << setw(5) << (row[0] ? row[0] : "NULL")
             << "| " << left << setw(20) << (row[1] ? row[1] : "NULL")
             << "|\n";
    }
    cout << "--------------------------------\n";

    int id;
    cout << "Enter Movie ID to edit: ";
    std::cin >> id;
    std::cin.ignore();

    std::string str_id = std::to_string(id);

    // Check if movie exists
    std::string check_query = "SELECT * FROM movie_tb WHERE m_id = '" + str_id + "'";
    QueryResult check_result = DatabaseManager::getInstance()->executeQuery(check_query);

    if (!check_result.success) {
        std::cerr << "Query Execution Problem! Error: " << check_result.error_message << std::endl;
        return;
    }

    MYSQL_RES* check_res = check_result.result.get();
    if (mysql_num_rows(check_res) == 0) {
        cout << "Movie not found!\n";
        return;
    }

    row = mysql_fetch_row(check_res);
    Movie movie(
        row[0], row[1], row[2], row[3],
        row[4], row[5], row[6], row[7]
    );

    string default_string = "xN";
    string input;

    cout << "Enter new name (" << default_string << " to keep [" << movie.getName() << "]): ";
    std::getline(std::cin, input);
    if (input != default_string) movie.setName(input);

    cout << "Enter new genre (" << default_string << " to keep [" << movie.getGenre() << "]): ";
    std::getline(std::cin, input);
    if (input != default_string) movie.setGenre(input);

    cout << "Enter new format (" << default_string << " to keep [" << movie.getFormat() << "]): ";
    std::getline(std::cin, input);
    if (input != default_string) movie.setFormat(input);

    cout << "Enter new show date (" << default_string << " to keep [" << movie.getShowDate() << "]): ";
    std::getline(std::cin, input);
    if (input != default_string) movie.setShowDate(input);

    cout << "Enter new show time (" << default_string << " to keep [" << movie.getShowTime() << "]): ";
    std::getline(std::cin, input);
    if (input != default_string) movie.setShowTime(input);

    cout << "Enter new ticket price (" << default_string << " to keep [" << movie.getTicketPrice() << "]): ";
    std::getline(std::cin, input);
    if (input != default_string) movie.setTicketPrice(input);

    cout << "Enter new seat (" << default_string << " to keep [" << movie.getSeat() << "]): ";
    std::getline(std::cin, input);
    if (input != default_string) movie.setSeat(input);

    // Build UPDATE query
    std::string update_query = 
        "UPDATE movie_tb SET "
        "m_name = '" + movie.getName() + "', "
        "m_genre = '" + movie.getGenre() + "', "
        "m_format = '" + movie.getFormat() + "', "
        "m_showdate = '" + movie.getShowDate() + "', "
        "m_showtime = '" + movie.getShowTime() + "', "
        "m_ticketprice = '" + movie.getTicketPrice() + "', "
        "m_seat = '" + movie.getSeat() + "' "
        "WHERE m_id = '" + movie.getIdMovie() + "'";

    QueryResult update_result = DatabaseManager::getInstance()->executeQuery(update_query);

    if (update_result.success) {
        cout << "Movie updated successfully!\n";
    } else {
        cout << "Failed to update movie! Error: " << update_result.error_message << endl;
    }
}

void MovieRepositories::deleteMovie() {
    std::string query = "SELECT m_id, m_name FROM movie_tb";
    QueryResult result = DatabaseManager::getInstance()->executeQuery(query);

    if (!result.success) {
        std::cerr << "Query Execution Problem! Error: " << result.error_message << std::endl;
        return;
    }

    MYSQL_RES* res = result.result.get();
    MYSQL_ROW row;

    cout << "--------------------------------\n";
    cout << "| " << left << setw(5) << "ID"
         << "| " << left << setw(20) << "Name"
         << "|\n";
    cout << "--------------------------------\n";
    while ((row = mysql_fetch_row(res))) {
        cout << "| " << left << setw(5) << (row[0] ? row[0] : "NULL")
             << "| " << left << setw(20) << (row[1] ? row[1] : "NULL")
             << "|\n";
    }
    cout << "--------------------------------\n";

    int id;
    cout << "Enter Movie ID to delete: ";
    std::cin >> id;

    std::string strId = std::to_string(id);

    std::string delete_query = "DELETE FROM movie_tb WHERE m_id = '" + strId + "'";
    QueryResult delete_result = DatabaseManager::getInstance()->executeQuery(delete_query);

    if (delete_result.success) {
        cout << "Movie deleted successfully!\n";
    } else {
        cout << "Failed to delete movie! Error: " << delete_result.error_message << endl;
    }
}


void MovieRepositories::addNewMovie() {
    std::string name, genre, format, show_date, show_time, ticket_price, seat;

    std::cin.ignore(); // Xóa '\n' còn sót lại nếu cần
    cout << "Enter Name: ";
    std::getline(std::cin, name);
    cout << "Enter Genre: ";
    std::getline(std::cin, genre);
    cout << "Enter Format: ";
    std::getline(std::cin, format);
    cout << "Enter Show Date (dd-mm-yyyy): ";
    std::getline(std::cin, show_date);
    cout << "Enter Show Time (hh:mm): ";
    std::getline(std::cin, show_time);
    cout << "Enter Ticket Price: ";
    std::getline(std::cin, ticket_price);
    cout << "Enter Seat: ";
    std::getline(std::cin, seat);

    // Build insert query
    std::string insert_query = 
    "INSERT INTO movie_tb (m_name, m_genre, m_format, m_showdate, m_showtime, m_ticketprice, m_seat) "
    "VALUES ('" + name + "', '" + genre + "', '" + format + "', "
    "STR_TO_DATE('" + show_date + "', '%d-%m-%Y'), '" + show_time + "', '" + ticket_price + "', '" + seat + "')";
    QueryResult insert_result = DatabaseManager::getInstance()->executeQuery(insert_query);

    if (insert_result.success) {
        cout << "Successfully added movie to database.\n";
    } else {
        cout << "Failed to add movie! Error: " << insert_result.error_message << endl;
    }
}