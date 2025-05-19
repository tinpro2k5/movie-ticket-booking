#include <cassert>
#include <fstream>
#include "../exporters/PdfExporter.h" // Đường dẫn đến file header
#include "../models/Ticket.h"
#include "../models/Movie.h"

void test_exportToPdf_createsFile() {
    // Tạo dữ liệu mẫu
    Ticket ticket(1, 1, 101, 5, "C3", "2025-05-19 18:00", 95000, "2025-05-18 10:00", true);
    Movie movie(2, "Avengers: Endgame", "Action", "Superhero final battle", 180, 8.5f, "", 95000);

    Info info = { ticket, movie };
    std::string filename = "test_ticket_output.pdf";

    // Gọi hàm tạo PDF
    TicketPdfExporter exporter;
    exporter.exportToPdf(info, filename);

    // Kiểm tra xem file đã được tạo
    std::ifstream file(filename);
    assert(file.good() && "PDF file should be created");
    file.close();

    // (Tùy chọn) Xóa file sau khi kiểm tra
    std::remove(filename.c_str());

    std::cout << "✅ test_exportToPdf_createsFile passed.\n";
}

int main() {
    test_exportToPdf_createsFile();
    return 0;
}
