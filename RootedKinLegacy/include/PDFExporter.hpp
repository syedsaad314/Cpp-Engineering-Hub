#ifndef PDFEXPORTER_HPP
#define PDFEXPORTER_HPP

#include "PersonNode.hpp"
#include <string>
#include <fstream>

class PDFExporter {
public:
    static bool exportToPrintableHTML(const PersonNode* rootNode, const std::string& filename);

private:
    static void renderNodeHTML(const PersonNode* node, std::ofstream& out, int generation);
};

#endif