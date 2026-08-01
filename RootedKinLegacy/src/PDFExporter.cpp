#include "../include/PDFExporter.hpp"
#include <fstream>
#include <iostream>

bool PDFExporter::exportToPrintableHTML(const PersonNode* rootNode, const std::string& filename) {
    if (!rootNode) return false;

    std::ofstream out(filename);
    if (!out.is_open()) return false;

    out << R"HTML(<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Rooted Kin Legacy - Professional Family Tree Report</title>
    <style>
        @page { size: A3 landscape; margin: 10mm; }
        body { font-family: 'Inter', 'Segoe UI', Arial, sans-serif; background: #0f172a; color: #f8fafc; margin: 0; padding: 20px; }
        
        .header { text-align: center; border-bottom: 2px solid #38bdf8; padding-bottom: 15px; margin-bottom: 30px; }
        .ascii-title {
            font-family: 'Courier New', Courier, monospace;
            font-weight: bold;
            font-size: 9px;
            line-height: 1.15;
            color: #38bdf8;
            white-space: pre;
            display: inline-block;
            text-align: left;
            margin: 0 auto;
        }
        .header p { margin: 12px 0 0 0; color: #94a3b8; font-weight: 700; letter-spacing: 3px; font-size: 14px; }
        
        .tree-viewport { display: flex; justify-content: center; overflow-x: auto; padding: 20px 0; }
        .tree ul { padding-top: 25px; position: relative; transition: all 0.5s; display: flex; justify-content: center; }
        .tree li { float: left; text-align: center; list-style-type: none; position: relative; padding: 25px 10px 0 10px; }
        
        .tree li::before, .tree li::after { content: ''; position: absolute; top: 0; right: 50%; border-top: 2px solid #64748b; width: 50%; height: 25px; }
        .tree li::after { right: auto; left: 50%; border-left: 2px solid #64748b; }
        .tree li:only-child::after, .tree li:only-child::before { display: none; }
        .tree li:only-child { padding-top: 0; }
        .tree li:first-child::before, .tree li:last-child::after { border: none; }
        .tree li:last-child::before { border-right: 2px solid #64748b; border-radius: 0 6px 0 0; }
        .tree li:first-child::after { border-radius: 6px 0 0 0; }
        .tree ul ul::before { content: ''; position: absolute; top: 0; left: 50%; border-left: 2px solid #64748b; width: 0; height: 25px; }
        
        .card {
            background: #1e293b;
            border: 2px solid #0284c7;
            border-radius: 10px;
            padding: 12px 20px;
            display: inline-block;
            min-width: 150px;
            box-shadow: 0 10px 15px -3px rgba(0, 0, 0, 0.5);
        }
        .card.female { border-color: #ec4899; }
        .name { font-weight: 700; font-size: 16px; color: #ffffff; }
        .badge { display: inline-block; padding: 2px 8px; border-radius: 12px; font-size: 11px; font-weight: 600; margin-top: 6px; }
        .badge-male { background: #0369a1; color: #e0f2fe; }
        .badge-female { background: #be185d; color: #fce7f3; }
        .spouse { background: #334155; color: #fbbf24; border: 1px solid #d97706; margin-top: 8px; font-size: 12px; padding: 4px 8px; border-radius: 6px; }

        @media print {
            body { background: white; color: black; padding: 0; }
            .no-print { display: none; }
            .ascii-title { color: #0284c7; }
            .header p { color: #334155; }
            .card { background: #f8fafc; border-color: #000; box-shadow: none; }
            .name { color: #000; }
            .tree li::before, .tree li::after, .tree ul ul::before { border-color: #000; }
        }
    </style>
</head>
<body>
    <div class="no-print" style="text-align: center; margin-bottom: 25px;">
        <button onclick="window.print()" style="background:#0284c7; color:white; padding:12px 30px; border:none; border-radius:8px; font-weight:bold; font-size:16px; cursor:pointer;">
            🖨️ Print Report / Save Vector PDF
        </button>
    </div>

    <div class="header">
        <pre class="ascii-title">
  ██████╗  ██████╗  ██████╗ ████████╗███████╗██████╗     ██╗  ██╗██╗███╗   ██╗
  ██╔══██╗██╔═══██╗██╔═══██╗╚══██╔══╝██╔════╝██╔══██╗    ██║ ██╔╝██║████╗  ██║
  ██████╔╝██║   ██║██║   ██║   ██║   █████╗  ██║  ██║    █████╔╝ ██║██╔██╗ ██║
  ██╔══██╗██║   ██║██║   ██║   ██║   ██╔══╝  ██║  ██║    ██╔═██╗ ██║██║╚██╗██║
  ██║  ██║╚██████╔╝╚██████╔╝   ██║   ███████╗██████╔╝    ██║  ██╗██║██║ ╚████║
  ╚═╝  ╚═╝ ╚═════╝  ╚═════╝    ╚═╝   ╚══════╝╚═════╝     ╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝
  ██╗     ███████╗ ██████╗  █████╗  ██████╗ ██╗  ██╗
  ██║     ██╔════╝██╔════╝ ██╔══██╗██╔════╝ ╚██╗██╔╝
  ██║     █████╗  ██║  ███╗███████║██║       ╚███╔╝ 
  ██║     ██╔══╝  ██║   ██║██╔══██║██║        ██║   
  ███████╗███████╗╚██████╔╝██║  ██║╚██████╗   ██║   
  ╚══════╝╚══════╝ ╚═════╝ ╚═╝  ╚═╝ ╚═════╝   ╚═╝   </pre>
        <p>AUTHENTIC LINEAGE GRAPH & GENERATION TREE REPORT</p>
    </div>

    <div class="tree-viewport">
        <div class="tree">
            <ul>
)HTML";

    renderNodeHTML(rootNode, out, 1);

    out << R"HTML(
            </ul>
        </div>
    </div>
</body>
</html>)HTML";

    out.close();
    return true;
}

void PDFExporter::renderNodeHTML(const PersonNode* node, std::ofstream& out, int generation) {
    if (!node) return;

    bool isFemale = (node->getGender() == Gender::Female);
    out << "<li>\n";
    out << "  <div class=\"card " << (isFemale ? "female" : "male") << "\">\n";
    out << "    <div class=\"name\">" << node->getName() << "</div>\n";
    out << "    <div class=\"badge " << (isFemale ? "badge-female" : "badge-male") << "\">GEN " << generation << " • " << (isFemale ? "Female" : "Male") << "</div>\n";

    if (node->getSpouse() != nullptr) {
        out << "    <div class=\"spouse\">♥ " << node->getSpouse()->getName() << "</div>\n";
    }

    out << "  </div>\n";

    const auto& children = node->getChildren();
    if (!children.empty()) {
        out << "  <ul>\n";
        for (const auto* child : children) {
            renderNodeHTML(child, out, generation + 1);
        }
        out << "  </ul>\n";
    }
    out << "</li>\n";
}