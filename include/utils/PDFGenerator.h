#ifndef _PDF_GENERATOR_H
#define _PDF_GENERATOR_H

#include <hpdf.h>
#include <string>
#include "../models/Ticket.h"
#include "../models/Movie.h"
#include "../utils/Logger.h"

struct Info {
    Ticket ticket;
    Movie movie;
};

class IPdfExporter {
public:
    virtual ~IPdfExporter() = default;
    virtual void exportToPdf(const Info& info, const std::string& filename) = 0;
    virtual void setOutputDir(const std::string& dir) = 0;
    virtual std::string getOutputDir() const = 0;
};

class TicketPdfExporter : public IPdfExporter {
private:
    std::string output_dir = ".";
    TicketPdfExporter() = default;

    static void errorHandler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data);

public:
    TicketPdfExporter(const TicketPdfExporter&) = delete;
    TicketPdfExporter& operator=(const TicketPdfExporter&) = delete;

    static TicketPdfExporter& getInstance();

    void exportToPdf(const Info& info, const std::string& filename) override;
    void setOutputDir(const std::string& dir) override;
    std::string getOutputDir() const override;
};

#endif
