/* ----------------------------------------------------------------------------
 * Copyright &copy; 2016 Ben Blazak <bblazak@fullerton.edu>
 * Released under the [MIT License] (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#include "constants.h"
/**
 * Class implementing an arbitrarily sized 2D character buffer, in which we may
 * draw before outputting the information to the terminal.
 *
 * This way, we don't have to draw characters in order from left to right, then
 * top to bottom.
 *
 * Notes:
 * - We use `exit(1)` here for errors.  Later, we'll go over exceptions, which
 *   would be a much better solution.
 */

#ifndef BUFFER_H
#define BUFFER_H
// ----------------------------------------------------------------------------

#include <string>
#include <cstring>
#include <iostream>
#include "constants.h"
// ----------------------------------------------------------------------------

class Buffer {
    private:
        char * data_;
        /**
         * Our character data.
         *
         * Since we don't know how big the array will be, we can't use a
         * regular (stack allocated) array.  In the constructor, this will be
         * initialized to a 1D array large enough to hold all the values, and
         * we will emulate using it as a 2D array by taking the index as
         * ```
         * data_[ y * size_x + x ];
         * ```
         * (where, if it were a real 2D array, we could have said
         * `data_[y][x]`).
         */


    public:
        const unsigned int size_x = TERM_SIZE_X;
        const unsigned int size_y = TERM_SIZE_Y;

    Buffer(unsigned int size_x, unsigned int size_y)
	{
		data_ = new char[size_x * size_y];
		clear();
	}

    ~Buffer()
	{
		delete [] data_;
	}

    char get(unsigned int x, unsigned int y) const
	{
		if( x > size_x || y > size_y)
		{
			std::cerr << "ERROR: `Buffer::get`: index out of bounds\n";
			exit(1);
		}
		else
			return data_[ y * size_x + x];
	}

    void set(unsigned int x, unsigned int y, char c)
	{
		if( x > size_x || y >=size_y )
		{
			std::cerr << "ERROR: `Buffer::set`: index out of bounds\n";
			exit(1);
		}
		else
			data_[ y * size_x + x ] = c;
	}

        void set(unsigned int pos_x, unsigned int pos_y, std::string s);

		void draw() const {

			for (int y = 0; y < size_y-1; y++) {
				for (int x = 0; x < size_x; x++) {
					std::cout << get(x,y);
				}
				std::cout << std::endl;
			}
		}
        /**
         * Output the contents of the buffer to `cout`.
         */


    void clear()
	{
		data_ = new char[size_x*size_y];
		for (unsigned int i = 0; i < size_x*size_y; i++)
			data_[i] = ' ';
	}
};

// ----------------------------------------------------------------------------
#endif

