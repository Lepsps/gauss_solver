#pragma once
#include <iostream>


class Vector {
protected:
    int N_ = 0;
    double* data = nullptr;
public:

    Vector(int N) {
        this->N_ = N;
        this->data = new double[N_];
        for (int i = 0; i < this->N_; i++)
            this->data[i] = 0;
    }

    Vector(const Vector& v) {
        this->N_ = v.N_;
        this->data = new double[N_];
        for (int i = 0; i < N_; i++)
            this->data[i] = v.data[i];
    }

    Vector& operator=(const Vector& v) {
        if (this == &v) return *this;
        if (this->N_ != v.N_) {
            delete[] this->data;
            this->data = new double[v.N_];
        }
        this->N_ = v.N_;
        for (int i = 0; i < v.N_; i++)
            this->data[i] = v.data[i];
        return *this;
    }

    ~Vector() {
        delete[] this->data;
    }

    double operator[](int index) const {
        return this->data[index];
    }

    double& operator[](int index) {
        return this->data[index];
    }

    void Print() {
        for (int i = 0; i < this->N_; i++)
            std::cout << this->data[i] << " ";
        std::cout << std::endl;

    }

    int size() const {
        return this->N_;
    }

    void resize(int N) {
        delete[] this->data;
        this->N_ = N;
        this->data = new double[N_]();
    }

};