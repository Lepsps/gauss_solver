#pragma once

#include <iostream>
#include "Vector.h"
#include "Matrix.h"
#include <vector>


class GaussSolver {
public:
    std::vector<Vector> solve(const Matrix& A, const Vector& b) {
        int rows = A.rows();
        int cols = A.cols();
        double s = 0.0;
        int rank = 0;

        Matrix A_ = A;
        Vector b_ = b;

        std::vector<int> per(cols);
        for (int i = 0; i < cols; i++)
            per[i] = i;

        std::vector<int> ved_col(cols, -1);

        for (int i = 0; i < std::min(rows, cols); i++) {
            int max_col = i;
            int max_row = i;
            double max_elem = 0;
            for (int k = i; k < rows; k++) {
                for (int j = i; j < cols; j++) {
                    if (std::abs(A_(k, j)) > max_elem) {
                        max_elem = std::abs(A_(k, j));
                        max_row = k;
                        max_col = j;
                    }
                }
            }

            if (max_elem == 0)
                break;

            if (max_row != i) {
                for (int j = 0; j < cols; j++) {
                    std::swap(A_(i, j), A_(max_row, j));
                }
                std::swap(b_[i], b_[max_row]);
            }

            if (max_col != i) {
                for (int j = 0; j < rows; j++) {
                    std::swap(A_(j, max_col), A_(j, i));
                }
                std::swap(per[i], per[max_col]);
                std::swap(ved_col[i], ved_col[max_col]);
            }


            for (int k = i + 1; k < rows; k++) {
                double c = -A_(k, i) / A_(i, i);
                for (int j = i; j < cols; j++) {
                    A_(k, j) += c * A_(i, j);
                }
                b_[k] += c * b_[i];
            }
            rank++;
            ved_col[i] = i;
        }

        for (int i = rank; i < rows; i++) {
            if (std::abs(b_[i] - 0.0f) > 1e-12) {
                std::cout << "No solutions " << std::endl;
                return {};
            }
        }

        if (rank < cols) {
            std::vector<Vector> sol;

            std::cout << "Inf solutions" << std::endl;
            Vector st_y(cols);
            for (int i = rank - 1; i >= 0; i--) {
                s = 0.0;
                for (int j = i + 1; j < cols; j++) {
                    s += A_(i, j) * st_y[j];
                }
                st_y[ved_col[i]] = (b_[i] - s) / A_(i, i);
            }
            Vector ed_y(cols);
            for (int i = 0; i < cols; i++) {
                ed_y[per[i]] = st_y[i];
            }
            sol.push_back(ed_y);


            for (int val = 0; val < cols; val++) {
                bool index_check = false;
                for (int k = 0; k < rank; k++) {
                    if (ved_col[k] == val) {
                        index_check = true;
                        break;
                    }
                }
                if (!index_check) {
                    Vector st_basis(cols);
                    st_basis[val] = 1;
                    for (int i = rank - 1; i >= 0; i--) {
                        s = 0.0;
                        for (int j = i + 1; j < cols; j++) {
                            s += A_(i, j) * st_basis[j];
                        }
                        st_basis[ved_col[i]] = (0 - s) / A_(i, i);
                    }
                    Vector ed_basis(cols);
                    for (int i = 0; i < cols; i++) {
                        ed_basis[per[i]] = st_basis[i];
                    }
                    sol.push_back(ed_basis);
                }
            }
            // std::cout << "Basis: " << std::endl;
            // for (int i = 0; i < sol.size(); i++)
            //     sol[i].Print();

            return sol;
        }
        else {
            Vector st_x(cols);
            for (int i = cols - 1; i >= 0; i--) {
                s = 0.0;
                for (int j = i + 1; j < cols; j++) {
                    s += A_(i, j) * st_x[j];
                }
                st_x[ved_col[i]] = (b_[i] - s) / A_(i, i);
            }
            Vector ed_x(cols);
            for (int i = 0; i < cols; ++i) {
                ed_x[per[i]] = st_x[i];
            }

            //std::cout << "One solve: ";
            //ed_x.Print();
            return { ed_x };
        }
    }
};
