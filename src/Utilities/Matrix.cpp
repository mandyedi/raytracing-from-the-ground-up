//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.

//  Copyright notice for changes since the originally published version:
//  Copyright (C) Eduárd Mándy 2019-2025
//  Though this C++ code was change in a large measure it still has the original copyright notice.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.

#include "Matrix.h"

Matrix Matrix::operator*(const Matrix& mat) const {
    Matrix product;

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            float sum = 0.0f;

            for (int j = 0; j < 4; j++) {
                sum += m[x][j] * mat.m[j][y];
            }

            product.m[x][y] = sum;
        }
    }

    return product;
}

Matrix Matrix::operator/(const float d) {
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            m[x][y] = m[x][y] / d;
        }
    }

    return *this;
}

void Matrix::set_identity() {
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            if (x == y) {
                m[x][y] = 1.0f;
            } else {
                m[x][y] = 0.0f;
            }
        }
    }
}
