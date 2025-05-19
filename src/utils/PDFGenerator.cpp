#include "../../include/utils/PDFGenerator.h"

void TicketPdfExporter::errorHandler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data) {
    Logger::getInstance()->log("PDF Error: " + std::to_string(error_no) + ", Detail: " + std::to_string(detail_no), Logger::Level::ERROR);
    std::cerr << "PDF Error: " << error_no << ", Detail: " << detail_no << std::endl;
}

TicketPdfExporter& TicketPdfExporter::getInstance() {
    static TicketPdfExporter instance;
    return instance;
}

void TicketPdfExporter::exportToPdf(const Info& info, const std::string& filename) {
    HPDF_Doc pdf = HPDF_New(errorHandler, nullptr);
    if (!pdf) {
        Logger::getInstance()->log("Error creating PDF document", Logger::Level::ERROR);
        return;
    }

    HPDF_Page page = HPDF_AddPage(pdf);
    HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A6, HPDF_PAGE_PORTRAIT);
    HPDF_Page_SetFontAndSize(page, HPDF_GetFont(pdf, "Helvetica", nullptr), 12);

    HPDF_Page_BeginText(page);
    HPDF_Page_MoveTextPos(page, 40, 380);
    HPDF_Page_ShowText(page, "🎟 Ticket Information");
    HPDF_Page_MoveTextPos(page, 0, -20);

    const Ticket& t = info.ticket;
    const Movie& m = info.movie;

    auto writeLine = [&](const std::string& text) {
        HPDF_Page_ShowText(page, text.c_str());
        HPDF_Page_MoveTextPos(page, 0, -15);
    };

    writeLine("Movie: " + m.getMovieTitle());
    writeLine("Genre: " + m.getMovieGenre());
    writeLine("Seat: " + t.getSeatNumber());
    writeLine("Show Time: " + t.getShowTime());
    writeLine("Price: " + std::to_string(t.getPrice()));
    writeLine("Paid: " + std::string(t.isPaid() ? "Yes" : "No"));

    HPDF_Page_EndText(page);

    std::string full_path = output_dir + "/" + filename;
    if (HPDF_SaveToFile(pdf, full_path.c_str()) != HPDF_OK) {
        Logger::getInstance()->log("Error saving PDF file", Logger::Level::ERROR);
    }

    HPDF_Free(pdf);
}

void TicketPdfExporter::setOutputDir(const std::string& dir) {
    output_dir = dir;
}

std::string TicketPdfExporter::getOutputDir() const {
    return output_dir;
}
