#pragma once

#include <string>
#include <vector>
#include "interpolater.h"

using namespace std;

class InputReader {
public:
    InputReader() noexcept = default;
    explicit InputReader(string & filename) noexcept { Read(filename); }
    void Read(string & filename) noexcept;
    const vector<Point3D> &Get3DPoints() const noexcept { return m_vecPoints; }
    void Dump(ostream &os) const noexcept;
private:
    vector<Point3D> m_vecPoints;
};