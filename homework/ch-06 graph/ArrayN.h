#ifndef _ARRAYN_H_
#define _ARRAYN_H_
#include <vector>
#include <initializer_list>
#include <iostream>

template<typename T>
class Array3D {
public:
    Array3D(size_t dim1, size_t dim2, size_t dim3)
        : dim1_(dim1), dim2_(dim2), dim3_(dim3), data_(dim1 * dim2 * dim3) {}

    Array3D(std::initializer_list<std::initializer_list<std::initializer_list<T>>> values) {
        dim1_ = values.size();
        dim2_ = values.begin()->size();
        dim3_ = values.begin()->begin()->size();
        data_.resize(dim1_ * dim2_ * dim3_);
        
        size_t i = 0;
        for (const auto& dim1_values : values) {
            for (const auto& dim2_values : dim1_values) {
                for (const auto& value : dim2_values) {
                    data_[i++] = value;
                }
            }
        }
    }

    class Array2D {
    public:
        Array2D(size_t dim2, size_t dim3, std::vector<T>& data, size_t offset)
            : dim2_(dim2), dim3_(dim3), data_(data), offset_(offset) {}

        T& operator[](size_t index) {
            return data_[offset_ + index];
        }

        const T& operator[](size_t index) const {
            return data_[offset_ + index];
        }
        
        Array2D& operator=(const Array2D& other) {
            for (size_t i = 0; i < dim2_ * dim3_; ++i) {
                (*this)[i] = other[i];
            }
            return *this;
        }

    private:
        size_t dim2_;
        size_t dim3_;
        std::vector<T>& data_;
        size_t offset_;
    };

    Array2D operator[](size_t index) {
        size_t offset = index * dim2_ * dim3_;
        return Array2D(dim2_, dim3_, data_, offset);
    }

    const Array2D operator[](size_t index) const {
        size_t offset = index * dim2_ * dim3_;
        return Array2D(dim2_, dim3_, data_, offset);
    }

    Array3D& operator=(const Array3D& other) {
        for (size_t i = 0; i < dim1_ * dim2_ * dim3_; ++i) {
            data_[i] = other.data_[i];
        }
        return *this;
    }

	void display() const {
        for (size_t i = 0; i < dim1_; ++i) {
            for (size_t j = 0; j < dim2_; ++j) {
                for (size_t k = 0; k < dim3_; ++k) {
                    std::cout << data_[(i * dim2_ * dim3_) + (j * dim3_) + k] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
    }

	std::vector<size_t> getDims() const {
        return {dim1_, dim2_, dim3_};
    }

private:
    size_t dim1_;
    size_t dim2_;
    size_t dim3_;
    std::vector<T> data_;
};

#endif
