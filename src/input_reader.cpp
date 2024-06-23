#include "input_reader.h"

#include <fstream>
#include <sstream>

using namespace std;

void InputReader::Read(string& filename) throw() {
    ifstream in(filename.c_str());
    if (!in) {
        std::cout << "Failed to open..." << std::endl;
        return;
    }

    double x, y, z;
    m_vecPoints.clear();
    while (!in.eof()) {
        string line;
        getline(in, line);
        istringstream iss(line);
        iss >> x >> y >> z;
        m_vecPoints.emplace_back(x, y, z);
    }
}

void InputReader::Dump(ostream &os) const noexcept {
    for (const auto & m_vecPoint : m_vecPoints)
        os << m_vecPoint.x << "\t" << m_vecPoint.y << "\t" << m_vecPoint.z << endl;
}