#pragma once
#include <iostream>
#include <vector>

class Matrix {
protected:
    int rows_ = 0;
    int cols_ = 0;
    std::vector<std::vector<double>> data;
public:
    Matrix(int rows, int cols) {
        this->rows_ = rows;
        this->cols_ = cols;
        for (int i = 0; i < rows; i++) {
            std::vector<double> row;
            for (int j = 0; j < cols; j++)
                row.push_back(0);
            this->data.push_back(row);
        }
    }

    double operator()(int ind_row, int ind_col) const {
        return this->data[ind_row][ind_col];
    }

    double& operator()(int ind_row, int ind_col) {
        return this->data[ind_row][ind_col];
    }

    int rows() const { return this->rows_; }
    int cols() const { return this->cols_; }

    void Print() const {
        for (int i = 0; i < this->rows_; i++) {
            for (int j = 0; j < this->cols_; j++)
                std::cout << this->data[i][j] << " ";
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};

