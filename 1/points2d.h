// --> FAHIM NAYTIK
// The Points2D class was implemented to manage sequences of 2D points using templates. The focus was on implementing the "big five" (destructor, copy constructor, copy assignment operator, move constructor, and move assignment operator) and overloading the + and [] operators.

#ifndef CSCI335_HOMEWORK1_POINTS2D_H_
#define CSCI335_HOMEWORK1_POINTS2D_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>
// ADDING A NEW COMMENT
namespace teaching_project
{

    template <typename Object>
    class Points2D
    {
    public:
        // Default "big five" -- you have to alter them for your assignment. That means that you will remove the "= default" statement and you will provide an implementation.
        // Zero-parameter constructor. Set size to 0.

        Points2D() : size_(0), sequence_(nullptr) {} // Initializes an empty Points2D object with size 0.

        // Copy-constructor.
        Points2D(const Points2D &rhs) // Creates a deep copy of the given Points2D object.
        {
            size_ = rhs.size_;
            sequence_ = new std::array<Object, 2>[size_];
            for (size_t i = 0; i < size_; ++i)
            {
                sequence_[i] = rhs.sequence_[i];
            }
        }

        // Copy-assignment.
        Points2D &operator=(const Points2D &rhs) // Assigns the given Points2D object to this object.
        {
            if (this != &rhs)
            {
                delete[] sequence_;
                size_ = rhs.size_;
                sequence_ = new std::array<Object, 2>[size_];
                for (size_t i = 0; i < size_; ++i)
                {
                    sequence_[i] = rhs.sequence_[i];
                }
            }
            return *this;
        }

        // Move-constructor.
        Points2D(Points2D &&rhs) : size_(rhs.size_), sequence_(rhs.sequence_) // Transfers ownership of the resources from the given Points2D object to this object.
        {
            rhs.size_ = 0;
            rhs.sequence_ = nullptr;
        }

        // Move-assignment.
        Points2D &operator=(Points2D &&rhs) // Transfers ownership of the resources from the given Points2D object to this object.
        {
            if (this != &rhs)
            {
                delete[] sequence_;
                size_ = rhs.size_;
                sequence_ = rhs.sequence_;
                rhs.size_ = 0;
                rhs.sequence_ = nullptr;
            }
            return *this;
        }

        ~Points2D() // Deallocates the dynamic memory used by the sequence.
        {
            delete[] sequence_;
        }

        // End of big-five.


        // One parameter constructor.
        Points2D(const std::array<Object, 2> &item) // Initializes a Points2D object with a single 2D point.
        {
            size_ = 1;
            sequence_ = new std::array<Object, 2>[1];
            sequence_[0] = item;
        }

        size_t size() const // Returns the size of the sequence.
        {
            return size_;
        }

        // @location: an index to a location in the sequence.
        // @returns the point at @location.
        // const version.
        // abort() if out-of-range.
        const std::array<Object, 2> &operator[](size_t location) const // Returns the point at the given location. Aborts if the location is out-of-range.
        {
            if (location >= size_)
            {
                std::cerr << "ERROR" << std::endl;
                abort();
            }
            return sequence_[location];
        }

        //  @c1: A sequence.
        //  @c2: A second sequence.
        //  @return their sum. If the sequences are not of the same size, append the
        //    result with the remaining part of the larger sequence.
        friend Points2D operator+(const Points2D &c1, const Points2D &c2) // Returns the sum of two Points2D objects.
        {
            Points2D result;
            result.size_ = c1.size_ + c2.size_;
            result.sequence_ = new std::array<Object, 2>[result.size_];
            for (size_t i = 0; i < c1.size_; ++i)
            {
                result.sequence_[i] = c1.sequence_[i];
            }
            for (size_t i = 0; i < c2.size_; ++i)
            {
                result.sequence_[c1.size_ + i] = c2.sequence_[i];
            }
            return result;
        }

        // Overloading the << operator.
        friend std::ostream &operator<<(std::ostream &out, const Points2D &some_points) // Outputs the sequence of points to the given output stream.
        {
            for (size_t i = 0; i < some_points.size_; ++i)
            {
                out << "(" << some_points.sequence_[i][0] << ", " << some_points.sequence_[i][1] << ") ";
            }
            return out;
        }

        // Overloading the >> operator.
        // Read a chain from an input stream (e.g., standard input).
        friend std::istream &operator>>(std::istream &in, Points2D &some_points)
        {
            size_t size;
            in >> size;
            some_points.size_ = size;
            delete[] some_points.sequence_;
            some_points.sequence_ = new std::array<Object, 2>[size];
            for (size_t i = 0; i < size; ++i)
            {
                in >> some_points.sequence_[i][0] >> some_points.sequence_[i][1];
            }
            return in;
        }

    private:
        // Sequence of points.
        std::array<Object, 2> *sequence_;
        // Size of sequence.
        size_t size_;
    };

} // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_Points2D_H_